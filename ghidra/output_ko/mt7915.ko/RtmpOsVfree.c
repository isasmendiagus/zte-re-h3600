// module: mt7915.ko
// function: RtmpOsVfree @ 0x244cb4
// size: 12 bytes
//

void RtmpOsVfree(int param_1)

{
  if (param_1 == 0) {
    return;
  }
  vfree();
  return;
}

