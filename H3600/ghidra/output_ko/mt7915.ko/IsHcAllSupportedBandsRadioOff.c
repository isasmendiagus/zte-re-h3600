// module: mt7915.ko
// function: IsHcAllSupportedBandsRadioOff @ 0xa8f4c
// size: 88 bytes
//

bool IsHcAllSupportedBandsRadioOff(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0xa797a0);
  if (*(byte *)(iVar1 + 0x32d8) != 0) {
    if (*(char *)(*(int *)(iVar1 + 4) + 1) == '\x01') {
      return false;
    }
    if (1 < *(byte *)(iVar1 + 0x32d8)) {
      return *(char *)(*(int *)(iVar1 + 0x20) + 1) != '\x01';
    }
  }
  return true;
}

