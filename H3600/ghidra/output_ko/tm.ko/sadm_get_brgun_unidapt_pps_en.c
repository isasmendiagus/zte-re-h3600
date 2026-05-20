// module: tm.ko
// function: sadm_get_brgun_unidapt_pps_en @ 0x24d40
// size: 268 bytes
//

undefined4 sadm_get_brgun_unidapt_pps_en(uint param_1,uint *param_2)

{
  undefined4 uVar1;
  int iVar2;
  uint local_14 [2];
  
  local_14[0] = 0;
  if (param_1 < 8) {
    if (6 < g_tm_debug_level) {
      printk("[TM][sadm_get_brgun_unidapt_pps_en]input:reg_array = %d\n",param_1);
    }
    iVar2 = tmOnuRegRead(0x10,local_14,param_1,sadmRegTable);
    if (iVar2 != 0) {
      if ((g_tm_debug_level != 0) &&
         (iVar2 = ___ratelimit(_rs_14500,"sadm_get_brgun_unidapt_pps_en"), iVar2 != 0)) {
        printk("[TM][sadm_get_brgun_unidapt_pps_en]write reg failed!\n");
      }
      return 0xffffffff;
    }
    if (local_14[0] < 2) {
      *param_2 = local_14[0];
    }
    if (g_tm_debug_level < 7) {
      uVar1 = 0;
    }
    else {
      printk("[TM][sadm_get_brgun_unidapt_pps_en]output:en = %d\n",*param_2);
      uVar1 = 0;
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar1 = 1;
  }
  else {
    printk("[TM][sadm_get_brgun_unidapt_pps_en]input invalid parameter!\n");
    uVar1 = 1;
  }
  return uVar1;
}

