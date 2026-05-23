// module: plat-zxylzb_9128S.ko
// function: pon_tm_bmu_init @ 0x183ec
// size: 576 bytes
//

undefined4 pon_tm_bmu_init(void)

{
  int iVar1;
  undefined4 in_r3;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  iVar1 = ZX_RESERVE_MEM_SIZE * 0x100000;
  iVar2 = pdt_mem_size + -0x40000000;
  bppe_va_addr = iVar2 + ZX_RESERVE_MEM_SIZE * -0x100000;
  if (u32_BPPE_POOL_SIZE != 0) {
    uVar3 = 0;
    uVar4 = 0;
    do {
      iVar1 = uVar3 * 2;
      uVar3 = uVar3 + 1;
      *(short *)(bppe_va_addr + iVar1) = (short)uVar4;
      uVar4 = (uVar3 & 0xff) << 8 | uVar3 >> 8 & 0xff;
    } while (uVar3 < u32_BPPE_POOL_SIZE);
    iVar1 = ZX_RESERVE_MEM_SIZE << 0x14;
    iVar2 = pdt_mem_size + -0x40000000;
  }
  jumbo_bppe_va_addr = (iVar2 + 0x10000) - iVar1;
  uVar4 = 0;
  if (u32_JUMBO_BPPE_POOL_SIZE != 0) {
    uVar4 = 0;
    uVar3 = 0;
    do {
      iVar1 = uVar4 * 2;
      uVar4 = uVar4 + 1;
      *(short *)(jumbo_bppe_va_addr + iVar1) = (short)uVar3;
      uVar3 = (uVar4 & 0xff) << 8 | uVar4 >> 8 & 0xff;
    } while (uVar4 < u32_JUMBO_BPPE_POOL_SIZE);
  }
  dma_cache_maint(bppe_va_addr,0x20000,1,uVar4,in_r3);
  *(undefined4 *)(tm_base + 0x8000) = 0;
  *(undefined4 *)(tm_base + 0x8004) = 0x104c040;
  *(undefined4 *)(tm_base + 0x8008) = 0x104c040;
  *(uint *)(tm_base + 0x8058) = (u32_BPPE_POOL_SIZE >> 5) - 1;
  *(uint *)(tm_base + 0x805c) = (u32_JUMBO_BPPE_POOL_SIZE >> 5) - 1;
  *(int *)(tm_base + 0xf4) = pdt_mem_size + 0x40520000 + ZX_RESERVE_MEM_SIZE * -0x100000;
  *(uint *)(tm_base + 0xf8) =
       u32_BP_SIZE * u32_BPPE_POOL_SIZE + pdt_mem_size + 0x40520000 +
       ZX_RESERVE_MEM_SIZE * -0x100000;
  *(int *)(tm_base + 0xe8) = pdt_mem_size + 0x40000000 + ZX_RESERVE_MEM_SIZE * -0x100000;
  *(int *)(tm_base + 0xec) = pdt_mem_size + 0x40010000 + ZX_RESERVE_MEM_SIZE * -0x100000;
  *(uint *)(tm_base + 0xfc) = u32_BP_SIZE | u32_JUMBO_BP_SIZE << 0x10;
  *(uint *)(tm_base + 0x8048) = u32_BPPE_POOL_SIZE << 0x10;
  *(uint *)(tm_base + 0x804c) = u32_JUMBO_BPPE_POOL_SIZE << 0x10;
  __memzero(bmu_status,0x28);
  return 0;
}

