// module: mt7915.ko
// function: set_ht_fixed_mcs @ 0x137a28
// size: 88 bytes
//

undefined4 set_ht_fixed_mcs(int param_1,int param_2,int param_3)

{
  uint uVar1;
  
  if (param_2 == 0x20) {
    uVar1 = *(ushort *)(param_1 + 0xbe) & 0xfffffe7f;
    *(byte *)(param_1 + 0xbe) = (byte)uVar1 & 0xc0 | 0xa0;
    *(byte *)(param_1 + 0xbf) = (byte)(uVar1 >> 8) & 0x19 | 0x40;
    return 1;
  }
  if (param_3 < (int)(*(byte *)(param_1 + 0xbe) & 0x3f)) {
    *(byte *)(param_1 + 0xbe) = *(byte *)(param_1 + 0xbe) & 0xc0 | (byte)param_3 & 0x3f;
  }
  return 1;
}

