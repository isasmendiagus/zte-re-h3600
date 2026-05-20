// module: mt7915.ko
// function: net_ad_update_wdev @ 0x25b63c
// size: 840 bytes
//

undefined4 net_ad_update_wdev(int param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  byte bVar3;
  char cVar4;
  undefined2 uVar5;
  int iVar6;
  int iVar7;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_2 + 4));
  if (iVar1 == 0) {
    return 0x606;
  }
  iVar6 = *(int *)(param_3 + 0x28);
  if (iVar6 == 0) goto LAB_0025b698;
  printk("%s: wdev_idx(txd)=%d, ch=%d\n","net_ad_update_wdev",*(undefined1 *)(iVar6 + 0xc),
         *(undefined1 *)(iVar6 + 0x1a),param_4);
  HcReleaseRadioForWdev(iVar1,iVar6);
  iVar7 = *(int *)(param_3 + 0x24);
  if (iVar7 == 0) goto LAB_0025b698;
  printk("%s: wdev_idx=%d, ch=%d\n","net_ad_update_wdev",*(undefined1 *)(iVar7 + 0xc),
         *(undefined1 *)(iVar7 + 0x1a),param_4);
  HcReleaseRadioForWdev(iVar1,iVar7);
  if (((*(uint *)("Get_RBIST_IQ_Data_Proc" + iVar1 + 0xc) & 0xffff) == 0x7915) &&
     (*(char *)(param_2 + 0x34) != '\0')) {
    bVar3 = (byte)*(undefined2 *)(param_3 + 0xc4e) & 3;
    if (param_1 == 0) {
      "SetPartProfileParameters"[iVar1 + 0x1b] = bVar3;
    }
    else {
      "rtmp_read_vow_parms_from_file"[iVar1 + 1] = bVar3;
    }
  }
  else {
    bVar3 = (byte)((*(uint *)(param_3 + 0xc48) & 0xf) << 4);
    "SetPartProfileParameters"[iVar1 + 0x18] =
         "SetPartProfileParameters"[iVar1 + 0x18] & 0xfU | bVar3;
    "SetPartProfileParameters"[iVar1 + 0x18] = bVar3 | (byte)*(undefined2 *)(param_3 + 0xc4e) & 0xf;
  }
  cVar4 = *(char *)(param_3 + 0xc51);
  printk("%s: ch_band=%d\n","net_ad_update_wdev",cVar4);
  if (cVar4 == '\0') {
    *(undefined2 *)(iVar7 + 0x18) = 0x4e;
    *(undefined2 *)(iVar6 + 0x18) = 0x4e;
  }
  else {
    if (cVar4 == '\x01') {
      uVar5 = 0xb1;
    }
    else {
      uVar5 = 0x128;
    }
    *(undefined2 *)(iVar7 + 0x18) = uVar5;
    *(undefined2 *)(iVar6 + 0x18) = uVar5;
  }
  *(undefined1 *)(iVar7 + 0x1a) = *(undefined1 *)(param_3 + 0xc52);
  wlan_config_set_ch_band(iVar7,*(undefined2 *)(iVar7 + 0x18));
  wlan_config_set_tx_stream(iVar7,*(undefined1 *)(param_3 + 0xc48));
  wlan_config_set_rx_stream(iVar7,*(undefined1 *)(param_3 + 0xc4e));
  wlan_config_set_ht_bw(iVar7,*(char *)(param_3 + 0xc56) != '\0');
  wlan_config_set_ext_cha(iVar7,*(undefined1 *)(param_3 + 0xc54));
  wlan_config_set_cen_ch_2(iVar7,*(undefined1 *)(param_3 + 0xc63));
  bVar3 = *(byte *)(param_3 + 0xc56);
  if (bVar3 < 5) {
    if (bVar3 < 2) {
      cVar4 = '\0';
    }
    else {
      cVar4 = bVar3 - 1;
    }
    wlan_config_set_vht_bw(iVar7,cVar4);
  }
  else {
    wlan_config_set_vht_bw(iVar7,bVar3 - 3);
  }
  bVar3 = *(byte *)(param_3 + 0xc57);
  if (2 < bVar3) {
    bVar3 = 2;
  }
  wlan_config_set_ap_bw(iVar7,bVar3);
  wlan_config_set_ap_cen(iVar7,*(char *)(param_3 + 0xc50) - *(char *)(param_3 + 0xc54));
  iVar2 = wdev_attr_update(iVar1,iVar7);
  if (iVar2 == 1) {
    iVar2 = wdev_edca_acquire(iVar1,iVar7);
    if (iVar2 == 1) {
      *(undefined1 *)(iVar6 + 0x1a) = *(undefined1 *)(param_3 + 0xc52);
      wlan_config_set_ch_band(iVar6,*(undefined2 *)(iVar6 + 0x18));
      wlan_config_set_tx_stream(iVar6,*(undefined1 *)(param_3 + 0xc48));
      wlan_config_set_rx_stream(iVar6,*(undefined1 *)(param_3 + 0xc4e));
      wlan_config_set_ht_bw(iVar6,*(char *)(param_3 + 0xc56) != '\0');
      wlan_config_set_ext_cha(iVar6,*(undefined1 *)(param_3 + 0xc54));
      wlan_config_set_cen_ch_2(iVar6,*(undefined1 *)(param_3 + 0xc63));
      bVar3 = *(byte *)(param_3 + 0xc56);
      if (bVar3 < 5) {
        if (bVar3 < 2) {
          cVar4 = '\0';
        }
        else {
          cVar4 = bVar3 - 1;
        }
        wlan_config_set_vht_bw(iVar6,cVar4);
      }
      else {
        wlan_config_set_vht_bw(iVar6,bVar3 - 3);
      }
      bVar3 = *(byte *)(param_3 + 0xc57);
      iVar2 = iVar6;
      if (2 < bVar3) {
        bVar3 = 2;
        iVar2 = iVar7;
      }
      wlan_config_set_ap_bw(iVar2,bVar3);
      wlan_config_set_ap_cen(iVar6,*(char *)(param_3 + 0xc50) - *(char *)(param_3 + 0xc54));
      iVar7 = wdev_attr_update(iVar1,iVar6);
      if (iVar7 != 1) goto LAB_0025b970;
      iVar1 = wdev_edca_acquire(iVar1,iVar6);
      if (iVar1 == 1) {
        return 0;
      }
    }
    printk("%s: error to acquire edca\n","net_ad_update_wdev");
  }
  else {
LAB_0025b970:
    printk("%s: error to update wdev\n","net_ad_update_wdev");
  }
LAB_0025b698:
  printk("%s: updats wdev failed!\n","net_ad_update_wdev");
  return 0x604;
}

