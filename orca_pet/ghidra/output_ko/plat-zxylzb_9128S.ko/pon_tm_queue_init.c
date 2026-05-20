// module: plat-zxylzb_9128S.ko
// function: pon_tm_queue_init @ 0x1a704
// size: 248 bytes
//

void pon_tm_queue_init(void)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  
  puVar3 = (undefined4 *)(queue_ctrl + 4);
  iVar4 = u32_BP_SIZE * u32_BPPE_POOL_SIZE + u32_JUMBO_BP_SIZE * u32_JUMBO_BPPE_POOL_SIZE +
          pdt_mem_size + ZX_RESERVE_MEM_SIZE * -0x100000;
  iVar2 = iVar4 + -0x3fae0000;
  do {
    iVar1 = iVar2 + 0x20000;
    puVar3[-1] = iVar2;
    iVar2 = iVar2 + 0x4000;
    puVar3[0xf] = iVar1;
    *puVar3 = 0;
    puVar3[0x10] = 0;
    puVar3 = puVar3 + 2;
  } while (iVar2 != iVar4 + -0x3fac0000);
  net_txq._28_4_ = iVar4 + -0x3fa10000;
  net_txq._20_4_ = 0;
  net_txq._0_4_ = iVar4 + -0x3fa20000;
  net_txq._48_4_ = 1;
  printk("DMA_DN_DESC_CNT = 0x%x\n",*(undefined4 *)(tm_base + 0x10068));
  printk("DMA_UP_DESC_CNT = 0x%x\n",*(undefined4 *)(tm_base + 0x10058));
  return;
}

