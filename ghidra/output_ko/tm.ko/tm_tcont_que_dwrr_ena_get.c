// module: tm.ko
// function: tm_tcont_que_dwrr_ena_get @ 0x4bd0c
// size: 84 bytes
//

undefined4 tm_tcont_que_dwrr_ena_get(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  int local_c;
  
  local_c = 0;
  iVar1 = sch_get_secsch_dwrr_enable(&local_c);
  if (iVar1 == 0) {
    *(bool *)param_1 = local_c != 0;
    uVar2 = 0;
  }
  else {
    printk("tm_tcont_que_dwrr_ena_get fail\n");
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

