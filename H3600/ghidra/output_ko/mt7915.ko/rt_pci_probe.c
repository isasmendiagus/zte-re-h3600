// module: mt7915.ko
// function: rt_pci_probe @ 0x1d8d5c
// size: 700 bytes
//

int rt_pci_probe(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int local_9c;
  int *local_98;
  undefined4 local_94;
  undefined1 local_90 [4];
  undefined4 local_8c;
  int local_88 [4];
  char local_78;
  int local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_64;
  undefined1 auStack_60 [68];
  
  local_9c = 0;
  if (2 < DebugLevel) {
    printk("===> %s(): device: %x\n","rt_pci_probe",*(undefined4 *)(param_2 + 4));
  }
  iVar1 = FUN_001d8af0(param_1,&local_94);
  if (iVar1 == 0) {
    os_alloc_mem(0,&local_98,0x44);
    if (local_98 == (int *)0x0) {
      if (-1 < DebugLevel) {
        printk("%s(): Allocate memory for os handle failed!\n","rt_pci_probe");
      }
    }
    else {
      __memzero(local_98,0x44);
      *local_98 = param_1;
      local_98[3] = param_1 + 0x68;
      iVar1 = RTMPAllocAdapterBlock(local_98,&local_9c,5);
      if (iVar1 == 0) {
        RTMP_COM_IoctlHandle(local_9c,0,0x502a,0,0,local_94);
        local_88[2] = 0x2c;
        local_78 = '\0';
        local_88[1] = 2;
        local_88[3] = 0x2e;
        local_88[0] = param_1;
        RTMP_COM_IoctlHandle(local_9c,0,0x502b,0,local_88,0);
        if ((local_78 == '\x01') && (iVar1 = RtmpPhyNetDevInit(local_9c,auStack_60), iVar1 != 0)) {
          *(undefined4 *)(iVar1 + 0x28) = *(undefined4 *)(param_1 + 0x1c4);
          *(undefined4 *)(iVar1 + 0x24) = local_94;
          *(uint *)(iVar1 + 0x88) = *(uint *)(iVar1 + 0x88) & 0xffffffdf;
          *(undefined4 *)(iVar1 + 0x8c) = *(undefined4 *)(iVar1 + 0x8c);
          local_70 = *(undefined4 *)(param_2 + 4);
          local_6c = *(undefined4 *)(param_1 + 0x1c4);
          local_64 = local_94;
          local_74 = param_1 + 0x68;
          pci_hif_chip_init(&local_8c,&local_74);
          *(undefined4 *)(param_1 + 0xc0) = local_8c;
          iVar2 = hc_get_hif_ctrl(*(undefined4 *)(local_9c + 0xa797a0));
          *(int *)(iVar2 + 0xb0) = iVar1;
          *(undefined4 *)(iVar2 + 0xa0) = local_8c;
          RTMP_COM_IoctlHandle(local_9c,0,0x504c,0,0,0);
          RTMP_COM_IoctlHandle(local_9c,0,0x5002,0,local_90,0);
          iVar2 = RtmpOSNetDevAttach(local_90[0],iVar1,auStack_60);
          if (iVar2 == 0) {
            if (2 < DebugLevel) {
              printk("<=%s()\n","rt_pci_probe");
            }
            g_pAd = local_9c;
            register_reboot_notifier(wlan_reboot_notifier);
            rlk_register_wlan_led(0);
            rlk_register_wlan_led(1);
            return 0;
          }
          RtmpOSNetDevFree(iVar1);
        }
        RTMPFreeAdapter(local_9c);
      }
    }
    __arm_iounmap(local_94);
    pci_release_regions(param_1);
    pci_disable_device(param_1);
    iVar1 = -0x13;
  }
  else if (-1 < DebugLevel) {
    printk("<=== %s() failed with rv = %d!\n","rt_pci_probe",iVar1);
  }
  return iVar1;
}

