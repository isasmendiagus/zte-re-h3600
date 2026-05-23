// module: mt7915.ko
// function: RtmpChipWriteMemory @ 0x147b84
// size: 12 bytes
//

void RtmpChipWriteMemory(void)

{
  int in_r3;
  
  if (in_r3 != 4) {
    return;
  }
  mac_io_write32();
  return;
}

