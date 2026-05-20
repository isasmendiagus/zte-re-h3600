// module: tm.ko
// function: sbrg_set_isolate_pt_cfg @ 0x19504
// size: 188 bytes
//

undefined4 sbrg_set_isolate_pt_cfg(uint param_1,uint param_2)

{
  int iVar1;
  bool bVar2;
  bool bVar3;
  
  bVar3 = 0xfe < param_1;
  bVar2 = param_1 == 0xff;
  if (param_1 < 0x100) {
    bVar3 = 6 < param_2;
    bVar2 = param_2 == 7;
  }
  if (bVar3 && !bVar2) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("[TM][sbrg_set_isolate_pt_cfg]input invalid parameter!\n");
    return 1;
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][sbrg_get_isolate_pt_cfg]input:port_mask = 0x%x,port_id = %d\n",param_1,param_2);
  }
  iVar1 = tmOnuRegWrite(0x39,param_1,param_2,&sbragRegTable);
  if (iVar1 == 0) {
    return 0;
  }
  if (g_tm_debug_level == 0) {
    return 0xffffffff;
  }
  printk("[TM][sbrg_set_isolate_pt_cfg]write reg failed!\n");
  return 0xffffffff;
}

