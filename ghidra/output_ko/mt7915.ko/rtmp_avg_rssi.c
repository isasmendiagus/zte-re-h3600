// module: mt7915.ko
// function: rtmp_avg_rssi @ 0x12f944
// size: 212 bytes
//

int rtmp_avg_rssi(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  if (("SetPartProfileParameters"[param_1 + 0x18] & 0xfU) != 0) {
    uVar3 = 0;
    iVar1 = 0;
    do {
      iVar2 = param_2 + uVar3;
      uVar3 = uVar3 + 1 & 0xff;
      if (*(char *)(iVar2 + 4) != -0x7f) {
        iVar1 = iVar1 + 1;
      }
    } while (uVar3 < ((byte)"SetPartProfileParameters"[param_1 + 0x18] & 0xf));
    if (iVar1 == 4) {
      return (int)(char)((int)*(char *)(param_2 + 4) + (int)*(char *)(param_2 + 5) +
                         (int)*(char *)(param_2 + 6) + (int)*(char *)(param_2 + 7) >> 2);
    }
    if (iVar1 == 3) {
      iVar1 = (int)*(char *)(param_2 + 4) + (int)*(char *)(param_2 + 5) +
              (int)*(char *)(param_2 + 6);
      return (int)(char)((char)((ulonglong)((longlong)iVar1 * 0x55555556) >> 0x20) -
                        (char)(iVar1 >> 0x1f));
    }
    if (iVar1 == 2) {
      return (int)(char)((int)*(char *)(param_2 + 4) + (int)*(char *)(param_2 + 5) >> 1);
    }
  }
  return (int)*(char *)(param_2 + 4);
}

