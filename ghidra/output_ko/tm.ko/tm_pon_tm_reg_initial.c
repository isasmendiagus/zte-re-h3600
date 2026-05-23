// module: tm.ko
// function: tm_pon_tm_reg_initial @ 0x4d5fc
// size: 236 bytes
//

uint tm_pon_tm_reg_initial
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  
  uVar1 = pon_tm_set_queue_int_mask(0,0,param_3,param_4,param_4);
  uVar2 = pon_tm_set_queue_int_mask(0,1);
  uVar3 = pon_tm_set_queue_int_mask(1,2);
  uVar3 = uVar2 | uVar1 | uVar3;
  if (uVar3 != 0) {
    printk("ERROR:(%s:%d) reg read fail\n","tm_api.c",0x61);
    return uVar3;
  }
  uVar1 = pon_tm_set_dma_des_int_mask(1,1);
  uVar2 = pon_tm_set_dma_des_int_mask(1,0);
  iVar4 = 0;
  if ((uVar2 | uVar1) == 0) {
    do {
      uVar1 = pon_tm_set_fifo_int_mask(iVar4,1);
      iVar4 = iVar4 + 1;
      if (uVar1 != 0) {
        printk("ERROR:(%s:%d) reg read fail\n","tm_api.c",0x6c);
        return uVar1;
      }
    } while (iVar4 != 8);
    pon_tm_set_gap_add(4);
    return 0;
  }
  printk("ERROR:(%s:%d) reg read fail\n","tm_api.c",0x66);
  return uVar2 | uVar1;
}

