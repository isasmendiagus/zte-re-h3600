// module: tm.ko
// function: tm_smac_statistics4 @ 0x4b194
// size: 312 bytes
//

undefined4 tm_smac_statistics4(undefined4 *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  iVar1 = smac_get_statistics(*param_1,0x21,&local_2c);
  param_1[3] = 0;
  param_1[2] = local_2c;
  iVar2 = smac_get_statistics(*param_1,0x20,&local_2c);
  param_1[5] = 0;
  param_1[4] = local_2c;
  iVar3 = smac_get_statistics(*param_1,0x1d,&local_2c);
  param_1[7] = 0;
  param_1[6] = local_2c;
  iVar4 = smac_get_statistics(*param_1,0x1e,&local_2c);
  param_1[9] = 0;
  param_1[10] = 0;
  param_1[0xb] = 0;
  param_1[8] = local_2c;
  iVar5 = smac_get_statistics(*param_1,0x1f,&local_2c);
  param_1[0xd] = 0;
  param_1[0xe] = 0;
  param_1[0xf] = 0;
  param_1[0xc] = local_2c;
  iVar6 = smac_get_statistics(*param_1,0x22,&local_2c);
  param_1[0x11] = 0;
  param_1[0x10] = local_2c;
  iVar7 = smac_get_statistics(*param_1,0x2e,&local_2c);
  param_1[0x13] = 0;
  param_1[0x14] = 0;
  param_1[0x15] = 0;
  param_1[0x12] = local_2c;
  uVar8 = 0;
  if ((((((iVar2 != 0 || iVar1 != 0) || iVar3 != 0) || iVar4 != 0) || iVar5 != 0) || iVar6 != 0) ||
      iVar7 != 0) {
    printk("tm_smac_statistics4 fail\n");
    uVar8 = 0xffffffff;
  }
  return uVar8;
}

