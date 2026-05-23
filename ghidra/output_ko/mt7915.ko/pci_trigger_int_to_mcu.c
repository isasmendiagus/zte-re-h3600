// module: mt7915.ko
// function: pci_trigger_int_to_mcu @ 0x176d44
// size: 40 bytes
//

undefined4
pci_trigger_int_to_mcu(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x55000108,param_2,param_4,param_4);
  return 1;
}

