# FDB Learn-Commit — live verification + stock-vs-mainline register gap

**Date:** 2026-05-28. **Device:** booted, probed live over REPL `localhost:9999`.
**Question driving this pass:** did the host MAC actually get LEARNED into the
HW FDB, or is auto-learn silently failing (the leading hypothesis)?

**Verdict (one line):** Learning is **NOT** the problem — the host MAC IS in
FDB-A on the correct egress port. The wedge is that mainline's `zx_pp_brg_init`
programs the FDB aging/lookup control registers wrong, so the *learned* entry
is never used by the DA-forwarding lookup. **Hypothesis REFUTED.**

---

## 1. LIVE FDB readback (the empirical core)

### Read method caveat (important for anyone re-running)
`tail -c +N /sys/kernel/debug/zx_eth/mem` does **not** seek reliably on this
debugfs file — single-offset reads drift and intermittently return zero-fill.
**Do not trust a single small read.** The robust method that works: stream a
large window (`tail -c +<0x1c8001>` = PP[0x8000]) for ~4 s, capture ~30–60 KB,
and **scan the whole buffer for the MAC signature**. Across repeated streams
the host-MAC entry is consistently found.

### FDB-A (PP_BRG_RAM directly-readable shadow @ PP[0x80a8])
Found reliably (multiple streamed reads):

```
w0 (PP[0x80a8]) = 0x62e95900     mac bytes 5..2
w1 (PP[0x80ac]) = 0x0000c8a3     mac bytes 1..0
w2 (PP[0x80b0]) = 0x00000108     status(valid bit8) + port bitmap low byte = 0x08
```

* MAC = **c8:a3:62:e9:59:00** = the HOST MAC. **LEARNED. ✓**
* Port bitmap = 0x08 = **bit 3 = internal port 3**. Via the driver's
  `port_remap[8] = {1,2,3,4,5,0,6,7}` (zx-eth-main.c:2110), internal port 3 =
  **logical port 2 = host's PHY[2]** (the LAN jack with `link=1` in stats).
  **Learned on the CORRECT egress port. ✓**
* Stock-live shadow had `0x102` (port bit 1) only because the stock dump was
  captured with the host on a different LAN jack; the encoding matches.

### FDB-B (sbrag mirror @ PP[0x88e1c])
All zeros. Mainline never populates FDB-B; per `fdb_learning_enable_re.md` Q4 +
`cpu_egress_routing_re.md`, FDB-B is the optional sbrag-indirect mirror and is
NOT required for auto-learn / DA-forwarding. **Not the wedge.**

### Live counters (cat /sys/kernel/debug/zx_eth/stats)
```
tm_rx_count = 6   tm_tx_count = 23   tm_rx_loopback_drops = 15
TX kick on TM[0x10054]=1 (UP ring)   BMU recycle OK   PHY[2] link=1
```
The BP buffer dump even shows the captured ARP frame (host MAC + device MAC
f4:f6:47:0f:42:64). TX is generated and consumed; frames hairpin to CPU
(loopback drops = CPU's own SMAC coming back) instead of egressing to port 3.

**Conclusion:** the entry exists, is valid, sits on the right port — yet the
egress DA-lookup does not forward to it. So the defect is in the FDB
**aging/lookup control config**, not in learn-commit.

---

## 2. Stock vs mainline — the exact register gap

Stock's real bridge init is `tm_pon_pp_brg_initial` (`decomp_all_tm.c:43579`),
NOT just the 13-write block mainline copied. It additionally calls (decomp
line / sbragRegTable regId / resolved PP location all cited):

| Stock call (tm.c line) | regId | PP byte . bit | Effect |
|---|---|---|---|
| `sbrg_set_macaddr_age_en(1)` (43606) | 4 | **0x8004 bit17** | enable MAC aging/refresh FSM |
| `sbrg_set_hash_collision_pktdeal(1)` (43608) | 6 | **0x8004 bit26** | hash-collision handling |
| `tm_mac_ramaddr_sel_set(1)` (43607) → `sbrg_set_table_sel(1)` (tm.c:7102, regId 0x1d) | 29 | **0x8184 [1:0]=1** | FDB RAM size = 512 buckets |
| ` ` → `sbrg_set_srcaddr_aging_cycle(..)` (tm.c:6185, regId 0x1e) | 30 | **0x8188** | aging cycle (scaled by table_sel) |
| `sbrg_set_macaddr_exchange_md(1)` (43610) | 0x17=23 | 0x8180 bit0 | SA/DA exchange mode |
| `sbrg_set_multicst_md(1)` (43609) | 0x18=24 | 0x8180 bit1 | multicast mode |
| `sbrg_set_multi_vlan_mode(1)` (regId 0x19, tm.c:9181) | 25 | 0x8180 bit2 | multi-vlan mode |

regId→PP mapping from mainline `zx_sbragregtable` (zx-fpga-reg-tables.h:421+):
`PP_byte = (base_off & 0xffff) * 4`. regId4 base_off 0x2001→0x8004 bit17;
regId6 0x2001 bit26; regId29 0x2061→0x8184 [1:0]; regId30 0x2062→0x8188.

### Authoritative stock-LIVE snapshot (`regs/stock_eth_2mib.txt`)
```
92388004 040200ff      <- bit17 (age_en) + bit26 (hash_collision) SET, bit25 CLEAR
92388180 00000004      <- multi_vlan_mode (bit2) set
92388184 00000001      <- table_sel = 1 (512 buckets)
92388188 00211b00      <- aging cycle
923881c0 000000ff  ok
923881c4 00005555  ok
923882c0 000000ff  ok
92388340 015555ff  ok (already fixed)
```

### What mainline `zx_pp_brg_init` actually programs
```
zx-eth-main.c:2361  writel(0x020000ff, pp + 0x8004);   // bit25 set; bit17 + bit26 MISSING
zx-eth-main.c:2384  writel(0x0013f434, pp + 0x8188);   // WRONG aging-cycle value
                    (never writes pp + 0x8184)          // table_sel left = 0  (128 buckets)
                    (never writes pp + 0x8180)          // exchange/mcast/multi-vlan left = 0
```

**Bit-level diff at PP[0x8004]:** stock `0x040200ff`, mainline `0x020000ff`.
Mainline is **missing bit 17 (macaddr_age_en)** and **bit 26
(hash_collision_pktdeal)**, and erroneously sets **bit 25** (part of regId-5's
[25:18] field which stock leaves 0).

---

## 3. Root cause

`macaddr_age_en` (PP[0x8004] bit 17) gates the FDB aging/refresh state machine.
Mainline leaves it **clear** while programming a nonzero aging cycle
(PP[0x8188]) and a learn pipeline that *does* commit entries to RAM (proven:
the host MAC is in the shadow). With the aging FSM disabled, learned entries
are written but are not marked "live" for the DA-forwarding lookup, so the
egress classifier treats DA = host MAC as a **miss** → unknown-unicast →
PP[0x8340] forwards CPU-only → the CPU sees its own ARP reply as loopback
(the +15 loopback drops). The frame never egresses to internal port 3.

Secondary, lower-confidence contributors that compound the lookup miss:
`table_sel`=0 vs stock 1 (different bucket count between mainline's view and
the stock-tuned aging-cycle constant), wrong PP[0x8188] aging value, and the
unset PP[0x8180] mode bits.

---

## 4. CONCRETE FIX

**File:** `linux-v6.6/drivers/net/ethernet/zte/zx-eth-main.c`,
function `zx_pp_brg_init`.

Primary (matches stock-live exactly — replace the hardcoded literals and add
the two missing writes):

```c
// line 2361  — was: writel(0x020000ff, pp + 0x8004);
writel(0x040200ff, pp + 0x8004);   // +bit17 macaddr_age_en, +bit26 hash_collision_pktdeal, -bit25

// line 2384  — was: writel(0x0013f434, pp + 0x8188);
writel(0x00211b00, pp + 0x8188);   // stock-live aging cycle

// ADD (mainline currently writes neither) — place alongside the other 0x81xx writes:
writel(0x00000001, pp + 0x8184);   // sbrg_set_table_sel(1): FDB = 512 buckets
writel(0x00000004, pp + 0x8180);   // multi_vlan_mode (stock-live PP[0x8180]=0x4)
```

The single highest-leverage change is **PP[0x8004] = 0x040200ff** (enables
aging FSM). Land that first; the other three are stock-matching hardening that
remove the remaining lookup-vs-learn config divergence.

After this, the already-learned host-MAC entry should be honored by the egress
DA-lookup and the ARP reply should forward to internal port 3 (host PHY[2])
instead of hairpinning to the CPU. Expect `tm_rx_loopback_drops` → 0 and wire
egress of the device MAC f4:f6:47:0f:42:64.

---

## 5. Confidence
* **HIGH** host MAC is learned on the correct port — direct live FDB-A
  readback, reproduced across multiple streamed reads (status 0x108, pbm bit3).
* **HIGH** mainline omits age_en / table_sel / 0x8180 and uses wrong 0x8004 /
  0x8188 — static diff of `zx_pp_brg_init` literals vs stock-live snapshot vs
  `tm_pon_pp_brg_initial` decomp, with regId→PP mappings cited.
* **MEDIUM-HIGH** that age_en (bit 17) is THE gate that makes the learned entry
  forwardable — the entry is provably in RAM yet ignored at egress; age_en is
  the one stock-enabled control whose semantics (validate/refresh entries)
  directly explain "learned-but-not-forwarded". Empirical confirmation requires
  applying the fix and re-pinging (read-only this pass).
