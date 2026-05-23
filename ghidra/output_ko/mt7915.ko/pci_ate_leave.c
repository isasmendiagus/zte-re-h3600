// module: mt7915.ko
// function: pci_ate_leave @ 0x27e9dc
// size: 132 bytes
//

undefined4 pci_ate_leave(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  if (2 < DebugLevel) {
    printk(&_LC65,"pci_ate_leave",param_3,DebugLevel,param_4);
  }
  RtmpChipOpsEepromHook(param_1,*(undefined4 *)(param_1 + 0x286280),0);
  NICReadEEPROMParameters(param_1,0);
  NICInitAsicFromEEPROM(param_1);
  if (*(int *)(param_1 + 0xa3abcc) != 0) {
    os_free_mem();
    *(undefined4 *)(param_1 + 0xa3abcc) = 0;
  }
  return 0;
}

