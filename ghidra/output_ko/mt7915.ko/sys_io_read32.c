// module: mt7915.ko
// function: sys_io_read32 @ 0x1df4a0
// size: 32 bytes
//

void sys_io_read32(undefined4 param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  uVar1 = fixed_pci_read_u32(0,param_1);
  *param_2 = uVar1;
  return;
}

