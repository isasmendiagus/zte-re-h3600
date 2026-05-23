// module: mt7915.ko
// function: RTMPStaFixedTxMode @ 0x131770
// size: 160 bytes
//

uint RTMPStaFixedTxMode(int param_1,int *param_2)

{
  uint uVar1;
  int iVar2;
  
  if (*(char *)(param_1 + 0x286285) != '\x01') {
    if (*(char *)(param_1 + 0x286285) == '\0') {
      uVar1 = ((uint)(byte)(&DAT_0036e407)[param_1] << 0x1a) >> 0x1d;
    }
    else {
      uVar1 = 0;
    }
    return uVar1;
  }
  if (param_2 == (int *)0x0) {
    return 0;
  }
  iVar2 = *param_2;
  if (iVar2 == 0x20001) {
    return ((uint)(byte)(&DAT_002b7af7)[(uint)*(byte *)(param_2 + 0x39) * 0x5834 + param_1] << 0x1a)
           >> 0x1d;
  }
  if (iVar2 == 2 || iVar2 == 0x40001) {
    uVar1 = ((uint)*(byte *)(param_2[2] + 0x8af) << 0x1a) >> 0x1d;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

