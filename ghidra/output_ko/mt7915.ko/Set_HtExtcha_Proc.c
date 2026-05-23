// module: mt7915.ko
// function: Set_HtExtcha_Proc @ 0xde0d4
// size: 148 bytes
//

undefined4 Set_HtExtcha_Proc(int *param_1,undefined4 param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  
  iVar1 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if ((iVar1 != 0) && (uVar2 = os_str_tol(param_2,0,10), uVar2 < 2)) {
    set_extcha_for_wdev(param_1,iVar1,uVar2 & 0xff);
    uVar3 = wlan_config_get_ext_cha(iVar1);
    if (DebugLevel < 3) {
      return 1;
    }
    printk("Set_HtExtcha_Proc::(HtExtcha=%d)\n",uVar3);
    return 1;
  }
  return 0;
}

