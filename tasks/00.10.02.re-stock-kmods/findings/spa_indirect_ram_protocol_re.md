# SPA indirect-RAM access protocol (ZTE ZX279128S / tm.ko) — RE

Decomp-only analysis. Source: `decomp_all_tm.c`, `static_analysis_tm_ko_init.md`.
HW window (given): SPA block phys 0x921d4000 (npp+0x14000); CMD 0x921d4014,
DONE/STATUS 0x921d4018 (poll bit0), DATA 0x921d401c..0x921d4030 (6 words).
Reg-table mapping (`spaRegTable`, via `tmOnuRegWrite/Read(subblk,...)`):
subblk 4 = CMD (0x...4014), subblk 5 = STATUS (0x...4018), subblk 6 = DATA
(0x...401c, stride 1, idx 0..5). Confirmed by `spa_set_indirect_rw_cmd`→reg4,
`spa_get_indirect_rw_status`→reg5, `spa_set/get_indirect_rw_data`→reg6.

---

## 1. CMD bit-layout @ 0x921d4014  (CONFIDENCE: HIGH)
Built in `spa_set_indirect_rw_cmd` (tm:25957):
`val = ram_addr + ram_id*0x400000 + ind_rw_en*0x8000000`
=> **addr   = bits[21:0]**   (mask 0x3FFFFF; validated `<= 0x3FFFFF`, tm:25945)
   **ram_id = bits[26:22]**  (×0x400000; validated `<= 5`, tm:25943)
   **rw/go  = bit[27]**      (×0x8000000; `ind_rw_en`, validated `<= 1`, tm:25947)

`ind_rw_en` semantics (from callers): **1 = READ-prefetch**, **0 = WRITE-commit**
(matchram does cmd(1,..) then re-reads, then cmd(0,..) then writes — tm:26196/26249).
There is NO separate go/enable bit; writing CMD *is* the trigger, completion polled
on STATUS bit0. No READ-vs-WRITE field beyond bit27.

**Decode of leftover stock `0x01400007`:** bit27=0 (WRITE-commit), ram_id=(>>22)&0x1f=5
(hash-RAM), addr=&0x3FFFFF=7. => last write was hash-RAM entry idx 7. **Matches**
`spa_set_hashram` final iteration (loop ends at idx 7, ram_id 5). CONFIRMED. ✓

## 2. READ recipe  (CONFIDENCE: HIGH; from spa_set_matchram read-phase tm:26171-26205)
Per entry:
1. Poll STATUS (reg5, 0x...4018) bit0 until 0 ("access done"), ≤0x13 tries
   (`spa_get_indirect_rw_status`, tm:25979 + spin tm:26174).
2. Write CMD = `addr | ram_id<<22 | (1<<27)`  (READ-prefetch; addr = N>>2 for matchram).
3. Poll STATUS bit0==0 again.
4. Read DATA words via `spa_get_indirect_rw_data(id)` for id=5,4,3,2,1,0
   (reg6 idx, 0x...401c..0x4030). **6 DATA words (0x18 bytes) per RAM line** for
   ram_id 0; hash-RAM read would use **2 words** (only idx0/1 ever written).

## 3. Entry count + format
- **ram_id 0 (match-RAM):** memcpy `_LANCHOR1`, 0x160 bytes = 88 words, consumed
  8 words/entry → **11 entries** (tm:43329/43344-43358, `local_180[88]`, +8/iter,
  stop at `&uStack_20`). Each match-RAM *line* holds **4 rules** (addr=N>>2, slot=N&3),
  6 packed data words/line. Per-rule logical fields (from input struct, printk
  tm:26164-26168 + packing tm:26206-26248):
  `rule_num, valid(1b), v4_v6_flag(1b), offset_mode(2b), offset(6b),
   compare_mode(2b), mask(16b), data(16b)` — i.e. an offset/mask/data byte-match,
   NOT an explicit src-port→out-port pair. **No source-port/MAC/out-port columns
   exist in the match-RAM line itself.** (Out-port forwarding is decided downstream
   by PM out-port rules `0x201a0…` + match_mode, per `pm_spa_init_recipe_re.md`.)
- **ram_id 5 (hash-RAM):** **8 entries** (tm:43361, loop idx 0..7, `local_1b0`,
  +6 bytes/iter). 2 data words/entry. Fields (printk tm:26045-26049):
  `valid(1b), match_array, action_rsn, action(2b)`.

## 4. WRITE recipe  (CONFIDENCE: HIGH for matchram; format dense)
matchram (tm:26194-26257): (1) poll done; (2) CMD READ-prefetch `(rw=1,ram=0,N>>2)`;
(3) read 6 words; (4) OR new 8-byte entry into the slot (`N&3`) of those 6 words
(packing switch tm:26206-26248); (5) CMD WRITE `(rw=0,ram=0,N>>2)`; (6) write the 6
words back (`spa_set_indirect_rw_data` id=5..0). It is a read-modify-write because
4 rules share one 6-word line. hashram (tm:26074-26083): poll done; CMD WRITE
`(rw=0,ram=5,idx)`; write only data id=1 then id=0 (2 words). No read-modify needed.

## 5. VERDICT on _LANCHOR1 payload — STATIC-RECONSTRUCTABLE, not "must-read-stock"
The match-RAM VALUES come from the `_LANCHOR1` .rodata blob (0x160 bytes) +
`DAT_0004eee4` (12-word) copy (tm:43329-43343). These bytes are **NOT in this
decomp dump** and **NOT visible in MMIO stock dumps** (RAM is indirect-only; only the
leftover CMD 0x01400007 leaks). **However they are constant data baked into tm.ko's
.rodata.** Therefore:
- They are **fully static-reconstructable by reading `_LANCHOR1`/`DAT_0004eee4`
  directly out of the tm.ko ELF .rodata** (`readelf`/`objdump` at symbol `_LANCHOR1`).
  That is the correct, deterministic source — reading live stock RAM is NOT required.
- Reading the RAM live via the §2 READ recipe is only a *cross-check*, not a
  necessity.
- Caveat: whether any of these 11 match entries actually encodes the CPU-source-port
  authorization is **unconfirmed** — the match-RAM lines carry offset/mask/data
  byte-matchers, not a src→egress mapping. The CPU→physical egress gate is most
  likely the 3 direct load-bearing pokes (PM `0x201a0=0x08`, PM `0x20054=0xc0`,
  SPA `0x1407c=0x01`) per `pm_spa_init_recipe_re.md`, with match_mode=1 + the
  _LANCHOR1 table providing classification, not the gate itself.

## Not derivable from decomp alone
- The 11 match-RAM / hash-RAM literal entry bytes (need the tm.ko ELF .rodata at
  `_LANCHOR1` + `DAT_0004eee4`; not in this .c dump).
- Exact semantic meaning of hash-RAM `action`/`action_rsn` codes.
