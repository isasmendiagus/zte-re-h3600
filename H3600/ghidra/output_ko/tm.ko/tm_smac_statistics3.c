// module: tm.ko
// function: tm_smac_statistics3 @ 0x4aff4
// size: 416 bytes
//

undefined4 tm_smac_statistics3(undefined4 *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  undefined4 local_1c [2];
  
  local_1c[0] = 0;
  smac_get_statistics(*param_1,0x33,local_1c);
  param_1[3] = 0;
  param_1[2] = local_1c[0];
  smac_get_statistics(*param_1,0x34,local_1c);
  param_1[5] = 0;
  param_1[4] = local_1c[0];
  smac_get_statistics(*param_1,0x35,local_1c);
  param_1[7] = 0;
  param_1[6] = local_1c[0];
  smac_get_statistics(*param_1,0x36,local_1c);
  param_1[9] = 0;
  param_1[8] = local_1c[0];
  smac_get_statistics(*param_1,0x37,local_1c);
  param_1[0xb] = 0;
  param_1[10] = local_1c[0];
  smac_get_statistics(*param_1,0x38,local_1c);
  param_1[0xd] = 0;
  param_1[0xc] = local_1c[0];
  iVar1 = smac_get_statistics(*param_1,0x13,local_1c);
  param_1[0xf] = 0;
  param_1[0xe] = local_1c[0];
  iVar2 = smac_get_statistics(*param_1,0x14,local_1c);
  param_1[0x11] = 0;
  param_1[0x10] = local_1c[0];
  iVar3 = smac_get_statistics(*param_1,0x15,local_1c);
  param_1[0x13] = 0;
  param_1[0x12] = local_1c[0];
  iVar4 = smac_get_statistics(*param_1,0x16,local_1c);
  param_1[0x15] = 0;
  param_1[0x14] = local_1c[0];
  iVar5 = smac_get_statistics(*param_1,0x17,local_1c);
  param_1[0x17] = 0;
  param_1[0x16] = local_1c[0];
  iVar6 = smac_get_statistics(*param_1,0x18,local_1c);
  param_1[0x19] = 0;
  param_1[0x18] = local_1c[0];
  uVar7 = 0;
  if (((((iVar2 != 0 || iVar1 != 0) || iVar3 != 0) || iVar4 != 0) || iVar5 != 0) || iVar6 != 0) {
    printk("tm_smac_statistics3 fail\n");
    uVar7 = 0xffffffff;
  }
  return uVar7;
}

