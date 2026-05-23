// module: tm.ko
// function: tm_tcont_sharp_set @ 0x518fc
// size: 180 bytes
//

undefined4 tm_tcont_sharp_set(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = sch_set_shp_fill_time(0x1869);
  if (iVar1 != 0) {
    printk("tm_tcont_que_sharp_set fail\n");
    return 0xffffffff;
  }
  iVar1 = sch_set_spend_byte(0x14);
  if (iVar1 == 0) {
    if (param_2 == 0) {
      param_2 = 0x1f4000;
    }
    iVar1 = sch_set_up_tcont_sharp_fill_rate(param_1,param_2);
    if (iVar1 == 0) {
      uVar2 = tm_getFillcap(param_2);
      iVar1 = sch_set_up_tcont_sharp_bucket_cap(param_1,uVar2);
      if (iVar1 == 0) {
        return 0;
      }
      printk("tm_port_egress_traffic_sharp_set fail\n");
      return 0xffffffff;
    }
    printk("tm_tcont_sharp_set fail\n");
    return 0xffffffff;
  }
  printk("tm_tcont_sharp_set spend_byte fail\n");
  return 0xffffffff;
}

