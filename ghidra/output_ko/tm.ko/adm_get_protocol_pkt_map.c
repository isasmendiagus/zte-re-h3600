// module: tm.ko
// function: adm_get_protocol_pkt_map @ 0x2b214
// size: 200 bytes
//

undefined4 adm_get_protocol_pkt_map(int param_1,uint param_2,uint *param_3)

{
  undefined4 uVar1;
  bool bVar2;
  bool bVar3;
  uint local_1c [2];
  
  local_1c[0] = 0;
  if (g_tm_debug_level < 7) {
    bVar3 = 6 < param_2;
    bVar2 = param_2 == 7;
    if (param_2 < 8) {
      bVar3 = param_1 != 0;
      bVar2 = param_1 == 1;
    }
    if (!bVar3 || bVar2) {
LAB_0002b25c:
      if (param_1 == 0) {
        uVar1 = 10;
      }
      else {
        uVar1 = 9;
      }
      tmOnuRegRead(uVar1,local_1c,0,AdmRegTable);
      *param_3 = local_1c[0] >> (param_2 * 3 & 0xff) & 7;
      return 0;
    }
  }
  else {
    printk("[TM][adm_set_protocol_pkt_map]input:direction =%d, cpu_queid = %d,\n",param_1,param_2);
    bVar3 = 6 < param_2;
    bVar2 = param_2 == 7;
    if (param_2 < 8) {
      bVar3 = param_1 != 0;
      bVar2 = param_1 == 1;
    }
    if (!bVar3 || bVar2) goto LAB_0002b25c;
    if (6 < g_tm_debug_level) {
      printk("[TM][adm_set_protocol_pkt_map]input invalid parameter!\n");
    }
  }
  return 1;
}

