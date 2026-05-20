// module: tm.ko
// function: dpa_set_protocol_cpu_pps_en @ 0x275e8
// size: 200 bytes
//

int dpa_set_protocol_cpu_pps_en
              (uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][dpa_set_protocol_cpu_pps_en]input:pps_en = %d\n",param_1,param_3,g_tm_debug_level,
           param_4);
  }
  if (1 < param_1) {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_6969,"dpa_set_protocol_cpu_pps_en"), iVar1 != 0)) {
      printk("[TM][dpa_set_protocol_cpu_pps_en]input invalid parameter!\n");
    }
    return 1;
  }
  iVar1 = tmOnuRegWrite(7,param_1,0,dpaRegTable);
  if (((iVar1 != 0) && (g_tm_debug_level != 0)) &&
     (iVar2 = ___ratelimit(_rs_6972,"dpa_set_protocol_cpu_pps_en"), iVar2 != 0)) {
    printk("[TM][dpa_set_protocol_cpu_pps_en]write reg failed!\n");
    return iVar1;
  }
  return iVar1;
}

