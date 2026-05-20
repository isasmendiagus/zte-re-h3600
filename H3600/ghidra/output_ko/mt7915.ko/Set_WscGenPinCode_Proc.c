// module: mt7915.ko
// function: Set_WscGenPinCode_Proc @ 0xda194
// size: 420 bytes
//

undefined4
Set_WscGenPinCode_Proc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  
  if (param_1 == (int *)0x0) {
    if (DebugLevel < 0) {
      return 1;
    }
    printk("%s: pAd == NULL!\n","Set_WscGenPinCode_Proc",param_3,DebugLevel,param_4);
    return 1;
  }
  iVar3 = *param_1;
  uVar4 = *(uint *)(iVar3 + 0x3c);
  if (*(char *)((int)param_1 + 0x286285) == '\x01') {
    if (*(int *)(iVar3 + 0x38) == 0x400) {
      piVar2 = param_1 + (uVar4 & 0xff) * 0x84dec + 0xdbb8f;
      if (DebugLevel < 3) goto LAB_000da1ec;
      printk("IF(apcli%d) Set_WscGenPinCode_Proc:: This command is from apcli interface now.\n");
    }
    else {
      piVar2 = param_1 + (uVar4 & 0xff) * 0x160d + 0xae14b;
      if (DebugLevel < 3) goto LAB_000da1ec;
      printk("IF(ra%d) Set_WscGenPinCode_Proc:: This command is from ra interface now.\n");
    }
    if (*(char *)((int)param_1 + 0x286285) != '\0') goto LAB_000da1ec;
    uVar1 = *(uint *)(iVar3 + 0x3c);
  }
  else {
    uVar1 = uVar4;
    if (*(char *)((int)param_1 + 0x286285) != '\0') {
      if (DebugLevel < 0) {
        return 1;
      }
      printk("%s: pWscControl == NULL!\n","Set_WscGenPinCode_Proc",param_3,DebugLevel,param_4);
      return 1;
    }
  }
  piVar2 = param_1 + uVar1 * 0x84dec + 0xdbb8f;
LAB_000da1ec:
  if (*(char *)((int)piVar2 + 0x19) == '\0') {
    *(undefined1 *)(piVar2 + 8) = 8;
    iVar3 = WscRandomGeneratePinCode(param_1,uVar4 & 0xff);
    piVar2[7] = iVar3;
  }
  else {
    *(undefined1 *)(piVar2 + 8) = 4;
    iVar3 = WscRandomGen4digitPinCode();
    piVar2[7] = iVar3;
  }
  if (2 < DebugLevel) {
    printk("Set_WscGenPinCode_Proc:: Enrollee PinCode\t\t%08u\n",piVar2[7]);
  }
  return 1;
}

