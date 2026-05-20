// module: mt7915.ko
// function: pci_subsys_int_func @ 0x1cbee4
// size: 32 bytes
//

void pci_subsys_int_func(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(*(int *)(param_1 + 0xd0) + 0xb0));
  chip_subsys_int_handler(uVar1,param_1);
  return;
}

