// module: mt7915.ko
// function: RTMPAvgRssi @ 0x12f8b0
// size: 148 bytes
//

int RTMPAvgRssi(int param_1,int param_2)

{
  char cVar1;
  int iVar2;
  byte bVar3;
  
  bVar3 = "SetPartProfileParameters"[param_1 + 0x18] & 0xf;
  if (bVar3 == 4) {
    return (int)(char)((int)*(char *)(param_2 + 4) + (int)*(char *)(param_2 + 5) +
                       (int)*(char *)(param_2 + 6) + (int)*(char *)(param_2 + 7) >> 2);
  }
  if (bVar3 == 3) {
    iVar2 = (int)*(char *)(param_2 + 4) + (int)*(char *)(param_2 + 5) + (int)*(char *)(param_2 + 6);
    return (int)(char)((char)((ulonglong)((longlong)iVar2 * 0x55555556) >> 0x20) -
                      (char)(iVar2 >> 0x1f));
  }
  if (bVar3 == 2) {
    cVar1 = (char)((int)*(char *)(param_2 + 4) + (int)*(char *)(param_2 + 5) >> 1);
  }
  else {
    cVar1 = *(char *)(param_2 + 4);
  }
  return (int)cVar1;
}

