// module: tm.ko
// function: sbrg_get_multicst_vltrans_table @ 0x1bd2c
// size: 216 bytes
//

undefined4 sbrg_get_multicst_vltrans_table(uint *param_1,uint param_2)

{
  undefined4 uVar1;
  int iVar2;
  uint local_c;
  
  local_c = 0;
  if (param_2 < 0x30) {
    iVar2 = tmOnuRegRead(0x48,&local_c,param_2,&sbragRegTable);
    if (iVar2 == 0) {
      *param_1 = local_c & 7;
      param_1[1] = (local_c << 0x11) >> 0x14;
      param_1[2] = (local_c << 0xe) >> 0x1d;
      param_1[3] = (local_c << 2) >> 0x14;
      param_1[4] = (local_c << 1) >> 0x1f;
      param_1[5] = local_c >> 0x1f;
      return 0;
    }
    if (g_tm_debug_level == 0) {
      uVar1 = 0xffffffff;
    }
    else {
      printk("[TM][sbrg_get_multicst_vltrans_table] reg read failed\n");
      uVar1 = 0xffffffff;
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar1 = 1;
  }
  else {
    printk("[TM][sbrg_get_multicst_vltrans_table]input invalid parameter!\n");
    uVar1 = 1;
  }
  return uVar1;
}

