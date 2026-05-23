// module: mt7915.ko
// function: RcReleaseBandForObj @ 0xac2c8
// size: 136 bytes
//

void RcReleaseBandForObj(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (param_2 == 0) {
    if (DebugLevel < 0) {
      return;
    }
    printk("%s():can\'t find obj\n","RcReleaseBandForObj",param_3,param_4);
    return;
  }
  iVar1 = *(int *)(param_2 + 8);
  ReleaseOmacIdx(param_1,*(undefined2 *)(param_2 + 2),iVar1,*(undefined1 *)(param_2 + 4));
  if (iVar1 == 0) {
    return;
  }
  if (*(char *)(param_2 + 6) == '\0') {
    HdevObjDel(iVar1,param_2);
    return;
  }
  wmm_ctrl_release_entry(param_2);
  HdevObjDel(iVar1,param_2);
  return;
}

