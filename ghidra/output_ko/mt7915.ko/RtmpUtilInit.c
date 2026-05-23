// module: mt7915.ko
// function: RtmpUtilInit @ 0x2431d0
// size: 32 bytes
//

void RtmpUtilInit(void)

{
  if (FlgIsUtilInit == '\0') {
    FlgIsUtilInit = '\x01';
    UtilSemLock = 0;
  }
  return;
}

