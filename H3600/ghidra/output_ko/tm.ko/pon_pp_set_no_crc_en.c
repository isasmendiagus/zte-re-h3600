// module: tm.ko
// function: pon_pp_set_no_crc_en @ 0x29158
// size: 220 bytes
//

undefined4
pon_pp_set_no_crc_en(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][pon_pp_set_no_crc_en]input: enable=%d\n",param_1,param_3,g_tm_debug_level,param_4);
  }
  if (1 < param_1) {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_7232,"pon_pp_set_no_crc_en"), iVar1 != 0)) {
      printk("ERROR:(%s:%d) reg invalid para\n","pp/src/pp_reg.c",0x39f);
    }
    return 1;
  }
  iVar1 = tmOnuRegWrite(0xb,param_1,0,PonPpRegTable);
  if (iVar1 == 0) {
    return 0;
  }
  if ((g_tm_debug_level != 0) && (iVar1 = ___ratelimit(_rs_7235,"pon_pp_set_no_crc_en"), iVar1 != 0)
     ) {
    printk("ERROR:(%s:%d) reg write fail\n","pp/src/pp_reg.c",0x3a8);
  }
  return 0xffffffff;
}

