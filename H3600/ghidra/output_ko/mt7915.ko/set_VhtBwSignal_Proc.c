// module: mt7915.ko
// function: set_VhtBwSignal_Proc @ 0xdf90c
// size: 440 bytes
//

undefined4 set_VhtBwSignal_Proc(int *param_1,undefined4 param_2)

{
  int iVar1;
  uint uVar2;
  char *local_24 [4];
  
  local_24[0] = "NONE";
  local_24[1] = "STATIC";
  local_24[2] = "DYNAMIC";
  iVar1 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  uVar2 = os_str_tol(param_2,0,10);
  if (uVar2 < 3) {
    if (iVar1 == 0) {
      return 0;
    }
    wlan_config_set_vht_bw_sig(iVar1,uVar2 & 0xff);
    AsicSetRtsSignalTA(param_1,uVar2 & 0xff);
    if (uVar2 != 0) {
      mac_io_read32(param_1[0x29e5e8],0x820f4000);
      mac_io_write32(param_1[0x29e5e8],0x820f4000);
      if (uVar2 == 2 && (param_1[0xa5b19] & 0xffffU) == 0x7615) {
        mac_io_write32(param_1[0x29e5e8],0x820f2040,0x2020202);
      }
      goto LAB_000df9c4;
    }
  }
  else {
    if (iVar1 == 0) {
      return 0;
    }
    wlan_config_set_vht_bw_sig(iVar1,0);
    AsicSetRtsSignalTA(param_1,0);
  }
  uVar2 = 0;
  mac_io_read32(param_1[0x29e5e8],0x820f4000);
  mac_io_write32(param_1[0x29e5e8],0x820f4000);
LAB_000df9c4:
  wlan_operate_set_rts_len_thld(iVar1,500);
  if (2 < DebugLevel) {
    printk("vht_bw_signal = %s\n",local_24[uVar2]);
  }
  return 1;
}

