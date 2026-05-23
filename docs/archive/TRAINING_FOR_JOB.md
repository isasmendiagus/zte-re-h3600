# Training for Job — ARM ROP exploit walkthrough on a GPL'd home router

> **Sandbox**: ZTE ZXHN H3600 V9.0.20P72 (Digi Spain), ARM Cortex-A9, my own device. Source code requested formally to ZTE/Digi under GPL terms; this exercise is purely educational while waiting for sources.
>
> **Goal**: learn how a complete stack-overflow → ROP → privilege-escalation chain looks on real ARM 32-bit hardware. Skills demonstrated map directly to junior pentest / firmware-security roles.

---

> 🌤️ **Weather snapshot — Tres Cantos, 5 May 2026 (cabecera)**: 11.6 °C (feels 9.9 °C), overcast (WMO code 3, 81% cloud cover), humidity 64%, wind 3.3 km/h from south. Daily range 8.6–18 °C, light precipitation 0.30 mm. Tomorrow forecast: 5–19.2 °C, clear skies (WMO code 2). Source: Open-Meteo API (`api.open-meteo.com`).

---

## 0. The exercise

A stripped-down version of the question this walkthrough answers:

> *Given an ARM 32-bit binary with a hypothetical buffer overflow in a function that calls `decode_base64(stack_buf, user_input)` without a length cap, design an end-to-end ROP chain that calls a privileged auth-mutation function inside the same binary to set the admin password to a value of our choice.*

This is the minimum-viable shape of a real CVE on consumer routers. It exercises:

- **Static binary RE** (objdump, nm, readelf, strings)
- **Mitigation analysis** (PIE / NX / stack canaries / ASLR)
- **ARM calling convention + epilogue analysis**
- **ROP gadget hunting** in non-PIE ELF
- **Two-stage payload design** when single-stage primitives are insufficient
- **Reasoning about randomisation surfaces** (what's fixed, what isn't)

---

## 1. Recon — characterising the target

### 1.1 Identification

```
$ file httpd
httpd: ELF 32-bit LSB executable, ARM, EABI5 version 1 (SYSV),
       dynamically linked, interpreter /lib/ld-uClibc.so.0, not stripped

$ readelf -h httpd | grep -E 'Type|Class|Entry'
  Class:                             ELF32
  Type:                              EXEC (Executable file)         ← non-PIE
  Entry point address:               0x1bbd0
```

Key observation: `Type: EXEC` (not `DYN`) means this is **not a Position-Independent Executable**. The kernel cannot apply ASLR to the binary's own load base. Every address inside the `.text` and `.data` of `httpd` is fixed at link time and will be identical across:

- every reboot of the device
- every device running the same firmware version
- every process invocation

This is the single biggest gift the binary gives us. ASLR can still randomise the *stack*, the *heap*, and *shared library* load bases, but the binary's own code and globals are pinned.

### 1.2 Mitigation profile

Manual checklist (in absence of `checksec` for ARM):

| Mitigation | Status | Reason |
|---|---|---|
| PIE | **NO** | `Type: EXEC` |
| NX (non-exec stack) | **YES** | `GNU_STACK` segment lacks `RWE` |
| Stack canaries (SSP) | **NO** | `__stack_chk_fail` symbol absent |
| Fortify (`_chk` variants) | **NO** | no `*_chk@` PLT entries |
| Stripped | **NO** | 16,059 symbols intact |

Reading: hugely favourable. No canary means a stack overflow translates 1-for-1 into saved-LR overwrite. NX means we cannot drop shellcode on the stack — but we don't need to, ROP gives us code reuse against the binary's own `.text`. Symbols intact means we can name our gadgets after the source-level functions they belong to, which makes the chain auditable.

### 1.3 Useful primitive functions

`nm` plus a grep on names lets us shortlist functions worth ROP'ing into:

| Primitive | Address | Signature (inferred) | Why useful |
|---|---|---|---|
| `SetUserInfo` | `0x000368ec` | `(r0=id, r1=&struct)` | calls `CmDevSetAuthInfo@plt` → mutates the auth DB row, **no role check on the C side** |
| `httpd_write_fully` | `0x000472a0` | `(r0=fd, r1=buf, r2=len)` | sends arbitrary bytes back to the requesting socket |
| `send_response` | `0x000445f8` | `(r0=ctx, r1=msg, r2=?, r3=body)` | well-formed HTTP response with headers |
| `memcpy@plt` | `0x000191e4` | `(r0=dst, r1=src, r2=len)` | copies arbitrary memory ranges |
| `system@plt` | (PLT) | `(r0=cmdstr)` | one-shot RCE if we can plant a string at a known address |

Crucially, **`SetUserInfo` performs zero per-request role validation**. The role check that prevents a `user`-level browser session from changing the admin password lives entirely in Lua-side dispatch (`Page:__checkRightPassed`). If we get the C side to call `SetUserInfo` directly via ROP, we bypass the Lua gate entirely.

### 1.4 ROP gadget inventory

Disassembled the whole binary once and grepped epilogue patterns:

```
$ grep -oE 'pop\s+\{[^}]+pc\}' httpd.dis | sort | uniq -c | sort -rn | head
    692 pop {fp, pc}
    640 pop {r4, r5, fp, pc}
    308 pop {r4, r5, r6, r7, r8, fp, pc}
    297 pop {r4, r5, r6, fp, pc}
    269 pop {r4, r5, r6, r7, r8, r9, sl, fp, pc}
    236 pop {r4, r5, r6, r7, r8, r9, fp, pc}
    ...
     36 pop {r3, r4, r5, r6, r7, r8, fp, pc}        ← sets r3 (function pointer)
```

Two gadgets carry the chain:

| Address | Instructions | Purpose |
|---|---|---|
| `0x0001bed8` | `pop {r3, r4, r5, r6, r7, r8, fp, pc}` | popping `r3` from controlled stack lets us seed any function pointer; r4 will become first arg, r6 second arg |
| `0x000462e0` | `mov r0, r4 ; mov r1, r6 ; blx r3` | the call thunk: invoke `r3` with `r0 = r4` and `r1 = r6` |

`0x1bed8` lives at the tail of `PluginSectionInit` — a textbook example of how compiler-generated function epilogues become reusable gadgets in non-PIE binaries.

The combination gives us a clean *"pop-funcptr-and-two-args, then call"* primitive in two stack-bounces.

---

## 2. The hypothetical sink

```c
// hypothetical patch into the GPL'd source — what we're "planting" to study the chain
void handle_request(const char *user_input)
{
    char stack_buf[512];                      // resides at fp - 540
    decode_base64(stack_buf, user_input);     // 2 args, no max_len
    /* … */
}
```

ARM prologue/epilogue for such a function will compile to roughly:

```
push  {r4, r5, r6, fp, l