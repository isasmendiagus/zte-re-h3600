// module: mt7915.ko
// function: ZTE_Send_Deauth_At_Btm_Failed @ 0x15c8e4
// size: 244 bytes
//

undefined4 ZTE_Send_Deauth_At_Btm_Failed(int param_1,undefined1 *param_2)

{
  int iVar1;
  void *__s2;
  int iVar2;
  
  if (0 < DebugLevel) {
    printk("(%s)sta_mac=%02x:%02x:%02x:%02x:%02x:%02x\n","ZTE_Send_Deauth_At_Btm_Failed",*param_2,
           param_2[1],param_2[2],param_2[3],param_2[4],param_2[5]);
  }
  __s2 = (void *)(param_1 + 0xa1e0c);
  iVar2 = 0;
  while (((*(int *)((int)__s2 + -0xec) != 0x20001 || (iVar1 = memcmp(param_2,__s2,6), iVar1 != 0))
         || (*(char *)((int)__s2 + 0xc37) == '\0'))) {
    iVar2 = iVar2 + 1;
    __s2 = (void *)((int)__s2 + 0x14c0);
    if (iVar2 == 0x120) {
      return 0;
    }
  }
  __MlmeDeAuthAction(param_1,iVar2 * 0x14c0 + param_1 + 0xa1d20,3,0,"ZTE_Send_Deauth_At_Btm_Failed",
                     0x1999);
  return 0;
}

