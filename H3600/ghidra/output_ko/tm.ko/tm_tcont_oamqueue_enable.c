// module: tm.ko
// function: tm_tcont_oamqueue_enable @ 0x4d1d4
// size: 244 bytes
//

undefined4 tm_tcont_oamqueue_enable(int param_1)

{
  int iVar1;
  
  iVar1 = sch_set_shp_fill_time(0x1869);
  if (iVar1 != 0) {
    printk("tm_tcont_que_sharp_set fail\n");
    return 0xffffffff;
  }
  iVar1 = sch_set_spend_byte(0x14);
  if (iVar1 != 0) {
    printk("tm_tcont_que_sharp_set spend_byte fail\n");
    return 0xffffffff;
  }
  if (param_1 == 0) {
    iVar1 = sch_set_up_pq_sharp_fill_rate(1,0,0);
    if (iVar1 != 0) goto LAB_0004d2b4;
    iVar1 = sch_set_up_pq_sharp_bucket_cap(1,0,0);
    if (iVar1 != 0) goto LAB_0004d240;
  }
  else if (param_1 == 1) {
    iVar1 = sch_set_up_pq_sharp_fill_rate(1,0,0x1fffff);
    if (iVar1 == 0) {
      iVar1 = sch_set_up_pq_sharp_bucket_cap(1,0,0x3fffff);
      if (iVar1 == 0) {
        return 0;
      }
LAB_0004d240:
      printk("sch_set_up_pq_sharp_bucket_cap fail\n");
      return 0xffffffff;
    }
LAB_0004d2b4:
    printk("tm_tcont_oamqueue_enable fail\n");
    return 0xffffffff;
  }
  return 0;
}

