// module: tm.ko
// function: dpa_get_protocol_cpu_pps_en @ 0x276c0
// size: 156 bytes
//

int dpa_get_protocol_cpu_pps_en(uint *param_1)

{
  int iVar1;
  int iVar2;
  uint local_14 [2];
  
  iVar1 = tmOnuRegRead(7,local_14,0,dpaRegTable);
  if (iVar1 == 0) {
    *param_1 = local_14[0] & 1;
    if (6 < g_tm_debug_level) {
      printk("[TM][dpa_get_protocol_cpu_pps_en]output: pps_en = %d\n");
    }
  }
  else if ((g_tm_debug_level != 0) &&
          (iVar2 = ___ratelimit(_rs_6979,"dpa_get_protocol_cpu_pps_en"), iVar2 != 0)) {
    printk("[TM][dpa_get_protocol_cpu_pps_en]write reg failed!\n");
  }
  return iVar1;
}

