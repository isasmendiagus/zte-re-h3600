// module: tm.ko
// function: pon_pp_get_dslite_flow_lable @ 0x29f58
// size: 256 bytes
//

int pon_pp_get_dslite_flow_lable(uint param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 local_14;
  
  local_14 = 0;
  if (6 < g_tm_debug_level) {
    printk("[TM][pon_pp_get_dslite_flow_lable]input: num = %d\n",param_1);
  }
  if (param_1 < 8) {
    iVar1 = tmOnuRegRead(0x12,&local_14,param_1,PonPpRegTable);
    if (iVar1 == 0) {
      *param_2 = local_14;
      if (g_tm_debug_level < 7) {
        return 0;
      }
      printk("[TM][pon_pp_get_dslite_flow_lable]output: flow_lable=%d\n");
    }
    else {
      if (g_tm_debug_level == 0) {
        return iVar1;
      }
      printk("ERROR:(%s:%d) reg read fail\n","pp/src/pp_reg.c",0x5de);
    }
  }
  else if (g_tm_debug_level == 0) {
    iVar1 = 1;
  }
  else {
    printk("ERROR:(%s:%d) reg invalid para\n","pp/src/pp_reg.c",0x5d7);
    iVar1 = 1;
  }
  return iVar1;
}

