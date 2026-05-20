// module: mt7915.ko
// function: dedicated_rx_hist_scan_timeout @ 0x22ebc4
// size: 100 bytes
//

void dedicated_rx_hist_scan_timeout(undefined4 param_1,int param_2)

{
  undefined1 auStack_11 [5];
  
  MlmeEnqueue(param_2,0x2b,0xd,0,0,0);
  RtmpOsMlmeUp(param_2 + 0x286298);
  RTMPCancelTimer(param_2 + 0xa791f8,auStack_11);
  RTMPReleaseTimer(param_2 + 0xa791f8,auStack_11);
  return;
}

