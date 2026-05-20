// module: tm.ko
// function: tm_tcont_que_dwrr_ena_set @ 0x45ebc
// size: 44 bytes
//

undefined4 tm_tcont_que_dwrr_ena_set(int param_1)

{
  int iVar1;
  
  iVar1 = sch_set_secsch_dwrr_enable(param_1 != 0);
  if (iVar1 == 0) {
    return 0;
  }
  printk("tm_tcont_que_dwrr_ena_set fail\n");
  return 0xffffffff;
}

