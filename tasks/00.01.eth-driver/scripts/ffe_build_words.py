#!/usr/bin/env python3
"""Reconstruct the FFE extract rule (ram1, 17 words) and index (ram0, 5 words)
buffers field-by-field exactly as the stock decomp builds local_b0/local_6c/auStack_c4,
then cross-check the IPv4 rule/index against the live-captured ram1[0x98]/ram0[0x09].

A "buffer" is a little-endian byte array of 0x44 bytes (17 u32 words). The decomp
writes named locals at fixed stack offsets; we model the buffer as bytes and apply
the same masked assignments, then read it out as 17 LE u32 words.
"""
import struct

class Buf:
    def __init__(self, n=0x44):
        self.b = bytearray(n)
    def setw(self, off, val):           # write u32 LE at byte offset (full word)
        struct.pack_into('<I', self.b, off, val & 0xffffffff)
    def getw(self, off):
        return struct.unpack_from('<I', self.b, off)[0]
    def seth(self, off, val):           # write u16 LE
        struct.pack_into('<H', self.b, off, val & 0xffff)
    def geth(self, off):
        return struct.unpack_from('<H', self.b, off)[0]
    def setb(self, off, val):
        self.b[off] = val & 0xff
    def words(self, count):
        return [self.getw(i*4) for i in range(count)]

def hexw(ws):
    return ' '.join('%08x' % w for w in ws)

# ---------------------------------------------------------------------------
# RULE buffer (ram1, 17 words) — IPv4 5-tuple, from tm_acl_fast_init local_b0
# Stack layout (offsets relative to &local_b0):
#   local_b0 @0x00  local_ac @0x04  local_a0 @0x08  uStack_9d @0x0b
#   local_9c @0x0c  local_98 @0x10  local_94 @0x14  local_76 @... etc.
# We map each named local to its byte offset within the 0x44 buffer.
# From the decomp declaration order + ARM stack packing this is the standard
# Ghidra layout: contiguous descending addresses => buffer offset = (base - addr_of_local).
# We instead use the offsets implied by the printk decoders in cla_set_extra_rule_table:
#   winoffset0 = byte0&0x7f ; word0 = 0x22038608 -> winoffsets
#   inport/outport mask @ byte0x39 ; etc.
# Easiest faithful path: replicate the exact assignments using the SAME relative
# offsets the compiler used. We derive them from the struct field order in the
# function (each local's offset = its distance below local_b0=offset0).
# ---------------------------------------------------------------------------

def build_rule_v4():
    """tm_acl_fast_init local_b0 (IPv4/TCP 5-tuple extract rule)."""
    r = Buf(0x44)
    # local_b0 = 0x22038608                       @0x00
    r.setw(0x00, 0x22038608)
    # local_ac = (..&0xfffe0007)|0x58a0  (was CONCAT22(hi,1)) low16 base 1 -> |0x58a0
    #   net effect on a zeroed buffer: low halfword 0x0001, then &0xfffe0007|0x58a0
    v = (0x00000001 & 0xfffe0007) | 0x58a0
    r.setw(0x04, v)                                # @0x04 -> 0x000058a1
    # _local_a0 = CONCAT13(0xf0, uVar1&0xfff|0xff000) ; uVar1=(uint3)local_a0 (=0 init)
    #   => 24-bit low = (0|0xff000)&0xffffff... actually (0&0xfff)|0xff000 = 0xff000
    #   CONCAT13(0xf0, 0x0ff000) = 0xf00ff000
    r.setw(0x08, 0xf00ff000)                       # @0x08
    # local_9c = 0xffffffff                        @0x0c
    r.setw(0x0c, 0xffffffff)
    # local_98 = 0xffffffff                        @0x10
    r.setw(0x10, 0xffffffff)
    # local_94 = (..&0xf0000fff)|0xfffffff then &.. : net = 0x0fffffff
    r.setw(0x14, 0x0fffffff)                        # @0x14
    # local_76 ushort @ ? and local_74 ...
    # local_74 = CONCAT22(hi,0x2492); then &0xffe07fff|0x90000 => low16=0x2492, |0x90000
    #   0x00002492 & 0xffe07fff = 0x00002492 ; |0x90000 = 0x00092492
    # local_74 sits at @0x1c (after local_76 ushort @0x18-0x19 region).
    # local_76 = (..&0xfe0f)|0x70  then |0x200 for the 0x91 rule.
    # Place per the captured layout: word @0x18 holds local_76(low16)+pad; word@0x1c=local_74
    # captured ram1[0x98] word6 (0x18) = 0x00700000, word7(0x1c)=0x00092492.
    # local_76 = 0x0070 placed at byte 0x1a (high half of word0x18): 0x0070<<16=0x00700000
    r.seth(0x1a, 0x0070)                            # local_76 -> word@0x18 = 0x00700000
    r.setw(0x1c, 0x00092492)                        # local_74
    return r

def build_index(valid_bits, ext_byte, extract_lo, extract_hi):
    """ram0 index table buffer (5 words). extract_index0..15 = bytes 0..15.
    For index 9 (v4) the extract bytes are 0x90..0x9f (set by aclRamInit_part_6 loop).
    valid_bits -> u16 at 0x10 ; ext_byte -> byte 0x12."""
    r = Buf(0x14)
    for i in range(16):
        r.setb(i, 0x90 + i)   # extract_index0..15 = 0x90..0x9f for index 9
    r.seth(0x10, valid_bits)
    r.setb(0x12, ext_byte)
    return r

rule_v4 = build_rule_v4()
print("RULE ram1 (v4, rule 0x90/0x91) 17 words:")
print(" ", hexw(rule_v4.words(17)))
print("captured ram1[0x98]:")
print("  22038608 000058a1 0 0 f00ff000 ffffffff ffffffff 0fffffff 0 0 0 0 0 0 00700000 00092492 0")

idx9 = build_index(0x0051, 0x15, None, None)
print("\nINDEX ram0[0x09] 5 words:")
print(" ", hexw(idx9.words(5)))
print("captured ram0[0x09]:")
print("  93929190 97969594 9b9a9998 9f9e9d9c 00150051")
