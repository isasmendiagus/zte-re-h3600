// module: mt7915.ko
// function: D_BndStrgSendMsg @ 0x9ddb8
// size: 48 bytes
//

void D_BndStrgSendMsg(undefined4 param_1,undefined4 *param_2,undefined4 param_3)

{
  RtmpOSWrielessEventSend(*param_2,1,0x950,0,param_3,0x40);
  return;
}

