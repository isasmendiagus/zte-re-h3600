// module: mt7915.ko
// function: SwitchChSanityCheck @ 0x110e08
// size: 108 bytes
//

undefined4 SwitchChSanityCheck(int param_1,undefined4 param_2,uint param_3)

{
  byte *pbVar1;
  undefined4 uVar2;
  byte *pbVar3;
  uint uVar4;
  
  uVar2 = HcGetBandByChannel();
  pbVar3 = (byte *)hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),uVar2);
  pbVar1 = pbVar3 + 0x49c;
  if (*pbVar1 == 0) {
    return 0;
  }
  if (*pbVar3 != param_3) {
    uVar4 = 0;
    do {
      uVar4 = uVar4 + 1;
      if (uVar4 == *pbVar1) {
        return 0;
      }
      pbVar3 = pbVar3 + 0x14;
    } while (*pbVar3 != param_3);
  }
  return 1;
}

