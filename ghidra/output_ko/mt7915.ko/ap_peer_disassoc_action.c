// module: mt7915.ko
// function: ap_peer_disassoc_action @ 0x4e138
// size: 672 bytes
//

void ap_peer_disassoc_action(int param_1,int param_2)

{
  ushort uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  undefined2 local_36;
  undefined4 local_34;
  undefined2 local_30;
  undefined4 local_2e;
  undefined2 local_2a;
  
  if (DebugLevel < 1) {
    local_34 = *(uint *)(param_2 + 4);
    local_36 = *(undefined2 *)(param_2 + 0x18);
    local_30 = *(undefined2 *)(param_2 + 8);
    local_2e = *(uint *)(param_2 + 10);
    local_2a = *(undefined2 *)(param_2 + 0xe);
  }
  else {
    printk("ASSOC - 1 receive DIS-ASSOC request\n");
    local_34 = *(uint *)(param_2 + 4);
    uVar6 = *(uint *)(param_2 + 10);
    local_30 = *(undefined2 *)(param_2 + 8);
    local_2a = *(undefined2 *)(param_2 + 0xe);
    local_36 = *(undefined2 *)(param_2 + 0x18);
    local_2e = uVar6;
    if (2 < DebugLevel) {
      local_2a._1_1_ = (undefined1)((ushort)local_2a >> 8);
      uVar3 = local_2a._1_1_;
      local_2e._1_1_ = (undefined1)(uVar6 >> 8);
      uVar2 = local_2e._1_1_;
      uVar4 = (undefined1)local_2a;
      printk("ASSOC - receive DIS-ASSOC(seq-%d) request from %02x:%02x:%02x:%02x:%02x:%02x, reason=%d\n"
             ,(uint)*(byte *)(param_2 + 0x17) << 4 | (uint)(*(byte *)(param_2 + 0x16) >> 4),
             uVar6 & 0xff,uVar2,uVar6 >> 0x10 & 0xff,uVar6 >> 0x18,uVar4,uVar3,local_36);
    }
  }
  iVar5 = MacTableLookup(param_1,&local_2e);
  if (iVar5 != 0) {
    if ((*(char *)(iVar5 + 0x562) == '\x01') && ((*(byte *)(param_2 + 1) & 0x40) == 0)) {
      if (2 < DebugLevel) {
        printk("drop due to unprotect disassoc frame\n");
      }
    }
    else {
      uVar1 = *(ushort *)(param_2 + 0x920);
      uVar6 = HcGetMaxStaNum(param_1);
      if (uVar1 < uVar6) {
        iVar8 = (uint)*(byte *)(iVar5 + 0xe4) * 0x5834;
        iVar7 = memcmp("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                       + param_1 + iVar8 + 0xfb,&local_34,6);
        if (iVar7 == 0) {
          if (((*(uint *)(iVar5 + 0x17c) & 0x10048) != 0) ||
             ("Airtime control --> %s(%d)\n"[param_1 + iVar8 + 0x18] == '\x01')) {
            DOT1X_InternalCmdAction(param_1,iVar5,0);
          }
          if ((*(ushort *)(iVar5 + 0xe0) < 0x120) && (*(int *)(iVar5 + 0xfc) == 2)) {
            ZTE_Notify_Node_AD(0,iVar5);
            __ZTE_STA_Assoc_Process
                      (param_1,0xd,0,0,local_36,0,iVar5,"ap_peer_disassoc_action",0xcac);
          }
          wlan_dbg_save_staoffline_record(iVar5,local_36,0xcaf,"ap_peer_disassoc_action");
          MacTableDeleteEntry(param_1,*(ushort *)(param_2 + 0x920),&local_2e);
        }
        else if (-1 < DebugLevel) {
          printk("ASSOC - The DA of this DIS-ASSOC request is %02x:%02x:%02x:%02x:%02x:%02x, ignore.\n"
                 ,local_34 & 0xff,local_34._1_1_,local_34._2_1_,local_34 >> 0x18,
                 (undefined1)local_30,local_30._1_1_);
        }
      }
    }
  }
  return;
}

