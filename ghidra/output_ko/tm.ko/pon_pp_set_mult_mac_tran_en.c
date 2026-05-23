// module: tm.ko
// function: pon_pp_set_mult_mac_tran_en @ 0x28ba4
// size: 220 bytes
//

undefined4
pon_pp_set_mult_mac_tran_en(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][pon_pp_set_mult_mac_tran_en]intput: tran_en=%d\n",param_1,param_3,g_tm_debug_level,
           param_4);
  }
  if (1 < param_1) {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_7171,"pon_pp_set_mult_mac_tran_en"), iVar1 != 0)) {
      printk("ERROR:(%s:%d) reg invalid para\n","pp/src/pp_reg.c",0x259);
    }
    return 1;
  }
  iVar1 = tmOnuRegWrite(7,param_1,0,PonPpRegTable);
  if (iVar1 == 0) {
    return 0;
  }
  if ((g_tm_debug_level != 0) &&
     (iVar1 = ___ratelimit(_rs_7174,"pon_pp_set_mult_mac_tran_en"), iVar1 != 0)) {
    printk("ERROR:(%s:%d) reg write fail\n","pp/src/pp_reg.c",0x262);
  }
  return 0xffffffff;
}

