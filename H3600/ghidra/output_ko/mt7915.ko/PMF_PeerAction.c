// module: mt7915.ko
// function: PMF_PeerAction @ 0x2197ec
// size: 132 bytes
//

void PMF_PeerAction(int param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  char *pcVar3;
  undefined1 uVar4;
  char cVar5;
  undefined1 uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  undefined1 uStack_44;
  undefined1 uStack_43;
  undefined2 uStack_42;
  int iStack_40;
  undefined4 uStack_3c;
  uint uStack_38;
  undefined4 uStack_34;
  uint uStack_30;
  uint uStack_2c;
  uint uStack_28;
  uint uStack_24;
  undefined2 uStack_1c;
  undefined1 uStack_1b;
  ushort uStack_1a;
  
  cVar5 = *(char *)(param_2 + 0x19);
  if (1 < DebugLevel) {
    printk("[PMF]%s : PMF_PeerAction Action=%d\n","PMF_PeerAction",cVar5);
  }
  if (cVar5 == '\0') {
    if (*(char *)(param_2 + 0x19) != '\0') {
      return;
    }
    iStack_40 = 0;
    uStack_3c = 0;
    if (-1 < DebugLevel) {
      printk("[PMF]%s : Receive SA Query Request\n","PMF_PeerSAQueryReqAction");
    }
    if (*(char *)(param_1 + 0x286285) == '\x01') {
      piVar1 = (int *)MacTableLookup(param_1,param_2 + 10);
      if (*(char *)(param_1 + 0x286285) == '\0') goto LAB_002193b4;
LAB_002193c8:
      iVar2 = param_2 + 10;
      if (piVar1 != (int *)0x0) {
        if (*(char *)((int)piVar1 + 0x562) == '\0') {
          if (DebugLevel < 0) {
            return;
          }
          uStack_34._0_1_ = *(undefined1 *)(param_2 + 10);
          uStack_34._1_1_ = *(undefined1 *)(param_2 + 0xb);
          uVar8 = (uint)*(byte *)(param_2 + 0xc);
          pcVar3 = "[PMF]%s : Entry is not PMF capable, STA(%02x:%02x:%02x:%02x:%02x:%02x)\n";
          uVar7 = (uint)*(byte *)(param_2 + 0xd);
          uVar10 = (uint)*(byte *)(param_2 + 0xe);
          uVar9 = (uint)*(byte *)(param_2 + 0xf);
        }
        else if ((*(byte *)(param_2 + 1) & 0x40) == 0) {
          if (DebugLevel < 0) {
            return;
          }
          uStack_34._0_1_ = *(undefined1 *)(param_2 + 10);
          uStack_34._1_1_ = *(undefined1 *)(param_2 + 0xb);
          uVar8 = (uint)*(byte *)(param_2 + 0xc);
          pcVar3 = 
          "[PMF]%s : un-Protected SA Query Req.!!! Drop it!!, STA(%02x:%02x:%02x:%02x:%02x:%02x)\n";
          uVar7 = (uint)*(byte *)(param_2 + 0xd);
          uVar10 = (uint)*(byte *)(param_2 + 0xe);
          uVar9 = (uint)*(byte *)(param_2 + 0xf);
        }
        else {
          uStack_42 = *(undefined2 *)(param_2 + 0x1a);
          os_alloc_mem(0,&iStack_40,0x800);
          if (iStack_40 == 0) {
            return;
          }
          cVar5 = *(char *)(param_1 + 0x286285);
          if (cVar5 == '\x01') {
            if (*piVar1 == 2) {
              ApCliMgtMacHeaderInit(param_1,&uStack_38,0xd,0,iVar2,iVar2,(char)piVar1[0x39]);
              cVar5 = *(char *)(param_1 + 0x286285);
            }
            else {
              MgtMacHeaderInit(param_1,&uStack_38,0xd,0,iVar2,
                               "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                               + (uint)*(byte *)(piVar1 + 0x39) * 0x5834 + param_1 + 0x101,
                               "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                               + (uint)*(byte *)(piVar1 + 0x39) * 0x5834 + param_1 + 0x101);
              cVar5 = *(char *)(param_1 + 0x286285);
            }
          }
          if (cVar5 == '\0') {
            MgtMacHeaderInit(param_1,&uStack_38,0xd,0,iVar2,param_1 + 0x794b5b,iVar2);
          }
          uStack_43 = 1;
          uStack_44 = 8;
          MakeOutgoingFrame(iStack_40,&uStack_3c,0x18,&uStack_38,1,&uStack_44,1,&uStack_43,2,
                            &uStack_42,0xffffffff);
          MiniportMMRequest(param_1,0xd,iStack_40,uStack_3c);
          os_free_mem(iStack_40);
          if (DebugLevel < 0) {
            return;
          }
          uVar8 = uStack_34 >> 0x10 & 0xff;
          pcVar3 = "[PMF]%s - Send SA Query Response to STA(%02x:%02x:%02x:%02x:%02x:%02x)\n";
          uVar7 = uStack_34 >> 0x18;
          uVar10 = uStack_30 & 0xff;
          uVar9 = uStack_30 >> 8 & 0xff;
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
    uStack_34._0_1_ = *(undefined1 *)(param_2 + 10);
    uStack_34._1_1_ = *(undefined1 *)(param_2 + 0xb);
    uVar8 = (uint)*(byte *)(param_2 + 0xc);
    pcVar3 = "[PMF]%s : Entry is not found, STA(%02x:%02x:%02x:%02x:%02x:%02x)\n";
    uVar7 = (uint)*(byte *)(param_2 + 0xd);
    uVar10 = (uint)*(byte *)(param_2 + 0xe);
    uVar9 = (uint)*(byte *)(param_2 + 0xf);
LAB_0021940c:
    printk(pcVar3,"PMF_PeerSAQueryReqAction",(undefined1)uStack_34,uStack_34._1_1_,uVar8,uVar7,
           uVar10,uVar9);
    return;
  }
  if (cVar5 != '\x01') {
    return;
  }
  if (*(char *)(param_2 + 0x19) != '\x01') {
    return;
  }
  if (-1 < DebugLevel) {
    printk("[PMF]%s : Receive SA Query Response\n","PMF_PeerSAQueryRspAction");
  }
  if (*(char *)(param_1 + 0x286285) == '\x01') {
    iVar2 = MacTableLookup(param_1,param_2 + 10);
    if (*(char *)(param_1 + 0x286285) == '\0') goto LAB_002196a4;
LAB_002196b8:
    if (iVar2 != 0) {
      if (*(char *)(iVar2 + 0x562) == '\0') {
        if (DebugLevel < 0) {
          return;
        }
        uVar4 = *(undefined1 *)(param_2 + 10);
        uVar6 = *(undefined1 *)(param_2 + 0xb);
        pcVar3 = "[PMF]%s : Entry is not PMF capable, STA(%02x:%02x:%02x:%02x:%02x:%02x)\n";
      }
      else {
        _uStack_1c = CONCAT22(*(ushort *)(param_2 + 0x1a),uStack_1c);
        uStack_28 = (uint)*(ushort *)(iVar2 + 0x629);
        uStack_24 = (uint)*(ushort *)(param_2 + 0x1a);
        if (uStack_28 != uStack_24) {
          if (DebugLevel < 0) {
            return;
          }
          uStack_38 = (uint)*(byte *)(param_2 + 0xc);
          uStack_34 = (uint)*(byte *)(param_2 + 0xd);
          uStack_30 = (uint)*(byte *)(param_2 + 0xe);
          uStack_2c = (uint)*(byte *)(param_2 + 0xf);
          printk("[PMF]%s - Compare TransactionID wrong, STA(%02x:%02x:%02x:%02x:%02x:%02x), AP TransactionID =%d, STA TransactionID =%d\n"
                 ,"PMF_PeerSAQueryRspAction",*(undefined1 *)(param_2 + 10),
                 *(undefined1 *)(param_2 + 0xb));
          return;
        }
        *(undefined1 *)(iVar2 + 0x628) = 0;
        RTMPCancelTimer(iVar2 + 0x5c0,&uStack_1b);
        RTMPCancelTimer(iVar2 + 0x5f4,&uStack_1b);
        if (DebugLevel < 0) {
          return;
        }
        uVar4 = *(undefined1 *)(param_2 + 10);
        uVar6 = *(undefined1 *)(param_2 + 0xb);
        pcVar3 = "[PMF]%s - Compare TransactionID correctly, STA(%02x:%02x:%02x:%02x:%02x:%02x)\n";
      }
      goto LAB_002196e8;
    }
  }
  else if (*(char *)(param_1 + 0x286285) == '\0') {
LAB_002196a4:
    iVar2 = MacTableLookup2(param_1,param_2 + 10,*(undefined4 *)(param_2 + 0x92c));
    goto LAB_002196b8;
  }
  if (DebugLevel < 0) {
    return;
  }
  uVar4 = *(undefined1 *)(param_2 + 10);
  uVar6 = *(undefined1 *)(param_2 + 0xb);
  pcVar3 = "[PMF]%s : Entry is not found, STA(%02x:%02x:%02x:%02x:%02x:%02x)\n";
LAB_002196e8:
  uStack_2c = (uint)*(byte *)(param_2 + 0xf);
  uStack_38 = (uint)*(byte *)(param_2 + 0xc);
  uStack_34 = (uint)*(byte *)(param_2 + 0xd);
  uStack_30 = (uint)*(byte *)(param_2 + 0xe);
  printk(pcVar3,"PMF_PeerSAQueryRspAction",uVar4,uVar6);
  return;
}

