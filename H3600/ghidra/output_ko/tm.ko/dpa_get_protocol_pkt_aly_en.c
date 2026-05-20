// module: tm.ko
// function: dpa_get_protocol_pkt_aly_en @ 0x274d4
// size: 260 bytes
//

int dpa_get_protocol_pkt_aly_en(uint param_1,uint *param_2)

{
  int iVar1;
  int iVar2;
  uint local_14;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][dpa_get_protocol_pkt_aly_en]input: type_id = %d\n",param_1);
  }
  if (param_1 < 7) {
    iVar1 = tmOnuRegRead(param_1,&local_14,0,dpaRegTable);
    if (iVar1 == 0) {
      *param_2 = local_14 & 1;
      if (g_tm_debug_level < 7) {
        return 0;
      }
      printk("[TM][dpa_get_protocol_pkt_aly_en]output: act_val = %d\n");
    }
    else {
      if ((g_tm_debug_level == 0) ||
         (iVar2 = ___ratelimit(_rs_6963,"dpa_get_protocol_pkt_aly_en"), iVar2 == 0)) {
        return iVar1;
      }
      printk("[TM][dpa_get_protocol_pkt_aly_en]write reg failed!\n");
    }
  }
  else {
    if ((g_tm_debug_level != 0) &&
       (iVar1 = ___ratelimit(_rs_6960,"dpa_get_protocol_pkt_aly_en"), iVar1 != 0)) {
      printk("[TM][dpa_get_protocol_pkt_aly_en]input invalid parameter!\n");
    }
    iVar1 = 1;
  }
  return iVar1;
}

