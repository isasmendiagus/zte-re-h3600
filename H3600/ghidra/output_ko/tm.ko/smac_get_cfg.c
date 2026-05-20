// module: tm.ko
// function: smac_get_cfg @ 0x3055c
// size: 304 bytes
//

int smac_get_cfg(undefined4 param_1,uint *param_2)

{
  int iVar1;
  uint local_14 [2];
  
  local_14[0] = 0;
  iVar1 = tmOnuRegRead(1,local_14,param_1,&smacRegTable);
  if (iVar1 != 0) {
    if (6 < g_tm_debug_level) {
      printk("[TM][smac_set_efc]write reg failed!\n");
    }
    return iVar1;
  }
  param_2[0x16] = local_14[0] & 1;
  param_2[0x15] = (local_14[0] << 0x1e) >> 0x1f;
  param_2[0x14] = (local_14[0] << 0x1c) >> 0x1e;
  param_2[0x13] = (local_14[0] << 0x1b) >> 0x1f;
  param_2[0x12] = (local_14[0] << 0x19) >> 0x1e;
  param_2[0x11] = (local_14[0] << 0x17) >> 0x1f;
  param_2[0x10] = (local_14[0] << 0x16) >> 0x1f;
  param_2[0xf] = (local_14[0] << 0x15) >> 0x1f;
  param_2[0xe] = (local_14[0] << 0x14) >> 0x1f;
  param_2[0xd] = (local_14[0] << 0x13) >> 0x1f;
  param_2[0xc] = (local_14[0] << 0x12) >> 0x1f;
  param_2[0xb] = (local_14[0] << 0x11) >> 0x1f;
  param_2[10] = (local_14[0] << 0x10) >> 0x1f;
  param_2[9] = (local_14[0] << 0xf) >> 0x1f;
  param_2[8] = (local_14[0] << 0xe) >> 0x1f;
  param_2[7] = (local_14[0] << 0xd) >> 0x1f;
  param_2[6] = (local_14[0] << 0xc) >> 0x1f;
  param_2[5] = (local_14[0] << 0xb) >> 0x1f;
  param_2[4] = (local_14[0] << 10) >> 0x1f;
  param_2[3] = (local_14[0] << 9) >> 0x1f;
  param_2[2] = (local_14[0] << 8) >> 0x1f;
  param_2[1] = (local_14[0] << 5) >> 0x1d;
  *param_2 = (local_14[0] << 4) >> 0x1f;
  return 0;
}

