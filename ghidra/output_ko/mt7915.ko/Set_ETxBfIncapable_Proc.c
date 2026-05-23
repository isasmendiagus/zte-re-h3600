// module: mt7915.ko
// function: Set_ETxBfIncapable_Proc @ 0xe5518
// size: 124 bytes
//

undefined4
Set_ETxBfIncapable_Proc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = os_str_tol(param_2,0,10,param_4,param_4);
  iVar2 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (1 < uVar1 || iVar2 == 0) {
    return 0;
  }
  *(char *)((int)param_1 + 0x7959a5) = (char)uVar1;
  mt_WrapSetETxBFCap(param_1,iVar2,(int)param_1 + 0x79563d);
  return 1;
}

