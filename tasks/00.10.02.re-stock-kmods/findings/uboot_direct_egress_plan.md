# U-Boot direct-mux CPU-TX egress — full trace + mainline replication plan (2026-05-28)

Goal: replicate U-Boot's **proven-working** CPU→LAN egress, which bypasses the
PP_BRG fabric and uses the **ETH_TM2 direct mux** (0x923a0000). Mainline's
fabric egress dies at DSCH→SOPC (no `send2smacN`, SMAC[N] TX never increments).
U-Boot's path is simpler and known to put bytes on the wire on this exact chip.

Source: `tasks/00.10.03.re-uboot/findings/uboot_eth_decomp/FUN_*.c`. Driver:
`linux-v6.6/drivers/net/ethernet/zte/zx-eth-main.c`.

Physical→driver address map (both already mapped, no new ioremap):
- `e->fpga_base` = ioremap(0x92000000, 0x400000) → any phys X = `e->fpga_base + (X - 0x92000000)`.
- `e->base` = npp window (0x921c0000) → ETH_TM2 = `e->base + 0x1e0000` = phys 0x923a0000.
- ETH_TM2 phys 0x923a0000 = `e->fpga_base + 0x3a0000` = `e->base + 0x1e0000`. Use either.
- PP-block phys 0x92380000 = `e->fpga_base + 0x380000`. 0x9238c000 = `+0x38c000`.
  (Note: existing `zx_pp_brg_init` already uses `e->fpga_base + 0x380000` for PP_BRG.)
- sys_ctrl reset reg phys 0x92000008 = `e->fpga_base + 0x8`.
- QMG phys 0x921cc000 = `e->base + 0xc000` (TM_OFF is 0x180000, so this is NOT tm_*;
  it is `e->base + 0xc000` directly, == the QMG block at npp+0xc000).

---

## 1. The full U-Boot CPU-TX bring-up call tree

Entry that wires the direct mux: **FUN_40e4fda4** (eth init "lan up"):
```
FUN_40e4fda4:
  FUN_40e50384()            # TM/SCH/DSCH/BMU + MAC-slot-table + DMA bring-up
  FUN_40e50b0c()            # PP block bring-up (0x92380000/0x9238c000/0x92388000) + ETH_TM2 clear
  FUN_40e50f20()            # SCH/RED per-queue + QMG[0]=0x11
  *(0x923a0000 + 0xe0) = 0x11      # <<< THE DIRECT EGRESS MUX ENABLE
```
Separately, **FUN_40e50440** does per-MAC/PHY bring-up (FUN_40e4fe04 + 4× FUN_40e50c40),
which is the smac_init equivalent and pulses the per-port sys_ctrl reset.

### 1a. PP-block bring-up + ETH_TM2 reset (FUN_40e50b0c)
```
FUN_40e50b34:  *0x92380000      = 2          # PP master reset/enable, then ~1ms delay
FUN_40e50a9c:  (PP_BRG @ 0x92388000)  ← already replicated by zx_pp_brg_init
                 +0x004 = 0x000200ff
                 +0x340 = 0xff5555ff
                 +0x344 = 0x3e
                 +0x380 = 0x3f
                 +0x63c = 0xaaaaaaaa
                 +0x1c0 = 0xff
                 +0x1c4 = 0x5555
                 +0x188 = 0x000bf874
                 +0x2c0 = 0xff
                 +0x300 = 0xffff
                 +0x304 = 0x3e
FUN_40e50a60:  (0x9238c000)  ← NOT in mainline; this is the ETH_TM2/PP-mux sub-block
                 +0x80 = 0x309a
                 +0x88 = 0
                 +0xcc = 1
ETH_TM2 clear: *(0x923a0000 + 0x10) = 0      # clear mux state
               *(0x923a0000 + 0x14) = 0
```
**FUN_40e50b34's `*0x92380000=2` is the PP master enable that also gates the ETH_TM2
mux block. FUN_40e50a60's `0x9238c000` writes (+0x80=0x309a, +0xcc=1) are the
ETH_TM2-mux clock/enable. Mainline does NEITHER → ETH_TM2 reads 0 / not clocked.**

### 1b. MAC-slot table (DA→slot mapping) — FUN_40e50978 → FUN_40e4fd24
```
FUN_40e4fd24(slot, mac6):   # slot < 4
  *(0x923a0078 + slot*8) = mac[3]<<16 | mac[2]<<24 | mac[5] | mac[4]<<8   # low 4 bytes, byte-swapped
  *(0x923a007c + slot*8) = mac[0]<<8 | mac[1]                              # high 2 bytes (CONCAT11(mac0,mac1))
```
U-Boot programs **slot 0** with the device MAC (`DAT_40e50994 = 0x47f4af88`, the
board MAC stored in RAM). Encoding: the two-word slot holds the 6-byte MAC; the
direct mux matches DA against these slots to pick the egress port. For our single
host/egress port we only need slot used by the mux (slot 0 here). Reg layout:
`0x923a0078 + slot*8` = MAC low word, `0x923a007c + slot*8` = MAC high word.

### 1c. QMG + SCH/RED (FUN_40e50f20)
```
*(0x921c0000 + 0x08) = 0xffffffff ; delay ; *(0x921c0000 + 0x0c) = 0xffffffff ; delay
FUN_40e50b84:  SCH @ 0x921d4000 — 8× FUN_40e50b58(q,1) per-queue init, then:
                 [0x00]=0x30000000 [0x04]=0x8800 [0x40]=0x30000000 [0x44]=0x8800 [0x1c0]=0x11000000
FUN_40e50ed4:  RED — 4× ([0x47f5969c+i*4]=0xffffffff ; FUN_40e50eb0(i,0))
FUN_40e50f0c:  *0x921cc000 = 0x11      # QMG[0] = 0x11  (the QMG forward-mode for direct egress)
*(0x921c0000 + 0x48) = 0
```

### 1d. TM/DMA + BMU bring-up (FUN_40e50384, mostly already in mainline)
- FUN_40e501f8: CLA/classify table fill (0x92344000 indirect, 400+0x180+0x180 entries).
- FUN_40e50348: DMA mode `0x92350000` low-nibble = 0x2x0000; ring bases `+0x50/+0x60`, `+0x3c=0x00400040`.
- FUN_40e4fe5c: BMU `0x92348000` init (+1/+2=0x0104c040, pool tables) — mirrors mainline `zx_tm_pools_init`.
- FUN_40e4ff74: `*0x92348000 = 1` (BMU go).
- `*(0x92340000+0xf0)=0x41a00000 ; +0x04=0x10` ; FUN_40e50978 (slot table) ; FUN_40e50a4c (`*0x9234c000+4=0`).

### 1e. Per-MAC bring-up (FUN_40e50c40) — smac_init equivalent (mainline has this)
Per port N (base 0x92200000 + N*0x40000): pulse `FUN_40e4fdcc(1<<(N+6))` (sys_ctrl
0x92000008 per-port reset), then ctrl=`0x00bbe003`, ena=`0x80000001`, `+0xe0=0x00011200`,
`+0xc20=0x32`, `+0xc50=0xa8`, `+0x070=0x00300002`, `+0x0b4=0x4000`, `+0xb00=0x0010ff11`,
`MAC[N][0] |= 3`. **Mainline zx_smac_init_port already replicates all of this.**

---

## 2. The TX descriptor format + ring + kick (FUN_40e50854 / FUN_40e50860 → FUN_40e50730)

U-Boot's TX dispatcher builds a **16-byte desc** in the UP ring (`iVar6 + iVar4*0x10`,
ring base at struct+0x58, head at struct+0x54 wrapping at 0x400=1024):
```
desc[0x0] = 0x80          # NOT 0xc9 (mainline uses 0xc9 — this is the key difference)
desc[0x4] = 0x00010000    # (desc[6]=1)
desc[0x8] = 0x01000000    # (desc[11]=1) — VALID, but bit5(0x20) NOT set here; FUN_40e50730 sets it
desc[0xc] = 2             # <<< queue/dir = 2 (mainline puts a port-hint here instead)
then FUN_40e50730(buf, len):
  bp = FUN_40e4ff88()                       # BMU alloc bp index (<0x800)
  copy frame to 0x41000010 + bp*0x800       # BP buffer (frame at +0x10 offset)
  desc[7] = (desc[7]&1) | ((bp&0x7f)<<1)    # bp low 7 bits
  desc[8] = (bp>>7) & 0xff                   # bp high bits
  desc[0xc] = (desc[0xc]&3) | ((len&0x3fff)<<2)        # len in high bits, keeps dir=2 in low 2
  desc[8..11] = (desc[8..11]&0xff8001ff) | ((len&0x3fff)<<9)   # len mirror
  desc[0xb] = (desc[0xb]&1) | 0x20          # VALID bit (0x20) set last
  FUN_40e215f0(buf, buf+len)                # cache flush
  FUN_40e502f0(desc)                        # KICK (helper not in decomp dump; UP-ring kick)
```
**No 0xc9 marker. No post-kick desc clear. desc[0]=0x80, desc[0xc] low2 = dir/queue = 2.**
This is the minimal difference vs mainline's `zx_sw_xmit` (which sets desc[0]=0xc9 and
encodes a port-hint in desc[2..3]/desc[12..13]). The kick helper FUN_40e502f0 was not
extracted; the UP-ring kick is TM[0x10054]=1 per the architecture doc — keep that.

---

## 3. MINIMAL direct-mux egress recipe (one CPU frame out MAC2/LAN3)

Prereqs already in mainline: BMU pools, SCH shaper (the DSCH fix), per-MAC smac_init,
PP_BRG init (FUN_40e50a9c values).

NEW writes mainline is missing, in order:
1. **PP master enable**: `writel(2, e->fpga_base + 0x380000)` ; `usleep_range(1000,2000)`.
2. **ETH_TM2 mux clock/enable** (0x9238c000): `+0x80=0x309a`, `+0x88=0`, `+0xcc=1`.
3. **ETH_TM2 reset/clear**: `writel(0, ETH_TM2+0x10)`, `writel(0, ETH_TM2+0x14)`.
4. **MAC slot table**: program slot 0 with device MAC → `ETH_TM2+0x78`/`+0x7c` (encoding §1b).
5. **QMG[0]=0x11**: `writel(0x11, e->base + 0xc000)`.
6. **DIRECT MUX ENABLE**: `writel(0x11, ETH_TM2 + 0xe0)`.  ← the egress switch
7. TX desc per §2: desc[0]=0x80 (not 0xc9), desc[0xc] low2=2, len/bp encoded, VALID=0x20 last,
   kick TM[0x10054]=1, **no post-kick clear**.

---

## 4. Mainline implementation plan (zx-eth-main.c)

Add `#define ETH_TM2_OFF 0x1e0000` (relative to e->base) and helpers
`tm2_write(e,off,v)=writel(v, e->base+ETH_TM2_OFF+off)`.

(a) **New `zx_eth_tm2_init(e)`** — call from probe AFTER `zx_pp_brg_init` / `zx_npp_init`
    and BEFORE netdevs come up (insert near line 4337 where `zx_pp_brg_init` is, or just
    after it). Body = recipe steps 1–6:
    - `writel(2, e->fpga_base + 0x380000); usleep_range(1000,2000);`  (PP master — guard: only
      if not already done by an earlier PP init to avoid double-reset of PP_BRG).
    - 0x9238c000 block: `writel(0x309a, e->fpga_base+0x38c080); writel(0, +0x38c088); writel(1, +0x38c0cc);`
    - `tm2_write(e,0x10,0); tm2_write(e,0x14,0);`
    - slot 0 MAC: from `ndev->dev_addr` / `e->mac_addr`, encode and write `tm2 0x78`/`0x7c`.
    - `writel(0x11, e->base + 0xc000);`  (QMG[0])
    - `tm2_write(e, 0xe0, 0x11);`  (THE MUX)

(b) **New `zx_tm2_set_slot(e, slot, mac6)`** mirroring FUN_40e4fd24:
    ```
    lo = mac[3]<<16 | mac[2]<<24 | mac[5] | mac[4]<<8;
    hi = mac[0]<<8 | mac[1];
    tm2_write(e, 0x78 + slot*8, lo);
    tm2_write(e, 0x7c + slot*8, hi);
    ```

(c) **TX desc change in `zx_sw_xmit`** — add a build-time/module-param switch
    `zx_direct_egress` (default off until validated). When set, replace the desc build
    (lines ~3299–3328) with the U-Boot format:
    - `desc[0] = 0x80;` (was 0xc9)
    - drop the desc[2..3] port-hint (leave 0)
    - `*(u32*)(desc+4) = cpu_to_le32(0x00010000);`
    - `desc[7] = (bp & 0x7f) << 1;`
    - `desc[8] = (bp >> 7) & 0xff;`  → encode in the desc[8..11] word as today, but
      set the VALID/format byte: `desc[11] = (desc[11]&1) | 0x20;`
    - `*(__le16*)(desc+12) = cpu_to_le16(((len & 0x3fff) << 2) | 0x2);`  (dir/queue=2 in low2)
    - keep `tm_write(e, 0x10054, 1);`, **remove the dual DN kick** and keep no post-kick clear.
    - BP buffer: U-Boot copies frame at bp_buf+0x10 — mainline already does +16. Good.

(d) Leave the fabric path (`zx_pp_brg_init` FDB/isolation/flood) intact; the direct
    mux egress does not need the FDB DA-lookup, but the bring-up writes don't conflict.

---

## 5. Poke-testable validation BEFORE committing (use debugfs `poke <phys> <val>`)

Validate the clock/enable hypothesis live, on the current (DSCH-fixed) build, then
fire txtest and watch SMAC2 TX (0x92280718):

1. Confirm ETH_TM2 is dead: `regdump`/`mem 0x923a00e0` → expect 0 (not clocked).
2. Clock it: `poke 0x92380000 2` ; `poke 0x9238c080 0x309a` ; `poke 0x9238c0cc 1`.
3. Re-read `mem 0x923a00e0` → should now be writable/non-zero behavior.
4. `poke 0x923a0010 0` ; `poke 0x923a0014 0`.
5. Program slot 0 with the device MAC: `poke 0x923a0078 <lo>` ; `poke 0x923a007c <hi>`.
6. `poke 0x921cc000 0x11` (QMG[0]).
7. `poke 0x923a00e0 0x11` (THE MUX).
8. `txtest 4` and read deltas on SMAC2 TX `0x92280718` and SOPC/DSCH counters; tcpdump host.
   - If SMAC2 TX increments and frames appear on the wire → direct mux works; the desc
     format change is then the only remaining source edit.
   - If step 1 already shows non-zero at 0x923a00e0, ETH_TM2 is clocked and the gate is
     elsewhere (slot table / QMG mode) — re-check §1b encoding and slot selection.

**#1 thing mainline is missing: the ETH_TM2 block is never clocked/enabled.**
U-Boot powers it via `*0x92380000=2` (PP master) + `0x9238c000` writes
(`+0x80=0x309a`, `+0xcc=1`); only then does `*0x923a00e0=0x11` (the direct mux) take.
Mainline never maps/touches 0x9238c000 nor writes 0x923a00e0, so ETH_TM2 reads 0 and
no fabric/SOPC egress can substitute for it on this chip.
