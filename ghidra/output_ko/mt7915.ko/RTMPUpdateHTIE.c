// module: mt7915.ko
// function: RTMPUpdateHTIE @ 0x138778
// size: 384 bytes
//

void RTMPUpdateHTIE(undefined4 param_1,undefined4 param_2,byte *param_3,int param_4)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  byte bVar7;
  byte bVar8;
  byte *pbVar9;
  int iVar10;
  
  bVar7 = wlan_config_get_ht_bw(param_2);
  bVar8 = wlan_config_get_ht_bw(param_2);
  pbVar9 = (byte *)wlan_operate_get_ht_cap(param_2);
  iVar10 = wlan_operate_get_addht(param_2);
  RTMPZeroMemory(param_3,0x1a);
  RTMPZeroMemory(param_4,0x16);
  bVar1 = param_3[1];
  *param_3 = *param_3 & 0xfd | (bVar7 & 1) << 1;
  bVar7 = *param_3;
  bVar2 = param_3[2];
  bVar3 = (byte)((((uint)*pbVar9 << 0x1c) >> 0x1e) << 2);
  *param_3 = bVar7 & 0xf3 | bVar3;
  bVar4 = (byte)((((uint)*pbVar9 << 0x1b) >> 0x1f) << 4);
  *param_3 = bVar7 & 0xe3 | bVar3 | bVar4;
  bVar5 = (byte)((((uint)*pbVar9 << 0x1a) >> 0x1f) << 5);
  *param_3 = bVar7 & 0xc3 | bVar3 | bVar4 | bVar5;
  bVar6 = (byte)((((uint)*pbVar9 << 0x19) >> 0x1f) << 6);
  *param_3 = bVar7 & 0x83 | bVar3 | bVar4 | bVar5 | bVar6;
  *param_3 = bVar7 & 3 | bVar3 | bVar4 | bVar5 | bVar6 | *pbVar9 & 0x80;
  bVar7 = pbVar9[1];
  param_3[1] = bVar1 & 0xfc | bVar7 & 3;
  param_3[1] = bVar1 & 0xf4 | bVar7 & 3 | (byte)((((uint)pbVar9[1] << 0x1c) >> 0x1f) << 3);
  bVar1 = pbVar9[2];
  param_3[2] = bVar2 & 0xfc | bVar1 & 3;
  param_3[2] = bVar2 & 0xe0 | bVar1 & 3 | (byte)((((uint)pbVar9[2] << 0x1b) >> 0x1d) << 2);
  *(byte *)(param_4 + 1) =
       *(byte *)(param_4 + 1) & 0xf8 | *(byte *)(iVar10 + 1) & 3 | (bVar8 & 1) << 2;
  *(byte *)(param_4 + 2) = *(byte *)(param_4 + 2) & 0xfc | *(byte *)(iVar10 + 2) & 3;
  *(byte *)(param_4 + 2) =
       *(byte *)(param_4 + 2) & 0xfb | (byte)((((uint)*(byte *)(iVar10 + 2) << 0x1d) >> 0x1f) << 2);
  RTMPMoveMemory(param_4 + 6,param_1,4);
  if (DebugLevel < 3) {
    return;
  }
  printk("RTMPUpdateHTIE <==\n");
  return;
}

