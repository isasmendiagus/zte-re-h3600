// module: tm.ko
// function: cla_get_def_qos_info_cfg @ 0x13ec8
// size: 176 bytes
//

undefined4 cla_get_def_qos_info_cfg(uint *param_1,uint *param_2)

{
  int iVar1;
  undefined4 uVar2;
  uint local_14;
  
  local_14 = 0;
  iVar1 = tmOnuRegRead(0x3a,&local_14,0,&claRegTable);
  if (iVar1 == 0) {
    *param_1 = (local_14 << 0x16) >> 0x1f;
    *param_2 = local_14 & 0x1ff;
    uVar2 = 0;
    if (6 < g_tm_debug_level) {
      printk("[TM][cla_get_def_qos_info_cfg]output: def_qos_vld = %d, qos_id = %d\n",*param_1);
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    printk("[TM][cla_get_def_qos_info_cfg]reg read failed\n");
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

