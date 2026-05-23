// module: plat-zxylzb_9128S.ko
// function: tm_pon_tm_init @ 0x1aaf4
// size: 260 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int tm_pon_tm_init(void)

{
  int iVar1;
  
  printk("pon tm init\n");
  *(undefined4 *)(tm_base + 0x128) = 0x1fff;
  *(undefined4 *)(tm_base + 0x130) = 0x1fffff;
  (*_request_threaded_irq)(0x66665b0);
  pon_tm_red_init();
  pon_tm_dma_init();
  iVar1 = pon_tm_bmu_init();
  if (-1 < iVar1) {
    *(int *)(tm_base + 0xf0) =
         u32_JUMBO_BP_SIZE * u32_JUMBO_BPPE_POOL_SIZE +
         u32_BP_SIZE * u32_BPPE_POOL_SIZE + pdt_mem_size + 0x40520000 +
         ZX_RESERVE_MEM_SIZE * -0x100000;
    pon_tm_bmu_enable();
    *(undefined4 *)(tm_base + 0xc008) = 0;
    pon_tm_net_init();
    pon_tm_int_init();
    return 0;
  }
  printk("init bmu moduel failed %d\n",iVar1);
  return iVar1;
}

