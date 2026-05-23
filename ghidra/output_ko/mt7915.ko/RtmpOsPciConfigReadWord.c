// module: mt7915.ko
// function: RtmpOsPciConfigReadWord @ 0x260384
// size: 24 bytes
//

void RtmpOsPciConfigReadWord(int param_1,undefined4 param_2,undefined4 param_3)

{
  pci_bus_read_config_word
            (*(undefined4 *)(param_1 + 8),*(undefined4 *)(param_1 + 0x1c),param_2,param_3);
  return;
}

