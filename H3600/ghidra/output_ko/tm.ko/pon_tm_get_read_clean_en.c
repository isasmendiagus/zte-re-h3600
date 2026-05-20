// module: tm.ko
// function: pon_tm_get_read_clean_en @ 0x44400
// size: 216 bytes
//

undefined4 pon_tm_get_read_clean_en(uint *param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint local_14 [2];
  
  local_14[0] = 0;
  iVar1 = tmOnuRegRead(0,local_14,0,PonTmRegTable);
  if (iVar1 == 0) {
    *param_1 = local_14[0] & 1;
    if ((g_tm_debug_level == 0) ||
       (iVar1 = ___ratelimit(_rs_6983,"pon_tm_get_read_clean_en"), iVar1 == 0)) {
      return 0;
    }
    printk("[TM][pon_tm_get_read_clean_en]output: enable=%d\n",*param_1);
    uVar2 = 0;
  }
  else {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_6980,"pon_tm_get_read_clean_en"), iVar1 != 0)) {
      printk("ERROR:(%s:%d) reg read fail\n","tm/src/pon_tm_reg.c",0x7a);
    }
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

