// module: mt7915.ko
// function: ba_reodering_resource_dump @ 0xa545c
// size: 192 bytes
//

void ba_reodering_resource_dump(int param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  ushort *puVar4;
  int *piVar5;
  
  uVar1 = HcGetMaxStaNum();
  if (uVar1 <= param_2) {
    return;
  }
  iVar2 = 0;
  puVar4 = (ushort *)(param_1 + param_2 * 0x14c0 + 0xa29f2);
  do {
    puVar4 = puVar4 + 1;
    if (*puVar4 != 0) {
      for (piVar5 = *(int **)(param_1 + (uint)*puVar4 * 0x60 + 0x1ec); piVar5 != (int *)0x0;
          piVar5 = (int *)*piVar5) {
        for (piVar3 = (int *)piVar5[1]; piVar3 != (int *)0x0; piVar3 = (int *)*piVar3) {
          iVar2 = iVar2 + 1;
        }
        iVar2 = iVar2 + 1;
      }
    }
  } while (puVar4 != (ushort *)(param_1 + param_2 * 0x14c0 + 0xa2a02));
  if (0 < DebugLevel) {
    printk("total %d msdu packt in wcid (%d) ba list\n",iVar2,param_2,param_4);
    return;
  }
  return;
}

