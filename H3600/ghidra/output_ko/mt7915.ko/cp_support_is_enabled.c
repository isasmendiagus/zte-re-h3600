// module: mt7915.ko
// function: cp_support_is_enabled @ 0xed900
// size: 168 bytes
//

void cp_support_is_enabled(int param_1)

{
  if (2 < *(byte *)(param_1 + 0xa7beca) - 1) {
    if (DebugLevel < 0) {
      return;
    }
    printk("The CP Mode is invaild. Mode should be 1~3.\n");
    return;
  }
  if (*(char *)(param_1 + 0xa7becb) != '\x01') {
    if (DebugLevel < 0) {
      return;
    }
    printk("%s: set Driver CP_SUPPORT to Mode %d.\n","cp_support_is_enabled");
    return;
  }
  MtCmdSetCPSEnable(param_1,2);
  if (DebugLevel < 0) {
    return;
  }
  printk("%s: set CR4 CP_SUPPORT to Mode %d.\n","cp_support_is_enabled",
         *(undefined1 *)(param_1 + 0xa7beca));
  return;
}

