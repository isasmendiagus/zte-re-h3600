// module: mt7915.ko
// function: os_str_chr @ 0x245b50
// size: 4 bytes
//

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

char * os_str_chr(char *__s,int __c)

{
  char *pcVar1;
  
  pcVar1 = strchr(__s,__c);
  return pcVar1;
}

