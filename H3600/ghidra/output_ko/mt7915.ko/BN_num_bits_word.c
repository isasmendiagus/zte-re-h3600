// module: mt7915.ko
// function: BN_num_bits_word @ 0x20d014
// size: 76 bytes
//

int BN_num_bits_word(ulong param_1)

{
  int iVar1;
  
  if (param_1 >> 0x10 == 0) {
    if ((param_1 & 0xff00) == 0) {
      iVar1 = (int)(char)(&DAT_002a1f08)[param_1];
    }
    else {
      iVar1 = (char)(&DAT_002a1f08)[param_1 >> 8] + 8;
    }
    return iVar1;
  }
  if ((param_1 & 0xff000000) == 0) {
    iVar1 = (char)(&DAT_002a1f08)[param_1 >> 0x10] + 0x10;
  }
  else {
    iVar1 = (char)(&DAT_002a1f08)[param_1 >> 0x18] + 0x18;
  }
  return iVar1;
}

