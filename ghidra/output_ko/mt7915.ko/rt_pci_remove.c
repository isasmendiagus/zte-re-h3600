// module: mt7915.ko
// function: rt_pci_remove @ 0x1d8a28
// size: 196 bytes
//

void rt_pci_remove(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  
  iVar3 = *(int *)(param_1 + 0xc0);
  iVar2 = *(int *)(*(int *)(iVar3 + 0xd0) + 0xb0);
  uVar4 = *(undefined4 *)(iVar2 + 0x24);
  iVar1 = RtmpOsGetNetDevPriv(iVar2);
  if (2 < DebugLevel) {
    printk("===> %s()\n","rt_pci_remove");
  }
  if (iVar1 == 0) {
    RtmpOSNetDevDetach(iVar2);
    __arm_iounmap(*(undefined4 *)(iVar2 + 0x24));
    pci_release_regions(param_1);
  }
  else {
    RtmpPhyNetDevExit(iVar1,iVar2);
    RtmpRaDevCtrlExit(iVar1);
    g_pAd = 0;
    unregister_reboot_notifier(wlan_reboot_notifier);
    __arm_iounmap(uVar4);
    pci_release_regions(param_1);
  }
  RtmpOSNetDevFree(iVar2);
  pci_hif_chip_exit(iVar3);
  return;
}

