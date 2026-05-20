// module: mt7915.ko
// function: RTMPSearchPMKIDCache @ 0x19820
// size: 248 bytes
//

int RTMPSearchPMKIDCache(int param_1,uint param_2,undefined1 *param_3)

{
  int iVar1;
  void *__s1;
  int iVar2;
  
  __s1 = (void *)(param_1 + 1);
  iVar2 = 0;
  while (((*(char *)((int)__s1 + 0x5b) != '\x01' || (*(byte *)((int)__s1 + -1) != param_2)) ||
         (iVar1 = memcmp(__s1,param_3,6), iVar1 != 0))) {
    iVar2 = iVar2 + 1;
    __s1 = (void *)((int)__s1 + 0x60);
    if (iVar2 == 0x80) {
      if (2 < DebugLevel) {
        printk("%s(): - IF(%d) not found\n","RTMPSearchPMKIDCache",param_2);
      }
      return -1;
    }
  }
  if (2 < DebugLevel) {
    printk("%s():%02x:%02x:%02x:%02x:%02x:%02x cache(%d) from IF(ra%d)\n","RTMPSearchPMKIDCache",
           *param_3,param_3[1],param_3[2],param_3[3],param_3[4],param_3[5],iVar2,param_2);
  }
  return iVar2;
}

