// module: mt7915.ko
// function: PrintSrNRT @ 0x16d418
// size: 44 bytes
//

void PrintSrNRT(undefined1 *param_1)

{
  if (DebugLevel < 0) {
    return;
  }
  printk("u1TableIdx = %x, u4NRTValue = %x\n",*param_1,*(undefined4 *)(param_1 + 4));
  return;
}

