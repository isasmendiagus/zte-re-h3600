// module: tm.ko
// function: tm_port_ingress_unkown_unida_pps_set @ 0x51e78
// size: 140 bytes
//

undefined4 tm_port_ingress_unkown_unida_pps_set(undefined4 param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  undefined1 auStack_18 [4];
  uint local_14;
  
  iVar1 = getPort(param_1,auStack_18);
  if ((iVar1 == 0) && (local_14 < 8)) {
    iVar1 = sadm_set_brgun_unidapt_pps_en(local_14,param_2 != 0);
    if ((iVar1 == 0) && (iVar1 = sadm_set_brgun_unidapt_pps_pktnum(local_14,param_3), iVar1 == 0)) {
      return 0;
    }
    printk("tm_port_ingress_unkown_unida_pps_set fail\n");
  }
  else {
    printk("tm_port_ingress_unkown_unida_pps_set fail, error port %d\n",param_1);
  }
  return 0xffffffff;
}

