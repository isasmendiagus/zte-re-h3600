// module: mt7915.ko
// function: mt_asic_init_txrx_ring @ 0x1c9c70
// size: 392 bytes
//

void mt_asic_init_txrx_ring(int param_1)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  
  pbVar2 = (byte *)hc_get_hif_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
  chip_set_hif_dma(param_1,2,0);
  chip_wait_hif_dma_idle(param_1,0xff,100,1000);
  bVar1 = *pbVar2;
  if (bVar1 != 0) {
    uVar7 = 0;
    do {
      iVar5 = *(int *)(*(int *)(pbVar2 + 8) + uVar7 * 4);
      uVar7 = uVar7 + 1;
      iVar3 = *(int *)(iVar5 + 0x2c);
      uVar4 = *(undefined4 *)(*(int *)(iVar5 + 0xc) + 8);
      *(int *)(iVar5 + 0x30) = iVar3 + 4;
      *(int *)(iVar5 + 4) = iVar3 + 0xc;
      *(undefined4 *)(iVar5 + 0x10) = 0;
      *(undefined4 *)(iVar5 + 0x28) = 0;
      *(int *)(iVar5 + 0x24) = iVar3 + 8;
      hif_io_write32(*(undefined4 *)(param_1 + 0xa797a0),iVar3,uVar4);
      hif_io_write32(*(undefined4 *)(param_1 + 0xa797a0),*(undefined4 *)(iVar5 + 0x24),
                     *(undefined4 *)(iVar5 + 0x28));
      hif_io_write32(*(undefined4 *)(param_1 + 0xa797a0),*(undefined4 *)(iVar5 + 0x30),
                     *(undefined2 *)(iVar5 + 0x5a));
    } while (bVar1 != uVar7);
  }
  if (pbVar2[1] != 0) {
    iVar3 = 0;
    do {
      iVar6 = *(int *)(*(int *)(pbVar2 + 4) + iVar3 * 4);
      iVar5 = *(int *)(iVar6 + 0x4c);
      uVar7 = (uint)*(ushort *)(iVar6 + 0x14);
      uVar4 = *(undefined4 *)(*(int *)(iVar6 + 0x18) + 8);
      *(undefined4 *)(iVar6 + 0x10) = 0;
      *(int *)(iVar6 + 0x3c) = iVar5 + 8;
      *(uint *)(iVar6 + 0x34) = uVar7 - 1;
      *(int *)(iVar6 + 8) = iVar5 + 0xc;
      *(int *)(iVar6 + 0x50) = iVar5 + 4;
      hif_io_write32(*(undefined4 *)(param_1 + 0xa797a0),iVar5,uVar4);
      hif_io_write32(*(undefined4 *)(param_1 + 0xa797a0),*(undefined4 *)(iVar6 + 0x3c),
                     *(undefined4 *)(iVar6 + 0x34));
      hif_io_write32(*(undefined4 *)(param_1 + 0xa797a0),*(undefined4 *)(iVar6 + 0x50),uVar7);
      if (2 < DebugLevel) {
        printk("-->RX_RING%d[0x%x]: Base=0x%x, Cnt=%d\n",iVar3,*(undefined4 *)(iVar6 + 0x4c),uVar4,
               uVar7);
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < (int)(uint)pbVar2[1]);
  }
  return;
}

