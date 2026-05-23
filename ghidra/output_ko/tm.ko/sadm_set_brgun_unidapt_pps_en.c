// module: tm.ko
// function: sadm_set_brgun_unidapt_pps_en @ 0x24c58
// size: 216 bytes
//

undefined4 sadm_set_brgun_unidapt_pps_en(uint param_1,uint param_2)

{
  int iVar1;
  bool bVar2;
  bool bVar3;
  
  bVar3 = param_2 != 0;
  bVar2 = param_2 == 1;
  if (param_2 < 2) {
    bVar3 = 6 < param_1;
    bVar2 = param_1 == 7;
  }
  if (bVar3 && !bVar2) {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_14489,"sadm_set_brgun_unidapt_pps_en"), iVar1 != 0)) {
      printk("[TM][sadm_set_brgun_unidapt_pps_en]input invalid parameter!\n");
    }
    return 1;
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][sadm_set_brgun_unidapt_pps_en]input:reg_array = %d,en = %d\n",param_1,param_2);
  }
  iVar1 = tmOnuRegWrite(0x10,param_2,param_1,sadmRegTable);
  if (iVar1 == 0) {
    return 0;
  }
  if ((g_tm_debug_level != 0) &&
     (iVar1 = ___ratelimit(_rs_14492,"sadm_set_brgun_unidapt_pps_en"), iVar1 != 0)) {
    printk("[TM][sadm_set_brgun_unidapt_pps_en]write reg failed!\n");
  }
  return 0xffffffff;
}

