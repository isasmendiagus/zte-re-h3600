// module: tm.ko
// function: adm_get_down_drop_protocol_pktcnt @ 0x2bd68
// size: 168 bytes
//

int adm_get_down_drop_protocol_pktcnt(undefined4 *param_1)

{
  int iVar1;
  int iVar2;
  undefined4 local_14 [2];
  
  local_14[0] = 0;
  iVar1 = tmOnuRegRead(0x14,local_14,0,AdmRegTable);
  if (iVar1 == 0) {
    *param_1 = local_14[0];
    if (6 < g_tm_debug_level) {
      printk("[TM][adm_get_drop_protocol_PktCnt]output: dp_pkt_cnt=%d\n");
    }
  }
  else if ((g_tm_debug_level != 0) &&
          (iVar2 = ___ratelimit(_rs_7296,"adm_get_down_drop_protocol_pktcnt"), iVar2 != 0)) {
    printk("ERROR:(%s:%d) reg read fail\n","pp_adm.c",0x4dd);
  }
  return iVar1;
}

