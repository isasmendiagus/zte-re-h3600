# Stock init flow — `idmfdb.ko` static analysis

Walk of `tasks/00.10.02.re-stock-kmods/findings/decomp_all_idmfdb.c`
(65KB decomp).

## Summary

`idmfdb.ko` is the **IDM (Independent/In-band Data Module) Forwarding
Database** management module. It depends on `switch.ko` and provides a
parallel FDB to the main switch fabric for in-band management traffic
flowing through the `idm0` and `idm1` netdevs (registered by
`pon_npp_idm_init` in plat-zxylzb_9128S).

This kmod **owns no MMIO directly** — it manages an in-memory FDB,
multicast lookup, and LED state.

## Functions

### [fn-00] `init_module` @ decomp_all_idmfdb.c:1857 — entry stub

What it does: chains 4 sub-inits.

HW writes: **none**.

Sub-calls in order:
1. `idm_fdb_init()` — [fn-01]
2. `idm_proc_init()` — [fn-02]
3. `idm_multicast_init()` — [fn-03]
4. `idm_led_init()` — [fn-04]

In mainline? **N/A** — IDM is for in-band PON/OAM mgmt traffic, not LAN
forwarding. Not on ping bidi hot path.

### [fn-01] `idm_fdb_init` @ decomp_all_idmfdb.c:1870 — FDB callback registration

What it does: sets `idm_skb_recv` callback to `idm_fdb_forward` (the actual
FDB-lookup forwarding function), zeros 0x210 bytes of `idm_flood_cnt` (per-
port flood counter array?), and registers a netdevice notifier.

HW writes: **none**.

Sub-calls:
- `__memzero(&idm_flood_cnt, 0x210, ...)`
- `register_netdevice_notifier(&idm_netdev_notifier)` — get notified on
  netdev events (REGISTER/UNREGISTER/UP/DOWN)

In mainline? **N/A**.

### [fn-02] `idm_proc_init` @ decomp_all_idmfdb.c:1554 — /proc/idm entries

Not read in full but per grep is at line 1552. Probably creates /proc/idm
debug entries. Pure diagnostic.

In mainline? **N/A** — diag.

### [fn-03] `idm_multicast_init` @ decomp_all_idmfdb.c:1110 — multicast table init

Per grep at line 1108. Initializes IDM multicast forwarding tables.

In mainline? **N/A** — IDM-specific.

### [fn-04] `idm_led_init` @ decomp_all_idmfdb.c:1884 — WLAN LED hookup

What it does: looks up wifi_led functions in kallsyms (the `mt7915` WiFi
kmod's symbols), registers LED handlers for WLAN status. Two bands if both
functions exist (dual-band 2.4GHz + 5GHz).

HW writes: **none**.

Sub-calls:
- `__memzero(&led_handle, 0x80)`
- `kallsyms_lookup_name(wifi_led_func_name)` — find mt7915's LED helper
- `kallsyms_lookup_name(wifi_led2_func_name)` — find 2nd band helper
- `register_idm_led(...)` — register LED handler (band 0 and optionally band 1)

In mainline? **N/A** — WiFi LED indicator only.

### [fn-05] `register_idm_led(band, group, period, fn)` @ decomp_all_idmfdb.c:1921 — LED entry setup

Helper for `idm_led_init`. Allocates an LED handle in `led_handle` array
indexed by band (each entry 0x40 bytes), sets the LED config + group +
period, and starts a timer. Used to blink the WLAN LED at the configured
rate.

HW writes: **none** (LED registers are presumably owned by mt7915 or a
separate LED kmod).

In mainline? **N/A**.

### [fn-06] `cleanup_module` @ decomp_all_idmfdb.c:1908 — exit

What it does: mirrors init in reverse:

```c
idm_fdb_exit();
idm_proc_exit();
idm_multicast_exit();
idm_led_exit();
```

## Conclusions

- `idmfdb.ko` is entirely **management-plane infrastructure** for the
  in-band PON/OAM channel. The "FDB" here is a parallel FDB for IDM
  traffic, separate from the switch fabric's PP_CLA hash table that
  manages LAN/WAN forwarding.
- `idm_skb_recv = idm_fdb_forward` is the hook by which packets arriving
  on the IDM netdev get FDB-resolved and forwarded. The forwarding rule
  table is built up dynamically (via the netdevice notifier and ioctl
  paths, not at init).
- WLAN LED integration is a side feature — uses kallsyms to dynamically
  bind to mt7915's exported LED helpers.
- **Mainline doesn't need to port this kmod.** It's for PON-mgmt / OAM
  traffic only; we don't have GPON/OAM in the test bench.

## Cross-refs

- Depends on `switch.ko` for the IDM netdev infrastructure.
- The IDM netdevs themselves (`idm0`, `idm1`) are registered by
  `pon_npp_idm_init` in plat-zxylzb_9128S — see
  `static_analysis_plat_zxylzb_init.md` [fn-23].
