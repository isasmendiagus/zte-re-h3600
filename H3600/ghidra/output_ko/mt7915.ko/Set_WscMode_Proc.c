// module: mt7915.ko
// function: Set_WscMode_Proc @ 0x5a400
// size: 244 bytes
//

undefined4 Set_WscMode_Proc(int *param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = *(int *)(*param_1 + 0x3c);
  iVar2 = os_str_tol(param_2,0,10);
  iVar1 = DebugLevel;
  if (iVar2 == 3) {
    iVar4 = iVar3 * 0x20;
    if ((char)param_1[iVar3 * 0x84dec + 0xdc6ee] != '\x01') goto LAB_0005a45c;
  }
  else if (iVar2 - 1U < 3) {
    iVar4 = iVar3 << 5;
LAB_0005a45c:
    param_1[(iVar4 * 4 + iVar3 * 5) * 0xffc + 0xdbb90] = iVar2;
    if (2 < iVar1) {
      printk("Set_WscMode_Proc::(WscMode=%d)\n",iVar2);
      return 1;
    }
    return 1;
  }
  if (2 < DebugLevel) {
    printk("Set_WscMode_Proc:: Set failed!!(Set_WscMode_Proc=%s)\n",param_2);
    return 0;
  }
  return 0;
}

