// module: tm.ko
// function: pon_pp_set_pm_base_addr @ 0x297a0
// size: 144 bytes
//

undefined4
pon_pp_set_pm_base_addr(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][pon_pp_set_jumb_len]input: base_addr=%d\n",param_1,param_3,g_tm_debug_level,param_4
          );
  }
  iVar1 = tmOnuRegWrite(0xe,param_1,0,PonPpRegTable);
  if (iVar1 == 0) {
    return 0;
  }
  if ((g_tm_debug_level != 0) &&
     (iVar1 = ___ratelimit(_rs_7298,"pon_pp_set_pm_base_addr"), iVar1 != 0)) {
    printk("ERROR:(%s:%d) reg write fail\n","pp/src/pp_reg.c",0x494);
  }
  return 0xffffffff;
}

