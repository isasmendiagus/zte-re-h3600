// module: mt7915.ko
// function: HcGetChannelByRf @ 0xa98d0
// size: 96 bytes
//

undefined1 HcGetChannelByRf(int param_1,byte param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0xa797a0);
  if (*(byte *)(iVar2 + 0x32d8) == 0) {
    return 0;
  }
  if ((param_2 & *(byte *)(iVar2 + 0x1360)) == 0) {
    if (*(byte *)(iVar2 + 0x32d8) < 2) {
      return 0;
    }
    if ((param_2 & *(byte *)(iVar2 + 0x16b4)) == 0) {
      return 0;
    }
    iVar1 = 1;
  }
  else {
    iVar1 = 0;
  }
  return *(undefined1 *)(iVar1 * 0x354 + iVar2 + 0x16a0);
}

