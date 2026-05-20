// module: tm.ko
// function: tm_port_ingress_unkown_unida_pps_get @ 0x51f04
// size: 160 bytes
//

undefined4
tm_port_ingress_unkown_unida_pps_get(undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  int iVar1;
  undefined4 local_20;
  int local_1c;
  undefined1 auStack_18 [4];
  uint local_14;
  
  iVar1 = getPort(param_1,auStack_18);
  if ((iVar1 == 0) && (local_14 < 8)) {
    iVar1 = sadm_get_brgun_unidapt_pps_en(local_14,&local_1c);
    if (iVar1 == 0) {
      *(bool *)param_2 = local_1c != 0;
      iVar1 = sadm_get_brgun_unidapt_pps_pktnum(local_14,&local_20);
      if (iVar1 == 0) {
        *param_3 = local_20;
        return 0;
      }
    }
    printk("tm_port_ingress_unkown_unida_pps_get fail\n");
  }
  else {
    printk("tm_port_ingress_unkown_unida_pps_get fail, error port %d\n",param_1);
  }
  return 0xffffffff;
}

