// module: tm.ko
// function: zte_api_sw_port_get_port_statistics4 @ 0x62e2c
// size: 380 bytes
//

undefined4 zte_api_sw_port_get_port_statistics4(int param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  int local_78 [2];
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
  
  __memzero(local_78,0x58);
  local_78[0] = param_1;
  iVar1 = tm_smac_statistics4(local_78);
  if (iVar1 == 0) {
    param_1 = param_1 * 0x50;
    *param_2 = local_70;
    param_2[1] = uStack_6c;
    param_2[2] = local_68;
    param_2[3] = uStack_64;
    param_2[4] = local_60;
    param_2[5] = uStack_5c;
    param_2[6] = local_58;
    param_2[7] = uStack_54;
    param_2[8] = local_50;
    param_2[9] = uStack_4c;
    param_2[10] = local_48;
    param_2[0xb] = uStack_44;
    param_2[0xc] = local_40;
    param_2[0xd] = uStack_3c;
    param_2[0xe] = local_38;
    param_2[0xf] = uStack_34;
    param_2[0x10] = local_30;
    param_2[0x11] = uStack_2c;
    param_2[0x12] = local_28;
    param_2[0x13] = uStack_24;
    sw_get_pm_overflow(param_2,port_stat4_last + param_1,port_stat4_total + param_1);
    sw_get_pm_overflow(param_2 + 2,param_1 + 0xd7e80,param_1 + 0xd8100);
    sw_get_pm_overflow(param_2 + 4,param_1 + 0xd7e88,param_1 + 0xd8108);
    sw_get_pm_overflow(param_2 + 6,param_1 + 0xd7e90,param_1 + 0xd8110);
    sw_get_pm_overflow(param_2 + 8,param_1 + 0xd7e98,param_1 + 0xd8118);
    sw_get_pm_overflow(param_2 + 10,param_1 + 0xd7ea0,param_1 + 0xd8120);
    sw_get_pm_overflow(param_2 + 0xc,param_1 + 0xd7ea8,param_1 + 0xd8128);
    sw_get_pm_overflow(param_2 + 0xe,param_1 + 0xd7eb0,param_1 + 0xd8130);
    sw_get_pm_overflow(param_2 + 0x10,param_1 + 0xd7eb8,param_1 + 0xd8138);
    sw_get_pm_overflow(param_2 + 0x12,param_1 + 0xd7ec0,param_1 + 0xd8140);
    uVar2 = 0;
  }
  else {
    printk("[%s] L%d tm sdk failed!\n","zte_api_sw_port_get_port_statistics4",0xb47);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

