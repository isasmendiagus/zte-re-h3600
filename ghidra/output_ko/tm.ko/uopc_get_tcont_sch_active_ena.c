// module: tm.ko
// function: uopc_get_tcont_sch_active_ena @ 0x3c224
// size: 156 bytes
//

int uopc_get_tcont_sch_active_ena(uint *param_1)

{
  int iVar1;
  uint local_14 [2];
  
  local_14[0] = 0;
  iVar1 = tmOnuRegRead(2,local_14,0,&UopcRegTable);
  if (iVar1 == 0) {
    *param_1 = local_14[0] & 1;
    if (6 < g_tm_debug_level) {
      printk("[TM][uopc_get_tcont_sch_active_ena]output: act_ena = %d\n");
    }
  }
  else if (g_tm_debug_level != 0) {
    printk("ERROR:(%s:%d) reg read fail\n","npp/pon_npp_uopc.c",0xbe);
  }
  return iVar1;
}

