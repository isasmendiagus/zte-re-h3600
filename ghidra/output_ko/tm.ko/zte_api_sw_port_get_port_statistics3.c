// module: tm.ko
// function: zte_api_sw_port_get_port_statistics3 @ 0x62c70
// size: 436 bytes
//

undefined4 zte_api_sw_port_get_port_statistics3(int param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  int local_88 [2];
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
  
  __memzero(local_88,0x68);
  local_88[0] = param_1;
  iVar1 = tm_smac_statistics3(local_88);
  if (iVar1 == 0) {
    param_1 = param_1 * 0x60;
    *param_2 = local_80;
    param_2[1] = uStack_7c;
    param_2[2] = local_78;
    param_2[3] = uStack_74;
    param_2[4] = local_70;
    param_2[5] = uStack_6c;
    param_2[6] = local_68;
    param_2[7] = uStack_64;
    param_2[8] = local_60;
    param_2[9] = uStack_5c;
    param_2[10] = local_58;
    param_2[0xb] = uStack_54;
    param_2[0xc] = local_50;
    param_2[0xd] = uStack_4c;
    param_2[0xe] = local_48;
    param_2[0xf] = uStack_44;
    param_2[0x10] = local_40;
    param_2[0x11] = uStack_3c;
    param_2[0x12] = local_38;
    param_2[0x13] = uStack_34;
    param_2[0x14] = local_30;
    param_2[0x15] = uStack_2c;
    param_2[0x16] = local_28;
    param_2[0x17] = uStack_24;
    sw_get_pm_overflow(param_2,port_stat3_last + param_1,port_stat3_total + param_1);
    sw_get_pm_overflow(param_2 + 2,param_1 + 0xd7880,param_1 + 0xd7b80);
    sw_get_pm_overflow(param_2 + 4,param_1 + 0xd7888,param_1 + 0xd7b88);
    sw_get_pm_overflow(param_2 + 6,param_1 + 0xd7890,param_1 + 0xd7b90);
    sw_get_pm_overflow(param_2 + 8,param_1 + 0xd7898,param_1 + 0xd7b98);
    sw_get_pm_overflow(param_2 + 10,param_1 + 0xd78a0,param_1 + 0xd7ba0);
    sw_get_pm_overflow(param_2 + 0xc,param_1 + 0xd78a8,param_1 + 0xd7ba8);
    sw_get_pm_overflow(param_2 + 0xe,param_1 + 0xd78b0,param_1 + 0xd7bb0);
    sw_get_pm_overflow(param_2 + 0x10,param_1 + 0xd78b8,param_1 + 0xd7bb8);
    sw_get_pm_overflow(param_2 + 0x12,param_1 + 0xd78c0,param_1 + 0xd7bc0);
    sw_get_pm_overflow(param_2 + 0x14,param_1 + 0xd78c8,param_1 + 0xd7bc8);
    sw_get_pm_overflow(param_2 + 0x16,param_1 + 0xd78d0,param_1 + 0xd7bd0);
    uVar2 = 0;
  }
  else {
    printk("[%s] L%d tm sdk failed!\n","zte_api_sw_port_get_port_statistics3",0xb1d);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

