// module: tm.ko
// function: sadm_get_brgunsapt_pps_pktnum @ 0x24758
// size: 260 bytes
//

undefined4 sadm_get_brgunsapt_pps_pktnum(uint param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 local_14;
  
  local_14 = 0;
  if (param_1 < 8) {
    if (6 < g_tm_debug_level) {
      printk("[TM][sadm_get_brgunsapt_pps_pktnum]input:reg_array = %d\n",param_1);
    }
    iVar2 = tmOnuRegRead(0xd,&local_14,param_1,sadmRegTable);
    if (iVar2 != 0) {
      if ((g_tm_debug_level != 0) &&
         (iVar2 = ___ratelimit(_rs_14443,"sadm_get_brgunsapt_pps_pktnum"), iVar2 != 0)) {
        printk("[TM][sadm_get_brgunsapt_pps_pktnum]write reg failed!\n");
      }
      return 0xffffffff;
    }
    *param_2 = local_14;
    uVar1 = 0;
    if (6 < g_tm_debug_level) {
      printk("[TM][sadm_get_brgunsapt_pps_pktnum]output:max = %d\n");
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar1 = 1;
  }
  else {
    printk("[TM][sadm_get_brgunsapt_pps_pktnum]input invalid parameter!\n");
    uVar1 = 1;
  }
  return uVar1;
}

