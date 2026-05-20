// module: mt7915.ko
// function: BndStrg_TableInit @ 0x9d59c
// size: 612 bytes
//

undefined4 BndStrg_TableInit(int *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int *piVar1;
  undefined1 uVar2;
  int iVar3;
  int *piVar4;
  char cVar5;
  bool bVar6;
  
  piVar1 = (int *)get_wdev_by_ioctl_idx_and_iftype
                            (param_1,*(undefined1 *)(*param_1 + 0x3c),
                             *(undefined4 *)(*param_1 + 0x38),param_4,param_4);
  if (piVar1 == (int *)0x0) {
    if (DebugLevel < 0) {
      return 9;
    }
    printk("Error in %s(), wdev is NULL!\n","BndStrg_TableInit");
    return 9;
  }
  if ((char *)((int)param_1 +
              (int)(
                   "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                   + param_2 * 0x5834 + 0xe0)) == (char *)0x0) {
    if (DebugLevel < 0) {
      return 9;
    }
    printk("Error in %s(), pMbss is NULL!\n","BndStrg_TableInit");
    return 9;
  }
  if ((*(ushort *)(param_1 + (int)(WtcGetWcidLinkType + param_2 * 0x160d)) & 0xb1) == 0) {
    cVar5 = '\x02';
  }
  else {
    cVar5 = '\x01';
  }
  if (*(char *)((int)param_1 + param_2 * 0x5834 + 0x2b7262) == '\0') {
    if (DebugLevel < 0) {
      return 9;
    }
    printk("%s(),Invalid Channel:%d pMbss apidx:%d\n","BndStrg_TableInit",0,param_2);
    return 9;
  }
  if ((char)param_1[0xdae4a] == '\0') {
    piVar4 = param_1 + 0xdae49;
    if ((char)param_1[0xdb26f] != '\0') goto LAB_0009d750;
    if (piVar4 != (int *)0x0) goto LAB_0009d678;
LAB_0009d664:
    piVar4 = param_1 + 0xdb26e;
  }
  else {
    if (*(char *)((int)param_1 + 0x36c992) == cVar5) {
      return 0;
    }
    if ((char)param_1[0xdb26f] == '\0') goto LAB_0009d664;
    piVar4 = (int *)0x0;
LAB_0009d750:
    if (*(char *)((int)param_1 + 0x36da26) == cVar5) {
      return 0;
    }
  }
  if (piVar4 == (int *)0x0) {
    return 0;
  }
LAB_0009d678:
  __memzero(piVar4,0x1094);
  *(char *)((int)piVar4 + 0x106e) = cVar5;
  piVar4[0x405] = 0;
  BndStrg_SetInfFlags(param_1,piVar4,0);
  piVar4[0x406] = (int)D_BndStrgOps;
  *(undefined1 *)((int)piVar4 + 0x1023) = 0xb0;
  *(undefined1 *)(piVar4 + 0x409) = 0xd8;
  *(undefined1 *)((int)piVar4 + 0x1025) = 0x50;
  piVar4[0x40a] = 150000;
  piVar4[0x40b] = 90000;
  piVar4[0x41c] = 4000;
  uVar2 = 0x1e;
  piVar4[0x40c] = 30000;
  *(undefined1 *)((int)piVar4 + 0x1022) = 0x1e;
  piVar4[3] = 3;
  piVar4[4] = 0x148;
  piVar4[0x422] = 0x1e;
  bVar6 = *(char *)((int)piVar4 + 0x106e) == '\x02';
  *(undefined1 *)(piVar4 + 0x421) = 3;
  *(undefined1 *)(piVar4 + 0x41e) = 0;
  piVar4[0x41f] = 0;
  if (bVar6) {
    uVar2 = 4;
  }
  piVar4[0x420] = 0;
  if (bVar6) {
    *(undefined1 *)((int)piVar4 + 0x108e) = uVar2;
    piVar4[0x424] = 0x4b;
  }
  piVar4[0x407] = (int)param_1;
  iVar3 = *piVar1;
  *(undefined1 *)(piVar4 + 1) = 1;
  *piVar4 = iVar3;
  return 0;
}

