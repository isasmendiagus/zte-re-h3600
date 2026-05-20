#!/usr/bin/env python3
"""Flash a uImage to slot A in NAND, fully automated.

Workflow:
  1. Pad input uimg to a NAND-erase-block multiple (0x20000 = 128 KiB) with 0xff
  2. Compute kernel csp_crc = zlib.crc32 over padded data
  3. Patch header_A_modified.bin with new size + new CRC at offsets 0x38 / 0x3c
  4. Wait for U-Boot via uart.py auto wait, drive prompts
  5. tftp slotA.bin -> nand erase + write at 0x700000
  6. tftp header_A.bin -> nand erase + write at 0x2080000
  7. setenv autorun "" + saveenv + reset

Usage:
  ./flash_kernel_to_nand.py <input_uimg>            # default tftp/zImage_dtb.uimg
"""
import os, sys, struct, zlib, time, threading
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from uart import open_port, send_slow, log_loop, _wait_for_boot_and_drive_prompts, LOG

TFTP_DIR = "/home/ubuntu/Projects/MYSELF/ZTE/H3600/tftp"
NAND_ERASE_BLOCK = 0x20000      # 128 KiB
SLOT_A_KERNEL_OFF = 0x700000
SLOT_A_KERNEL_MAX = 0x1980000   # 25 MiB available
HEADER_A_OFF = 0x2080000
HEADER_A_SIZE = 0x20000          # 1 erase block

PORT_IP = "192.168.1.1"
SERVER_IP = "192.168.1.50"

CRC_OFFSET = 0x3C       # kernel csp_crc (LE u32)
SIZE_OFFSET = 0x38      # kernel size in header (LE u32) — observed
HDR_CRC_OFFSET = 0xA4   # BootPara header CRC (zlib.crc32 of header[0..0xa4])

HDR_TEMPLATE = os.path.join(TFTP_DIR, "header_A_modified.bin")

def pad_uimg(src_path, dst_path):
    data = open(src_path, "rb").read()
    sz = len(data)
    padded_sz = ((sz + NAND_ERASE_BLOCK - 1) // NAND_ERASE_BLOCK) * NAND_ERASE_BLOCK
    if padded_sz > SLOT_A_KERNEL_MAX:
        raise SystemExit(f"uimg ({sz} B) padded to {padded_sz} B exceeds slot A max {SLOT_A_KERNEL_MAX} B")
    padded = data + b"\xff" * (padded_sz - sz)
    open(dst_path, "wb").write(padded)
    crc = zlib.crc32(padded) & 0xFFFFFFFF
    print(f"[+] padded {sz} -> {padded_sz} B, crc32=0x{crc:08x}, wrote {dst_path}")
    return padded_sz, crc

def patch_header(template, dst, kernel_size, kernel_crc):
    hdr = bytearray(open(template, "rb").read())
    struct.pack_into("<I", hdr, SIZE_OFFSET, kernel_size)
    struct.pack_into("<I", hdr, CRC_OFFSET, kernel_crc)
    # Recalculate the BootPara header CRC over [0..0xA4)
    new_hdr_crc = zlib.crc32(bytes(hdr[:HDR_CRC_OFFSET])) & 0xFFFFFFFF
    struct.pack_into("<I", hdr, HDR_CRC_OFFSET, new_hdr_crc)
    open(dst, "wb").write(bytes(hdr))
    print(f"[+] header_A patched: size=0x{kernel_size:x}, csp_crc=0x{kernel_crc:08x}, hdr_crc=0x{new_hdr_crc:08x}")

def main():
    src = sys.argv[1] if len(sys.argv) > 1 else os.path.join(TFTP_DIR, "zImage_dtb.uimg")
    if not os.path.isfile(src):
        raise SystemExit(f"missing {src}")

    slotA_bin = os.path.join(TFTP_DIR, "slotA.bin")
    header_bin = os.path.join(TFTP_DIR, "header_A.bin")

    kernel_size, kernel_crc = pad_uimg(src, slotA_bin)
    patch_header(HDR_TEMPLATE, header_bin, kernel_size, kernel_crc)

    # Round size to nand write block (also 0x20000)
    nand_write_size = ((kernel_size + NAND_ERASE_BLOCK - 1) // NAND_ERASE_BLOCK) * NAND_ERASE_BLOCK

    cmds = [
        (f"setenv ipaddr {PORT_IP}",                              2),
        (f"setenv serverip {SERVER_IP}",                          2),
        ("tftp 0x42000000 slotA.bin",                             60),
        (f"nand erase {SLOT_A_KERNEL_OFF:#x} {SLOT_A_KERNEL_MAX:#x}", 20),
        (f"nand write 0x42000000 {SLOT_A_KERNEL_OFF:#x} {nand_write_size:#x}", 90),
        ("tftp 0x42000000 header_A.bin",                          8),
        (f"nand erase {HEADER_A_OFF:#x} {HEADER_A_SIZE:#x}",      5),
        (f"nand write 0x42000000 {HEADER_A_OFF:#x} {HEADER_A_SIZE:#x}", 8),
        ('setenv autorun ""',                                      2),
        ("saveenv",                                                5),
        ("reset",                                                  2),
    ]

    print("\n>>> Power-cycle the modem now to start the boot sequence...")
    ser = open_port()
    if not _wait_for_boot_and_drive_prompts(ser):
        print("ERROR: U-Boot prompt not reached")
        return 1

    print("\n>>> U-Boot reached. Streaming output to terminal + log...\n")
    fout = open(LOG, "ab")
    stop = threading.Event()
    t = threading.Thread(target=log_loop, args=(ser, fout, stop, True))
    t.start()
    time.sleep(1)
    for i, (cmd, wait) in enumerate(cmds, 1):
        print(f"\n>>> [{i}/{len(cmds)}] {cmd}  (wait {wait}s)")
        send_slow(ser, cmd)
        time.sleep(wait)

    print("\n>>> All commands sent. Modem is rebooting now.")
    print(">>> Watching boot output — Ctrl+C to stop.\n")
    try:
        while True: time.sleep(1)
    except KeyboardInterrupt:
        stop.set(); t.join(); fout.close()
    return 0

if __name__ == "__main__":
    sys.exit(main())
