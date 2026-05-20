// module: tm.ko
// function: tm_tcont_que_hw_age_time_get @ 0x543e0
// size: 36 bytes
//

undefined4 tm_tcont_que_hw_age_time_get(void)

{
  int iVar1;
  
  iVar1 = sch_get_hw_age_time();
  if (iVar1 == 0) {
    return 0;
  }
  printk("tm_tcont_que_age_mode_get fail\n");
  return 0xffffffff;
}

