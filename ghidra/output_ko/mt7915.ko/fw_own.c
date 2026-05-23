// module: mt7915.ko
// function: fw_own @ 0x17ed04
// size: 240 bytes
//

void fw_own(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  iVar2 = hc_get_hif_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
  iVar2 = *(int *)(iVar2 + 0xa4);
  if ((*(uint *)(param_1 + 0x286280) & 0xfffffffb) != 1) {
    return;
  }
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x18060010);
  iVar1 = DebugLevel;
  *(undefined1 *)(param_1 + 0xa7becc) = 0;
  if (iVar1 < 1) {
    if (iVar2 == 0) {
      return;
    }
  }
  else {
    printk("%s: fw own to p(%d)\n","pci_fw_own_by_port");
    if (iVar2 == 0) {
      if (DebugLevel < 1) {
        return;
      }
      printk("%s: port=1 is not enabled\n","fw_own");
      return;
    }
  }
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x18060020,1);
  iVar2 = DebugLevel;
  *(undefined1 *)(param_1 + 0xa7becd) = 0;
  if (iVar2 < 1) {
    return;
  }
  printk("%s: fw own to p(%d)\n","pci_fw_own_by_port",1,param_4);
  return;
}

