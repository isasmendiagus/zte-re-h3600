// module: mt7915.ko
// function: HcDevExit @ 0xa8ab4
// size: 72 bytes
//

void HcDevExit(int param_1)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0xa797a0);
  if (*(char *)(iVar3 + 0x32d8) == '\0') {
    return;
  }
  bVar1 = 0;
  do {
    bVar2 = bVar1 + 1;
    HdevExit(iVar3,bVar1);
    bVar1 = bVar2;
  } while (bVar2 < *(byte *)(iVar3 + 0x32d8));
  return;
}

