// module: mt7915.ko
// function: RT_CfgSetWscPinCode @ 0xb8d28
// size: 188 bytes
//

undefined4 RT_CfgSetWscPinCode(undefined4 param_1,char *param_2,int param_3)

{
  undefined4 uVar1;
  size_t sVar2;
  int iVar3;
  
  uVar1 = os_str_tol(param_2,0,10);
  sVar2 = strlen(param_2);
  if (sVar2 == 4) {
    *(undefined4 *)(param_3 + 0x1c) = uVar1;
    *(undefined1 *)(param_3 + 0x20) = 4;
  }
  else {
    iVar3 = ValidateChecksum(uVar1);
    if (iVar3 == 0) {
      if (-1 < DebugLevel) {
        printk("RT_CfgSetWscPinCode(): invalid Wsc PinCode (%d)\n",uVar1);
        return 0;
      }
      return 0;
    }
    *(undefined4 *)(param_3 + 0x1c) = uVar1;
    *(undefined1 *)(param_3 + 0x20) = 8;
  }
  if (2 < DebugLevel) {
    printk("RT_CfgSetWscPinCode():Wsc PinCode=%d\n",uVar1);
    return 1;
  }
  return 1;
}

