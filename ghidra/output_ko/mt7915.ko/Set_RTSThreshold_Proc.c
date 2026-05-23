// module: mt7915.ko
// function: Set_RTSThreshold_Proc @ 0xd9d30
// size: 192 bytes
//

undefined4 Set_RTSThreshold_Proc(int *param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (param_2 == 0) {
    uVar2 = 0;
    if (-1 < DebugLevel) {
      printk("Usage:\niwpriv raN set RTSThreshold=[length]\n");
    }
  }
  else {
    uVar2 = 0;
    if (iVar1 != 0) {
      uVar2 = os_str_tol(param_2,0,10);
      wlan_operate_set_rts_len_thld(iVar1,uVar2);
      if (DebugLevel < 1) {
        uVar2 = 1;
      }
      else {
        printk("%s: set wdev%d rts length threshold=%d(0x%x)\n","Set_RTSThreshold_Proc",
               *(undefined1 *)(iVar1 + 0xc),uVar2,uVar2);
        uVar2 = 1;
      }
    }
  }
  return uVar2;
}

