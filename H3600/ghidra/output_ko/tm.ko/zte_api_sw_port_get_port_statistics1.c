// module: tm.ko
// function: zte_api_sw_port_get_port_statistics1 @ 0x6290c
// size: 492 bytes
//

undefined4 zte_api_sw_port_get_port_statistics1(int param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  int local_98 [2];
  undefined4 local_90;
  undefined4 uStack_8c;
  undefined4 local_88;
  undefined4 uStack_84;
  undefined4 local_80;
  undefined4 uStack_7c;
  undefined4 local_78;
  undefined4 uStack_74;
  undefined4 local_70;
  undefined4 uStack_6c;
  undefined4 local_68;
  undefined4 uStack_64;
  undefined4 local_60;
  undefined4 uStack_5c;
  undefined4 local_58;
  undefined4 uStack_54;
  undefined4 local_50;
  undefined4 uStack_4c;
  undefined4 local_48;
  undefined4 uStack_44;
  undefined4 local_40;
  undefined4 uStack_3c;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 local_28;
  undefined4 uStack_24;
  
  __memzero(local_98,0x78);
  local_98[0] = param_1;
  iVar1 = tm_smac_statistics1(local_98);
  if (iVar1 == 0) {
    param_1 = param_1 * 0x70;
    *param_2 = local_90;
    param_2[1] = uStack_8c;
    param_2[2] = local_88;
    param_2[3] = uStack_84;
    param_2[4] = local_80;
    param_2[5] = uStack_7c;
    param_2[6] = local_78;
    param_2[7] = uStack_74;
    param_2[8] = local_70;
    param_2[9] = uStack_6c;
    param_2[10] = local_68;
    param_2[0xb] = uStack_64;
    param_2[0xc] = local_60;
    param_2[0xd] = uStack_5c;
    param_2[0xe] = local_58;
    param_2[0xf] = uStack_54;
    param_2[0x10] = local_50;
    param_2[0x11] = uStack_4c;
    param_2[0x12] = local_48;
    param_2[0x13] = uStack_44;
    param_2[0x14] = local_40;
    param_2[0x15] = uStack_3c;
    param_2[0x16] = local_38;
    param_2[0x17] = uStack_34;
    param_2[0x18] = local_30;
    param_2[0x19] = uStack_2c;
    param_2[0x1a] = local_28;
    param_2[0x1b] = uStack_24;
    sw_get_pm_overflow(param_2,port_stat1_last + param_1,port_stat1_total + param_1);
    sw_get_pm_overflow(param_2 + 2,param_1 + 0xd6c00,param_1 + 0xd6f80);
    sw_get_pm_overflow(param_2 + 4,param_1 + 0xd6c08,param_1 + 0xd6f88);
    sw_get_pm_overflow(param_2 + 6,param_1 + 0xd6c10,param_1 + 0xd6f90);
    sw_get_pm_overflow(param_2 + 8,param_1 + 0xd6c18,param_1 + 0xd6f98);
    sw_get_pm_overflow(param_2 + 10,param_1 + 0xd6c20,param_1 + 0xd6fa0);
    sw_get_pm_overflow(param_2 + 0xc,param_1 + 0xd6c28,param_1 + 0xd6fa8);
    sw_get_pm_overflow(param_2 + 0xe,param_1 + 0xd6c30,param_1 + 0xd6fb0);
    sw_get_pm_overflow(param_2 + 0x10,param_1 + 0xd6c38,param_1 + 0xd6fb8);
    sw_get_pm_overflow(param_2 + 0x12,param_1 + 0xd6c40,param_1 + 0xd6fc0);
    sw_get_pm_overflow(param_2 + 0x14,param_1 + 0xd6c48,param_1 + 0xd6fc8);
    sw_get_pm_overflow(param_2 + 0x16,param_1 + 0xd6c50,param_1 + 0xd6fd0);
    sw_get_pm_overflow(param_2 + 0x18,param_1 + 0xd6c58,param_1 + 0xd6fd8);
    sw_get_pm_overflow(param_2 + 0x1a,param_1 + 0xd6c60,param_1 + 0xd6fe0);
    uVar2 = 0;
  }
  else {
    printk("[%s] L%d tm sdk failed!\n","zte_api_sw_port_get_port_statistics1",0xac9);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

