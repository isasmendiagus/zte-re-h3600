// module: mt7915.ko
// function: wpf_init @ 0x105e14
// size: 656 bytes
//

void wpf_init(int param_1)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  undefined *puVar4;
  int iVar5;
  undefined *puVar6;
  int *piVar7;
  int *piVar8;
  
  pcVar3 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
           + param_1 + 0xe0;
  iVar5 = 0;
  while( true ) {
    iVar1 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    if (iVar1 <= iVar5) break;
    if (((*(int *)(pcVar3 + 0xb10) == 0) && (*(int *)(pcVar3 + 0xb14) == 0)) &&
       (iVar1 = FUN_00105be0(param_1,pcVar3), iVar1 < 0)) goto LAB_00105e84;
    pcVar3 = pcVar3 + 0x5834;
    iVar5 = iVar5 + 1;
  }
  puVar4 = &DAT_0036db58 + param_1;
  puVar6 = puVar4;
  do {
    if (((*(int *)(puVar6 + 0xb10) == 0) && (*(int *)(puVar6 + 0xb14) == 0)) &&
       (iVar5 = FUN_00105be0(param_1,puVar6), iVar5 < 0)) goto LAB_00105e84;
    puVar6 = puVar6 + 0x2137b0;
  } while (puVar6 != (undefined *)(param_1 + 0x794ab8));
  while (((*(int *)(puVar4 + 0xb10) != 0 || (*(int *)(puVar4 + 0xb14) != 0)) ||
         (iVar5 = FUN_00105be0(param_1,puVar4), -1 < iVar5))) {
    puVar4 = puVar4 + 0x2137b0;
    if ((undefined *)(param_1 + 0x794ab8) == puVar4) {
      if (3 < DebugLevel) {
        printk("%s: acquiring SERVICE wdev_cfg!\n","wpf_init");
      }
      iVar1 = 0;
      iVar5 = 0;
      piVar7 = (int *)(*(int *)(param_1 + 0xa77bb8) + 0x500);
      piVar8 = piVar7;
      do {
        piVar8 = piVar8 + 1;
        iVar2 = *piVar8;
        while( true ) {
          if (iVar2 == 0) {
            os_alloc_mem(param_1,piVar8,0x4060);
            iVar2 = *piVar8;
            if (iVar2 == 0) {
              if (-1 < DebugLevel) {
                printk("%s:[ERROR] SERVICE DBDC/wdev band%d allocate memory failed!\n","wpf_init",
                       iVar1);
              }
            }
            else {
              os_zero_mem(iVar2,0x4060);
              if (((*(int *)(iVar2 + 0xb10) == 0) && (*(int *)(iVar2 + 0xb14) == 0)) &&
                 (iVar2 = FUN_00105be0(param_1,iVar2), iVar2 < 0)) {
                if (-1 < DebugLevel) {
                  printk("%s:[ERROR] wdev_cfg is full!\n","wpf_init");
                }
              }
              else if (3 < DebugLevel) {
                printk("%s:acquiring DBDC/wdev_cfg for band%d!\n","wpf_init",iVar1);
              }
            }
          }
          iVar5 = iVar5 + 4;
          if (iVar5 != 8) break;
          if (iVar1 == 1) {
            return;
          }
          iVar1 = 1;
          piVar8 = piVar7 + 0x347;
          iVar2 = *piVar8;
          iVar5 = 0;
          piVar7 = piVar7 + 0x346;
        }
      } while( true );
    }
  }
LAB_00105e84:
  if (DebugLevel < 0) {
    return;
  }
  printk("%s:[ERROR] wdev_cfg is full!\n","wpf_init");
  return;
}

