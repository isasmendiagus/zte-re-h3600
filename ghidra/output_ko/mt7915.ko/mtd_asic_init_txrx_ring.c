// module: mt7915.ko
// function: mtd_asic_init_txrx_ring @ 0x1ca094
// size: 464 bytes
//

void mtd_asic_init_txrx_ring(int param_1)

{
  byte bVar1;
  undefined2 uVar2;
  byte *pbVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  int iVar7;
  uint uVar8;
  undefined4 uVar9;
  
  pbVar3 = (byte *)hc_get_hif_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
  chip_set_hif_dma(param_1,2,0);
  chip_wait_hif_dma_idle(param_1,0xff,100,1000);
  bVar1 = *pbVar3;
  if (bVar1 != 0) {
    uVar8 = 0;
    do {
      puVar6 = *(undefined4 **)(*(int *)(pbVar3 + 8) + uVar8 * 4);
      iVar4 = puVar6[0xb];
      uVar2 = *(undefined2 *)((int)puVar6 + 0x5a);
      uVar9 = *(undefined4 *)(puVar6[3] + 8);
      puVar6[1] = iVar4 + 0xc;
      puVar6[9] = iVar4 + 8;
      puVar6[4] = 0;
      puVar6[10] = 0;
      puVar6[0xc] = iVar4 + 4;
      hif_io_write32(*(undefined4 *)(param_1 + 0xa797a0),iVar4,uVar9);
      hif_io_write32(*(undefined4 *)(param_1 + 0xa797a0),puVar6[9],puVar6[10]);
      hif_io_write32(*(undefined4 *)(param_1 + 0xa797a0),puVar6[0xc],uVar2);
      if (0 < DebugLevel) {
        printk("-->TX_RING_%d[0x%x]: Attr:%d, Base=0x%x, Cnt=%d!\n",uVar8,puVar6[0xb],*puVar6,uVar9,
               uVar2);
      }
      uVar8 = uVar8 + 1;
    } while (bVar1 != uVar8);
  }
  if (pbVar3[1] != 0) {
    iVar4 = 0;
    do {
      iVar7 = *(int *)(*(int *)(pbVar3 + 4) + iVar4 * 4);
      iVar5 = *(int *)(iVar7 + 0x4c);
      uVar8 = (uint)*(ushort *)(iVar7 + 0x14);
      uVar9 = *(undefined4 *)(*(int *)(iVar7 + 0x18) + 8);
      *(undefined4 *)(iVar7 + 0x10) = 0;
      *(int *)(iVar7 + 0x3c) = iVar5 + 8;
      *(uint *)(iVar7 + 0x34) = uVar8 - 1;
      *(int *)(iVar7 + 8) = iVar5 + 0xc;
      *(int *)(iVar7 + 0x50) = iVar5 + 4;
      hif_io_write32(*(undefined4 *)(param_1 + 0xa797a0),iVar5,uVar9);
      hif_io_write32(*(undefined4 *)(param_1 + 0xa797a0),*(undefined4 *)(iVar7 + 0x3c),
                     *(undefined4 *)(iVar7 + 0x34));
      hif_io_write32(*(undefined4 *)(param_1 + 0xa797a0),*(undefined4 *)(iVar7 + 0x50),uVar8);
      if (0 < DebugLevel) {
        printk("-->RX_RING%d[0x%x]: Base=0x%x, Cnt=%d\n",iVar4,*(undefined4 *)(iVar7 + 0x4c),uVar9,
               uVar8);
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < (int)(uint)pbVar3[1]);
  }
  return;
}

