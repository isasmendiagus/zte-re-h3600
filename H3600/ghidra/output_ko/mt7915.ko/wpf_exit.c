// module: mt7915.ko
// function: wpf_exit @ 0x1060a4
// size: 728 bytes
//

void wpf_exit(int param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  undefined *puVar2;
  int iVar3;
  int iVar4;
  char cVar5;
  int *piVar6;
  int iVar7;
  int *piVar8;
  int iVar9;
  char *pcVar10;
  
  cVar5 = *(char *)(param_1 + 0x286285);
  if (cVar5 == '\x01') {
    pcVar10 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
              + param_1 + 0xe0;
    iVar9 = 0;
    iVar7 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    if (0 < iVar7) {
      do {
        if (*(int *)(pcVar10 + 0xb10) == 0) {
          iVar7 = 0;
          if (*(int *)(pcVar10 + 0xb14) != 0) goto LAB_00106264;
        }
        else {
          iVar7 = 0;
LAB_00106264:
          do {
            iVar3 = iVar7 * 0x10;
            iVar7 = iVar7 + 1;
            if (pcVar10 == *(char **)(param_1 + iVar3 + 0xa7c55c)) {
              *(undefined4 *)(param_1 + iVar3 + 0xa7c55c) = 0;
              break;
            }
          } while (iVar7 != 0x68);
          pcVar10[0xb10] = '\0';
          pcVar10[0xb11] = '\0';
          pcVar10[0xb12] = '\0';
          pcVar10[0xb13] = '\0';
          pcVar10[0xb14] = '\0';
          pcVar10[0xb15] = '\0';
          pcVar10[0xb16] = '\0';
          pcVar10[0xb17] = '\0';
        }
        iVar9 = iVar9 + 1;
        iVar7 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
        pcVar10 = pcVar10 + 0x5834;
      } while (iVar9 < iVar7);
    }
    puVar2 = &DAT_0036db58 + param_1;
    do {
      if (*(int *)(puVar2 + 0xb10) == 0) {
        param_3 = 0;
        if (*(int *)(puVar2 + 0xb14) != 0) goto LAB_001062ec;
        param_3 = 0;
      }
      else {
        param_3 = 0;
LAB_001062ec:
        do {
          iVar7 = param_3 * 0x10;
          param_3 = param_3 + 1;
          if (puVar2 == *(undefined **)(param_1 + iVar7 + 0xa7c55c)) {
            *(undefined4 *)(param_1 + iVar7 + 0xa7c55c) = 0;
            break;
          }
        } while (param_3 != 0x68);
        *(undefined4 *)(puVar2 + 0xb10) = 0;
        *(undefined4 *)(puVar2 + 0xb14) = 0;
      }
      puVar2 = puVar2 + 0x2137b0;
    } while (puVar2 != (undefined *)(param_1 + 0x794ab8));
    cVar5 = *(char *)(param_1 + 0x286285);
  }
  if (cVar5 == '\0') {
    puVar2 = &DAT_0036db58 + param_1;
    do {
      if (*(int *)(puVar2 + 0xb10) == 0) {
        param_3 = 0;
        if (*(int *)(puVar2 + 0xb14) != 0) goto LAB_00106108;
        param_3 = 0;
      }
      else {
        param_3 = 0;
LAB_00106108:
        do {
          iVar7 = param_3 * 0x10;
          param_3 = param_3 + 1;
          if (puVar2 == *(undefined **)(param_1 + iVar7 + 0xa7c55c)) {
            *(undefined4 *)(param_1 + iVar7 + 0xa7c55c) = 0;
            break;
          }
        } while (param_3 != 0x68);
        *(undefined4 *)(puVar2 + 0xb10) = 0;
        *(undefined4 *)(puVar2 + 0xb14) = 0;
      }
      puVar2 = puVar2 + 0x2137b0;
    } while (puVar2 != (undefined *)(param_1 + 0x794ab8));
  }
  if (3 < DebugLevel) {
    printk("%s: releasing SERVICE wdev_cfg!\n","wpf_exit",param_3,DebugLevel,param_4);
  }
  iVar7 = *(int *)(param_1 + 0xa77bb8);
  piVar8 = (int *)(iVar7 + 0x500);
  do {
    iVar9 = 0;
    piVar6 = piVar8;
    do {
      piVar6 = piVar6 + 1;
      iVar3 = *piVar6;
      if (iVar3 != 0) {
        if (*(int *)(iVar3 + 0xb10) == 0) {
          iVar4 = 0;
          if (*(int *)(iVar3 + 0xb14) != 0) goto LAB_001061ac;
        }
        else {
          iVar4 = 0;
LAB_001061ac:
          do {
            iVar1 = iVar4 * 0x10;
            iVar4 = iVar4 + 1;
            if (iVar3 == *(int *)(param_1 + iVar1 + 0xa7c55c)) {
              *(undefined4 *)(param_1 + iVar1 + 0xa7c55c) = 0;
              break;
            }
          } while (iVar4 != 0x68);
          *(undefined4 *)(iVar3 + 0xb10) = 0;
          *(undefined4 *)(iVar3 + 0xb14) = 0;
          iVar3 = *piVar6;
        }
        os_free_mem(iVar3);
        *piVar6 = 0;
      }
      iVar9 = iVar9 + 4;
    } while (iVar9 != 8);
    piVar8 = piVar8 + 0x346;
    if (piVar8 == (int *)(iVar7 + 0x1f30)) {
      return;
    }
  } while( true );
}

