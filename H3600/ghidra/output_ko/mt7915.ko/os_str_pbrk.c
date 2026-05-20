// module: mt7915.ko
// function: os_str_pbrk @ 0x245b54
// size: 4 bytes
//

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

char * os_str_pbrk(char *__s,char *__accept)

{
  char *pcVar1;
  
  pcVar1 = strpbrk(__s,__accept);
  return pcVar1;
}

