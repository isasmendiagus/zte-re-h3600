// module: mt7915.ko
// function: get_wdev_by_ioctl_idx_and_iftype @ 0x139bf4
// size: 144 bytes
//

void get_wdev_by_ioctl_idx_and_iftype(undefined4 param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  
  if (param_3 != 0x200) {
    if (param_3 < 0x201) {
      if (param_3 == 0x100) goto LAB_00139c44;
    }
    else {
      if (param_3 == 0x400) {
        iVar1 = 0x30;
        goto LAB_00139c18;
      }
      if (param_3 == 0x800) goto LAB_00139c44;
    }
    if (2 < DebugLevel) {
      printk("%s: can not find ioctl_if_type(%d), if_idx(%d)\n","get_wdev_by_ioctl_idx_and_iftype",
             param_3,param_2);
      iVar1 = 0;
LAB_00139c18:
      get_wdev_by_idx(param_1,param_2 + iVar1);
      return;
    }
  }
LAB_00139c44:
  get_wdev_by_idx(param_1,param_2,param_3,param_4);
  return;
}

