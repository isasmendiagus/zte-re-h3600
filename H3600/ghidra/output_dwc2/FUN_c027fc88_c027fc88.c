// FUN_c027fc88 @ c027fc88
// matched: Hardware does not support descriptor DMA mode
//

void FUN_c027fc88(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  byte bVar1;
  ushort uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  bool bVar10;
  
  DataSynchronizationBarrier(0xe);
  if (DAT_c066d2b8 != (code *)0x0) {
    (*DAT_c066d2b8)();
  }
  *(undefined4 *)(param_1[1] + 0xe00) = 0;
  FUN_c027e524(param_1);
  iVar5 = param_1[9];
  if (*(int *)(iVar5 + 0x10) == 1) {
    uVar6 = *(uint *)(param_1[1] + 0x400);
    DataSynchronizationBarrier(0xf);
    DataSynchronizationBarrier(0xe);
    if (DAT_c066d2b8 != (code *)0x0) {
      (*DAT_c066d2b8)();
    }
    *(uint *)(param_1[1] + 0x400) = uVar6 | 4;
    iVar5 = param_1[9];
  }
  if (0 < *(int *)(iVar5 + 0x58)) {
    uVar6 = *(uint *)(param_1[1] + 0x404);
    DataSynchronizationBarrier(0xf);
    DataSynchronizationBarrier(0xe);
    if (DAT_c066d2b8 != (code *)0x0) {
      (*DAT_c066d2b8)();
    }
    *(uint *)(param_1[1] + 0x404) = uVar6 | 0x10000;
    iVar5 = param_1[9];
  }
  if (0 < *(int *)(iVar5 + 0xc)) {
    uVar6 = (uint)*(byte *)(param_1 + 2);
    uVar3 = uVar6 & 7;
    if ((0x4f542909 < (uint)param_1[8]) && ((*(byte *)(param_1 + 2) & 0x20) != 0)) {
      uVar6 = uVar3 - 3;
      bVar10 = 6 < uVar3;
      if (uVar3 != 7) {
        bVar10 = uVar6 != 0;
      }
      if (bVar10 && (uVar3 != 7 && uVar6 != 1)) {
        uVar6 = *(uint *)(param_1[1] + 0x400);
        DataSynchronizationBarrier(0xf);
        DataSynchronizationBarrier(0xe);
        if (DAT_c066d2b8 != (code *)0x0) {
          (*DAT_c066d2b8)();
        }
        *(uint *)(param_1[1] + 0x400) = uVar6 | 0x800000;
        iVar5 = param_1[9];
        iVar4 = *(int *)(iVar5 + 0x14);
        goto joined_r0xc027fe54;
      }
    }
    FUN_c01e9794(*param_1,s_Hardware_does_not_support_descri_c05ba030,uVar6,uVar3,param_4);
    FUN_c01e9794(*param_1,s_falling_back_to_buffer_DMA_mode__c05ba064);
    *(undefined4 *)(param_1[9] + 0xc) = 0;
    iVar5 = param_1[9];
  }
  iVar4 = *(int *)(iVar5 + 0x14);
joined_r0xc027fe54:
  if (iVar4 != 0) {
    uVar2 = *(ushort *)(param_1 + 7);
    if ((uint)uVar2 <
        (uint)(*(int *)(iVar5 + 0x20) + *(int *)(iVar5 + 0x1c) + *(int *)(iVar5 + 0x24))) {
      bVar1 = *(byte *)((int)param_1 + 0x19);
      *(undefined4 *)(iVar5 + 0x20) = 0x100;
      *(undefined4 *)(iVar5 + 0x24) = 0x300;
      uVar6 = (uint)(bVar1 >> 3);
      *(uint *)(iVar5 + 0x1c) = uVar6 + 0x204;
      if ((uint)uVar2 < uVar6 + 0x604) {
        FUN_c01e9794(*param_1,s_invalid_fifo_sizes_c05ba088);
      }
    }
    uVar6 = *(uint *)(param_1[1] + 0x24);
    DataSynchronizationBarrier(0xf);
    uVar2 = *(ushort *)(iVar5 + 0x1c);
    DataSynchronizationBarrier(0xe);
    if (DAT_c066d2b8 != (code *)0x0) {
      (*DAT_c066d2b8)();
    }
    *(uint *)(param_1[1] + 0x24) = uVar6 & 0xffff0000 | (uint)uVar2;
    iVar4 = *(int *)(iVar5 + 0x20);
    uVar2 = *(ushort *)(iVar5 + 0x1c);
    DataSynchronizationBarrier(0xe);
    if (DAT_c066d2b8 != (code *)0x0) {
      (*DAT_c066d2b8)();
    }
    *(uint *)(param_1[1] + 0x28) = (uint)uVar2 | iVar4 << 0x10;
    iVar8 = *(int *)(iVar5 + 0x1c);
    iVar4 = *(int *)(iVar5 + 0x20);
    iVar7 = *(int *)(iVar5 + 0x24);
    DataSynchronizationBarrier(0xe);
    if (DAT_c066d2b8 != (code *)0x0) {
      (*DAT_c066d2b8)();
    }
    *(uint *)(param_1[1] + 0x100) = iVar8 + iVar4 & 0xffffU | iVar7 << 0x10;
    if ((0 < *(int *)(param_1[9] + 0x18)) && ((uint)param_1[8] < 0x4f54294b)) {
      uVar6 = *(uint *)(param_1[1] + 0x5c);
      DataSynchronizationBarrier(0xf);
      iVar8 = *(int *)(iVar5 + 0x1c);
      iVar4 = *(int *)(iVar5 + 0x20);
      iVar5 = *(int *)(iVar5 + 0x24);
      DataSynchronizationBarrier(0xe);
      if (DAT_c066d2b8 != (code *)0x0) {
        (*DAT_c066d2b8)();
      }
      *(uint *)(param_1[1] + 0x5c) = uVar6 & 0xffff | (iVar8 + iVar4 + iVar5) * 0x10000;
    }
  }
  uVar6 = *(uint *)param_1[1];
  DataSynchronizationBarrier(0xf);
  DataSynchronizationBarrier(0xe);
  if (DAT_c066d2b8 != (code *)0x0) {
    (*DAT_c066d2b8)();
  }
  *(uint *)param_1[1] = uVar6 & 0xfffffbff;
  FUN_c027fb34(param_1,0x10);
  FUN_c027fbec(param_1);
  uVar6 = *(uint *)param_1[1];
  DataSynchronizationBarrier(0xf);
  DataSynchronizationBarrier(0xe);
  if (DAT_c066d2b8 != (code *)0x0) {
    (*DAT_c066d2b8)();
  }
  *(uint *)param_1[1] = uVar6 & 0xfffffbff;
  if ((*(int *)(param_1[9] + 0xc) < 1) && (iVar5 = *(int *)(param_1[9] + 0x30), 0 < iVar5)) {
    iVar4 = 0x500;
    iVar8 = 0;
    do {
      uVar6 = *(uint *)(param_1[1] + iVar4);
      DataSynchronizationBarrier(0xf);
      DataSynchronizationBarrier(0xe);
      if (DAT_c066d2b8 != (code *)0x0) {
        (*DAT_c066d2b8)();
      }
      *(uint *)(param_1[1] + iVar4) = uVar6 & 0x7fff7fff | 0x40000000;
      iVar8 = iVar8 + 1;
      iVar4 = iVar4 + 0x20;
    } while (iVar8 != iVar5);
    iVar8 = 0x500;
    iVar4 = 0;
LAB_c0280060:
    do {
      uVar6 = *(uint *)(param_1[1] + iVar8);
      DataSynchronizationBarrier(0xf);
      DataSynchronizationBarrier(0xe);
      if (DAT_c066d2b8 != (code *)0x0) {
        (*DAT_c066d2b8)();
      }
      *(uint *)(param_1[1] + iVar8) = uVar6 & 0xffff7fff | 0xc0000000;
      iVar7 = 0x3e9;
      do {
        iVar9 = *(int *)(param_1[1] + iVar8);
        DataSynchronizationBarrier(0xf);
        iVar7 = iVar7 + -1;
        if (iVar7 == 0) {
          iVar7 = iVar4 + 1;
          FUN_c01e9794(*param_1,s_Unable_to_clear_enable_on_channe_c05ba09c,iVar4);
          iVar8 = iVar8 + 0x20;
          iVar4 = iVar7;
          if (iVar7 == iVar5) goto LAB_c027fdf4;
          goto LAB_c0280060;
        }
        (*DAT_c068531c)(0x1a36e);
      } while (iVar9 < 0);
      iVar4 = iVar4 + 1;
      iVar8 = iVar8 + 0x20;
    } while (iVar4 != iVar5);
  }
LAB_c027fdf4:
  if (param_1[10] == 9) {
    uVar6 = *(uint *)(param_1[1] + 0x440);
    DataSynchronizationBarrier(0xf);
    if ((uVar6 & 0x1000) == 0) {
      DataSynchronizationBarrier(0xe);
      if (DAT_c066d2b8 != (code *)0x0) {
        (*DAT_c066d2b8)();
      }
      *(uint *)(param_1[1] + 0x440) = uVar6 & 0xffffffd1 | 0x1000;
    }
  }
  DataSynchronizationBarrier(0xe);
  if (DAT_c066d2b8 != (code *)0x0) {
    (*DAT_c066d2b8)();
  }
  *(undefined4 *)(param_1[1] + 0x18) = 0;
  DataSynchronizationBarrier(0xe);
  if (DAT_c066d2b8 != (code *)0x0) {
    (*DAT_c066d2b8)();
  }
  *(undefined4 *)(param_1[1] + 0x418) = 0;
  FUN_c027e490(param_1);
  uVar6 = *(uint *)(param_1[1] + 0x18);
  DataSynchronizationBarrier(0xf);
  DataSynchronizationBarrier(0xe);
  if (DAT_c066d2b8 != (code *)0x0) {
    (*DAT_c066d2b8)();
  }
  *(uint *)(param_1[1] + 0x18) = uVar6 | 0x23000000;
  return;
}

