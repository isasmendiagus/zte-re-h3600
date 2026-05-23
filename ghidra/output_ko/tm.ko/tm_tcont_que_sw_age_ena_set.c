// module: tm.ko
// function: tm_tcont_que_sw_age_ena_set @ 0x54404
// size: 44 bytes
//

undefined4 tm_tcont_que_sw_age_ena_set(int param_1)

{
  int iVar1;
  
  iVar1 = sch_set_sw_age_enable(param_1 != 0);
  if (iVar1 == 0) {
    return 0;
  }
  printk("tm_tcont_que_sw_age_ena_set fail\n");
  return 0xffffffff;
}

