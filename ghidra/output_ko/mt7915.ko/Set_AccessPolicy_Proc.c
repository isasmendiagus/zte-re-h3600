// module: mt7915.ko
// function: Set_AccessPolicy_Proc @ 0x34360
// size: 288 bytes
//

undefined4 Set_AccessPolicy_Proc(int *param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = *param_1;
  iVar1 = os_str_tol(param_2,0,10);
  if ((iVar1 == 1) || (iVar1 == 2)) {
    iVar2 = *(int *)(iVar3 + 0x3c);
    *(char *)((int)param_1 + iVar2 * 0x5834 + 0x2bb671) = (char)iVar1;
    *(undefined1 *)((int)param_1 + iVar2 * 0x5834 + 0x2bb672) = 0;
    *(undefined1 *)((int)param_1 + iVar2 * 0x5834 + 0x2bb673) = 0;
    *(undefined1 *)(param_1 + iVar2 * 0x160d + 0xaed9d) = 0;
  }
  else {
    if (iVar1 != 0) {
      if (DebugLevel < 0) {
        return 0;
      }
      printk("Set_AccessPolicy_Proc::Invalid argument (=%s)\n",param_2);
      return 0;
    }
    iVar1 = *(int *)(iVar3 + 0x3c);
    *(undefined1 *)((int)param_1 + iVar1 * 0x5834 + 0x2bb671) = 0;
    *(undefined1 *)((int)param_1 + iVar1 * 0x5834 + 0x2bb672) = 0;
    *(undefined1 *)((int)param_1 + iVar1 * 0x5834 + 0x2bb673) = 0;
    *(undefined1 *)(param_1 + iVar1 * 0x160d + 0xaed9d) = 0;
  }
  ApUpdateAccessControlList(param_1,*(undefined1 *)(iVar3 + 0x3c));
  if (DebugLevel < 3) {
    return 1;
  }
  printk("IF(ra%d) Set_AccessPolicy_Proc::(AccessPolicy=%d)\n",*(int *)(iVar3 + 0x3c),
         *(undefined4 *)((int)param_1 + *(int *)(iVar3 + 0x3c) * 0x5834 + 0x2bb671));
  return 1;
}

