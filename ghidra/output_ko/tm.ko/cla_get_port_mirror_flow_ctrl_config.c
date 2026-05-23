// module: tm.ko
// function: cla_get_port_mirror_flow_ctrl_config @ 0x10f58
// size: 228 bytes
//

undefined4 cla_get_port_mirror_flow_ctrl_config(uint param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 local_14;
  
  local_14 = 0;
  if (6 < g_tm_debug_level) {
    printk("[TM][cla_get_port_mirror_flow_ctrl_config]input: gemport_id = %d\n",param_1);
  }
  if (param_1 < 4) {
    iVar2 = tmOnuRegRead(param_1 + 8,&local_14,0,&claRegTable);
    if (iVar2 == 0) {
      *param_2 = local_14;
      uVar1 = 0;
      if (6 < g_tm_debug_level) {
        printk("[TM][cla_get_port_mirror_flow_ctrl_config]output: ctrl_val = %d\n");
      }
    }
    else if (g_tm_debug_level == 0) {
      uVar1 = 0xffffffff;
    }
    else {
      printk("[TM][cla_get_port_mirror_flow_ctrl_config]reg read failed\n");
      uVar1 = 0xffffffff;
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar1 = 1;
  }
  else {
    printk("[TM][cla_get_port_mirror_flow_ctrl_config]input invalid parameter!\n");
    uVar1 = 1;
  }
  return uVar1;
}

