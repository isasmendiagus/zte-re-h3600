// module: mt7915.ko
// function: MlmeLpExit @ 0x12cb1c
// size: 156 bytes
//

void MlmeLpExit(int *param_1)

{
  int iVar1;
  int iVar2;
  bool bVar3;
  
  if (*(char *)((int)param_1 + 0x286285) == '\x01') {
    iVar1 = *(int *)(*param_1 + 0x3c) * 0x160d + 0xadc92;
  }
  else {
    if (*(char *)((int)param_1 + 0x286285) != '\0') {
      return;
    }
    iVar1 = *(int *)(*param_1 + 0x3c) * 0x84dec + 0xdb6d6;
  }
  iVar2 = param_1[0xa18a0];
  bVar3 = iVar2 != 0;
  if (iVar2 != 1) {
    bVar3 = iVar2 != 4;
  }
  if (bVar3 && (iVar2 != 1 && iVar2 != 5)) {
    return;
  }
  if (param_1 + iVar1 == (int *)0x0) {
    return;
  }
  if ((param_1[0xa5b19] & 0xffffU) != 0x7622) {
    MTMlmeLpExit();
    return;
  }
  MlmeRadioOn();
  return;
}

