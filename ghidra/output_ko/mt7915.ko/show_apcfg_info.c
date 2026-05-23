// module: mt7915.ko
// function: show_apcfg_info @ 0x2822c
// size: 2844 bytes
//

undefined4 show_apcfg_info(int *param_1)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int *piVar5;
  int iVar6;
  
  if (0 < DebugLevel) {
    printk("show ap cfg info:\n");
  }
  if (*param_1 == 0) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("pObj is NULL\n");
    return 0;
  }
  iVar6 = *(int *)(*param_1 + 0x3c);
  piVar5 = param_1 + iVar6 * 0x160d + 0xadc92;
  if (piVar5 == (int *)0x0) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("wdev is NULL\n");
    return 0;
  }
  if (0 < DebugLevel) {
    printk("%-24s%-16s%-8s\n",&_LC55,"WIFI_DRIVER","PEAK_VALUE");
  }
  uVar1 = *(ushort *)(param_1 + (int)(WtcGetWcidLinkType + iVar6 * 0x160d));
  iVar2 = wmode_2_cfgmode(uVar1);
  if ((iVar2 == 9) || (iVar2 == 0xe)) {
    if (0 < DebugLevel) {
      printk("%-24s%-16ld%ld\n","WirelessMode",iVar2,iVar2);
      goto LAB_00028590;
    }
  }
  else if (0 < DebugLevel) {
    printk("%-24s%-16ld%ld/%ld\n","WirelessMode",iVar2,9,0xe);
LAB_00028590:
    if (0 < DebugLevel) {
      printk("%-24s%-16lu%lu\n","TxPower",0,100);
      if (0 < DebugLevel) {
        printk("%-24s%-16lu%lu\n","TxPreamble",param_1[0x1e5419],1);
      }
    }
  }
  uVar3 = wlan_config_get_rts_len_thld(piVar5);
  uVar4 = wlan_operate_get_rts_len_thld(piVar5);
  if ((0 < DebugLevel) &&
     (printk("%-24s%-16d%d\n","RTSThreshold(config)",uVar3,0x92b), 0 < DebugLevel)) {
    printk("%-24s%-16d%d\n","RTSThreshold(operate)",uVar4,0x92b);
  }
  uVar3 = wlan_config_get_frag_thld(piVar5);
  uVar4 = wlan_operate_get_frag_thld(piVar5);
  if ((0 < DebugLevel) &&
     (printk("%-24s%-16d%d\n","FragThreshold(config)",uVar3,0x92a), 0 < DebugLevel)) {
    printk("%-24s%-16d%d\n","FragThreshold(operate)",uVar4,0x92a);
    if (0 < DebugLevel) {
      printk("%-24s%-16d%d\n","TxBurst",*(undefined1 *)((int)param_1 + 0x795071),1);
      if (0 < DebugLevel) {
        printk("%-24s%-16d%d\n","ShortSlot",(char)param_1[0x1e541c],1);
      }
    }
  }
  uVar3 = wlan_config_get_ht_bw(piVar5);
  uVar4 = wlan_operate_get_ht_bw(piVar5);
  if ((0 < DebugLevel) && (printk("%-24s%-16d%d\n","HT_BW(config)",uVar3,1), 0 < DebugLevel)) {
    printk("%-24s%-16d%d\n","HT_BW(operate)",uVar4,1);
    if (0 < DebugLevel) {
      printk("%-24s%-16d%d\n","HT_BSSCoexistence",*(undefined1 *)((int)param_1 + 0x79564e),0);
    }
  }
  uVar3 = wlan_config_get_tx_stream(piVar5);
  if (0 < DebugLevel) {
    if (*(char *)((int)param_1 + 0x79504d) == '\0') {
      uVar4 = 4;
    }
    else {
      uVar4 = 2;
    }
    printk("%-24s%-16d%d\n","HT_TxStream",uVar3,uVar4);
  }
  uVar3 = wlan_config_get_rx_stream(piVar5);
  if (0 < DebugLevel) {
    if (*(char *)((int)param_1 + 0x79504d) == '\0') {
      uVar4 = 4;
    }
    else {
      uVar4 = 2;
    }
    printk("%-24s%-16d%d\n","HT_RxStream",uVar3,uVar4);
  }
  uVar3 = wlan_config_get_ba_decline(piVar5);
  if (0 < DebugLevel) {
    printk("%-24s%-16d%d\n","HT_BADecline",uVar3,0);
  }
  uVar3 = wlan_config_get_ba_enable(piVar5);
  if (0 < DebugLevel) {
    printk("%-24s%-16d%d\n","HT_AutoBA",uVar3,1);
    if (0 < DebugLevel) {
      printk("%-24s%-16d%d\n","HT_AMSDU",((uint)*(byte *)((int)param_1 + 0x795047) << 0x1d) >> 0x1f,
             1);
    }
  }
  uVar3 = wlan_config_get_ba_rx_wsize(piVar5);
  if (0 < DebugLevel) {
    printk("%-24s%-16d%d\n","HT_BAWinSize",uVar3,0x40);
    if (0 < DebugLevel) {
      printk("%-24s%-16d%d\n","HT_GI",((uint)*(byte *)((int)param_1 + 0x794ccd) << 0x1b) >> 0x1f,1);
    }
  }
  uVar3 = wlan_config_get_ht_stbc(piVar5);
  if (0 < DebugLevel) {
    printk("%-24s%-16d%d\n","HT_STBC",uVar3,1);
  }
  uVar3 = wlan_config_get_ht_ldpc(piVar5);
  if (0 < DebugLevel) {
    printk("%-24s%-16d%d\n","HT_LDPC",uVar3,1);
    if (0 < DebugLevel) {
      printk("%-24s%-16d%d\n","HT_RDG",*(undefined1 *)((int)param_1 + 0x79507d),0);
      if (0 < DebugLevel) {
        printk("%-24s%-16d%d\n","HT_DisallowTKIP",(char)param_1[0x1e5661],1);
      }
    }
  }
  if ((uVar1 & 0xb1) == 0) {
LAB_00028448:
    if ((uVar1 & 0x4e) != 0) {
      if (DebugLevel < 1) goto LAB_00028464;
      printk("%-24s%-16d%d\n","G_BAND_256QAM",*(undefined1 *)((int)param_1 + 0x79505f),1);
    }
    if (0 < DebugLevel) {
      printk("%-24s%-16d%d\n","IEEE80211H",(char)param_1[0x1e541d],1);
    }
  }
  else {
    uVar3 = wlan_config_get_vht_bw(piVar5);
    uVar4 = wlan_operate_get_vht_bw(piVar5);
    if ((0 < DebugLevel) && (printk("%-24s%-16d%d\n","VHT_BW(config)",uVar3,1), 0 < DebugLevel)) {
      printk("%-24s%-16d%d\n","VHT_BW(operate)",uVar4,1);
    }
    uVar3 = wlan_config_get_vht_sgi(piVar5);
    if (0 < DebugLevel) {
      printk("%-24s%-16d%d\n","VHT_SGI",uVar3,1);
    }
    uVar3 = wlan_config_get_vht_stbc(piVar5);
    if (0 < DebugLevel) {
      printk("%-24s%-16d%d\n","VHT_STBC",uVar3,1);
    }
    uVar3 = wlan_config_get_vht_bw_sig(piVar5);
    if (0 < DebugLevel) {
      printk("%-24s%-16d%d\n","VHT_BW_SIGNAL",uVar3,0);
    }
    uVar3 = wlan_config_get_vht_ldpc(piVar5);
    if (0 < DebugLevel) {
      printk("%-24s%-16d%d\n","VHT_LDPC",uVar3,1);
      goto LAB_00028448;
    }
  }
LAB_00028464:
  if ((uVar1 & 0xb1) != 0) {
    if (DebugLevel < 1) goto LAB_0002847c;
    printk("%-24s%-16d%d\n","DfsEnable",*(undefined1 *)((int)param_1 + 0x7953ef),0);
  }
  if ((*(char *)((int)param_1 + 0x79504d) == '\0') && (0 < DebugLevel)) {
    printk("%-24s%-16d%d\n","DfsZeroWait",*(undefined1 *)((int)param_1 + 0xa79631));
  }
LAB_0002847c:
  uVar3 = wlan_config_get_mu_dl_ofdma(piVar5);
  if (0 < DebugLevel) {
    printk("%-24s%-16d%d\n","MuOfdmaDlEnable",uVar3,0);
  }
  uVar3 = wlan_config_get_mu_ul_ofdma(piVar5);
  if (0 < DebugLevel) {
    printk("%-24s%-16d%d\n","MuOfdmaUlEnable",uVar3,0);
  }
  uVar3 = wlan_config_get_mu_dl_mimo(piVar5);
  if (0 < DebugLevel) {
    printk("%-24s%-16d%d\n","MuMimoDlEnable",uVar3,0);
  }
  uVar3 = wlan_config_get_mu_ul_mimo(piVar5);
  if (0 < DebugLevel) {
    printk("%-24s%-16d%d\n","MuMimoUlEnable",uVar3,0);
    if (0 < DebugLevel) {
      printk("%-24s%-16lu%lu\n","CommonCfg.ETxBfEnCond",param_1[0x1e5667],0);
    }
  }
  uVar3 = wlan_config_get_etxbf(piVar5);
  if (0 < DebugLevel) {
    printk("%-24s%-16lu%lu\n","ETxBfEnCond",uVar3,0);
    if (0 < DebugLevel) {
      printk("%-24s%-16d%d\n","CommonCfg.ITxBfEn",
             ((uint)*(byte *)((int)param_1 + 0x794ccd) << 0x1d) >> 0x1f,0);
    }
  }
  uVar3 = wlan_config_get_itxbf(piVar5);
  if (0 < DebugLevel) {
    printk("%-24s%-16d%d\n","ITxBfEn",uVar3,0);
    if ((0 < DebugLevel) &&
       (printk("%-24s%-16lu%lu\n","MUTxRxEnable",param_1[0x1e5668],0), 0 < DebugLevel)) {
      printk("-----------------------------------------------------\n");
      if (0 < DebugLevel) {
        printk("%-24s%-16u\n","current channel",
               *(undefined1 *)((int)param_1 + iVar6 * 0x5834 + 0x2b7262));
      }
    }
  }
  wlan_operate_get_ext_cha(piVar5);
  if (0 < DebugLevel) {
    printk("%-24s%-16s\n","extension channel");
  }
  return 1;
}

