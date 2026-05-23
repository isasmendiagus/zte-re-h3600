// module: mt7915.ko
// function: MT_ATEStop @ 0x2823c8
// size: 1844 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int MT_ATEStop(int param_1)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  code *pcVar6;
  int *piVar7;
  int iVar8;
  bool bVar9;
  undefined4 local_30;
  undefined4 local_2c;
  
  iVar4 = *(int *)(param_1 + 0xa39fd8);
  iVar2 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  bVar1 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
          [param_1 + 0xda];
  if (2 < DebugLevel) {
    printk(&_LC65,"MT_ATEStop");
  }
  if ((*(uint *)(param_1 + 0xa3ac14) & 0x101) == 1) {
    if (*(code **)(iVar2 + 0x2d4) != (code *)0x0) {
      (**(code **)(iVar2 + 0x2d4))(param_1);
    }
    uVar5 = *(uint *)(param_1 + 0xa3ac14);
    if ((uVar5 & 0x280) == 0) {
LAB_00282480:
      if ((uVar5 & 0x200) != 0) {
        iVar2 = MtCmdRfTestSwitchMode(param_1,0,0,8);
        iVar3 = 2000;
        do {
          (*_memcpy)(0x66665b0);
          iVar3 = iVar3 + -1;
        } while (iVar3 != 0);
        if (iVar2 != 0) goto LAB_0028274c;
      }
      if (*(char *)(param_1 + 0xa3b8bd) != '\0') {
        if (2 < DebugLevel) {
          printk("Manual Set Frequency Restore\n");
        }
        MtTestModeRestoreCr(param_1,0x81021238);
        MtTestModeRestoreCr(param_1,0x81021234);
        *(undefined1 *)(param_1 + 0xa3b8bd) = 0;
      }
      os_zero_mem(&local_30,8);
      local_2c = local_2c & 0xff000000;
      local_30 = 0x73b86;
      MtATESetRxFilter(param_1,0x73b86,local_2c);
      if (*(char *)(param_1 + 0x79504d) != '\0') {
        local_2c._0_3_ = CONCAT12(1,(undefined2)local_2c);
        MtATESetRxFilter(param_1,local_30,local_2c);
      }
      FUN_0027d3f4(param_1);
      iVar2 = 0;
      do {
        iVar3 = net_ad_wrap_service(param_1);
        iVar3 = iVar2 * 0xd18 + iVar3;
        if (*(int *)(iVar3 + 0x11cc) != 0) {
          os_free_mem();
        }
        bVar9 = iVar2 != 1;
        *(int *)(iVar3 + 0x11bc) = iVar2;
        *(undefined4 *)(iVar3 + 0x11cc) = 0;
        iVar2 = 1;
        *(undefined1 *)(iVar3 + 0x11c4) = 0;
        *(undefined4 *)(iVar3 + 0x11b8) = 0;
        *(undefined4 *)(iVar3 + 0x11c0) = 0;
        *(undefined4 *)(iVar3 + 0x11c8) = 1;
      } while (bVar9);
      piVar7 = (int *)(param_1 + 0xa3abcc);
      do {
        piVar7 = piVar7 + 1;
        if (*piVar7 != 0) {
          RTMPFreeNdisPacket(param_1);
          *piVar7 = 0;
        }
      } while (piVar7 != (int *)(param_1 + 0xa3ac0c));
      if (*(char *)(param_1 + 0x79504d) != '\0') {
        piVar7 = (int *)(param_1 + 0xa3a0a8);
        do {
          piVar7 = piVar7 + 1;
          if (*piVar7 != 0) {
            RTMPFreeNdisPacket(param_1);
            *piVar7 = 0;
          }
        } while (piVar7 != (int *)(param_1 + 0xa3a0e8));
      }
      if (param_1 == -0xa3a014) {
        iVar2 = 0;
LAB_00282644:
        iVar3 = DebugLevel;
        *(undefined1 *)(param_1 + 0xa3a010) = 0;
LAB_00282654:
        if (0 < iVar3) {
          printk("%s: Release thread_idx=%d\n","TESTMODE_TXTHREAD_RELEASE",0);
        }
      }
      else {
        iVar2 = RtmpOSTaskKill();
        if (iVar2 != 1) goto LAB_00282644;
        if (-1 < DebugLevel) {
          printk("kill ATE Tx task failed!\n");
          iVar3 = DebugLevel;
          goto LAB_00282654;
        }
      }
      msleep(2);
      if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7626) {
        *(undefined1 *)(param_1 + 0xa3bae4) = 0;
        if (param_1 == -0xa3bab0) {
          iVar2 = 0;
LAB_002829b8:
          iVar3 = DebugLevel;
          *(undefined1 *)(param_1 + 0xa3baac) = 0;
          *(undefined1 *)(param_1 + 0xa3bae4) = 0;
LAB_002829cc:
          if (0 < iVar3) {
            printk("%s: Release Done\n","TESTMODE_PeriodicThread_RELEASE");
          }
        }
        else {
          iVar2 = RtmpOSTaskKill();
          if (iVar2 != 1) goto LAB_002829b8;
          if (-1 < DebugLevel) {
            printk("kill ATE Periodic task failed!\n");
            iVar3 = DebugLevel;
            goto LAB_002829cc;
          }
        }
        msleep(2);
      }
      pcVar6 = *(code **)(iVar4 + 4);
      if (pcVar6 != (code *)0x0) {
        iVar2 = (*pcVar6)(param_1);
      }
      pcVar6 = *(code **)(iVar4 + 0x14);
      if (pcVar6 != (code *)0x0) {
        iVar4 = (*pcVar6)(param_1);
        iVar2 = iVar2 + iVar4;
      }
      if (iVar2 == 0) {
        iVar2 = mt_ate_release_wdev(param_1,0);
        if ((*(char *)(param_1 + 0x79504d) != '\0') &&
           (iVar2 = mt_ate_release_wdev(param_1,1), *(int *)(param_1 + 0xa3a0a8) != 0)) {
          os_free_mem();
          *(undefined4 *)(param_1 + 0xa3a0a8) = 0;
        }
        NICInitializeAdapter(param_1);
        if (*(char *)(param_1 + 0x795b0d) == '\0') {
          MtATESetMacTxRx(param_1,3,1);
          if (*(char *)(param_1 + 0x79504d) != '\0') {
            MtATESetMacTxRx(param_1,3,1,1);
          }
        }
        else {
          MtATESetMacTxRx(param_1,4,1,0);
          if (*(char *)(param_1 + 0x79504d) != '\0') {
            MtATESetMacTxRx(param_1,4,1,1);
          }
        }
        complete(param_1 + 0xa3ba38);
        *(undefined4 *)(param_1 + 0xa3ac14) = 0x100;
        iVar4 = net_ad_wrap_service(param_1);
        *(undefined4 *)(iVar4 + 0x11f8) = 0x100;
        MtCmdATEModeCtrl(param_1,0);
        RTMPSetTimer(param_1 + 0x82910c,100);
        *(undefined1 *)(param_1 + 0x795071) = *(undefined1 *)(param_1 + 0xa3baf0);
        *(undefined2 *)(&DAT_00794c50 + param_1) = *(undefined2 *)(param_1 + 0xa3baf2);
        APStartUp(param_1,"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                          + param_1 + 0xe0,0);
        _clear_bit(0,*(int *)(*(int *)(param_1 + 4) + 0x240) + 0x50);
        if (*(char *)(param_1 + 0x286285) == '\x01') {
          iVar4 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
          if (iVar4 < (int)(uint)bVar1) {
            hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
          }
          piVar7 = (int *)("%s: Allocate memory fail!!!\n" + param_1 + 0xc);
          iVar4 = 1;
          while( true ) {
            iVar3 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
            iVar8 = iVar4 + 1;
            if (iVar3 <= iVar4) break;
            iVar3 = *piVar7;
            piVar7 = piVar7 + 0x160d;
            iVar4 = iVar8;
            if (iVar3 != 0) {
              _clear_bit(0,*(int *)(iVar3 + 0x240) + 0x50);
            }
          }
        }
        if (iVar2 == 0) {
          return 0;
        }
      }
    }
    else {
      iVar8 = 2000;
      iVar3 = (**(code **)(*(int *)(param_1 + 0xa39fd4) + 0xdc))(param_1,0);
      iVar2 = MtCmdRfTestSwitchMode(param_1,0,0,8);
      iVar2 = iVar2 + iVar3;
      do {
        (*_memcpy)(0x66665b0);
        iVar8 = iVar8 + -1;
      } while (iVar8 != 0);
      if (iVar2 == 0) {
        uVar5 = *(uint *)(param_1 + 0xa3ac14) & 0xfffffd7f;
        *(uint *)(param_1 + 0xa3ac14) = uVar5;
        goto LAB_00282480;
      }
LAB_0028274c:
      if (DebugLevel < 0) goto LAB_00282444;
      printk("%s: RF-test stop fail, ret:%d\n","MT_ATEStop",iVar2);
    }
    if (DebugLevel < 0) goto LAB_00282444;
    printk("%s: if stop fail, ret:%d\n","MT_ATEStop",iVar2);
  }
  else {
    iVar2 = 0;
  }
  if (0 < DebugLevel) {
    printk("%s: ATE has already stopped ret:%d\n","MT_ATEStop",iVar2);
  }
LAB_00282444:
  *(undefined4 *)(param_1 + 0xa3ac14) = 0x100;
  return iVar2;
}

