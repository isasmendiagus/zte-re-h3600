// module: tm.ko
// function: sadm_set_brgun_unidapt_pps_pktnum @ 0x24a60
// size: 216 bytes
//

undefined4 sadm_set_brgun_unidapt_pps_pktnum(uint param_1,uint param_2)

{
  int iVar1;
  bool bVar2;
  
  bVar2 = 6 < param_1;
  if (param_1 < 8) {
    bVar2 = 0x1fff < param_2;
  }
  if (bVar2) {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_14470,"sadm_set_brgun_unidapt_pps_pktnum"), iVar1 != 0)) {
      printk("[TM][sadm_set_brgun_unidapt_pps_pktnum]input invalid parameter!\n");
    }
    return 1;
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][sadm_set_brgun_unidapt_pps_pktnum]input:reg_array = %d,max = %d\n",param_1,param_2)
    ;
  }
  iVar1 = tmOnuRegWrite(0xf,param_2,param_1,sadmRegTable);
  if (iVar1 == 0) {
    return 0;
  }
  if ((g_tm_debug_level != 0) &&
     (iVar1 = ___ratelimit(_rs_14473,"sadm_set_brgun_unidapt_pps_pktnum"), iVar1 != 0)) {
    printk("[TM][sadm_set_brgun_unidapt_pps_pktnum]write reg failed!\n");
  }
  return 0xffffffff;
}

