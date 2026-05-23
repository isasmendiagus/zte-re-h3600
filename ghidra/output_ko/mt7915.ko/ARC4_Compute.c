// module: mt7915.ko
// function: ARC4_Compute @ 0x124174
// size: 116 bytes
//

void ARC4_Compute(uint *param_1,byte *param_2,int param_3,int param_4)

{
  byte bVar1;
  byte *pbVar2;
  byte *pbVar3;
  byte *pbVar4;
  uint uVar5;
  uint uVar6;
  
  if (param_3 == 0) {
    return;
  }
  pbVar4 = (byte *)(param_4 + -1);
  pbVar2 = param_2;
  do {
    uVar5 = *param_1 + 1 & 0xff;
    *param_1 = uVar5;
    bVar1 = *(byte *)((int)param_1 + uVar5 + 8);
    uVar6 = (uint)bVar1 + param_1[1] & 0xff;
    param_1[1] = uVar6;
    *(undefined1 *)((int)param_1 + uVar5 + 8) = *(undefined1 *)((int)param_1 + uVar6 + 8);
    *(byte *)((int)param_1 + uVar6 + 8) = bVar1;
    pbVar3 = pbVar2 + 1;
    pbVar4 = pbVar4 + 1;
    *pbVar4 = *(byte *)((int)param_1 +
                       ((uint)bVar1 + (uint)*(byte *)((int)param_1 + uVar5 + 8) & 0xff) + 8) ^
              *pbVar2;
    pbVar2 = pbVar3;
  } while (pbVar3 != param_2 + param_3);
  return;
}

