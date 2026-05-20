// module: mt7915.ko
// function: DfsDedicatedExamineSetNewCh @ 0x234a28
// size: 108 bytes
//

void DfsDedicatedExamineSetNewCh(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = HcGetBandByWdev(param_2);
  iVar1 = param_1 + 0x795000 + iVar1;
  iVar2 = DfsPrimToCent(param_3,*(undefined1 *)(iVar1 + 0x134));
  if (*(char *)(param_1 + 0x7953fa) != '\0') {
    iVar1 = DfsPrimToCent(*(undefined1 *)(param_1 + 0x7953fb),*(undefined1 *)(iVar1 + 0x134));
    *(bool *)(param_1 + 0x795403) = iVar1 != iVar2;
    DfsDedicatedSetNewChStat(param_1,param_2);
    return;
  }
  return;
}

