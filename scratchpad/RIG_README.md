# scratchpad/rig.py — canonical mainline test rig

**Use this instead of re-deriving the rig setup from memory/findings.**
It consolidates the already-proven scripts in this directory into one
entry point with clear subcommands. It invents no new procedure — every
subcommand's commands are lifted verbatim (or with only the source-of-truth
IPs pulled to constants) from the script named in its "source:" comment.

```
rig.py boot [--long]                          # DTR-boot mainline, wait for REPL
rig.py wan                                     # device: lan4 WAN + NAT + verify modem ping
rig.py client                                  # host: netns client on lan2 (anti-wifi-leak)
rig.py offload                                 # device: nft flowtable {lan2,lan4} flags offload
rig.py download [--url U] [--dur S] [--lport P] [--counters]
rig.py counters                                # one-shot decoded pipeline-counter dump
rig.py teardown [--skip-device]                # netns_down (mandatory) + device nft flush
rig.py up [--long]                             # boot + wan + client + offload
rig.py status                                  # device alive? modem 0% loss? wedged? host route ok?
```

Typical session:

```
python3 scratchpad/rig.py up                   # full rig ready (boot+wan+client+offload)
python3 scratchpad/rig.py download --counters   # measure + watch the pipeline counters
...  # your actual test work here (a device agent's real task) ...
python3 scratchpad/rig.py teardown              # MANDATORY before any reboot
```

If the WAN modem is dead (0% ping fails repeatedly): `rig.py boot --long` does a
10s DTR-off power-cycle, which also power-cycles the upstream DIGI modem and
usually revives it (a normal/short boot does not).

## Topology this assumes (2026-07 cabling)

Host NIC `enxc8a362e95900` is **time-shared** between two roles:

| Role | netns | IP | Used by |
|---|---|---|---|
| mgmt/boot | root | 192.168.1.50/24 | TFTP boot, reaching device mgmt IP 192.168.1.1 |
| client | `client` | 172.31.9.50/24 on device lan2 | `download`, simulates a downstream LAN device |

`rig.py client` moves the NIC mgmt→client; `rig.py teardown` (and the start
of `rig.py boot`) moves it back client→mgmt. **Never TFTP-boot while the NIC
is in the client netns** — U-Boot's TFTP needs 192.168.1.50 in the root ns.

Device ports: lan1 = mgmt (rc.router leaves an IP here — **wrong port**, `wan`
flushes it), lan2 = client-facing (gw 172.31.9.1), lan4 = WAN via the DIGI
modem (10.44.66.223/24, gw 10.44.66.250).

## Safety baked into the tool (do not bypass)

- DTR/RAM-boot only — never NAND-flash, never trigger a stock rewrite.
- Never memdump/raw-poke the MAC4 stat region (phys `0x92300000`+, i.e.
  `npp_base + (4+1)*0x40000`). A prior agent hard-hung the device doing this.
  MAC4 counters are only read via `pipeline_stats` (see `rig.py counters`).
- `TM[0x10058]`/`TM[0x10068]` (UP/DN TX consumed-count) are clear-on-read and,
  since build #490 (txflowctrl fix), are owned exclusively by the driver's
  `zx_sw_tx_reclaim_locked()`. This tool **never** raw-pokes them — stealing
  a reclaim event this way can reintroduce the TX-ring-overrun wedge.
  `counters`/`download --counters` read the safe equivalent
  (`sw_tx_pending`/`sw_tx_reclaimed`/`sw_tx_full_drops`) from
  `/sys/kernel/debug/zx_eth/pipeline_stats` instead.
- Several fpga-indirect debug counters (`sw_alcecnt`/`*_erlscnt`/`bmu_bperr`,
  `qmg_fifo_err`, `red_reg_up_dbg`, `smct`...) read back constant garbage via
  a raw `poke` (need the stock latch protocol, not wired on mainline) — this
  tool doesn't expose them; don't trust ad-hoc reads of them either.
- sudo is never persisted — every host-side privileged command goes through
  `echo <pw> | sudo -S ...` inline, one shot at a time (see `rig.py`'s
  `SUDO` constant).
- The sudo password itself is NOT in git: `rig.py`, `netns_up.sh` and
  `netns_down.sh` read it from `$ZTE_SUDO_PW` or the git-ignored one-line
  file `scratchpad/.sudo_pw` (chmod 600). On a fresh checkout, recreate
  `.sudo_pw` before using the rig.

## Where each subcommand's commands came from

| Subcommand | Source script(s) | Status |
|---|---|---|
| `boot` | `reboot_mainline.py`, `reboot_mainline_longdtr.py`, `netns_down.sh` (pre-restore) | **Assembled from proven scripts**, invoked as subprocesses unmodified. The 27s post-boot settle wait and the REPL-alive re-check after it are new glue — confirm the wait is long enough on first live run. |
| `wan` | prior `scratchpad/rig.py`'s `SETUP`/`CHECK` command lists | Commands themselves are proven (this is literally the old rig.py content). The `ping 10.44.66.250` pass/fail parse is new glue — confirm the "0% packet loss" regex matches the device's busybox ping output verbatim on first run. |
| `client` | `netns_up.sh`, called as-is | Proven as-is. The "default route confirmed" check parses netns_up.sh's own printed output — confirm the grep still matches if that script's echo format ever changes. |
| `offload` | prior `scratchpad/rig.py`'s `NFT` list | Proven as-is (unchanged nft commands). |
| `download` | `dl_run.py` (bytes/rate/http + before/after delta), `dn_e2e_native.py`/`wedge_run.py` (the `--counters` time-series variant) | Command shapes proven; the **merge** of "simple mode" and "counters mode" into one flag-gated function is new glue — needs a first live run to confirm the background-sampler thread doesn't perturb the plain (non-counters) path and that `--size` (Range-capped download, not used by any source script — they all use `--max-time` only) actually works against the test server. |
| `counters` | `scratchpad/ctr.py` (full sweep), `validate_fix.py` (desOut decode), driver's `pipeline_stats` (TX/RX-safe fields) | Proven reads; this is a straight assembly of three already-working read paths into one dump. |
| `teardown` | `netns_down.sh`, called as-is; device `nft flush ruleset` | `netns_down.sh` part proven as-is. The device-side nft flush is new glue (harmless — a fresh boot wipes it anyway) — low risk, not verified live. |
| `up` | composition of `boot`+`wan`+`client`+`offload` | New glue (simple sequential call + abort-on-failure) — needs one first live run end-to-end. |
| `status` | `ctr.py`/poke idiom, `netns_up.sh`/`netns_down.sh` output shape, redwedge memory note (qmg_dn_trap≈1024 heuristic) | Read-only, safe by construction. The "likely WEDGED" heuristic is informative only, not a diagnosis — cross-check with `wedge_deep.py`/`wedge_run.py` before concluding a wedge. |

**Bottom line for the next device agent:** everything above is expected to
work, but this file has only been syntax-checked and self-reviewed
(`python -m py_compile`, plus manual command-by-command diffing against the
source scripts) — it has **not** been run against the live device. Run
`rig.py up` first and watch the output; if any step's parse/regex doesn't
match reality, the fix is almost always in the `[FAIL]`/`[WARN]` print right
above it, not in the underlying command (which is copied from a script that
already worked).

## What's deliberately NOT in here

Deep, single-purpose diagnostics (wedge root-cause hunts, CLA RAM diffing,
PM-slot bisection, egress descriptor poking, etc.) stay as their own
scripts (`wedge_deep.py`, `stock_entry_test.py`, `dn_denat_poke.py`, `vbisect.py`,
...). `rig.py` only owns the **repeated setup/teardown/measure** steps every
session needs; once the rig is `up`, reach for the specific diagnostic script
for anything beyond a basic throughput+counters download.

## Regression battery

For "did my driver change regress anything", don't hand-run the QA scenarios
again — `scratchpad/regress.py` is a companion script that imports this file
and runs the whole proven QA battery (baseline/sustained/multiflow/churn/
bidirectional/edge-cases/counters/dmesg/recovery) as scripted PASS/FAIL tests
with a summary table and a nonzero exit on any FAIL:

```
python3 scratchpad/regress.py            # full battery
python3 scratchpad/regress.py --quick    # fast subset for iteration
```

See `scratchpad/REGRESS_README.md` for the full test list, pass criteria, and
which thresholds still need first-run tuning.
