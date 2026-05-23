// module: tm.ko
// function: pm_get_g988_index_cfg @ 0x35724
// size: 156 bytes
//

undefined4 pm_get_g988_index_cfg(uint param_1,int param_2)

{
  uint local_c;
  
  if (0x3f < param_1) {
    if (g_tm_debug_level != 0) {
      printk("[TM][pm_get_g988_index_cfg]input invalid parameter!\n");
    }
    return 1;
  }
  tmOnuRegRead(0xd,&local_c,param_1,pmRegTable);
  *(uint *)(param_2 + 4) = (local_c << 0xb) >> 0x1f;
  *(byte *)(param_2 + 8) = (byte)((local_c << 0xc) >> 0x1f);
  *(uint *)(param_2 + 0xc) = (local_c << 0xd) >> 0x1f;
  *(uint *)(param_2 + 0x10) = (local_c << 0xe) >> 0x1d;
  *(uint *)(param_2 + 0x14) = (local_c << 0x11) >> 0x1d;
  *(uint *)(param_2 + 0x18) = local_c & 0xfff;
  return 0;
}

