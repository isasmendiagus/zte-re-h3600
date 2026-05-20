// module: mt7915.ko
// function: RTMPSearchPMKIDCacheByPmkId @ 0x19ab8
// size: 276 bytes
//

int RTMPSearchPMKIDCacheByPmkId(int param_1,uint param_2,undefined1 *param_3,void *param_4)

{
  int iVar1;
  void *__s2;
  int iVar2;
  
  __s2 = (void *)(param_1 + 7);
  iVar2 = 0;
  while ((((*(char *)((int)__s2 + 0x55) != '\x01' || (*(byte *)((int)__s2 + -7) != param_2)) ||
          (iVar1 = memcmp((void *)((int)__s2 + -6),param_3,6), iVar1 != 0)) ||
         (iVar1 = memcmp(param_4,__s2,0x10), iVar1 != 0))) {
    iVar2 = iVar2 + 1;
    __s2 = (void *)((int)__s2 + 0x60);
    if (iVar2 == 0x80) {
      if (2 < DebugLevel) {
        printk("%s(): - IF(%d) not found\n","RTMPSearchPMKIDCacheByPmkId",param_2);
      }
      return -1;
    }
  }
  if (2 < DebugLevel) {
    printk("%s():%02x:%02x:%02x:%02x:%02x:%02x cache(%d) from IF(ra%d)\n",
           "RTMPSearchPMKIDCacheByPmkId",*param_3,param_3[1],param_3[2],param_3[3],param_3[4],
           param_3[5],iVar2,param_2);
  }
  return iVar2;
}

