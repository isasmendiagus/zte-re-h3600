// module: tm.ko
// function: sopc_set_crc_pad_cfg @ 0x374b4
// size: 192 bytes
//

undefined4 sopc_set_crc_pad_cfg(uint param_1,uint param_2)

{
  int iVar1;
  
  if ((param_1 >> 5 != 0) || (param_2 >> 4 != 0)) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("[TM][sopc_set_crc_pad_cfg]input invalid parameter!\n");
    return 1;
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][sopc_set_crc_pad_cfg]input: port = %d, crc_pad_en = %d\n",param_1,param_2);
  }
  iVar1 = tmOnuRegWrite(param_1,param_2,0,&sopcRegTable);
  if (iVar1 == 0) {
    return 0;
  }
  if (g_tm_debug_level == 0) {
    return 0xffffffff;
  }
  printk("[TM][sopc_set_crc_pad_cfg]reg write failed\n");
  return 0xffffffff;
}

