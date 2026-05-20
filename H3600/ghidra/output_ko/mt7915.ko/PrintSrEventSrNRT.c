// module: mt7915.ko
// function: PrintSrEventSrNRT @ 0x171324
// size: 88 bytes
//

void PrintSrEventSrNRT(int param_1)

{
  int iVar1;
  
  if (-1 < DebugLevel) {
    FUN_0016b708();
  }
  iVar1 = param_1 + 0xc0;
  do {
    if (-1 < DebugLevel) {
      printk("u1TableIdx = %x, u4NRTValue = %x\n",*(undefined1 *)(param_1 + 0xc),
             *(undefined4 *)(param_1 + 0x10));
    }
    param_1 = param_1 + 0xc;
  } while (param_1 != iVar1);
  return;
}

