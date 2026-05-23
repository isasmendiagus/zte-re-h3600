// module: mt7915.ko
// function: ChannelSwitchSanityCheck @ 0xa23d8
// size: 196 bytes
//

undefined4 ChannelSwitchSanityCheck(int param_1,uint param_2,uint param_3,int param_4)

{
  byte *pbVar1;
  byte bVar2;
  uint uVar3;
  undefined4 uVar4;
  byte *pbVar5;
  byte bVar6;
  bool bVar7;
  
  uVar3 = HcGetMaxStaNum();
  if (param_2 < uVar3) {
    uVar4 = HcGetBandByWdev(*(undefined4 *)(param_2 * 0x14c0 + param_1 + 0xa1d28));
    pbVar5 = (byte *)hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),uVar4);
    if (param_4 != 1 || param_3 < 8) {
      bVar7 = param_3 == 4;
      if (param_3 < 5) {
        bVar7 = param_4 == 3;
      }
      if (!bVar7) {
        bVar6 = 0;
        pbVar1 = pbVar5 + 0x49c;
        if (*pbVar1 == 0) {
          return 0;
        }
        bVar2 = *pbVar5;
        while( true ) {
          if (bVar2 == param_3) {
            return 1;
          }
          bVar6 = bVar6 + 1;
          if (bVar6 == *pbVar1) break;
          pbVar5 = pbVar5 + 0x14;
          bVar2 = *pbVar5;
        }
      }
    }
  }
  return 0;
}

