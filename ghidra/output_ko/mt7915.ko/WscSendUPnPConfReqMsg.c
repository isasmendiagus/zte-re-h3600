// module: mt7915.ko
// function: WscSendUPnPConfReqMsg @ 0x1e20d4
// size: 56 bytes
//

undefined4 WscSendUPnPConfReqMsg(undefined4 param_1,undefined4 param_2,char *param_3)

{
  char acStack_2f [39];
  
  memset(acStack_2f,0,0x27);
  strncpy(acStack_2f,param_3,0x20);
  return 0;
}

