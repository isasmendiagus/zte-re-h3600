// module: mt7915.ko
// function: APReleaseRekeyTimer @ 0x189d8
// size: 28 bytes
//

void APReleaseRekeyTimer(undefined4 param_1,int param_2)

{
  undefined1 auStack_9 [5];
  
  RTMPReleaseTimer(param_2 + 0x31c,auStack_9);
  return;
}

