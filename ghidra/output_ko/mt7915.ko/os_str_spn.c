// module: mt7915.ko
// function: os_str_spn @ 0x245b58
// size: 4 bytes
//

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

size_t os_str_spn(char *__s,char *__accept)

{
  size_t sVar1;
  
  sVar1 = strspn(__s,__accept);
  return sVar1;
}

