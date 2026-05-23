// module: plat-zxylzb_9128S.ko
// function: check_pon_tm_queue @ 0x1a368
// size: 284 bytes
//

void check_pon_tm_queue(void)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  undefined4 extraout_r2;
  undefined4 in_r3;
  uint uVar4;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  
  if (uncache_tx_desc == 0) {
    uVar7 = __arm_ioremap(u32_JUMBO_BP_SIZE * u32_JUMBO_BPPE_POOL_SIZE +
                          u32_BP_SIZE * u32_BPPE_POOL_SIZE + pdt_mem_size + 0x405e0000 +
                          ZX_RESERVE_MEM_SIZE * -0x100000,0x20000);
    uncache_tx_desc = (int)uVar7;
    if (uncache_tx_desc == 0) {
      printk("ioremap failed\n",(int)((ulonglong)uVar7 >> 0x20),extraout_r2,in_r3);
      return;
    }
  }
  iVar2 = net_txq._52_4_;
  if (0x3ff < (uint)net_txq._52_4_) {
    iVar2 = 0x400;
  }
  if (iVar2 == 0) {
    return;
  }
  iVar3 = 0;
  uVar4 = (uint)(*(ushort *)(uncache_tx_desc + 0x1000c) >> 2);
  iVar5 = uncache_tx_desc + 0x10000;
  iVar6 = uncache_tx_desc + 0x10000;
  if (uVar4 == (uint)(*(int *)(uncache_tx_desc + 0x10008) << 9) >> 0x12) {
    do {
      iVar6 = iVar5;
      if (uVar4 < 0x20) break;
      iVar3 = iVar3 + 1;
      iVar6 = iVar5 + 0x10;
      if (iVar2 == iVar3) {
        return;
      }
      piVar1 = (int *)(iVar5 + 0x18);
      uVar4 = (uint)(*(ushort *)(iVar5 + 0x1c) >> 2);
      iVar5 = iVar6;
    } while (uVar4 == (uint)(*piVar1 << 9) >> 0x12);
  }
  printk("invalid desc index %d:\n");
  dump_desc_tx(iVar6);
  return;
}

