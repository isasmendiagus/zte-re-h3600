// module: mt7915.ko
// function: RTMPFindHostPCIDev @ 0x2601e8
// size: 212 bytes
//

int RTMPFindHostPCIDev(int param_1)

{
  int iVar1;
  int iVar2;
  char local_13;
  short local_12;
  
  if (2 < DebugLevel) {
    printk("%s.===>\n","RTMPFindHostPCIDev");
  }
  iVar1 = *(int *)(*(int *)(param_1 + 8) + 8);
  if (iVar1 != 0) {
    iVar2 = 0;
    while( true ) {
      iVar1 = pci_get_slot(iVar1,iVar2);
      if (iVar1 != 0) {
        pci_bus_read_config_word
                  (*(undefined4 *)(iVar1 + 8),*(undefined4 *)(iVar1 + 0x1c),10,&local_12);
        pci_bus_read_config_byte
                  (*(undefined4 *)(iVar1 + 8),*(undefined4 *)(iVar1 + 0x1c),0x19,&local_13);
        if ((local_12 == 0x604) && (*(char *)(*(int *)(param_1 + 8) + 0x6c) == local_13)) {
          return iVar1;
        }
      }
      if (iVar2 + 1 == 0xff) break;
      iVar1 = *(int *)(*(int *)(param_1 + 8) + 8);
      iVar2 = iVar2 + 1;
    }
  }
  return 0;
}

