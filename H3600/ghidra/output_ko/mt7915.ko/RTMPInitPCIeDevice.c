// module: mt7915.ko
// function: RTMPInitPCIeDevice @ 0x1d85f0
// size: 236 bytes
//

void RTMPInitPCIeDevice(int *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *param_2;
  pci_bus_read_config_word
            (*(undefined4 *)(*param_1 + 8),*(undefined4 *)(*param_1 + 0x1c),param_1[1]);
  iVar1 = DebugLevel;
  *(undefined2 *)(iVar2 + 8) = 0;
  if (0 < iVar1) {
    printk("%s():device_id=0x%x\n","RTMPInitPCIeDevice",0);
  }
  param_2[0x1e5449] = param_2[0x1e5449] & 0xfffdffff;
  iVar2 = mt_pci_chip_cfg(param_2,0);
  iVar1 = DebugLevel;
  if (iVar2 == 0) {
    *(undefined1 *)(param_1 + 4) = 1;
    if (param_2[0xa18a0] != 0) {
      RtmpRaDevCtrlInit(param_2);
      return;
    }
  }
  else {
    *(undefined1 *)(param_1 + 4) = 0;
    if (0 < iVar1) {
      printk("%s():pci configuration space can\'t be read\n","RTMPInitPCIeDevice");
    }
  }
  return;
}

