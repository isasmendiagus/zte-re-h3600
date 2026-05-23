// module: mt7915.ko
// function: ShowIrqHistory @ 0x192f80
// size: 572 bytes
//

void ShowIrqHistory(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint *puVar8;
  uint *puVar9;
  uint *puVar10;
  uint local_d0;
  int local_cc;
  uint auStack_c8 [10];
  uint auStack_a0 [10];
  uint auStack_78 [10];
  uint auStack_50 [11];
  
  local_d0 = 0;
  local_cc = 0;
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x2170bc,&local_d0);
  uVar6 = local_d0 & 0xff;
  uVar7 = local_d0 >> 8 & 0xff;
  if (0 < DebugLevel) {
    printk("\n\n\n       Irq Idx (Dis=%d Res=%d):\n",uVar7,uVar6);
  }
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x2170b8,&local_cc);
  iVar5 = 0;
  puVar9 = auStack_c8;
  puVar10 = auStack_a0;
  do {
    hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar5 + local_cc,&local_d0);
    uVar1 = *(undefined4 *)(param_1 + 0xa797a0);
    iVar2 = local_cc + 4 + iVar5;
    iVar5 = iVar5 + 8;
    puVar8 = puVar9 + 1;
    *puVar9 = local_d0;
    hw_io_read32(uVar1,iVar2,&local_d0);
    *puVar10 = local_d0;
    puVar9 = puVar8;
    puVar10 = puVar10 + 1;
  } while (puVar8 != auStack_a0);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x2170b4,&local_cc);
  iVar5 = 0;
  puVar9 = auStack_78;
  puVar10 = auStack_50;
  do {
    hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar5 + local_cc,&local_d0);
    uVar1 = *(undefined4 *)(param_1 + 0xa797a0);
    iVar2 = local_cc + 4 + iVar5;
    iVar5 = iVar5 + 8;
    puVar8 = puVar9 + 1;
    *puVar9 = local_d0;
    hw_io_read32(uVar1,iVar2,&local_d0);
    *puVar10 = local_d0;
    puVar9 = puVar8;
    puVar10 = puVar10 + 1;
  } while (puVar8 != auStack_50);
  if (0 < DebugLevel) {
    printk("\n       Dis Irq history (from old to new):\n");
  }
  uVar4 = uVar7 + 10;
  iVar5 = DebugLevel;
  do {
    if (0 < iVar5) {
      uVar3 = uVar7 % 10;
      printk("      [%d].LP = 0x%x   time=%u\n",uVar3,auStack_a0[uVar3],auStack_c8[uVar3]);
      iVar5 = DebugLevel;
    }
    uVar7 = uVar7 + 1;
  } while (uVar7 != uVar4);
  if (0 < iVar5) {
    printk("\n       Restore Irq history (from old to new):\n");
    iVar5 = DebugLevel;
  }
  uVar7 = uVar6 + 10;
  do {
    if (0 < iVar5) {
      uVar4 = uVar6 % 10;
      printk("      [%d].LP = 0x%x   time=%u\n",uVar4,auStack_50[uVar4],auStack_78[uVar4]);
    }
    uVar6 = uVar6 + 1;
    iVar5 = DebugLevel;
  } while (uVar6 != uVar7);
  return;
}

