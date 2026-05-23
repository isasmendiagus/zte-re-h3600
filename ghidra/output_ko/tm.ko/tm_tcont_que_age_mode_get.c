// module: tm.ko
// function: tm_tcont_que_age_mode_get @ 0x53fec
// size: 96 bytes
//

undefined4 tm_tcont_que_age_mode_get(int param_1,uint *param_2)

{
  int iVar1;
  undefined4 uVar2;
  int local_c;
  
  local_c = 2;
  if (param_1 == 0) {
    iVar1 = sch_get_hw_up_age_mode();
  }
  else {
    iVar1 = sch_get_hw_dn_age_mode(&local_c);
  }
  if (iVar1 == 0) {
    *param_2 = (uint)(local_c != 0);
    uVar2 = 0;
  }
  else {
    printk("tm_tcont_que_age_mode_get fail\n");
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

