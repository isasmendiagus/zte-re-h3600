// module: switch.ko
// function: sw_port_get_port_statistics4 @ 0x15eb4
// size: 532 bytes
//

undefined4 sw_port_get_port_statistics4(int *param_1)

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
  
  cVar1 = tm_set_p2pmode[*param_1];
  __memzero(&local_70,0x50);
  if (2 < g_switch_debug_level) {
    printk("[%s] input: port=%d\n","sw_port_get_port_statistics4",cVar1);
  }
  iVar3 = zte_api_sw_port_get_port_statistics4(cVar1,&local_70);
  uVar2 = g_switch_debug_level;
  if (iVar3 != 0) {
    printk("[%s] L%d tm sdk failed!\n","sw_port_get_port_statistics4",0x10e);
    return 0xffffffff;
  }
  param_1[6] = local_60;
  param_1[7] = iStack_5c;
  param_1[4] = local_68;
  param_1[5] = iStack_64;
  param_1[8] = local_58;
  param_1[9] = iStack_54;
  param_1[10] = local_50;
  param_1[0xb] = iStack_4c;
  param_1[0xc] = local_48;
  param_1[0xd] = iStack_44;
  param_1[2] = local_70;
  param_1[3] = iStack_6c;
  param_1[0xe] = local_40;
  param_1[0xf] = iStack_3c;
  param_1[0x10] = local_38;
  param_1[0x11] = iStack_34;
  param_1[0x12] = local_30;
  param_1[0x13] = iStack_2c;
  param_1[0x14] = local_28;
  param_1[0x15] = iStack_24;
  if (uVar2 < 3) {
    return 0;
  }
  printk("outexcession = %lld\n");
  uVar4 = extraout_r1;
  if (g_switch_debug_level < 3) {
LAB_0001600c:
    if (g_switch_debug_level < 3) goto LAB_0001608c;
    printk("outdeferred = %lld\n",uVar4,local_48,iStack_44);
    if (g_switch_debug_level < 3) {
      return 0;
    }
    printk("outmacerror = %lld\n",extraout_r1_04,local_40,iStack_3c);
    uVar4 = extraout_r1_05;
  }
  else {
    printk("outlate = %lld\n",extraout_r1,local_68,iStack_64);
    if (g_switch_debug_level < 3) {
      return 0;
    }
    printk("outsingle = %lld\n",extraout_r1_00,local_60,iStack_5c);
    uVar4 = extraout_r1_01;
    if (2 < g_switch_debug_level) {
      printk("outmultiple = %lld\n",extraout_r1_01,local_58,iStack_54);
      if (g_switch_debug_level < 3) {
        return 0;
      }
      printk("SQE = %lld\n",extraout_r1_02,local_50,iStack_4c);
      uVar4 = extraout_r1_03;
      goto LAB_0001600c;
    }
  }
  if (g_switch_debug_level < 3) {
    return 0;
  }
  printk("outcarrier = %lld\n",uVar4,local_38,iStack_34);
  if (g_switch_debug_level < 3) {
    return 0;
  }
  printk("inalignment = %lld\n",extraout_r1_06,local_30,iStack_2c);
  uVar4 = extraout_r1_07;
LAB_0001608c:
  if (2 < g_switch_debug_level) {
    printk("inmacerror = %lld\n",uVar4,local_28,iStack_24);
  }
  return 0;
}

