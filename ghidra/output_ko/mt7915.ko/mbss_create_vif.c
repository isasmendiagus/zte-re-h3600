// module: mt7915.ko
// function: mbss_create_vif @ 0x51d84
// size: 1016 bytes
//

void mbss_create_vif(int param_1,uint *param_2,int param_3)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  char *pcVar9;
  int *piVar10;
  int iVar11;
  uint *puVar12;
  uint *puVar13;
  uint *puVar14;
  char local_8d;
  undefined4 local_8c;
  char local_88 [32];
  uint local_68 [8];
  char *local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined2 local_3c;
  undefined1 local_2a;
  
  cVar1 = (char)param_3;
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  iVar11 = 0;
  local_8c = 0;
  local_88[0] = '\0';
  local_88[1] = '\0';
  local_88[2] = '\0';
  local_88[3] = '\0';
  local_88[4] = '\0';
  local_88[5] = '\0';
  local_88[6] = '\0';
  local_88[7] = '\0';
  local_88[8] = '\0';
  local_88[9] = '\0';
  local_88[10] = '\0';
  local_88[0xb] = '\0';
  local_88[0xc] = '\0';
  local_88[0xd] = '\0';
  local_88[0xe] = '\0';
  local_88[0xf] = '\0';
  local_88[0x10] = '\0';
  local_88[0x11] = '\0';
  local_88[0x12] = '\0';
  local_88[0x13] = '\0';
  local_88[0x14] = '\0';
  local_88[0x15] = '\0';
  local_88[0x16] = '\0';
  local_88[0x17] = '\0';
  local_88[0x18] = '\0';
  local_88[0x19] = '\0';
  local_88[0x1a] = '\0';
  local_88[0x1b] = '\0';
  local_88[0x1c] = '\0';
  local_88[0x1d] = '\0';
  local_88[0x1e] = '\0';
  local_88[0x1f] = '\0';
  local_8d = cVar1;
  iVar3 = get_dev_name_prefix(param_1,0x200);
  if (iVar3 == 0) {
    if (-1 < DebugLevel) {
      printk("get_dev_name_prefix error!\n");
    }
  }
  else {
    snprintf(local_88,0x20,"%s");
    if (((&DAT_0036db48)[param_1] == '\x01') && (*(char *)(param_1 + 0x79504c) != '\0')) {
      local_68[0] = 0;
      local_68[1] = 0;
      if ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
          [param_1 + 0xda] == '\0') {
        iVar11 = 0;
      }
      else {
        iVar3 = 0;
        piVar10 = (int *)(
                         "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                         + param_1 + 0xe0);
        do {
          iVar3 = iVar3 + 1;
          if (*piVar10 != 0) {
            iVar4 = HcGetBandByWdev(piVar10);
            iVar11 = iVar11 + 1;
            local_68[iVar4] = local_68[iVar4] + 1;
          }
          piVar10 = piVar10 + 0x160d;
        } while (iVar3 < (int)(uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                          [param_1 + 0xda]);
      }
      if (((iVar11 <= param_3) &&
          ((int)local_68[0] <
           (int)(uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                            [param_1 + 0xdb])) && (local_8d = (char)local_68[0], 0 < DebugLevel)) {
        printk("%s, re-assign ifidx %d -> %d\n","mbss_create_vif",param_3,local_68[0] & 0xff);
      }
    }
    multi_profile_devname_req(param_1,local_88,&local_8d);
    iVar11 = RtmpOSNetDevCreate(0,&local_8c,0x200,local_8d,0x10,local_88,local_8d != '\0');
    if (iVar11 == 0) {
      if (-1 < DebugLevel) {
        printk("pDevNew == NULL!\n");
      }
      "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
      [param_1 + 0xda] = cVar1;
      return;
    }
    if (0 < DebugLevel) {
      printk("Register MBSSID IF %d (%s)\n",param_3,iVar11);
    }
    pcVar9 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
             + param_3 * 0x5834 + param_1 + 0xe0;
    iVar3 = wdev_init(param_1,pcVar9,1,iVar11,(int)cVar1,pcVar9,param_1);
    if (iVar3 == 0) {
      if (-1 < DebugLevel) {
        printk("Assign wdev idx for %s failed, free net device!\n",iVar11);
      }
    }
    else {
      iVar2 = wdev_ops_register(pcVar9,1,ap_wdev_ops,*(undefined1 *)(iVar2 + 0x75));
      if (iVar2 != 0) {
        RtmpOsSetNetDevPriv(iVar11,param_1);
        RtmpOsSetNetDevWdev(iVar11,pcVar9);
        puVar12 = param_2;
        puVar14 = local_68;
        do {
          puVar13 = puVar12 + 4;
          uVar6 = puVar12[1];
          uVar7 = puVar12[2];
          uVar8 = puVar12[3];
          *puVar14 = *puVar12;
          puVar14[1] = uVar6;
          puVar14[2] = uVar7;
          puVar14[3] = uVar8;
          puVar12 = puVar13;
          puVar14 = puVar14 + 4;
        } while (puVar13 != param_2 + 0x10);
        iVar2 = param_3 * 0x5834 + param_1;
        local_40 = *(undefined4 *)
                    (
                    "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                    + iVar2 + 0x101);
        local_44 = 0x200;
        local_2a = 1;
        local_3c = *(undefined2 *)
                    (
                    "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                    + iVar2 + 0x105);
        local_48 = pcVar9;
        iVar2 = RtmpOSNetDevAttach(*(undefined1 *)(param_1 + 0x286285),iVar11,local_68);
        if ((iVar2 != 0) && (0 < DebugLevel)) {
          printk("%s, create IF %d (%s) failed!!\n","mbss_create_vif",param_3,iVar11);
        }
        if (4 < param_3) {
          local_8d = local_8d + '\x05';
        }
        uVar5 = register_idm_fdb_node(local_8d,iVar11);
        *(undefined4 *)
         ("Set::OID_802_11_SET_PASSPHRASE, Failed (len less than 8 or greater than 64)!!\n" +
         param_3 * 0x5834 + param_1 + 0x24) = uVar5;
        setHwMirrorFlag(iVar11);
        return;
      }
      if (-1 < DebugLevel) {
        printk("register wdev_ops %s failed, free net device!\n",iVar11);
      }
    }
    RtmpOSNetDevFree(iVar11);
  }
  return;
}

