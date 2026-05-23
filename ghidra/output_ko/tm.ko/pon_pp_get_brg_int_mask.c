// module: tm.ko
// function: pon_pp_get_brg_int_mask @ 0x27f68
// size: 172 bytes
//

int pon_pp_get_brg_int_mask(uint *param_1)

{
  int iVar1;
  int iVar2;
  uint local_14 [2];
  
  local_14[0] = 0;
  iVar1 = tmOnuRegRead(1,local_14,0,PonPpRegTable);
  if (iVar1 == 0) {
    *param_1 = local_14[0] & 1;
    if (6 < g_tm_debug_level) {
      printk("[TM][pon_pp_get_brg_int_mask]output: brg_int_msk=%d\n");
    }
  }
  else if ((g_tm_debug_level != 0) &&
          (iVar2 = ___ratelimit(_rs_7053,"pon_pp_get_brg_int_mask"), iVar2 != 0)) {
    printk("ERROR:(%s:%d) reg write fail\n","pp/src/pp_reg.c",0xa7);
  }
  return iVar1;
}

