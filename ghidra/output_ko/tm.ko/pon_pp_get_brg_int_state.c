// module: tm.ko
// function: pon_pp_get_brg_int_state @ 0x27db0
// size: 216 bytes
//

undefined4 pon_pp_get_brg_int_state(uint *param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint local_14 [2];
  
  local_14[0] = 0;
  iVar1 = tmOnuRegRead(0,local_14,0,PonPpRegTable);
  if (iVar1 == 0) {
    *param_1 = local_14[0] & 1;
    if ((g_tm_debug_level == 0) ||
       (iVar1 = ___ratelimit(_rs_7036,"pon_pp_get_brg_int_state"), iVar1 == 0)) {
      return 0;
    }
    printk("[TM][pon_pp_get_brg_int_state]output: brg_int_sta = %d\n",*param_1);
    uVar2 = 0;
  }
  else {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_7033,"pon_pp_get_brg_int_state"), iVar1 != 0)) {
      printk("ERROR:(%s:%d) reg read fail\n","pp/src/pp_reg.c",0x5e);
    }
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

