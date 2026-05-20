// module: mt7915.ko
// function: wlan_show_ap_bss_wmminfo @ 0x158d58
// size: 428 bytes
//

undefined4 wlan_show_ap_bss_wmminfo(int *param_1)

{
  int iVar1;
  undefined1 *puVar2;
  int iVar3;
  undefined4 uVar4;
  
  iVar1 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  if (iVar1 != 0) {
    puVar2 = (undefined1 *)HcGetEdca(param_1,iVar1);
    if (puVar2 != (undefined1 *)0x0) {
      printk("AP WMM Valid=%d\n",*puVar2);
      wlan_show_wmm_info(puVar2,0);
      wlan_show_wmm_info(puVar2,1);
      wlan_show_wmm_info(puVar2,2);
      wlan_show_wmm_info(puVar2,3);
    }
    iVar3 = wlan_config_get_ht_edca(iVar1);
    if (iVar3 != 0) {
      puVar2 = (undefined1 *)wlan_config_get_ht_edca(iVar1);
      printk("STA WMM Valid=%d\n",*puVar2);
    }
    uVar4 = wlan_config_get_ht_edca(iVar1);
    wlan_show_wmm_info(uVar4,0);
    uVar4 = wlan_config_get_ht_edca(iVar1);
    wlan_show_wmm_info(uVar4,1);
    uVar4 = wlan_config_get_ht_edca(iVar1);
    wlan_show_wmm_info(uVar4,2);
    uVar4 = wlan_config_get_ht_edca(iVar1);
    wlan_show_wmm_info(uVar4,3);
    printk("AP Config WMM Valid=%d\n",(char)param_1[(uint)*(byte *)(iVar1 + 0x8d7) * 9 + 0x1e5421]);
    wlan_show_wmm_info(param_1 + (uint)*(byte *)(iVar1 + 0x8d7) * 9 + 0x1e5421,0);
    wlan_show_wmm_info(param_1 + (uint)*(byte *)(iVar1 + 0x8d7) * 9 + 0x1e5421,1);
    wlan_show_wmm_info(param_1 + (uint)*(byte *)(iVar1 + 0x8d7) * 9 + 0x1e5421,2);
    wlan_show_wmm_info(param_1 + (uint)*(byte *)(iVar1 + 0x8d7) * 9 + 0x1e5421,3);
    return 1;
  }
  printk("wlan_show_ap_bss_wmminfo para error %p\n",0);
  return 0;
}

