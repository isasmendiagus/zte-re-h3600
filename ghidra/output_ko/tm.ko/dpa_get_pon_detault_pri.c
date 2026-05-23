// module: tm.ko
// function: dpa_get_pon_detault_pri @ 0x27840
// size: 156 bytes
//

int dpa_get_pon_detault_pri(uint *param_1)

{
  int iVar1;
  int iVar2;
  uint local_14 [2];
  
  iVar1 = tmOnuRegRead(8,local_14,0,dpaRegTable);
  if (iVar1 == 0) {
    *param_1 = local_14[0] & 0xffffff;
    if (6 < g_tm_debug_level) {
      printk("[TM][dpa_get_pon_detault_pri]output: dft_pri = %d\n");
    }
  }
  else if ((g_tm_debug_level != 0) &&
          (iVar2 = ___ratelimit(_rs_6996,"dpa_get_pon_detault_pri"), iVar2 != 0)) {
    printk("[TM][dpa_get_pon_detault_pri]write reg failed!\n");
  }
  return iVar1;
}

