// module: mt7915.ko
// function: MtCmdGetEdcaRsp @ 0x1ab488
// size: 112 bytes
//

void MtCmdGetEdcaRsp(int param_1,byte *param_2)

{
  int iVar1;
  byte bVar2;
  byte *pbVar3;
  byte *pbVar4;
  byte *pbVar5;
  uint uVar6;
  
  bVar2 = param_2[4];
  pbVar5 = *(byte **)(param_1 + 0xc);
  *pbVar5 = bVar2;
  if (bVar2 == 0) {
    return;
  }
  uVar6 = 0;
  pbVar3 = param_2;
  pbVar4 = pbVar5;
  do {
    iVar1 = uVar6 * 8;
    uVar6 = uVar6 + 1;
    *(undefined2 *)(pbVar5 + iVar1 + 10) = *(undefined2 *)(param_2 + iVar1 + 0xe);
    *(undefined2 *)(pbVar5 + iVar1 + 8) = *(undefined2 *)(param_2 + iVar1 + 0xc);
    pbVar4[4] = pbVar3[8];
    pbVar4[6] = pbVar3[10];
    pbVar4[7] = pbVar3[0xb];
    pbVar3 = pbVar3 + 8;
    pbVar4 = pbVar4 + 8;
  } while (uVar6 != bVar2);
  return;
}

