# Runtime call sequence inside `chip_tm_init` (stock switch.ko)

Captured 2026-05-23 via `kotrace.ko` Phase 3 (loader-notifier RAM patcher
targeting both switch.ko and tm.ko at MODULE_STATE_COMING). See
[[idea_a_kotrace]] for the tracer mechanism, and the Phase 3 entry in
[`../PLAN_init_debug.md`](../PLAN_init_debug.md) for context.

This is the first time we have the **exact runtime order** of the calls
`chip_tm_init` makes — previously we only had Ghidra static disassembly
which doesn't tell us how often each is called or which paths are
actually taken at runtime on this device.

## Methodology

`chip_tm_init` itself is in switch.ko but ALL of its `bl` callees are
`UND GLOBAL` symbols (extern) — they live in `tm.ko`. So
`kotrace.ko`'s `targets[]` was extended to two `trace_module`
entries:

```c
static const struct trace_module trace_modules[] = {
    { "switch", switch_targets, 5  },   // top-level init markers C/S/A/W/E
    { "tm",     tm_targets,     15 },   // chip_tm_init's callees: g s l P q r t G p i b m u v V
};
```

When tm.ko's COMING fires (before its `init_module`), kotrace patches its
15 target functions. When switch.ko's COMING fires next, kotrace patches
its 5 top-level inits. Once switch's `init_module` runs and calls
`chip_tm_init`, each call into tm.ko's API emits a unique 1-char marker
to UART (via direct PL011 write, bypass kmsg2uart). The result is a
single interleaved stream of stock printks + our markers.

## The captured chunk (raw)

Between the last "patched OK" of switch's targets and the `[ko:L switch]`
event (= switch's `init_module` completed, so this is the entire
`init_module` execution window):

```
SW<4>Init switch module           ← S=sw_init_switch  W=sw_init_wlan_ssid
<4>g_sw_cap.sw_uni_count=5
... [stock init prints; switch is enumerating its capabilities] ...
<4>port id 4, name pon
<4>Error! NFBI maybe not connect!
<4>Error! NFBI maybe not connect!
E<4>Error! NFBI maybe not connect!     ← E (1) = ethdrv_port_dev_init for UNI 0
<4>Error! NFBI maybe not connect!
EEEECG pvVVVVibum pvVVibum pvVVibum pvVVibum pvVVibum pvVVibum pvVVibum pvVVibum P qll qll qll qll q tl tttttttt rrA
                                       ↑ C = chip_tm_init enters
```

I split the inner sequence for readability — it's emitted as a
single contiguous burst with no separator.

## Marker-by-marker decode

Marker char → function (also defined in `kotrace.c:tm_targets[]`):

| Marker | Function | Lives in |
|---|---|---|
| `g` | `tm_cla_outspace_cfg_get` | tm.ko |
| `s` | `tm_cla_outspace_cfg_set` | tm.ko |
| `l` | `tm_protocol_pkt_limit_pps_set` | tm.ko |
| `P` | `zte_api_pp_global_init` | tm.ko |
| `q` | `zte_api_pp_set_cpu_queue_rate` | tm.ko |
| `r` | `zte_api_pp_set_pro_action` | tm.ko |
| `t` | `zte_api_pp_set_trap_queue` | tm.ko |
| `G` | `zte_api_sw_global_init` | tm.ko |
| `p` | `zte_api_sw_port_init` | tm.ko |
| `i` | `zte_api_sw_port_set_port_isolatemask` | tm.ko |
| `b` | `zte_api_sw_set_port_brdcast` | tm.ko |
| `m` | `zte_api_sw_set_port_muticast` | tm.ko |
| `u` | `zte_api_sw_set_port_unicast` | tm.ko |
| `v` | `zte_api_sw_vlan_set_port_pvid` | tm.ko |
| `V` | `zte_api_sw_vlan_set_port_vlancfg` | tm.ko |

## What chip_tm_init actually does, step by step

Tagged with the marker that appears in the stream:

### Phase A — switch global init
```
G   zte_api_sw_global_init             ← bring up the switch's central state
```

### Phase B — per-port loop, 8 iterations (one per port)

There are 8 hardware ports total: 5 UNI (LAN-facing) + 3 service ports
(WAN/PON/CPU). The 1st iteration has 4 VLAN configs, subsequent 7
iterations have 2 each:

```
p     zte_api_sw_port_init                       (init the port)
v     zte_api_sw_vlan_set_port_pvid              (default VLAN id)
VVVV  zte_api_sw_vlan_set_port_vlancfg × 4       (1st port only)
i     zte_api_sw_port_set_port_isolatemask       (which other ports this one talks to)
b     zte_api_sw_set_port_brdcast                (broadcast egress policy)
u     zte_api_sw_set_port_unicast                (unicast egress policy)
m     zte_api_sw_set_port_muticast               (multicast egress policy)
```

then 7 more times with `VV` (2 vlancfgs each).

### Phase C — packet-processor global init
```
P   zte_api_pp_global_init             ← bring up PP (the packet processor block)
```

### Phase D — CPU queue rate config, 4 iterations
```
q   zte_api_pp_set_cpu_queue_rate
l l tm_protocol_pkt_limit_pps_set × 2
```
Repeated 4 times — looks like setting up 4 CPU queue classes with
their pps rate limits.

### Phase E — one extra cpu-queue + trap-queue setup
```
q       zte_api_pp_set_cpu_queue_rate     (5th time)
t l     trap_queue + pps_limit
tttttttt zte_api_pp_set_trap_queue × 8    (one per port, 8 ports)
```

### Phase F — pro_action × 2 (THE BIG ONE)
```
r r   zte_api_pp_set_pro_action × 2
```

This is the missing piece called out in `research/rx_path_dead.md`
task #93 — `pro_action` controls per-protocol packet decisions
(forward / drop / trap to CPU). Two calls = probably one for "default
drop" + one for "specific forward rule".

### Phase G — chip_tm_init returns, sw_alarm_init runs
```
A   sw_alarm_init                       ← outside chip_tm_init; happens after it returns
```

## Cross-reference to mainline blockers

From `research/rx_path_dead.md` and the TaskList:

| TaskList | What | This trace tells us |
|---|---|---|
| #87 | "Port chip_tm_init (confirmed missing in mainline)" | The whole sequence above is what's missing |
| #89 | "Port zte_api_pp_global_init + cpu_queue_rate" | Phase C (P) + Phase D (qllqll...) |
| #90 | "Dump + replay def_ptl_pkt_map + def_ptl_pkt_action" | Phase F (rr) — 2× pro_action |
| #91 | "Decode SchRegTable/QmgRegTable → TM→PP forwarding gate" | We see the gate is configured by P+q+t+r sequence |
| #93 | "Extract def_ptl_pkt_action table + pro_action replay" | Phase F (rr) — call count and order confirmed |

## What's NOT yet visible from this trace

This gives us the **call structure**, not the **register writes** each
function performs. To get those (and the argument values), the next
step is to extend `kotrace.c` so each thunk also writes the function's
incoming `r0..r3` to a sysfs-exposed ring buffer (or to a sequence of
UART bytes if we encode them tightly).

Easier alternative: now that we know which 15 tm.ko functions to focus
on, **Ghidra-reverse those 15 functions** in the
`tasks/00.10.02.re-stock-kmods/` project. The function bodies in tm.ko
will tell us exactly which registers they poke. The runtime trace
already proves what arguments they get called with — partially —
because we see the call counts (8 per port → port index 0..7, 4 cpu
queues → queue index 0..3, etc.).

## Reproduction

```bash
make -C tasks/00.01.eth-driver/kotrace
python3 tasks/00.01.eth-driver/kotrace/build_rootfs_with_kotrace.py
# (don't redirect to terminal — let it tee to /tmp/p3_boot.log for analysis)
python3 tasks/00.04.flash-tool/flash.py rootfs \
    --src tasks/00.01.eth-driver/out/rootfs_kotrace_enc.jffs2 > /tmp/p3_boot.log 2>&1
# wait for SSH, then:
python3 -c '
import re
d = open("/tmp/p3_boot.log","rb").read()
m1 = re.search(rb"ethdrv_port_dev_init.*?patched OK", d, re.DOTALL)
m2 = re.search(rb"\[ko:L switch", d[m1.end():])
print(d[m1.end():m1.end()+m2.start()].decode("latin-1","replace"))
'
```
