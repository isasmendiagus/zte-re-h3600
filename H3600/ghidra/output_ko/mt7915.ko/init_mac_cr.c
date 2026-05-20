// module: mt7915.ko
// function: init_mac_cr @ 0x17d5a0
// size: 96 bytes
//

void init_mac_cr(int *param_1)

{
  int iVar1;
  
  get_wdev_by_ioctl_idx_and_iftype
            (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  iVar1 = wlan_config_get_vht_bw_sig();
  if (0 < DebugLevel) {
    printk("%s()-->\n","init_mac_cr");
  }
  if (iVar1 == 0) {
    return;
  }
  AsicSetRtsSignalTA(param_1,iVar1);
  return;
}

