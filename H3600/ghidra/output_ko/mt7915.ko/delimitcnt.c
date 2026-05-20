// module: mt7915.ko
// function: delimitcnt @ 0xeea90
// size: 48 bytes
//

int delimitcnt(char *param_1,char *param_2)

{
  char *pcVar1;
  int iVar2;
  
  iVar2 = 0;
  while( true ) {
    pcVar1 = strpbrk(param_1,param_2);
    param_1 = pcVar1 + 1;
    if (pcVar1 == (char *)0x0) break;
    iVar2 = iVar2 + 1;
  }
  return iVar2;
}

