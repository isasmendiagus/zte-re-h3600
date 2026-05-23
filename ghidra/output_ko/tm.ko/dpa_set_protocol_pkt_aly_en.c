// module: tm.ko
// function: dpa_set_protocol_pkt_aly_en @ 0x273e8
// size: 228 bytes
//

int dpa_set_protocol_pkt_aly_en(uint param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  bool bVar3;
  bool bVar4;
  
  if (6 < g_tm_debug_level) {
    printk("[TM][dpa_set_protocol_pkt_aly_en]input: type_id = %d, act_val = %d\n",param_1,param_2);
  }
  bVar4 = param_2 != 0;
  bVar3 = param_2 == 1;
  if (param_2 < 2) {
    bVar4 = 5 < param_1;
    bVar3 = param_1 == 6;
  }
  if (!bVar4 || bVar3) {
    iVar1 = tmOnuRegWrite(param_1,param_2,0,dpaRegTable);
    if (((iVar1 != 0) && (g_tm_debug_level != 0)) &&
       (iVar2 = ___ratelimit(_rs_6952,"dpa_set_protocol_pkt_aly_en"), iVar2 != 0)) {
      printk("[TM][dpa_set_protocol_pkt_aly_en]write reg failed!\n");
      return iVar1;
    }
    return iVar1;
  }
  if ((g_tm_debug_level != 0) &&
     (iVar1 = ___ratelimit(&_rs_6949,"dpa_set_protocol_pkt_aly_en"), iVar1 != 0)) {
    printk("[TM][dpa_set_protocol_pkt_aly_en]input invalid parameter!\n");
  }
  return 1;
}

