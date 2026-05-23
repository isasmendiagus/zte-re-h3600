// module: tm.ko
// function: tm_tcont_que_hw_age_time_set @ 0x5404c
// size: 36 bytes
//

undefined4 tm_tcont_que_hw_age_time_set(void)

{
  int iVar1;
  
  iVar1 = sch_set_hw_age_time();
  if (iVar1 == 0) {
    return 0;
  }
  printk("tm_tcont_que_age_mode_get fail\n");
  return 0xffffffff;
}

