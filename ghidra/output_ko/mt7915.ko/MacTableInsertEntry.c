// module: mt7915.ko
// function: MacTableInsertEntry @ 0x14addc
// size: 4320 bytes
//

int MacTableInsertEntry(int param_1,byte *param_2,char *param_3,int param_4,char param_5,
                       undefined1 param_6)

{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  byte bVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  undefined1 uVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  void *__s1;
  bool bVar14;
  int local_19c;
  int local_178;
  uint local_15c;
  undefined4 local_158;
  undefined2 local_154;
  
  if (param_3 == (char *)0x0) {
    local_178 = 0;
  }
  else {
    local_178 = *(int *)(param_3 + 4);
    if ((local_178 != 0) && (*(int *)(param_3 + 0x14) != 2)) {
      if (*(int *)(param_3 + 0x14) == 0x100) {
        local_178 = *(int *)(*(int *)(local_178 + 0x4140) + 4);
      }
      else {
        local_178 = 0;
      }
    }
  }
  uVar1 = *(ushort *)(param_1 + 0x285920);
  uVar2 = HcGetMaxStaNum(param_1);
  if (uVar2 <= uVar1) {
    printk(&_LC53,0x367);
    dump_stack();
    return 0;
  }
  iVar12 = param_1 + 0x285958;
  hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  _raw_spin_lock_bh(iVar12);
  iVar3 = HcAcquireUcastWcid(param_1,param_3);
  if (iVar3 == 0xffff) {
    if (-1 < DebugLevel) {
      printk("%s(): Entry full!\n","MacTableInsertEntry");
    }
    goto LAB_0014b6f0;
  }
  if (2 < DebugLevel) {
    printk("%s(): wcid %d EntryType:%d =====\n","MacTableInsertEntry",iVar3,
           *(undefined4 *)(iVar3 * 0x14c0 + param_1 + 0xa1d20));
  }
  iVar11 = iVar3 * 0x14c0;
  iVar13 = param_1 + iVar11;
  if (*(int *)(iVar13 + 0xa1d20) != 0) {
    local_19c = 0;
    goto LAB_0014aedc;
  }
  local_19c = param_1 + iVar11 + 0xa1d20;
  FUN_00147e00(param_1,local_19c,param_6);
  *(undefined4 *)(iVar13 + 0xa31d4) = jiffies;
  *(char **)(iVar13 + 0xa1d28) = param_3;
  *(short *)(iVar13 + 0xa1e00) = (short)iVar3;
  iVar7 = param_1 + iVar11 + 0xa1e08;
  *(char *)(iVar13 + 0xa1e04) = param_3[0xe];
  *(char *)(iVar13 + 0xa1e05) = param_3[0xe];
  __s1 = (void *)(iVar7 + 4);
  *(undefined2 *)(iVar13 + 0xa29e8) = 0;
  *(undefined1 *)(iVar13 + 0xa1e07) = 0;
  *(int *)(iVar13 + 0xa1d2c) = param_1;
  *(undefined1 *)(iVar13 + 0xa27f8) = 0;
  *(undefined4 *)(iVar7 + 4) = *(undefined4 *)param_2;
  *(undefined2 *)(iVar7 + 8) = *(undefined2 *)(param_2 + 4);
  if (param_5 != '\x04') {
    iVar11 = iVar11 + 0xa2000;
    RTMPInitTimer(param_1,param_1 + iVar11 + 0x124,rtmp_timer_WPAStartFor4WayExec,local_19c,0);
    RTMPInitTimer(param_1,param_1 + iVar11 + 0x158,rtmp_timer_WPAStartFor2WayExec,local_19c,0);
    RTMPInitTimer(param_1,param_1 + iVar11 + 0x240,rtmp_timer_WPAHandshakeMsgRetryExec,local_19c,0);
    RTMPInitTimer(param_1,param_1 + iVar11 + 0x2e0,rtmp_timer_PMF_SAQueryTimeOut,local_19c,0);
    RTMPInitTimer(param_1,param_1 + iVar11 + 0x314,rtmp_timer_PMF_SAQueryConfirmTimeOut,local_19c,0)
    ;
  }
  iVar13 = param_1 + iVar3 * 0x14c0;
  *(undefined4 *)(iVar13 + 0xa3188) = 0;
  __init_waitqueue_head(iVar13 + 0xa318c,"&x->wait",&_LANCHOR1);
  *(undefined4 *)(iVar13 + 0xa1e1c) = 0;
  *(undefined4 *)(iVar13 + 0xa1e20) = 0;
  *(undefined4 *)(iVar13 + 0xa1e24) = 0;
  iVar11 = entrytb_aid_aquire(param_1 + 0x28594c);
  *(short *)(iVar13 + 0xa1e18) = (short)iVar11;
  if (iVar11 == 0x7d8) {
    if (-1 < DebugLevel) {
      printk("%s(): allocate AID fail!\n","MacTableInsertEntry");
    }
LAB_0014baf0:
    HcReleaseUcastWcid(param_1,param_3,*(undefined2 *)(iVar3 * 0x14c0 + param_1 + 0xa1e00));
    FUN_00147e00(param_1,local_19c,param_6);
LAB_0014b6f0:
    _raw_spin_unlock_bh(iVar12);
    return 0;
  }
  iVar11 = param_1 + iVar3 * 0x620;
  *(undefined2 *)(iVar13 + 0xa2816) = 0;
  *(undefined4 *)(iVar13 + 0xa2810) = 5;
  *(undefined1 *)(iVar13 + 0xa2818) = 0;
  *(undefined4 *)(iVar13 + 0xa2808) = 0;
  *(undefined4 *)(iVar13 + 0xa299c) = 0;
  *(undefined4 *)(iVar13 + 0xa29a0) = 0;
  *(undefined1 *)(iVar11 + 0x2f763) = 0;
  *(undefined1 *)(iVar11 + 0x2f72c) = 0;
  *(undefined4 *)(iVar13 + 0xa29ec) = 0xffffffff;
  *(undefined4 *)(iVar13 + 0xa29f0) = 0;
  *(undefined1 *)(iVar13 + 0xa2a33) = 0;
  *(undefined4 *)(iVar11 + 0x2f954) = 0;
  *(undefined4 *)(iVar11 + 0x2f94c) = 0;
  *(undefined1 *)(iVar11 + 0x2f765) = 0;
  *(undefined4 *)(iVar11 + 0x2f950) = 0;
  *(undefined1 *)(iVar11 + 0x2fa7c) = 0;
  *(undefined4 *)(iVar13 + 0xa2428) = 0;
  *(undefined4 *)(iVar13 + 0xa242c) = 0;
  *(undefined1 *)(iVar13 + 0xa3148) = 0;
  *(undefined4 *)(iVar13 + 0xa314c) = 0;
  *(undefined1 *)(iVar13 + 0xa3149) = 0;
  if (param_4 == 1) {
    *(undefined4 *)(iVar13 + 0xa1d20) = 2;
    iVar11 = iVar3 * 0x14c0 + 0xa2800;
    *(undefined4 *)(param_1 + iVar11) = *(undefined4 *)param_2;
    *(undefined2 *)(param_1 + iVar11 + 4) = *(undefined2 *)(param_2 + 4);
    *(undefined2 *)(local_178 + 0x2132e0) = *(undefined2 *)(iVar13 + 0xa1e00);
    *(undefined4 *)(iVar13 + 0xa3144) = 0x10002;
    *(int *)(local_178 + 0x21246c) = local_19c;
    if ((*(uint *)(iVar13 + 0xa1e9c) & 7) == 0) {
      *(undefined1 *)(iVar13 + 0xa2234) = 3;
      *(undefined4 *)(iVar13 + 0xa27fc) = 1;
    }
    else {
      *(undefined1 *)(iVar13 + 0xa2234) = 0;
      *(undefined4 *)(iVar13 + 0xa27fc) = 0;
    }
    if (param_1 != 0) {
      if (*(char *)(param_1 + 0xa7a2e8) == '\x01') {
        bVar6 = *(byte *)(iVar3 * 0x14c0 + param_1 + 0xa1e04);
        iVar11 = param_1 + (uint)bVar6;
        uVar10 = *(undefined1 *)(iVar11 + 0xa7bea8);
      }
      else {
        if (*(char *)(param_1 + 0xa7a2ea) != '\x01') goto LAB_0014b24c;
        bVar6 = *(byte *)(iVar3 * 0x14c0 + param_1 + 0xa1e04);
        iVar11 = param_1 + (uint)bVar6;
        uVar10 = *(undefined1 *)(iVar11 + 0xa7bea8);
        if (*(char *)(param_1 + 0xa7a2e8) == '\0') goto LAB_0014b828;
      }
      *(byte *)(iVar11 + 0xa7bea8) = ((char)*(undefined2 *)(param_1 + 0xa7bec8) + -1) - bVar6;
LAB_0014b828:
      RTMP_SET_STA_DWRR(param_1,local_19c);
      *(undefined1 *)(param_1 + (uint)*(byte *)(iVar3 * 0x14c0 + param_1 + 0xa1e04) + 0xa7bea8) =
           uVar10;
    }
  }
  else {
    if (param_4 == 2 || param_4 == 0x2001) {
      if (param_4 == 0x2001) {
        *(undefined4 *)(iVar13 + 0xa1d20) = 0x2001;
      }
      iVar11 = iVar3 * 0x14c0 + 0xa2800;
      *(undefined4 *)(param_1 + iVar11) = *(undefined4 *)param_2;
      *(undefined2 *)(param_1 + iVar11 + 4) = *(undefined2 *)(param_2 + 4);
      *(undefined4 *)(param_1 + iVar3 * 0x14c0 + 0xa27fc) = 0;
    }
    else if (param_4 == 0x40001) {
      if (param_3 == (char *)0x0) {
        iVar11 = 0;
      }
      else {
        iVar11 = *(int *)(param_3 + 4);
        if ((iVar11 != 0) && (*(int *)(param_3 + 0x14) != 2)) {
          if (*(int *)(param_3 + 0x14) == 0x100) {
            iVar11 = *(int *)(*(int *)(iVar11 + 0x4140) + 4);
          }
          else {
            iVar11 = 0;
          }
        }
      }
      uVar1 = *(ushort *)(iVar11 + 0x2132e0);
      iVar7 = param_1 + iVar3 * 0x14c0;
      iVar11 = iVar3 * 0x14c0 + 0xa2800;
      *(undefined4 *)(iVar7 + 0xa1d20) = 0x40001;
      iVar13 = (uint)uVar1 * 0x14c0 + param_1;
      *(undefined4 *)(param_1 + iVar11) = *(undefined4 *)param_2;
      *(undefined2 *)(param_1 + iVar11 + 4) = *(undefined2 *)(param_2 + 4);
      *(undefined4 *)(iVar7 + 0xa1e9c) = *(undefined4 *)(iVar13 + 0xa1e9c);
      *(undefined4 *)(iVar7 + 0xa1fe4) = *(undefined4 *)(iVar13 + 0xa1fe4);
      *(undefined4 *)(iVar7 + 0xa20c4) = *(undefined4 *)(iVar13 + 0xa20c4);
      *(undefined4 *)(iVar7 + 0xa281c) = 0;
      *(undefined4 *)(iVar7 + 0xa3144) = 0x10002;
      if ((*(uint *)(iVar7 + 0xa1e9c) & 7) == 0) {
        *(undefined1 *)(iVar7 + 0xa2234) = 3;
        *(undefined4 *)(iVar7 + 0xa27fc) = 1;
      }
      else {
        *(undefined1 *)(iVar7 + 0xa2234) = 0;
        *(undefined4 *)(iVar7 + 0xa27fc) = 0;
      }
      if (param_1 == 0) {
LAB_0014b538:
        if (2 < DebugLevel) {
          iVar11 = iVar3 * 0x14c0 + param_1;
          printk("Repeater Security wcid=%d, AKMMap=0x%x, PairwiseCipher=0x%x, GroupCipher=0x%x\n",
                 *(undefined2 *)(iVar11 + 0xa1e00),*(undefined4 *)(iVar11 + 0xa1e9c),
                 *(undefined4 *)(iVar11 + 0xa1fe4),*(undefined4 *)(iVar11 + 0xa20c4));
        }
        goto LAB_0014b24c;
      }
      if (*(char *)(param_1 + 0xa7a2e8) == '\x01') {
        iVar11 = param_1 + (uint)*(byte *)(iVar3 * 0x14c0 + param_1 + 0xa1e04);
        uVar10 = *(undefined1 *)(iVar11 + 0xa7bea8);
      }
      else {
        if (*(char *)(param_1 + 0xa7a2ea) != '\x01') goto LAB_0014b538;
        iVar11 = param_1 + (uint)*(byte *)(iVar3 * 0x14c0 + param_1 + 0xa1e04);
        uVar10 = *(undefined1 *)(iVar11 + 0xa7bea8);
        if (*(char *)(param_1 + 0xa7a2e8) == '\0') goto LAB_0014b828;
      }
      *(char *)(iVar11 + 0xa7bea8) =
           ((char)*(undefined2 *)(param_1 + 0xa7bec8) -
           *(char *)((uint)uVar1 * 0x14c0 + param_1 + 0xa1e04)) + -1;
      goto LAB_0014b828;
    }
    if (param_4 == 0x20001) {
      bVar6 = (&DAT_0036b916)[param_1];
      uVar2 = HcGetMaxStaNum(param_1);
      if (bVar6 < uVar2) {
        iVar11 = iVar3 * 0x14c0 + param_1;
        uVar2 = (uint)*(byte *)(iVar11 + 0xa1e04);
        if (uVar2 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                          [param_1 + 0xda]) {
          uVar4 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
          bVar14 = uVar2 < uVar4;
          uVar2 = (uint)*(byte *)(iVar11 + 0xa1e04);
          if ((bVar14) && (uVar2 < 0x20)) {
            iVar11 = uVar2 * 0x5834 + param_1;
            if (("pStaCfg->WpaPassPhrase"[iVar11 + 10] != 0) &&
               ((byte)"pStaCfg->WpaPassPhrase"[iVar11 + 10] <=
                (byte)"pStaCfg->WpaPassPhrase"[iVar11 + 0xb])) {
              if (1 < DebugLevel) {
                printk("%s: The connection table is full in ra%d.\n","MacTableInsertEntry",uVar2);
              }
              if ((*(uint *)(param_1 + 0xa7d168) & 4) != 0) {
                __memzero(&local_15c,0x134);
                local_158 = *(undefined4 *)param_2;
                local_154 = *(undefined2 *)(param_2 + 4);
                local_15c = (uint)*(byte *)(iVar3 * 0x14c0 + param_1 + 0xa1e05);
                Kernel_ASEND("cspd.wlan_manage.wlan_mgr",0xa23f,&local_15c,0x134,0,0);
              }
              goto LAB_0014bc28;
            }
          }
        }
        uVar4 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
        if ((uVar2 < uVar4) &&
           (uVar2 = (uint)*(byte *)(iVar3 * 0x14c0 + param_1 + 0xa1e04), uVar2 < 0x20)) {
          if (param_3 !=
              "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
              + uVar2 * 0x5834 + param_1 + 0xe0) {
            printk(&_LC63,0x4a2);
            dump_stack();
          }
          iVar11 = iVar3 * 0x14c0 + param_1;
          *(undefined4 *)(iVar11 + 0xa1d20) = 0x20001;
          *(undefined4 *)(iVar11 + 0xa3144) = 0x10001;
          bVar6 = *(byte *)(iVar11 + 0xa1e04);
          *(char **)(iVar11 + 0xa1e14) =
               "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
               + (uint)bVar6 * 0x5834 + param_1 + 0xe0;
          uVar2 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
          if ((uVar2 <= bVar6) || (0x1f < *(byte *)(iVar11 + 0xa1e04))) {
            if (-1 < DebugLevel) {
              printk("%s> Error! apidx = %d > MAX_MBSSID_NUM!\n","MacTableInsertEntry",
                     *(undefined1 *)(iVar3 * 0x14c0 + param_1 + 0xa1e04));
            }
            *(undefined1 *)(iVar3 * 0x14c0 + param_1 + 0xa1e04) = 0;
          }
          iVar11 = iVar3 * 0x14c0 + 0xa2800;
          *(undefined4 *)(param_1 + iVar11) = *(undefined4 *)(param_3 + 0x21);
          *(undefined2 *)(param_1 + iVar11 + 4) = *(undefined2 *)(param_3 + 0x25);
          uVar2 = *(uint *)(param_3 + 0x2c);
          if (((uVar2 & 1) != 0) && ((*(uint *)(param_3 + 0x174) & 0xe) != 0)) {
            iVar11 = param_1 + iVar3 * 0x14c0;
            *(uint *)(iVar11 + 0xa1e9c) = uVar2;
            *(undefined4 *)(iVar11 + 0xa1fe4) = *(undefined4 *)(param_3 + 0x174);
            *(char *)(iVar11 + 0xa1fe8) = param_3[0x178];
            *(undefined4 *)(iVar11 + 0xa20c4) = *(undefined4 *)(param_3 + 0x254);
            *(char *)(iVar11 + 0xa20c8) = param_3[600];
            os_move_mem((void *)(iVar11 + 0xa1ea0),param_3 + 0x30,0x144);
            *(char *)(iVar11 + 0xa20c8) = param_3[600];
            uVar2 = *(uint *)(param_3 + 0x2c);
          }
          if ((uVar2 & 3) == 0) {
            *(undefined1 *)(iVar3 * 0x14c0 + param_1 + 0xa2234) = 3;
          }
          else {
            *(undefined1 *)(iVar3 * 0x14c0 + param_1 + 0xa2234) = 0;
          }
          iVar11 = iVar3 * 0x14c0 + param_1;
          *(undefined4 *)(iVar11 + 0xa27fc) = 0;
          *(undefined4 *)(iVar11 + 0xa2828) = *(undefined4 *)(&DAT_0036b90c + param_1);
          iVar11 = (uint)*(byte *)(iVar11 + 0xa1e04) * 0x5834 + param_1;
          "pStaCfg->WpaPassPhrase"[iVar11 + 0xb] = "pStaCfg->WpaPassPhrase"[iVar11 + 0xb] + '\x01';
          (&DAT_0036b916)[param_1] = (&DAT_0036b916)[param_1] + '\x01';
          if ((param_1 != 0) &&
             (((*(char *)(param_1 + 0xa7a2e8) == '\x01' || (*(char *)(param_1 + 0xa7a2ea) == '\x01')
               ) && (iVar11 = vow_watf_is_enabled(param_1), iVar11 != 0)))) {
            set_vow_watf_sta_dwrr(param_1,__s1,*(undefined2 *)(iVar3 * 0x14c0 + param_1 + 0xa1e00));
          }
          RTMP_SET_STA_DWRR(param_1,local_19c);
          goto LAB_0014b24c;
        }
        if (0 < DebugLevel) {
          uVar5 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
          printk("%s: The func_tb_idx is over cap = %d\n","MacTableInsertEntry",uVar5);
        }
      }
      else if (0 < DebugLevel) {
        uVar5 = HcGetMaxStaNum(param_1);
        printk("%s: The station number is over MaxUcastEntryNum = %d\n","MacTableInsertEntry",uVar5)
        ;
      }
LAB_0014bc28:
      iVar11 = *(int *)(param_1 + 0x28594c);
      uVar1 = *(ushort *)(iVar3 * 0x14c0 + param_1 + 0xa1e18);
      if (iVar11 != 0) {
        uVar2 = (uint)(uVar1 >> 5);
        *(uint *)(iVar11 + uVar2 * 4) = *(uint *)(iVar11 + uVar2 * 4) & ~(1 << (uVar1 & 0x1f));
      }
      goto LAB_0014baf0;
    }
    if (param_4 == 0x10) {
      iVar11 = iVar3 * 0x14c0 + param_1;
      *(undefined4 *)(iVar11 + 0xa1d20) = 0x10;
      uVar2 = *(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff;
      if (uVar2 == 0x7915 || (uVar2 == 0x7663 || uVar2 == 0x7626)) {
        *(undefined4 *)(iVar11 + 0xa3144) = 0x10001;
      }
    }
    else if (param_4 == 0x20) {
      iVar11 = iVar3 * 0x14c0 + param_1;
      *(undefined4 *)(iVar11 + 0xa1d20) = 0x20001;
      *(undefined4 *)(iVar11 + 0xa3144) = 0x10001;
      *(char **)(iVar11 + 0xa1e14) =
           "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
           + (uint)*(byte *)(iVar11 + 0xa1e04) * 0x5834 + param_1 + 0xe0;
    }
  }
LAB_0014b24c:
  iVar11 = iVar3 * 0x14c0 + param_1;
  TRTableInsertEntry(param_1,*(undefined2 *)(iVar11 + 0xa1e00),local_19c);
  if (*(int *)(iVar11 + 0xa1d20) == 0x20001) {
    if (2 < DebugLevel) {
      printk("%s(): INIT UAPSD MR ENTRY","MacTableInsertEntry");
    }
    iVar11 = DebugLevel;
    puVar8 = (undefined4 *)(param_1 + iVar3 * 0x14c0 + 0xa283c);
    do {
      *puVar8 = 0;
      puVar9 = puVar8 + 4;
      puVar8[-1] = 0;
      puVar8[1] = 0;
      puVar8 = puVar9;
    } while (puVar9 != (undefined4 *)(param_1 + iVar3 * 0x14c0 + 0xa287c));
    iVar13 = iVar3 * 0x14c0 + param_1;
    *(undefined2 *)(iVar13 + 0xa2880) = 0;
    *(undefined4 *)(iVar13 + 0xa287c) = 0;
    *(undefined1 *)(iVar13 + 0xa2883) = 0;
    *(undefined1 *)(iVar13 + 0xa2882) = 0;
    *(undefined1 *)(iVar13 + 0xa2835) = 0;
    if (2 < iVar11) {
      printk("uapsd> MaxSPLength = 0!\n");
      goto LAB_0014b284;
    }
    *(short *)(param_1 + 0x285920) = *(short *)(param_1 + 0x285920) + 1;
    if (*(char *)(param_1 + 0x286285) == '\x01') goto LAB_0014b65c;
  }
  else {
LAB_0014b284:
    iVar11 = DebugLevel;
    *(short *)(param_1 + 0x285920) = *(short *)(param_1 + 0x285920) + 1;
    if (*(char *)(param_1 + 0x286285) == '\x01') {
LAB_0014b65c:
      iVar13 = iVar3 * 0x14c0 + param_1;
      *(undefined1 *)(iVar13 + 0xa2a44) = 0;
      *(undefined1 *)(iVar13 + 0xa2a45) = 0;
    }
    if (2 < iVar11) {
      printk("%s(): alloc entry #%d, Total= %d\n","MacTableInsertEntry",iVar3);
    }
  }
  if (local_19c != 0) {
    iVar13 = param_1 + (uint)(byte)(*param_2 ^ param_2[1] ^ param_2[2] ^ param_2[3] ^ param_2[4] ^
                                   param_2[5]) * 4;
    iVar11 = *(int *)(iVar13 + 0xa1920);
    if (iVar11 == 0) {
      *(int *)(iVar13 + 0xa1920) = local_19c;
    }
    else {
      do {
        iVar13 = iVar11;
        iVar11 = *(int *)(iVar13 + 0x10);
      } while (iVar11 != 0);
      *(int *)(iVar13 + 0x10) = local_19c;
    }
    if ((*(char *)(param_1 + 0x286285) == '\x01') &&
       (iVar11 = iVar3 * 0x14c0 + param_1, *(int *)(iVar11 + 0xa1d20) == 0x20001)) {
      bVar6 = *(byte *)(iVar11 + 0xa1e04);
      if ((uint)bVar6 <
          (uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                      [param_1 + 0xda]) {
        iVar13 = memcmp(__s1,"%s(): FIXME!!!Unexpected frame send to MgmtRing, need to assign the length!\n"
                             + (uint)bVar6 * 0x5834 + param_1 + 0x31,6);
        if ((iVar13 == 0) &&
           (__memzero("%s(): FIXME!!!Unexpected frame send to MgmtRing, need to assign the length!\n"
                      + (uint)bVar6 * 0x5834 + param_1 + 0x31,6),
           *(int *)(iVar11 + 0xa1d20) != 0x20001)) goto LAB_0014aedc;
      }
      if (0 < DebugLevel) {
        printk("New Sta:%pM\n",__s1);
      }
      RtmpOSWrielessEventSend(**(undefined4 **)(iVar3 * 0x14c0 + param_1 + 0xa1d28),1,3,0,__s1,6);
    }
  }
LAB_0014aedc:
  _raw_spin_unlock_bh(iVar12);
  return local_19c;
}

