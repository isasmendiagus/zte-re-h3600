// module: mt7915.ko
// function: Set_DisConnectAllSta_Proc @ 0x3271c
// size: 824 bytes
//

undefined4 Set_DisConnectAllSta_Proc(int *param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  uint uVar5;
  int *piVar6;
  undefined2 local_4a;
  undefined4 local_48;
  undefined4 local_44;
  undefined1 auStack_40 [28];
  
  cVar1 = os_str_tol(param_2,0,10);
  if (cVar1 == '\x02') {
    iVar2 = *param_1;
    if (1 < DebugLevel) {
      printk("[PMF]%s:: apidx=%d\n","Set_DisConnectAllSta_Proc",*(undefined4 *)(iVar2 + 0x3c));
    }
    APMlmeKickOutAllSta(param_1,*(undefined1 *)(iVar2 + 0x3c),3);
    piVar6 = param_1 + 0x28748;
    piVar4 = param_1 + 0x28783;
    iVar2 = 0;
    while( true ) {
      iVar3 = HcGetMaxStaNum(param_1);
      if (iVar3 <= iVar2) break;
      if (piVar4[-0x3b] == 0x20001) {
        __ZTE_STA_Assoc_Process(param_1,0x11,0,0,3,0,piVar6,"Set_DisConnectAllSta_Proc",0x4849);
        if (-1 < DebugLevel) {
          printk("[PMF]%s: MacTableDeleteEntry %02x:%02x:%02x:%02x:%02x:%02x\n",
                 "Set_DisConnectAllSta_Proc",(char)piVar6[0x3b],*(undefined1 *)((int)piVar6 + 0xed),
                 *(undefined1 *)((int)piVar6 + 0xee),*(undefined1 *)((int)piVar6 + 0xef),
                 (char)piVar6[0x3c],*(undefined1 *)((int)piVar6 + 0xf1));
        }
        MacTableDeleteEntry(param_1,(short)piVar6[0x38],piVar4);
      }
      piVar6 = piVar6 + 0x530;
      piVar4 = piVar4 + 0x530;
      iVar2 = iVar2 + 1;
    }
  }
  else {
    local_48 = 0;
    piVar4 = param_1 + 0x28783;
    local_44 = 0;
    piVar6 = param_1 + 0x28748;
    for (uVar5 = 0; iVar2 = HcGetMaxStaNum(param_1), (int)uVar5 < iVar2; uVar5 = uVar5 + 1) {
      if (piVar4[-0x3b] == 0x20001) {
        *(undefined1 *)((int)piVar4 + 0x8f) = 0;
        if ((*(char *)((int)param_1 + 0x286285) == '\x01') && (piVar4[4] == 2)) {
          iVar2 = os_alloc_mem(param_1,&local_48,0x900);
          if (iVar2 != 0) {
            if (2 < DebugLevel) {
              printk(" MlmeAllocateMemory fail  ..\n",0x11,iVar2);
            }
            return 0;
          }
          local_4a = 2;
          __ZTE_STA_Assoc_Process(param_1,0x11,0,0,2,0,piVar6,"Set_DisConnectAllSta_Proc",0x4874);
          if (1 < DebugLevel) {
            printk("Send DeAuth (Reason=%d) to %02x:%02x:%02x:%02x:%02x:%02x\n",local_4a,
                   (char)piVar6[0x3b],*(undefined1 *)((int)piVar4 + 1),
                   *(undefined1 *)((int)piVar4 + 2),*(undefined1 *)((int)piVar4 + 3),(char)piVar4[1]
                   ,*(undefined1 *)((int)piVar4 + 5));
          }
          ZTE_Notify_Node_AD(0,piVar6);
          MgtMacHeaderInit(param_1,auStack_40,0xc,0,piVar4,
                           (char *)((int)param_1 +
                                   (int)(
                                        "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                        + (uint)*(byte *)(piVar4 + -2) * 0x5834 + 0xfb)),
                           (char *)((int)param_1 +
                                   (int)(
                                        "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                        + (uint)*(byte *)(piVar4 + -2) * 0x5834 + 0x101)));
          MakeOutgoingFrame(local_48,&local_44,0x18,auStack_40,2,&local_4a,0xffffffff);
          MiniportMMRequest(param_1,0,local_48,local_44);
          os_free_mem(local_48);
          RtmpusecDelay(5000);
        }
        MacTableDeleteEntry(param_1,uVar5 & 0xffff,piVar4);
      }
      piVar6 = piVar6 + 0x530;
      piVar4 = piVar4 + 0x530;
    }
  }
  return 1;
}

