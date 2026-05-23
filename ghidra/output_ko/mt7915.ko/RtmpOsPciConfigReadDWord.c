// module: mt7915.ko
// function: RtmpOsPciConfigReadDWord @ 0x2603b4
// size: 24 bytes
//

void RtmpOsPciConfigReadDWord(int param_1,undefined4 param_2,undefined4 param_3)

{
  pci_bus_read_config_dword
            (*(undefined4 *)(param_1 + 8),*(undefined4 *)(param_1 + 0x1c),param_2,param_3);
  return;
}

