// module: mt7915.ko
// function: ARC4_Discard_KeyLength @ 0x1241e8
// size: 84 bytes
//

void ARC4_Discard_KeyLength(uint *param_1,int param_2)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  
  if (param_2 == 0) {
    return;
  }
  uVar2 = *param_1;
  iVar4 = 0;
  uVar3 = param_1[1];
  do {
    iVar4 = iVar4 + 1;
    uVar2 = uVar2 + 1 & 0xff;
    bVar1 = *(byte *)((int)param_1 + uVar2 + 8);
    uVar3 = uVar3 + bVar1 & 0xff;
    *(undefined1 *)((int)param_1 + uVar2 + 8) = *(undefined1 *)((int)param_1 + uVar3 + 8);
    *(byte *)((int)param_1 + uVar3 + 8) = bVar1;
  } while (iVar4 != param_2);
  *param_1 = uVar2;
  param_1[1] = uVar3;
  return;
}

