// module: mt7915.ko
// function: sta_set_wireless_bandwidth @ 0xcf1d8
// size: 100 bytes
//

void sta_set_wireless_bandwidth(int *param_1,undefined1 *param_2)

{
  undefined1 uVar1;
  int iVar2;
  
  iVar2 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  uVar1 = *param_2;
  if (0 < DebugLevel) {
    printk("func:%s, arg:%s\n","sta_set_wireless_bandwidth",param_2);
  }
  if (iVar2 == 0) {
    return;
  }
  wlan_config_set_he_bw(iVar2,uVar1);
  return;
}

