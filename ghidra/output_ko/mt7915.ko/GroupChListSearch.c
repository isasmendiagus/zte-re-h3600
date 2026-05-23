// module: mt7915.ko
// function: GroupChListSearch @ 0x22d7b8
// size: 104 bytes
//

char GroupChListSearch(int param_1,uint param_2)

{
  byte *pbVar1;
  char cVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0xa795e4) != '\0') {
    if (*(byte *)(param_1 + 0xa79235) == param_2) {
      return '\0';
    }
    cVar2 = '\0';
    iVar3 = param_1 + 0xa79234;
    while( true ) {
      cVar2 = cVar2 + '\x01';
      if (cVar2 == *(char *)(param_1 + 0xa795e4)) break;
      pbVar1 = (byte *)(iVar3 + 0x11);
      iVar3 = iVar3 + 0x10;
      if (*pbVar1 == param_2) {
        return cVar2;
      }
    }
  }
  return -1;
}

