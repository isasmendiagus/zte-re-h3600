// module: mt7915.ko
// function: sta_set_wireless_addbaresp_bufsize @ 0xcefcc
// size: 104 bytes
//

void sta_set_wireless_addbaresp_bufsize
               (int *param_1,undefined2 *param_2,undefined4 param_3,undefined4 param_4)

{
  undefined2 uVar1;
  int iVar2;
  
  iVar2 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  uVar1 = *param_2;
  if (0 < DebugLevel) {
    printk("func:%s,set addbaresp_bufsize tx/rx win_size = %d\n",
           "sta_set_wireless_addbaresp_bufsize",uVar1);
  }
  if (iVar2 == 0) {
    return;
  }
  wlan_config_set_ba_txrx_wsize(iVar2,uVar1,uVar1,param_4);
  return;
}

