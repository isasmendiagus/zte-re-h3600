// module: mt7915.ko
// function: compose_rrm_BcnReq_ie @ 0x22225c
// size: 772 bytes
//

/* WARNING: Type propagation algorithm not settling */

void compose_rrm_BcnReq_ie
               (int param_1,int param_2,int *param_3,int param_4,undefined1 param_5,byte param_6)

{
  int iVar1;
  char cVar2;
  uint uVar3;
  uint uVar4;
  int local_40 [2];
  undefined1 local_35;
  undefined1 local_34;
  undefined2 local_33;
  undefined2 local_31;
  undefined1 local_2f;
  uint local_2e;
  undefined2 local_2a;
  
  local_40[0] = 0;
  local_40[1] = 0;
  if (2 < DebugLevel) {
    printk(&_LC50,"compose_rrm_BcnReq_ie");
  }
  local_35 = *(undefined1 *)(param_4 + 8);
  local_2e = *(uint *)(param_4 + 0xe);
  local_34 = *(undefined1 *)(param_4 + 9);
  local_33 = *(undefined2 *)(param_4 + 10);
  local_2a = *(undefined2 *)(param_4 + 0x12);
  local_31 = *(undefined2 *)(param_4 + 0xc);
  local_2f = *(undefined1 *)(param_4 + 0x14);
  local_40[0] = 10;
  RRM_InsertBcnReqIE(param_1,param_2 + 10,local_40,&local_35);
  if (2 < DebugLevel) {
    printk("%s RegulatoryClass=%d ChNumber=%d RandomInterval=%d MeasureDuration=%d MeasureMode=%d Bssid(%02x:%02x:%02x:%02x:%02x:%02x)\n"
           ,"compose_rrm_BcnReq_ie",local_35,local_34,local_33,local_31,local_2f,local_2e & 0xff,
           local_2e >> 8 & 0xff,local_2e >> 0x10 & 0xff,local_2e >> 0x18,(undefined1)local_2a,
           local_2a._1_1_);
  }
  RRM_InsertBcnReqSsidSubIE
            (param_1,param_2 + local_40[0],local_40,param_4 + 0x16,*(undefined1 *)(param_4 + 0x15));
  uVar3 = *(byte *)(param_4 + 0x15) + 0x19 & 0xff;
  RRM_InsertBcnReqRepCndSubIE
            (param_1,param_2 + local_40[0],local_40,*(undefined1 *)(param_4 + 0x3b),
             *(undefined1 *)(param_4 + 0x3c));
  RRM_InsertBcnReqRepDetailSubIE
            (param_1,param_2 + local_40[0],local_40,*(undefined1 *)(param_4 + 0x3d));
  if (*(char *)(param_4 + 0x3d) == '\x01') {
    RRM_InsertRequestIE_11KV_API
              (param_1,param_2 + local_40[0],local_40,param_4 + 0x6f,*(undefined1 *)(param_4 + 0x6e)
              );
    uVar3 = uVar3 + *(byte *)(param_4 + 0x6e) + 2 & 0xff;
  }
  if ((*(char *)(param_4 + 9) == -1) && (cVar2 = *(char *)(param_4 + 0x3f), cVar2 != '\0')) {
    uVar4 = 0;
    do {
      iVar1 = local_40[0];
      uVar4 = uVar4 + 1 & 0xff;
      InsertChannelRepIE(param_1,param_2 + local_40[0],local_40,param_1 + 0x794c31,cVar2,
                         param_4 + 0x50,
                         *(undefined2 *)
                          (
                          "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                          + (uint)param_6 * 0x5834 + param_1 + 0xf8),(uint)param_6);
      cVar2 = *(char *)(param_4 + uVar4 + 0x3f);
      uVar3 = uVar3 + (local_40[0] - iVar1) & 0xff;
    } while (cVar2 != '\0');
  }
  if ((0xfa < uVar3) && (-1 < DebugLevel)) {
    printk("%s() MeasureReq IE len > 255!\n","compose_rrm_BcnReq_ie");
  }
  MakeMeasurementReqFrame
            (param_1,param_2,local_40 + 1,uVar3,5,0,param_5,0,5,*(undefined2 *)(param_4 + 6));
  *param_3 = local_40[0];
  return;
}

