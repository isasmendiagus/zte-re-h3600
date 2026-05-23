// module: mt7915.ko
// function: PrintSrEventSrInd @ 0x1711a4
// size: 56 bytes
//

void PrintSrEventSrInd(int param_1)

{
  undefined4 unaff_r4;
  undefined4 unaff_r5;
  
  if (DebugLevel < 0) {
    return;
  }
  FUN_0016b708();
  if (DebugLevel < 0) {
    return;
  }
  printk("%s:\nu1NonSrgInterPpduRcpi   = %x, u1SrgInterPpduRcpi     = %x\nu2NonSrgVldCnt          = %x, u2SrgVldCnt            = %x\nu2IntraBssPpduCnt       = %x, u2InterBssPpduCnt      = %x\nu2NonSrgPpduVldCnt      = %x, u2SrgPpduVldCnt        = %x\nu4SrAmpduMpduCnt        = %x, u4SrAmpduMpduAckedCnt  = %x\n"
         ,"PrintSrInd",*(undefined1 *)(param_1 + 0xc),*(undefined1 *)(param_1 + 0xd),
         *(undefined2 *)(param_1 + 0xe),*(undefined2 *)(param_1 + 0x10),
         *(undefined2 *)(param_1 + 0x12),*(undefined2 *)(param_1 + 0x14),
         *(undefined2 *)(param_1 + 0x16),*(undefined2 *)(param_1 + 0x18),
         *(undefined4 *)(param_1 + 0x1c),*(undefined4 *)(param_1 + 0x20),unaff_r4,unaff_r5);
  return;
}

