// module: tm.ko
// function: tm_smac_statistics2 @ 0x4ae80
// size: 372 bytes
//

undefined4 tm_smac_statistics2(undefined4 *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  undefined4 local_160;
  undefined4 local_15c;
  undefined4 local_158;
  undefined4 local_154;
  undefined1 auStack_150 [16];
  undefined1 auStack_140 [24];
  undefined1 auStack_128 [28];
  undefined4 local_10c;
  undefined4 local_f0;
  undefined4 uStack_ec;
  undefined1 auStack_88 [40];
  undefined4 local_60;
  undefined4 uStack_5c;
  undefined4 local_28;
  undefined4 uStack_24;
  
  local_160 = 0;
  local_15c = 0;
  local_158 = 0;
  local_154 = 0;
  __memzero(auStack_140,0x18);
  __memzero(auStack_150,0x10);
  __memzero(&local_f0,0x68);
  __memzero(auStack_88,0x68);
  __memzero(auStack_128,0x38);
  iVar1 = smac_get_statistics(*param_1,0x31,&local_160);
  param_1[3] = 0;
  param_1[2] = local_160;
  iVar2 = smac_get_statistics(*param_1,0x32,&local_160);
  param_1[5] = 0;
  param_1[4] = local_160;
  iVar3 = smac_get_statistics(*param_1,0x2f,&local_160);
  param_1[7] = 0;
  param_1[6] = local_160;
  iVar4 = smac_get_statistics(*param_1,0x30,&local_160);
  param_1[9] = 0;
  param_1[0xf] = 0;
  param_1[0x10] = 0;
  param_1[0x11] = 0;
  param_1[8] = local_160;
  param_1[0xe] = local_10c;
  param_1[10] = local_60;
  param_1[0xb] = uStack_5c;
  param_1[0xc] = local_28;
  param_1[0xd] = uStack_24;
  iVar5 = smac_get_statistics(*param_1,0x26,&local_160);
  param_1[0x13] = 0;
  param_1[0x12] = local_160;
  iVar6 = smac_get_statistics(*param_1,0x3c,&local_160);
  param_1[0x15] = 0;
  param_1[0x14] = local_160;
  param_1[0x16] = local_f0;
  param_1[0x17] = uStack_ec;
  uVar7 = 0;
  if (((((iVar2 != 0 || iVar1 != 0) || iVar3 != 0) || iVar4 != 0) || iVar5 != 0) || iVar6 != 0) {
    printk("tm_smac_statistics2 fail\n");
    uVar7 = 0xffffffff;
  }
  return uVar7;
}

