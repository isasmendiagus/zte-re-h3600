// module: mt7915.ko
// function: pci_free_irq_local @ 0x1cb43c
// size: 68 bytes
//

undefined4 pci_free_irq_local(void)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = hc_get_hif_ctrl();
  if (*(char *)(iVar2 + 0xa8) != '\0') {
    uVar3 = 0;
    do {
      iVar1 = uVar3 * 4;
      uVar3 = uVar3 + 1;
      RtmpOSIRQRelease(*(undefined4 *)(*(int *)(*(int *)(iVar2 + 0xac) + iVar1) + 0xd4));
    } while (uVar3 < *(byte *)(iVar2 + 0xa8));
  }
  return 0;
}

