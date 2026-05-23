# dtr-mod — FTDI cable hardware-mod tooling

**One-time hardware setup**, not part of any iter cycle. Read this only
if you're building a new cable or your existing one stopped resetting
the device.

## What the mod does

We rewired one of the FT232R USB-UART cable's pins to a small relay
that controls **device power**. That lets scripts toggle device power
purely via software (no physical hand on the power button).

The DTR-pin wiring is documented in the hardware build (not in this repo).
The runtime semantics are:

- `DTR = True`  → relay opens  → device **OFF**
- `DTR = False` → relay closes → device **ON**

`zxic/lib/uart.py::reset()` does `DTR-True → sleep 2s → DTR-False` to
power-cycle. All the `auto_*` commands in `uart.py` use this.

## Why the FTDI EEPROM mod is needed

FT232R chips can be configured to **invert the DTR output**. We flip
that bit because of how our relay is wired — without inverting, DTR's
default logic level holds the device perpetually off.

## Files

### One-time EEPROM patch (run once per new cable)

| File | Role |
|---|---|
| `ft232_invert_dtr.py` | Flip the invert-DTR EEPROM bit on the FT232R chip (preserves all other EEPROM bytes). Hand-crafts the checksum so libftdi's lossy rebuild doesn't corrupt strings. |
| `ft232_invert_dtr_v2.py` | Alternate implementation; keep both until one proves more reliable. |
| `ft232_backup.bin` | Pre-mod EEPROM contents (revert with `ftdi_eeprom --flash-eeprom ftdi_backup.conf`). |
| `ft232_new.bin` | Post-mod EEPROM contents (reference). |
| `ftdi_backup.conf` | libftdi config file for the pre-mod state. |
| `ftdi_invert.conf` | libftdi config file for the post-mod state. |

### Runtime helpers

| File | Role |
|---|---|
| `dtr.py` | Toggle DTR programmatically (used during debugging when `uart.py reset` isn't appropriate). |
| `dtr-hold.service` | Systemd unit that holds DTR in the "device ON" state at boot — so the device stays on whenever the host is up. Install with `sudo cp dtr-hold.service /etc/systemd/system/ && sudo systemctl enable --now dtr-hold`. |
| `bb.py`, `bb_dtr_toggle.py` | Bit-bang variants of the DTR toggle (alternate strategies if the standard DTR signal doesn't reach the relay). |
| `ten.py`, `tx_tristate.py` | TX-line tri-state experiments — used during early diagnosis of why the cable behaved oddly; keep for posterity. |
| `ztetool.py` | Higher-level wrapper that bundles common operations. |

## When you'd use these

| Scenario | Action |
|---|---|
| New cable, fresh FT232R | Run `ft232_invert_dtr.py` once. Then install `dtr-hold.service`. |
| Existing setup, device suddenly won't power on | Check `systemctl status dtr-hold`; if dead, restart it. |
| Want to manually power-cycle | `python3 dtr.py off; sleep 2; python3 dtr.py on` (or just call `uart.py reset`). |
| Cable EEPROM got corrupted | `ftdi_eeprom --flash-eeprom ftdi_backup.conf` (restores factory state). |

## You DO NOT need these for normal work

If `uart.py auto_*` commands already power-cycle the device for you,
the mod is working and you can ignore this folder. It only matters
when setting up a new cable or diagnosing why the reset stopped working.

## See also

- `tasks/00.03.nand-flash/README.md` "DTR-pin hardware mod" — the runtime
  consumer's view (how it gets used during flash sequences)
- `lib/uart.py::reset()` — the function every `auto_*` script calls
