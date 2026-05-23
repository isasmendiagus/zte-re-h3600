// module: tm.ko
// function: sadm_set_bps_th @ 0x236e0
// size: 204 bytes
//

undefined4 sadm_set_bps_th(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (0x1fffff < param_1) {
    if ((g_tm_debug_level != 0) && (iVar1 = ___ratelimit(_rs_14266,"sadm_set_bps_th"), iVar1 != 0))
    {
      printk("[TM][sadm_set_bps_th]input invalid parameter!\n");
    }
    return 1;
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][sadm_set_bps_th]input:threshold = %d\n",param_1,param_3,g_tm_debug_level,param_4);
  }
  iVar1 = tmOnuRegWrite(4,param_1,0,sadmRegTable);
  if (iVar1 == 0) {
    return 0;
  }
  if ((g_tm_debug_level != 0) && (iVar1 = ___ratelimit(_rs_14269,"sadm_set_bps_th"), iVar1 != 0)) {
    printk("[TM][sadm_set_bps_th]write reg failed!\n");
  }
  return 0xffffffff;
}

