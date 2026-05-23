#!/usr/bin/env python3
"""
auto_patch_plat.py — iterate stockport boot → patch → rebuild loop.

Handles several crash classes:
  1. Crash AT a plat instruction (ldr/str with bad offset) — patch offset
  2. Crash IN kernel function called by plat (e.g. __memzero, register_netdev)
     — find the plat-level caller in backtrace, disasm there, patch the bad call
  3. Already covered manually: known struct offset shifts, NOPed accesses
  4. Falls back to NOP if we can't identify the right fix

After each iteration: rebuild shim (in case shim source was edited) + kernel.
"""
import os, re, subprocess, sys, struct
from pathlib import Path

ROOT = Path("/home/ubuntu/Projects/MYSELF/ZTE/zxic")
KMOD_SRC = ROOT / "rootfs/kmodule/plat-zxylzb_9128S.ko"
KMOD_PATCHED = Path("/tmp/plat_patched.ko")
KMOD_DEPLOY = Path("/tmp/initramfs_stockport/lib/modules/4.1.25/plat-zxylzb_9128S.ko")
SHIM_DIR = ROOT / "linux-stockport/zte_shim"
SHIM_DEPLOY = Path("/tmp/initramfs_stockport/lib/modules/4.1.25/zte_shim.ko")
UART_LOG = Path("/tmp/uart.log")
BUILD_SH = ROOT / "linux-stockport/build.sh"

TOOLCHAIN = os.path.expanduser("~/toolchains/armv7-eabihf--glibc--stable-2018.11-1/bin")
OBJDUMP = TOOLCHAIN + "/arm-buildroot-linux-gnueabihf-objdump"

# Stock → Ours offset map for `struct net_device`.
# Derived from:
#  - memory dump of stock pon_tm_netdev (offsets 0..0x200)
#  - disasm comparison of register_netdevice, alloc_etherdev_mqs,
#    free_netdev, netif_set_real_num_tx_queues (stock via /proc/tm/shell
#    vs ours via objdump)
# See struct_offset_diff.py and /tmp/stock_dumps/.
NETDEV_MAP = {
    0x12C: 0x124,   # netdev_ops (Δ -8)
    0x138: 0x130,   # name_hash or similar (Δ -8)
    0x180: 0x174,   # tx_dropped or similar (Δ -12)
    0x420: 0x418,   # tx queue counters (Δ -8)
    0x1DC: None,    # ZTE-custom pointer; ours has u32 here → NOP
}
# sk_buff map: TODO
SKB_MAP = {}

NOP = 0xE1A00000
PATCHED_OFFSETS = set()

def run(cmd, timeout=600, env=None):
    print(f"  $ {cmd[:200]}", flush=True)
    return subprocess.run(cmd, shell=True, capture_output=True, text=True,
                          timeout=timeout, env=env)

def apply_known_patches():
    """Reset to original .ko + apply our manually-verified patches +
    apply the known stock→ours offset map to ALL [r4, #X] accesses in plat."""
    KMOD_PATCHED.write_bytes(KMOD_SRC.read_bytes())
    data = bytearray(KMOD_PATCHED.read_bytes())
    fixed = [
        (b'\xdc\xc1\x94\xe5', b'\x00\x00\xa0\xe1', 'idm_net_register: ldr ip,[r4,#0x1DC] → NOP'),
        (b'\xdc\x11\x94\xe5', b'\x00\x00\xa0\xe1', 'pon_tm_net_register: ldr r1,[r4,#0x1DC] → NOP'),
        (b'\x00\x00\x81\xe5', b'\x00\x00\xa0\xe1', 'pon_tm_net_register: str r0,[r1] → NOP'),
        (b'\xb4\x20\xc1\xe1', b'\x00\x00\xa0\xe1', 'pon_tm_net_register: strh r2,[r1,#4] → NOP'),
        (b'\x00\x00\x8c\xe5', b'\x00\x00\xa0\xe1', 'idm_net_register: str r0,[ip] → NOP'),
        (b'\xb4\x20\xcc\xe1', b'\x00\x00\xa0\xe1', 'idm_net_register: strh r2,[ip,#4] → NOP'),
    ]
    for old, new, desc in fixed:
        n = data.count(old)
        if n:
            data = data.replace(old, new)
            print(f"  base patch: {desc} ({n}x)")

    # Bulk patch: for each known mapping, scan for `ldr/str Rx, [r4, #stock]`
    # and rewrite to `[r4, #ours]`.
    def is_ldr_str_r4_word_pos(op):
        if (op >> 28) != 0xE: return False                 # cond=always
        if ((op >> 25) & 0x7) != 0x2: return False         # type bits 27-25 = 010
        p = (op >> 24) & 1; u = (op >> 23) & 1
        b = (op >> 22) & 1; w = (op >> 21) & 1
        rn = (op >> 16) & 0xF
        return p == 1 and u == 1 and w == 0 and rn == 4 and b == 0
    patched_imms = 0
    for i in range(0, len(data) - 3, 4):
        op = struct.unpack_from('<I', data, i)[0]
        if not is_ldr_str_r4_word_pos(op): continue
        imm = op & 0xFFF
        if imm not in NETDEV_MAP: continue
        new_imm = NETDEV_MAP[imm]
        if new_imm is None:
            new_op = 0xE1A00000  # NOP
            print(f"    NOP @ 0x{i:x} (was [r4,#0x{imm:03x}])")
        else:
            new_op = (op & ~0xFFF) | new_imm
            print(f"    @ 0x{i:x}: [r4,#0x{imm:03x}] → [r4,#0x{new_imm:03x}]")
        struct.pack_into('<I', data, i, new_op)
        patched_imms += 1
    print(f"  bulk: patched {patched_imms} [r4, #...] accesses via NETDEV_MAP")

    KMOD_PATCHED.write_bytes(bytes(data))

def boot_and_get_log(timeout_s=250):
    if UART_LOG.exists(): UART_LOG.unlink()
    cmd = f"cd {ROOT} && timeout {timeout_s} python3 uart.py auto_bootm_stockport"
    run(cmd, timeout=timeout_s + 30)
    return UART_LOG.read_text(errors='replace') if UART_LOG.exists() else ""

def parse_plat_call_stack(log):
    """Returns list of (func, offset) for plat frames in the backtrace,
    deepest-first. Also captures crash PC if directly in plat."""
    frames = []
    pc = re.search(r"PC is at (\w+)\+0x([0-9a-fA-F]+)/0x[0-9a-fA-F]+ \[plat_zxylzb_9128S\]", log)
    if pc:
        frames.append((pc.group(1), int(pc.group(2), 16)))
    for m in re.finditer(r"\[<[0-9a-f]+>\] \((\w+) \[plat_zxylzb_9128S\]\) from \[<[0-9a-f]+>\] \((\w+)\+0x([0-9a-fA-F]+)/", log):
        frames.append((m.group(1), None))  # callee, return PC isn't here
    # Also pick up the format "called_func from plat_caller+0xOFFSET"
    for m in re.finditer(r"\[<[0-9a-f]+>\] \(\w+\) from \[<[0-9a-f]+>\] \((\w+)\+0x([0-9a-fA-F]+)/0x[0-9a-fA-F]+ \[plat_zxylzb_9128S\]\)", log):
        frames.append((m.group(1), int(m.group(2), 16)))
    return frames

def disasm_func_at(func_name, instr_offset):
    """Return (file_byte_offset, opcode, asm_text) or None."""
    r = run(f"{OBJDUMP} -d {KMOD_PATCHED} | awk '/<{func_name}>:/,/^$/' | head -300")
    out = r.stdout
    m = re.search(rf"^([0-9a-f]+) <{re.escape(func_name)}>:", out, re.M)
    if not m: return None
    func_base = int(m.group(1), 16)
    target_addr = func_base + instr_offset
    line = re.search(rf"^\s*{target_addr:x}:\s+([0-9a-f]{{8}})\s+(.+)$", out, re.M)
    if not line: return None
    opcode = int(line.group(1), 16)
    asm = line.group(2).strip()
    file_data = KMOD_PATCHED.read_bytes()
    opcode_bytes = struct.pack('<I', opcode)
    cnt = file_data.count(opcode_bytes)
    if cnt != 1:
        # need surrounding context to find unique
        return None
    pos = file_data.find(opcode_bytes)
    return pos, opcode, asm

def decode_ldr_str_offset(opcode):
    cond = (opcode >> 28) & 0xF
    if cond != 0xE: return None
    typ = (opcode >> 20) & 0xF0
    if typ not in (0x50, 0x90): return None
    return opcode & 0xFFF

def patch_instr(file_offset, new_opcode):
    data = bytearray(KMOD_PATCHED.read_bytes())
    old = bytes(data[file_offset:file_offset+4])
    new = struct.pack('<I', new_opcode)
    data[file_offset:file_offset+4] = new
    KMOD_PATCHED.write_bytes(bytes(data))
    print(f"  patched offset 0x{file_offset:x}: {old.hex()} → {new.hex()}")

def rebuild_shim():
    """If shim source newer than current .ko, rebuild it."""
    src = SHIM_DIR / "zte_shim.c"
    ko = SHIM_DIR / "zte_shim.ko"
    if not ko.exists() or src.stat().st_mtime > ko.stat().st_mtime:
        print("  rebuilding shim (source modified) ...")
        r = run(f"cd {SHIM_DIR} && PATH={TOOLCHAIN}:$PATH ARCH=arm "
                f"CROSS_COMPILE=arm-buildroot-linux-gnueabihf- make 2>&1 | tail -5",
                timeout=120)
        print(r.stdout[-500:])
        if not ko.exists():
            return False
    # always deploy
    import shutil
    shutil.copy(ko, SHIM_DEPLOY)
    return True

def rebuild_and_deploy():
    import shutil
    if not rebuild_shim(): return False
    shutil.copy(KMOD_PATCHED, KMOD_DEPLOY)
    r = run(f"cd {BUILD_SH.parent} && ./build.sh kernel && ./build.sh deploy",
            timeout=400)
    return "Image is ready" in r.stdout or "Image is ready" in r.stderr

def handle_crash(log):
    """Identify plat crash + apply patch. Returns True if a patch was made."""
    frames = parse_plat_call_stack(log)
    if not frames:
        return False
    # Try each frame, deepest first (the PC-level)
    for func, off in frames:
        if off is None: continue
        key = (func, off)
        if key in PATCHED_OFFSETS:
            continue  # already tried
        d = disasm_func_at(func, off)
        if not d:
            print(f"  could not uniquely identify instr at {func}+0x{off:x}")
            continue
        file_off, opcode, asm = d
        print(f"  crash frame: {func}+0x{off:x}  instr: {asm}")
        imm = decode_ldr_str_offset(opcode)
        if imm is not None:
            new_imm = NETDEV_MAP.get(imm, 'UNKNOWN')
            if new_imm == 'UNKNOWN':
                # NOP as fallback
                patch_instr(file_off, NOP)
                print(f"  NOPed (no map for offset 0x{imm:x})")
            elif new_imm is None:
                patch_instr(file_off, NOP)
                print(f"  NOPed (offset 0x{imm:x} known unmappable)")
            else:
                new_op = (opcode & ~0xFFF) | new_imm
                patch_instr(file_off, new_op)
                print(f"  remapped offset 0x{imm:x} → 0x{new_imm:x}")
        else:
            # not a load/store with simple imm — NOP it
            patch_instr(file_off, NOP)
            print(f"  NOPed (not a ldr/str-imm pattern)")
        PATCHED_OFFSETS.add(key)
        return True
    return False

def main():
    apply_known_patches()
    print(f"Initial patches applied. Starting iteration loop.")

    for it in range(1, 31):
        print(f"\n========== Iteration {it} ==========")
        if not rebuild_and_deploy():
            print("BUILD FAILED — stop"); return 1
        print("Booting stockport...")
        log = boot_and_get_log(timeout_s=240)

        # Success markers
        if "Welcome" in log or "STOCKPORT INIT DONE" in log or "tm OK" in log:
            print("✓ BOOT REACHED USERSPACE / TM LOADED")
            return 0

        # Handle TFTP transient
        if "Retry count exceeded" in log:
            print("TFTP transient — repeating iteration")
            continue

        if not handle_crash(log):
            print("Could not identify any patchable plat crash. Stop.")
            print("--- last 50 log lines ---")
            print("\n".join(log.splitlines()[-50:]))
            return 1

    print("Hit max iterations.")
    return 1

if __name__ == "__main__":
    sys.exit(main())
