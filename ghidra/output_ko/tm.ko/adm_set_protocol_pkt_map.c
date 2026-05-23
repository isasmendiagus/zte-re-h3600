// module: tm.ko
// function: adm_set_protocol_pkt_map @ 0x2b0a4
// size: 364 bytes
//

undefined4 adm_set_protocol_pkt_map(uint param_1,uint param_2,uint param_3)

{
  uint uVar1;
  uint uVar2;
  uint local_1c [2];
  
  local_1c[0] = 0;
  if (g_tm_debug_level < 7) {
    uVar2 = param_3;
    if (param_3 < 8) {
      uVar2 = param_2;
    }
    if (param_1 < 2 && uVar2 < 8) {
LAB_0002b100:
      if (param_1 == 0) {
        tmOnuRegRead(10,local_1c,0,AdmRegTable);
        local_1c[0] = local_1c[0] & ~(7 << (param_2 * 3 & 0xff)) | param_3 << (param_2 * 3 & 0xff);
        uVar2 = tmOnuRegWrite(10,local_1c[0],0,AdmRegTable);
      }
      else {
        uVar1 = tmOnuRegRead(9,local_1c,0,AdmRegTable);
        local_1c[0] = local_1c[0] & ~(7 << (param_2 * 3 & 0xff)) | param_3 << (param_2 * 3 & 0xff);
        uVar2 = tmOnuRegWrite(9,local_1c[0],0,AdmRegTable);
        uVar2 = uVar2 | uVar1;
      }
      if (uVar2 == 0) {
        return 0;
      }
      if (6 < g_tm_debug_level) {
        printk("[TM][adm_set_protocol_pkt_map]indirect access failed\n");
        return 0xffffffff;
      }
      return 0xffffffff;
    }
  }
  else {
    printk("[TM][adm_set_protocol_pkt_map]input:direction =%d, cpu_queid = %d, pps_bucketnum = %d\n"
           ,param_1,param_2,param_3);
    uVar2 = param_3;
    if (param_3 < 8) {
      uVar2 = param_2;
    }
    if (param_1 < 2 && uVar2 < 8) goto LAB_0002b100;
    if (6 < g_tm_debug_level) {
      printk("[TM][adm_set_protocol_pkt_map]input invalid parameter!\n");
    }
  }
  return 1;
}

