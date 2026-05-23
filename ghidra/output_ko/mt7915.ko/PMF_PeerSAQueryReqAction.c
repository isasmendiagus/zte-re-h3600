// module: mt7915.ko
// function: PMF_PeerSAQueryReqAction @ 0x219b24
// size: 780 bytes
//

void PMF_PeerSAQueryReqAction(int param_1,int param_2)

{
  int *piVar1;
  char *pcVar2;
  char cVar3;
  int iVar4;
  undefined1 local_44;
  undefined1 local_43;
  undefined2 local_42;
  int local_40;
  undefined4 local_3c;
  undefined1 auStack_38 [4];
  undefined1 local_34;
  undefined1 local_33;
  undefined1 local_32;
  undefined1 local_31;
  undefined1 local_30;
  undefined1 local_2f;
  
  if (*(char *)(param_2 + 0x19) != '\0') {
    return;
  }
  local_40 = 0;
  local_3c = 0;
  if (-1 < DebugLevel) {
    printk("[PMF]%s : Receive SA Query Request\n","PMF_PeerSAQueryReqAction");
  }
  if (*(char *)(param_1 + 0x286285) == '\x01') {
    piVar1 = (int *)MacTableLookup(param_1,param_2 + 10);
    if (*(char *)(param_1 + 0x286285) == '\0') goto LAB_002193b4;
LAB_002193c8:
    iVar4 = param_2 + 10;
    if (piVar1 != (int *)0x0) {
      if (*(char *)((int)piVar1 + 0x562) == '\0') {
        if (DebugLevel < 0) {
          return;
        }
        local_34 = *(undefined1 *)(param_2 + 10);
        local_33 = *(undefined1 *)(param_2 + 0xb);
        local_32 = *(undefined1 *)(param_2 + 0xc);
        pcVar2 = "[PMF]%s : Entry is not PMF capable, STA(%02x:%02x:%02x:%02x:%02x:%02x)\n";
        local_31 = *(undefined1 *)(param_2 + 0xd);
        local_30 = *(undefined1 *)(param_2 + 0xe);
        local_2f = *(undefined1 *)(param_2 + 0xf);
      }
      else if ((*(byte *)(param_2 + 1) & 0x40) == 0) {
        if (DebugLevel < 0) {
          return;
        }
        local_34 = *(undefined1 *)(param_2 + 10);
        local_33 = *(undefined1 *)(param_2 + 0xb);
        local_32 = *(undefined1 *)(param_2 + 0xc);
        pcVar2 = 
        "[PMF]%s : un-Protected SA Query Req.!!! Drop it!!, STA(%02x:%02x:%02x:%02x:%02x:%02x)\n";
        local_31 = *(undefined1 *)(param_2 + 0xd);
        local_30 = *(undefined1 *)(param_2 + 0xe);
        local_2f = *(undefined1 *)(param_2 + 0xf);
      }
      else {
        local_42 = *(undefined2 *)(param_2 + 0x1a);
        os_alloc_mem(0,&local_40,0x800);
        if (local_40 == 0) {
          return;
        }
        cVar3 = *(char *)(param_1 + 0x286285);
        if (cVar3 == '\x01') {
          if (*piVar1 == 2) {
            ApCliMgtMacHeaderInit(param_1,auStack_38,0xd,0,iVar4,iVar4,(char)piVar1[0x39]);
            cVar3 = *(char *)(param_1 + 0x286285);
          }
          else {
            MgtMacHeaderInit(param_1,auStack_38,0xd,0,iVar4,
                             "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                             + (uint)*(byte *)(piVar1 + 0x39) * 0x5834 + param_1 + 0x101,
                             "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                             + (uint)*(byte *)(piVar1 + 0x39) * 0x5834 + param_1 + 0x101);
            cVar3 = *(char *)(param_1 + 0x286285);
          }
        }
        if (cVar3 == '\0') {
          MgtMacHeaderInit(param_1,auStack_38,0xd,0,iVar4,param_1 + 0x794b5b,iVar4);
        }
        local_43 = 1;
        local_44 = 8;
        MakeOutgoingFrame(local_40,&local_3c,0x18,auStack_38,1,&local_44,1,&local_43,2,&local_42,
                          0xffffffff);
        MiniportMMRequest(param_1,0xd,local_40,local_3c);
        os_free_mem(local_40);
        if (DebugLevel < 0) {
          return;
        }
        pcVar2 = "[PMF]%s - Send SA Query Response to STA(%02x:%02x:%02x:%02x:%02x:%02x)\n";
      }
      goto LAB_0021940c;
    }
  }
  else if (*(char *)(param_1 + 0x286285) == '\0') {
LAB_002193b4:
    piVar1 = (int *)MacTableLookup2(param_1,param_2 + 10,*(undefined4 *)(param_2 + 0x92c));
    goto LAB_002193c8;
  }
  if (DebugLevel < 0) {
    return;
  }
  local_34 = *(undefined1 *)(param_2 + 10);
  local_33 = *(undefined1 *)(param_2 + 0xb);
  local_32 = *(undefined1 *)(param_2 + 0xc);
  pcVar2 = "[PMF]%s : Entry is not found, STA(%02x:%02x:%02x:%02x:%02x:%02x)\n";
  local_31 = *(undefined1 *)(param_2 + 0xd);
  local_30 = *(undefined1 *)(param_2 + 0xe);
  local_2f = *(undefined1 *)(param_2 + 0xf);
LAB_0021940c:
  printk(pcVar2,"PMF_PeerSAQueryReqAction",local_34,local_33,local_32,local_31,local_30,local_2f);
  return;
}

