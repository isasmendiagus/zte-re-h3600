// module: tm.ko
// function: tm_tcont_que_age_mode_set @ 0x53fa4
// size: 72 bytes
//

undefined4 tm_tcont_que_age_mode_set(int param_1,int param_2)

{
  int iVar1;
  
  if (param_1 == 0) {
    iVar1 = sch_set_hw_up_age_mode();
    if (iVar1 == 0) {
      return 0;
    }
  }
  else {
    iVar1 = sch_set_hw_dn_age_mode(param_2 != 0);
    if (iVar1 == 0) {
      return 0;
    }
  }
  printk("tm_tcont_que_age_mode_set fail\n");
  return 0xffffffff;
}

