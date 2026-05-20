// module: switch.ko
// function: sw_port_get_port_statistics1 @ 0x156d4
// size: 700 bytes
//

undefined4 sw_port_get_port_statistics1(int *param_1)

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
  undefined4 extraout_r1_10;
  undefined4 extraout_r1_11;
  int local_90;
  int iStack_8c;
  int local_88;
  int iStack_84;
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
  
  __memzero(&local_90,0x70);
  cVar1 = zte_api_sw_mac_set_port_macfiltermode[*param_1];
  if (2 < g_switch_debug_level) {
    printk("[%s] input: port=%d\n","sw_port_get_port_statistics1",cVar1);
  }
  iVar3 = zte_api_sw_port_get_port_statistics1(cVar1,&local_90);
  uVar2 = g_switch_debug_level;
  if (iVar3 != 0) {
    printk("[%s] L%d tm sdk failed!\n","sw_port_get_port_statistics1",0x59);
    return 0xffffffff;
  }
  param_1[2] = local_90;
  param_1[3] = iStack_8c;
  param_1[0x12] = local_70;
  param_1[0x13] = iStack_6c;
  param_1[4] = local_88;
  param_1[5] = iStack_84;
  param_1[0xe] = local_80;
  param_1[0xf] = iStack_7c;
  param_1[0x10] = local_78;
  param_1[0x11] = iStack_74;
  param_1[0x14] = local_68;
  param_1[0x15] = iStack_64;
  param_1[0x16] = local_60;
  param_1[0x17] = iStack_5c;
  param_1[0x1a] = local_58;
  param_1[0x1b] = iStack_54;
  param_1[0x1c] = local_50;
  param_1[0x1d] = iStack_4c;
  param_1[0x26] = local_48;
  param_1[0x27] = iStack_44;
  param_1[0x2a] = local_38;
  param_1[0x2b] = iStack_34;
  param_1[0x2c] = local_30;
  param_1[0x2d] = iStack_2c;
  param_1[0x28] = local_40;
  param_1[0x29] = iStack_3c;
  param_1[0x2e] = local_28;
  param_1[0x2f] = iStack_24;
  if (uVar2 < 3) {
    return 0;
  }
  printk("inbytes = %lld\n",iStack_2c,local_90,iStack_8c);
  uVar4 = extraout_r1;
  if (g_switch_debug_level < 3) {
LAB_00015854:
    if (2 < g_switch_debug_level) {
      printk("inerror = %lld\n",uVar4,local_68,iStack_64);
      if (g_switch_debug_level < 3) {
        return 0;
      }
      printk("indiscard = %lld\n",extraout_r1_04,local_60,iStack_5c);
      uVar4 = extraout_r1_05;
      goto LAB_00015894;
    }
LAB_000158d4:
    if (g_switch_debug_level < 3) goto LAB_00015954;
    printk("outunicast = %lld\n",uVar4,local_48,iStack_44);
    if (g_switch_debug_level < 3) {
      return 0;
    }
    printk("outmulticast = %lld\n",extraout_r1_08,local_40,iStack_3c);
    uVar4 = extraout_r1_09;
  }
  else {
    printk("inpkts = %lld\n",extraout_r1,local_88,iStack_84);
    if (g_switch_debug_level < 3) {
      return 0;
    }
    printk("inunicast = %lld\n",extraout_r1_00,local_80,iStack_7c);
    uVar4 = extraout_r1_01;
    if (2 < g_switch_debug_level) {
      printk("inmulticast = %lld\n",extraout_r1_01,local_78,iStack_74);
      if (g_switch_debug_level < 3) {
        return 0;
      }
      printk("inbroadcast = %lld\n",extraout_r1_02,local_70,iStack_6c);
      uVar4 = extraout_r1_03;
      goto LAB_00015854;
    }
LAB_00015894:
    if (2 < g_switch_debug_level) {
      printk("outbytes = %lld\n",uVar4,local_58,iStack_54);
      if (g_switch_debug_level < 3) {
        return 0;
      }
      printk("outpkts = %lld\n",extraout_r1_06,local_50,iStack_4c);
      uVar4 = extraout_r1_07;
      goto LAB_000158d4;
    }
  }
  if (g_switch_debug_level < 3) {
    return 0;
  }
  printk("outbroadcast = %lld\n",uVar4,local_38,iStack_34);
  if (g_switch_debug_level < 3) {
    return 0;
  }
  printk("outerror = %lld\n",extraout_r1_10,local_30,iStack_2c);
  uVar4 = extraout_r1_11;
LAB_00015954:
  if (2 < g_switch_debug_level) {
    printk("outdiscard = %lld\n",uVar4,local_28,iStack_24);
  }
  return 0;
}

