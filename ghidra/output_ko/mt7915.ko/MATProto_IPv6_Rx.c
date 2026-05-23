// module: mt7915.ko
// function: MATProto_IPv6_Rx @ 0x7c040
// size: 236 bytes
//

char * MATProto_IPv6_Rx(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  void *__s1;
  char *pcVar2;
  
  pcVar2 = *(char **)(param_1 + 0xc);
  if (pcVar2 == (char *)0x0) {
    return (char *)0x0;
  }
  if (*pcVar2 == '\0') {
    return (char *)0x0;
  }
  if (*(char *)(param_3 + 0x18) == -1) {
    if ((void *)(param_3 + 0x18) == (void *)0x0) {
      return pcVar2 + 0x108;
    }
    pcVar2[0x108] = '3';
    pcVar2[0x109] = '3';
    pcVar2[0x10a] = *(char *)(param_3 + 0x24);
    pcVar2[0x10b] = *(char *)(param_3 + 0x25);
    pcVar2[0x10c] = *(char *)(param_3 + 0x26);
    pcVar2[0x10d] = *(char *)(param_3 + 0x27);
    return pcVar2 + 0x108;
  }
  __s1 = *(void **)(pcVar2 + ((byte)(*(byte *)(param_3 + 0x22) ^ *(byte *)(param_3 + 0x25) ^
                                     *(byte *)(param_3 + 0x26) ^ *(byte *)(param_3 + 0x27)) & 0x3f)
                             * 4 + 4);
  while( true ) {
    if (__s1 == (void *)0x0) {
      return (char *)(*(int *)(pcVar2 + 0x104) + 0x10);
    }
    iVar1 = memcmp(__s1,(void *)(param_3 + 0x18),0x10);
    if (iVar1 == 0) break;
    __s1 = *(void **)((int)__s1 + 0x1c);
  }
  *(undefined4 *)((int)__s1 + 0x18) = jiffies;
  return (char *)((int)__s1 + 0x10);
}

