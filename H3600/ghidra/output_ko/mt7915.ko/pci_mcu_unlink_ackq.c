// module: mt7915.ko
// function: pci_mcu_unlink_ackq @ 0x1cae64
// size: 20 bytes
//

void pci_mcu_unlink_ackq(int param_1)

{
  AndesUnlinkCmdMsg(param_1,*(int *)(param_1 + 0x1c) + 0xa784d4);
  return;
}

