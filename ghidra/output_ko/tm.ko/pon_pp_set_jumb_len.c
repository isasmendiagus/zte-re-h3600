// module: tm.ko
// function: pon_pp_set_jumb_len @ 0x29328
// size: 220 bytes
//

undefined4
pon_pp_set_jumb_len(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][pon_pp_set_jumb_len]input: jumb_len=%d\n",param_1,param_3,g_tm_debug_level,param_4)
    ;
  }
  if (0x7fff < param_1) {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_7251,"pon_pp_set_jumb_len"), iVar1 != 0)) {
      printk("ERROR:(%s:%d) reg invalid para\n","pp/src/pp_reg.c",0x3e9);
    }
    return 1;
  }
  iVar1 = tmOnuRegWrite(0xc,param_1,0,PonPpRegTable);
  if (iVar1 == 0) {
    return 0;
  }
  if ((g_tm_debug_level != 0) && (iVar1 = ___ratelimit(_rs_7254,"pon_pp_set_jumb_len"), iVar1 != 0))
  {
    printk("ERROR:(%s:%d) reg write fail\n","pp/src/pp_reg.c",0x3f1);
  }
  return 0xffffffff;
}

