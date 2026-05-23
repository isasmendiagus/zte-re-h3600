// module: tm.ko
// function: tm_tcont_que_age_ena_set @ 0x53efc
// size: 72 bytes
//

undefined4 tm_tcont_que_age_ena_set(int param_1,int param_2)

{
  int iVar1;
  
  if (param_1 == 0) {
    iVar1 = sch_set_hw_up_age_enable();
    if (iVar1 == 0) {
      return 0;
    }
  }
  else {
    iVar1 = sch_set_hw_dn_age_enable(param_2 != 0);
    if (iVar1 == 0) {
      return 0;
    }
  }
  printk("tm_tcont_que_age_ena_set fail\n");
  return 0xffffffff;
}

