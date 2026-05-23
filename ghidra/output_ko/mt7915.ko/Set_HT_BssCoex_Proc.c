// module: mt7915.ko
// function: Set_HT_BssCoex_Proc @ 0xdf544
// size: 280 bytes
//

undefined4
Set_HT_BssCoex_Proc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  
  cVar1 = os_str_tol(param_2,0,10,param_4,param_4);
  iVar2 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (iVar2 == 0) {
    return 0;
  }
  iVar3 = HcGetBandByWdev();
  iVar4 = DebugLevel;
  if (iVar3 != 1) {
    cVar1 = cVar1 == '\x01';
    *(char *)((int)param_1 + 0x79564e) = cVar1;
    if (2 < iVar4) {
      printk("Set bBssCoexEnable=%d!\n");
      cVar1 = *(char *)((int)param_1 + 0x79564e);
    }
    if ((cVar1 == '\0') && (*(char *)((int)param_1 + 0x795949) != '\0')) {
      if (2 < DebugLevel) {
        printk("Set bBssCoexEnable:  Switch back 20/40.\n");
      }
      *(undefined1 *)((int)param_1 + 0x795949) = 0;
      iVar4 = HcIsRfSupport(param_1,1);
      if ((iVar4 != 0) && (iVar4 = wlan_config_get_ht_bw(iVar2), iVar4 == 1)) {
        uVar5 = wlan_config_get_ext_cha(iVar2);
        wlan_operate_set_ht_bw(iVar2,1,uVar5);
        return 1;
      }
    }
  }
  return 1;
}

