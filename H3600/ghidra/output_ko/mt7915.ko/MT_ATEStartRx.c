// module: mt7915.ko
// function: MT_ATEStartRx @ 0x280534
// size: 1772 bytes
//

undefined4 MT_ATEStartRx(int param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  code *pcVar10;
  char *pcVar11;
  int iVar12;
  uint uVar13;
  uint uVar14;
  char *pcVar15;
  bool bVar16;
  uint uVar17;
  int *piVar18;
  bool bVar19;
  uint local_30;
  
  iVar9 = *(int *)(param_1 + 0xa39fd8);
  iVar4 = net_ad_wrap_service();
  uVar13 = (uint)*(byte *)(iVar4 + 0x4cc);
  iVar4 = net_ad_wrap_service(param_1);
  local_30 = (uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                         [param_1 + 0xda];
  uVar14 = *(uint *)(uVar13 * 0xd18 + iVar4 + 0x4e0);
  if ((uVar14 & 4) != 0) {
    return 0;
  }
  MtATESetMacTxRx(param_1,6,0,uVar13);
  msleep(0x1e);
  iVar4 = *(int *)(*(int *)(param_1 + 4) + 0x240);
  if (iVar4 == 0) {
    warn_slowpath_null("include/linux/netdevice.h",0xa06);
    printk(&_LC113);
  }
  else {
    _set_bit(0,iVar4 + 0x50);
  }
  if (*(char *)(param_1 + 0x286285) == '\x01') {
    iVar4 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    if (iVar4 < (int)local_30) {
      local_30 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    }
    piVar18 = (int *)("%s: Allocate memory fail!!!\n" + param_1 + 0xc);
    for (iVar4 = 1; iVar12 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0)),
        iVar4 < iVar12; iVar4 = iVar4 + 1) {
      if (*piVar18 != 0) {
        iVar12 = *(int *)(*piVar18 + 0x240);
        if (iVar12 == 0) {
          warn_slowpath_null("include/linux/netdevice.h",0xa06);
          printk(&_LC113);
        }
        else {
          _set_bit(0,iVar12 + 0x50);
        }
      }
      piVar18 = piVar18 + 0x160d;
    }
  }
  *(uint *)(param_1 + 0xa39f84) = *(uint *)(param_1 + 0xa39f84) | 0x800000;
  chip_set_hif_dma(param_1,0,0);
  pcVar10 = *(code **)(iVar9 + 4);
  if (pcVar10 != (code *)0x0) {
    (*pcVar10)(param_1);
  }
  _clear_bit(0,*(int *)(*(int *)(param_1 + 4) + 0x240) + 0x50);
  if (*(char *)(param_1 + 0x286285) == '\x01') {
    iVar4 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    if (iVar4 < (int)local_30) {
      hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    }
    piVar18 = (int *)("%s: Allocate memory fail!!!\n" + param_1 + 0xc);
    iVar4 = 1;
    while( true ) {
      iVar12 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
      iVar5 = iVar4 + 1;
      if (iVar12 <= iVar4) break;
      iVar12 = *piVar18;
      piVar18 = piVar18 + 0x160d;
      iVar4 = iVar5;
      if (iVar12 != 0) {
        _clear_bit(0,*(int *)(iVar12 + 0x240) + 0x50);
      }
    }
  }
  *(uint *)(param_1 + 0xa39f84) = *(uint *)(param_1 + 0xa39f84) & 0xff7fffff;
  if ((uVar14 & 2) != 0) {
    MtATESetMacTxRx(param_1,1,1,uVar13);
  }
  if (*(char *)(param_1 + 0xa3b8b6) == '\x01') {
    *(undefined4 *)(param_1 + 0xa39c58) = 0;
    chip_set_hif_dma(param_1,2,1);
    MtATESetMacTxRx(param_1,6,1,uVar13);
    if (uVar13 != 0) {
      bVar16 = uVar13 == 1;
      goto LAB_002806fc;
    }
  }
  else {
    if (uVar13 != 0) {
      bVar16 = uVar13 == 1;
      bVar19 = *(char *)(param_1 + 0x79504d) != '\0';
      if (bVar19 && bVar16) {
        *(undefined4 *)(param_1 + 0xa3b750) = 0;
        *(undefined4 *)(param_1 + 0xa39c58) = 0;
        chip_set_hif_dma(param_1,2,1);
        MtATESetMacTxRx(param_1,6,1,1);
        bVar16 = bVar19 && bVar16;
      }
      else {
        *(undefined4 *)(param_1 + 0xa39c58) = 0;
        chip_set_hif_dma(param_1,2,1);
        MtATESetMacTxRx(param_1,6,1,uVar13);
      }
LAB_002806fc:
      if (*(char *)(param_1 + 0x79504d) == '\0') {
        bVar16 = false;
      }
      if (bVar16) {
        MtCmdSetPhyCounter(param_1,0,1);
        MtCmdSetPhyCounter(param_1,1,1);
      }
      goto LAB_00280714;
    }
    *(undefined4 *)(param_1 + 0xa3b74c) = 0;
    *(undefined4 *)(param_1 + 0xa39c58) = 0;
    chip_set_hif_dma(param_1,2,1);
    MtATESetMacTxRx(param_1,6,1,0);
  }
  MtCmdSetPhyCounter(param_1,0,0);
  MtCmdSetPhyCounter(param_1,1,0);
LAB_00280714:
  msleep(0x1e);
  iVar4 = net_ad_wrap_service(param_1);
  iVar12 = uVar13 * 0xd18;
  *(uint *)(iVar4 + iVar12 + 0x4e0) = uVar14 | 4;
  iVar4 = net_ad_wrap_service(param_1);
  if (*(char *)(iVar4 + iVar12 + 0x1135) == '\v') {
    iVar4 = net_ad_wrap_service(param_1);
    if (*(int *)(iVar4 + iVar12 + 0x1110) == 0) {
      MtATESetRxMUAid(param_1,uVar13,0xf100);
    }
    else {
      iVar4 = net_ad_wrap_service(param_1);
      MtATESetRxMUAid(param_1,uVar13,*(undefined2 *)(iVar4 + iVar12 + 0x1110));
    }
  }
  else {
    iVar4 = net_ad_wrap_service(param_1);
    if (*(char *)(iVar4 + iVar12 + 0x1135) == '\n') {
      iVar4 = hc_get_chip_dbg(*(undefined4 *)(param_1 + 0xa797a0));
      iVar5 = net_ad_wrap_service(param_1);
      pcVar11 = (char *)(iVar5 + iVar12 + 0xa1c);
      pcVar15 = pcVar11;
      do {
        if (*pcVar15 != '\0') {
          iVar7 = *(int *)(pcVar15 + 0x20);
          iVar6 = net_ad_wrap_service(param_1);
          uVar1 = *(undefined1 *)(iVar6 + iVar12 + 0x113a);
          iVar6 = net_ad_wrap_service(param_1);
          uVar2 = *(undefined1 *)(iVar6 + iVar12 + 0x113c);
          iVar6 = net_ad_wrap_service(param_1);
          FUN_0027ef70(pcVar15,iVar7 + 0xd,uVar1,uVar2,
                       (*(byte *)(iVar6 + iVar12 + 0x1150) & 0x7f) << 1);
        }
        pcVar15 = pcVar15 + 0x6c;
      } while (pcVar15 != (char *)(iVar5 + iVar12 + 0x10dc));
      iVar12 = net_ad_wrap_service(param_1);
      uVar8 = 0;
      uVar17 = 0;
      uVar14 = 0;
      pcVar15 = (char *)(uVar13 * 0xd18 + iVar12 + 0xa1c);
      do {
        if ((*pcVar15 != '\0') && (uVar14 < *(uint *)(pcVar15 + 0x60))) {
          uVar17 = uVar8 & 0xff;
          uVar14 = *(uint *)(pcVar15 + 0x60);
        }
        uVar8 = uVar8 + 1;
        pcVar15 = pcVar15 + 0x6c;
      } while (uVar8 != 0x10);
      iVar12 = net_ad_wrap_service(param_1);
      *(char *)(iVar12 + uVar13 * 0xd18 + 0x10dc) = (char)uVar17;
      iVar12 = net_ad_wrap_service(param_1);
      iVar12 = iVar12 + uVar13 * 0xd18 + uVar17 * 0x6c;
      iVar5 = iVar12 + 0xa1c;
      if (0 < DebugLevel) {
        printk("%s: dominated by user[%d], RU index:%d\n","mt_ate_dominate_ru",uVar17,
               *(uint *)(iVar12 + 0xa28) >> 1);
      }
      if ((iVar5 != 0) && (pcVar10 = *(code **)(iVar4 + 0x9c), pcVar10 != (code *)0x0)) {
        iVar4 = net_ad_wrap_service(param_1);
        iVar12 = uVar13 * 0xd18;
        uVar1 = *(undefined1 *)(iVar4 + iVar12 + 0x1137);
        iVar4 = net_ad_wrap_service(param_1);
        uVar2 = *(undefined1 *)(iVar4 + iVar12 + 0x113c);
        iVar4 = net_ad_wrap_service(param_1);
        uVar3 = *(undefined1 *)(iVar4 + iVar12 + 0x113a);
        iVar4 = net_ad_wrap_service(param_1);
        (*pcVar10)(param_1,uVar13,1,uVar1,uVar2,uVar3,*(undefined4 *)(iVar4 + iVar12 + 0x1158),
                   *(undefined4 *)(iVar4 + iVar12 + 0x115c),iVar5,pcVar11);
      }
    }
  }
  pcVar10 = *(code **)(iVar9 + 0x10);
  if (pcVar10 != (code *)0x0) {
    (*pcVar10)(param_1);
  }
  *(undefined1 *)(param_1 + 0xa3b8bc) = 1;
  return 0;
}

