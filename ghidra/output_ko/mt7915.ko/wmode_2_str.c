// module: mt7915.ko
// function: wmode_2_str @ 0xb7f90
// size: 240 bytes
//

char * wmode_2_str(int param_1)

{
  uint uVar1;
  char *pcVar2;
  int iVar3;
  size_t sVar4;
  size_t __n;
  uint uVar5;
  undefined **ppuVar6;
  char *__s;
  char *pcVar7;
  char *local_2c [2];
  
  iVar3 = os_alloc_mem(0,local_2c,0x1b);
  if (iVar3 != 0) {
    return (char *)0x0;
  }
  __memzero(local_2c[0],0x1b);
  pcVar7 = local_2c[0];
  ppuVar6 = &PTR__LC460_002942a8;
  sVar4 = strlen(local_2c[0]);
  uVar5 = 0;
  iVar3 = 0;
  while( true ) {
    uVar1 = uVar5 & 0xff;
    uVar5 = uVar5 + 1;
    if ((param_1 >> uVar1 & 1U) != 0) {
      __s = ppuVar6[1];
      __n = strlen(__s);
      pcVar2 = local_2c[0];
      if (0x19 < __n + sVar4) {
        return pcVar7;
      }
      if (*pcVar7 != '\0') {
        pcVar7[iVar3] = '/';
        __n = strlen(__s);
        iVar3 = iVar3 + 1;
        pcVar7 = pcVar2;
      }
      memmove(pcVar7 + iVar3,__s,__n);
      sVar4 = strlen(__s);
      pcVar7 = local_2c[0];
      iVar3 = iVar3 + sVar4;
      sVar4 = strlen(local_2c[0]);
    }
    ppuVar6 = ppuVar6 + 1;
    if (0x1a < sVar4) break;
    if (uVar5 == 9) {
      return pcVar7;
    }
  }
  return pcVar7;
}

