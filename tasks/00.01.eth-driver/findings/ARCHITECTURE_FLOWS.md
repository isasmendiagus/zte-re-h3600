# Mainline driver — data flow diagrams

Visual reference for how packets traverse the ZX279128S hardware + Linux
networking stack in our mainline driver. Useful when debugging — tells
you exactly where to insert a printk or look for a stuck buffer.

## CPU-path LAN ping (current setup)

```
Host                                Device (ZX279128S)
─────                               ─────────────────────────────────────────────
ICMP echo request    ──────────→    LAN MAC (0..3) physical port
                                    │
                                    ↓
                                    Switch fabric (PP block)
                                    │  consults HW FDB (sbrag table) for dst MAC
                                    │  dst = our_mac → routed to CPU port 6/7
                                    ↓
                                    TM block (Traffic Manager)
                                    │  HW grabs BMU buffer (BP), DMAs frame in
                                    │  format: [16-byte prefix][ethernet frame]
                                    │  Writes RX descriptor with bp_idx + len
                                    ↓
                                    TM IRQ (GIC 68)
                                    │  zx_tm_irq → napi_schedule
                                    ↓
                                    zx_tm_napi_poll
                                    │  Reads RX desc, extracts bp_idx
                                    │  bp_buf = bp_dma + bp_idx * 2304
                                    │  Heuristic: frame at bp_buf+16 (HW prefix)
                                    │  Drops LOOPBACK if src_mac == our_mac
                                    │  Dynamic FDB learn host_mac → ingress_port
                                    ↓
                                    netif_receive_skb()
                                    │  Linux IP stack processes ICMP echo
                                    │  ICMP responder generates reply skb
                                    ↓
                                    ndo_start_xmit = zx_sw_xmit
                                    │  zx_bmu_alloc_bp() — HW BMU protocol
                                    │  (tm[0x8014]|=1; poll; read tm[0x800c])
                                    │  bp_idx returned, bp_buf at known location
                                    │  memset(bp_buf, 0, 16) — clear HW prefix area
                                    │  memcpy(bp_buf+16, skb->data, len) — frame at +16
                                    │  Build TX descriptor:
                                    │    desc[0] = 0xc9 (CPU/source marker)
                                    │    desc[2..3] = port hint (port=0 hardcoded)
                                    │    desc[6] = 0x01 ; desc[7] = (bp_idx&0x7f)<<1
                                    │    desc[8..11] = ((bp_idx>>7)&0x7f)
                                    │                | ((len & 0x3fff) << 9)
                                    │                | (0x21 << 24) [VALID|0x20]
                                    │    desc[12..13] = len << 2 (or 0x100 if small)
                                    │  TM kick: tm[0x10054] = 1 (upstream only)
                                    ↓
                                    TM processes desc, reads bp_buf via DMA
                                    │  HW skips 16-byte prefix, reads len bytes
                                    │  passes frame to PP switch
                                    ↓
                                    Switch fabric — egress
                                    │  Consults HW FDB for dst MAC (host)
                                    │  If found: egress to specific LAN MAC port
                                    │  If miss : FLOOD all LAN ports
                                    │  ALSO sends copy back to CPU port (LOOPBACK)
                                    ↓
                                    LAN MAC → wire    ──────────→ Host sees reply
                                    │
                                    │ (and ALSO bounces back to CPU port — caught
                                    │  by our LOOPBACK drop heuristic in napi_poll)
```

## Heuristics currently active

⚠️ **Most of these are OUR invention, not validated against stock**.
Listed here so we can challenge each one later. None of them are confirmed
to match stock's actual behavior — only #4 has a partial correspondence in
stock decomp.

| # | Where (file:line) | What | Confidence vs stock | Why we did it |
|---|---|---|---|---|
| 1 | eth.c:1916-1921 | **Ethertype offset detect** — `frame_at = (bp_buf[12..13] >= 0x0600 && != 0xffff) ? bp_buf : bp_buf+16` | 🟡 **EMPIRICALLY NECESSARY** (tested 2026-05-25 05:03). Removed it (forced +16 always) → 100% loss. So SOME frames legitimately come at +0 even after the FDB fix that eliminated DUPs. Unknown what they are — could be short frames bypassing prefix, or another class of loopback we haven't classified. Stock decomp has no such conditional but stock's bp_buf address formula differs from ours. Keep heuristic until we understand what `+0` frames are. | We observed RX buffers with frame at +0 AND +16. Couldn't tell apart by length/desc. Used ethertype as crude tag. |
| 2 | eth.c:1943-1947 | **LOOPBACK drop** — if `src_mac == our_dev_mac` drop frame | 🟡 **Stock probably doesn't need this**. Stock's switch routes CPU TX to specific egress port (no flood), so no bounce-back to itself. Stock has no "if src==my_mac drop" code we found. We added it because OUR switch floods → we'd otherwise re-process our own TX as RX and loop forever. **Should become a no-op once HW FDB is correctly populated.** | Without this, every TX from CPU comes back as an RX event, Linux processes it, may generate yet another reply, infinite cascade. |
| 3 | eth.c:1968-1980 | **Dynamic FDB learn from RX** — on each delivered packet, register `src_mac → ingress_port` in HW FDB | 🟡 **Stock uses `ffe_learn_skb`** (different mechanism — fast forwarding engine, not direct FDB write). We approximate via `zx_fdb_add` which writes a (now hopefully right-format) entry to brg_ram. Stock's path is more efficient (HW does it). | Bootstrap problem: at boot, FDB is empty; without learning anything, every unicast TX floods. We seed entries as host packets arrive. |
| 4 | eth.c:2235 | **TX frame at bp_buf+16** with 16-byte zero prefix | 🟢 **Partial match**. Stock `pon_tm_data_raw_send` does `memcpy(__dest, skb->data, __n)` where `__dest` is an address calculated as `bp_size * idx + pdt_mem_size + (some negative constants)`. Stock's `__dest` formula probably already includes the +16 offset implicitly. Our explicit `bp_buf+16` is the visible equivalent. **Empirically validated**: this fix took us from 0 wire frames to working frames. | RX clearly has [16-byte prefix][frame] layout (BPDUMP confirms). TX must mirror or HW DMAs the wrong bytes. |
| 5 | eth.c:2375 | **HW FDB seed** — at probe, register our own MAC at port=1 | 🟢 **Matches stock kotrace exact** — captured `sbrg_add_mactable(mac=our_mac, port=1)` at stock boot. | Without seeding our own MAC, switch doesn't know where to route packets destined for us (matters less for ICMP echo, but matters for any device-targeted unicast). |

## When the heuristics should go away

Heuristics 1, 2, 3 are workarounds for **broken switch egress routing**.
They mask the real problem: our HW FDB write doesn't actually populate
the table the switch consults during egress decisions, so the switch
floods on every unicast TX.

Once we fix:
- **D2→D1→D0 write order** (done — D0 commits last)
- **Entry encoding format** (done — matches stock sbrg_add_mactable)
- **Probe-loop d1/d2 clobber bug** (done — save before, restore for set)
- **Hash function** (TODO — currently CRC-16/IBM, stock uses CRC-16/CCITT)
- **Status nibble check** (done — bit 31..28 of d2 instead of d0)

…the switch should stop flooding, LOOPBACK drops should disappear,
DUPs should drop to near-zero, and we can DELETE heuristics 1, 2, 3.

If after that the system still floods, the problem isn't entry format —
it's something else (maybe table_sel value, maybe `cla_set_unknown_da_action_cfg`,
maybe `dpa_set_protocol_pkt_aly_en` gating, maybe the mem_id we're writing
to isn't the table the switch egress logic actually reads).

## DUPs source (current understanding)

Switch egress on unicast TX:
- **Best case**: HW FDB has dst_mac → egress to specific port → host sees 1 frame.
- **Current behavior**: HW FDB miss (we write to wrong-table format → switch doesn't find entry) → **flood to all LAN ports + CPU port**. Host's LAN port sees frame. CPU port sees bounce (we drop).

If host's NIC is connected to MULTIPLE LAN ports (4×RJ45 → 4 MAC ports), some configurations could result in host seeing the same frame from multiple ports → DUPs from host's perspective.

OR: switch internally generates MULTIPLE egress events because flood logic + bridge port mask interaction. Each generates a separate wire emit.

## HW responder path (NOT active for LAN — stock also doesn't use)

```
Host    ── ICMP echo (192.168.1.1) → wire ──→  CLA classifier (PP block)
                                                │  Checks: local_ipv4_addr == dst IP?
                                                ↓ YES
                                                HW generates ICMP echo reply directly
                                                │  No CPU involvement
                                                │  Wire latency: sub-ms
                                                ↓
LAN MAC → wire  ←──────────────────────────────  back to host
```

To enable: `cla_set_local_ipv4_addr(0xc0a80163)` → writes `PP[+0xc09c] = 0xc0a80163`.
Stock doesn't enable this for LAN IP. We don't either.

## TX BMU buffer layout

```
bp_cpu base (ioremap)
  │
  ↓
bp_buf = bp_cpu + bp_idx * 2304     (= TM_BP_SIZE)
  │
  ↓
+0    [HW prefix — 16 bytes, we memset to 0]
+16   [ethernet frame — skb->data copied here]
+16+len  [padding / unused, up to 2304]
```

HW reads `len` bytes starting at `bp_buf + 0`, but interprets the first
16 as "HW metadata to skip" and emits bytes 16..16+len-16 on wire. So
effectively HW reads from bp_buf+16. (TODO: verify whether `len` in desc
should include the 16 prefix or not — current code uses skb->len without
prefix offset, which seems to work.)
