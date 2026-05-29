# Stock /sys/devices/platform/tm debug API — full tree

Captured 2026-05-27 via SSH on stock 4.1.25 (factory NAND boot). The platform
device exposes a rich set of write-only/read-only entries under
`/sys/devices/platform/tm/<subsystem>/<entry>`. Stock developers use these
for runtime debugging; we mirror them as a target API set for our mainline
driver's debugfs.

## Why this is useful

Names confirm the kmod internal layout — the same blocks we see referenced
in Ghidra decomp now have **canonical user-facing names**. Use this as a
naming reference when porting more init code.

## File modes

All entries are `0200` (write-only by root) or `0400` (read-only by root).
Writes accept an ASCII port index / argument and emit text via printk
that goes to the UART console only (stripped busybox has no `dmesg`,
and /proc/kmsg is consumed by klogd in factory firmware). So to USE
these on stock: redirect the serial console to a capture (we have the
UART bridge on host:9999) and write to the entry.

## Subdirectories (= kmod sub-modules)

```
/sys/devices/platform/tm/
├── nppGreg/        — NPP global registers (port status, 802.1x auth, PHY LDO)
├── nppPm/          — NPP performance monitor counters
├── nppSdet/        — NPP service detection (likely OAM)
├── nppSpa/         — NPP service-port-aggregation
├── ppAdm/          — PP admin / control plane
├── ppBrg/          — PP bridge (FDB / VLAN logic — 14 init writes we replay)
├── ppCla/          — PP classifier (fast / extra rule tables, ACL, FDB hashtable)
├── ppPm/           — PP performance monitor
├── tmRed/          — TM RED (random early drop) queue mgmt — we have via Phase 9d
└── tmTest/         — TM test/debug entries (per-port stats, queue weights, etc.)
```

## `tmTest/` (TM debug)

```
gportcastratelimit    sportcastratelimit
gportegrssch          sportegrssch          (egress scheduler)
gportegrstfsharp      sportegrstfsharp      (egress traffic shaper sharp)
gportingratelimit     sportingratelimit
gportstatistics1
gportstatistics2
gportstatistics3
gportstatistics4
spqdwrr               (per-queue DWRR weights)
spqshprate            (per-queue shaper rate)
spqweight             (per-queue weight)
stcontshprate
tmdn                  ← TX downstream test
tmup                  ← TX upstream test
tmerrormonitor        ← !!! error monitor — likely the diagnostic we want for our wedged TX path
```

**Naming confirms UP/DN ring terminology**: TM has explicit `tmup` and
`tmdn` test entries. Matches our driver's TM_REG_DMA_TX_UP_BASE (0x10050)
vs TM_REG_DMA_TX_DN_BASE (0x10060). The "UP=switch→CPU=RX from CPU view"
and "DN=CPU→switch=TX" interpretation in our findings is consistent.

**`tmerrormonitor` is the most interesting unread entry** — stock has a
built-in TM error monitor. Mainline lacks any TX/RX error counter
visibility. Adding a similar mechanism to our debugfs would help debug
the "HW consumes desc but no wire output" bug we're chasing. The
mechanism may be a separate IRQ line or a polled register block — RE'ing
`tmerrormonitor` write handler in `tm.ko` is a high-value follow-up.

## `nppGreg/` (NPP global / link state)

```
gport802xauth         (per-port 802.1x auth state)
gportstatus           ← per-port link/state status — we'd want this for PHY[3]
helpGreg              (printed help, may list valid args)
phyLdoTest            (PHY LDO test — see gephy_ldo_timer in init flow)
phyGuardEn            (PHY guard band enable)
sport802xauth
sportstatus
```

`phyLdoTest` and `phyGuardEn` confirm GePHY LDO timer is a thing (we already
have `gephy_ldo_timer` in stock RE per `eth_init_flow_2026_05_26.md`).

## `ppCla/` (PP classifier)

```
# Rules / FDB management
addfastrule           setmaxfastentry
delfastrule           setmaxl3entry
modhashtable          
calculatehashaddr     gparsehashkey      (hashing helpers)

# Tables
gclacfg               (CLA config)
gextraindextable
gextraruletable
gfastentrynum         (fast entry count)
ghashtable            (FDB hash table dump)

# Diagnostic / inspection
desIn                 (input descriptor inspect)
desOut                (output descriptor inspect)
flowInfoList
gagingstatus          (entry aging)
reason                (classification reason — e.g. why a frame was dropped)
showaclinfoall        showcommrule         showfastinfoall    showfastrule
statics               (flow statistics)
helpCla               (printed help)
```

**Key finding**: stock has a `reason` entry that explains classification
decisions. This is **exactly what we need** to debug our wedged TX path —
write a desc, then read `reason` to see WHY the switch fabric drops it.
But it printks to UART only on stock; our mainline doesn't replicate this
at all (CLA replay table mode dumps the entries blind).

**fastentry vs l3entry**: ppCla has both a "fast" path table and an "L3"
path table. Stock distinguishes them. Our `zx_cla_apply_replay` writes
both via stock_table.h but doesn't know the semantic split. Worth RE'ing
the difference to understand which table the ARP-reply-egress lookup
uses.

## Action items derived

1. **Port `tmerrormonitor` mechanism to mainline debugfs** — read whatever
   it writes to identify HW-level TX/RX errors. RE the write handler in
   `tm.ko` (we have `decomp_all_tm.c` available).

2. **Port `ppCla/reason` equivalent** — drop-reason exposure when a frame
   doesn't make it through PP classification. RE the entry in
   `decomp_all_plat_zxylzb_9128S.c`.

3. **Confirm fastentry table contents in stock vs our CLA replay table** —
   if stock's `gfastentrynum > 0` after ARP, but ours is 0 (because the
   ARP response was never seen by SW), it's evidence that the bug is
   upstream of CLA (in TM IRQ delivery).

4. **`gportstatistics1..4` map** — four per-port counter blocks. Likely:
   1=RX bytes/packets, 2=TX, 3=drops, 4=errors. Confirm by RE'ing each
   write handler. If we can read these on the live device, comparing
   stock-during-ping with mainline-during-ping pinpoints which counter
   isn't incrementing.

## Constraint

All output goes to UART console. To capture it from automation, redirect
serial via our UART bridge (host:9999) while writing to the entries.
Mainline equivalents should go through `/sys/kernel/debug/zx_eth/` and be
readable directly via SSH.
