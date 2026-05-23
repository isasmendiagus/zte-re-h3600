// module: mt7915.ko
// function: Set_AP_WscConfMode_Proc @ 0x318b0
// size: 1416 bytes
//

undefined4 Set_AP_WscConfMode_Proc(int *param_1,undefined4 param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  undefined1 uVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  int *piVar10;
  uint uVar11;
  
  iVar9 = *param_1;
  uVar11 = (uint)*(byte *)(iVar9 + 0x3c);
  uVar8 = os_str_tol(param_2,0,10);
  if (uVar8 != 5) {
    if (*(int *)(iVar9 + 0x38) == 0x400) {
      iVar9 = uVar11 * 0x84dec + 0xdbb8f;
      if (2 < DebugLevel) {
        printk("IF(apcli%d) Set_WscConfMode_Proc:: This command is from apcli interface now.\n",
               uVar11);
      }
      iVar7 = DebugLevel;
      if ((uVar8 & 7) == 0) {
        param_1[uVar11 * 0x84dec + 0xdbb8f] = 0;
        param_1[uVar11 * 0x84dec + 0xdbb92] = 0;
        if (2 < iVar7) {
          printk("IF(apcli%d) Set_WscConfMode_Proc:: WPS is disabled.\n",uVar11);
        }
      }
      else {
        if (uVar8 != 1) {
          if (DebugLevel < 3) {
            return 0;
          }
          printk("IF(apcli%d) Set_WscConfMode_Proc:: Ap Client only supports Enrollee mode.(ConfModeIdx=%d)\n"
                 ,uVar11,uVar8);
          return 0;
        }
        param_1[uVar11 * 0x84dec + 0xdbb8f] = 1;
        WscInit(param_1,1,uVar11);
        param_1[uVar11 * 0x84dec + 0xdbb92] = 1;
      }
      uVar6 = *(undefined1 *)((int)param_1 + uVar11 * 0x2137b0 + 0x36db76);
      uVar5 = *(undefined1 *)((int)param_1 + uVar11 * 0x2137b0 + 0x36db73);
      uVar1 = (undefined1)param_1[uVar11 * 0x84dec + 0xdb6dd];
      uVar2 = *(undefined1 *)((int)param_1 + uVar11 * 0x2137b0 + 0x36db75);
      uVar3 = *(undefined1 *)((int)param_1 + uVar11 * 0x2137b0 + 0x36db77);
      uVar4 = (undefined1)param_1[uVar11 * 0x84dec + 0xdb6de];
    }
    else {
      if (2 < DebugLevel) {
        printk("IF(ra%d) Set_WscConfMode_Proc:: This command is from ra interface now.\n",uVar11);
      }
      iVar9 = DebugLevel;
      if ((uVar8 & 7) == 0) {
        param_1[uVar11 * 0x160d + 0xae14b] = 0;
        param_1[uVar11 * 0x160d + 0xae14e] = 0;
        if (2 < iVar9) {
          printk("IF(ra%d) Set_WscConfMode_Proc:: WPS is disabled.\n",uVar11);
        }
        *(undefined2 *)(param_1 + uVar11 * 0x160d + 0xae04a) = 0;
        *(undefined2 *)((int)param_1 + uVar11 * 0x5834 + 0x2b832a) = 0;
        UpdateBeaconHandler(param_1,(char *)((int)param_1 +
                                            (int)(
                                                 "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                                 + uVar11 * 0x5834 + 0xe0)),2);
      }
      else {
        param_1[uVar11 * 0x160d + 0xae14b] = uVar8 & 7;
        WscInit(param_1,0,uVar11);
        param_1[uVar11 * 0x160d + 0xae14e] = 1;
      }
      iVar9 = uVar11 * 0x160d + 0xae14b;
      uVar1 = *(undefined1 *)((int)param_1 + uVar11 * 0x5834 + 0x2b726a);
      uVar2 = *(undefined1 *)((int)param_1 + uVar11 * 0x5834 + 0x2b726b);
      uVar6 = (undefined1)param_1[uVar11 * 0x160d + 0xadc9b];
      uVar3 = *(undefined1 *)((int)param_1 + uVar11 * 0x5834 + 0x2b726d);
      uVar4 = *(undefined1 *)((int)param_1 + uVar11 * 0x5834 + 0x2b726e);
      uVar5 = *(undefined1 *)((int)param_1 + uVar11 * 0x5834 + 0x2b7269);
    }
    if (DebugLevel < 3) {
      return 1;
    }
    printk("IF(%02x:%02x:%02x:%02x:%02x:%02x) Set_WscConfMode_Proc::(WscConfMode(0~7)=%d)\n",uVar5,
           uVar1,uVar2,uVar6,uVar3,uVar4,param_1[iVar9]);
    return 1;
  }
  if (0 < DebugLevel) {
    printk("WPS is using concurrent WPS now apidx=%d\n",uVar11);
  }
  if (*(char *)((int)param_1 + 0x36da51) == '\x01') {
    if (uVar11 < *(byte *)((int)param_1 + 0x3678f9)) {
      iVar9 = GetAssociatedAPByWdev
                        (param_1,(undefined *)
                                 ((int)param_1 + (int)(&DAT_0036db58 + uVar11 * 0x2137b0)));
      if (((iVar9 == 0) ||
          (param_1[(uint)*(ushort *)(param_1 + uVar11 * 0x84dec + 0x16038e) * 0x530 + 0x28787] != 2)
          ) || (*(char *)((int)param_1 +
                         (uint)*(ushort *)(param_1 + uVar11 * 0x84dec + 0x16038e) * 0x620 + 0x2f762)
                != '\x01')) goto LAB_000319c8;
      *(undefined1 *)((int)param_1 + 0x36da53) = 1;
    }
    else if (*(char *)((int)param_1 + 0x36da53) != '\x01') goto LAB_000319e8;
LAB_00031c64:
    if (DebugLevel < 1) {
      if (*(char *)((int)param_1 + 0x36da52) == '\x01') {
        return 1;
      }
      piVar10 = param_1 + uVar11 * 0x160d + 0xae14b;
      goto LAB_00031a14;
    }
    printk("Diabled the ApClient when using concurrent WPS now.\n");
  }
  else {
LAB_000319c8:
    if (*(char *)((int)param_1 + 0x36da53) == '\x01') goto LAB_00031c64;
    if (((uVar11 < *(byte *)((int)param_1 + 0x3678f9)) &&
        (*(char *)((int)param_1 + uVar11 * 0x2137b0 + 0x580e8d) != '\0')) &&
       ((undefined *)((int)param_1 + (int)(&DAT_0036db58 + uVar11 * 0x2137b0)) != (undefined *)0x0))
    {
      if (0 < DebugLevel) {
        printk("Set_AP_WscConfMode_Proc enter  WscPushConcurrentPBCAction(apcli%d) pWscControl=0x%p\n"
               ,uVar11,param_1 + uVar11 * 0x84dec + 0xdbb8f);
      }
      RTMPZeroMemory((char *)((int)param_1 +
                             (int)(s_format__t_id_task_id_task_prempt_00371a7c +
                                  uVar11 * 0x2137b0 + 0xe)),0x10);
      RTMPMoveMemory((char *)((int)param_1 +
                             (int)(s_format__t_id_task_id_task_prempt_00371a7c +
                                  uVar11 * 0x2137b0 + 0xe)),param_1[uVar11 * 0x84dec + 0xdb6d6],0x10
                    );
      FUN_000316c4(param_1,param_1 + uVar11 * 0x84dec + 0xdbb8f,1);
    }
  }
LAB_000319e8:
  if (*(char *)((int)param_1 + 0x36da52) == '\x01') {
    if (DebugLevel < 1) {
      return 1;
    }
    printk("Disable the AP when using concurrent WPS now\n");
    return 1;
  }
  piVar10 = param_1 + uVar11 * 0x160d + 0xae14b;
  if (0 < DebugLevel) {
    printk("Set_AP_WscConfMode_Proc enter  WscPushConcurrentPBCAction(ra%d)\n",uVar11);
  }
LAB_00031a14:
  FUN_000316c4(param_1,piVar10,0);
  return 1;
}

