// module: mt7915.ko
// function: GetChannelLimitPwr @ 0xd84ac
// size: 172 bytes
//

byte GetChannelLimitPwr(int param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  byte bVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  byte *pbVar7;
  
  iVar5 = 0;
  while( true ) {
    iVar2 = iVar5 * 8;
    iVar1 = iVar5 * 8;
    iVar5 = iVar5 + 1;
    if (Region_ChPwrDesc_5GHZ[iVar2] == *(char *)(param_1 + 0x794c47)) break;
    if (iVar5 == 0x10) {
      return 0x24;
    }
  }
  pbVar7 = *(byte **)(Region_ChPwrDesc_5GHZ + iVar1 + 4);
  bVar3 = *pbVar7;
  do {
    uVar6 = (uint)bVar3;
    if (uVar6 == 0) {
      return 0x24;
    }
    if (pbVar7[1] != 0) {
      if (param_2 == uVar6) {
LAB_000d8550:
        return pbVar7[2];
      }
      uVar4 = 0;
      while( true ) {
        uVar4 = uVar4 + 1;
        uVar6 = uVar6 + 4 & 0xff;
        if (uVar4 == pbVar7[1]) break;
        if (uVar6 == param_2) goto LAB_000d8550;
      }
    }
    pbVar7 = pbVar7 + 3;
    bVar3 = *pbVar7;
  } while( true );
}

