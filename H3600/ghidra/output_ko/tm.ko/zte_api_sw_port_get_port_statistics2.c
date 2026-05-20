// module: tm.ko
// function: zte_api_sw_port_get_port_statistics2 @ 0x62b00
// size: 356 bytes
//

undefined4 zte_api_sw_port_get_port_statistics2(int param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  int local_80 [2];
  undefined4 local_78;
  undefined4 uStack_74;
  undefined4 local_70;
  undefined4 uStack_6c;
  undefined4 local_68;
  undefined4 uStack_64;
  undefined4 local_60;
  undefined4 uStack_5c;
  undefined4 local_48;
  undefined4 uStack_44;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 local_28;
  undefined4 uStack_24;
  
  __memzero(local_80,0x60);
  local_80[0] = param_1;
  iVar1 = tm_smac_statistics2(local_80);
  if (iVar1 == 0) {
    *param_2 = local_78;
    param_2[1] = uStack_74;
    param_1 = param_1 * 0x58;
    param_2[2] = local_70;
    param_2[3] = uStack_6c;
    param_2[4] = local_68;
    param_2[5] = uStack_64;
    param_2[6] = local_60;
    param_2[7] = uStack_5c;
    param_2[0xc] = local_48;
    param_2[0xd] = uStack_44;
    param_2[0x10] = local_38;
    param_2[0x11] = uStack_34;
    param_2[0x12] = local_30;
    param_2[0x13] = uStack_2c;
    param_2[8] = 0;
    param_2[9] = 0;
    param_2[0x14] = local_28;
    param_2[0x15] = uStack_24;
    param_2[10] = 0;
    param_2[0xb] = 0;
    param_2[0xe] = 0;
    param_2[0xf] = 0;
    sw_get_pm_overflow(param_2,port_stat2_last + param_1,port_stat2_total + param_1);
    sw_get_pm_overflow(param_2 + 2,param_1 + 0xd7300,param_1 + 0xd75c0);
    sw_get_pm_overflow(param_2 + 4,param_1 + 0xd7308,param_1 + 0xd75c8);
    sw_get_pm_overflow(param_2 + 6,param_1 + 0xd7310,param_1 + 0xd75d0);
    sw_get_pm_overflow(param_2 + 0xc,param_1 + 0xd7328,param_1 + 0xd75e8);
    sw_get_pm_overflow(param_2 + 0x10,param_1 + 0xd7338,param_1 + 0xd75f8);
    sw_get_pm_overflow(param_2 + 0x12,param_1 + 0xd7340,param_1 + 0xd7600);
    sw_get_pm_overflow(param_2 + 0x14,param_1 + 0xd7348,param_1 + 0xd7608);
    uVar2 = 0;
  }
  else {
    printk("[%s] L%d tm sdk failed!\n","zte_api_sw_port_get_port_statistics2",0xaf7);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

