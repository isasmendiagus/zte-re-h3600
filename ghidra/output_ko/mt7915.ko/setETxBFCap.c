// module: mt7915.ko
// function: setETxBFCap @ 0x176e48
// size: 248 bytes
//

void setETxBFCap(undefined4 param_1,int param_2)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte *pbVar5;
  byte bVar6;
  int iVar7;
  
  iVar7 = *(int *)(param_2 + 0x28);
  pbVar5 = *(byte **)(param_2 + 0x14);
  if (iVar7 == 0) {
    __memzero(pbVar5,4);
    return;
  }
  if (iVar7 == 2) {
    bVar1 = pbVar5[2];
    bVar6 = *pbVar5 & 0xf7;
  }
  else {
    if (iVar7 == 3) {
      bVar3 = pbVar5[1];
      bVar4 = pbVar5[3];
      *pbVar5 = *pbVar5 & 0xeb | 8;
      pbVar5[2] = ~(~(pbVar5[2] & 0x18) & 0x78);
      goto LAB_00176ec0;
    }
    bVar1 = pbVar5[2];
    bVar6 = *pbVar5 | 8;
  }
  *pbVar5 = bVar6;
  bVar2 = *(byte *)(param_2 + 5);
  bVar3 = pbVar5[1];
  bVar4 = pbVar5[3];
  pbVar5[2] = ~(~(bVar1 & 0x18) & 0x78);
  *pbVar5 = bVar6 & 0xeb | (1 < bVar2) << 4;
LAB_00176ec0:
  pbVar5[1] = bVar3 & 0x1d | 4;
  pbVar5[3] = bVar4 | 1;
  pbVar5[3] = bVar4 & 0xe7 | 1 | (*(char *)(param_2 + 5) - 1U & 3) << 3;
  return;
}

