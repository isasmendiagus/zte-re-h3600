// module: tm.ko
// function: sbrg_get_pt_learn_mode @ 0x19148
// size: 232 bytes
//

undefined4 sbrg_get_pt_learn_mode(undefined4 *param_1,uint param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 local_14;
  
  local_14 = 0;
  if (param_2 < 8) {
    if (6 < g_tm_debug_level) {
      printk("[TM][sbrg_get_pt_learn_mode]input:port_id = %d\n");
    }
    iVar2 = tmOnuRegRead(param_2 + 0x22,&local_14,0,&sbragRegTable);
    if (iVar2 == 0) {
      *param_1 = local_14;
      uVar1 = 0;
      if (6 < g_tm_debug_level) {
        printk("[TM][sbrg_get_pt_learn_mode]output:learn_mode = %d\n");
      }
    }
    else if (g_tm_debug_level == 0) {
      uVar1 = 0xffffffff;
    }
    else {
      printk("[TM][sbrg_get_pt_learn_mode] reg read failed\n");
      uVar1 = 0xffffffff;
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar1 = 1;
  }
  else {
    printk("[TM][sbrg_get_pt_learn_mode]input invalid parameter!\n");
    uVar1 = 1;
  }
  return uVar1;
}

