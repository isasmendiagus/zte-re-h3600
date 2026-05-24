# Runtime call trace of `chip_tm_init` WITH arguments

Captured 2026-05-23 via `kotrace.ko` Phase 3b — extended thunks now write
`[marker(1B) pad(3B) r0(4B) r1(4B) r2(4B) r3(4B)]` to a ring buffer in
`module_alloc`'d kernel memory. Buffer is exposed via
`/proc/kotrace_dump` as text (`<seq> <marker> <r0_hex> <r1_hex> <r2_hex> <r3_hex>`).

**Full raw dump**:
[`captures/kotrace_full_args.txt`](captures/kotrace_full_args.txt) (610 entries).

Builds on [[chip_tm_init_sequence]] (Phase 3 — order only, no args).

---

## Per-marker call counts (610 total)

```
l=217  tm_protocol_pkt_limit_pps_set      ← per-port × per-queue/protocol PPS limits
t=164  zte_api_pp_set_trap_queue          ← per-port × per-trap-class
r=142  zte_api_pp_set_pro_action          ← THE def_ptl_pkt_action table (#93)
V= 18  zte_api_sw_vlan_set_port_vlancfg   ← VLAN config (varies per port)
p=  8  zte_api_sw_port_init               ← per-port (8 ports)
v=  8  zte_api_sw_vlan_set_port_pvid      ← PVID per port
i=  8  zte_api_sw_port_set_port_isolatemask  ← isolation mask per port
b=  8  zte_api_sw_set_port_brdcast        ← broadcast policy per port
u=  8  zte_api_sw_set_port_unicast        ← unicast policy per port
m=  8  zte_api_sw_set_port_muticast       ← multicast policy per port
q=  8  zte_api_pp_set_cpu_queue_rate      ← per-queue rate limit
E=  5  ethdrv_port_dev_init               ← per UNI port (UNIs 0..4)
S=W=C=A=G=P=g=s=1                          ← one-shot global setups
```

## Compressed call sequence (deduped consecutive)

```
l S W E C G p v V i b u m
P q l q l q l q l q l q l q l q l   ← 8 queues
t l t l t l ... × 80 pairs           ← trap_queue + pps_limit per port × protocol
r r r r ... × 142                    ← THE pro_action table
g s A l
```

The dense `t l` and `r` runs make this the BULK of the init work.

## The reverse-engineering wins for the mainline port

### Win #1 — `pro_action` is `def_ptl_pkt_action` (task #93 blocker)

142 calls = 71 protocol IDs × 2 PP instances. r0 ∈ {0,1} (PP instance),
r1 = protocol id, r2 = action (1 = trap/forward to CPU, 0 = normal),
r3 = 0 (reserved).

```c
// Reconstructed from the trace — the FULL def_ptl_pkt_action table
struct ptl_action { u8 proto; u8 action; };
static const struct ptl_action def_ptl_pkt_action[] = {
    { 0x3f, 1 }, { 0x21, 1 }, { 0x12, 0 }, { 0x1e, 0 }, { 0x0a, 1 },
    { 0x1c, 1 }, { 0x05, 1 }, { 0x06, 1 }, { 0x07, 1 }, { 0x08, 1 },
    { 0x09, 1 }, { 0x04, 1 }, { 0x03, 1 }, { 0x00, 1 }, { 0x01, 1 },
    { 0x02, 1 }, { 0x1f, 0 }, { 0x16, 1 }, { 0x17, 1 }, { 0x18, 1 },
    { 0x19, 1 }, { 0x15, 1 }, { 0x13, 1 }, { 0x14, 0 }, /* NB: r0=0 has 1, r0=1 has 0 */
    { 0x20, 0 }, { 0x1a, 1 }, { 0x0e, 1 }, { 0x0f, 1 }, { 0x10, 1 },
    { 0x0c, 1 }, { 0x40, 1 }, { 0x41, 1 }, { 0x42, 1 }, { 0x29, 1 },
    { 0x2b, 1 }, { 0x0b, 1 }, { 0x43, 0 }, { 0x44, 0 }, { 0x23, 0 },
    { 0x24, 0 }, { 0x2c, 1 }, { 0x25, 1 }, { 0x1d, 1 }, { 0x45, 1 },
    { 0x46, 1 }, { 0x22, 1 }, { 0x0d, 1 }, { 0x11, 1 }, { 0x1b, 1 },
    { 0x26, 0 }, { 0x27, 1 }, { 0x28, 0 }, { 0x2a, 1 }, { 0x2d, 1 },
    { 0x2e, 1 }, { 0x2f, 1 }, { 0x30, 1 }, { 0x31, 1 }, { 0x32, 1 },
    { 0x33, 1 }, { 0x34, 1 }, { 0x35, 1 }, { 0x36, 1 }, { 0x37, 1 },
    { 0x38, 1 }, { 0x39, 1 }, { 0x3a, 1 }, { 0x3b, 1 }, { 0x3c, 1 },
    { 0x3d, 1 }, { 0x3e, 1 },
};
```

⚠️ Entry `{0x14, 0/1 inconsistent}` between r0=0 and r0=1 calls — needs
double-check at index 484-485 in the raw dump. May indicate per-PP-instance
behavior (PPE 0 vs PPE 1 see different action for protocol 0x14).

For mainline driver: build this table from the trace, replay via the
mainline equivalent of `zte_api_pp_set_pro_action()`.

### Win #2 — `sw_global_init` magic numbers

`zte_api_sw_global_init(ctx_ptr, 0x8100, 0x9100, 0x9200)`:
- 0x8100 = IEEE 802.1Q VLAN ethertype (standard)
- 0x9100 = QinQ outer tag ethertype (common but non-standard)
- 0x9200 = (?) extended VLAN ethertype — may be ZTE custom or AppleTalk?

For mainline: pass the same three ethertypes when calling our equivalent.

### Win #3 — `pp_global_init` magic numbers

`zte_api_pp_global_init(ctx_ptr, 0x1f40, 0, 1)`:
- 0x1f40 = 8000 (could be a packet buffer pool size, MTU * something, queue depth?)
- r3 = 1 (mode flag)

### Win #4 — `pps_limit_set` rate table

10 calls during tm.ko's own init give us the default per-protocol PPS limits:

```
(pp_inst=0, proto=0): pps=0x320 = 800
(pp_inst=0, proto=3): pps=0x190 = 400
(pp_inst=0, proto=4): pps=0x190 = 400
(pp_inst=0, proto=5): pps=0x190 = 400
(pp_inst=0, proto=6): pps=0x3e8 = 1000
(pp_inst=1, proto=0..6): same values mirrored
```

200 more `l` calls during chip_tm_init body — likely per-port per-protocol.
Full extraction TODO; for first port we already have enough to validate.

### Win #5 — per-port loop pattern (8 ports)

```c
// chip_tm_init's port loop, distilled:
for (port = 0; port < 8; port++) {
    zte_api_sw_port_init(ctx, 0x650650, port_callbacks, 1);
    zte_api_sw_vlan_set_port_pvid(port, 0, 0, 1);
    zte_api_sw_vlan_set_port_vlancfg(port, 0, 0, 3);
    zte_api_sw_vlan_set_port_vlancfg(port, 0, 0xfff, 3);
    if (port == 0)   // first iteration only: one extra vlancfg
        zte_api_sw_vlan_set_port_vlancfg(port, 0, 0xfff, 3);
    zte_api_sw_port_set_port_isolatemask(port, isolate_mask[port], cb, 0xff);
    zte_api_sw_set_port_brdcast(ctx, port_brdmask[port], cb, 0xff);
    zte_api_sw_set_port_unicast(ctx, 1, cb, 5);
    zte_api_sw_set_port_muticast(ctx, 1, cb, 0);
}
```

Isolate masks observed:
| Port | r1 (mask) |
|---|---|
| 4 (UNI 4)  | 0xffffff10 |
| 0 (UNI 0)  | 0xffffff01 |
| 1 (UNI 1)  | 0xffffff02 |
| 2 (UNI 2)  | 0xffffff04 |
| ...        | (each port can talk to all UPLINKS but not other UNIs) |

That's the standard "port isolation" pattern for ONT/CPE: each UNI talks
to the WAN/PON uplink but not to other UNIs.

## Driver port roadmap (Phase 4)

Now that we have the call sequence + args, the mainline port is a
structured exercise:

1. **Mechanical** — translate each `zte_api_*` call into the equivalent
   register write sequence in `linux-v6.6/drivers/net/ethernet/zte/zx279128-eth.c`.
   For each function:
   - Look up its body in `tasks/00.10.02.re-stock-kmods/` Ghidra project
     for tm.ko
   - Identify the register pokes it does
   - Write the same pokes in our driver, using our `tm_reg_write()` helper

2. **Hard-coded tables** — embed `def_ptl_pkt_action[]`, isolate mask
   table, pps limit table as static const arrays. They're set ONCE at
   init, never updated at runtime.

3. **Init order** — replay the SAME order as the trace shows. Some
   orderings matter (e.g., `pp_global_init` must come before `pro_action`
   calls because the PP instance must exist).

4. **Verification** — boot with mainline, check `cat /proc/net/dev` →
   `rx_packets` should be > 0 within seconds of an ARP storm from the
   host.

Expected outcome: this should resolve the entire `rx_path_dead.md`
blocker (#87, #91, #92, #93) in one PR.

## Reproduction

```bash
make -C tasks/00.01.eth-driver/kotrace
python3 tasks/00.01.eth-driver/kotrace/build_rootfs_with_kotrace.py
python3 tasks/00.04.flash-tool/flash.py rootfs \
    --src tasks/00.01.eth-driver/out/rootfs_kotrace_enc.jffs2
# wait for SSH:
ssh admin@192.168.1.1 'cat /proc/kotrace_dump' > /tmp/dump.txt
```
