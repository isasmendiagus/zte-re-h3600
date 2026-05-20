// module: mt7915.ko
// function: RepeaterDisconnectRootAP @ 0x830c8
// size: 72 bytes
//

void RepeaterDisconnectRootAP(undefined4 param_1,int param_2,undefined4 param_3)

{
  if (param_2 == 0) {
    return;
  }
  *(undefined4 *)(param_2 + 0x94) = param_3;
  __cntl_disconnect_request(param_2 + 0xe0,0,param_2 + 0x101,3,"RepeaterDisconnectRootAP",0x67d);
  return;
}

