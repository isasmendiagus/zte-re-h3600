// module: mt7915.ko
// function: a4_ap_peer_enable @ 0x9f910
// size: 428 bytes
//

undefined4 a4_ap_peer_enable(int param_1,int *param_2,uint param_3)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  bool bVar4;
  undefined2 local_20;
  undefined2 local_1e;
  undefined1 local_1c;
  undefined1 local_1b;
  undefined1 local_1a;
  
  if ((param_2 != (int *)0x0) && (*param_2 == 0x20001)) {
    uVar3 = (uint)*(byte *)(param_2 + 0x39);
    uVar1 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    bVar4 = 0x1e < uVar3;
    if (uVar3 < 0x20) {
      bVar4 = uVar1 <= uVar3;
    }
    if ((!bVar4) &&
       ((("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
          + param_1 + uVar3 * 0x5834 + 0xe0 == (char *)0x0 ||
         (iVar2 = param_1 + uVar3 * 0x5834,
         *(int *)(
                 "4/home/ws/zx279128s/packages/function/wlan/mtk/drivers/MT7915_V7.0.1.0/mt_wifi_ap/../mt_wifi/embedded/fsm/ap_mgmt_cntl.c:%d assert pAdfailed\n"
                 + iVar2 + 0x2b) == 0)) ||
        ("PIN authentication or communication error occurs!!\nRegistrar does NOT accept the same PIN again!(PIN:%08u)\n"
         [iVar2 + 0x5c] != '\x01')))) {
      uVar1 = (uint)*(byte *)(param_2 + 0x3a);
      if (uVar1 == 0) {
        a4_proxy_delete(param_1,uVar3,param_2 + 0x3b);
        os_zero_mem(&local_20,8);
        if (1 < DebugLevel) {
          printk("Enabled A4 for entry:%02x:%02x:%02x:%02x:%02x:%02x\n",(char)param_2[0x3b],
                 *(undefined1 *)((int)param_2 + 0xed),*(undefined1 *)((int)param_2 + 0xee),
                 *(undefined1 *)((int)param_2 + 0xef),(char)param_2[0x3c],
                 *(undefined1 *)((int)param_2 + 0xf1));
        }
        local_1e = 8;
        local_20 = 6;
        local_1c = 1;
        local_1b = 1;
        local_1a = 0;
        iVar2 = CmdExtWtblUpdate(param_1,(short)param_2[0x38],2,&local_20,8);
        if (iVar2 != 0) {
          return 0;
        }
        a4_add_entry(param_1,uVar3,(short)param_2[0x38]);
        uVar1 = (uint)*(byte *)(param_2 + 0x3a);
      }
      if ((uVar1 < param_3) && (*(char *)(param_2 + 0x3a) = (char)param_3, 0 < DebugLevel)) {
        printk("SET_A4_ENTRY type:%d OK!\n",param_3);
      }
      return 1;
    }
  }
  return 0;
}

