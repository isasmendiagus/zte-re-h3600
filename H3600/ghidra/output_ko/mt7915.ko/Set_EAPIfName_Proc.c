// module: mt7915.ko
// function: Set_EAPIfName_Proc @ 0x28e90
// size: 196 bytes
//

undefined4 Set_EAPIfName_Proc(int *param_1,char *param_2,undefined4 param_3,undefined4 param_4)

{
  size_t sVar1;
  uint uVar2;
  
  uVar2 = (uint)*(byte *)(*param_1 + 0x3c);
  if (uVar2 < *(byte *)((int)param_1 + 0x2b7242)) {
    if ((*param_2 != '\0') && (sVar1 = strlen(param_2), sVar1 < 0x11)) {
      *(char *)(param_1 + uVar2 * 0x160d + 0xaddd2) = (char)sVar1;
      sVar1 = strlen(param_2);
      memmove(param_1 + uVar2 * 0x160d + 0xaddce,param_2,sVar1);
      if (2 < DebugLevel) {
        printk("EAPifname=%s, len=%d\n",param_1 + uVar2 * 0x160d + 0xaddce,
               (char)param_1[uVar2 * 0x160d + 0xaddd2],DebugLevel,param_4);
      }
    }
    return 1;
  }
  return 0;
}

