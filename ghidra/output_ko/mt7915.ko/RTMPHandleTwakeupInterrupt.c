// module: mt7915.ko
// function: RTMPHandleTwakeupInterrupt @ 0x56550
// size: 20 bytes
//

void RTMPHandleTwakeupInterrupt(int param_1)

{
  AsicWakeup(param_1,0,&DAT_0036db58 + param_1);
  return;
}

