// module: plat-zxylzb_9128S.ko
// function: pon_tm_data_raw_send @ 0x1957c
// size: 672 bytes
//

/* WARNING: Restarted to delay deadcode elimination for space: ram */

undefined4 pon_tm_data_raw_send(int param_1,int param_2,int param_3)

{
  undefined1 uVar1;
  int iVar2;
  uint uVar3;
  byte bVar4;
  uint uVar5;
  byte bVar6;
  uint uVar7;
  size_t __n;
  void *__dest;
  
  __n = *(size_t *)(param_1 + 100);
  uVar3 = pon_tm_bmu_alloc_bp();
  if ((int)uVar3 < 0) {
    printk("alloc bp failed\n");
    return 0xffffffff;
  }
  if (*(uint *)((int)&bp_max_number + (*(byte *)(param_2 + 9) & 1) * 4) <= uVar3) {
    printk("invalid bp %d\n",uVar3);
    return 0xffffffff;
  }
  __dest = (void *)(u32_BP_SIZE * uVar3 +
                   pdt_mem_size + -0x3fadfff0 + ZX_RESERVE_MEM_SIZE * -0x100000);
  memcpy(__dest,*(void **)(param_1 + 0xd4),__n);
  *(byte *)(param_2 + 0xb) = *(byte *)(param_2 + 0xb) & 1 | 0x20;
  uVar1 = (undefined1)((int)uVar3 >> 7);
  uVar7 = __n;
  if (param_3 == 0) {
    if ((*(byte *)(param_2 + 6) & 4) != 0) {
      uVar5 = __n & 0x3fff;
      bVar6 = *(byte *)(param_2 + 0xe) & 1;
      goto LAB_0001962c;
    }
    bVar6 = *(byte *)(param_2 + 0xe) & 1;
    bVar4 = bVar6 ^ 1;
    if (0x3f < (int)__n) {
      bVar4 = 0;
    }
    if (bVar4 == 0) {
      uVar5 = __n & 0x3fff;
      goto LAB_0001962c;
    }
    if (__n != 0x40) {
      __memzero((int)__dest + __n);
      uVar5 = 0x40;
      bVar6 = *(byte *)(param_2 + 0xe) & 1;
      uVar7 = 0x40;
      goto LAB_0001962c;
    }
    uVar5 = 0x40;
    *(byte *)(param_2 + 7) = *(byte *)(param_2 + 7) & 1 | (byte)((uVar3 & 0x7f) << 1);
    *(undefined1 *)(param_2 + 8) = uVar1;
    *(ushort *)(param_2 + 0xc) = *(ushort *)(param_2 + 0xc) & 3 | 0x100;
    uVar7 = uVar5;
  }
  else {
    uVar5 = __n & 0x3fff;
    bVar6 = *(byte *)(param_2 + 0xe) & 1;
LAB_0001962c:
    *(undefined1 *)(param_2 + 8) = uVar1;
    *(byte *)(param_2 + 7) = *(byte *)(param_2 + 7) & 1 | (byte)((uVar3 & 0x7f) << 1);
    *(ushort *)(param_2 + 0xc) = *(ushort *)(param_2 + 0xc) & 3 | (ushort)(uVar5 << 2);
    if (bVar6 != 0) goto LAB_00019660;
  }
  *(uint *)(param_2 + 8) = *(uint *)(param_2 + 8) & 0xff8001ff | uVar5 << 9;
LAB_00019660:
  if (0 < pon_tm_net_debug) {
    printk("Send skb %x data %x,len %u buf size %u, BP %d \naddr %x,off %x,c %d\n",param_1,
           *(undefined4 *)(param_1 + 0xd4),uVar7,*(int *)(param_1 + 0xcc) - *(int *)(param_1 + 0xd0)
           ,uVar3,__dest,*(byte *)(param_2 + 0xb) >> 1,*(byte *)(param_1 + 0x72) & 1);
    printk("pri %x",0);
    printk("f %x\n",0);
    dump_desc_tx(param_2);
    dump_net_data(__dest,uVar7);
    pon_tm_net_debug = pon_tm_net_debug + -1;
  }
  iVar2 = param_3 * 0x1c;
  *(int *)(net_txq + iVar2 + 0x10) = *(int *)(net_txq + iVar2 + 0x10) + 1;
  dma_cache_maint(__dest,__n);
  soft_insert_tx_1desc(param_2,param_3);
  *(int *)(net_txq + iVar2 + 0x18) = *(int *)(net_txq + iVar2 + 0x18) + 1;
  bmu_status._24_4_ = bmu_status._24_4_ + 1;
  return 0;
}

