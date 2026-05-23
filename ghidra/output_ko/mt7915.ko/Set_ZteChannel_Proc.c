// module: mt7915.ko
// function: Set_ZteChannel_Proc @ 0xd8964
// size: 120 bytes
//

undefined4
Set_ZteChannel_Proc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = *param_1;
  uVar1 = *(undefined1 *)(iVar4 + 0x3c);
  iVar3 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,uVar1,*(undefined4 *)(iVar4 + 0x38),param_4,param_4);
  uVar2 = os_str_tol(param_2,0,10);
  if (iVar3 == 0) {
    if (-1 < DebugLevel) {
      printk("%s: wdev == NULL! if_type %d, if_idx = %d\n","Set_ZteChannel_Proc",
             *(undefined4 *)(iVar4 + 0x38),uVar1);
    }
  }
  else {
    *(undefined1 *)(iVar3 + 0x1a) = uVar2;
  }
  return 0;
}

