// module: tm.ko
// function: cla_set_port_mirror_flow_ctrl_config @ 0x10ea0
// size: 184 bytes
//

undefined4 cla_set_port_mirror_flow_ctrl_config(uint param_1,uint param_2)

{
  int iVar1;
  bool bVar2;
  bool bVar3;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][cla_set_port_mirror_flow_ctrl_config]input: gemport_id = %d, ctrl_val = %d\n",
           param_1,param_2);
  }
  bVar3 = param_2 != 0;
  bVar2 = param_2 == 1;
  if (param_2 < 2) {
    bVar3 = 2 < param_1;
    bVar2 = param_1 == 3;
  }
  if (bVar3 && !bVar2) {
    if (g_tm_debug_level != 0) {
      printk("[TM][cla_set_port_mirror_flow_ctrl_config]input invalid parameter!\n");
      return 1;
    }
    return 1;
  }
  iVar1 = tmOnuRegWrite(param_1 + 8,param_2,0,&claRegTable);
  if (iVar1 == 0) {
    return 0;
  }
  if (g_tm_debug_level != 0) {
    printk("[TM][cla_set_port_mirror_flow_ctrl_config]reg write failed\n");
    return 0xffffffff;
  }
  return 0xffffffff;
}

