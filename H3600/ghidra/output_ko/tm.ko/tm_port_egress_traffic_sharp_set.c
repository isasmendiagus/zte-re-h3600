// module: tm.ko
// function: tm_port_egress_traffic_sharp_set @ 0x516c0
// size: 176 bytes
//

undefined4 tm_port_egress_traffic_sharp_set(uint param_1,uint param_2,int param_3)

{
  bool bVar1;
  int iVar2;
  undefined4 uVar3;
  
  if (param_3 == 0) {
    bVar1 = false;
    param_2 = 0;
  }
  else if (param_2 < 2) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if (7 < param_1) {
    bVar1 = true;
  }
  if (bVar1) {
    printk("tm_port_egress_traffic_sharp_set fail, error port %d\n",param_1);
    return 0xffffffff;
  }
  iVar2 = sch_set_shp_fill_time(0x1869);
  if (iVar2 == 0) {
    if (param_2 == 0) {
      param_3 = 0x1f4000;
    }
    iVar2 = sch_set_dn_tcont_sharp_fill_rate(param_1,param_3);
    if (iVar2 == 0) {
      uVar3 = tm_getFillcap(param_3);
      iVar2 = sch_set_dn_tcont_sharp_bucket_cap(param_1,uVar3);
      if (iVar2 == 0) {
        return 0;
      }
    }
  }
  printk("tm_port_egress_traffic_sharp_set fail\n");
  return 0xffffffff;
}

