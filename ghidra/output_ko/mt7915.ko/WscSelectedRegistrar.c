// module: mt7915.ko
// function: WscSelectedRegistrar @ 0x1ed360
// size: 1364 bytes
//

void WscSelectedRegistrar(int param_1,ushort *param_2,uint param_3,int param_4)

{
  undefined4 uVar1;
  ushort uVar2;
  void *__s1;
  undefined4 *puVar3;
  int iVar4;
  ushort uVar5;
  char cVar6;
  uint uVar7;
  int iVar8;
  char *pcVar9;
  ushort *puVar10;
  char local_39;
  ushort local_38;
  ushort local_36;
  ushort local_34;
  undefined2 local_32;
  void *local_30;
  undefined4 *local_2c [2];
  
  cVar6 = '\0';
  local_38 = 0;
  local_36 = 0;
  local_30 = (void *)0x0;
  local_39 = '\0';
  if (param_3 < 4) {
    if (DebugLevel < 3) {
      return;
    }
    printk("WscSelectedRegistrar --> Unknown IE\n");
    return;
  }
  hex_dump("WscSelectedRegistrar - Reginfo");
  if (param_3 != 4) {
    do {
      local_34 = *param_2;
      uVar7 = (param_2[1] & 0xff) << 8 | (uint)(param_2[1] >> 8);
      local_32 = (undefined2)uVar7;
      if (param_3 < uVar7 + 4) {
        if (2 < DebugLevel) {
          printk("unexpected WSC IE Length(%u)\n",uVar7);
        }
        break;
      }
      puVar10 = param_2 + 2;
      uVar5 = local_34 << 8 | local_34 >> 8;
      if (uVar5 == 0x1049) {
        if (uVar7 != 0 && "%-10d, %d, %d%%\n"[param_1 + param_4 * 0x5834 + 0xd] != '\0') {
          if ((local_30 == (void *)0x0) &&
             (os_alloc_mem(0,&local_30,uVar7), local_30 == (void *)0x0)) {
            if (DebugLevel < 3) {
              return;
            }
            printk("allocate pAuthorizedMACs memory fail!!\n");
            return;
          }
          __memzero(local_30,uVar7);
          WscParseV2SubItem(1,puVar10,uVar7,local_30,&local_39);
        }
      }
      else if (uVar5 < 0x104a) {
        if (uVar5 == 0x1012) {
          local_38 = *puVar10 << 8 | *puVar10 >> 8;
        }
        else {
          if (uVar5 != 0x1041) goto LAB_001ed500;
          cVar6 = (char)param_2[2];
        }
      }
      else if (uVar5 != 0x104a) {
        if (uVar5 == 0x1053) {
          local_36 = *puVar10 << 8 | *puVar10 >> 8;
        }
        else {
LAB_001ed500:
          if (2 < DebugLevel) {
            printk("WscSelectedRegistrar --> Unknown IE 0x%04x\n");
          }
        }
      }
      param_2 = (ushort *)((int)puVar10 + uVar7);
      param_3 = param_3 + (-4 - uVar7);
    } while (4 < param_3);
    uVar2 = local_36;
    uVar5 = local_38;
    if (cVar6 == '\x01') {
      iVar8 = param_1 + param_4 * 0x5834;
      pcVar9 = "4/home/ws/zx279128s/packages/function/wlan/mtk/drivers/MT7915_V7.0.1.0/mt_wifi_ap/../mt_wifi/embedded/fsm/ap_mgmt_cntl.c:%d assert pAdfailed\n"
               + iVar8 + 0x4f;
      pcVar9[0] = '\x01';
      pcVar9[1] = '\0';
      pcVar9[2] = '\0';
      pcVar9[3] = '\0';
      WscBuildBeaconIE(param_1,2,1,local_38,local_36,param_4,local_30,local_39,0);
      WscBuildProbeRespIE(param_1,3,2,1,uVar5,uVar2,
                          "%s(): FIXME!!!Unexpected frame send to MgmtRing, need to assign the length!\n"
                          [iVar8 + 0x30],local_30,local_39,0);
      hex_dump("WscSelectedRegistrar - AuthorizedMACs::",local_30,local_39);
      __s1 = local_30;
      if ((((local_39 != '\x06') || (iVar4 = memcmp(local_30,&BROADCAST_ADDR,6), iVar4 == 0)) ||
          (iVar4 = memcmp(__s1,&ZERO_MAC_ADDR,6), iVar4 == 0)) ||
         (0x12 < *(int *)(
                         "4/home/ws/zx279128s/packages/function/wlan/mtk/drivers/MT7915_V7.0.1.0/mt_wifi_ap/../mt_wifi/embedded/fsm/ap_mgmt_cntl.c:%d assert pAdfailed\n"
                         + iVar8 + 0x3b))) goto LAB_001ed5e8;
      local_2c[0] = (undefined4 *)0x0;
      memmove("%s(): FIXME!!!Unexpected frame send to MgmtRing, need to assign the length!\n" +
              iVar8 + 0x31,__s1,6);
      iVar4 = param_1 + param_4 * 0x5834 + 0xc;
      pcVar9 = "!!! Link UP, ignore this set::OID_802_11_BSSID_LIST_SCAN\n" + iVar4 + 4;
      _raw_spin_lock_bh(pcVar9);
      WscClearPeerList("!!! Link UP, ignore this set::OID_802_11_BSSID_LIST_SCAN\n" + iVar4 + 8);
      os_alloc_mem(param_1,local_2c,0x10);
      if (local_2c[0] == (undefined4 *)0x0) {
LAB_001ed88c:
        printk(&_LC279,0x1b47);
        dump_stack();
      }
      else {
        __memzero(local_2c[0],0x10);
        puVar3 = local_2c[0];
        memmove(local_2c[0] + 2,local_30,6);
        uVar1 = jiffies;
        *puVar3 = 0;
        puVar3[1] = uVar1;
        if (*(undefined4 **)
             ("!!! Link UP, ignore this set::OID_802_11_BSSID_LIST_SCAN\n" + iVar8 + 0x18) ==
            (undefined4 *)0x0) {
          *(undefined4 **)
           ("!!! Link UP, ignore this set::OID_802_11_BSSID_LIST_SCAN\n" + iVar8 + 0x14) = puVar3;
        }
        else {
          **(undefined4 **)
            ("!!! Link UP, ignore this set::OID_802_11_BSSID_LIST_SCAN\n" + iVar8 + 0x18) = puVar3;
        }
        iVar8 = DebugLevel;
        iVar4 = param_4 * 0x5834 + param_1;
        *(undefined4 **)
         ("!!! Link UP, ignore this set::OID_802_11_BSSID_LIST_SCAN\n" + iVar4 + 0x18) = puVar3;
        "!!! Link UP, ignore this set::OID_802_11_BSSID_LIST_SCAN\n"[iVar4 + 0x1c] =
             "!!! Link UP, ignore this set::OID_802_11_BSSID_LIST_SCAN\n"[iVar4 + 0x1c] + '\x01';
        if (2 < iVar8) {
          printk("WscSelectedRegistrar --> Add this MAC to WscPeerList\n");
        }
        if (local_2c[0] == (undefined4 *)0x0) goto LAB_001ed88c;
      }
      _raw_spin_unlock_bh(pcVar9);
      goto LAB_001ed5e8;
    }
  }
  iVar8 = param_4 * 0x5834 + param_1;
  pcVar9 = "4/home/ws/zx279128s/packages/function/wlan/mtk/drivers/MT7915_V7.0.1.0/mt_wifi_ap/../mt_wifi/embedded/fsm/ap_mgmt_cntl.c:%d assert pAdfailed\n"
           + iVar8 + 0x4f;
  pcVar9[0] = '\0';
  pcVar9[1] = '\0';
  pcVar9[2] = '\0';
  pcVar9[3] = '\0';
  WscBuildBeaconIE(param_1,2,0,0,0,param_4,0,0,0);
  WscBuildProbeRespIE(param_1,3,2,0,0,0,
                      "%s(): FIXME!!!Unexpected frame send to MgmtRing, need to assign the length!\n"
                      [iVar8 + 0x30],0,0,0);
LAB_001ed5e8:
  UpdateBeaconHandler(param_1,"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                              + param_1 + param_4 * 0x5834 + 0xe0,2);
  if (local_30 == (void *)0x0) {
    return;
  }
  os_free_mem();
  return;
}

