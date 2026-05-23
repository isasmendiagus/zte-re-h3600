// module: mt7915.ko
// function: AutoChBssTableDestroy @ 0x1fb80
// size: 72 bytes
//

void AutoChBssTableDestroy(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  bool bVar3;
  
  iVar2 = 0;
  do {
    iVar1 = HcGetAutoChCtrlbyBandIdx(param_1,iVar2);
    if ((iVar1 != 0) && (*(int *)(iVar1 + 4) != 0)) {
      os_free_mem();
      *(undefined4 *)(iVar1 + 4) = 0;
    }
    bVar3 = iVar2 != 1;
    iVar2 = 1;
  } while (bVar3);
  return;
}

