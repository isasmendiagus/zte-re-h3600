// module: mt7915.ko
// function: RtmpIoctl_rt_ioctl_giwrts @ 0x62b98
// size: 48 bytes
//

undefined4 RtmpIoctl_rt_ioctl_giwrts(int *param_1,undefined2 *param_2)

{
  undefined2 uVar1;
  int iVar2;
  
  iVar2 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (iVar2 != 0) {
    uVar1 = wlan_operate_get_rts_len_thld();
    *param_2 = uVar1;
  }
  return 0;
}

