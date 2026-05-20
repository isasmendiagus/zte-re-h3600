// module: mt7915.ko
// function: Set_ApCli_Ssid_Proc @ 0x30078
// size: 348 bytes
//

undefined4 Set_ApCli_Ssid_Proc(int *param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  size_t sVar3;
  uint uVar4;
  void *__dest;
  
  if (*(int *)(*param_1 + 0x38) != 0x400) {
    return 0;
  }
  uVar4 = *(uint *)(*param_1 + 0x3c);
  sVar3 = strlen(param_2);
  if (0x20 < sVar3) {
    return 0;
  }
  uVar4 = uVar4 & 0xff;
  cVar1 = *(char *)((int)param_1 + uVar4 * 0x2137b0 + 0x580e8d);
  sta_reset_owe_parameters(param_1,uVar4);
  if (cVar1 == '\x01') {
    *(undefined1 *)((int)param_1 + uVar4 * 0x2137b0 + 0x580e8d) = 0;
    ApCliIfDown(param_1);
  }
  __dest = (void *)((int)param_1 + uVar4 * 0x2137b0 + 0x580e3a);
  *(undefined1 *)(param_1 + uVar4 * 0x84dec + 0x1603a7) = 0;
  __memzero(__dest,0x20);
  sVar3 = strlen(param_2);
  memmove(__dest,param_2,sVar3);
  sVar3 = strlen(param_2);
  iVar2 = DebugLevel;
  *(char *)((int)param_1 + uVar4 * 0x2137b0 + 0x580e5a) = (char)sVar3;
  if (2 < iVar2) {
    printk("I/F(apcli%d) Set_ApCli_Ssid_Proc::(Len=%d,Ssid=%s)\n",uVar4,sVar3 & 0xff,__dest);
  }
  *(char *)((int)param_1 + uVar4 * 0x2137b0 + 0x580e8d) = cVar1;
  return 1;
}

