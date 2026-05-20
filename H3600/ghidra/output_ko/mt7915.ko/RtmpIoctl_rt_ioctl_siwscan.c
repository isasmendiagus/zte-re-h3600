// module: mt7915.ko
// function: RtmpIoctl_rt_ioctl_siwscan @ 0x62454
// size: 312 bytes
//

undefined4
RtmpIoctl_rt_ioctl_siwscan(int *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = *(int *)(*param_1 + 0x3c);
  *(undefined4 *)(param_2 + 0x10) = 0;
  if ((char)param_1[0xa6e43] != '\x01') {
    *(undefined1 *)((int)param_1 + iVar1 * 0x2137b0 + 0x580ccd) = 1;
    if ((((param_1[iVar1 * 0x84dec + 0x15ffef] & 0x80U) == 0) ||
        ((param_1[iVar1 * 0x84dec + 0xdb6e1] & 0x12cf8U) == 0)) ||
       ((char)param_1[iVar1 * 0x84dec + 0xdb8f8] != '\x02')) {
      StaSiteSurvey(param_1,0,*(undefined1 *)(param_2 + 0xc),param_1 + iVar1 * 0x84dec + 0xdb6d6,
                    param_4);
    }
    else if (2 < DebugLevel) {
      printk("!!! Link UP, Port Not Secured! ignore this set::OID_802_11_BSSID_LIST_SCAN\n");
    }
    *(undefined4 *)(param_2 + 0x10) = 0;
    return 0;
  }
  if (2 < DebugLevel) {
    printk("!!! Driver is in Monitor Mode now !!!\n");
  }
  *(undefined4 *)(param_2 + 0x10) = 30000;
  return 1;
}

