// module: mt7915.ko
// function: RtmpOsSetNetDevPriv @ 0x244094
// size: 16 bytes
//

void RtmpOsSetNetDevPriv(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x4c0) = param_2;
  *(undefined4 *)(param_1 + 0x4c8) = 0;
  return;
}

