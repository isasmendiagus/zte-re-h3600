// module: tm.ko
// function: pon_pp_get_mult_mac_tran_en @ 0x28c90
// size: 172 bytes
//

int pon_pp_get_mult_mac_tran_en(uint *param_1)

{
  int iVar1;
  int iVar2;
  uint local_14 [2];
  
  local_14[0] = 0;
  iVar1 = tmOnuRegRead(7,local_14,0,PonPpRegTable);
  if (iVar1 == 0) {
    *param_1 = local_14[0] & 1;
    if (6 < g_tm_debug_level) {
      printk("[TM][pon_pp_get_mult_mac_tran_en]output: tran_en=%d\n");
    }
  }
  else if ((g_tm_debug_level != 0) &&
          (iVar2 = ___ratelimit(_rs_7181,"pon_pp_get_mult_mac_tran_en"), iVar2 != 0)) {
    printk("ERROR:(%s:%d) reg write fail\n","pp/src/pp_reg.c",0x282);
  }
  return iVar1;
}

