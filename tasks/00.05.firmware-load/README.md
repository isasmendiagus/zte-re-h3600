# firmware-load — methods catalog: how to get code onto the device

**ID**: 00.05
**Parent**: [00 openwrt-port](../00.openwrt-port/)
**Children**: [00.05.01 rop-no-uart](../00.05.01.rop-no-uart/)
**TaskList items**: none directly (per-method children own their tasks)
**Status**: REFERENCE — catalog of access methods we've explored.

## What this folder is

Bootstrap question: "I have a ZTE H3600 in front of me. How do I get
my code running on it?" Different units, different conditions, different
methods apply.

This folder catalogs the methods. The actual scripts/exploits live in
the per-method child folders.

## Methods comparison

| Method | Needs UART cable? | Needs known SSH creds? | Status | Where |
|---|---|---|---|---|
| **U-Boot + UART + TFTP** (our daily iter loop) | yes (with DTR mod) | no | ✅ in daily use | `lib/uart.py` + flash scripts in `tasks/00.01.eth-driver/scripts/` + `tasks/00.02.stock-shell/`; full NAND-side recipes in `tasks/00.03.nand-flash/README.md` |
| **ROP via httpd `rsaDecryptWithoutKeyFile` bug** | NO | no (pre-auth RCE) | ✅ working exploit | `tasks/00.05.01.rop-no-uart/` |
| **Web upload via Haikui_V2 universal creds** | NO | yes (`admin / Haikui_V2`) | 📋 documented in memory, never tried | (none yet; would be `tasks/00.05.02.web-upload-haikui/`) |
| **Stock-firmware GPL release** | N/A | N/A | ❌ never released for H3600/ZX279128S | (impossible — see memory `gpl_legitimacy_context`) |

## Decision tree — which method should I use?

```
Do you have the FTDI cable with DTR-mod?
├── YES → U-Boot + UART + TFTP (default, the daily loop)
└── NO
    Do you have admin/Haikui_V2 working on this unit?
    ├── YES → web upload via Haikui_V2  (untested; would need 00.05.02)
    └── NO  → ROP exploit (00.05.01) — pre-auth, just needs HTTP reachability
```

## When you'd actually need this

- **Bringing up a fresh factory unit** before you've built/connected the cable
- **Helping a remote contributor** who only has network access to their device
- **Security research / disclosure** (we own this hardware; see `docs/EXTERNAL_RESEARCH.md`)
- **Recovery scenarios** where UART is unavailable for some reason

For our actual day-to-day driver work, you'll always be on the U-Boot+UART path.

## See also

- Memory `digi_h3600_universal_creds` — factory-default credentials + ACS URL
- Memory `gpl_legitimacy_context` — why this RE/exploit work on owned hardware is legitimate
- `docs/EXTERNAL_RESEARCH.md` — orca.pet writeup (the original SSH-bootstrap method)
- `tasks/00.03.nand-flash/README.md` — what to DO with the access once you have it (flash recipes, slot management)
