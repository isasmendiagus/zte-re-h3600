// module: tm.ko
// function: cla_set_mac_req_ctrl_config @ 0x10b98
// size: 168 bytes
//

undefined4
cla_set_mac_req_ctrl_config(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][cla_set_mac_req_ctrl_config]input: mac_lookup_en = %d\n",param_1,param_3,
           g_tm_debug_level,param_4);
  }
  if (1 < param_1) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("[TM][cla_set_mac_req_ctrl_config]input invalid parameter!\n");
    return 1;
  }
  iVar1 = tmOnuRegWrite(5,param_1,0,&claRegTable);
  if (iVar1 == 0) {
    return 0;
  }
  if (g_tm_debug_level == 0) {
    return 0xffffffff;
  }
  printk("[TM][cla_set_mac_req_ctrl_config]reg write failed\n");
  return 0xffffffff;
}

