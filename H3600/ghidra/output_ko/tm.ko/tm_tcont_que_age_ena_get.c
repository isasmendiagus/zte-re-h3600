// module: tm.ko
// function: tm_tcont_que_age_ena_get @ 0x53f44
// size: 96 bytes
//

undefined4 tm_tcont_que_age_ena_get(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  int local_c;
  
  local_c = 0;
  if (param_1 == 0) {
    iVar1 = sch_get_hw_up_age_enable();
  }
  else {
    iVar1 = sch_get_hw_dn_age_enable(&local_c);
  }
  if (iVar1 == 0) {
    *(bool *)param_2 = local_c != 0;
    uVar2 = 0;
  }
  else {
    printk("tm_tcont_que_age_ena_get fail\n");
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

