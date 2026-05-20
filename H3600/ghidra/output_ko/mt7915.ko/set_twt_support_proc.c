// module: mt7915.ko
// function: set_twt_support_proc @ 0xdeb90
// size: 176 bytes
//

undefined4 set_twt_support_proc(int *param_1,undefined4 param_2)

{
  byte bVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 uVar6;
  
  iVar5 = *param_1;
  iVar2 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(iVar5 + 0x3c),*(undefined4 *)(iVar5 + 0x38));
  bVar1 = os_str_tol(param_2,0,10);
  if (iVar2 != 0) {
    if (bVar1 < 3) {
      wlan_config_set_he_twt_support(iVar2);
    }
    if (2 < DebugLevel) {
      uVar6 = *(undefined4 *)(iVar5 + 0x3c);
      uVar4 = *(undefined4 *)(iVar5 + 0x38);
      uVar3 = wlan_config_get_he_twt_support(iVar2);
      printk("%s(), if=%d, if_type=%d, twt_support on wf_cfg_twt=%d\n","set_twt_support_proc",uVar6,
             uVar4,uVar3);
    }
    return 1;
  }
  return 0;
}

