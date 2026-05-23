// module: mt7915.ko
// function: pci_register_irq @ 0x1cb480
// size: 116 bytes
//

undefined4 pci_register_irq(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 in_r3;
  int iVar4;
  
  iVar1 = hc_get_hif_ctrl();
  if (*(char *)(iVar1 + 0xa8) != '\0') {
    iVar4 = 0;
    do {
      iVar2 = *(int *)(*(int *)(iVar1 + 0xac) + iVar4 * 4);
      iVar4 = iVar4 + 1;
      iVar3 = *(int *)(*(int *)(iVar2 + 0xcc) + 0x2c);
      if (iVar3 == 0) {
        iVar3 = *(int *)(*(int *)(iVar2 + 0xcc) + 8);
      }
      iVar2 = RtmpOSIRQRequest(*(undefined4 *)(iVar2 + 0xd4),iVar3,rt2860_interrupt,iVar2,in_r3);
      if (iVar2 != 0) {
        return 1;
      }
    } while (iVar4 < (int)(uint)*(byte *)(iVar1 + 0xa8));
  }
  return 0;
}

