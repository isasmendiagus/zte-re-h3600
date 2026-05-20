// module: tm.ko
// function: tm_tcont_que_sharp_set @ 0x51868
// size: 148 bytes
//

undefined4 tm_tcont_que_sharp_set(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = sch_set_shp_fill_time(0x1869);
  if (iVar1 == 0) {
    iVar1 = sch_set_spend_byte(0x14);
    if (iVar1 != 0) {
      printk("tm_tcont_que_sharp_set spend_byte fail\n");
      return 0xffffffff;
    }
    iVar1 = sch_set_up_pq_sharp_fill_rate(param_1,param_2,param_3);
    if (iVar1 == 0) {
      uVar2 = tm_getFillcap(param_3);
      iVar1 = sch_set_up_pq_sharp_bucket_cap(param_1,param_2,uVar2);
      if (iVar1 == 0) {
        return 0;
      }
    }
  }
  printk("tm_tcont_que_sharp_set fail\n");
  return 0xffffffff;
}

