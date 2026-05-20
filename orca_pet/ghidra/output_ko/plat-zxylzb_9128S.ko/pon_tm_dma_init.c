// module: plat-zxylzb_9128S.ko
// function: pon_tm_dma_init @ 0x18e94
// size: 352 bytes
//

undefined4 pon_tm_dma_init(void)

{
  *(uint *)(tm_base + 0x10000) = *(uint *)(tm_base + 0x10000) | 0x2f0000;
  *(undefined4 *)(tm_base + 0x10028) = 1;
  *(undefined4 *)(tm_base + 0x1002c) = 1;
  *(undefined4 *)(tm_base + 0x10030) = 50000;
  *(undefined4 *)(tm_base + 0x10034) = 0x40;
  *(undefined4 *)(tm_set_onu_mac + tm_base + 4) = 0x7f;
  *(undefined4 *)(tm_base + 0x10020) = 0x20;
  *(undefined4 *)(tm_base + 0x10024) = 0x20;
  *(int *)(tm_base + 0x10050) =
       u32_JUMBO_BP_SIZE * u32_JUMBO_BPPE_POOL_SIZE +
       u32_BP_SIZE * u32_BPPE_POOL_SIZE + pdt_mem_size + 0x405e0000 +
       ZX_RESERVE_MEM_SIZE * -0x100000;
  *(int *)(tm_base + 0x10060) =
       u32_JUMBO_BP_SIZE * u32_JUMBO_BPPE_POOL_SIZE +
       u32_BP_SIZE * u32_BPPE_POOL_SIZE + pdt_mem_size + 0x405f0000 +
       ZX_RESERVE_MEM_SIZE * -0x100000;
  *(undefined4 *)(tm_base + 0x10388) = 0x131217;
  *(undefined4 *)(tm_base + 0x1003c) = 0x400040;
  return 0;
}

