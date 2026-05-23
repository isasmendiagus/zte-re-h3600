// module: mt7915.ko
// function: set_no_bcn @ 0xe9fd4
// size: 140 bytes
//

undefined4 set_no_bcn(int *param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar1 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  iVar2 = os_str_tol(param_2,0,10);
  if (iVar1 != 0) {
    if (iVar2 == 0) {
      uVar3 = 5;
    }
    else {
      uVar3 = 6;
    }
    UpdateBeaconHandler(param_1,iVar1,uVar3);
  }
  if (0 < DebugLevel) {
    printk("%s(): Set no beacon as:%d\n","set_no_bcn",iVar2 != 0);
  }
  return 1;
}

