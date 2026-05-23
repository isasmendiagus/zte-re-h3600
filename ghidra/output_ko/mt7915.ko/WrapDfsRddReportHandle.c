// module: mt7915.ko
// function: WrapDfsRddReportHandle @ 0x238190
// size: 1468 bytes
//

void WrapDfsRddReportHandle(int param_1,int param_2)

{
  char cVar1;
  char cVar2;
  undefined1 uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  undefined1 uVar7;
  undefined4 uVar8;
  uint uVar9;
  char cVar10;
  uint uVar11;
  int iVar12;
  int iVar13;
  char local_2e [2];
  uint local_2c [2];
  
  local_2c[0] = 0;
  if ((0 < DebugLevel) &&
     (printk("[%s]:  Radar detected !!!!!!!!!!!!!!!!!\n","WrapDfsRddReportHandle"), 0 < DebugLevel))
  {
    printk("[%s]:  ucRddIdx: %d\n","WrapDfsRddReportHandle",param_2);
  }
  iVar12 = param_1 + 0x795000;
  if (*(char *)(param_1 + 0x7953ee) == '\0') {
    uVar4 = dfs_rddidx_to_dbdc(param_1,param_2);
    iVar13 = 0;
    if (uVar4 < 2) {
      iVar5 = param_1 + (uVar4 + 0x51bb9) * 0x20;
      iVar13 = iVar5 + 4;
      *(undefined1 *)(iVar12 + uVar4 * 0x20 + 0x2f0) = *(undefined1 *)(iVar5 + 8);
    }
    iVar5 = DfsRddReportHandle(param_1,param_1 + 0x795130,param_2,uVar4);
    if (iVar5 != 0) {
      if ((((*(char *)(param_1 + 0x7953fa) != '\x01') || (*(char *)(param_1 + 0x7953e6) != '\x01'))
          && (iVar13 != 0)) && (*(char *)(iVar13 + 4) == '\x02')) {
        *(undefined2 *)(iVar13 + 2) = 0;
      }
      WrapDfsSetNonOccupancy(param_1,uVar4);
      if (*(char *)(param_1 + 0x7953fa) == '\x01') {
        if (*(char *)(param_1 + 0x7953e6) == '\x01') {
          if (0 < DebugLevel) {
            printk("RDD%d detect. Please switch to another outBand channel\n",2);
          }
          ZeroWait_DFS_collision_report
                    (param_1,2,*(undefined1 *)(param_1 + 0x7953fb),
                     *(undefined1 *)(param_1 + 0x7953fc));
          iVar12 = DebugLevel;
          if (*(char *)(param_1 + 0x795404) != '\0') {
            if (*(int *)(param_1 + 0x79540c) == 2) {
              *(undefined4 *)(param_1 + 0x79540c) = 0;
              if (2 < iVar12) {
                printk("%s(): ch_stat %d\n","WrapDfsRddReportHandle");
              }
            }
            else {
              if (2 < DebugLevel) {
                printk("%s(): ch_stat %d\n","WrapDfsRddReportHandle");
              }
              MlmeEnqueue(param_1,0x2b,7,0,0,0);
              RtmpOsMlmeUp(param_1 + 0x286298);
            }
          }
          *(undefined1 *)(param_1 + 0x7953e6) = 0;
          return;
        }
        if ((*(char *)(iVar12 + param_2 + 0x3e4) == '\x01') && (*(int *)(param_1 + 0xa79184) == 2))
        {
          if (0 < DebugLevel) {
            printk("RDD%d detect. OutBand channel come back to InBand\n",param_2);
          }
          *(undefined1 *)(param_1 + 0x7953fd) = *(undefined1 *)(iVar12 + uVar4 + 0x130);
          uVar7 = *(undefined1 *)(iVar12 + uVar4 + 0x134);
          *(undefined1 *)(param_1 + 0x795408) = 1;
          *(undefined1 *)(param_1 + 0x7953fe) = uVar7;
        }
      }
      cVar1 = *(char *)(iVar12 + uVar4 + 0x134);
      WrapDfsSelectChannel(param_1,uVar4);
      if (0 < DebugLevel) {
        printk("[%s]PrimCh: %d, Band0Ch:%d, Band1Ch:%d\n","WrapDfsRddReportHandle",
               *(undefined1 *)(param_1 + 0x795132),*(undefined1 *)(param_1 + 0x795130),
               *(undefined1 *)(param_1 + 0x795131));
      }
      uVar9 = (uint)*(byte *)(param_1 + 0x795132);
      uVar11 = 0;
      local_2e[0] = '\0';
      local_2e[1] = 0;
      if ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
          [param_1 + 0xda] != '\0') {
        do {
          local_2c[0] = 0;
          if (((*(int *)(
                        "Wrong format, vow_watf_q=[Level]-[Quantum]\n[Level] should be among 0 to 3 !\n[Quantum] unit is 256us.\n"
                        + param_1 + uVar11 * 0x5834 + 0x14) != 0) &&
              (uVar6 = HcGetBandByWdev("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                       + param_1 + uVar11 * 0x5834 + 0xe0), uVar6 == uVar4)) &&
             (local_2e[uVar4] != '\x01')) {
            local_2e[uVar4] = '\x01';
            if (0 < DebugLevel) {
              printk("[%s]Update wdev of BssIdx %d\n","WrapDfsRddReportHandle",uVar11);
            }
            if ((*(char *)(param_1 + 0x7953fa) == '\x01') && (*(int *)(param_1 + 0xa79184) == 2)) {
              cVar10 = *(char *)(iVar12 + uVar4 + 0x134);
              cVar2 = *(char *)(param_1 + 0x7953fc);
              iVar5 = *(int *)("%u-%02x:%02x:%02x:%02x:%02x:%02x" + uVar11 * 0x5834 + param_1);
              if (cVar10 != cVar2) {
                cVar10 = cVar2;
                switch(cVar2) {
                case '\0':
                  uVar3 = 0;
                  uVar7 = 0;
                  break;
                case '\x01':
                  uVar3 = 0;
                  uVar7 = 1;
                  break;
                case '\x02':
                  uVar3 = 1;
                  uVar7 = 1;
                  break;
                case '\x03':
                  uVar3 = 2;
                  uVar7 = 1;
                  break;
                default:
                  goto switchD_00238398_default;
                }
                *(undefined1 *)(iVar5 + 0x15) = uVar7;
                *(undefined1 *)(iVar5 + 0x5c) = uVar3;
                cVar10 = *(char *)(param_1 + 0x7953fc);
              }
            }
            else {
              cVar2 = *(char *)(iVar12 + uVar4 + 0x134);
              iVar5 = *(int *)("%u-%02x:%02x:%02x:%02x:%02x:%02x" + uVar11 * 0x5834 + param_1);
              cVar10 = cVar1;
              if (cVar1 != cVar2) {
                cVar10 = cVar2;
                switch(cVar2) {
                case '\0':
                  uVar7 = 0;
                  uVar3 = 0;
                  break;
                case '\x01':
                  uVar7 = 0;
                  uVar3 = 1;
                  break;
                case '\x02':
                  uVar3 = 1;
                  uVar7 = uVar3;
                  break;
                case '\x03':
                  uVar3 = 1;
                  uVar7 = 2;
                  break;
                default:
                  goto switchD_00238398_default;
                }
                *(undefined1 *)(iVar5 + 0x15) = uVar3;
                *(undefined1 *)(iVar5 + 0x5c) = uVar7;
                cVar10 = *(char *)(iVar12 + uVar4 + 0x134);
              }
            }
switchD_00238398_default:
            iVar5 = DebugLevel;
            if (iVar13 != 0 &&
                "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                [uVar11 * 0x5834 + param_1 + 0x108] != '\0') {
              if (*(char *)(iVar13 + 4) == '\0') {
                *(undefined1 *)(iVar12 + param_2 + 0x3e1) = 0;
                *(undefined1 *)(iVar12 + param_2 + 0x3e4) = 0;
                if (0 < iVar5) {
                  printk(&_LC153,"WrapDfsRddReportHandle",uVar9,cVar10);
                }
                DedicatedZeroWaitStop(param_1,0);
                uVar8 = 0x1b;
              }
              else {
                if (*(char *)(iVar13 + 4) != '\x02') goto LAB_002382dc;
                *(undefined1 *)(iVar12 + param_2 + 0x3e1) = 0;
                *(undefined1 *)(iVar12 + param_2 + 0x3e4) = 0;
                if (0 < iVar5) {
                  printk(&_LC154,"WrapDfsRddReportHandle",uVar9,cVar10);
                }
                uVar8 = 0x19;
              }
              local_2c[0] = uVar9 | local_2c[0] | uVar4 << 0x10 | uVar11 << 8;
              RTEnqueueInternalCmd(param_1,uVar8,local_2c,4);
              RtmpOsMlmeUp(param_1 + 0x286298);
            }
          }
LAB_002382dc:
          uVar11 = uVar11 + 1 & 0xff;
        } while (uVar11 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                [param_1 + 0xda]);
      }
    }
  }
  return;
}

