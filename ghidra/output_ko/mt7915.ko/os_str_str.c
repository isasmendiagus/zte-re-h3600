// module: mt7915.ko
// function: os_str_str @ 0x245b64
// size: 4 bytes
//

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

char * os_str_str(char *__haystack,char *__needle)

{
  char *pcVar1;
  
  pcVar1 = strstr(__haystack,__needle);
  return pcVar1;
}

