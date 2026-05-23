// module: mt7915.ko
// function: RT28xx_MSTA_Remove @ 0x685b8
// size: 48 bytes
//

void RT28xx_MSTA_Remove(undefined4 param_1)

{
  RTMP_STA_IoctlHandle(param_1,0,0xa02a,0,0,0,0);
  return;
}

