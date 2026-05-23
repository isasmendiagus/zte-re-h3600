// module: mt7915.ko
// function: SendBTMConfirm @ 0x224df0
// size: 348 bytes
//

void SendBTMConfirm(int param_1,byte *param_2)

{
  byte bVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  undefined1 uStack_19;
  
  bVar1 = *param_2;
  uVar8 = *(undefined4 *)
           (
           "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
           + (uint)bVar1 * 0x5834 + param_1 + 0xe0);
  if (2 < DebugLevel) {
    printk(&_LC6,"SendBTMConfirm");
  }
  wext_send_btm_cfm_event_newapi(uVar8,param_2 + 1,param_2 + 0xc,*(undefined2 *)(param_2 + 10));
  iVar7 = (uint)bVar1 * 0x5834;
  down_interruptible("RT_OID_WSC_SET_CONF_MODE:: WscConfMode = %d\n" + param_1 + iVar7 + 0x20);
  iVar6 = param_1 + iVar7;
  piVar4 = (int *)**(int **)("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + iVar6 + 0x28);
  piVar3 = *(int **)("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + iVar6 + 0x28);
  do {
    piVar2 = piVar4;
    if (piVar3 == (int *)("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + iVar6 + 0x28)) {
LAB_00224f28:
      up("RT_OID_WSC_SET_CONF_MODE:: WscConfMode = %d\n" + param_1 + iVar7 + 0x20);
      return;
    }
    iVar5 = memcmp((char *)((int)piVar3 + 0xd),param_2 + 1,6);
    if (iVar5 == 0) {
      if (*piVar3 != 0) {
        *(int *)(*piVar3 + 4) = piVar3[1];
      }
      if ((int *)piVar3[1] != (int *)0x0) {
        *(int *)piVar3[1] = *piVar3;
      }
      *piVar3 = 0;
      piVar3[1] = 0;
      RTMPCancelTimer(piVar3 + 6,&uStack_19);
      RTMPReleaseTimer(piVar3 + 6,&uStack_19);
      RTMPCancelTimer(piVar3 + 0x13,&uStack_19);
      RTMPReleaseTimer(piVar3 + 0x13,&uStack_19);
      os_free_mem(piVar3);
      goto LAB_00224f28;
    }
    piVar4 = (int *)*piVar2;
    piVar3 = piVar2;
  } while( true );
}

