// module: mt7915.ko
// function: rx_eapol_frm_handle @ 0xca420
// size: 1176 bytes
//

void rx_eapol_frm_handle(int param_1,int *param_2,int param_3,uint param_4)

{
  byte bVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  void *__src;
  uint uVar5;
  char *pcVar6;
  size_t __n;
  void *pvVar7;
  undefined1 local_2e;
  undefined1 local_2d;
  undefined1 local_2c;
  undefined1 local_2b;
  undefined1 local_2a;
  undefined1 local_29;
  
  if (((param_2 != (int *)0x0) && (*(int *)(param_2[2] + 0x14) == 2)) &&
     (iVar3 = GetStaCfgByWdev(), iVar3 == 0)) {
    printk(&_LC85,0x1180);
    dump_stack();
  }
  if (0x67 < param_4) goto LAB_000ca490;
  pcVar6 = *(char **)(param_1 + param_4 * 4 + 0xc);
  if (*(ushort *)(param_3 + 0x40) < 0xc) {
    if (-1 < DebugLevel) {
      printk("pkts size too small\n");
    }
    wlan_dbg_set_last_error(0,1,0x118b,"rx_eapol_frm_handle");
    goto LAB_000ca490;
  }
  pvVar7 = *(void **)(param_3 + 0x3c);
  iVar3 = memcmp(&SNAP_802_1H,pvVar7,6);
  if (iVar3 != 0) {
    if (-1 < DebugLevel) {
      printk("no SNAP_802_1H parameter\n");
    }
    wlan_dbg_set_last_error(0,1,0x118f,"rx_eapol_frm_handle");
    goto LAB_000ca490;
  }
  iVar3 = memcmp(&EAPOL,(void *)((int)pvVar7 + 6),2);
  if (iVar3 != 0) {
    if (-1 < DebugLevel) {
      printk("no EAPOL parameter\n");
    }
    wlan_dbg_set_last_error(0,1,0x1193,"rx_eapol_frm_handle");
    goto LAB_000ca490;
  }
  if (4 < *(byte *)((int)pvVar7 + 9)) {
    if (-1 < DebugLevel) {
      printk("Unknown EAP type(%d)\n");
    }
    wlan_dbg_set_last_error(0,1,0x1197,"rx_eapol_frm_handle");
    goto LAB_000ca490;
  }
  if ((*(uint *)(param_3 + 0x44) & 0x800) == 0) {
    __n = 0x18;
  }
  else {
    __n = 0x1e;
  }
  if (param_2 == (int *)0x0) {
    __src = *(void **)(param_3 + 0x1c);
    pvVar7 = (void *)((int)pvVar7 - __n);
    bVar2 = false;
  }
  else if (*param_2 == 0x20001) {
    if (*(byte *)(param_2 + 0x145) < 6) {
      uVar5 = param_2[0x5f];
      if ((uVar5 & 8) == 0) {
        if ((uVar5 & 0x40) != 0) {
          iVar3 = is_pmkid_cache_in_sec_config(param_2 + 0x5f);
          if (iVar3 == 0) goto LAB_000ca6ec;
          uVar5 = param_2[0x5f];
        }
        if ((((uVar5 & 0x10000) == 0) ||
            (iVar3 = is_pmkid_cache_in_sec_config(param_2 + 0x5f), iVar3 != 0)) &&
           ((char)param_2[0x1c4] != '\x01')) goto LAB_000ca6a4;
      }
LAB_000ca6ec:
      if ((*(int *)(
                   "4/home/ws/zx279128s/packages/function/wlan/mtk/drivers/MT7915_V7.0.1.0/mt_wifi_ap/../mt_wifi/embedded/fsm/ap_mgmt_cntl.c:%d assert pAdfailed\n"
                   + param_1 + (uint)*(byte *)(param_2 + 0x39) * 0x5834 + 0x2b) == 0) ||
         (iVar3 = memcmp("%s(): FIXME!!!Unexpected frame send to MgmtRing, need to assign the length!\n"
                         + param_1 + (uint)*(byte *)(param_2 + 0x39) * 0x5834 + 0x31,&ZERO_MAC_ADDR,
                         6), iVar3 == 0)) goto LAB_000ca630;
      bVar2 = true;
      __src = (void *)(*(int *)(param_3 + 0x3c) - __n);
      *(void **)(param_3 + 0x1c) = __src;
      pvVar7 = __src;
    }
    else {
LAB_000ca6a4:
      if (*(int *)(pcVar6 + 0x14) == 1 || *(int *)(pcVar6 + 0x14) == 0x20) {
        bVar1 = pcVar6[0xe];
        uVar5 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
        if ((uVar5 <= bVar1) || (uVar5 = (uint)(byte)pcVar6[0xe], 0x1f < uVar5)) {
          printk(&_LC90,0x1279);
          dump_stack();
          uVar5 = (uint)(byte)pcVar6[0xe];
        }
        uVar4 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
        if (((uVar5 < uVar4) && ((byte)pcVar6[0xe] < 0x20)) &&
           (pcVar6 != "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                      + (uint)(byte)pcVar6[0xe] * 0x5834 + param_1 + 0xe0)) {
          printk(&_LC91,0x127c);
          dump_stack();
        }
        if ((*(int *)(pcVar6 + 0x14) == 1 || *(int *)(pcVar6 + 0x14) == 0x20) &&
           (iVar3 = memcmp(*(void **)(param_3 + 0x30),
                           "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                           + (uint)(byte)pcVar6[0xe] * 0x5834 + param_1 + 0x101,6), iVar3 != 0)) {
          bVar2 = true;
          __src = *(void **)(param_3 + 0x1c);
          pvVar7 = (void *)(*(int *)(param_3 + 0x3c) - __n);
        }
        else {
          bVar2 = false;
          __src = *(void **)(param_3 + 0x1c);
          pvVar7 = (void *)(*(int *)(param_3 + 0x3c) - __n);
        }
      }
      else {
        bVar2 = false;
        __src = *(void **)(param_3 + 0x1c);
        pvVar7 = (void *)(*(int *)(param_3 + 0x3c) - __n);
      }
    }
  }
  else {
    __src = *(void **)(param_3 + 0x1c);
    bVar2 = false;
    pvVar7 = (void *)((int)pvVar7 - __n);
  }
  pvVar7 = memmove(pvVar7,__src,__n);
  local_2e = *(undefined1 *)(param_3 + 0x58);
  local_2d = *(undefined1 *)(param_3 + 0x59);
  local_2a = 0;
  local_2c = *(undefined1 *)(param_3 + 0x5a);
  local_2b = *(undefined1 *)(param_3 + 0x5b);
  local_29 = (undefined1)*(undefined2 *)(param_3 + 0x80);
  MlmeEnqueueForRecv(param_1,*(undefined2 *)(param_3 + 0x4e),&local_2e,
                     *(ushort *)(param_3 + 0x40) + __n,pvVar7,*(undefined1 *)(param_3 + 0x4b),pcVar6
                     ,*(byte *)(param_3 + 99) >> 5);
  if (2 < DebugLevel) {
    printk("!!! report EAPOL DATA to MLME (len=%d) !!!\n",*(undefined2 *)(param_3 + 0x40));
  }
  if (!bVar2) {
LAB_000ca490:
    RTMPFreeNdisPacket(param_1,*(undefined4 *)(param_3 + 0x38));
    return;
  }
LAB_000ca630:
  indicate_802_11_pkt(param_1,param_3,param_4);
  return;
}

