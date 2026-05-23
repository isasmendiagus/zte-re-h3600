// module: mt7915.ko
// function: RtmpOsPciConfigWriteDWord @ 0x2603cc
// size: 24 bytes
//

void RtmpOsPciConfigWriteDWord(int param_1,undefined4 param_2,undefined4 param_3)

{
  pci_bus_write_config_dword
            (*(undefined4 *)(param_1 + 8),*(undefined4 *)(param_1 + 0x1c),param_2,param_3);
  return;
}

