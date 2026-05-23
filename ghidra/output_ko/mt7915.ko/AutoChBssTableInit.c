// module: mt7915.ko
// function: AutoChBssTableInit @ 0x1fbc8
// size: 144 bytes
//

void AutoChBssTableInit(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  bool bVar3;
  int local_1c;
  
  iVar2 = 0;
  local_1c = 0;
  do {
    iVar1 = HcGetAutoChCtrlbyBandIdx(param_1,iVar2);
    os_alloc_mem(param_1,&local_1c,0x2a01);
    if (local_1c == 0) {
      if (-1 < DebugLevel) {
        printk("%s Fail to alloc memory for pAutoChCtrl->pBssInfoTab","AutoChBssTableInit");
      }
    }
    else {
      __memzero(local_1c,0x2a01);
      *(int *)(iVar1 + 4) = local_1c;
    }
    bVar3 = iVar2 != 1;
    iVar2 = 1;
  } while (bVar3);
  return;
}

