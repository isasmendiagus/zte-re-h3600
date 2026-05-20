// module: tm.ko
// function: tm_smac_statistics1 @ 0x4abf8
// size: 648 bytes
//

/* WARNING: Type propagation algorithm not settling */

undefined4 tm_smac_statistics1(undefined4 *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  undefined4 uVar16;
  uint uVar17;
  uint uVar18;
  uint local_b4;
  uint local_b0;
  uint local_ac;
  uint local_a8;
  uint local_a4 [2];
  undefined1 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 uStack_84;
  
  local_b4 = 0;
  local_b0 = 0;
  local_ac = 0;
  local_a8 = 0;
  local_a4[0] = 0;
  __memzero(local_a4 + 1);
  __memzero(&local_88,0x68);
  local_94 = *param_1;
  local_90 = 0xffff;
  local_8c = 0xffff;
  local_a4[1] = 1;
  local_98 = 0;
  local_9c = 0;
  iVar1 = smac_get_statistics(local_94,0x29,&local_b4);
  param_1[3] = 0;
  param_1[2] = local_b4;
  iVar2 = smac_get_statistics(*param_1,0x39,&local_b4);
  iVar3 = smac_get_statistics(*param_1,0x2c,&local_b0);
  iVar4 = smac_get_statistics(*param_1,0x2b,&local_ac);
  param_1[6] = local_b4;
  param_1[7] = 0;
  param_1[8] = local_b0;
  param_1[9] = 0;
  param_1[10] = local_ac;
  param_1[0xb] = 0;
  param_1[4] = local_ac + local_b4 + local_b0;
  param_1[5] = (uint)CARRY4(local_b4,local_b0) + (uint)CARRY4(local_ac,local_b4 + local_b0);
  iVar5 = smac_get_statistics(*param_1,0x2d,&local_b4);
  param_1[0xd] = 0;
  param_1[0xe] = local_88;
  param_1[0xf] = uStack_84;
  param_1[0xc] = local_b4;
  iVar6 = smac_get_statistics(*param_1,0x23,&local_b4);
  param_1[0x11] = 0;
  param_1[0x10] = local_b4;
  iVar7 = smac_get_statistics(*param_1,0x24,&local_b4);
  param_1[0x13] = 0;
  param_1[0x12] = local_b4;
  iVar8 = smac_get_statistics(*param_1,0x19,&local_b4);
  iVar9 = smac_get_statistics(*param_1,0x1a,&local_b0);
  iVar10 = smac_get_statistics(*param_1,0x1b,&local_ac);
  param_1[0x15] = 0;
  param_1[0x17] = 0;
  param_1[0x19] = 0;
  param_1[0x1a] = 0;
  param_1[0x1b] = 0;
  param_1[0x16] = local_b0;
  param_1[0x18] = local_ac;
  param_1[0x14] = local_b4;
  iVar11 = smac_get_statistics(*param_1,0x1c,&local_b4);
  iVar12 = smac_get_statistics(*param_1,0x20,&local_b0);
  iVar13 = smac_get_statistics(*param_1,0x21,&local_ac);
  iVar14 = smac_get_statistics(*param_1,0x22,&local_a8);
  iVar15 = smac_get_statistics(*param_1,0x25,local_a4);
  uVar17 = local_b4 + local_b0 + local_ac;
  uVar18 = uVar17 + local_a8;
  param_1[0x1c] = uVar18 + local_a4[0];
  param_1[0x1d] =
       (uint)CARRY4(local_b4,local_b0) + (uint)CARRY4(local_b4 + local_b0,local_ac) +
       (uint)CARRY4(uVar17,local_a8) + (uint)CARRY4(uVar18,local_a4[0]);
  uVar16 = 0;
  if ((((((((((((((iVar2 != 0 || iVar1 != 0) || iVar3 != 0) || iVar4 != 0) || iVar5 != 0) ||
              iVar6 != 0) || iVar7 != 0) || iVar8 != 0) || iVar9 != 0) || iVar10 != 0) ||
         iVar11 != 0) || iVar12 != 0) || iVar13 != 0) || iVar14 != 0) || iVar15 != 0) {
    printk("tm_smac_statistics1 fail\n");
    uVar16 = 0xffffffff;
  }
  return uVar16;
}

