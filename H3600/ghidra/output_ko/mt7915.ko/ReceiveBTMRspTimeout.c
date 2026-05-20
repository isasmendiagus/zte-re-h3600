// module: mt7915.ko
// function: ReceiveBTMRspTimeout @ 0x224c64
// size: 392 bytes
//

void ReceiveBTMRspTimeout(int param_1,void *param_2)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  char *pcVar7;
  undefined1 uStack_2d;
  byte local_2c;
  undefined1 auStack_2b [8];
  undefined1 auStack_23 [7];
  
  if (0 < DebugLevel) {
    printk(&_LC6,"ReceiveBTMRspTimeout");
  }
  os_move_mem(&local_2c,param_2,0xc);
  uVar6 = (uint)local_2c;
  pcVar7 = "RT_OID_WSC_SET_CONF_MODE:: WscConfMode = %d\n" + param_1 + uVar6 * 0x5834 + 0x20;
  down_interruptible(pcVar7);
  iVar5 = param_1 + uVar6 * 0x5834;
  piVar3 = (int *)**(int **)("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + iVar5 + 0x28);
  piVar2 = *(int **)("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + iVar5 + 0x28);
  while( true ) {
    piVar1 = piVar3;
    if (piVar2 == (int *)("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n" + iVar5 + 0x28)) {
      up(pcVar7);
      if (0 < DebugLevel) {
        printk("%s receive btm rsp;BTMPeerEntry is already deleted \n","ReceiveBTMRspTimeout");
      }
      return;
    }
    iVar4 = memcmp((char *)((int)piVar2 + 0xd),auStack_2b,6);
    if (iVar4 == 0) break;
    piVar3 = (int *)*piVar1;
    piVar2 = piVar1;
  }
  up(pcVar7);
  wext_send_btm_cfm_event_newapi
            (*(undefined4 *)
              (
              "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
              + (uint)local_2c * 0x5834 + param_1 + 0xe0),auStack_2b,auStack_23,1);
  down_interruptible(pcVar7);
  if (*piVar2 != 0) {
    *(int *)(*piVar2 + 4) = piVar2[1];
  }
  if ((int *)piVar2[1] != (int *)0x0) {
    *(int *)piVar2[1] = *piVar2;
  }
  *piVar2 = 0;
  piVar2[1] = 0;
  up(pcVar7);
  RTMPReleaseTimer(piVar2 + 6,&uStack_2d);
  RTMPReleaseTimer(piVar2 + 0x13,&uStack_2d);
  os_free_mem(piVar2);
  return;
}

