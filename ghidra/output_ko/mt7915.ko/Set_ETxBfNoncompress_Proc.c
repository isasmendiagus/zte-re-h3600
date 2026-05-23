// module: mt7915.ko
// function: Set_ETxBfNoncompress_Proc @ 0xe54b0
// size: 104 bytes
//

undefined4 Set_ETxBfNoncompress_Proc(int param_1,undefined4 param_2)

{
  uint uVar1;
  
  uVar1 = os_str_tol(param_2,0,10);
  if (uVar1 < 2) {
    *(char *)(param_1 + 0x7959a4) = (char)uVar1;
    return 1;
  }
  if (DebugLevel < 0) {
    return 0;
  }
  printk("Set_ETxBfNoncompress_Proc: value > 1!\n");
  return 0;
}

