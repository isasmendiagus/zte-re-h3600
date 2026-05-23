// module: switch.ko
// function: npu_drv_lookup_multientry @ 0x209d4
// size: 100 bytes
//

char * npu_drv_lookup_multientry(char *param_1)

{
  short sVar1;
  int iVar2;
  undefined1 *__s1;
  
  __s1 = gMultiVlanEntry;
  sVar1 = *(short *)(param_1 + 0x10);
  while (((*(short *)(__s1 + 0x10) != sVar1 ||
          (*(short *)(__s1 + 0x12) != *(short *)(param_1 + 0x12))) ||
         (iVar2 = strcmp(__s1,param_1), iVar2 != 0))) {
    __s1 = __s1 + 0x16;
    if ((undefined4 *)__s1 == &g_multivlan_lock) {
      return (char *)0x0;
    }
  }
  return __s1;
}

