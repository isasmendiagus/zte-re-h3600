// module: mt7915.ko
// function: Set_HideSSID_Proc @ 0x2bc18
// size: 232 bytes
//

undefined4 Set_HideSSID_Proc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = *param_1;
  cVar1 = os_str_tol(param_2,0,10,param_4,param_4);
  if ((cVar1 != '\x01') && (cVar1 != '\0')) {
    return 0;
  }
  iVar2 = *(int *)(iVar3 + 0x3c);
  if (*(char *)((int)param_1 + iVar2 * 0x5834 + 0x2bb2d2) != cVar1) {
    *(char *)((int)param_1 + iVar2 * 0x5834 + 0x2bb2d2) = cVar1;
    iVar2 = *(int *)(iVar3 + 0x3c);
  }
  if (*(char *)((int)param_1 + iVar2 * 0x5834 + 0x2bb05d) != '\0') {
    WscOnOff(param_1,iVar2,*(undefined1 *)((int)param_1 + iVar2 * 0x5834 + 0x2bb2d2));
  }
  if (2 < DebugLevel) {
    printk("IF(ra%d) Set_HideSSID_Proc::(HideSSID=%d)\n",*(int *)(iVar3 + 0x3c),
           *(undefined1 *)((int)param_1 + *(int *)(iVar3 + 0x3c) * 0x5834 + 0x2bb2d2));
    return 1;
  }
  return 1;
}

