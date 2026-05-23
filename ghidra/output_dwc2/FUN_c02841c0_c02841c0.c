// FUN_c02841c0 @ c02841c0
// matched: dwc2_hcd_init
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_c02841c0(int *param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int *piVar2;
  undefined1 *puVar3;
  undefined4 uVar4;
  undefined4 extraout_r1;
  undefined4 *puVar5;
  int iVar6;
  int *piVar7;
  undefined8 uVar8;
  
  iVar1 = FUN_c026269c();
  if (iVar1 != 0) {
    return -0x13;
  }
  iVar1 = FUN_c0280c78(param_1);
  if (iVar1 != 0) {
    return iVar1;
  }
  DataSynchronizationBarrier(0xf);
  iVar1 = FUN_c00a2ff0(_DAT_c06a7140,0x80d0,*(undefined4 *)(param_1[1] + 0x400));
  param_1[9] = iVar1;
  if (iVar1 == 0) {
    iVar6 = -0xc;
    iVar1 = 0;
    goto LAB_c0284480;
  }
  puVar5 = (undefined4 *)(iVar1 + -4);
  do {
    puVar5 = puVar5 + 1;
    *puVar5 = 0xffffffff;
  } while (puVar5 != (undefined4 *)(iVar1 + 0x60));
  FUN_c0280af8(param_1,param_3);
  if (0 < *(int *)(param_1[9] + 8)) {
    iVar1 = *param_1;
    if (*(int *)(iVar1 + 0xe8) == 0) {
      FUN_c01e9838(iVar1,s_dma_mask_not_set__disabling_DMA_c05bac20);
      *(undefined4 *)(param_1[9] + 8) = 0;
      *(undefined4 *)(param_1[9] + 0xc) = 0;
      if (*(int *)(param_1[9] + 8) < 1) goto LAB_c02842d8;
      iVar1 = *param_1;
    }
    if (iVar1 == 0) {
      puVar5 = &DAT_c06764c4;
    }
    else {
      puVar5 = *(undefined4 **)(iVar1 + 0x10c);
      if (*(undefined4 **)(iVar1 + 0x10c) == (undefined4 *)0x0) {
        puVar5 = &DAT_c06764c4;
      }
    }
    uVar8 = (*(code *)puVar5[0xe])(iVar1,(code *)puVar5[0xe],0xffffffff,0);
    uVar4 = (undefined4)((ulonglong)uVar8 >> 0x20);
    if ((int)uVar8 < 0) {
      FUN_c01e9838(*param_1,s_can_t_set_DMA_mask_c05bac44);
      uVar4 = extraout_r1;
    }
    iVar6 = *param_1;
    iVar1 = FUN_c001124c(iVar6,uVar4,0xffffffff,0);
    if (iVar1 == 0) {
      FUN_c01e9838(*param_1,s_can_t_set_coherent_DMA_mask_c05bac98);
    }
    else {
      *(undefined4 *)(iVar6 + 0xf0) = 0xffffffff;
      *(undefined4 *)(iVar6 + 0xf4) = 0;
    }
  }
LAB_c02842d8:
  iVar1 = *param_1;
  iVar6 = *(int *)(iVar1 + 0x2c);
  if (iVar6 == 0) {
    iVar6 = *(int *)(iVar1 + 8);
  }
  piVar2 = (int *)FUN_c026a3c0(&DAT_c068ef40,iVar1,iVar6);
  if (piVar2 == (int *)0x0) {
    iVar1 = param_1[9];
    iVar6 = -0xc;
  }
  else {
    iVar1 = *(int *)(param_1[9] + 8);
    piVar2[0x54] = (int)param_1;
    if (iVar1 < 1) {
      *(undefined1 *)(piVar2 + 3) = 0;
    }
    *(byte *)(piVar2 + 0x32) = *(byte *)(piVar2 + 0x32) | 0x80;
    param_1[0x1c] = (int)piVar2;
    FUN_c0280f58(param_1);
    iVar6 = FUN_c027e8d4(param_1,1,param_2);
    if (iVar6 == 0) {
      iVar1 = FUN_c002e474(s_Umount_time_mft_mirror_syncing_i_c0596878 + 0x38,0x2000a,1,0,0,
                           &DAT_c05bac58);
      param_1[0x20] = iVar1;
      if (iVar1 == 0) {
        iVar6 = -0xc;
        FUN_c01e9794(*param_1,s_Failed_to_create_workqueue_c05bac60);
      }
      else {
        param_1[0x21] = -0x20;
        param_1[0x24] = (int)FUN_c0282c88;
        param_1[0x22] = (int)(param_1 + 0x22);
        param_1[0x23] = (int)(param_1 + 0x22);
        FUN_c005744c(param_1 + 0x25,0,0,0);
        param_1[0x32] = (int)(param_1 + 0x32);
        param_1[0x33] = (int)(param_1 + 0x32);
        param_1[0x37] = (int)(param_1 + 0x37);
        param_1[0x38] = (int)(param_1 + 0x37);
        param_1[0x29] = (int)FUN_c0281fb8;
        param_1[0x2a] = (int)param_1;
        param_1[0x34] = (int)(param_1 + 0x34);
        param_1[0x35] = (int)(param_1 + 0x34);
        param_1[0x39] = (int)(param_1 + 0x39);
        param_1[0x3a] = (int)(param_1 + 0x39);
        param_1[0x3b] = (int)(param_1 + 0x3b);
        param_1[0x3c] = (int)(param_1 + 0x3b);
        param_1[0x3d] = (int)(param_1 + 0x3d);
        param_1[0x3e] = (int)(param_1 + 0x3d);
        param_1[0x45] = (int)(param_1 + 0x45);
        param_1[0x46] = (int)(param_1 + 0x45);
        iVar1 = *(int *)(param_1[9] + 0x30);
        FUN_c0181880(param_1 + 0x4a,0x40);
        if (0 < iVar1) {
          piVar7 = param_1 + 0x49;
          iVar6 = 0;
          do {
            puVar3 = (undefined1 *)FUN_c00a2ff0(_DAT_c06a7128,0x80d0);
            if (puVar3 == (undefined1 *)0x0) goto LAB_c0284460;
            *puVar3 = (char)iVar6;
            iVar6 = iVar6 + 1;
            piVar7 = piVar7 + 1;
            *piVar7 = (int)puVar3;
          } while (iVar6 != iVar1);
        }
        if (0 < *(int *)(param_1[9] + 0x60)) {
          FUN_c0286ccc(param_1);
        }
        param_1[0x5f] = (int)&LAB_c0282194;
        param_1[0x5c] = -0x20;
        param_1[0x5d] = (int)(param_1 + 0x5d);
        param_1[0x5e] = (int)(param_1 + 0x5d);
        FUN_c005744c(param_1 + 0x60,2,0,0);
        param_1[0x6c] = (int)FUN_c0281788;
        param_1[0x65] = (int)(param_1 + 0x5c);
        param_1[0x69] = -0x20;
        param_1[100] = (int)&LAB_c002a240;
        param_1[0x6a] = (int)(param_1 + 0x6a);
        param_1[0x6b] = (int)(param_1 + 0x6a);
        FUN_c005744c(param_1 + 0x6d,2,0,0);
        param_1[0x71] = (int)&LAB_c002a240;
        param_1[0x72] = (int)(param_1 + 0x69);
        if (*(int *)(param_1[9] + 8) < 1) {
          iVar1 = FUN_c00a2ff0(_DAT_c06a713c,0x80d0);
          param_1[0x5a] = iVar1;
        }
        else {
          iVar1 = *param_1;
          if ((iVar1 == 0) ||
             (puVar5 = *(undefined4 **)(iVar1 + 0x10c), puVar5 == (undefined4 *)0x0)) {
            puVar5 = &DAT_c06764c4;
          }
          iVar1 = (*(code *)*puVar5)(iVar1,0x40,param_1 + 0x5b,0xd0,0);
          param_1[0x5a] = iVar1;
        }
        if (iVar1 == 0) {
LAB_c0284460:
          iVar6 = -0xc;
        }
        else {
          param_1[0x77] = 0;
          *(undefined1 *)(param_1 + 0x76) = 1;
          param_1[0x78] = 0;
          *(undefined2 *)(param_1 + 0x44) = 0;
          param_1[0x2c] = 3;
          *(undefined1 *)((int)piVar2 + 0xe) = 1;
          piVar2[4] = 0;
          iVar6 = FUN_c026ab00(piVar2,param_2,0x80);
          if (-1 < iVar6) {
            *(byte *)(*piVar2 + 0x68) = *(byte *)(*piVar2 + 0x68) | 1;
            FUN_c0280f18(param_1);
            return 0;
          }
        }
        FUN_c027edd8(param_1);
        FUN_c0283ff0(param_1);
      }
    }
    FUN_c026a1e4(piVar2);
    iVar1 = param_1[9];
  }
LAB_c0284480:
  FUN_c00a35dc(iVar1);
  FUN_c01e9794(*param_1,s__s___FAILED__returning__d_c05bac7c,DAT_c02846b0,iVar6);
  return iVar6;
}

