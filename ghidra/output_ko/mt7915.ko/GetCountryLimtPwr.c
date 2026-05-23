// module: mt7915.ko
// function: GetCountryLimtPwr @ 0xd8558
// size: 80 bytes
//

undefined1 GetCountryLimtPwr(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  do {
    iVar2 = iVar3 * 2;
    iVar1 = iVar3 * 2;
    iVar3 = iVar3 + 1;
    if (Region_PwrDesc_2GHZ[iVar2] == *(char *)(param_1 + 0x794c46)) {
      return Region_PwrDesc_2GHZ[iVar1 + 1];
    }
  } while (iVar3 != 7);
  return 0x24;
}

