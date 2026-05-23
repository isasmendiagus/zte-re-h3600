// module: mt7915.ko
// function: RtmpOSNetDevIsUp @ 0x244084
// size: 16 bytes
//

uint RtmpOSNetDevIsUp(int param_1)

{
  uint uVar1;
  
  uVar1 = 0;
  if (param_1 != 0) {
    uVar1 = *(uint *)(param_1 + 0x138) & 1;
  }
  return uVar1;
}

