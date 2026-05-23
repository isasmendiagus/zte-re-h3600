// module: mt7915.ko
// function: pci_subsys_int_handler @ 0x17cb48
// size: 332 bytes
//

void pci_subsys_int_handler(int param_1,int param_2)

{
  undefined4 uVar1;
  uint local_1c [2];
  
  local_1c[0] = 0;
  if ((*(uint *)(param_2 + 0xc) & 0x10000000) == 0) {
    return;
  }
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x18060014,local_1c);
  if ((local_1c[0] & 1) != 0) {
    *(undefined1 *)(param_1 + 0xa7becc) = 1;
    local_1c[0] = 1;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x18060014,1);
    if (2 < DebugLevel) {
      printk("%s::DriverOwn\n","pci_subsys_int_handler");
    }
  }
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x18060024,local_1c);
  if ((local_1c[0] & 1) != 0) {
    *(undefined1 *)(param_1 + 0xa7becd) = 1;
    local_1c[0] = 1;
    mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x18060024,1);
    if (2 < DebugLevel) {
      printk("%s::DriverOwn1\n","pci_subsys_int_handler");
    }
  }
  uVar1 = _raw_spin_lock_irqsave(param_2 + 0xc0);
  *(uint *)(param_2 + 0xc) = *(uint *)(param_2 + 0xc) & 0xefffffff;
  mt_int_enable(param_1,param_2,0x10000000);
  _raw_spin_unlock_irqrestore(param_2 + 0xc0,uVar1);
  return;
}

