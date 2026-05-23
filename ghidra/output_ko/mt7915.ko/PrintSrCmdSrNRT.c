// module: mt7915.ko
// function: PrintSrCmdSrNRT @ 0x1705a0
// size: 68 bytes
//

void PrintSrCmdSrNRT(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  if (0 < DebugLevel) {
    FUN_0016b3c0();
  }
  if (DebugLevel < 0) {
    return;
  }
  printk("u1TableIdx = %x, u4NRTValue = %x\n",*(undefined1 *)(param_1 + 0xc),
         *(undefined4 *)(param_1 + 0x10),param_4);
  return;
}

