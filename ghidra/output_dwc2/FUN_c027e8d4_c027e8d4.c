// FUN_c027e8d4 @ c027e8d4
// matched: FS PHY selected at HS!, dwc2_core_init
//

int FUN_c027e8d4(undefined4 *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  
  DataSynchronizationBarrier(0xf);
  uVar4 = *(uint *)(param_1[1] + 0xc) & 0xffefffff;
  if (*(int *)(param_1[9] + 0x40) == 1) {
    uVar4 = uVar4 | 0x100000;
  }
  uVar4 = uVar4 & 0xffbfffff;
  if (0 < *(int *)(param_1[9] + 0x54)) {
    uVar4 = uVar4 | 0x400000;
  }
  DataSynchronizationBarrier(0xe);
  if (DAT_c066d2b8 != (code *)0x0) {
    (*DAT_c066d2b8)();
  }
  *(uint *)(param_1[1] + 0xc) = uVar4;
  iVar1 = FUN_c027e728(param_1);
  if (iVar1 != 0) {
    FUN_c01e9794(*param_1,s__s____Reset_failed__aborting_c05b9f30,DAT_c027ed4c);
    return iVar1;
  }
  if ((*(int *)(param_1[9] + 0x10) == 1) && (*(int *)(param_1[9] + 0x34) == 0)) {
    if (param_2 != 0) {
      uVar4 = *(uint *)(param_1[1] + 0xc);
      DataSynchronizationBarrier(0xf);
      DataSynchronizationBarrier(0xe);
      if (DAT_c066d2b8 != (code *)0x0) {
        (*DAT_c066d2b8)();
      }
      *(uint *)(param_1[1] + 0xc) = uVar4 | 0x40;
      iVar1 = FUN_c027e728(param_1);
      if (iVar1 != 0) {
        FUN_c01e9794(*param_1,s__s___Reset_failed__aborting_c05b9f50,DAT_c027ed48);
        return iVar1;
      }
    }
    DataSynchronizationBarrier(0xf);
    if ((*(uint *)(param_1[1] + 0x14) & 1) != 0) {
      FUN_c027e524(param_1);
    }
    if (0 < *(int *)(param_1[9] + 0x44)) {
      uVar4 = *(uint *)(param_1[1] + 0xc);
      DataSynchronizationBarrier(0xf);
      DataSynchronizationBarrier(0xe);
      if (DAT_c066d2b8 != (code *)0x0) {
        (*DAT_c066d2b8)();
      }
      *(uint *)(param_1[1] + 0xc) = uVar4 | 0x10000;
      DataSynchronizationBarrier(0xf);
      uVar4 = *(uint *)(param_1[1] + 0x30) & 0xf37fffff;
      DataSynchronizationBarrier(0xe);
      if (DAT_c066d2b8 != (code *)0x0) {
        (*DAT_c066d2b8)();
      }
      *(uint *)(param_1[1] + 0x30) = uVar4 | 0x4000000;
      DataSynchronizationBarrier(0xe);
      if (DAT_c066d2b8 != (code *)0x0) {
        (*DAT_c066d2b8)();
      }
      *(uint *)(param_1[1] + 0x30) = uVar4 | 0x4800000;
    }
  }
  else if (param_2 != 0) {
    uVar4 = *(uint *)(param_1[1] + 0xc);
    DataSynchronizationBarrier(0xf);
    iVar1 = param_1[9];
    iVar2 = *(int *)(iVar1 + 0x34);
    if (iVar2 == 1) {
      uVar4 = uVar4 & 0xffffffe7;
      if (*(int *)(iVar1 + 0x38) == 0x10) {
        uVar4 = uVar4 | 8;
      }
    }
    else if (iVar2 == 2) {
      if (*(int *)(iVar1 + 0x3c) < 1) {
        uVar4 = uVar4 & 0xffffff77 | 0x10;
      }
      else {
        uVar4 = uVar4 & 0xffffff77 | 0x90;
      }
    }
    else {
      FUN_c01e9794(*param_1,s_FS_PHY_selected_at_HS__c05b9f6c,iVar1,iVar2,param_4);
    }
    DataSynchronizationBarrier(0xe);
    if (DAT_c066d2b8 != (code *)0x0) {
      (*DAT_c066d2b8)();
    }
    *(uint *)(param_1[1] + 0xc) = uVar4;
    iVar1 = FUN_c027e728(param_1);
    if (iVar1 != 0) {
      FUN_c01e9794(*param_1,s__s___Reset_failed__aborting_c05b9f50,DAT_c027ed44);
      return iVar1;
    }
  }
  if (((*(byte *)((int)param_1 + 0x1a) & 0xf) == 6) && (0 < *(int *)(param_1[9] + 0x48))) {
    DataSynchronizationBarrier(0xf);
    uVar4 = *(uint *)(param_1[1] + 0xc) | 0xa0000;
    DataSynchronizationBarrier(0xe);
  }
  else {
    DataSynchronizationBarrier(0xf);
    uVar4 = *(uint *)(param_1[1] + 0xc) & 0xfff5ffff;
    DataSynchronizationBarrier(0xe);
  }
  if (DAT_c066d2b8 != (code *)0x0) {
    (*DAT_c066d2b8)();
  }
  *(uint *)(param_1[1] + 0xc) = uVar4;
  uVar5 = *(uint *)(param_1[1] + 8);
  DataSynchronizationBarrier(0xf);
  uVar4 = ((uint)*(byte *)(param_1 + 2) << 0x1b) >> 0x1e;
  if (uVar4 == 1) {
    FUN_c01e9794(*param_1,s_External_DMA_Mode_not_supported_c05b9f84);
    return -0x16;
  }
  iVar1 = param_1[9];
  if ((uVar4 == 2) && (*(uint *)(iVar1 + 0x5c) != 0xffffffff)) {
    uVar5 = uVar5 & 0x1a1 | *(uint *)(iVar1 + 0x5c) & 0xfffffe5e;
  }
  if ((0 < *(int *)(iVar1 + 8)) || (*(undefined4 *)(iVar1 + 0xc) = 0, 0 < *(int *)(param_1[9] + 8)))
  {
    uVar5 = uVar5 | 0x20;
  }
  DataSynchronizationBarrier(0xe);
  if (DAT_c066d2b8 != (code *)0x0) {
    (*DAT_c066d2b8)();
  }
  *(uint *)(param_1[1] + 8) = uVar5;
  DataSynchronizationBarrier(0xf);
  uVar4 = *(uint *)(param_1[1] + 0xc) & 0xfffffcff;
  switch(*(byte *)(param_1 + 2) & 7) {
  case 0:
    iVar1 = *(int *)param_1[9];
    if (iVar1 != 0) goto LAB_c027ec08;
    uVar4 = uVar4 | 0x200;
    break;
  case 1:
  case 3:
  case 5:
    iVar1 = *(int *)param_1[9];
LAB_c027ec08:
    if (iVar1 == 2) goto switchD_c027eb8c_caseD_2;
    break;
  default:
    goto switchD_c027eb8c_caseD_2;
  }
  uVar4 = uVar4 | 0x100;
switchD_c027eb8c_caseD_2:
  DataSynchronizationBarrier(0xe);
  if (DAT_c066d2b8 != (code *)0x0) {
    (*DAT_c066d2b8)();
  }
  *(uint *)(param_1[1] + 0xc) = uVar4;
  DataSynchronizationBarrier(0xf);
  uVar4 = *(uint *)param_1[1] & 0xffefffff;
  if (0 < *(int *)(param_1[9] + 4)) {
    uVar4 = uVar4 | 0x100000;
  }
  DataSynchronizationBarrier(0xe);
  if (DAT_c066d2b8 != (code *)0x0) {
    (*DAT_c066d2b8)();
  }
  *(uint *)param_1[1] = uVar4;
  *(byte *)(param_1 + 0x1f) = *(byte *)(param_1 + 0x1f) & 0xfd;
  FUN_c027e490(param_1);
  DataSynchronizationBarrier(0xf);
  if ((*(uint *)(param_1[1] + 0x14) & 1) == 0) {
    uVar3 = 3;
  }
  else {
    uVar3 = 9;
  }
  param_1[10] = uVar3;
  return 0;
}

