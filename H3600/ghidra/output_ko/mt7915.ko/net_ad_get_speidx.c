// module: mt7915.ko
// function: net_ad_get_speidx @ 0x25c414
// size: 148 bytes
//

undefined4 net_ad_get_speidx(int param_1,uint param_2,byte *param_3)

{
  byte *pbVar1;
  int iVar2;
  byte *pbVar3;
  byte *pbVar4;
  byte *pbVar5;
  
  iVar2 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar2 == 0) {
    return 0x606;
  }
  *param_3 = 0;
  pbVar3 = *(byte **)(param_1 + 0x68);
  if (*(char *)(param_1 + 0x6c) == '\0') {
    return 0;
  }
  if (*pbVar3 != param_2) {
    pbVar5 = pbVar3 + (uint)(byte)(*(char *)(param_1 + 0x6c) - 1) * 2;
    pbVar4 = pbVar3;
    do {
      pbVar3 = pbVar4 + 2;
      if (pbVar4 == pbVar5) {
        return 0;
      }
      pbVar1 = pbVar4 + 2;
      pbVar4 = pbVar3;
    } while (*pbVar1 != param_2);
  }
  *param_3 = pbVar3[1];
  return 0;
}

