// module: mt7915.ko
// function: D_SetEnable @ 0x9d454
// size: 324 bytes
//

undefined4 D_SetEnable(int param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  int iVar4;
  
  iVar4 = *(int *)(param_1 + 0x101c);
  if (DebugLevel < 1) {
    if (*(byte *)(param_1 + 5) == param_2) {
      return 0;
    }
  }
  else {
    printk("%s(): enable = %u\n","D_SetEnable",param_2,DebugLevel,param_4);
    if (*(byte *)(param_1 + 5) == param_2) {
      if (DebugLevel < 1) {
        return 0;
      }
      pcVar3 = "enabled";
      if (*(byte *)(param_1 + 5) == 0) {
        pcVar3 = "disabled";
      }
      printk(&_LC60,pcVar3);
      return 0;
    }
  }
  if (param_2 == 0) {
    (&DAT_0036b920)[iVar4] = 0;
    iVar2 = BndStrg_Release(iVar4);
  }
  else {
    iVar2 = BndStrg_Enable(param_1,param_2);
    iVar1 = DebugLevel;
    if ((((&DAT_0036c9bd)[iVar4] != '\0') && ((&DAT_0036b929)[iVar4] != '\0')) &&
       ((&DAT_0036b920)[iVar4] = (char)param_2, 0 < iVar1)) {
      printk("%s(): BandSteering enable = %u\n","D_SetEnable",param_2);
    }
  }
  if ((iVar2 != 0) && (-1 < DebugLevel)) {
    printk("Error in %s(), error code = %d!\n","D_SetEnable",iVar2,DebugLevel,param_4);
    return 1;
  }
  return 1;
}

