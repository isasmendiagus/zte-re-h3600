// module: mt7915.ko
// function: CHAN_PropertyCheck @ 0x131978
// size: 156 bytes
//

bool CHAN_PropertyCheck(int param_1,uint param_2,uint param_3)

{
  undefined4 uVar1;
  byte *pbVar2;
  uint uVar3;
  byte *pbVar4;
  
  uVar1 = HcGetBandByChannel(param_1,param_2 & 0xff);
  pbVar2 = (byte *)hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),uVar1);
  if (pbVar2[0x49c] == 0) {
    return false;
  }
  if (*pbVar2 == param_2) {
    uVar3 = 0;
  }
  else {
    uVar3 = 0;
    pbVar4 = pbVar2;
    do {
      uVar3 = uVar3 + 1;
      if (uVar3 == pbVar2[0x49c]) {
        return false;
      }
      pbVar4 = pbVar4 + 0x14;
    } while (*pbVar4 != param_2);
  }
  return param_3 == (param_3 & *(uint *)(pbVar2 + uVar3 * 0x14 + 0x10));
}

