// module: mt7915.ko
// function: Reset_OBSS_AirTime @ 0xc83cc
// size: 80 bytes
//

void Reset_OBSS_AirTime(int param_1)

{
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820f53c4);
  hw_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820f53c4);
  return;
}

