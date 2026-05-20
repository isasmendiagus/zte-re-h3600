// module: mt7915.ko
// function: pci_sw_int_handler @ 0x17c99c
// size: 424 bytes
//

void pci_sw_int_handler(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  uint local_28;
  undefined4 local_24 [2];
  
  iVar2 = *(int *)(param_2 + 0x6c0);
  local_28 = 0;
  if ((*(uint *)(param_2 + 0xc) & 0x20000000) != 0) {
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x7c0251f0,&local_28);
    if ((local_28 & 1) != 0) {
      mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c0251f0,1);
      FUN_00177ffc(param_1,0);
      if (2 < DebugLevel) {
        printk("%s::SWI DriverOwn\n","pci_sw_int_handler");
      }
    }
    if ((local_28 & 2) != 0) {
      mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c0251f0,2);
      FUN_00177ffc(param_1,1);
      if (2 < DebugLevel) {
        printk("%s::SWI DriverOwn1\n","pci_sw_int_handler");
      }
    }
    iVar1 = param_2 + 0xc0;
    if ((local_28 & 0x3c) == 0) {
      local_24[0] = _raw_spin_lock_irqsave(iVar1);
      *(uint *)(param_2 + 0xc) = *(uint *)(param_2 + 0xc) & 0xdfffffff;
      mt_int_enable(param_1,param_2,0x20000000);
      _raw_spin_unlock_irqrestore(iVar1,local_24[0]);
      return;
    }
    wlan_dbg_radio_statistics_inc(0,0x14);
    OS_SPIN_LOCK_IRQSAVE(iVar1,local_24);
    *(uint *)(param_1 + 0xa7bf08) = local_28;
    OS_SPIN_UNLOCK_IRQRESTORE(iVar1,local_24);
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x7c0251f0,local_28);
    (**(code **)(iVar2 + 0x10))(param_2 + 0xe0);
    chip_dump_ser_stat(param_1,0);
  }
  return;
}

