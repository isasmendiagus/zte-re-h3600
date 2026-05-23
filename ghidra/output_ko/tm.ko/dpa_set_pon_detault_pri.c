// module: tm.ko
// function: dpa_set_pon_detault_pri @ 0x27768
// size: 200 bytes
//

int dpa_set_pon_detault_pri(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][dpa_set_pon_detault_pri]input: dft_pri = %d\n",param_1,param_3,g_tm_debug_level,
           param_4);
  }
  if (0xffffff < param_1) {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_6986,"dpa_set_pon_detault_pri"), iVar1 != 0)) {
      printk("[TM][dpa_set_pon_detault_pri]input invalid parameter!\n");
    }
    return 1;
  }
  iVar1 = tmOnuRegWrite(8,param_1,0,dpaRegTable);
  if (((iVar1 != 0) && (g_tm_debug_level != 0)) &&
     (iVar2 = ___ratelimit(_rs_6989,"dpa_set_pon_detault_pri"), iVar2 != 0)) {
    printk("[TM][dpa_set_pon_detault_pri]write reg failed!\n");
    return iVar1;
  }
  return iVar1;
}

