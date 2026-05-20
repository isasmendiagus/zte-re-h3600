// module: mt7915.ko
// function: DuplicatePacket @ 0x243714
// size: 56 bytes
//

void DuplicatePacket(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = skb_clone(param_2,0x20);
  if (iVar1 == 0) {
    return;
  }
  g_stWlanRadioStat._8_4_ = g_stWlanRadioStat._8_4_ + 1;
  *(undefined4 *)(iVar1 + 0x18) = param_1;
  return;
}

