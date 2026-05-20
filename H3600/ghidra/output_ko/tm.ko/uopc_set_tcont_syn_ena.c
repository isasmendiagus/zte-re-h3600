// module: tm.ko
// function: uopc_set_tcont_syn_ena @ 0x3c41c
// size: 192 bytes
//

int uopc_set_tcont_syn_ena(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][uopc_set_tcont_syn_ena]input: syn_ena = %d\n",param_1,param_3,g_tm_debug_level,
           param_4);
  }
  if (1 < param_1) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("ERROR:(%s:%d) input invalid parameter\n","npp/pon_npp_uopc.c",0x120,g_tm_debug_level,
           param_4);
    return 1;
  }
  iVar1 = tmOnuRegWrite(4,param_1,0,&UopcRegTable);
  if ((iVar1 != 0) && (g_tm_debug_level != 0)) {
    printk("ERROR:(%s:%d) reg write fail\n","npp/pon_npp_uopc.c",0x128,g_tm_debug_level,param_4);
    return iVar1;
  }
  return iVar1;
}

