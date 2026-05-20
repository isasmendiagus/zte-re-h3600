// module: mt7915.ko
// function: ShowSchduleTrace @ 0x19359c
// size: 376 bytes
//

void ShowSchduleTrace(int param_1)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 uVar8;
  undefined1 *puVar9;
  undefined1 *puVar10;
  int iVar11;
  int iVar12;
  undefined1 *puVar13;
  undefined4 uVar14;
  undefined4 local_104;
  undefined4 local_fd [7];
  undefined1 auStack_e1 [17];
  undefined1 auStack_d0 [60];
  int local_94;
  undefined4 local_8c;
  undefined1 auStack_88 [16];
  int local_78 [20];
  undefined1 auStack_28 [4];
  
  local_104 = 0;
  puVar3 = local_fd;
  puVar4 = &DAT_0029d458;
  do {
    puVar7 = puVar4;
    puVar6 = puVar3;
    uVar8 = puVar7[1];
    uVar14 = puVar7[2];
    uVar5 = puVar7[3];
    *puVar6 = *puVar7;
    puVar6[1] = uVar8;
    puVar6[2] = uVar14;
    puVar6[3] = uVar5;
    puVar3 = puVar6 + 4;
    puVar4 = puVar7 + 4;
  } while (puVar7 + 4 != &DAT_0029d478);
  uVar5 = puVar7[5];
  uVar8 = puVar7[6];
  uVar1 = *(undefined1 *)(puVar7 + 7);
  puVar6[4] = 0x20324946;
  puVar6[5] = uVar5;
  puVar6[6] = uVar8;
  *(undefined1 *)(puVar6 + 7) = uVar1;
  puVar13 = auStack_88;
  do {
    puVar9 = puVar13 + 4;
    hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),puVar13 + (0x215400 - (int)auStack_88),puVar13)
    ;
    puVar13 = puVar9;
  } while (puVar9 != auStack_28);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x219838,&local_104);
  if (0 < DebugLevel) {
    printk("\n\n\n       TASK    XTIME    RATIO    PREMPT CNT\n");
  }
  iVar12 = 0;
  puVar13 = auStack_88;
  do {
    iVar11 = *(int *)(puVar13 + 0x10);
    puVar9 = auStack_d0;
    do {
      puVar10 = puVar9 + 4;
      hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),puVar9 + (iVar11 - (int)auStack_d0),puVar9);
      iVar2 = local_94;
      puVar9 = puVar10;
    } while (puVar10 != auStack_88);
    if (0 < DebugLevel) {
      uVar5 = __aeabi_uidiv(local_94 * 100,local_104);
      printk("       %s    %d    %d       %d\n",(int)local_fd + iVar12,iVar2,uVar5,local_8c);
    }
    iVar12 = iVar12 + 0xf;
    puVar13 = puVar13 + 0x20;
  } while (iVar12 != 0x2d);
  return;
}

