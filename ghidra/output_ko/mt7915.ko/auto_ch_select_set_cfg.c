// module: mt7915.ko
// function: auto_ch_select_set_cfg @ 0x26720
// size: 416 bytes
//

void auto_ch_select_set_cfg(int param_1,undefined4 param_2)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  uint *puVar4;
  undefined *puVar5;
  uint *puVar6;
  undefined *puVar7;
  bool bVar8;
  uint local_30;
  
  iVar2 = rstrtok(param_2,&_LC86);
  puVar4 = (uint *)(&DAT_0036b828 + param_1);
  puVar7 = &DAT_0036b824 + param_1;
  if (iVar2 != 0) {
    bVar8 = false;
    local_30 = 3;
    puVar5 = puVar7;
    puVar6 = puVar4;
    do {
      iVar3 = os_str_tol(iVar2,0,10);
      bVar1 = false;
      if (iVar3 != 0) {
        local_30 = simple_strtol(iVar2,0,10);
        bVar1 = local_30 < 4;
      }
      if ((*(int *)(param_1 + 0x795050) == 2) ||
         ((*(ushort *)
            (
            "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
            + param_1 + 0xf8) & 0xb1) == 0)) {
        *puVar6 = local_30;
        *puVar5 = bVar1;
      }
      else if ((bVar8) || (*(char *)(param_1 + 0x79504d) != '\x01')) {
        *(uint *)(&DAT_0036b828 + param_1) = local_30;
        (&DAT_0036b824)[param_1] = bVar1;
      }
      else {
        *(uint *)(&DAT_0036b82c + param_1) = local_30;
        (&DAT_0036b825)[param_1] = bVar1;
      }
      puVar6 = puVar6 + 1;
      iVar2 = rstrtok(0,&_LC86);
      puVar5 = puVar5 + 1;
      if (iVar2 == 0) {
        bVar8 = true;
      }
      bVar1 = !bVar8;
      bVar8 = true;
    } while (bVar1);
  }
  iVar2 = 0;
  do {
    if (2 < DebugLevel) {
      printk("%s(): BandIdx%d, AutoChannelAtBootup=%d, AutoChannelAlg = %d\n",
             "auto_ch_select_set_cfg",iVar2,*puVar7,*puVar4);
    }
    bVar8 = iVar2 != 1;
    puVar4 = puVar4 + 1;
    iVar2 = 1;
    puVar7 = puVar7 + 1;
  } while (bVar8);
  return;
}

