// module: tm.ko
// function: pon_tm_set_read_clean_en @ 0x44310
// size: 232 bytes
//

undefined4
pon_tm_set_read_clean_en(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][pon_tm_set_read_clean_en]input: enable=%d\n",param_1,param_3,g_tm_debug_level,
           param_4);
  }
  if (1 < param_1) {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(&_rs_6970,"pon_tm_set_read_clean_en"), iVar1 != 0)) {
      printk("ERROR:(%s:%d) reg invalid para\n","tm/src/pon_tm_reg.c",0x52);
    }
    return 1;
  }
  iVar1 = tmOnuRegWrite(0,param_1,0,PonTmRegTable);
  if (iVar1 == 0) {
    return 0;
  }
  if ((g_tm_debug_level != 0) &&
     (iVar1 = ___ratelimit(_rs_6973,"pon_tm_set_read_clean_en"), iVar1 != 0)) {
    printk("ERROR:(%s:%d) reg write fail\n","tm/src/pon_tm_reg.c",0x5b);
  }
  return 0xffffffff;
}

