# IDM-ring zx_sw_xmit: implemented + tested — frame consumed but dies before QMG (2026-05-28)

## What I changed
Rewrote `zx_sw_xmit` (zx-eth-main.c) to submit CPU→LAN TX on the **IDM CPU-port DMA
ring** (mirroring `zx_idm_xmit` / stock `idm_net_tx`) instead of the TM UP DMA ring.
- desc word0 = `cpu_to_le32(dma)` (dma_map_single of skb->data); word1 = `len & 0x1FFFFF`
  (idm_idx 0, egress_port 0 → FDB DA-lookup decides).
- ring: `e->desc_cpu + IDM_TX_DESC_OFFSET`, base already programmed to npp+0x8004
  (zx-eth-main.c:1369); kick `npp_write(IDM_REG_TX_KICK=0x8040, 1<<16)`.
- Old UP-ring/BMU/TM-desc code left below as dead (early `return` short-circuits it);
  compiles clean (build exit 0).

## Verification I did MYSELF before implementing
Read stock `idm_net_tx` (decomp_all_plat_zxylzb_9128S.c:4206): word0 = skb_data_phys
− 0x80000000 (4266), word1 = len | idm_idx<<31 | egress_port(cb+0xb7)<<28 (4268-70),
ring base npp+0x8004 = RX_base+0x4000 (4389), kick npp+0x8040 = nframes<<16 after DSB
(4289-90), **never writes TM[0x10054]** ✓ — matches the live oracle (TM[0x10054/58/5c]=0
while stock egresses) and mainline's existing zx_idm_xmit. Mechanism confirmed.

## Live test (new build active, confirmed by behavior)
Enabled MAC2 stock-style by poke first: ctrl 0x92280000=0x00ba6003 (already), mask
0x92280004=0x3fff, +0xe0/c20/c50/070/b4=0, en 0x92280008=**0x80000001**. (No storm —
+0xe0=0 so no direct-mux; loopback growth is background IPv6 MC, not MAC2.)

`txtest 3` deltas:
```
tm_tx_count           +3   software submitted 3
IDM consume npp+0x8044 +3   *** HW DMA consumed all 3 descriptors ***
QMG sw_fwd  0x9234c044  0   frame NEVER reaches QMG forward
QMG hw_fwd  0x9234c048  0
QMG hw_trap 0x9234c04c  0
drop_DSCH   0x921da04c  0   not dropped at DSCH
drop_PP     0x921da040  0   not dropped at PP
SOPC smac2  0x921d9164  0   never reaches crossbar→MAC
SMAC2 TX    0x92280718  0   MAC2 never transmits
wire (tcpdump)          0   nothing egresses
```
(tm_rx_loopback_drops / tm_rx_count grow from background device IPv6 multicast, not
the txtest — SMAC2 TX & SOPC are the clean, noise-free signals and both stay 0.)

## Conclusion (new, precise localization)
The IDM-ring submission is CORRECT — the HW DMA engine consumes the descriptor
(npp+0x8044 +3). But the injected frame **vanishes between IDM-consume and the QMG**:
it never reaches QMG sw_fwd, so never FDB-routed, never hits SOPC/MAC. So the gate is
now **the IDM CPU-port → L2-fabric forwarding/classification config**, which mainline
omits. On stock the same idm_net_tx frame reaches QMG sw_fwd → FDB → SOPC send2smac2 →
MAC2 (oracle). Mainline submits + HW consumes, but the CPU-port isn't bound to inject
into the fabric.

## Next (RE agent dispatched: idm_cpuport_fabric_forward_re.md)
Find the stock IDM-init register(s) that bind the CPU-port to the fabric (CPU-port
enable / CPU-port→QMG-CLA binding / default src-port|VLAN for IDM-injected frames /
"forward to switch" mode bit), + whether the LAN netdev's egress_port (cb+0xb7) is 0
or explicit, + confirm the LAN netdev (br0/.1) actually binds idm_net_tx. Then
poke-test the missing config. Device left on this build, MAC2 enabled.
