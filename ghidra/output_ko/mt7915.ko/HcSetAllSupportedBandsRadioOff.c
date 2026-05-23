// module: mt7915.ko
// function: HcSetAllSupportedBandsRadioOff @ 0xa8dd4
// size: 76 bytes
//

void HcSetAllSupportedBandsRadioOff(int param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = *(int *)(param_1 + 0xa797a0);
  if (*(char *)(iVar2 + 0x32d8) == '\0') {
    return;
  }
  uVar3 = 0;
  do {
    iVar1 = uVar3 * 0x1c;
    uVar3 = uVar3 + 1 & 0xff;
    *(undefined1 *)(*(int *)(iVar2 + iVar1 + 4) + 1) = 2;
  } while (uVar3 < *(byte *)(iVar2 + 0x32d8));
  return;
}

