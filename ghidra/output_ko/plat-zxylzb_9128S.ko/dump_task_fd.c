// module: plat-zxylzb_9128S.ko
// function: dump_task_fd @ 0x1c644
// size: 152 bytes
//

void dump_task_fd(int param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint *puVar6;
  int iVar7;
  undefined1 auStack_118 [256];
  
  puVar6 = *(uint **)(*(int *)(param_1 + 0x310) + 4);
  for (iVar7 = 0; uVar5 = iVar7 << 3, uVar5 < *puVar6; iVar7 = iVar7 + 4) {
    iVar4 = iVar7 << 5;
    uVar3 = *(uint *)(puVar6[3] + iVar7);
    while (uVar3 != 0) {
      uVar1 = uVar3 & 1;
      uVar3 = uVar3 >> 1;
      if (uVar1 != 0) {
        if ((*(int *)(puVar6[1] + iVar4) != 0) &&
           (iVar2 = d_path(*(int *)(puVar6[1] + iVar4) + 8,auStack_118,0x100), iVar2 != 0)) {
          printk("fd %d : %s\n",uVar5);
        }
      }
      uVar5 = uVar5 + 1;
      iVar4 = iVar4 + 4;
    }
  }
  return;
}

