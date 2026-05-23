// module: mt7915.ko
// function: get_channel_bw_cap @ 0x103508
// size: 188 bytes
//

uint get_channel_bw_cap(int param_1,uint param_2)

{
  undefined4 uVar1;
  byte *pbVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  byte *pbVar6;
  bool bVar7;
  
  iVar4 = *(int *)(param_1 + 8);
  uVar1 = HcGetBandByWdev();
  pbVar2 = (byte *)hc_get_channel_ctrl(*(undefined4 *)(iVar4 + 0xa797a0),uVar1);
  if (pbVar2[0x49c] == 0) {
    return 0;
  }
  if (*pbVar2 == param_2) {
    uVar5 = 0;
  }
  else {
    uVar3 = 1;
    pbVar6 = pbVar2;
    do {
      uVar5 = uVar3;
      uVar3 = uVar5 & 0xff;
      bVar7 = 0x39 < uVar3;
      if (uVar3 < 0x3b) {
        bVar7 = pbVar2[0x49c] <= uVar3;
      }
      if (bVar7) {
        return 0;
      }
      pbVar6 = pbVar6 + 0x14;
      uVar3 = uVar5 + 1;
    } while (*pbVar6 != param_2);
  }
  uVar3 = *(uint *)(pbVar2 + uVar5 * 0x14 + 0x10);
  if ((uVar3 & 0x100) != 0) {
    return 3;
  }
  if ((uVar3 & 0x80) == 0) {
    return (uVar3 << 0x19) >> 0x1f;
  }
  return 2;
}

