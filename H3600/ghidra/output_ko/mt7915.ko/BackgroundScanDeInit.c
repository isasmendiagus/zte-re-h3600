// module: mt7915.ko
// function: BackgroundScanDeInit @ 0x22de30
// size: 60 bytes
//

void BackgroundScanDeInit(int param_1)

{
  undefined1 uStack_9;
  
  RTMPReleaseTimer(param_1 + 0xa79190,&uStack_9);
  RTMPReleaseTimer(param_1 + 0xa791c4,&uStack_9);
  return;
}

