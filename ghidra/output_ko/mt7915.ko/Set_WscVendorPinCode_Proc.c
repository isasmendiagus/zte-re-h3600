// module: mt7915.ko
// function: Set_WscVendorPinCode_Proc @ 0xda33c
// size: 296 bytes
//

undefined4 Set_WscVendorPinCode_Proc(int *param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  
  iVar4 = *param_1;
  uVar3 = *(uint *)(iVar4 + 0x3c);
  if (*(char *)((int)param_1 + 0x286285) == '\x01') {
    uVar3 = uVar3 & 0xff;
    if (*(int *)(iVar4 + 0x38) == 0x400) {
      piVar2 = param_1 + uVar3 * 0x84dec + 0xdbb8f;
      if (DebugLevel < 3) goto LAB_000da38c;
      printk("Set_WscVendorPinCode_Proc() for apcli(%d)\n",uVar3);
    }
    else {
      piVar2 = param_1 + uVar3 * 0x160d + 0xae14b;
      if (DebugLevel < 3) goto LAB_000da38c;
      printk("Set_WscVendorPinCode_Proc() for ra%d!\n",uVar3);
    }
    if (*(char *)((int)param_1 + 0x286285) != '\0') goto LAB_000da38c;
    uVar3 = *(uint *)(iVar4 + 0x3c);
  }
  else if (*(char *)((int)param_1 + 0x286285) != '\0') {
    return 0;
  }
  piVar2 = param_1 + uVar3 * 0x84dec + 0xdbb8f;
LAB_000da38c:
  if (piVar2 == (int *)0x0) {
    return 0;
  }
  uVar1 = RT_CfgSetWscPinCode(param_1,param_2);
  return uVar1;
}

