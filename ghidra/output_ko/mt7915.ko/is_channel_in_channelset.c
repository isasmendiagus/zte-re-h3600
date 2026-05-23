// module: mt7915.ko
// function: is_channel_in_channelset @ 0x141a40
// size: 48 bytes
//

undefined4 is_channel_in_channelset(byte *param_1,uint param_2)

{
  byte bVar1;
  
  bVar1 = *param_1;
  while( true ) {
    if (bVar1 == 0) {
      return 0;
    }
    if (bVar1 == param_2) break;
    param_1 = param_1 + 1;
    bVar1 = *param_1;
  }
  return 1;
}

