// module: mt7915.ko
// function: pci_hif_chip_exit @ 0x1d116c
// size: 496 bytes
//

void pci_hif_chip_exit(int param_1)

{
  byte bVar1;
  byte bVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  
  uVar3 = *(undefined4 *)(param_1 + 0xcc);
  bVar1 = *(byte *)(param_1 + 0x10);
  bVar2 = *(byte *)(param_1 + 0x11);
  if (2 < DebugLevel) {
    printk("--> %s\n","pci_free_txrx_ring_mem");
  }
  if (bVar2 != 0) {
    uVar5 = 0;
    uVar6 = uVar5;
    do {
      iVar9 = *(int *)(*(int *)(param_1 + 0x14) + uVar5);
      FUN_001cec5c(param_1,*(int *)(param_1 + 0x14) + uVar5 + 0x58);
      if (iVar9 == 5) {
        iVar9 = *(int *)(param_1 + 0x14) + uVar5;
        if (*(short *)(iVar9 + 0x24) != 0) {
          uVar7 = 0;
          uVar8 = uVar7;
          do {
            uVar7 = uVar7 + 1;
            iVar4 = *(int *)(iVar9 + 0x28) + uVar8;
            uVar8 = uVar8 + 0xc;
            os_free_mem(*(undefined4 *)(iVar4 + 4));
          } while (uVar7 < *(ushort *)(iVar9 + 0x24));
        }
        os_free_mem(*(undefined4 *)(iVar9 + 0x28));
        if (*(short *)(iVar9 + 0x44) != 0) {
          uVar7 = 0;
          uVar8 = uVar7;
          do {
            uVar8 = uVar8 + 1;
            iVar4 = *(int *)(iVar9 + 0x48) + uVar7;
            uVar7 = uVar7 + 0xc;
            os_free_mem(*(undefined4 *)(iVar4 + 4));
          } while (uVar8 < *(ushort *)(iVar9 + 0x44));
        }
        os_free_mem(*(undefined4 *)(iVar9 + 0x48));
      }
      uVar6 = uVar6 + 1;
      iVar9 = *(int *)(param_1 + 0x14) + uVar5;
      uVar5 = uVar5 + 0xa0;
      os_free_mem(*(undefined4 *)(iVar9 + 0x18));
    } while (uVar6 != bVar2);
  }
  if (bVar1 != 0) {
    uVar5 = 0;
    uVar6 = uVar5;
    do {
      uVar6 = uVar6 + 1;
      iVar9 = *(int *)(param_1 + 0x18) + uVar5;
      if (*(int *)(iVar9 + 0x4c) != 0) {
        RTMP_FreeFirstTxBuffer
                  (uVar3,*(undefined4 *)(iVar9 + 0x48),0,*(int *)(iVar9 + 0x4c),
                   *(undefined4 *)(iVar9 + 0x50));
        iVar9 = *(int *)(param_1 + 0x18) + uVar5;
      }
      __memzero(iVar9 + 0x48,0xc);
      FUN_001cec5c(param_1,*(int *)(param_1 + 0x18) + uVar5 + 0x3c);
      iVar9 = *(int *)(param_1 + 0x18) + uVar5;
      uVar5 = uVar5 + 0x60;
      os_free_mem(*(undefined4 *)(iVar9 + 0xc));
    } while (uVar6 != bVar1);
  }
  if (2 < DebugLevel) {
    printk("<-- %s\n","pci_free_txrx_ring_mem");
  }
  os_free_mem(*(undefined4 *)(param_1 + 0x18));
  os_free_mem(*(undefined4 *)(param_1 + 0x14));
  hif_ctrl_exit(param_1);
  return;
}

