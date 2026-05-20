// module: mt7915.ko
// function: WscParseV2SubItem @ 0x201700
// size: 168 bytes
//

undefined4 WscParseV2SubItem(uint param_1,int param_2,int param_3,void *param_4,byte *param_5)

{
  int iVar1;
  byte *pbVar2;
  uint uVar3;
  byte bVar4;
  
  param_3 = param_3 + -3;
  pbVar2 = (byte *)(param_2 + 3);
  hex_dump("WscParseV2SubItem - pData",pbVar2,param_3);
  bVar4 = *(byte *)(param_2 + 4);
  iVar1 = bVar4 + 2;
  if (param_3 < iVar1) {
    return 0;
  }
  if (*(byte *)(param_2 + 3) != param_1) {
    uVar3 = 0;
    do {
      pbVar2 = pbVar2 + iVar1;
      uVar3 = uVar3 + iVar1 & 0xffff;
      bVar4 = pbVar2[1];
      iVar1 = bVar4 + 2;
      if (param_3 < (int)(uVar3 + 2 + (uint)bVar4)) {
        return 0;
      }
    } while (*pbVar2 != param_1);
  }
  *param_5 = bVar4;
  memmove(param_4,pbVar2 + 2,(uint)pbVar2[1]);
  return 1;
}

