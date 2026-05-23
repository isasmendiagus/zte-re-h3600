// module: switch.ko
// function: sw_port_get_port_statistics3 @ 0x15b94
// size: 612 bytes
//

undefined4 sw_port_get_port_statistics3(int *param_1)

{
  code cVar1;
  uint uVar2;
  int iVar3;
  undefined4 extraout_r1;
  undefined4 extraout_r1_00;
  undefined4 extraout_r1_01;
  undefined4 extraout_r1_02;
  undefined4 extraout_r1_03;
  undefined4 uVar4;
  undefined4 extraout_r1_04;
  undefined4 extraout_r1_05;
  undefined4 extraout_r1_06;
  undefined4 extraout_r1_07;
  undefined4 extraout_r1_08;
  undefined4 extraout_r1_09;
  int local_80;
  int iStack_7c;
  int local_78;
  int iStack_74;
  int local_70;
  int iStack_6c;
  int local_68;
  int iStack_64;
  int local_60;
  int iStack_5c;
  int local_58;
  int iStack_54;
  int local_50;
  int iStack_4c;
  int local_48;
  int iStack_44;
  int local_40;
  int iStack_3c;
  int local_38;
  int iStack_34;
  int local_30;
  int iStack_2c;
  int local_28;
  int iStack_24;
  
  __memzero(&local_80,0x60);
  cVar1 = zte_api_sw_mac_set_port_macfiltermode[*param_1];
  if (2 < g_switch_debug_level) {
    printk("[%s] input: port=%d\n","sw_port_get_port_statistics3",cVar1);
  }
  iVar3 = zte_api_sw_port_get_port_statistics3(cVar1,&local_80);
  uVar2 = g_switch_debug_level;
  if (iVar3 != 0) {
    printk("[%s] L%d tm sdk failed!\n","sw_port_get_port_statistics3",0xe1);
    return 0xffffffff;
  }
  param_1[4] = local_78;
  param_1[5] = iStack_74;
  param_1[6] = local_70;
  param_1[7] = iStack_6c;
  param_1[10] = local_60;
  param_1[0xb] = iStack_5c;
  param_1[8] = local_68;
  param_1[9] = iStack_64;
  param_1[0xe] = local_50;
  param_1[0xf] = iStack_4c;
  param_1[0xc] = local_58;
  param_1[0xd] = iStack_54;
  param_1[0x10] = local_48;
  param_1[0x11] = iStack_44;
  param_1[2] = local_80;
  param_1[3] = iStack_7c;
  param_1[0x12] = local_40;
  param_1[0x13] = iStack_3c;
  param_1[0x14] = local_38;
  param_1[0x15] = iStack_34;
  param_1[0x18] = local_28;
  param_1[0x19] = iStack_24;
  param_1[0x16] = local_30;
  param_1[0x17] = iStack_2c;
  if (uVar2 < 3) {
    return 0;
  }
  printk("in64 = %lld\n");
  uVar4 = extraout_r1;
  if (g_switch_debug_level < 3) {
LAB_00015cfc:
    if (2 < g_switch_debug_level) {
      printk("in1024tomax = %lld\n",uVar4,local_58,iStack_54);
      if (g_switch_debug_level < 3) {
        return 0;
      }
      printk("out64 = %lld\n",extraout_r1_04,local_50,iStack_4c);
      uVar4 = extraout_r1_05;
      goto LAB_00015d3c;
    }
  }
  else {
    printk("in65to127 = %lld\n",extraout_r1,local_78,iStack_74);
    if (g_switch_debug_level < 3) {
      return 0;
    }
    printk("in128to255 = %lld\n",extraout_r1_00,local_70,iStack_6c);
    uVar4 = extraout_r1_01;
    if (2 < g_switch_debug_level) {
      printk("in256to511 = %lld\n",extraout_r1_01,local_68,iStack_64);
      if (g_switch_debug_level < 3) {
        return 0;
      }
      printk("in512to1023 = %lld\n",extraout_r1_02,local_60,iStack_5c);
      uVar4 = extraout_r1_03;
      goto LAB_00015cfc;
    }
LAB_00015d3c:
    if (g_switch_debug_level < 3) goto LAB_00015dbc;
    printk("out65to127 = %lld\n",uVar4,local_48,iStack_44);
    if (g_switch_debug_level < 3) {
      return 0;
    }
    printk("out128to255 = %lld\n",extraout_r1_06,local_40,iStack_3c);
    uVar4 = extraout_r1_07;
  }
  if (g_switch_debug_level < 3) {
    return 0;
  }
  printk("out256to511 = %lld\n",uVar4,local_38,iStack_34);
  if (g_switch_debug_level < 3) {
    return 0;
  }
  printk("out512to1024 = %lld\n",extraout_r1_08,local_30,iStack_2c);
  uVar4 = extraout_r1_09;
LAB_00015dbc:
  if (2 < g_switch_debug_level) {
    printk("out1024tomax = %lld\n",uVar4,local_28,iStack_24);
  }
  return 0;
}

