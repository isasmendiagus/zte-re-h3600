// module: mt7915.ko
// function: HcGetQloadCtrlByRf @ 0xa9a80
// size: 104 bytes
//

undefined1 * HcGetQloadCtrlByRf(int param_1,byte param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(param_1 + 0xa797a0);
  if (*(byte *)(iVar1 + 0x32d8) == 0) {
    return (undefined1 *)0x0;
  }
  if ((param_2 & *(byte *)(iVar1 + 0x1360)) == 0) {
    if (*(byte *)(iVar1 + 0x32d8) < 2) {
      return (undefined1 *)0x0;
    }
    if ((param_2 & *(byte *)(iVar1 + 0x16b4)) == 0) {
      return (undefined1 *)0x0;
    }
    iVar2 = 1;
  }
  else {
    iVar2 = 0;
  }
  return &DAT_000015c4 + iVar2 * 0x354 + iVar1;
}

