// module: plat-zxylzb_9128S.ko
// function: dma_tx_free @ 0x19138
// size: 116 bytes
//

undefined4 dma_tx_free(int param_1,int param_2,uint param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = 5;
  do {
    if ((*(uint *)(tm_base + 0x1004c) & 0x200000) == 0) {
      *(uint *)(tm_base + 0x1004c) = param_3 | 0x200000 | param_2 << 0xc | param_1 << 0x14;
      return 0;
    }
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  printk("tx free %d/%d/%d failed\n",param_1,param_2,param_3,param_4);
  return 0xfffffff5;
}

