// module: mt7915.ko
// function: rt_pci_suspend @ 0x1d8894
// size: 400 bytes
//

undefined4 rt_pci_suspend(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int iVar2;
  int local_24 [2];
  
  iVar2 = *(int *)(*(int *)(*(int *)(param_1 + 0xc0) + 0xd0) + 0xb0);
  if (2 < DebugLevel) {
    printk("===>%s()\n","rt_pci_suspend");
  }
  if (iVar2 == 0) {
    if (-1 < DebugLevel) {
      printk("net_dev == NULL!\n");
    }
  }
  else {
    uVar1 = RtmpOsGetNetDevPriv(iVar2);
    RTMP_COM_IoctlHandle(uVar1,0,0x503a,0,local_24,0);
    if (local_24[0] != 0) {
      netif_carrier_off(iVar2);
      if (*(int *)(iVar2 + 0x240) == 0) {
        warn_slowpath_null("include/linux/netdevice.h",0xa06);
        printk(&_LC6);
      }
      else {
        _set_bit(0,*(int *)(iVar2 + 0x240) + 0x50);
      }
      netif_device_detach(iVar2);
      RTMP_COM_IoctlHandle(uVar1,0,0x5028,0,0,0);
      module_put(__this_module);
    }
  }
  uVar1 = pci_choose_state(param_1,param_2);
  __pci_enable_wake(param_1,uVar1,0,1);
  pci_save_state(param_1);
  pci_disable_device(param_1);
  uVar1 = pci_choose_state(param_1,param_2);
  uVar1 = pci_set_power_state(param_1,uVar1);
  if (2 < DebugLevel) {
    printk("<===%s()\n","rt_pci_suspend");
  }
  return uVar1;
}

