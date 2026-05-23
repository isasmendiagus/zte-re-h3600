// module: mt7915.ko
// function: Show_HtBaWinSize_Proc @ 0xd6414
// size: 96 bytes
//

undefined4 Show_HtBaWinSize_Proc(int *param_1,char *param_2,size_t param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  iVar1 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (iVar1 != 0) {
    uVar2 = wlan_config_get_ba_tx_wsize();
    uVar3 = wlan_config_get_ba_rx_wsize(iVar1);
    snprintf(param_2,param_3,"\t%u %u",uVar2,uVar3);
  }
  return 0;
}

