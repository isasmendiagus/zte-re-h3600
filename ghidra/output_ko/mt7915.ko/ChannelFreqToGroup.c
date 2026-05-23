// module: mt7915.ko
// function: ChannelFreqToGroup @ 0x141520
// size: 276 bytes
//

undefined4 ChannelFreqToGroup(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  if (param_1 < 0x9b5) {
    return 0;
  }
  if (param_1 - 0x12f2 < 0x123) {
    return 1;
  }
  if (param_1 - 0x1419 < 0x6a) {
    return 2;
  }
  if (param_1 - 0x1487 < 0x6a) {
    return 3;
  }
  if (param_1 - 0x14f5 < 0x6a) {
    return 4;
  }
  if (param_1 - 0x1563 < 0x6a) {
    return 5;
  }
  if (param_1 - 0x15d1 < 0x6a) {
    return 6;
  }
  if (param_1 - 0x163f < 0x6a) {
    return 7;
  }
  if (param_1 - 0x16ad < 0x92) {
    return 8;
  }
  if (DebugLevel < 0) {
    return 0xffffffff;
  }
  printk("%s : Can\'t find group for [%d].\n","ChannelFreqToGroup",param_1,DebugLevel,param_4);
  return 0xffffffff;
}

