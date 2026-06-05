#!/usr/bin/env python3
"""Generate the full FFE extract ram1-rule + ram0-index table for the mainline
driver, from the stock init loop structure, and VERIFY every generated entry
against the live-captured stock CLA dump (cla_stock_ram0-6_2026-06-01.txt).

Stock callers that build this infrastructure (decomp_all_tm.c):
  aclRamInit_part_6  (idx 1..10 base index tables, extract bytes sequential)
  tm_acl_l2_fast_init     idx 1..8  -> rules (p<<4)+0..3
  tm_acl_3tuple_fast_init idx 1..9  -> rules (0x14 + 0x10*(p-1))+0..3
  tm_acl_fast_init        -> rules 0x90/0x91 (v4 5tuple) + 0x02/0x03 (v6 5tuple),
                             index valid bits on idx 9 (|1) and idx 10 (|4)

The capture is a PARTIAL dump (rule_ids 0x02,0x03,0x10..0x29; index 0x00..0x0a).
We extrapolate the loop and assert the generated entries match every captured row.
"""
import re, sys, os

CAP = os.path.join(os.path.dirname(__file__),
    "../../00.10.02.re-stock-kmods/findings/captures/cla_stock/cla_stock_ram0-6_2026-06-01.txt")

def load_capture():
    ram = {0: {}, 1: {}}
    with open(CAP) as f:
        for line in f:
            m = re.match(r'ram(\d) a0x([0-9a-f]+):\s+(.*)', line)
            if not m:
                continue
            rid = int(m.group(1)); addr = int(m.group(2), 16)
            words = [int(x, 16) for x in m.group(3).split()]
            if rid in ram:
                ram[rid][addr] = words
    return ram

# ---- rule templates (17 words), captured verbatim, dir bit at word14 -------
# L2 5-tuple (v4) base, from ram1 a0x10 ; dir-set variant a0x11 (word14 0x00->0x02 high nibble)
T_L2_V4   = [0x22038608,0x000058a1,0,0,0xf00ff000,0xffffffff,0xffffffff,0x0fffffff,
             0,0,0,0,0,0,0x00700000,0x00092492,0]
# L2 v6, from ram1 a0x12
T_L2_V6   = [0xe1828406,0x16284880,0x01e3868c,0x94264889,0xfff0000a,0xffffffff,0xffffffff,
             0xffffffff,0xffffffff,0xffffffff,0xffffffff,0xffffffff,0xffffffff,0x0fffffff,
             0x01300000,0xdb6db6db,0x00db6db6]
# 3-tuple v4, from ram1 a0x14
T_3T_V4   = [0x22038608,0x00000001,0,0,0xf00ff000,0xffffffff,0x0fffffff,0,0,0,0,0,0,0,
             0x00500000,0x00002492,0]
# 3-tuple v6, from ram1 a0x16
T_3T_V6   = [0xe1828406,0x16284880,0x01e3868c,0x00264889,0xfff00000,0xffffffff,0xffffffff,
             0xffffffff,0xffffffff,0xffffffff,0xffffffff,0xffffffff,0x0fffffff,0x00000000,
             0x01100000,0xdb6db6db,0x00036db6]
# v4 5-tuple (tm_acl_fast_init rule 0x90), from phase6_cla_hw_hash_CRACKED.md ram1[0x98]
T_FAST_V4 = [0x22038608,0x000058a1,0,0,0xf00ff000,0xffffffff,0xffffffff,0x0fffffff,
             0,0,0,0,0,0,0x00700000,0x00092492,0]
# v6 5-tuple (tm_acl_fast_init rule 0x02), from ram1 a0x02
T_FAST_V6 = [0xe1828406,0x16284880,0x01e3868c,0x94264889,0xfff0000a,0xffffffff,0xffffffff,
             0xffffffff,0xffffffff,0xffffffff,0xffffffff,0xffffffff,0xffffffff,0x0fffffff,
             0x01300000,0xdb6db6db,0x00db6db6]

def dir_set(template):
    """The dir-set ('|0x200' on local_76/local_32/local_6e/local_2a) variant:
    in every captured pair the ONLY change is word14 high nibble 0->2 (e.g.
    0x00700000->0x02700000, 0x01300000->0x03300000, 0x00500000->0x02500000,
    0x01100000->0x03100000)."""
    w = list(template)
    w[14] = w[14] | 0x02000000
    return w

def gen_rules():
    """Returns dict rule_id -> 17 words."""
    rules = {}
    # tm_acl_l2_fast_init: idx 1..8  base = idx<<4
    for p in range(1, 9):
        base = p << 4
        rules[base + 0] = T_L2_V4
        rules[base + 1] = dir_set(T_L2_V4)
        rules[base + 2] = T_L2_V6
        rules[base + 3] = dir_set(T_L2_V6)
    # tm_acl_3tuple_fast_init: idx 1..9 base = 0x14 + 0x10*(idx-1)
    for p in range(1, 10):
        base = 0x14 + 0x10 * (p - 1)
        rules[base + 0] = T_3T_V4
        rules[base + 1] = dir_set(T_3T_V4)
        rules[base + 2] = T_3T_V6
        rules[base + 3] = dir_set(T_3T_V6)
    # tm_acl_fast_init: v6 rules 0x02/0x03, v4 rules 0x90/0x91
    rules[0x02] = T_FAST_V6
    rules[0x03] = dir_set(T_FAST_V6)
    rules[0x90] = T_FAST_V4
    rules[0x91] = dir_set(T_FAST_V4)
    return rules

def gen_index():
    """ram0 index tables idx 1..10. extract bytes sequential; word4 = valid+flags
    from the captured dump (post-FFE-enable state)."""
    # captured word4 per index (the index_valid|flags after all inits OR their bits)
    cap_word4 = {1:0x00150355,2:0x00150355,3:0x00150355,4:0x00150355,5:0x00150355,
                 6:0x00150055,7:0x00150055,8:0x00150755,9:0x00150051,10:0x00150004}
    idx = {}
    for i in range(1, 11):
        if i == 10:
            ext = list(range(0x00, 0x10))   # ram0 a0x0a = 03020100.. = 0x00..0x0f
        else:
            base = i << 4
            ext = [base + k for k in range(16)]
        # pack 16 ext bytes into 4 LE words + word4
        words = []
        for w in range(4):
            words.append(ext[w*4] | ext[w*4+1]<<8 | ext[w*4+2]<<16 | ext[w*4+3]<<24)
        words.append(cap_word4[i])
        idx[i] = words
    return idx

def main():
    cap = load_capture()
    rules = gen_rules()
    index = gen_index()

    errors = 0
    # verify rules
    for addr, words in sorted(cap[1].items()):
        if addr in rules:
            if rules[addr] != words:
                print(f"MISMATCH ram1[0x{addr:02x}]:")
                print("  gen:", ' '.join('%08x'%x for x in rules[addr]))
                print("  cap:", ' '.join('%08x'%x for x in words))
                errors += 1
        else:
            print(f"capture has ram1[0x{addr:02x}] but generator does not produce it")
            errors += 1
    # verify index
    for addr, words in sorted(cap[0].items()):
        if addr == 0:
            continue  # a0x00 is not an FFE index
        if addr in index:
            if index[addr][:5] != words[:5]:
                print(f"MISMATCH ram0[0x{addr:02x}]:")
                print("  gen:", ' '.join('%08x'%x for x in index[addr][:5]))
                print("  cap:", ' '.join('%08x'%x for x in words[:5]))
                errors += 1

    print(f"\nVerification: {errors} mismatches against captured stock dump.")
    print(f"Generated {len(rules)} ram1 rules, {len(index)} ram0 index tables.")

    if '--emit' in sys.argv:
        out = sys.argv[sys.argv.index('--emit') + 1] if len(sys.argv) > sys.argv.index('--emit') + 1 else '/tmp/ffe_table_c.txt'
        emit_c(rules, index, out)
        print(f"emitted C table to {out}")

def emit_c(rules, index, path):
    lines = []
    lines.append("/* ===== ram1 extract rules (17 words each) ===== */")
    lines.append("static const struct zx_ffe_rule { u16 id; u32 w[17]; } zx_ffe_rules[] = {")
    for addr in sorted(rules):
        w = rules[addr]
        lines.append(f"\t{{ 0x{addr:02x}, {{ " + ', '.join('0x%08x'%x for x in w) + " } },")
    lines.append("};")
    lines.append("")
    lines.append("/* ===== ram0 index tables (5 words each) ===== */")
    lines.append("static const struct zx_ffe_index { u8 id; u32 w[5]; } zx_ffe_index[] = {")
    for addr in sorted(index):
        w = index[addr]
        lines.append(f"\t{{ {addr:2d}, {{ " + ', '.join('0x%08x'%x for x in w) + " } },")
    lines.append("};")
    with open(path, 'w') as f:
        f.write('\n'.join(lines) + '\n')

if __name__ == '__main__':
    main()
