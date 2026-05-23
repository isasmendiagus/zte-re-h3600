// module: switch.ko
// function: sw_port_get_port_vlanstatistics @ 0x162f4
// size: 620 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sw_port_get_port_vlanstatistics(uint *param_1)

{
  uint uVar1;
  int iVar2;
  undefined4 local_84;
  uint local_80;
  uint local_7c;
  uint local_78;
  uint local_74;
  uint local_70;
  uint local_6c;
  uint local_68;
  uint local_64;
  uint local_60;
  uint local_5c;
  uint local_58;
  uint local_54;
  
  __memzero(&local_78,0x58);
  __memzero(&local_84,0xc);
  if (_tm_port_unknwn_multicast_floodport_set <= *param_1) {
    printk("[%s]%d input port error!\n","sw_port_get_port_vlanstatistics",0x16e);
    return 0xffffffff;
  }
  local_74 = param_1[1];
  local_78 = (uint)(byte)tm_set_p2pmode[*param_1];
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\nportid=%d\nvlanid=%d\n","sw_port_get_port_vlanstatistics",local_78,local_74
          );
  }
  local_84 = 1;
  local_80 = local_78;
  local_7c = local_74;
  iVar2 = tm_vlan_stat_config(&local_84);
  if (iVar2 != 0) {
    printk("[%s] L%d tm sdk failed!\n","sw_port_get_port_vlanstatistics",0x17b);
    return 0xffffffff;
  }
  iVar2 = tm_vlan_statistics(&local_78);
  uVar1 = g_switch_debug_level;
  if (iVar2 != 0) {
    printk("[%s] L%d tm sdk failed!\n","sw_port_get_port_vlanstatistics",0x182);
    return 0xffffffff;
  }
  param_1[2] = local_64;
  param_1[3] = local_68;
  param_1[4] = local_60;
  param_1[5] = local_54;
  param_1[6] = local_58;
  param_1[7] = local_70;
  param_1[8] = local_6c;
  param_1[9] = local_5c;
  if (uVar1 < 3) {
    return 0;
  }
  printk("[%s] output:\n","sw_port_get_port_vlanstatistics");
  if (2 < g_switch_debug_level) {
    printk("inframe = %d\n",local_64);
    if (g_switch_debug_level < 3) {
      return 0;
    }
    printk("inoct = %d\n",local_68);
    if (g_switch_debug_level < 3) goto LAB_000164c4;
    printk("outframe = %d\n",local_60);
    if (g_switch_debug_level < 3) {
      return 0;
    }
    printk("disinbound = %d\n",local_54);
  }
  if (g_switch_debug_level < 3) {
    return 0;
  }
  printk("disbuffer = %d\n",local_58);
  if (g_switch_debug_level < 3) {
    return 0;
  }
  printk("disdelay = %d\n",local_70);
LAB_000164c4:
  if ((2 < g_switch_debug_level) && (printk("diserror = %d\n",local_6c), 2 < g_switch_debug_level))
  {
    printk("disingress = %d\n",local_5c);
  }
  return 0;
}

