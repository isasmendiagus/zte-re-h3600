// module: tm.ko
// function: tm_protocol_pkt_limit_pps_set @ 0x4bba8
// size: 92 bytes
//

undefined4
tm_protocol_pkt_limit_pps_set(undefined4 param_1,uint param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  if (7 < param_2) {
    return 0xffffffff;
  }
  iVar1 = adm_set_policing_enable(param_1,param_2,param_3 != 0,param_4,param_4);
  iVar2 = adm_set_pass_pktcnt_persec(param_1,param_2,param_4);
  if (iVar2 == 0 && iVar1 == 0) {
    return 0;
  }
  printk("tm_protocol_pkt_limit_pps_set fail\n");
  return 0xffffffff;
}

