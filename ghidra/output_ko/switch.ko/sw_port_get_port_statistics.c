// module: switch.ko
// function: sw_port_get_port_statistics @ 0x16024
// size: 532 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sw_port_get_port_statistics(uint *param_1)

{
  uint uVar1;
  int iVar2;
  uint local_70 [2];
  uint local_68;
  uint local_64;
  uint local_60;
  uint local_5c;
  uint local_58;
  uint local_54;
  uint local_50;
  uint local_4c;
  
  __memzero(local_70,0x58);
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\nport=%d\n","sw_port_get_port_statistics",*param_1);
  }
  if (_tm_port_unknwn_multicast_floodport_set <= *param_1) {
    printk("[%s]%d input port error!\n","sw_port_get_port_statistics",0x140);
    return 0xffffffff;
  }
  local_70[0] = (uint)(byte)zte_api_sw_mac_set_port_macfiltermode[*param_1];
  iVar2 = tm_port_statistics(local_70);
  uVar1 = g_switch_debug_level;
  if (iVar2 != 0) {
    printk("[%s] L%d tm sdk failed!\n","sw_port_get_port_statistics",0x148);
    return 0xffffffff;
  }
  param_1[2] = local_5c;
  param_1[3] = local_60;
  param_1[4] = local_58;
  param_1[5] = local_4c;
  param_1[6] = local_50;
  param_1[7] = local_68;
  param_1[8] = local_64;
  param_1[9] = local_54;
  if (uVar1 < 3) {
    return 0;
  }
  printk("[%s] output:\n","sw_port_get_port_statistics");
  if (2 < g_switch_debug_level) {
    printk("inframe = %d\n",local_5c);
    if (g_switch_debug_level < 3) {
      return 0;
    }
    printk("inoct = %d\n",local_60);
    if (g_switch_debug_level < 3) goto LAB_000161bc;
    printk("outframe = %d\n",local_58);
    if (g_switch_debug_level < 3) {
      return 0;
    }
    printk("disinbound = %d\n",local_4c);
  }
  if (g_switch_debug_level < 3) {
    return 0;
  }
  printk("disbuffer = %d\n",local_50);
  if (g_switch_debug_level < 3) {
    return 0;
  }
  printk("disdelay = %d\n",local_68);
LAB_000161bc:
  if ((2 < g_switch_debug_level) && (printk("diserror = %d\n",local_64), 2 < g_switch_debug_level))
  {
    printk("disingress = %d\n",local_54);
  }
  return 0;
}

