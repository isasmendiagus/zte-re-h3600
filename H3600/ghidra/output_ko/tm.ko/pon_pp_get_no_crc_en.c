// module: tm.ko
// function: pon_pp_get_no_crc_en @ 0x29244
// size: 212 bytes
//

undefined4 pon_pp_get_no_crc_en(uint *param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint local_14 [2];
  
  local_14[0] = 0;
  iVar1 = tmOnuRegRead(0xb,local_14,0,PonPpRegTable);
  if (iVar1 == 0) {
    *param_1 = local_14[0] & 1;
    if ((g_tm_debug_level == 0) ||
       (iVar1 = ___ratelimit(_rs_7245,"pon_pp_get_no_crc_en"), iVar1 == 0)) {
      return 0;
    }
    printk("[TM][pon_pp_get_read_clean_en]output: enable=%d\n",*param_1);
    uVar2 = 0;
  }
  else {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_7242,"pon_pp_get_no_crc_en"), iVar1 != 0)) {
      printk("ERROR:(%s:%d) reg read fail\n","pp/src/pp_reg.c",0x3c7);
    }
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

