// module: mt7915.ko
// function: Set_FragThreshold_Proc @ 0xd9df4
// size: 176 bytes
//

undefined4 Set_FragThreshold_Proc(int *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = *param_1;
  iVar2 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(iVar2 + 0x3c),*(undefined4 *)(iVar2 + 0x38),iVar2,
                     param_4);
  if (param_2 == 0 || iVar2 == 0) {
    return 0;
  }
  uVar1 = os_str_tol(param_2,0,10);
  if (uVar1 - 0x100 < 0x82b) {
    if ((uVar1 & 1) != 0) {
      uVar1 = uVar1 - 1;
    }
  }
  else {
    uVar1 = 0x92a;
  }
  wlan_operate_set_frag_thld(iVar2,uVar1);
  if (0 < DebugLevel) {
    printk("%s::set wdev%d FragThreshold=%d)\n","Set_FragThreshold_Proc",
           *(undefined1 *)(iVar2 + 0xc),uVar1);
    return 1;
  }
  return 1;
}

