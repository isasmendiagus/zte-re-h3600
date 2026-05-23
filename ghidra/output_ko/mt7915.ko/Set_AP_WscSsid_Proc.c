// module: mt7915.ko
// function: Set_AP_WscSsid_Proc @ 0x28d48
// size: 328 bytes
//

undefined4 Set_AP_WscSsid_Proc(int *param_1,char *param_2)

{
  int iVar1;
  int iVar2;
  size_t sVar3;
  undefined *__dest;
  uint uVar4;
  void *__dest_00;
  
  if (*(int *)(*param_1 + 0x38) != 0x400) {
    return 0;
  }
  uVar4 = *(uint *)(*param_1 + 0x3c) & 0xff;
  iVar1 = uVar4 * 0x2137b0;
  __memzero((undefined *)((int)param_1 + (int)(&DAT_0036ee60 + iVar1 + 4)),0x24);
  if ((*param_2 != '\0') && (sVar3 = strlen(param_2), sVar3 < 0x21)) {
    __dest = (undefined *)((int)param_1 + (int)(&DAT_0036ee60 + iVar1 + 8));
    memmove(__dest,param_2,sVar3);
    sVar3 = strlen(param_2);
    __dest_00 = (void *)((int)param_1 + iVar1 + 0x580e3a);
    param_1[uVar4 * 0x84dec + 0xdbb99] = sVar3;
    __memzero(__dest_00,0x20);
    sVar3 = strlen(param_2);
    memmove(__dest_00,param_2,sVar3);
    sVar3 = strlen(param_2);
    iVar2 = DebugLevel;
    *(char *)((int)param_1 + iVar1 + 0x580e5a) = (char)sVar3;
    if (iVar2 < 3) {
      return 1;
    }
    printk("Set_WscSsid_Proc:: (Select SsidLen=%d,Ssid=%s)\n",param_1[uVar4 * 0x84dec + 0xdbb99],
           __dest);
    return 1;
  }
  return 0;
}

