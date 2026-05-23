// module: mt7915.ko
// function: TotalChNum @ 0x140f44
// size: 56 bytes
//

short TotalChNum(char *param_1)

{
  byte *pbVar1;
  short sVar2;
  
  if (*param_1 != '\0') {
    sVar2 = 0;
    do {
      pbVar1 = (byte *)(param_1 + 1);
      param_1 = param_1 + 3;
      sVar2 = sVar2 + (ushort)*pbVar1;
    } while (*param_1 != '\0');
    return sVar2;
  }
  return 0;
}

