// module: mt7915.ko
// function: PrintSrInd @ 0x16d0f8
// size: 132 bytes
//

void PrintSrInd(undefined1 *param_1)

{
  if (DebugLevel < 0) {
    return;
  }
  printk("%s:\nu1NonSrgInterPpduRcpi   = %x, u1SrgInterPpduRcpi     = %x\nu2NonSrgVldCnt          = %x, u2SrgVldCnt            = %x\nu2IntraBssPpduCnt       = %x, u2InterBssPpduCnt      = %x\nu2NonSrgPpduVldCnt      = %x, u2SrgPpduVldCnt        = %x\nu4SrAmpduMpduCnt        = %x, u4SrAmpduMpduAckedCnt  = %x\n"
         ,"PrintSrInd",*param_1,param_1[1],*(undefined2 *)(param_1 + 2),*(undefined2 *)(param_1 + 4)
         ,*(undefined2 *)(param_1 + 6),*(undefined2 *)(param_1 + 8),*(undefined2 *)(param_1 + 10),
         *(undefined2 *)(param_1 + 0xc),*(undefined4 *)(param_1 + 0x10),
         *(undefined4 *)(param_1 + 0x14));
  return;
}

