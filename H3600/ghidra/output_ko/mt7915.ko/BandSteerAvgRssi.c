// module: mt7915.ko
// function: BandSteerAvgRssi @ 0x9dde8
// size: 148 bytes
//

int BandSteerAvgRssi(int param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  byte bVar3;
  
  bVar3 = "SetPartProfileParameters"[param_1 + 0x18] & 0xf;
  if (bVar3 == 4) {
    return (int)(char)((int)*param_2 + (int)param_2[1] + (int)param_2[2] + (int)param_2[3] >> 2);
  }
  if (bVar3 == 3) {
    iVar2 = (int)*param_2 + (int)param_2[1] + (int)param_2[2];
    return (int)(char)((char)((ulonglong)((longlong)iVar2 * 0x55555556) >> 0x20) -
                      (char)(iVar2 >> 0x1f));
  }
  if (bVar3 == 2) {
    cVar1 = (char)((int)*param_2 + (int)param_2[1] >> 1);
  }
  else {
    cVar1 = *param_2;
  }
  return (int)cVar1;
}

