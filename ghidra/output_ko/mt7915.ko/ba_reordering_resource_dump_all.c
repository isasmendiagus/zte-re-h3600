// module: mt7915.ko
// function: ba_reordering_resource_dump_all @ 0xa53cc
// size: 144 bytes
//

void ba_reordering_resource_dump_all(int param_1)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar3 = 0;
  iVar4 = param_1 + 0x1d0;
  do {
    _raw_spin_lock_bh(iVar4);
    for (piVar1 = *(int **)(iVar4 + 0x1c); piVar1 != (int *)0x0; piVar1 = (int *)*piVar1) {
      for (piVar2 = (int *)piVar1[1]; piVar2 != (int *)0x0; piVar2 = (int *)*piVar2) {
        iVar3 = iVar3 + 1;
      }
      iVar3 = iVar3 + 1;
    }
    iVar5 = iVar4 + 0x60;
    _raw_spin_unlock_bh(iVar4);
    iVar4 = iVar5;
  } while (iVar5 != param_1 + 0x1b1d0);
  if (0 < DebugLevel) {
    printk("total %d msdu packt in ba list\n",iVar3);
    return;
  }
  return;
}

