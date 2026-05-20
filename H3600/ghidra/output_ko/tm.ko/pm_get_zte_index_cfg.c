// module: tm.ko
// function: pm_get_zte_index_cfg @ 0x35924
// size: 208 bytes
//

undefined4 pm_get_zte_index_cfg(uint param_1,int param_2)

{
  uint local_c;
  
  if (0x1f < param_1) {
    if (g_tm_debug_level != 0) {
      printk("[TM][pm_get_zte_index_cfg]input invalid parameter!\n");
    }
    return 1;
  }
  if (param_1 < 0x10) {
    tmOnuRegRead(0xe,&local_c,param_1,pmRegTable);
    *(uint *)(param_2 + 4) = (local_c << 0xf) >> 0x1f;
    *(uint *)(param_2 + 8) = (local_c << 0x10) >> 0x1f;
    *(uint *)(param_2 + 0xc) = (local_c << 0x11) >> 0x1d;
    *(uint *)(param_2 + 0x10) = local_c & 0xfff;
    return 0;
  }
  tmOnuRegRead(0xf,&local_c,param_1 - 0x10,pmRegTable);
  *(uint *)(param_2 + 4) = (local_c << 0x1b) >> 0x1f;
  *(uint *)(param_2 + 8) = (local_c << 0x1c) >> 0x1f;
  *(uint *)(param_2 + 0xc) = local_c & 7;
  return 0;
}

