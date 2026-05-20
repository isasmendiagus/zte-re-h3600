// module: mt7915.ko
// function: MT_ATEDumpReCal @ 0x27b920
// size: 88 bytes
//

undefined4 MT_ATEDumpReCal(void)

{
  undefined4 in_r3;
  undefined4 in_stack_00000000;
  undefined4 in_stack_00000004;
  
  if (0 < DebugLevel) {
    printk("[Recal][%08x][%08x]%08x\n",in_r3,in_stack_00000000,in_stack_00000004,in_r3);
  }
  return 0;
}

