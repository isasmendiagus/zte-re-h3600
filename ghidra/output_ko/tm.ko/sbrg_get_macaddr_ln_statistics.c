// module: tm.ko
// function: sbrg_get_macaddr_ln_statistics @ 0x1984c
// size: 236 bytes
//

undefined4 sbrg_get_macaddr_ln_statistics(undefined4 *param_1,uint param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 local_14;
  
  local_14 = 0;
  if (param_2 < 8) {
    if (6 < g_tm_debug_level) {
      printk("[TM][sbrg_get_macaddr_ln_statistics]input:port_id = %d\n",param_2,param_2);
    }
    iVar2 = tmOnuRegRead(0x2b,&local_14,param_2,&sbragRegTable);
    if (iVar2 == 0) {
      *param_1 = local_14;
      uVar1 = 0;
      if (6 < g_tm_debug_level) {
        printk("[TM][sbrg_get_macaddr_ln_statistics]output:statistics = %d\n");
      }
    }
    else if (g_tm_debug_level == 0) {
      uVar1 = 0xffffffff;
    }
    else {
      printk("[TM][sbrg_get_macaddr_ln_statistics] reg read failed\n");
      uVar1 = 0xffffffff;
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar1 = 1;
  }
  else {
    printk("[TM][sbrg_get_macaddr_ln_statistics]input invalid parameter!\n");
    uVar1 = 1;
  }
  return uVar1;
}

