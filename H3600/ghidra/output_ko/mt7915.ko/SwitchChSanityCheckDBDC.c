// module: mt7915.ko
// function: SwitchChSanityCheckDBDC @ 0x110e74
// size: 112 bytes
//

undefined4 SwitchChSanityCheckDBDC(int param_1,undefined4 param_2,undefined4 param_3,uint param_4)

{
  byte *pbVar1;
  undefined4 uVar2;
  byte *pbVar3;
  uint uVar4;
  
  uVar2 = HcGetBandByWdev(param_2);
  pbVar3 = (byte *)hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),uVar2);
  pbVar1 = pbVar3 + 0x49c;
  if (*pbVar1 == 0) {
    return 0;
  }
  if (*pbVar3 != param_4) {
    uVar4 = 0;
    do {
      uVar4 = uVar4 + 1;
      if (uVar4 == *pbVar1) {
        return 0;
      }
      pbVar3 = pbVar3 + 0x14;
    } while (*pbVar3 != param_4);
  }
  return 1;
}

