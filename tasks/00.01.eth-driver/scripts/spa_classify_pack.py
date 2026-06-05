#!/usr/bin/env python3
# Replicate stock spa_set_matchram packing (decomp tm.c:26194-26257) LITERALLY via
# Ghidra CONCAT/SUB helpers, to compute the 3 matchram banks from the 11 rules, + the
# 8 hashram entries. Emits the SPA-indirect load sequence (cmd 0x921d4014 / data
# 0x921d401c+id*4 / status 0x921d4018; matchram ram_id=0, hashram ram_id=5).
M = 0xffffffff
def C11(a,b): return ((a&0xff)<<8)|(b&0xff)
def C12(a,bc): return ((a&0xff)<<16)|(bc&0xffff)
def C13(a,bcd): return ((a&0xff)<<24)|(bcd&0xffffff)
def C22(a,b): return ((a&0xffff)<<16)|(b&0xffff)
def C21(ab,c): return ((ab&0xffff)<<8)|(c&0xff)
def C31(abc,d): return ((abc&0xffffff)<<8)|(d&0xff)
def S41(x,n): return (x>>(n*8))&0xff   # SUB41: byte n
def b(x,n): return (x>>(n*8))&0xff      # byte n of u32

# 11 matchram rules: (rule, valid, v4v6, offmode, offset, cmp, mask, data)
RULES = [
 (0,1,1,2,0x04,0,0x00ff,0x0011),(1,1,1,2,0x0b,0,0xffff,0x0208),
 (2,1,1,2,0x0b,0,0xffff,0x076c),(3,1,1,2,0x0b,1,0xffff,0x013e),
 (4,1,1,2,0x0b,2,0xffff,0x0141),(5,1,1,2,0x0a,0,0xffff,0x0043),
 (6,1,1,2,0x0a,0,0xffff,0x0044),(7,1,1,2,0x0b,0,0xffff,0x0043),
 (8,1,1,2,0x0b,0,0xffff,0x0044),(9,1,1,2,0x04,0,0x00ff,0x0006),
 (10,1,1,2,0x0b,0,0xffff,0x00b3),
]
# bank dict: bank_idx -> {l24,l28,l2c,l30,l34,l38} u32, init 0
banks={}
def getbank(bk):
    return banks.setdefault(bk, {'l24':0,'l28':0,'l2c':0,'l30':0,'l34':0,'l38':0})

for (rule,valid,v6,om,off,cmp,mask,data) in RULES:
    bk = rule>>2; sub = rule&3
    L = getbank(bk)
    p1,p2,p3,p4,p5,p6,p7,p8,p9 = valid,v6,om,off,cmp, mask&0xff,(mask>>8)&0xff, data&0xff,(data>>8)&0xff
    if sub==0:
        iVar1=(p5&3)<<7
        uVar7=(L['l28']&0xff80007f)|((data&0xffff)<<7)
        B0=((p7>>1)|(iVar1&0xff))&0xff
        B1=(((iVar1>>8)&0xff)|((p4&0x3f)<<1)|((p3&1)<<7))&0xff
        B2=((b(L['l24'],2)&0xf0)|(((om<<0x1e)&M)>>0x1f)|((p2&3)<<1)|((p1&1)<<3))&0xff
        L['l24']=C13(0, C12(B2, C11(B1,B0)))
        HI=((((uVar7<<9)&M)>>0x19)&0xffff)|((mask<<7)&0xffff)
        L['l28']=C22(HI, uVar7&0xffff)
    elif sub==1:
        L['l2c']=C13(((((mask<<10)&M)>>0x18)&0xff)|((p5&3)<<2)|((p4&0xf)<<4),
                     (((data&0xffff)>>6)|((mask<<10)&0xffffff))&0xffffff)
        L['l28']=C31(b(L['l28'],1)|(b(L['l28'],2)<<8)|(b(L['l28'],3)<<16),  # local_28._1_3_ preserved
                     ((b(L['l28'],0)&0x80)|(((om<<0x1a)&M)>>0x1e)|((p3&3)<<2)|((p2&3)<<4)|((p1&1)<<6))&0xff)
        L['l30']=C13(((b(L['l30'],3)&3)|((data&0xff)<<2))&0xff, L['l30']&0xffffff)
    elif sub==2:
        L['l30_02']=C11((((mask>>0xb)&0xff)|((p5&3)<<5))&0xff,(((mask>>3))&0xff))
        # rebuild l30 progressively (mirror decomp)
        l30=L['l30']
        l30=(l30&0xffff0000)|(L['l30_02']&0xffff)
        uVar7=(l30&0xffe07fff)|((p4&0x3f)<<0xf)
        l30=(l30&0x00ffffff)|((((l30&0xffe07fff)>>0x18)&0xff)<<24)
        l30=(l30&0xffff0000)|(uVar7&0xffff)
        l30=(l30&0xff00ffff)|(((((uVar7>>0x10)&0x9f)|((p3&3)<<5))&0xff)<<16)
        uVar7b=(L['l34']&0xe0001fff)|((data&0xffff)<<0xd)
        uVar5=(((l30>>0x10)&0xfe7f)|((p2&3)<<7))
        l30=(l30&0x0000ffff)|((uVar5&0xffff)<<16)
        L['l34']=C13(((((uVar7b<<3)&M)>>0x1b)|((mask&0xff)<<5))&0xff, uVar7b&0xffffff)
        l30=(l30&0x00ffffff)|(((((uVar5>>8)&0xfd)|((p1&1)<<1))&0xff)<<24)
        L['l30']=l30&M
    else:  # sub==3
        L['l34']=C31(b(L['l34'],0)|(C21(b(L['l34'],2)|(b(L['l34'],3)<<8),
                       (b(L['l34'],1)&0xe0)|((p3&3))|((p2&3)<<2)|((p1&1)<<4))<<8 & 0xffffff00),
                     ((p5&3)|((p4)<<2))&0xff) if False else (
                     # simpler literal: local_34 = CONCAT31(CONCAT21(l34._2_2_, B1), B0)
                     C31(C21((L['l34']>>16)&0xffff,
                             ((b(L['l34'],1)&0xe0)|(p3&3)|((p2&3)<<2)|((p1&1)<<4))&0xff),
                         ((p5&3)|((p4&0xff)<<2))&0xff))
        L['l38']=C22(mask&0xffff, data&0xffff)

# data_id mapping: id5=l24,id4=l28,id3=l2c,id2=l30,id1=l34,id0=l38
def bank_words(L):
    return [L['l38'],L['l34'],L['l30'],L['l2c'],L['l28'],L['l24']]  # data_id 0..5

print("=== MATCHRAM banks (data_id 0..5 = 0x1401c..0x14030) ===")
for bk in sorted(banks):
    w=bank_words(banks[bk])
    print("bank %d:"%bk, " ".join("%08x"%x for x in w))

HASH=[(0x000016a9,0x1aa50200),(0x00001aa5,0x328d0200),(0x0000328d,0x62750200),
      (0x00026275,0xa2750200),(0x0001a275,0x62750200),(0x00016275,0xa2750200),
      (0x0002a275,0x20a10200),(0x000c20a1,0x00000200)]  # slot7 data1 hi16=0 (read-live TODO)
print("=== HASHRAM slots (data0,data1) ===")
for i,(d0,d1) in enumerate(HASH): print("slot %d: data0=%08x data1=%08x"%(i,d0,d1))
