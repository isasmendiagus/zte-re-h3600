// module: mt7915.ko
// function: HcIsRfRun @ 0xa99ec
// size: 148 bytes
//

undefined4 HcIsRfRun(int param_1,uint param_2)

{
  char *pcVar1;
  int *piVar2;
  ushort uVar3;
  char cVar4;
  int iVar5;
  
  iVar5 = *(int *)(param_1 + 0xa797a0);
  pcVar1 = (char *)(iVar5 + 0x32d8);
  if (*pcVar1 == '\0') {
    return 0;
  }
  cVar4 = '\0';
  while( true ) {
    piVar2 = (int *)(iVar5 + 4);
    cVar4 = cVar4 + '\x01';
    iVar5 = iVar5 + 0x1c;
    uVar3 = *(ushort *)(*piVar2 + 2);
    if (((((uVar3 & 0x4e) != 0) && ((param_2 & 1) != 0)) ||
        (((uVar3 & 0xb1) != 0 && ((param_2 & 2) != 0)))) ||
       (((uVar3 & 0x100) != 0 && ((param_2 & 4) != 0)))) break;
    if (cVar4 == *pcVar1) {
      return 0;
    }
  }
  return 1;
}

