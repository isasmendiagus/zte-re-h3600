// module: switch.ko
// function: sw_port_get_port_statistics2 @ 0x15998
// size: 500 bytes
//

undefined4 sw_port_get_port_statistics2(int *param_1)

{
  code cVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined4 extraout_r1;
  undefined4 extraout_r1_00;
  undefined4 extraout_r1_01;
  undefined4 extraout_r1_02;
  undefined4 extraout_r1_03;
  undefined4 uVar5;
  undefined4 extraout_r1_04;
  undefined4 extraout_r1_05;
  undefined4 extraout_r1_06;
  int local_78;
  int iStack_74;
  int local_70;
  int iStack_6c;
  int local_68;
  int iStack_64;
  undefined4 local_60;
  undefined4 uStack_5c;
  int local_58;
  int iStack_54;
  int local_50;
  int iStack_4c;
  undefined4 local_40;
  undefined4 uStack_3c;
  int local_38;
  int iStack_34;
  int local_28;
  int iStack_24;
  
  __memzero(&local_78,0x58);
  cVar1 = zte_api_sw_mac_set_port_macfiltermode[*param_1];
  if (2 < g_switch_debug_level) {
    printk("[%s] input: port=%d\n","sw_port_get_port_statistics2",cVar1);
  }
  iVar4 = zte_api_sw_port_get_port_statistics2(cVar1,&local_78);
  iVar2 = g_LinkStateChangeCount;
  if (iVar4 != 0) {
    printk("[%s] L%d tm sdk failed!\n","sw_port_get_port_statistics2",0xb9);
    return 0xffffffff;
  }
  param_1[0x10] = local_58;
  param_1[0x11] = iStack_54;
  uVar3 = g_switch_debug_level;
  param_1[0x1b] = 0;
  param_1[0x1a] = iVar2;
  param_1[6] = local_70;
  param_1[7] = iStack_6c;
  param_1[0x12] = local_50;
  param_1[0x13] = iStack_4c;
  param_1[4] = local_78;
  param_1[5] = iStack_74;
  param_1[0x1c] = local_68;
  param_1[0x1d] = iStack_64;
  param_1[0x18] = local_38;
  param_1[0x19] = iStack_34;
  param_1[0x20] = local_28;
  param_1[0x21] = iStack_24;
  if (uVar3 < 3) {
    return 0;
  }
  printk("inundersize = %lld\n");
  uVar5 = extraout_r1;
  if (2 < g_switch_debug_level) {
    printk("inoversize = %lld\n",extraout_r1,local_70,iStack_6c);
    if (g_switch_debug_level < 3) {
      return 0;
    }
    printk("infragments = %lld\n",extraout_r1_00,local_68,iStack_64);
    uVar5 = extraout_r1_01;
    if (g_switch_debug_level < 3) goto LAB_00015b2c;
    printk("injabbers = %lld\n",extraout_r1_01,local_60,uStack_5c);
    if (g_switch_debug_level < 3) {
      return 0;
    }
    printk("outundersize = %lld\n",extraout_r1_02,local_58,iStack_54);
    uVar5 = extraout_r1_03;
  }
  if (g_switch_debug_level < 3) {
    return 0;
  }
  printk("outoversize = %lld\n",uVar5,local_50,iStack_4c);
  if (g_switch_debug_level < 3) {
    return 0;
  }
  printk("statechange = %lld\n",extraout_r1_04,local_40,uStack_3c);
  uVar5 = extraout_r1_05;
LAB_00015b2c:
  if ((2 < g_switch_debug_level) &&
     (printk("outpause = %lld\n",uVar5,local_38,iStack_34), 2 < g_switch_debug_level)) {
    printk("dropevents = %lld\n",extraout_r1_06,local_28,iStack_24);
  }
  return 0;
}

