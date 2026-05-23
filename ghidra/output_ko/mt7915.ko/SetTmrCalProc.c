// module: mt7915.ko
// function: SetTmrCalProc @ 0xbb19c
// size: 152 bytes
//

undefined4 SetTmrCalProc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  
  iVar4 = *param_1;
  iVar4 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(iVar4 + 0x3c),*(undefined4 *)(iVar4 + 0x38),iVar4,
                     param_4);
  uVar1 = os_str_tol(param_2,0,10);
  uVar2 = HcGetRadioChannel(param_1);
  if (0 < DebugLevel) {
    printk("%s(): TMR Calibration, TmrType: %d\n","SetTmrCalProc",uVar1);
  }
  if (iVar4 != 0) {
    uVar3 = wlan_operate_get_bw(iVar4);
    AsicSetTmrCal(param_1,uVar1,uVar2,uVar3);
  }
  return 1;
}

