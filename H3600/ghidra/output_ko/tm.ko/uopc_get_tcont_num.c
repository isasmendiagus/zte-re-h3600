// module: tm.ko
// function: uopc_get_tcont_num @ 0x3c0cc
// size: 152 bytes
//

int uopc_get_tcont_num(undefined4 *param_1)

{
  int iVar1;
  undefined4 local_14 [2];
  
  local_14[0] = 0;
  iVar1 = tmOnuRegRead(1,local_14,0,&UopcRegTable);
  if (iVar1 == 0) {
    *param_1 = local_14[0];
    if (6 < g_tm_debug_level) {
      printk("[TM][uopc_get_tcont_num]output: tcont_num = %d\n");
    }
  }
  else if (g_tm_debug_level != 0) {
    printk("ERROR:(%s:%d) reg read fail\n","npp/pon_npp_uopc.c",0x7c);
  }
  return iVar1;
}

