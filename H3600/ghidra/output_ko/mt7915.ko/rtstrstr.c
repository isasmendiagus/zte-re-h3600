// module: mt7915.ko
// function: rtstrstr @ 0xee358
// size: 112 bytes
//

char * rtstrstr(char *param_1,char *param_2)

{
  size_t __n;
  size_t sVar1;
  int iVar2;
  
  __n = strlen(param_2);
  if (__n == 0) {
    return param_1;
  }
  sVar1 = strlen(param_1);
  while( true ) {
    if ((int)sVar1 < (int)__n) {
      return (char *)0x0;
    }
    sVar1 = sVar1 - 1;
    iVar2 = memcmp(param_1,param_2,__n);
    if (iVar2 == 0) break;
    param_1 = param_1 + 1;
  }
  return param_1;
}

