// module: mt7915.ko
// function: ShowMsgWatch @ 0x193718
// size: 748 bytes
//

/* WARNING: Type propagation algorithm not settling */

void ShowMsgWatch(int param_1)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  uint *puVar9;
  int iVar10;
  int local_70;
  int local_6c [13];
  int local_38 [5];
  
  local_6c[9] = 1;
  local_6c[10] = 1;
  local_6c[0xb] = 2;
  local_6c[0xc] = 2;
  local_70 = 0;
  local_6c[1] = 0;
  local_6c[2] = 0;
  local_38[0] = 1;
  local_38[1] = 100;
  local_38[2] = 100;
  local_38[3] = 0x8a;
  local_6c[3] = 0;
  local_6c[4] = 0;
  local_6c[5] = 0;
  local_6c[6] = 0;
  local_6c[7] = 0;
  local_6c[8] = 0;
  local_6c[0] = 0;
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x219838,&local_70);
  if ((0 < DebugLevel) &&
     (printk("\n\n\n       Monitor Duration: %d unit = %d ms (unit 30.52us)\n",local_70,
             (local_70 * 0x1e + (uint)(local_70 * 0x34) / 100) / 1000), 0 < DebugLevel)) {
    printk("       MSG_ID     XTIME    RATIO    MAX_XTM      CNT\n");
  }
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),&DAT_0041f064,local_6c + 1);
  iVar8 = 0;
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),&DAT_0041f06c,local_6c + 2);
  puVar9 = (uint *)local_6c;
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),&DAT_0041f074,local_6c + 3);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),&DAT_0041f07c,local_6c + 4);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),&DAT_0041f060,local_6c + 5);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),&DAT_0041f068,local_6c + 6);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),&DAT_0041f070,local_6c + 7);
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),&DAT_0041f078,local_6c + 8);
  do {
    puVar9 = (uint *)((int)puVar9 + 4);
    uVar2 = *puVar9 * 0xc;
    os_alloc_mem(0,local_6c,uVar2);
    iVar7 = local_6c[0];
    if (local_6c[0] == 0) {
      if (-1 < DebugLevel) {
        printk("malloc msg buffer failed length=%d\n",uVar2);
      }
    }
    else {
      if (uVar2 != 0) {
        iVar10 = local_6c[iVar8 + 5] - local_6c[0];
        iVar3 = local_6c[0];
        do {
          iVar4 = iVar3 + 4;
          hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar3 + iVar10,iVar3);
          iVar3 = iVar4;
        } while ((uint)(iVar4 - iVar7) < uVar2);
      }
      if (0 < DebugLevel) {
        printk("       MSG WATCH TASK: %d\n",local_6c[iVar8 + 9]);
      }
      uVar2 = *puVar9;
      iVar7 = local_6c[0];
      if (uVar2 != 0) {
        uVar5 = 0;
        uVar6 = uVar5;
        do {
          if (0 < DebugLevel) {
            iVar10 = *(int *)(iVar7 + uVar6 + 4);
            iVar3 = local_38[iVar8];
            uVar1 = __aeabi_uidiv(iVar10 * 100,local_70);
            printk("       %d       %d        %d          %d       %d\n",uVar5 + iVar3,iVar10,uVar1,
                   *(undefined4 *)(iVar7 + uVar6 + 8),*(undefined4 *)(iVar7 + uVar6));
            uVar2 = *puVar9;
            iVar7 = local_6c[0];
          }
          uVar5 = uVar5 + 1;
          uVar6 = uVar6 + 0xc;
        } while (uVar5 < uVar2);
      }
      os_free_mem(iVar7);
    }
    iVar8 = iVar8 + 1;
  } while (iVar8 != 4);
  return;
}

