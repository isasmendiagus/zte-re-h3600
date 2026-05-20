// module: mt7915.ko
// function: RepeaterInvaildMacLookup @ 0x82758
// size: 140 bytes
//

void * RepeaterInvaildMacLookup(int param_1,byte *param_2)

{
  int iVar1;
  void *__s1;
  
  __s1 = *(void **)(param_1 +
                   ((byte)(*param_2 ^ param_2[1] ^ param_2[2] ^ param_2[3] ^ param_2[4] ^ param_2[5]
                          ) + 0xda0a8) * 4);
  while( true ) {
    if (__s1 == (void *)0x0) {
      return (void *)0x0;
    }
    iVar1 = memcmp(__s1,param_2,6);
    if (iVar1 == 0) break;
    __s1 = *(void **)((int)__s1 + 8);
  }
  if (*(char *)((int)__s1 + 7) == '\0') {
    __s1 = (void *)0x0;
  }
  return __s1;
}

