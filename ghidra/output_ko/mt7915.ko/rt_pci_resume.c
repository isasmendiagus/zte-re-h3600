// module: mt7915.ko
// function: rt_pci_resume @ 0x1d86e0
// size: 436 bytes
//

undefined4 rt_pci_resume(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int local_1c;
  
  iVar3 = *(int *)(*(int *)(*(int *)(param_1 + 0xc0) + 0xd0) + 0xb0);
  pci_set_power_state(param_1,0);
  pci_restore_state(param_1);
  iVar1 = pci_enable_device(param_1);
  if (iVar1 == 0) {
    if (2 < DebugLevel) {
      printk("===>%s()\n","rt_pci_resume");
    }
    if (iVar3 == 0) {
      if (-1 < DebugLevel) {
        printk("net_dev == NULL!\n");
      }
    }
    else {
      iVar1 = RtmpOsGetNetDevPriv(iVar3);
      if ((iVar1 != 0) && (RTMP_COM_IoctlHandle(iVar1,0,0x503a,0,&local_1c,0), local_1c != 0)) {
        netif_device_attach(iVar3);
        iVar2 = try_module_get(__this_module);
        if (iVar2 == 0) {
          if (-1 < DebugLevel) {
            printk("%s: cannot reserve module\n","rt_pci_resume");
          }
          return 0xffffffff;
        }
        RTMP_COM_IoctlHandle(iVar1,0,0x5029,0,0,0);
        _clear_bit(0,*(int *)(iVar3 + 0x240) + 0x50);
        netif_carrier_on(iVar3);
        netif_tx_wake_queue(*(undefined4 *)(iVar3 + 0x240));
      }
    }
    if (2 < DebugLevel) {
      printk("<=== %s()\n","rt_pci_resume");
      return 0;
    }
  }
  else if (-1 < DebugLevel) {
    printk("pci enable fail!\n");
    return 0;
  }
  return 0;
}

