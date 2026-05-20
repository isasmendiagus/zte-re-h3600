// module: mt7915.ko
// function: ZTE_set_BSSBE_proc @ 0x159184
// size: 84 bytes
//

undefined4 ZTE_set_BSSBE_proc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = *param_1;
  iVar2 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(iVar2 + 0x3c),*(undefined4 *)(iVar2 + 0x38),iVar2,
                     param_4);
  if (iVar2 == 0) {
    printk("ZTE_set_BSSBE_proc para error %p\n");
  }
  else {
    uVar1 = wlan_config_get_ht_edca();
    FUN_00155cf8(param_1,param_2,uVar1,0);
  }
  return 1;
}

