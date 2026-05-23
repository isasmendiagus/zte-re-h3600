// module: mt7915.ko
// function: RtmpIoctl_rt_ioctl_siwrts @ 0x62b68
// size: 48 bytes
//

undefined4 RtmpIoctl_rt_ioctl_siwrts(int *param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (iVar1 != 0) {
    wlan_operate_set_rts_len_thld(iVar1,param_3);
  }
  return 0;
}

