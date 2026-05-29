# Stock CPU→LAN frame INJECTION path (decomp/static RE, 2026-05-28)

Sources: `decomp_all_plat_zxylzb_9128S.c`, `decomp_all_idmfdb.c`,
`decomp_all_switch.c`; cross-checked against the live oracle
(`stock_live_egress_oracle_re.md`) and mainline `zx-eth-main.c`.

## TL;DR

The stock kmod has **two** CPU TX submission paths, on **two different
descriptor rings with two different kick registers**:

| netdev(s) | xmit fn | ring | desc | kick reg | reaches LAN? |
|---|---|---|---|---|---|
| `sw`, `pon` | `pon_tm_net_tx` → `pon_tm_data_raw_send` → `soft_insert_tx_1desc` | **UP DMA ring** (16-byte TM descriptors, BMU bp-buffers) | 16 B | **TM[0x10054]** (or DN 0x10064) | **NO** (the oracle's dead path) |
| `idm0`, `idm1` | `idm_net_tx` | **IDM ring** (8-byte descriptors, raw skb->data DMA) | 8 B | **npp_base + 0x8040** (`IDM_REG_TX_KICK`) | **YES** — this is the fabric sw_fwd inject |

The live oracle proved `TM[0x10054]/58/5c == 0` while stock egresses. That is
because stock's egressing CPU→LAN frames go out the **IDM ring** (`idm_net_tx`,
kick `npp+0x8040`), **NOT** the UP DMA ring. `pon_tm_net_tx`/`soft_insert_tx_1desc`
(the UP-ring path mainline's `zx_sw_xmit` clones) is the GPON/`pon` upstream path
and is simply unused for CPU→LAN egress in LAN-only mode.

> Mainline's bug: CPU→LAN is wired to `zx_sw_xmit` (kicks TM[0x10054]). The
> CORRECT mechanism — `zx_idm_xmit` (kicks `npp+0x8040`) — is **already
> implemented** in mainline but only bound to `idm0`/`idm1`. The fix is to
> egress CPU→LAN through the IDM ring, not the TM UP ring.

## The exact stock IDM inject mechanism (`idm_net_tx` @ 0x15ea8)

```
ndo_start_xmit(skb, ndev=idmN):
  desc_base = tx_desc          (= idm_desc_addr + 0x4000 ; programmed into npp+0x8004)
  idx       = idm_tx_index;  idm_tx_index = (idx+1) & 0x3ff   (1024-entry ring)
  pa        = skb->data_phys - 0x80000000          (DMA addr, low 2 GB alias)
  if (skb->len < 0x21) skb->len = 0x21             (min 33B)
  desc[idx*2 + 0] = pa
  desc[idx*2 + 1] = len               (bits 0..13, mask 0x3fff per dump_idm_desc_tx)
                  | (idm_port_idx << 31)           (ndev->priv 0x4c4: idm0=0 / idm1=1)
                  | (skb->cb[0xb7]  << 28)          (egress LAN port / SSID, 4 bits)
  tx_skb[idx] = skb            (reclaimed in idm_check_tx_done_nolock via npp+0x8044)
  DataSynchronizationBarrier(0xf)
  *(npp+0x8040) = nframes << 16     (IDM_REG_TX_KICK; HIGH16 = "frames to send")
```

Descriptor = **8 bytes / 2 words**. Word0 = phys buffer addr. Word1 =
`len[13:0] | ssid/port[31:28] | idm[31]`. TX-done: `npp+0x8044` LOW16 =
consumed count; ACK by writing that count back to `npp+0x8040` LOW16.

Init (`pon_npp_idm_init` @ 0x161b8): RX descs at `npp+0x8008`, TX descs at
`npp+0x8004` (note: NOT the TM 0x10000 window — IDM lives at `npp+0x8000`),
RX-enable `npp+0x800c=0x4000800`, IRQ mask `npp+0x8024`, byteorder
`npp+0x8000 |= 0xf0000`.

### How an IDM-submitted frame reaches QMG sw_fwd → SOPC → MAC
The IDM block is the **CPU-port DMA master** sitting on the NPP fabric. A frame
DMA'd in via the IDM TX ring is presented to the switch fabric as a
CPU-port-sourced packet → QMG makes a **sw_fwd** decision (oracle: 0x9234c044
counts) → PP_BRG FDB DA-lookup resolves the dst MAC to the LAN egress port →
SOPC `send2smac2` (oracle: 0x921d9164 counts) → MAC2 TX. No 16-byte TM descriptor,
no BMU bp alloc, **no TM[0x10054] kick** — exactly matching the oracle. The
`cb[0xb7]<<28` field is the explicit egress-port override (set by the WiFi FDB
forward path `idm_fdb_forward`/`idm_fdb_recv_handle`; for a routed/bridged host
frame it's 0xff = "let FDB decide").

## Required change to mainline `zx_sw_xmit`

`zx_sw_xmit` (zx-eth-main.c:3225) must **stop building a 16-byte TM desc and stop
kicking TM[0x10054]**, and instead submit via the IDM ring like `zx_idm_xmit`
(zx-eth-main.c:1540). Concretely, the simplest correct fix:

1. **Re-point the `sw` netdev's `ndo_start_xmit` at the IDM path.** Change
   `zx_sw_netdev_ops.ndo_start_xmit` from `zx_sw_xmit` to a wrapper that calls
   the IDM submit, OR set `zx_sw_netdev_ops = ... .ndo_start_xmit = zx_idm_xmit`
   after giving the `sw` netdev an IDM-port priv. The whole TM/BMU TX machinery
   (`zx_bmu_alloc_bp`, `txdesc_cpu`, `TM[0x10054]` kick, dual-kick, post-kick
   invalidation) is **dead code for egress** and should be removed from the TX
   path.

2. If keeping a distinct `zx_sw_xmit`, rewrite its body to be `zx_idm_xmit`'s
   body: 8-byte desc into `e->desc_cpu + IDM_TX_DESC_OFFSET`, word0 = dma addr,
   word1 = `len | (port_idx<<31) | (egress_port<<28)`, `dma_wmb()`, then
   `npp_write(e, IDM_REG_TX_KICK, 1<<16)`. **Never** write `tm_write(e,0x10054,..)`.

3. **Add the egress-port field** `zx_idm_xmit` currently omits: word1 should be
   `(len & IDM_DESC_LEN_MASK) | (port->idx ? IDM_DESC_PORT_BIT : 0) |
   (egress_port << IDM_DESC_PORT_SHIFT)` where `IDM_DESC_PORT_SHIFT = 28`. For
   a host LAN frame let the FDB decide (egress_port = 0xff masked to 4 bits, i.e.
   leave the field 0 → "no override" and rely on PP_BRG DA-lookup, which the
   oracle confirms routes to MAC2). Only set bits[31:28] when explicitly
   targeting a port.

4. **Reclaim** must follow stock `idm_check_tx_done_nolock`: poll
   `npp+0x8044 LOW16`, free that many `tx_skb[]` entries, ACK by writing the
   count to `npp+0x8040 LOW16` (mainline's NAPI TX-done at line 1403/1427
   already does this — reuse it).

Net effect: CPU→LAN frames flow CPU → IDM DMA → QMG sw_fwd → SOPC send2smac2 →
MAC2, with TM[0x10054]/58/5c untouched — bit-for-bit the stock oracle behaviour.

## Storm-free MAC2 enable (confirmed; do ONLY this, in this order)

Per the oracle the MAC is the **last** step, fed by the fabric (not the U-Boot
direct mux). Apply to MAC2 (= npp_base + 3*0x40000 = 0x92280000):

```
MAC2 +0x000 ctrl     = 0x00ba6003     (tx_en|rx_en bits0,1 + link bit15) — already matches
MAC2 +0x004 IRQ_MASK = 0x00003fff
MAC2 +0x008 ENABLE   = 0x80000001     (bit31 + bit0)
```
and **leave at 0** (do NOT write the U-Boot direct-mux words — this is what
caused the storm):
```
MAC2 +0x0e0 = 0   (iface direct-mux; stock NEVER writes 0x11200)
MAC2 +0x070 = 0
MAC2 +0x0b4 = 0
MAC2 +0xc20 = 0
MAC2 +0xc50 = 0
```
The storm in prior iters came from enabling the MAC *and* writing `+0xe0=0x11200`
(mixing direct-mux egress with fabric egress). With the IDM/fabric inject path,
the direct mux must stay disabled.

## PP_BRG secondary fixups (cosmetic; not the gate)

`pon_pp_brg_init` @ 0x17ba4 writes `pp_base+0x8008 = 0xff00` and
`pp_base+0x863c = 0xaaaaaaaa` — these MATCH mainline, **not** the oracle's
stock-LIVE values (`0x8008=0xdfdf`, `0x863c=0`). Nothing in the kmod
(`switch.c`/plat) rewrites them afterward, so the oracle's `0xdfdf`/`0` are set
by **cspd userspace** per-port recv/fwd-mask tuning later in boot. They are NOT
the egress gate (the gate is the inject ring). If aligning anyway, after
`pon_pp_brg_init`'s equivalent in mainline:
```
pp +0x8008 = 0x0000dfdf    (vs mainline/init-default 0xff00)
pp +0x863c = 0x00000000    (vs mainline/init-default 0xaaaaaaaa)
```
Low risk, do alongside the MAC enable as a cheap poke; revert if no effect.

## Concrete implementation plan for zx-eth-main.c

1. Add `#define IDM_DESC_PORT_SHIFT 28` and a 4-bit egress-port mask.
2. Delete the TM-UP-ring TX body of `zx_sw_xmit` (BMU alloc, 16B desc,
   `tm_write(0x10054/0x10064)`, post-kick invalidation). Re-implement it as an
   IDM submit (clone `zx_idm_xmit` body) or just bind `sw`'s
   `ndo_start_xmit = zx_idm_xmit` with an IDM port priv.
3. In the IDM submit, set word1 egress-port bits only when overriding;
   otherwise 0 (FDB DA-lookup routes to MAC2 — confirmed by oracle).
4. Ensure the IDM ring + `pon_npp_idm_init`-equivalent (`npp+0x8004/0x8008/
   0x800c/0x8024`, RX prefill, byteorder `npp+0x8000|=0xf0000`) is initialised
   before TX (mainline `zx_idm_*_init` already does this — verify it runs for
   the `sw` data path, not just idm0/1).
5. MAC2 enable sequence above (ctrl/IRQ_MASK/ENABLE only; all direct-mux words 0).
6. TX reclaim via NAPI polling `npp+0x8044`, ACK to `npp+0x8040` LOW16.
7. (Optional) PP fixups `0x8008=0xdfdf`, `0x863c=0`.

Verify on device: during `txtest`, `npp+0x8044` (IDM TX status) and QMG sw_fwd
(0x9234c044), SOPC send2smac2 (0x921d9164), MAC2 TX-OK (0x92280718) all climb
together, while `TM[0x10054]/58/5c` stay 0 — matching the stock oracle.
