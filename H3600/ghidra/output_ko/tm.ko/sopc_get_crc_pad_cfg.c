// module: tm.ko
// function: sopc_get_crc_pad_cfg @ 0x37574
// size: 240 bytes
//

undefined4 sopc_get_crc_pad_cfg(uint param_1,uint *param_2)

{
  undefined4 uVar1;
  int iVar2;
  uint local_14;
  
  local_14 = 0;
  if (param_1 >> 5 == 0) {
    if (6 < g_tm_debug_level) {
      printk("[TM][sopc_get_crc_pad_cfg]input: port = %d\n",param_1);
    }
    iVar2 = tmOnuRegRead(param_1,&local_14,0,&sopcRegTable);
    if (iVar2 == 0) {
      *param_2 = local_14 & 3;
      uVar1 = 0;
      if (6 < g_tm_debug_level) {
        printk("[TM][sopc_get_crc_pad_cfg]output: crc_pad_en = %d\n");
      }
    }
    else if (g_tm_debug_level == 0) {
      uVar1 = 0xffffffff;
    }
    else {
      printk("[TM][sopc_get_crc_pad_cfg]reg read failed\n");
      uVar1 = 0xffffffff;
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar1 = 1;
  }
  else {
    printk("[TM][sopc_get_crc_pad_cfg]input invalid parameter!\n");
    uVar1 = 1;
  }
  return uVar1;
}

