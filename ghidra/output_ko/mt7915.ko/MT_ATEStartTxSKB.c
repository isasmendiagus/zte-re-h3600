// module: mt7915.ko
// function: MT_ATEStartTxSKB @ 0x287ba0
// size: 1204 bytes
//

int MT_ATEStartTxSKB(int param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  byte bVar3;
  char cVar4;
  char cVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  code *pcVar11;
  int iVar12;
  int iVar13;
  uint uVar14;
  int *piVar15;
  uint local_2c;
  
  iVar7 = *(int *)(param_1 + 0xa39fd8);
  uVar14 = (uint)*(byte *)(param_1 + 0xa3ae36);
  iVar6 = net_ad_wrap_service();
  iVar12 = uVar14 * 0xd18;
  iVar8 = *(int *)(iVar6 + iVar12 + 0x4e4);
  iVar6 = net_ad_wrap_service(param_1);
  uVar1 = *(undefined1 *)(iVar6 + iVar12 + 0x1132);
  iVar6 = net_ad_wrap_service(param_1);
  uVar2 = *(undefined1 *)(iVar6 + iVar12 + 0x1130);
  iVar6 = net_ad_wrap_service(param_1);
  uVar9 = *(uint *)(iVar6 + iVar12 + 0x4e0);
  iVar6 = net_ad_wrap_service(param_1);
  iVar10 = *(int *)(iVar6 + iVar12 + 0x1118);
  iVar6 = net_ad_wrap_service(param_1);
  bVar3 = *(byte *)(iVar6 + iVar12 + 0x1136);
  iVar6 = net_ad_wrap_service(param_1);
  cVar4 = *(char *)(iVar6 + iVar12 + 0x50c);
  iVar6 = net_ad_wrap_service(param_1);
  local_2c = (uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                         [param_1 + 0xda];
  cVar5 = *(char *)(iVar6 + iVar12 + 0x1138);
  if (0 < DebugLevel) {
    printk("%s: control_band_idx:%u, ch:%x, cntl_ch:%x, wdev_idx:%x\n","MT_ATEStartTxSKB",uVar14,
           uVar2,uVar1,(int)cVar4);
  }
  if (iVar8 == 0) {
    iVar6 = 0;
  }
  else {
    if ((uVar9 & 2) != 0) {
      return 0;
    }
    MtATESetMacTxRx(param_1,1,1,uVar14);
    if (cVar5 == ' ') {
      WtblDwSet(param_1,*(undefined2 *)(param_1 + 0xa3b008),1,5,0xffffcfff,(bVar3 & 3) << 0xc);
    }
    MtATESetMacTxRx(param_1,6,0,uVar14);
    msleep(0x1e);
    iVar6 = *(int *)(*(int *)(param_1 + 4) + 0x240);
    if (iVar6 == 0) {
      warn_slowpath_null("include/linux/netdevice.h",0xa06);
      printk(&_LC113);
    }
    else {
      _set_bit(0,iVar6 + 0x50);
    }
    if (*(char *)(param_1 + 0x286285) == '\x01') {
      iVar6 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
      if (iVar6 < (int)local_2c) {
        local_2c = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
      }
      piVar15 = (int *)("%s: Allocate memory fail!!!\n" + param_1 + 0xc);
      for (iVar6 = 1; iVar12 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0)),
          iVar6 < iVar12; iVar6 = iVar6 + 1) {
        if (*piVar15 != 0) {
          iVar12 = *(int *)(*piVar15 + 0x240);
          if (iVar12 == 0) {
            warn_slowpath_null("include/linux/netdevice.h",0xa06);
            printk(&_LC113);
          }
          else {
            _set_bit(0,iVar12 + 0x50);
          }
        }
        piVar15 = piVar15 + 0x160d;
      }
    }
    *(uint *)(param_1 + 0xa39f84) = *(uint *)(param_1 + 0xa39f84) | 0x800000;
    if ((uVar9 & 4) != 0) {
      MtATESetMacTxRx(param_1,6,1,uVar14);
    }
    _clear_bit(0,*(int *)(*(int *)(param_1 + 4) + 0x240) + 0x50);
    if (*(char *)(param_1 + 0x286285) == '\x01') {
      iVar6 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
      if (iVar6 < (int)local_2c) {
        hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
      }
      piVar15 = (int *)("%s: Allocate memory fail!!!\n" + param_1 + 0xc);
      iVar6 = 1;
      while( true ) {
        iVar12 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
        iVar13 = iVar6 + 1;
        if (iVar12 <= iVar6) break;
        iVar12 = *piVar15;
        piVar15 = piVar15 + 0x160d;
        iVar6 = iVar13;
        if (iVar12 != 0) {
          _clear_bit(0,*(int *)(iVar12 + 0x240) + 0x50);
        }
      }
    }
    *(uint *)(param_1 + 0xa39f84) = *(uint *)(param_1 + 0xa39f84) & 0xff7fffff;
    pcVar11 = *(code **)(iVar7 + 8);
    if (pcVar11 == (code *)0x0) {
      iVar6 = MT_ATEComposePkt(param_1,iVar8,uVar14);
    }
    else {
      iVar6 = (*pcVar11)(param_1,1);
    }
    if (iVar6 == 0) {
      if (iVar10 != -1) {
        iVar6 = net_ad_wrap_service(param_1);
        *(int *)(uVar14 * 0xd18 + iVar6 + 0x1118) = iVar10;
      }
      iVar6 = net_ad_wrap_service(param_1);
      *(uint *)(uVar14 * 0xd18 + iVar6 + 0x4e0) = uVar9 | 2;
      pcVar11 = *(code **)(iVar7 + 0xc);
      if (pcVar11 == (code *)0x0) {
        MtATESetMacTxRx(param_1,1,0,uVar14);
        iVar6 = 0x200;
        do {
          mt_ate_enq_pkt(param_1,uVar14,0);
          iVar6 = iVar6 + -1;
        } while (iVar6 != 0);
        iVar6 = MT_ATETxControl(param_1,uVar14,0);
        MtATESetMacTxRx(param_1,1,1,uVar14);
      }
      else {
        iVar6 = (*pcVar11)();
      }
      if (iVar6 == 0) {
        *(undefined1 *)(param_1 + 0xa3b8bb) = 1;
        return 0;
      }
    }
  }
  if (-1 < DebugLevel) {
    printk("%s: Err %d, wdev_idx:%x\n","MT_ATEStartTxSKB",iVar6,(int)cVar4);
  }
  return iVar6;
}

