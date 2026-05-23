// module: mt7915.ko
// function: ap_dev_rx_mgmt_frm @ 0x1f2ac
// size: 724 bytes
//

byte ap_dev_rx_mgmt_frm(int param_1,int param_2,int *param_3)

{
  uint uVar1;
  int iVar2;
  byte bVar3;
  int *piVar4;
  byte bVar5;
  byte *pbVar6;
  short local_2e;
  undefined1 local_2c;
  undefined1 local_2b;
  byte local_2a;
  undefined1 local_29;
  
  pbVar6 = *(byte **)(param_2 + 0x1c);
  bVar3 = **(byte **)(param_2 + 0x10);
  bVar5 = bVar3 & 0x10;
  if ((bVar3 & 0x10) == 0) {
    bVar3 = *pbVar6 & 0xf0;
    if ((bVar3 - 0x40 & 0xb0) == 0) goto joined_r0x0001f35c;
    if (param_3 == (int *)0x0) {
      return bVar5;
    }
    if (*param_3 != 2) {
      return bVar5;
    }
    if (bVar3 != 0xa0 && (*pbVar6 & 0xe0) != 0xc0) {
      return bVar5;
    }
    if (bVar3 != 0xb0) goto LAB_0001f314;
    if ((pbVar6[1] & 0x40) != 0) goto LAB_0001f36c;
    iVar2 = 2;
  }
  else {
    bVar3 = *pbVar6 & 0xf0;
joined_r0x0001f35c:
    if ((bVar3 == 0xb0) && ((pbVar6[1] & 0x40) != 0)) {
LAB_0001f36c:
      bVar3 = (*(byte **)(param_2 + 0x10))[2];
      bVar5 = bVar3 & 1;
      if ((bVar3 & 1) == 0) {
        local_2e = *(short *)(param_2 + 0x48);
        if (param_3 == (int *)0x0) {
          if (DebugLevel < 0) {
            return bVar5;
          }
          printk("ERROR: SW decrypt WEP data fails - the Entry is empty.\n");
          return bVar5;
        }
        local_2e = local_2e + -0x18;
        iVar2 = RTMPSoftDecryptWEP("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                   + param_1 + (uint)(byte)
                                                  "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                                  [param_1 + (uint)*(byte *)(param_3 + 0x39) *
                                                             0x5834 + 600] * 0x51 +
                                               (uint)*(byte *)(param_3 + 0x39) * 0x5834 + 0x110,
                                   pbVar6 + 0x18,&local_2e);
        if (iVar2 == 0) {
          if (DebugLevel < 0) {
            return bVar5;
          }
          printk("ERROR: SW decrypt WEP data fails.\n");
          return bVar5;
        }
        if (2 < DebugLevel) {
          printk("Decrypt AUTH seq#3 successfully\n");
        }
        __ZTE_STA_Assoc_Process(param_1,0x10,0,0,0,0,param_3,"ap_dev_rx_mgmt_frm",0x11cd);
        *(short *)(param_2 + 0x40) = *(short *)(param_2 + 0x40) + -8;
        iVar2 = *param_3;
        goto LAB_0001f304;
      }
    }
    if (param_3 == (int *)0x0) goto LAB_0001f314;
    iVar2 = *param_3;
  }
LAB_0001f304:
  if (iVar2 == 0x20001) {
    RtmpPsIndicate(param_1,*(undefined4 *)(param_2 + 0x2c),*(undefined2 *)(param_2 + 0x4e),
                   ((uint)pbVar6[1] << 0x1b) >> 0x1f);
  }
LAB_0001f314:
  uVar1 = (uint)*(ushort *)(param_2 + 0x4e);
  if (uVar1 < 0x120) {
    iVar2 = *(int *)(uVar1 * 0x14c0 + param_1 + 0xa1d28);
  }
  else {
    piVar4 = (int *)(param_1 + 8);
    do {
      piVar4 = piVar4 + 1;
      iVar2 = *piVar4;
      if ((iVar2 != 0) && (*(char *)(iVar2 + 0x28) != '\0')) goto LAB_0001f41c;
    } while (piVar4 != (int *)(param_1 + 0x1a8));
    iVar2 = 0;
  }
LAB_0001f41c:
  local_2e = *(short *)(param_2 + 0x58);
  local_2c = *(undefined1 *)(param_2 + 0x5a);
  local_2a = *(byte *)(param_2 + 0x5c);
  if (*(byte *)(param_2 + 0x5d) <= *(byte *)(param_2 + 0x5c)) {
    local_2a = *(byte *)(param_2 + 0x5d);
  }
  local_2b = *(undefined1 *)(param_2 + 0x5b);
  local_29 = (undefined1)*(undefined2 *)(param_2 + 0x80);
  MlmeEnqueueForRecv(param_1,uVar1,&local_2e,*(undefined2 *)(param_2 + 0x40),pbVar6,1,iVar2,
                     *(byte *)(param_2 + 99) >> 5);
  return 1;
}

