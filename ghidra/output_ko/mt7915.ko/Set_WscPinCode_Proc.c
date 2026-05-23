// module: mt7915.ko
// function: Set_WscPinCode_Proc @ 0x5a4f4
// size: 448 bytes
//

undefined4 Set_WscPinCode_Proc(int *param_1,char *param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  size_t sVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = *(int *)(*param_1 + 0x3c);
  iVar1 = os_str_tol(param_2,0,10,*param_1,param_4);
  sVar2 = strlen(param_2);
  if ((sVar2 == 4) || (iVar3 = ValidateChecksum(iVar1), iVar3 != 0)) {
    if (((char)param_1[iVar4 * 0x84dec + 0xdc60c] == '\0') ||
       (param_1[iVar4 * 0x84dec + 0xdc60b] != iVar1)) {
      *(undefined1 *)(param_1 + iVar4 * 0x84dec + 0xdc60c) = 0;
      param_1[iVar4 * 0x84dec + 0xdbb94] = iVar1;
      param_1[iVar4 * 0x84dec + 0xdc60b] = iVar1;
      sVar2 = strlen(param_2);
      if (sVar2 == 4) {
        *(undefined1 *)(param_1 + iVar4 * 0x84dec + 0xdbb95) = 4;
      }
      else {
        *(undefined1 *)(param_1 + iVar4 * 0x84dec + 0xdbb95) = 8;
      }
      WscGetRegDataPIN(param_1,param_1[iVar4 * 0x84dec + 0xdbb94],
                       param_1 + iVar4 * 0x84dec + 0xdbb8f);
      if (2 < DebugLevel) {
        printk("IF(ra0) Set_WscPinCode_Proc::(PinCode=%d)\n",param_1[iVar4 * 0x84dec + 0xdbb94]);
      }
      return 1;
    }
    if (2 < DebugLevel) {
      printk("PIN authentication or communication error occurs!!\nRegistrar does NOT accept the same PIN again!(PIN:%08u)\n"
             ,iVar1);
    }
  }
  else if (2 < DebugLevel) {
    printk("Set_WscPinCode_Proc:: Checksum is invalid\n");
    return 0;
  }
  return 0;
}

