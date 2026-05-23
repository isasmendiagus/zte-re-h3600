// module: mt7915.ko
// function: Set_HtProtect_Proc @ 0xde4f4
// size: 124 bytes
//

undefined4 Set_HtProtect_Proc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 uVar1;
  int iVar2;
  
  iVar2 = *param_1;
  iVar2 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(iVar2 + 0x3c),*(undefined4 *)(iVar2 + 0x38),iVar2,
                     param_4);
  if (iVar2 == 0) {
    return 0;
  }
  uVar1 = os_str_tol(param_2,0,10);
  wlan_config_set_ht_protect_en(iVar2,uVar1);
  if (DebugLevel < 3) {
    return 1;
  }
  printk("Set_HtProtect_Proc::(HtProtect=%d)\n",uVar1);
  return 1;
}

