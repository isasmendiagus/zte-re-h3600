// module: mt7915.ko
// function: Channel2Index @ 0x1449f8
// size: 108 bytes
//

uint Channel2Index(int param_1,uint param_2,undefined4 param_3)

{
  byte *pbVar1;
  byte *pbVar2;
  uint uVar3;
  
  pbVar2 = (byte *)hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),param_3);
  pbVar1 = pbVar2 + 0x49c;
  if (*pbVar1 != 0) {
    if (*pbVar2 == param_2) {
      return 0;
    }
    uVar3 = 0;
    while (uVar3 = uVar3 + 1, uVar3 != *pbVar1) {
      pbVar2 = pbVar2 + 0x14;
      if (*pbVar2 == param_2) {
        return uVar3 & 0xff;
      }
    }
  }
  return 0xff;
}

