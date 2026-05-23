// module: mt7915.ko
// function: RtmpOSIRQRelease @ 0x244c84
// size: 36 bytes
//

undefined4 RtmpOSIRQRelease(undefined4 param_1,undefined4 param_2)

{
  synchronize_irq();
  free_irq(param_1,param_2);
  return 0;
}

