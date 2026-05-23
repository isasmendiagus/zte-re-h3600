// module: tm.ko
// function: cla_set_def_qos_info_cfg @ 0x13e10
// size: 184 bytes
//

undefined4 cla_set_def_qos_info_cfg(uint param_1,uint param_2)

{
  int iVar1;
  bool bVar2;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][cla_set_def_qos_info_cfg]input: def_qos_vld = %d, qos_id = %d\n",param_1,param_2);
  }
  bVar2 = param_1 != 0;
  if (param_1 < 2) {
    bVar2 = 0x1ff < param_2;
  }
  if (bVar2) {
    if (g_tm_debug_level != 0) {
      printk("[TM][cla_set_def_qos_info_cfg]input invalid parameter!\n");
      return 1;
    }
    return 1;
  }
  iVar1 = tmOnuRegWrite(0x3a,param_2 + param_1 * 0x200,0,&claRegTable);
  if (iVar1 == 0) {
    return 0;
  }
  if (g_tm_debug_level != 0) {
    printk("[TM][cla_set_def_qos_info_cfg]reg write failed\n");
    return 0xffffffff;
  }
  return 0xffffffff;
}

