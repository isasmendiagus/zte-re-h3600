// module: tm.ko
// function: pon_pp_set_brg_int_mask @ 0x27e98
// size: 192 bytes
//

undefined4
pon_pp_set_brg_int_mask(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (1 < param_1) {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_7043,"pon_pp_set_brg_int_mask"), iVar1 != 0)) {
      printk("ERROR:(%s:%d) reg invalid para\n","pp/src/pp_reg.c",0x7e);
    }
    return 1;
  }
  iVar1 = tmOnuRegWrite(1,param_1,0,PonPpRegTable,param_4);
  if (iVar1 == 0) {
    return 0;
  }
  if ((g_tm_debug_level != 0) &&
     (iVar1 = ___ratelimit(_rs_7046,"pon_pp_set_brg_int_mask"), iVar1 != 0)) {
    printk("ERROR:(%s:%d) reg write fail\n","pp/src/pp_reg.c",0x87);
  }
  return 0xffffffff;
}

