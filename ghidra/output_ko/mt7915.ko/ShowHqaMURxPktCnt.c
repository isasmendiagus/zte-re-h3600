// module: mt7915.ko
// function: ShowHqaMURxPktCnt @ 0x8f688
// size: 80 bytes
//

undefined4 ShowHqaMURxPktCnt(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  if (param_1 != 0) {
    if (0 < DebugLevel) {
      printk("%s:(MuRxCnt=%d\n","ShowHqaMURxPktCnt",*(undefined4 *)(param_1 + 0xa789d8),
             param_1 + 0xa78000,param_4);
    }
    return 1;
  }
  return 1;
}

