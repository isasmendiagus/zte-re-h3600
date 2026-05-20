// module: mt7915.ko
// function: ApUpdateAccessControlList @ 0x15674
// size: 1124 bytes
//

void ApUpdateAccessControlList(int param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  undefined2 local_4a;
  undefined4 local_48;
  undefined4 local_44;
  undefined1 auStack_40 [28];
  
  local_48 = 0;
  local_44 = 0;
  local_4a = 0;
  uVar1 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  if (uVar1 <= param_2) {
    printk(&_LC67,0xece);
    dump_stack();
  }
  uVar1 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  if (param_2 < uVar1) {
    if (2 < DebugLevel) {
      printk("ApUpdateAccessControlList : Apidx = %d\n",param_2);
    }
    iVar6 = param_2 * 0x5834;
    if (*(int *)("[RTMPSetInformation][BandIdx=%d] Ndis802_11OFDM5\n" + param_1 + iVar6 + 0x31) != 0
       ) {
      uVar1 = 0;
      while( true ) {
        uVar7 = uVar1 & 0xffff;
        uVar2 = HcGetMaxStaNum(param_1);
        if (uVar2 <= uVar7) break;
        iVar4 = param_1 + uVar7 * 0x14c0;
        if ((*(int *)(iVar4 + 0xa1d20) == 0x20001) && (*(byte *)(iVar4 + 0xa1e04) == param_2)) {
          uVar2 = *(uint *)("Set::OID_802_11_NETWORK_TYPE_IN_USE (=%d)\n" + param_1 + iVar6 + 1);
          if (uVar2 != 0) {
            uVar5 = 0;
            do {
              iVar4 = memcmp((void *)(param_1 + uVar7 * 0x14c0 + 0xa1e0c),
                             "Set::OID_802_11_NETWORK_TYPE_IN_USE (=%d)\n" +
                             param_1 + iVar6 + uVar5 * 8 + 5,6);
              uVar5 = uVar5 + 1 & 0xffff;
              if (iVar4 == 0) {
                if (*(int *)("[RTMPSetInformation][BandIdx=%d] Ndis802_11OFDM5\n" +
                            param_1 + iVar6 + 0x31) != 2) goto LAB_00015728;
                if (DebugLevel < 3) goto LAB_000158c0;
                printk("STA on negative ACL. remove it...\n");
                goto LAB_00015820;
              }
            } while (uVar5 < uVar2);
          }
          if (*(int *)("[RTMPSetInformation][BandIdx=%d] Ndis802_11OFDM5\n" + param_1 + iVar6 + 0x31
                      ) == 1) {
            if (2 < DebugLevel) {
              printk("STA not on positive ACL. remove it...\n");
LAB_00015820:
              if ((2 < DebugLevel) && (printk("Apidx = %d\n",param_2), 2 < DebugLevel)) {
                printk("pAd->ApCfg.MBSSID[%d].AccessControlList.Policy = %d\n",param_2,
                       *(undefined4 *)
                        ("[RTMPSetInformation][BandIdx=%d] Ndis802_11OFDM5\n" +
                        param_1 + iVar6 + 0x31));
              }
            }
LAB_000158c0:
            iVar8 = param_1 + uVar7 * 0x14c0;
            iVar4 = param_1 + uVar7 * 0x14c0 + 0xa1d20;
            if (*(int *)(iVar8 + 0xa1e1c) == 2) {
              iVar3 = os_alloc_mem(param_1,&local_48,0x900);
              if (iVar3 != 0) {
                if (DebugLevel < 3) {
                  return;
                }
                printk(" MlmeAllocateMemory fail  ..\n");
                return;
              }
              local_4a = 3;
              if (-1 < DebugLevel) {
                printk("ASSOC - Send DISASSOC  Reason = %d frame  TO %02x:%02x:%02x:%02x:%02x:%02x\n"
                       ,3,*(undefined1 *)(iVar8 + 0xa1e0c),*(undefined1 *)(iVar8 + 0xa1e0d),
                       *(undefined1 *)(iVar8 + 0xa1e0e),*(undefined1 *)(iVar8 + 0xa1e0f),
                       *(undefined1 *)(iVar8 + 0xa1e10),*(undefined1 *)(iVar8 + 0xa1e11));
              }
              MgtMacHeaderInit(param_1,auStack_40,0xc,0,uVar7 * 0x14c0 + param_1 + 0xa1e0c,
                               "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                               + param_1 + iVar6 + 0xfb,
                               "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                               + param_1 + iVar6 + 0x101);
              MakeOutgoingFrame(local_48,&local_44,0x18,auStack_40,2,&local_4a,0xffffffff);
              MiniportMMRequest(param_1,0,local_48,local_44);
              os_free_mem(local_48);
              ZTE_Notify_Node_AD(0,iVar4);
              wlan_dbg_save_staoffline_record(iVar4,local_4a,0xf1f,"ApUpdateAccessControlList");
              RtmpusecDelay(5000);
            }
            __ZTE_STA_Assoc_Process
                      (param_1,0x11,0,0,local_4a,0,iVar4,"ApUpdateAccessControlList",0xf26);
            mac_entry_delete(param_1,iVar4);
          }
        }
LAB_00015728:
        uVar1 = uVar1 + 1;
      }
    }
  }
  return;
}

