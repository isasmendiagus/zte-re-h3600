// module: mt7915.ko
// function: twtReqFsmSendEvent @ 0x169180
// size: 120 bytes
//

void twtReqFsmSendEvent(int param_1,undefined4 param_2,undefined1 param_3,undefined1 param_4)

{
  undefined1 local_46;
  undefined4 local_45;
  undefined1 local_41;
  
  memset(&local_46,0,0x26);
  local_46 = param_4;
  local_45 = param_2;
  local_41 = param_3;
  MlmeEnqueueWithWdev(param_1,9,0x1e,0x26,&local_46,0,param_2);
  RtmpOsMlmeUp(param_1 + 0x286298);
  return;
}

