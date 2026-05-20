// module: tm.ko
// function: tm_protocol_pkt_limit_pps_get @ 0x4bc04
// size: 136 bytes
//

undefined4
tm_protocol_pkt_limit_pps_get
          (undefined4 param_1,uint param_2,undefined4 param_3,undefined4 *param_4)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int local_20;
  undefined4 local_1c;
  
  local_1c = 0;
  if (param_2 < 8) {
    iVar1 = adm_get_policing_enable(param_1,param_2,&local_20);
    iVar2 = adm_get_pass_pktcnt_persec(param_1,param_2,&local_1c);
    if (iVar2 == 0 && iVar1 == 0) {
      *(bool *)param_3 = local_20 != 0;
      *param_4 = local_1c;
      uVar3 = 0;
    }
    else {
      printk("tm_protocol_pkt_limit_pps_get fail\n");
      uVar3 = 0xffffffff;
    }
  }
  else {
    uVar3 = 0xffffffff;
  }
  return uVar3;
}

