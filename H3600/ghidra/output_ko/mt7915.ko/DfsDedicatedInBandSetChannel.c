// module: mt7915.ko
// function: DfsDedicatedInBandSetChannel @ 0x236458
// size: 1048 bytes
//

void DfsDedicatedInBandSetChannel(int param_1,uint param_2,uint param_3,int param_4,byte param_5)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  undefined1 uVar4;
  byte bVar5;
  undefined1 uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  uint local_44;
  uint local_2c [2];
  
  uVar10 = (uint)param_5;
  local_2c[0] = 0;
  if (2 < DebugLevel) {
    printk(&_LC146,"DfsDedicatedInBandSetChannel",uVar10,param_2,param_3);
  }
  iVar8 = param_1 + 0x795000;
  if (*(char *)(param_1 + 0x7953fa) == '\0') {
    if (DebugLevel < 0) {
      return;
    }
    printk("[%s] DedicatedZeroWaitSupport is not enabled\n","DfsDedicatedInBandSetChannel");
    return;
  }
  iVar2 = DfsDedicatedCheckChBwValid(param_1,param_2,param_3,uVar10);
  iVar9 = DebugLevel;
  if (iVar2 == 0) {
    if (DebugLevel < 1) {
      return;
    }
    printk(&_LC148,"DfsDedicatedInBandSetChannel");
    return;
  }
  if (param_2 == 0) {
    local_44 = (uint)*(byte *)(param_1 + 0x7953fc);
    param_2 = (uint)*(byte *)(param_1 + 0x7953fb);
  }
  else {
    local_44 = param_3;
    if ((*(byte *)(param_1 + 0x7953fb) != param_2) || (*(byte *)(param_1 + 0x7953fc) != param_3)) {
      *(undefined1 *)(param_1 + 0x795403) = 1;
      if (0 < iVar9) {
        printk("InBand set to non-OutBand Channel %d, Bw %d\n",param_2,param_3);
      }
      goto LAB_002364f4;
    }
  }
  if (0 < DebugLevel) {
    printk("InBand set to OutBand Channel %d, Bw :%d\n",param_2,local_44);
  }
LAB_002364f4:
  bVar5 = *(byte *)(iVar8 + uVar10 + 0x130);
  if ((bVar5 == param_2) && (*(byte *)(iVar8 + uVar10 + 0x134) == local_44)) {
    if (0 < DebugLevel) {
      printk(&_LC151,param_2,local_44);
    }
    if ((param_4 == 0) && (iVar8 = param_1 + uVar10 * 0x20, *(char *)(iVar8 + 0xa37728) == '\x02'))
    {
      if (0 < DebugLevel) {
        printk(&_LC152);
      }
      *(undefined2 *)(iVar8 + 0xa37726) = *(undefined2 *)(param_1 + uVar10 * 0x20 + 0xa3772c);
    }
  }
  else {
    if (param_4 == 0) {
      *(undefined1 *)(param_1 + 0x795403) = 0;
      *(undefined1 *)(param_1 + 0x795402) = 1;
      bVar5 = *(byte *)(iVar8 + uVar10 + 0x130);
    }
    *(byte *)(param_1 + 0x7953fd) = bVar5;
    *(undefined1 *)(param_1 + 0x7953fe) = *(undefined1 *)(iVar8 + uVar10 + 0x134);
    *(char *)(iVar8 + uVar10 + 0x130) = (char)param_2;
    *(char *)(param_1 + 0x795132) = (char)param_2;
    *(byte *)(param_1 + 0x795133) = param_5;
    if ("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
        [param_1 + 0xda] != '\0') {
      uVar7 = 0;
      do {
        local_2c[0] = 0;
        iVar9 = param_1 + uVar7 * 0x5834;
        if (*(int *)(
                    "Wrong format, vow_watf_q=[Level]-[Quantum]\n[Level] should be among 0 to 3 !\n[Quantum] unit is 256us.\n"
                    + iVar9 + 0x14) != 0) {
          uVar3 = HcGetBandByWdev("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                  + param_1 + uVar7 * 0x5834 + 0xe0);
          if (uVar3 == uVar10) {
            iVar9 = *(int *)("%u-%02x:%02x:%02x:%02x:%02x:%02x" + iVar9);
            if (*(byte *)(iVar8 + uVar10 + 0x134) != local_44) {
              switch(local_44) {
              case 0:
                uVar6 = 0;
                uVar4 = 0;
                break;
              case 1:
                uVar6 = 0;
                uVar4 = 1;
                break;
              case 2:
                uVar4 = 1;
                uVar6 = uVar4;
                break;
              case 3:
                uVar4 = 1;
                uVar6 = 2;
                break;
              default:
                goto switchD_00236614_default;
              }
              *(undefined1 *)(iVar9 + 0x15) = uVar4;
              *(undefined1 *)(iVar9 + 0x5c) = uVar6;
            }
switchD_00236614_default:
            iVar9 = DebugLevel;
            cVar1 = *(char *)(param_1 + (uVar10 + 0x51bb9) * 0x20 + 8);
            if (cVar1 == '\0') {
              *(undefined1 *)(iVar8 + uVar10 + 0x3e1) = 0;
              *(undefined1 *)(iVar8 + uVar10 + 0x3e4) = 0;
              if (0 < iVar9) {
                printk(&_LC153,"DfsDedicatedInBandSetChannel",param_2,local_44);
              }
              rtmp_set_channel(param_1,"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                       + param_1 + uVar7 * 0x5834 + 0xe0,param_2);
            }
            else if (cVar1 == '\x02') {
              *(undefined1 *)(iVar8 + uVar10 + 0x3e1) = 0;
              *(undefined1 *)(iVar8 + uVar10 + 0x3e4) = 0;
              if (0 < iVar9) {
                printk(&_LC154,"DfsDedicatedInBandSetChannel",param_2,local_44);
              }
              local_2c[0] = uVar10 << 0x10 | local_2c[0] | param_2 | uVar7 << 8;
              RTEnqueueInternalCmd(param_1,0x19,local_2c,4);
              RtmpOsMlmeUp(param_1 + 0x286298);
            }
          }
        }
        uVar7 = uVar7 + 1 & 0xff;
      } while (uVar7 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                             [param_1 + 0xda]);
    }
  }
  return;
}

