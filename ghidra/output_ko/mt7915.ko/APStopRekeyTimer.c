// module: mt7915.ko
// function: APStopRekeyTimer @ 0x189bc
// size: 28 bytes
//

void APStopRekeyTimer(undefined4 param_1,int param_2)

{
  undefined1 auStack_9 [5];
  
  RTMPCancelTimer(param_2 + 0x31c,auStack_9);
  return;
}

