// module: mt7915.ko
// function: Set_PreAuthIfName_Proc @ 0x28f54
// size: 200 bytes
//

undefined4 Set_PreAuthIfName_Proc(int *param_1,char *param_2)

{
  size_t sVar1;
  uint uVar2;
  void *__dest;
  
  uVar2 = (uint)*(byte *)(*param_1 + 0x3c);
  if (uVar2 < *(byte *)((int)param_1 + 0x2b7242)) {
    if ((*param_2 != '\0') && (sVar1 = strlen(param_2), sVar1 < 0x11)) {
      __dest = (void *)((int)param_1 + uVar2 * 0x5834 + 0x2b7749);
      *(char *)((int)param_1 + uVar2 * 0x5834 + 0x2b7759) = (char)sVar1;
      sVar1 = strlen(param_2);
      memmove(__dest,param_2,sVar1);
      if (2 < DebugLevel) {
        printk("PreAuthifname=%s, len=%d\n",__dest,
               *(undefined1 *)((int)param_1 + uVar2 * 0x5834 + 0x2b7759));
      }
    }
    return 1;
  }
  return 0;
}

