# WiFi Stage-3 Phase B — the IDM ring dispatcher: implementation spec (2026-07-07)

Device-free RE. Phase A (ssid encoding, `gemport_uni_id = 0x10|(idm_ring<<3)|ssid`) is
SOLVED — see `wifi_stage3_stock_ssid_correlation_2026-07-07.md`. This document specs
**Phase B**: the CPU-side glue that shuttles packets between MT7915/mac80211 WiFi vifs
and the IDM DMA ring, so the switch fabric sees WiFi traffic at all (today `idm_rx_count`
stays 0 forever — mainline drives the ring's registers but nothing feeds it).

Sources newly read for this pass (all device-free, no device touched):
- `ghidra/output_ko/idmfdb.ko/{register_idm_fdb_node,get_node_index,idm_fdb_forward,
  idm_fdb_recv_handle,idm_fdb_idm_isolate_handle,idm_fdb_init,print_idm_map,
  WlanIndex2WlanIdmMap,IfName2WlanIdmMap}.c` — per-function Ghidra decomps, cleaner
  than the concatenated `decomp_all_idmfdb.c` for exact byte offsets.
- `ghidra/output_ko/mt7915.ko/{register_idm_fdb_node,idm_fdb_recv_handle,
  idm_fdb_hook_xmit,mbss_create_vif}.c` — the **caller side**, not previously read.
  `register_idm_fdb_node`/`idm_fdb_recv_handle`/`idm_fdb_hook_xmit` are 1-byte stub
  externs here (imported from idmfdb.ko) — confirms mt7915.ko *calls* idmfdb.ko, not
  the reverse. `mbss_create_vif` (real code, not a stub) is the actual call site.
- `refs/orca-h3600p/ghidra/output_ko/idmfdb.ko/register_idm_fdb_node_bydev.c` — a
  second, devname-keyed registration entry point present in this build variant only.
- `tasks/00.10.01.re-vmlinux/vmlinux.dis` around `c02ca5a0`–`c02ca830` — **full ARM
  disassembly of `WlanIndex2WlanIdmMap`/`IfName2WlanIdmMap` and four sibling lookup
  functions**. This resolves Q4: these are **vmlinux builtins** (`EXPORT_SYMBOL`,
  confirmed in `tasks/00.10.01.re-vmlinux/{nm,symbols}.txt`), not a separate loadable
  module — which is *why* no `.ko` decomp ever contained them.
- `linux-v6.6/drivers/net/ethernet/zte/zx-eth-main.c` — mainline gap points, read in
  full for the relevant ranges (IDM regs :107-124, struct :310-510, `zx_idm_init*`
  :1485-1572, `zx_idm_poll` :1621-1707, `zx_idm_xmit` :1733-1785, netdev ops :1846-1853,
  `zx_eth_probe_port` :6874-6914, `zx_fdb_add` :668-722).

Confidence key: **✅ CONFIRMED** = exact source citation; **🟡 DERIVED** = follows
necessarily from confirmed facts, no single line states it; **❓ OPEN** = flagged, not
guessed.

---

## Verification pass (Fable 5, 2026-07-23)

Independent device-free re-verification of every load-bearing claim against the decomps,
the stock binaries themselves, vmlinux.dis, and mainline source. Verdict: **the spec's
core contracts are correct**; several supporting details were wrong and are fixed inline
below. Summary:

**Confirmed (re-derived from primary sources, not taken on faith):**
- `node_index = ssid + idm_ring*8`, now from THREE independent sites (`get_node_index.c:16`,
  `idm_fdb_forward.c:25`, `idm_fdb_multi_send_handle.c:219`), plus the orca
  `register_idm_fdb_node_bydev.c:32`.
- `fdb_list` node layout `+0x00 enabled / +0x01 idm / +0x03 ssid / +0x04 type /
  +0x08 forbidIdm / +0x10 idm_dev / +0x14 wlan_dev`, stride 0x128 — all cites re-checked.
- **Q5 upgraded 🟡→✅**: the idm/ssid bytes really are compile-time constants — verified
  by hexdump of the real `ext/rootfs/kmodule/idmfdb.ko` binary (`.data..read_mostly`
  section, symbol `fdb_list` size 4736 = 16×0x128, file offset 0x3440): node k has
  byte`+1` = k>>3 and byte`+3` = k&7 exactly (§1.4). A full sweep of every fdb_list-touching
  function (incl. the LED/flood functions the original pass missed) found no runtime write.
- **Q4 confirmed**: `WlanIndex2WlanIdmMap` @ c02ca5a0 + 5 siblings all linear-scan the
  same 16×0x29 vmlinux table @ 0xc0691650 — and the table has a *name*: **`wlan_to_idm_map`**
  (`nm.txt:42288`, EXPORT_SYMBOL'd, `__ksymtab_wlan_to_idm_map` @ c05ed630). Key offsets
  +0x21/+0x22/+0x23/+0x24/+0x25/+0x26/+0x28 all re-verified instruction-by-instruction.
- The TX contract (`skb->cb[0xb7]` stamp, dispatch via `idm_dev->ndo_start_xmit`) and the
  stock TX descriptor packing `len | ring<<31 | cb[0xb7]<<28` **unmasked** (the clamp
  warning is real) — verified directly in `decomp_all_plat_zxylzb_9128S.c:4268-4270`,
  not just via the encoding spec. RX side (`desc byte6 bit3=valid/bits0-2=ssid → cb[0xb7]`,
  invalid→`0xff` sentinel) verified at `plat:4125-4131`.
- All `zx-eth-main.c` line cites (RX decode :1645-1663, xmit :1733-1785, RX_ENABLE
  0x4000800 :1564, netdev_ops, probe_port, fdb_add) re-read and correct.
- mt7915.ko stub-vs-real claims (1-byte `halt_baddata` externs; `mbss_create_vif` the real
  caller, `local_8d` = bss index `param_3` +5 remap) verified.

**Corrected in this pass (details at the marked spots):**
1. **§3 RX-dispatch code had a real bug**: it called `eth_type_trans()` (which *pulls the
   14-byte Ethernet header*) before `ndo_start_xmit` — mac80211 would have transmitted
   headerless frames. Stock does NOT do this on the dispatch path. Fixed; insertion point
   in `zx_idm_poll` moved to before the existing `eth_type_trans` call.
2. §1.3 counter offsets were wrong: RX-dispatch success counters are `+0x18..0x27`
   (not "+0x20..0x2f"), failures `+0xc0..0xcf` (not "+0xc8..0xd7"); TX-inject counters
   `+0xa8..0xb7`. Also found an undocumented `+0x02` static byte (copy of idm, never read).
3. `idm_fdb_recv_handle` does **not** IFF_UP-check the idm dev — it's a plain non-NULL
   check (`:28`); §1.3/§2.3's "IFF_UP gate" language fixed. (IFF_UP is only checked by
   `idm_fdb_forward` on `wlan_dev`, and by the isolate/LED helpers.)
4. §1.5 vmlinux-struct table: the ifname string lives at **+0x01..0x20**, with **+0x00 a
   dedicated in-use flag byte** — proven three ways (IfName2WlanIdmMap literal pool =
   table+1 with flag read at `[r4,#-1]`; switch.ko's `R_ARM_ABS32 wlan_to_idm_map`
   reloc addend = **+1**; `sw_init_wlan_ssid` passes row+1 as the *name* into
   `aclWLANToIDMEssidCfg2`). Also found a new field: **+0x27 = the composed essid
   `0x10|(idm<<3)|ssid`** — `aclEssidToWlanIDMMap2` validates it as 0x10..0x1f, an
   independent re-confirmation of Phase A's encoding.
5. §6 Q1 had the data flow backwards: `sw_init_wlan_ssid` **reads** `wlan_to_idm_map`
   (and programs the TM ACL essid map from it) — it cannot be the populator. No kmod
   writes the table (full reloc scan of every stock .ko: only switch.ko references it,
   read-only). Its address appears in vmlinux's `systools_proc_opts` blob → populated
   from userland via the systools config machinery (🟡, exact command untraced; still
   irrelevant to mainline).
6. §6 Q2 narrowed: `ffe_get_npu_enable` @ c0458714 disassembled — a 7-instruction getter
   returning `*(*(ptr@0xc07f7630)+8)+0x34` (global FFE/NPU state flag), 0 if the inner
   pointer is NULL. It IS a global master switch; who sets it remains untraced.
7. Mainline already defines `IDM_DESC_CSUM_SHIFT 28` (`zx-eth-main.c:305`) — **unused**
   anywhere, and almost certainly a misnamed early transcription of the very bits stock
   uses for ssid. Checklist step 1 now says rename/replace it, not add a colliding define.
8. §2.3's "without breaking the SW baseline" claim was too rosy: `netdev_rx_handler_register`
   on a vif **conflicts with br0 membership** (the bridge owns the rx_handler slot). While
   bound, the vif cannot be bridged; reversibility = unregister-and-rebridge. Hardened.
9. Minor: `mbss_create_vif` cite :164-171 → :164-167; `idm_netdev_event` matches *wlan
   ifnames* (via `IfName2WlanIdmMap(dev->name)`, idm==0 rows) on UP/DOWN, not "idm0/1".

**Still open** (unchanged verdicts): §6.1 exact systools populate command (irrelevant for
mainline), §6.2 who sets the NPU flag (irrelevant), §6.3 (idm,ssid) config policy (design
decision), §6.4 raw-xmit vs dev_queue_xmit (design decision), §6.5 step-4.5 bridging
topology (first thing to test live).

The implementation checklist (§5) is, after these fixes, considered trustworthy for a
Phase-B coding agent.

---

## 0. The contract in one picture

```
   over the air                                          switch fabric
        │                                                       │
        ▼                                                       ▼
  mt76/mac80211 vif netdev (wlan1, wlan5g0, ...)          idm0 / idm1 netdev
        │  RX (frame arrives from a STA)                        ▲  RX (poll)
        │                                                        │
        └──── idm_fdb_recv_handle(node, skb) ───────────────────┘
              skb->cb[0xb7] = node->ssid  (stock byte offset)
              node->idm_dev->netdev_ops->ndo_start_xmit(skb)   (= zx_idm_xmit)

        ▲  TX (frame needs to reach a STA)                       │
        │                                                        │  RX (poll)
        └──── idm_fdb_forward(idm_ring, skb) ◄────────────────────┘
              ssid = skb->cb[0xb7]  (decoded by IDM RX desc read)
              node_index = ssid + idm_ring*8  →  fdb_list[node_index]
              node->wlan_dev->netdev_ops->ndo_start_xmit(skb)
```

Both directions are **CPU-mediated shuttles**, not zero-copy HW paths — same as the
project's existing conclusion for the eth side (no WED). `zx_idm_poll`/`zx_idm_xmit`
already exist and are correct for the *ring* mechanics; Phase B only adds the *dispatch*
at both ends.

---

## 1. RX path (IDM ring → mac80211 vif)

### 1.1 Descriptor decode — already done, additively, in `zx_idm_poll`

`zx-eth-main.c:1645-1663`:
```c
u32 word1 = le32_to_cpu(d[1]);
u16 len = word1 & 0x3FFF;
u8 port = (word1 >> 31) & 1;                 /* = idm ring (0/1) */
u8 ssid = (word1 >> 16) & 0x7;
bool ssid_valid = (word1 >> 19) & 1;
```
This matches stock bit-for-bit (`wifi_stage3_ssid_encoding_spec_2026-07-07.md` §1).
`port` local variable here IS the idm-ring index (0 or 1) — same value stock's
`idm_fdb_forward(uint idm, ...)` takes as `param_1`. **`ssid_valid==0` must map to the
sentinel used by the RX decoder, not `ssid=0`** — stock uses `0xff` in `skb->cb[0xb7]`
(ssid_encoding_spec §1); a mainline dispatch table needs the equivalent "no valid ssid →
flood/no-ssid" branch, not a false hit on node 0.

### 1.2 Node-index formula — ✅ CONFIRMED

`get_node_index` (`ghidra/output_ko/idmfdb.ko/get_node_index.c:6-19`):
```c
int get_node_index(void)
{
  iVar1 = WlanIndex2WlanIdmMap();      /* arg is wlan_index, passed in r0 (ARM ABI;
                                           decompiler drops the implicit-carry arg) */
  if (iVar1 == 0) return 0xff;
  return (uint)*(byte*)(iVar1+0x26) + (uint)*(byte*)(iVar1+0x25)*8;   /* ssid + idm*8 */
}
```
and independently in `idm_fdb_forward` (`ghidra/output_ko/idmfdb.ko/idm_fdb_forward.c:24-26`),
operating on the **already-decoded RX values** (not the map struct):
```c
if (uVar2 < 8) {                       /* uVar2 = ssid, from skb->cb[0xb7] */
    iVar4 = uVar2 + param_1 * 8;       /* param_1 = idm ring. node_index = ssid + idm*8 */
```
**`node_index = ssid + idm_ring*8`**, range 0-15 (2 rings × 8 SSIDs). This is the same
formula the ssid-encoding spec already stated; now confirmed from two independent call
sites in the same `.ko`, not just one.

### 1.3 The `(idm,ssid)→vif` table structure — ✅ CONFIRMED, exact byte offsets

Stock's `fdb_list` is a flat array of 16 fixed-size (0x128 = 296-byte) node structs.
Offsets below are triple-cross-checked from **`print_idm_map`** (the debug dumper — the
single cleanest source, since it labels every field it prints),
**`register_idm_fdb_node`** (the writer), **`idm_fdb_forward`** (the RX-dispatch reader),
**`idm_fdb_recv_handle`** (the TX-injection reader), and **`idm_fdb_idm_isolate_handle`**
(a fourth independent reader):

| offset | size | field | confirmed by |
|---|---|---|---|
| `+0x00` | 1 B | `enabled` (bit0) | write: `register_idm_fdb_node.c:32` (`=1`); read: `idm_fdb_forward.c:32`, `print_idm_map.c:33`, `idm_fdb_idm_isolate_handle.c:22` |
| `+0x01` | 1 B | `idm` (ring 0/1) | read-only, see §1.4 below; printed `print_idm_map.c:43` (`"idm:%d"`), used for the `"idm%d"` devname lookup in `register_idm_fdb_node.c:33` |
| `+0x02` | 1 B | static copy of `idm` (verification pass: present in the `.data` initializer — see §1.4 — but no code in idmfdb.ko ever reads it) | idmfdb.ko binary `.data..read_mostly` dump |
| `+0x03` | 1 B | `ssid` (0-7) | read-only, see §1.4; printed `print_idm_map.c:43` (`"ssid:%d"`); **read to stamp `skb->cb[0xb7]`** in `idm_fdb_recv_handle.c:19` (`param_1[3]`) — this is the field the TX path (§2) consumes |
| `+0x04` | 1 B | `type` (0=AP-vif, 2=ApCli, per `WlanIfName2Index`/`ApcliCardIndex2WlanIdmMap` sibling functions) | write: `register_idm_fdb_node.c:39` (copied from map struct `+0x22`); read: `idm_fdb_idm_isolate_handle.c:24-25` (isolate-policy decision) |
| `+0x08` | 4 B (bit0) | `forbidIdm` flag | read+clear: `idm_fdb_idm_isolate_handle.c:23` (`&= 0xfffffffe`); read (must be 0) in `idm_fdb_recv_handle.c:28` |
| `+0x10` | 4 B | `idm_dev` (ptr to `idmN` netdev) | write: `register_idm_fdb_node.c:36` (`__dev_get_by_name("idm%d")` result); read: `idm_fdb_recv_handle.c:28` (**non-NULL check only — recv_handle does NOT IFF_UP-check the idm dev**), `:55` (TX dispatch target) |
| `+0x14` | 4 B | `wlan_dev` (ptr to the vif netdev) | write: `register_idm_fdb_node.c:35` (`= param_2`, the arg); read: `idm_fdb_forward.c:27,32-35,54` (non-NULL + `flags&IFF_UP` check on the *wlan* dev + RX dispatch target), `idm_fdb_recv_handle.c:29,32` |
| `+0x18..0x27` | 2×u64 | RX-dispatch success counters: pkt64 @`+0x18`, byte64 @`+0x20` (verification pass: `DAT_00013420`−`fdb_list`@0x13408 = **+0x18**, not +0x20 as originally stated) | `idm_fdb_forward.c:56-65` |
| `+0xa8..0xb7` | 2×u64 | TX-inject success counters: pkt64 @`+0xa8`, byte64 @`+0xb0` | `idm_fdb_recv_handle.c:20-26` |
| `+0xc0..0xcf` | 2×u64 | RX-dispatch failure counters: pkt64 @`+0xc0`, byte64 @`+0xc8` (originally misstated as "+0xc8..0xd7") | `idm_fdb_forward.c:68-77` (both the xmit-failed and the not-enabled `LAB_000101b0` paths) |
| `+0x28..0x9f`(≈) | — | further counter/LED-rate-shadow area (read+written by `idm_led_timer_handle.c:54-76`; not load-bearing, not fully mapped) | — |

Stride confirmed two ways: `iVar1 = node_index * 0x128` (byte-array indexing,
`register_idm_fdb_node.c:31`) **and** `(&DAT_0001341c)[node_index * 0x4a]` (u32-array
indexing at the same struct's `+0x14` field, `register_idm_fdb_node.c:35`) — `0x4a*4 =
0x128`, self-consistent.

**A mainline dispatch table is exactly this shape**: a flat `struct zx_wifi_dispatch_node
dispatch[16]` (or `[2][8]`), fields `{bool enabled; u8 idm; u8 ssid; struct net_device
*wlan_dev;}` — no need for the `type`/`forbidIdm`/counter fields unless the isolate
policy (§5) is also being ported.

### 1.4 ✅ Q5 ANSWERED — write-site of `fdb_list[node].idm`/`.ssid`

**There is no runtime write site.** Every function in idmfdb.ko that touches offsets
`+0x01` (`idm`) or `+0x03` (`ssid`) — `print_idm_map`, `idm_fdb_forward`,
`idm_fdb_recv_handle`, `idm_fdb_idm_isolate_handle`, `register_idm_fdb_node` itself —
**only reads them**. `register_idm_fdb_node` writes `+0x00`, `+0x04`, `+0x10`, `+0x14`
(confirmed above) but never `+0x01`/`+0x03`. This is not an oversight in the RE: it is
the necessary consequence of the node-index formula (§1.2) — **`idm = node_index >> 3`
and `ssid = node_index & 7` are fully determined by the node's position in the array**,
so `fdb_list[k].idm`/`.ssid` **must be compile-time constants baked into idmfdb.ko's
`.data` section** at module-build time (one static initializer row per of the 16 nodes:
`{idm:0,ssid:0}, {idm:0,ssid:1}, ..., {idm:1,ssid:7}`), never touched again at runtime.
✅ CONFIRMED (verification pass, 2026-07-23): **the static-initializer bytes were dumped
from the real binary.** `readelf -s ext/rootfs/kmodule/idmfdb.ko` → `fdb_list` is a
4736-byte (= exactly 16×0x128) OBJECT filling the whole `.data..read_mostly` section
(PROGBITS, file offset 0x3440). The dump shows, for every node k = 0..15: byte`+0x00`=0
(disabled), byte`+0x01` = k>>3 (idm), byte`+0x02` = k>>3 (undocumented duplicate, never
read by code), byte`+0x03` = k&7 (ssid), all other bytes 0. Additionally a *complete*
sweep of every fdb_list-touching function in the module (adding `idm_led_timer_handle`,
`idm_fdb_multi_send_handle`, `print_idm_led`, `print_idm_led_stat` to the five functions
originally checked) found no write to `+0x01`/`+0x02`/`+0x03` anywhere.
**For a mainline port this is actually simpler**:
just declare the dispatch table as `static const u8 node_idm[16] = {...}` /
`node_ssid[16] = {...}` (or compute `idm=i>>3, ssid=i&7` inline) — no init-time write
needed at all, exactly mirroring what stock does.

### 1.5 Registration — resolving Q4

`register_idm_fdb_node(int wlan_index, struct net_device *wlan_dev)`
(`ghidra/output_ko/idmfdb.ko/register_idm_fdb_node.c`, address `0x10674`):
```c
if (param_2 != 0 && (iVar2 = get_node_index(/*wlan_index=param_1, ABI-implicit*/), iVar2 < 0x10)) {
    iVar1 = iVar2 * 0x128;
    fdb_list[iVar1].enabled = 1;
    snprintf(name, "idm%d", fdb_list[iVar1].idm);        /* the static idm byte, §1.4 */
    idm_dev = __dev_get_by_name(&init_net, name);
    fdb_list[iVar2].wlan_dev = param_2;                   /* = wlan_dev, the netdev arg */
    fdb_list[iVar1].idm_dev  = idm_dev;
    map = WlanIndex2WlanIdmMap(param_1);                  /* re-fetch, for .type only */
    if (map) fdb_list[iVar1].type = map[0x22];
    create_idm_proc_file(&fdb_list[iVar1]);
    idm_fdb_idm_isolate_handle();
    return &fdb_list[iVar1];
}
return NULL;
```

**Caller (✅ CONFIRMED, real — not a stub):** `mbss_create_vif`
(`ghidra/output_ko/mt7915.ko/mbss_create_vif.c:164-167`), the MT7915 MBSSID-vif creation
routine (called once per configured SSID/BSS when the radio brings its BSS set up):
```c
if (4 < param_3) local_8d = local_8d + '\x05';   /* param_3 = bss index; +5 remap for
                                                     slots >4 (second radio/band per the
                                                     🟡 reading) — this IS the wlan_index */
uVar5 = register_idm_fdb_node(local_8d, iVar11);  /* iVar11 = the just-created vif netdev */
```
(Verification pass: `local_8d` provenance confirmed — initialized `= (char)param_3` at
`mbss_create_vif.c:33/69`, optionally re-assigned via the profile's own ifidx at `:104-105`
("re-assign ifidx %d -> %d") / `multi_profile_devname_req` at `:108` — so it is the
driver's bss/ifidx integer, exactly as stated.)
So **`wlan_index` is a small per-driver integer** (not the ssid/idm pair directly) —
one value per (radio, bss-slot) combination, assigned by the WLAN driver itself at vif
creation time, completely independent of the switch's `(idm,ssid)` numbering. The
*mapping* from that arbitrary integer to `(idm,ssid,type)` is exactly what
`WlanIndex2WlanIdmMap` provides (next paragraph) — i.e. **the wlan_index→(idm,ssid) glue
is a config table, not a formula**. ~~Presumably populated by `sw_init_wlan_ssid`~~ —
**corrected by the verification pass**: `sw_init_wlan_ssid` (`decomp_all_switch.c:5113-5143`)
*reads* this table (walking all 16 rows via the exported symbol; switch.ko's
`R_ARM_ABS32 wlan_to_idm_map` reloc, addend +1) and programs the TM ACL essid map from it
(`aclWLANToIDMEssidCfg2(row_idx, port6/7-from-idm@+0x25, essid@+0x27, name@+0x01)`), so it
is a *consumer*, not the populator. No stock kmod writes the table at all (full reloc scan:
only switch.ko references the symbol, read-only; mt7915.ko does not). The table's address
appears in vmlinux's `systools_proc_opts` blob → 🟡 populated from userland via the stock
systools config machinery at WLAN-config time (which also explains why it is already
populated *before* `mbss_create_vif` runs); exact command untraced, ❓ see §6.

**✅ Q4 ANSWERED — `WlanIndex2WlanIdmMap` internals.** It is a **vmlinux builtin**
(`EXPORT_SYMBOL`, `tasks/00.10.01.re-vmlinux/nm.txt:42278 "c02ca5a0 T WlanIndex2WlanIdmMap"`),
not a separate `.ko` — this is *why* no decomp set on disk ever contained its body: it
was never compiled as a loadable module in the first place. The table itself is a named,
**itself-EXPORT_SYMBOL'd** vmlinux object: **`wlan_to_idm_map` @ 0xc0691650**
(`nm.txt:42288 "c0691650 t wlan_to_idm_map"`, `__ksymtab_wlan_to_idm_map` @ c05ed630 —
verification pass). Full disassembly at `vmlinux.dis:749085-749107`:

```
WlanIndex2WlanIdmMap(r0=wlan_index):
  table = 0xc0691650                    /* = wlan_to_idm_map, vmlinux .data */
  for (r3 = table; r3 != table+16*41; r3 += 41) {   /* 16 entries × 0x29(41) bytes */
      if (r3[0] == 0) continue;                       /* byte 0 = in-use flag (a dedicated
                                                          byte; the ifname lives at +0x01) */
      if (r3[0x21] == wlan_index) return r3;           /* match on the wlan_index byte */
  }
  return 0;   /* NULL = "not mapped" — the mainline zte_shim stub's behavior */
```

Five sibling lookup functions immediately following in vmlinux (`WlanCardOffset2WlanIdmMap`
`:749109`, `WlanProbeSeq2WlanIdmMap` `:749137`, `ApcliCardIndex2WlanIdmMap` `:749161`,
`IfName2WlanIdmMap` `:749189`, `WlanIfName2Index`/`ApCliIfName2Index` `:749216`/`:749240`)
all linear-scan the **same 16×41-byte table** at `0xc0691650`, keyed on different byte
offsets — this cross-confirms the struct layout (each accessor's key offset is a distinct
field of one shared struct):

| offset | field | evidence |
|---|---|---|
| `+0x00` | **in-use flag** (u8, dedicated byte — CORRECTED: originally misread as the name's first char) | `WlanIndex2WlanIdmMap` `ldrb [r3]`/skip-if-0 (`:749093-749094`); `IfName2WlanIdmMap` reads it as `ldrb r3,[r4,#-1]` with r4 = row+1 (`:749192`) |
| `+0x01..0x20` | `ifname` (C string, ≤32 B incl NUL) | `IfName2WlanIdmMap`'s literal pool holds **0xc0691651 = table+1** (`:749214`) and `strcmp(row+1, ifname)` (`:749196-749200`); independently: switch.ko's `R_ARM_ABS32 wlan_to_idm_map` reloc has in-place addend **+1**, and `sw_init_wlan_ssid` passes that row+1 pointer as the *name* argument to `aclWLANToIDMEssidCfg2` |
| `+0x21` | `wlan_index` (u8) | match key of `WlanIndex2WlanIdmMap` (`:749095`) |
| `+0x22` | `type` (u8: 0=AP, 2=ApCli) | filter in `ApcliCardIndex2WlanIdmMap` (`==2`, `:749176-749178`) and `WlanIfName2Index`/`ApCliIfName2Index` (`==0`/`==2` gate, `:749223-749225`,`:749247-749249`); consumed as `fdb_list[].type` by `register_idm_fdb_node` |
| `+0x23` | `card_index` (u8) | key in `ApcliCardIndex2WlanIdmMap` (`:749179-749181`) and (as an output) `WlanIfName2Index`/`ApCliIfName2Index` (`:749227-749228`,`:749251-749252`) |
| `+0x24` | 🟡 secondary index (unconfirmed exact semantic — 2nd key of `WlanCardOffset2WlanIdmMap`'s 2-key lookup, also an output of `WlanIfName2Index`/`ApCliIfName2Index`) | `:749127-749128`, `:749230-749233` |
| `+0x25` | **`idm`** (ring: 0=idm0/port6, 1=idm1/port7) | consumed by `get_node_index.c:16` and `get_sw_port_from_devname` (`decomp_all_switch.c:4551,4560`: `*(char*)(iVar2+0x25)=='\0'`/`=='\x01'` branches) |
| `+0x26` | **`ssid`** (0-7) | consumed by `get_node_index.c:16` and `get_sw_port_from_devname` (`decomp_all_switch.c:4556,4565`: `*(byte*)(iVar2+0x26)+0x10`/`+0x18`) |
| `+0x27` | **`essid`** = the composed `0x10\|(idm<<3)\|ssid` (0x10-0x1f) — NEW, found by the verification pass | `sw_init_wlan_ssid` reads it (row+1 pointer `+0x26` = abs `+0x27`) and passes it as `aclWLANToIDMEssidCfg2`'s essid arg (`decomp_all_switch.c:5131/5135`); `aclEssidToWlanIDMMap2` (`decomp_all_tm.c:50203`) validates the same value as `param_1 - 0x10 < 0x10` → range **0x10..0x1f**, i.e. exactly Phase A's `gemport_uni_id` encoding — an independent stock-side re-confirmation of the Phase-A formula |
| `+0x28` | `probe_seq` (u8) | key of `WlanProbeSeq2WlanIdmMap` (`:749147-749148`) |

**`IfName2WlanIdmMap(const char *ifname)`** (`vmlinux.dis:749189-749213`) is the same
linear scan keyed on the `ifname` string field via `strcmp` — this is what
`get_sw_port_from_devname` and the alternate `register_idm_fdb_node_bydev`
(`refs/orca-h3600p/.../register_idm_fdb_node_bydev.c:31`) use instead of the
index-keyed lookup, when only a devname (not a wlan_index) is available.

**Net effect for the mainline registration API (item 3 of the deliverable):** a mainline
equivalent does **not** need to replicate this exact 41-byte vmlinux struct or its fixed
address — that whole table only exists to translate an *arbitrary* stock-driver
`wlan_index`/`ifname` into `(idm,ssid,type)`. A mainline implementation controls both
ends of that mapping itself (there is no closed-source WLAN driver imposing an opaque
`wlan_index`), so **the natural mainline design is to skip the indirection and have the
registration call take `(idm_ring, ssid, struct net_device *vif)` directly** — see §3.

---

## 2. TX path (mac80211 vif → IDM ring)

### 2.1 Stamp + inject — ✅ CONFIRMED

`idm_fdb_recv_handle`/`wlan_recv_idm_handle` (byte-identical, per the ssid-encoding spec;
this pass read `idm_fdb_recv_handle.c` in full, `0x10000`, 400 bytes):
```c
undefined4 idm_fdb_recv_handle(char *node, int skb)     /* node = fdb_list[node_index] ptr */
{
  if (skb == 0 || node == NULL) return -1;
  if (!ffe_get_npu_enable()) return -1;                  /* vmlinux builtin gate, ❓ open, §6 */
  skb->cb[0xb7] = node->ssid;                             /* node[3] — THE stamp, line 19 */
  /* ... byte/packet counters on node (+0xa8.. +0xb4) omitted, not load-bearing ... */
  if (node->enabled && node->idm_dev != NULL && !node->forbidIdm) {
      skb->dev = node->wlan_dev;                          /* line 29, cosmetic only */
      return node->idm_dev->netdev_ops->ndo_start_xmit(skb /*, node->idm_dev, ARM-implicit*/);
  }
  return -1;
}
```
The dispatch target is **`node->idm_dev`** (offset `+0x10`), i.e. it calls straight into
`idm_net_tx` (stock) / **`zx_idm_xmit`** (mainline) — confirming the ssid-encoding spec's
§5 claim exactly, now with the concrete offset (`node[3]`) instead of "node->ssid" prose.

### 2.2 TX descriptor packing — already fully specified (ssid-encoding spec §1), unchanged here

`zx_idm_xmit` (`zx-eth-main.c:1733-1785`) currently builds word1 with **no ssid bits**:
```c
tx_desc[idx*2+1] = cpu_to_le32((len & IDM_DESC_LEN_MASK) |
                                (port->idx ? IDM_DESC_PORT_BIT : 0));
```
Needs an added `| (ssid_clamped << IDM_DESC_SSID_SHIFT)` where `IDM_DESC_SSID_SHIFT` = 28
(bits 28-30) — verified by the verification pass **directly against stock's `idm_net_tx`**
(`decomp_all_plat_zxylzb_9128S.c:4268-4270`: `desc[1] = len | ring<<0x1f | cb[0xb7]<<0x1c`),
not only via the encoding spec. **⚠ must clamp ssid to 0-7 before the shift**; stock's own
contract does not mask `skb->cb[0xb7]` before `<<28`, so an invalid value (e.g. an echoed
RX sentinel `0xff`) corrupts bit31 (`IDM_DESC_PORT_BIT`, the ring select) as well. A
mainline implementation must NOT reproduce that bug.

**⚠ Naming collision (verification pass):** mainline already has `#define
IDM_DESC_CSUM_SHIFT 28` (`zx-eth-main.c:305`) — **unused anywhere in the driver** and
almost certainly a misnamed early transcription of these very ssid bits. **Rename/replace
it with `IDM_DESC_SSID_SHIFT`** rather than adding a second define for the same bit
positions (two names for one field is a future misprogramming hazard).

### 2.3 The exact mainline hook point — 🟡 DERIVED, a concrete recommendation

Stock's hook is inside the closed WLAN driver's own RX-completion path (mt7915.ko calls
`idm_fdb_hook_xmit`/`idm_fdb_recv_handle` explicitly — confirmed by the presence of both
as *imported* stub symbols in `mt7915.ko`'s own decomp, i.e. the vendor built the shim
call directly into their driver source). Mainline's MT7915 support is upstream mac76/
mac80211 — **we do not want to patch mac80211 or mt76 to add a vendor-specific hook.**
The idiomatic mainline mechanism for "intercept every RX frame on this netdev before the
normal stack sees it" is **`netdev_rx_handler_register()`** (used by bonding/team/bridge
lower devices for exactly this purpose — see `net/core/dev.c`
`__netif_receive_skb_core()`, which calls the registered `rx_handler` before bridging/L3).

**Recommended Phase-B TX hook:** for each WiFi vif netdev bound via the registration API
(§3), call `netdev_rx_handler_register(vif_ndev, zx_wifi_rx_handler, node)`. The handler:
```c
rx_handler_result_t zx_wifi_rx_handler(struct sk_buff **pskb)
{
    struct zx_wifi_dispatch_node *node = rx_handler_data;   /* from rx_handler_register */
    struct sk_buff *skb = *pskb;
    if (!node->idm_ndev || !(node->idm_ndev->flags & IFF_UP))
        return RX_HANDLER_PASS;           /* fall through to normal stack (SW baseline) */
    skb->dev = node->idm_ndev;
    zx_idm_xmit(skb, node->idm_ndev);      /* or dev_queue_xmit(skb) for qdisc-safety */
    return RX_HANDLER_CONSUMED;
}
```
This mirrors stock's gate (`idm_fdb_recv_handle.c:28`, `*(int*)(param_1+0x10)!=0` — note
that is a **non-NULL check on `node.idm_dev`, not an IFF_UP check**; the mainline handler
above deliberately adds the IFF_UP condition on top, which is strictly safer).

**⚠ Coexistence caveat (verification pass):** `netdev_rx_handler_register` on the vif
**conflicts with br0 membership of that same vif** — the bridge itself owns the one
rx_handler slot per netdev (this is exactly the `-EBUSY` case flagged in checklist step 2).
On the current rig the vif *is* a br0 member (the working SW baseline), so binding the
dispatch handler requires first removing the vif from br0. The "fall through on
RX_HANDLER_PASS" safety net therefore lands in the **local stack**, not the bridge; the
incremental/reversible posture holds in the weaker but still sufficient sense that
*unregistering the handler and re-adding the vif to br0* restores the exact SW baseline.
(The natural end-state topology — bridge `idmN` in place of the vif — is checklist
step 4.5's open question, §6.5.)

Context note from the stock RX side (verification pass): stock pre-marks every skb it
allocates for the IDM RX ring with `skb+0xbc |= 0x10` (`plat:4122`), and
`idm_fdb_hook_xmit` returns early on that flag (`idm_fdb_hook_xmit.c:12`) — a
"ring-originated frame" marker used to skip the FFE-learn hook. Not needed for the
minimal Phase-B dispatcher, but worth mirroring (an skb flag/cb marker) if step 4.5 ends
up bridging `idmN`, to make ring-origin frames distinguishable and loop-proof.
❓ Calling `zx_idm_xmit` directly (bypassing qdisc, like stock's raw `ndo_start_xmit`
call) vs `dev_queue_xmit()` (qdisc-safe, mainline-idiomatic) is a real design choice not
resolved here — recommend starting with the direct call (matches proven stock behavior,
simplest to validate) and only moving to `dev_queue_xmit()` if TX-side backpressure
(`NETDEV_TX_BUSY` from `zx_idm_xmit` when `IDM_TX_POOL_LIMIT` is hit) causes drops that
qdisc would otherwise queue.

---

## 3. Registration — what a mainline equivalent must set up

Given §1.5's conclusion (mainline owns both ends, no opaque `wlan_index` to translate),
**skip the `WlanIndex2WlanIdmMap` indirection** and register directly:

```c
/* Called once per WiFi vif netdev, at NETDEV_UP (or NETDEV_REGISTER) time — cf. the
 * notifier pattern idmfdb.ko itself uses (idm_netdev_event.c: matches *wlan ifnames*
 * via IfName2WlanIdmMap(dev->name) on UP/DOWN of idm==0 rows and re-runs the isolate
 * policy — corrected by the verification pass; it is not an idm0/1-side notifier). */
int zx_wifi_register_vif(struct net_device *vif_ndev, u8 idm_ring, u8 ssid)
{
    int node_index = ssid + idm_ring * 8;
    struct zx_wifi_dispatch_node *node;

    if (idm_ring > 1 || ssid > 7)
        return -EINVAL;
    node = &zx_wifi_dispatch[node_index];
    node->idm_ndev = zx_eth_global->ports[idm_ring].netdev;   /* the idmN netdev, already
                                                                  registered by zx_eth_probe_port */
    node->wlan_ndev = vif_ndev;
    node->enabled = true;
    return netdev_rx_handler_register(vif_ndev, zx_wifi_rx_handler, node);
}
```

`(idm_ring, ssid)` for a given vif must come from **configuration**, not from a
vendor-proprietary map — e.g. a devicetree property on the AP config, a debugfs/sysfs
knob set by the hostapd bring-up script (matching SSID index to radio/BSS index the way
`hostapd.conf`'s `bss=` ordering already implies), or a simple convention (radio0's N
BSSes → idm0/ssid 0..N-1, radio1's → idm1/ssid 0..N-1) mirroring the `mbss_create_vif`
`+5`-for-second-radio pattern (§1.5) closely enough to be predictable. **This is a policy
decision, not something the decomp can settle — flagged, not guessed.**

The `(idm,ssid) → vif` table itself (§1.3) is the RX-side structure; §3's registration
function is what *populates* it, replacing stock's `register_idm_fdb_node` +
`WlanIndex2WlanIdmMap` indirection with a direct, mainline-controlled binding.

**RX-side dispatch (§1), concretely, replacing the plain delivery in `zx_idm_poll`:**
```c
/* Insert AFTER skb_put(skb, len) (zx-eth-main.c:1682) but BEFORE the existing
 * "skb->protocol = eth_type_trans(skb, ndev)" line (zx-eth-main.c:1684).
 * ⚠ CORRECTED by the verification pass: the original spec called eth_type_trans()
 * before ndo_start_xmit — but eth_type_trans() PULLS the 14-byte Ethernet header
 * (skb_pull(ETH_HLEN)), so mac80211 would have transmitted a headerless frame.
 * Stock does NOT call eth_type_trans on the dispatch path: idm_fdb_forward only
 * sets skb->dev and calls ndo_start_xmit on the intact frame (idm_fdb_forward.c:35,54);
 * eth_type_trans appears only in plat's idm_skb_recv==NULL local-delivery fallback
 * (decomp_all_plat_zxylzb_9128S.c:4132-4136). */
if (ssid_valid && ssid < 8) {
    struct zx_wifi_dispatch_node *node = &zx_wifi_dispatch[ssid + port * 8];
    if (node->enabled && node->wlan_ndev && (node->wlan_ndev->flags & IFF_UP)) {
        skb->dev = node->wlan_ndev;
        node->wlan_ndev->netdev_ops->ndo_start_xmit(skb, node->wlan_ndev);
        goto refill;   /* skip eth_type_trans + napi_gro_receive below */
    }
}
/* fall through unchanged: eth_type_trans + napi_gro_receive
 * (broadcast/flood/unmapped/invalid ssid → local stack, as today) */
```
This mirrors `idm_fdb_forward`'s direct `ndo_start_xmit` call (§1.3, `idm_fdb_forward.c:54`)
— i.e. stock **also** bypasses the normal RX stack on this side, consistent with using
the same raw-dispatch idiom in both directions for symmetry (unlike §2.3's TX-side choice
of `netdev_rx_handler`, which has no RX-side analog since we're not intercepting the
*ring's* rx_handler — the ring already IS our own driver's netdev).

---

## 4. Enablement — does anything need to be turned on for the ring to receive?

**No additional register write is needed.** Two independent facts, both already
established by prior work in this project, confirm the ring's own hardware plumbing is
already fully live:

1. **IDM ring RX is already enabled** by mainline itself: `zx_idm_init`
   (`zx-eth-main.c:1564`) writes `npp_write(e, IDM_REG_RX_ENABLE, 0x4000800)` — this is
   the *exact* stock enable value (comment at :1563 "Final RX enable from stock"), and
   the ring is demonstrably capable of receiving (the ssid-decode counters at
   `zx-eth-main.c:1659-1663` exist and would increment on any RX descriptor completion;
   they read 0 today only because nothing arrives, not because the register is wrong).
2. **Fabric ports 6/7 are already un-isolated.** Per `wifi_stage3_PLAN_2026-07-07.md`
   §1 (commit `1478beecf`): `PP_BRG_ISOLATE` is an ALLOW-mask, and the live register
   dump showed ports 6/7 = `0xff` (fully open) — "no mask change needed" was the
   explicit finding of that pass.

**The reason `idm_rx_count` stays 0 is exactly the gap Phase B closes**: no software
(mainline has no WiFi-vif-to-IDM injector) and no hardware classification rule (CLA/FDB
never target port 6/7 for any traffic mainline currently generates) ever puts a frame
onto fabric port 6 or 7 in the first place. Once §2's TX-injection hook exists and a real
over-the-air frame is stamped+pushed via `zx_idm_xmit`, the ring's RX side of the *other*
end (whichever CPU is watching `idm0`/`idm1` — in this single-CPU design, the same host)
should see it arrive with no register changes required. **This is a testable, falsifiable
claim** — see the validation step in the checklist below.

---

## 5. Concrete, ordered mainline implementation checklist

For a future driver-coding agent. Each step is independently buildable/testable; do them
in order so a wrong step is caught before the next depends on it.

1. **Add the dispatch table + TX ssid clamp (no behavior change yet).**
   - Add `struct zx_wifi_dispatch_node { bool enabled; struct net_device *idm_ndev,
     *wlan_ndev; } zx_wifi_dispatch[16];` to `struct zx_eth` (near the existing
     `idm_rx_per_ssid[8]` fields, `zx-eth-main.c:416-418`).
   - **Rename the existing, unused `IDM_DESC_CSUM_SHIFT 28` (`zx-eth-main.c:305`) to
     `IDM_DESC_SSID_SHIFT`** (it is a misnamed early transcription of the same bits —
     verification pass, §2.2) and add `#define IDM_DESC_SSID_MASK 0x7` next to the
     `IDM_DESC_*` macros (`zx-eth-main.c:304-306`). Do NOT leave two defines for bit 28.
   - **Validate:** `make modules`; module still loads; `idm_rx_count` behavior
     unchanged (this step adds no new code path yet, pure scaffolding).

2. **Wire up `zx_wifi_register_vif()` (§3) and call it manually via a debugfs knob**
   (e.g. `debugfs_create_file("wifi_bind", ...)` taking `"<ifname> <idm> <ssid>"`) rather
   than a real netdev-notifier auto-bind at first — this decouples "does the dispatch
   table + rx_handler mechanism work" from "how do we discover the (idm,ssid) mapping"
   (§3's open policy question), letting you test with a manually-typed binding first.
   - **Validate:** `cat /sys/kernel/debug/zx_eth/wifi_bind` (or equivalent) shows the
     bound node; `netdev_rx_handler_register` returns 0 (not `-EBUSY` — a vif can only
     have one rx_handler; the **bridge** holds it while the vif is a br0 member, which
     it IS in the current SW-baseline rig config — `brctl delif br0 <vif>` first, and
     note this takes the vif out of the SW WAN⇄WiFi path until step 4.5 re-plumbs it;
     see §2.3's coexistence caveat).

3. **Implement `zx_wifi_rx_handler()` (§2.3) and the TX ssid-stamp+clamp in
   `zx_idm_xmit()` (§2.2).**
   - Modify `zx_idm_xmit` to accept/derive a per-skb ssid — simplest: stash it in
     `skb->cb[]` at a mainline-chosen offset (no existing convention; do NOT reuse
     stock's `0xb7` literally, mainline's `sk_buff::cb` layout is unrelated — pick any
     free offset via a new `#define ZX_SKB_CB_SSID_OFF` and confirm `sizeof(skb->cb) >
     offset` at compile time) set by `zx_wifi_rx_handler` before calling `zx_idm_xmit`.
   - **Validate (bring up a real AP first if not already up — see
     `wifi_ap_bringup_and_regdb_fix_2026-07-07.md`):** associate a real STA, generate
     upstream traffic (e.g. a ping *from* the STA), and watch
     `zx-eth-main.c`'s existing `zx_idm_tx_reclaim`/`atomic_read(&e->tx_pending)` — TX
     descriptors should now be produced on `idm0`/`idm1` where previously only `sw`
     carried traffic. A debugfs counter "wifi_tx_injected" is cheap to add for this.

4. **Wire up RX-side dispatch in `zx_idm_poll()` (§3's second code block), replacing
   `napi_gro_receive` when a mapping exists.** ⚠ Insertion point is BEFORE the existing
   `eth_type_trans()` call (`zx-eth-main.c:1684`) and the dispatch branch must NOT call
   `eth_type_trans()` itself — it pulls the Ethernet header, which `ndo_start_xmit`
   needs intact (§3, corrected).
   - **Validate — this is the step that answers §4's falsifiable claim:** send a frame
     *toward* the STA from the CPU side (e.g. `ping <STA IP>` from the router itself, or
     any downstream traffic that would normally exit via `br0`→`wlan1`). Confirm
     `idm_rx_count` / `idm_rx_per_ssid[ssid]` increments **only if** something upstream
     of the ring (still just Linux's own SW bridge at this point — HW CLA/FDB steering
     is Phase C) is made to route that traffic onto the `idmN` netdev instead of directly
     to the vif. **This may require an additional step 4.5**: bridging `idmN` into `br0`
     alongside the vif (or replacing the vif's `br0` membership with `idmN`'s) so that
     Linux's own software bridge, not just a raw netdev, treats `idmN` as the WiFi
     client's egress — otherwise nothing chooses to send traffic there. This bridging
     question is **not resolved by this spec** and should be the first thing the
     coding agent re-derives/tests once steps 1-3 are proven (mirrors idmfdb's own
     symmetric design: RX dispatch only fires for traffic that *arrives on the ring*,
     which requires something upstream to have chosen to put it there).

5. **Once 1-4 pass on live SW-forwarded traffic (idm_rx_count/idm_tx_injected both
   nonzero, ping still works end-to-end through the new path), only then move to Phase C**
   (CLA/PM flow-offload emitting `gemport_uni_id = 0x10|(idm_ring<<3)|ssid` for a
   WiFi-destined hardfast flow) — Phase C assumes Phase B's ring-level plumbing is
   already proven, not the other way around.

---

## 6. Open questions (do not guess past these)

1. **How stock populates `wlan_to_idm_map` (`0xc0691650`)** — NARROWED by the
   verification pass but still not fully traced. What is now known: it is NOT
   `sw_init_wlan_ssid` (that function *reads* the table and programs the TM ACL essid
   map from it — §1.5, corrected); no stock kmod writes it (full reloc scan — only
   switch.ko references the exported symbol, read-only); its address sits in vmlinux's
   `systools_proc_opts` blob (`vmlinux.dis:1237682`, blob @ c04dc850), so 🟡 it is
   written from userland via the stock systools config machinery at WLAN-config time
   (which also explains it being populated before `mbss_create_vif` runs). The exact
   systools command/proc path is untraced. **Not needed for the mainline implementation**
   (§1.5/§3 conclude mainline should bypass this table entirely).
2. **`ffe_get_npu_enable()`** — MOSTLY RESOLVED by the verification pass:
   disassembled at `vmlinux.dis` c0458714 — a 7-instruction getter,
   `return p ? *(u32*)(p+0x34) : 0` where `p = *(*(u32*)0xc07f7630 + 8)` — i.e. a
   global FFE/NPU-state "master enable" flag exactly as hypothesized. Who sets the flag
   (and the struct's full layout) remains untraced; irrelevant to a from-scratch
   mainline design, which has no equivalent global engine gate.
3. **The exact `(idm_ring, ssid)` discovery/configuration policy for a mainline vif**
   (§3's "this is a policy decision, not something the decomp can settle") — needs a
   human/design decision (devicetree property? debugfs? hostapd bring-up convention?),
   not an RE question.
4. **Whether `zx_idm_xmit`'s raw `ndo_start_xmit` bypass (mirroring stock, §2.3) or
   `dev_queue_xmit()` (qdisc-safe) is the right choice for the TX hook** — flagged as a
   design choice in §2.3, not resolved here; recommend starting with the direct call and
   revisiting only if backpressure causes drops.
5. **Step 4.5 in the checklist (§5)** — how upstream SW-forwarding decides to route
   CPU-originated WiFi-bound traffic onto the `idmN` netdev instead of directly to the
   vif's own netdev, so that the RX-side dispatch (§3) has anything to dispatch during
   Phase B validation (before Phase C's HW flow-offload exists to do this automatically).
   Not resolved — flagged as the first thing to re-derive when implementing.

---

## Source-cite index (file:line, for spot-checking)

- `ghidra/output_ko/idmfdb.ko/register_idm_fdb_node.c` (whole file, 46 lines) — the
  writer; offsets `+0x00,+0x04,+0x10,+0x14` written, `+0x01,+0x03` only ever read.
- `ghidra/output_ko/idmfdb.ko/get_node_index.c` (whole file) — `node_index = ssid+idm*8`
  computed from the *map* struct's `+0x25`/`+0x26`.
- `ghidra/output_ko/idmfdb.ko/idm_fdb_forward.c` (whole file, 608-byte fn) — RX dispatch,
  `node_index = ssid+idm*8` computed independently from `skb->cb[0xb7]`/idm-ring arg,
  direct `ndo_start_xmit` call at line 54.
- `ghidra/output_ko/idmfdb.ko/idm_fdb_recv_handle.c` (whole file, 400-byte fn) — TX
  injection, `skb->cb[0xb7] = node[3]` (ssid stamp) at line 19, direct dispatch to
  `node->idm_dev` (`node[0x10]`) at line 55.
- `ghidra/output_ko/idmfdb.ko/print_idm_map.c` (whole file) — the cleanest single source
  for the `fdb_list` struct's field layout (`"idm:%d ssid:%d dev:%s"` format string at
  line 43 naming offsets `+1`, `+3`, `+0x14`).
- `ghidra/output_ko/idmfdb.ko/idm_fdb_idm_isolate_handle.c` (whole file) — 4th
  independent reader of `+0x00`,`+0x04`,`+0x08`,`+0x14`; isolate policy (context only).
- `ghidra/output_ko/idmfdb.ko/idm_fdb_init.c` — hook install (`idm_skb_recv =
  idm_fdb_forward`), confirms nothing new vs. ssid-encoding spec §5.
- `ghidra/output_ko/mt7915.ko/mbss_create_vif.c:164-167` (provenance of `local_8d` at
  `:33,69,104-108`) — the real (non-stub) caller of `register_idm_fdb_node`, showing the
  `wlan_index` (`local_8d`, `+5` for slots >4) is a WLAN-driver-internal integer, not a
  switch-side value.
- `ghidra/output_ko/mt7915.ko/{register_idm_fdb_node,idm_fdb_recv_handle,
  idm_fdb_hook_xmit}.c` — all 1-byte `halt_baddata()` stubs, confirming these are
  *imported* (from idmfdb.ko) in mt7915.ko, not locally defined.
- `refs/orca-h3600p/ghidra/output_ko/idmfdb.ko/register_idm_fdb_node_bydev.c` (whole
  file) — sibling devname-keyed registration entry point (via `IfName2WlanIdmMap`
  instead of `WlanIndex2WlanIdmMap`), same fdb_list write pattern, present only in the
  orca-h3600p build variant.
- `tasks/00.10.01.re-vmlinux/vmlinux.dis:749085-749263` — full disassembly of
  `WlanIndex2WlanIdmMap`, `WlanCardOffset2WlanIdmMap`, `WlanProbeSeq2WlanIdmMap`,
  `ApcliCardIndex2WlanIdmMap`, `IfName2WlanIdmMap`, `WlanIfName2Index`,
  `ApCliIfName2Index` — all six linear-scan the same 16×41-byte table at `0xc0691650`,
  cross-confirming the struct layout in §1.5's table.
- `tasks/00.10.01.re-vmlinux/nm.txt:42278,10319` / `symbols.txt:32717,32721` —
  `WlanIndex2WlanIdmMap`/`IfName2WlanIdmMap` are `EXPORT_SYMBOL`'d vmlinux builtins
  (`__ksymtab_*`/`__kstrtab_*` present), not `.ko`-local — resolves Q4's "exporting
  module not present" framing: there is no exporting *module*, it's core vmlinux.
- `decomp_all_switch.c:4549-4568` (`get_sw_port_from_devname`) — independent 3rd
  confirmation of `IfName2WlanIdmMap` field offsets `+0x25`/`+0x26` (idm/ssid), matching
  the vmlinux disassembly exactly.
- `zx-eth-main.c:107-124` (IDM_REG_* macros), `:304-306` (IDM_DESC_* macros), `:416-418`
  (existing ssid-decode counters), `:1485-1572` (`zx_idm_init*`, incl. RX_ENABLE write
  at `:1564`), `:1621-1707` (`zx_idm_poll`), `:1733-1785` (`zx_idm_xmit`), `:1846-1853`
  (idm netdev ops), `:6874-6914` (`zx_eth_probe_port`, idm0/idm1 netdev creation),
  `:668-722` (`zx_fdb_add`, unchanged — no ssid field to add, confirmed again here).
- `wifi_stage3_PLAN_2026-07-07.md` §1 (commit `1478beecf`) — port 6/7 isolation already
  open, cited for §4's enablement answer.

Added by the verification pass (2026-07-23):
- `ext/rootfs/kmodule/idmfdb.ko` **binary** — `readelf -S/-s`: `fdb_list` = 4736-byte
  OBJECT = whole `.data..read_mostly` section (PROGBITS @ file 0x3440); hexdump of all 16
  node initializers confirms static `idm=k>>3` @+0x01 (+ duplicate @+0x02), `ssid=k&7`
  @+0x03 (§1.4, Q5 now binary-proven).
- `ext/rootfs/kmodule/switch.ko` relocations — `R_ARM_ABS32 wlan_to_idm_map` at .text
  +0x74a8 with in-place addend **+1** (the `sw_init_wlan_ssid` literal): proves the
  row+1 pointer convention and hence ifname@+0x01/flag@+0x00; full reloc scan of every
  stock `.ko` (ext + orca): only switch.ko references the table symbol, mt7915.ko does not.
- `decomp_all_plat_zxylzb_9128S.c:4122` (ring-RX skbs pre-marked `skb+0xbc|=0x10`),
  `:4125-4131` (RX ssid decode: desc byte6 bit3 valid / bits0-2 ssid → `cb[0xb7]`,
  invalid→0xff), `:4132-4136` (`idm_skb_recv==NULL` fallback = the only eth_type_trans
  on this path), `:4268-4270` (TX desc word1 = `len | ring<<31 | cb[0xb7]<<28`, unmasked).
- `decomp_all_switch.c:5112-5143` (`sw_init_wlan_ssid` — reads the map via row+1 pointer:
  flag@`iVar1-1`, idm@`iVar1+0x24`=abs+0x25 → port 6/7, essid@`iVar1+0x26`=abs+0x27,
  name=`iVar1` → `aclWLANToIDMEssidCfg2`).
- `decomp_all_tm.c:50175-50227` (`aclWLANToIDMEssidCfg2` stores {port,essid,name} in
  `s_aclWlanToIdmEssidMap` stride 0x12; `aclEssidToWlanIDMMap2` validates essid as
  `param_1-0x10 < 0x10` → essid range **0x10..0x1f** = Phase A's `0x10|(idm<<3)|ssid`).
- `tasks/00.10.01.re-vmlinux/nm.txt:42288` (`c0691650 t wlan_to_idm_map`) +
  `vmlinux.dis` `__ksymtab_wlan_to_idm_map` @ c05ed630 — the table is a named, exported
  vmlinux object; its address also appears in the `systools_proc_opts` blob
  (`vmlinux.dis:1237682`) → §6.1's populate-path narrowing.
- `vmlinux.dis` c0458714 (`ffe_get_npu_enable` full disassembly — §6.2).
- `ghidra/output_ko/idmfdb.ko/{idm_led_timer_handle,idm_fdb_multi_send_handle,
  print_idm_led,print_idm_led_stat}.c` — completing the fdb_list-touching sweep for
  §1.4's no-runtime-write claim (`idm_fdb_multi_send_handle.c:219` is also the third
  independent `ssid + idm*8` site).

## Relationship to the ssid-encoding spec's own open questions

Of that document's 6 open questions, this pass resolves **#4** (`WlanIndex2WlanIdmMap`/
`IfName2WlanIdmMap` internals — §1.5 above) and **#5** (fdb_list write-site — §1.4 above,
answer: "there is no runtime write site, they're static" — since upgraded to ✅ by the
2026-07-23 verification pass's binary `.data` dump). Questions #1/#2/#3 (FDB-A
spare bits, ssid_out provenance on a plain DA hit, CLA `outport` vs `gemport_uni_id`)
were already independently resolved by the Phase-A stock-live correlation
(`wifi_stage3_stock_ssid_correlation_2026-07-07.md`) and are out of Phase B's scope.
Question **#6** (`ffe_learn_skb`/`ffe_get_npu_enable` internals) remains open, reproduced
here as §6.2 since `ffe_get_npu_enable` resurfaced as a real gate in
`idm_fdb_recv_handle`.
