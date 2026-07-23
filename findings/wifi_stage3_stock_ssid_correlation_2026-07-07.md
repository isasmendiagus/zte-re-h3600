# WiFi Stage-3 Phase A — STOCK-live ssid correlation (2026-07-07, run 2026-07-23)

Device agent, live H3600 (ZX279128S), **running STOCK** (`Linux H3600 V9 4.1.25
armv7l`, NAND boot, uptime ~10 h — the real household router, actively serving
WAN/LAN/WiFi). **Strictly READ-ONLY**: no NAND write, no reflash, no HW/FDB/CLA/PM
programming. The only writes issued were `echo g_tm_debug_level=N > /proc/tm/shell`
(a debug-verbosity knob, reset to 1 afterward) and reading diag sysfs nodes; no
forwarding state was mutated. Transport = **SSH** (`admin`, paramiko
`invoke_shell`), dumps captured to on-device files / `/dev/logger_main` and read
back — per the transport rule (UART clips; SSH+file is clean).

**Data provenance = FRESH run on the still-running stock instance.** The prior
attempt's `scratchpad/stockdumps/` directory existed but was **empty** (0 files) —
nothing salvageable had been persisted. Stock was still up from the prior boot,
so I connected to that same live instance and took fresh dumps (no reboot).

---

## The subject: a REAL WiFi client stock already learned (no client of ours needed)

Stock (the live router) already had a household WiFi client on its fabric, so no
association by us was required (and the changed adb phone / its new WiFi MAC is
irrelevant here):

- **Client MAC `fa:f4:9f:69:7e:e5`** (locally-administered / randomized — a phone
  or laptop using MAC privacy), **IP `192.168.1.128`**, bridged on `br0`
  (`ip neigh`: `192.168.1.128 dev br0 lladdr fa:f4:9f:69:7e:e5`). It is **not** any
  of stock's AP-interface MACs (`wlan0-4` = `f?:f6:47:?f:42:64`, `wlan5g0-4` =
  `f?:f6:47:?f:42:65`), i.e. it is a genuine STA, not an internal vif.
- The device's stock radios expose SSIDs `DIGIFIBRA-fYtX`, `DIGIFIBRA-PLUS-fYtX`,
  `Netsphere5G_…`, `RADIO1.BSS1`, etc. (5 BSS per radio: `wpa-ap0x` + `wpa-ap1x`).
  No PSK was read/typed/logged.

Second reference client for contrast: our SSH host NIC `c8:a3:62:e9:59:00`
(`192.168.1.50`), wired on port 2.

---

## RAW DUMP 1 — FDB (ppBrg `macTable` = SBRAG / FDB-B), 3 reads

`cat /sys/devices/platform/tm/ppBrg/macTable` (output → `/dev/logger_main`; captured
with `g_tm_debug_level=1` to avoid the `smac_get_statistics` poller flood):

```
num  ramid addr mac                vlan portmask status smac_ctrl dmac_ctrl ssid
1    0     b8   fa:f4:9f:69:7e:e5  0    0x80     10/5/3 0         0         0
2    0     f9   c8:a3:62:e9:59:0   0    0x4      14     0         0         0
```

- Entry 1 = the WiFi client, `portmask 0x80` (**bit 7 = fabric port 7 = WLAN idm
  ring 1**). `status` varied 10→5→3 across the three reads = the aging counter
  ticking (0001-1110 = valid). **`ssid` column = 0.**
- Entry 2 = our wired SSH host, `portmask 0x4` (bit 2 = regport2 = logical port 1).
  `ssid` = 0.

**The `ssid` column is a hardcoded literal `0`, not decoded from the entry.**
Verified in decomp `sbrg_print_mactable` (`decomp_all_tm.c:8534`): the print reads
regs 0x4c/0x4d/0x4e (`sbragRegTable`) and its **last `printf` argument (the `ssid`
column) is the constant `0`** — the code never reads an ssid subfield. The reg-0x4e
word (`local_2c[0]`) is consumed only as: `[3:0]`=vlan-hi, `[7:4]`=status,
`[8]`=smac_ctrl, `[9]`=dmac_ctrl. **Bits [31:10] are never read.**

## RAW DUMP 2 — CLA hardfast flows + PM next-hop (the decisive data)

`cat ppCla/{gfastentrynum,showfastinfoall,showfastrule}` +
`cat ppCla/{desIn,desOut}` (with `g_tm_debug_level=7` so the shared entry-decoder
`cla_set_hash_table` / `cla_info_show` prints; the household's live NAT traffic
also re-triggered installs, giving the same stored entries from two angles).

`showfastinfoall`: `v4_up:3, v4_dn:3, v6_up:0, v6_dn:0` → **fast entry total 6**.

**WiFi-client entries** (next-hop resolves to the client MAC/IP):
```
pp_pm_set_next_hop_ram_info: next_hop_idx 165 → next_mac fa:f4:9f:69:7e:e5, next_dip 192.168.1.128
pp_pm_get_next_hop_ram_info: next_hop_idx 167 → next_mac fa:f4:9f:69:7e:e5, next_dip 192.168.1.128
pp_pm_set_flow_info: dir=1 (downstream), flow_ram_addr 1136, next_hop_idx 165, subnet_id 0

cla_set_hash_table (stored CLA hardfast entry, cmd_flow_id 1136/1137/1138/1139/1140):
   inport = 0, OUTPORT = 0, flow_pri = 0, wan_id = 0
   da_known = 1, valid_en = 1, direct = 1, rule_mode = 0
   e8_en = 0, cmd_flow_id = 113x, tcnt_gpid_rp_en = 1, GEMPORT_UNI_ID = 28
```

**Wired/other-client entries** for contrast (`cmd_flow_id 1149/1150`, `subnet_id 1`,
`next_hop_idx 164`):
```
   inport = 0, OUTPORT = 0, da_known = 0, direct = 0, GEMPORT_UNI_ID = 5
```

Field distribution over all 13 captured install/read-back records:
`outport` = **0 in every single one**; `gemport_uni_id` ∈ {**28** (WiFi client, ×8),
**5** (wired, ×5)}.

`gemport_uni_id` decode from the same decoder: `param_2[2]<<4 | param_2[1]>>4`
(a 12-bit stored field of the CLA entry) — a real stored value, = **28 = 0x1c**.

## RAW DUMP 3 — live pipeline descriptor (desOut) — non-decisive snapshot

`cat ppCla/desOut` while pinging the client caught only idle/CPU traffic:
`ssid_in:0, ssid_out:0, Outport:0`. The client was `STALE` in the neigh table and
the ping did not coincide with the capture microsecond, so this is **not** a
WiFi-flow descriptor and neither confirms nor refutes anything. Not relied upon.

---

## The ssid encoding — SOLVED

`28 = 0x1c` is in the range `[0x10, 0x1f]`, which decomp proves is exactly the
**WLAN logical-port / essid** space:

- `aclEssidToWlanIDMMap` (`decomp_all_tm.c:50083+`) validates its essid arg with
  `if (0xf < param_1 - 0x10) → "Essid invalid"`, i.e. **essid ∈ [0x10, 0x1f]**, and
  maps it via `s_aclWlanToIdmEssidMap` (16 slots × 0x12 B; `[0]`=idm_port ∈ {6,7},
  `[1]`=essid) to (idm_port, index).
- `get_sw_port_from_devname` (spec §4/§5): logical WLAN port = **`0x10 + ssid` for
  idm0/port6, `0x18 + ssid` for idm1/port7** → `essid = 0x10 | (ring<<3) | ssid`.

Therefore **`gemport_uni_id = 28 = 0x1c = 0x10 | (1<<3) | 4` → idm ring 1 (fabric
port 7), SSID index 4.** This is fully consistent with the FDB entry for the same
MAC showing `portmask 0x80` (port 7 = idm1). The FDB says "port 7"; the CLA flow's
`gemport_uni_id` refines it to (port 7, ssid 4).

**This is the mechanism stock uses to carry the WiFi (ring, ssid) egress through a
HW-offloaded flow: it is stored in the CLA entry's `gemport_uni_id` field (as the
essid value 0x10-0x1f), NOT in `outport` (which stays 0).**

---

## Verdicts on Q1 / Q2 / Q3

### Q1 — does stock's HW FDB learn write the client's `ssid` into an FDB entry (reg-0x4e bits[31:10])?
**REFUTED (for the FDB path), with numbers.** The FDB entry for the WiFi client
carries **only `portmask = 0x80` (port 7)** and **no ssid** — the `macTable` dump's
`ssid` column is a hardcoded literal `0` (`sbrg_print_mactable` never reads an ssid
subfield; reg-0x4e bits[31:10] are untouched by software). Confirmed live: same MAC,
three reads, `ssid`=0 every time while `status` aged. The FDB physically distinguishes
only "port 6" vs "port 7", exactly as spec §2 predicted. **ssid is NOT an FDB field.**
(Caveat: this is the SBRAG/FDB-B table that stock actually learns into — the wired
host MAC also lives here, proving it is the live learning table. The separate
PP_BRG_RAM/FDB-A auto-learn table has no stock sysfs dump; but since the ssid is
carried in the CLA flow (below), the FDB-A[31:10] hypothesis is moot for the
offload path.)

### Q2 — where does `ssid_out` come from on a DA/FDB hit?
**ANSWERED for the offloaded case: it comes from the CLA flow's stored
`gemport_uni_id` (essid 0x10-0x1f), decoded by HW into (idm ring, ssid).** On a
hardfast-flow hit, the client's entry has `da_known=1, direct=1, gemport_uni_id=28`
→ HW forwards direct to idm1/ssid4. The FDB DA lookup alone gives only "port 7";
the ssid resolution rides the CLA flow entry, not the FDB. This rules out spec §2's
"outport-encoded" reading and refines hypothesis: **ssid_out ← gemport_uni_id, not
VLAN, not outport, not FDB spare bits.** (Whether a *non-offloaded* plain-L2 WiFi DA
hit — no CLA flow — resolves ssid at all was not observable: every WiFi-client frame
on this live router already had a hardfast flow. Consistent with spec §2 hyp (3):
non-flow traffic's ssid is a SW/idmfdb concern.)

### Q3 — does stock's CLA store a WiFi flow with `outport = 0x10-0x1f`?
**REFUTED as stated; the SAME logical value lives in a DIFFERENT field.** Stock DOES
build WiFi hardfast flows (5 stored entries for the WiFi client, `da_known=1
direct=1`), but their **`outport = 0`** — the `0x10-0x1f` WLAN logical-port value is
stored in **`gemport_uni_id` (= 28 = 0x1c)** instead. Spec §4's hypothesis was right
about the *value* (0x10+... in [0x10,0x1f]) and the *reuse of the essid numbering*,
but **wrong about the field** — it is not `outport`. Programming a live CLA
`outport=0x10+ssid` (which spec §4 explicitly warned to bench-check first) would be
**incorrect**; the correct field is `gemport_uni_id`, with `outport` left 0.

### Bonus (two SSIDs / two clients)
Only one WiFi client was present (idm1/ssid4). The second flow set (`gemport_uni_id=5`)
is a **wired** client (uni 5, `da_known=0`, not in the WLAN range), so a two-SSID
mapping could not be pinned this session. But the (idm_port, essid) map shape is
triple-confirmed in decomp, so the full table is `essid = 0x10 | (ring<<3) | ssid`,
ring ∈ {port6→0, port7→1}, ssid 0-7.

---

## What it means for Stage-3 design

1. **The WiFi egress descriptor field to write is `gemport_uni_id`, set to
   `0x10 | (idm_ring<<3) | ssid` (0x10-0x1f), with `outport = 0`.** This supersedes
   the feasibility-scout and spec §4 "outport = 0x10+ssid" assumption. When mainline
   eventually builds a WiFi-destined hardfast flow (CLA/PM), it must pack
   `gemport_uni_id` (CLA entry bytes 1-2: `param_2[2]<<4 | param_2[1]>>4`), not
   `outport`.
2. **Do not add an ssid field to the FDB** — confirmed live there is none (matches
   spec §2). The FDB only ever needs `port 6`/`port 7` for a WiFi client MAC; ssid
   disambiguation is the flow entry's / SW dispatcher's job.
3. The flow-vs-FDB split is real on stock: WiFi client traffic is **flow-offloaded**
   (`da_known=1, direct=1`), which is what carries the ssid. Mainline's additive IDM
   RX/TX ssid decode (spec §1, already landed) plus a `(idm,ssid)→wlan netdev`
   dispatcher (mirroring idmfdb `fdb_list[16]`) remains the SW-forwarding baseline;
   the HW-offload upgrade now has a concrete, live-verified field to target.

---

## Reproduce / raw files
- SSH shell: `lib/ssh_shell.py` (admin, invoke_shell). SFTP: `scratchpad/stock_fetch.py`.
- Diag driver pattern: `scratchpad/stock_diag.py` (sets `g_tm_debug_level`, captures
  `/dev/logger_main`, greps). Sysfs used: `ppBrg/macTable`,
  `ppCla/{gfastentrynum,showfastinfoall,showfastrule,desIn,desOut}`.
- Raw captures (this session): `scratchpad/stockdumps/macTable_log2.txt`,
  `cla_fastrules_log.txt`, `cla_desc_log.txt`; clean extracts
  `macTable_clean.txt`, `wifi_client_flows_clean.txt`.
- Noise note: `smac_get_statistics` floods `/dev/logger_main` only at
  `g_tm_debug_level=7`; for macTable use level 1 (it prints regardless); for CLA
  getters level 7 is required — grep out the poller.

## Final device state
Left **on stock** (as required). `g_tm_debug_level` reset to 1; `/tmp/*.bin` capture
files removed. No reboot, no reflash, no forwarding-state change. WAN/PPPoE
untouched.
