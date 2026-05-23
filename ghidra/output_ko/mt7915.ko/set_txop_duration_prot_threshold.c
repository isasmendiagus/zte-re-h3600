// module: mt7915.ko
// function: set_txop_duration_prot_threshold @ 0xdaffc
// size: 276 bytes
//

undefined4 set_txop_duration_prot_threshold(int *param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  
  iVar1 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (param_2 == 0) {
    if (-1 < DebugLevel) {
      printk("Usage:\niwpriv raN set txop_rts_thld=[txop_duration_threshold]\n");
      return 0;
    }
  }
  else if (iVar1 != 0) {
    uVar2 = os_str_tol(param_2,0,10);
    if (uVar2 < 0x400) {
      uVar3 = *(undefined4 *)(iVar1 + 8);
      wlan_operate_set_he_txop_dur_rts_thld(iVar1,uVar2 & 0xffff);
      HW_SET_PROTECT(uVar3,iVar1,2,0,0);
      if (0 < DebugLevel) {
        printk("%s: set wdev%d txop_duration rts threshold=%d (0x%x)\n",
               "set_txop_duration_prot_threshold",*(undefined1 *)(iVar1 + 0xc),uVar2,uVar2);
        return 1;
      }
      return 1;
    }
    if (-1 < DebugLevel) {
      printk("%s: incorrect value:%d\n","set_txop_duration_prot_threshold",uVar2);
    }
  }
  return 0;
}

