// module: tm.ko
// function: sbrg_get_isolate_pt_cfg @ 0x195c0
// size: 228 bytes
//

undefined4 sbrg_get_isolate_pt_cfg(undefined4 *param_1,uint param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 local_14;
  
  if (param_2 < 8) {
    if (6 < g_tm_debug_level) {
      printk("[TM][sbrg_get_isolate_pt_cfg]input:port_id = %d\n",param_2,param_2);
    }
    iVar2 = tmOnuRegRead(0x39,&local_14,param_2,&sbragRegTable);
    if (iVar2 == 0) {
      *param_1 = local_14;
      uVar1 = 0;
      if (6 < g_tm_debug_level) {
        printk("[TM][sbrg_get_isolate_pt_cfg]output:port_mask = 0x%x\n");
      }
    }
    else if (g_tm_debug_level == 0) {
      uVar1 = 0xffffffff;
    }
    else {
      printk("[TM][sbrg_get_isolate_pt_cfg] reg read failed\n");
      uVar1 = 0xffffffff;
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar1 = 1;
  }
  else {
    printk("[TM][sbrg_get_isolate_pt_cfg]input invalid parameter!\n");
    uVar1 = 1;
  }
  return uVar1;
}

