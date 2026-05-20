// module: mt7915.ko
// function: dump_ba_list @ 0xa4b00
// size: 136 bytes
//

void dump_ba_list(int *param_1)

{
  int *piVar1;
  
  piVar1 = (int *)*param_1;
  if (piVar1 != (int *)0x0) {
    if (0 < DebugLevel) {
      printk("\n ba sn list:");
      piVar1 = (int *)*param_1;
      if (piVar1 == (int *)0x0) goto LAB_000a4b44;
    }
    do {
      printk(&_LC6,piVar1[5]);
      piVar1 = (int *)*piVar1;
    } while (piVar1 != (int *)0x0);
  }
LAB_000a4b44:
  if (0 < DebugLevel) {
    printk(&_LC7);
    return;
  }
  return;
}

