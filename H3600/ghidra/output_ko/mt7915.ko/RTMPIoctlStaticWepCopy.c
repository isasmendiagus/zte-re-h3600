// module: mt7915.ko
// function: RTMPIoctlStaticWepCopy @ 0x37bd0
// size: 504 bytes
//

void RTMPIoctlStaticWepCopy(int *param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  undefined1 auStack_a8 [2];
  undefined1 auStack_a6 [6];
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined2 local_94;
  undefined1 local_92;
  undefined1 local_91;
  undefined1 auStack_1e [10];
  
  uVar3 = *(uint *)(*param_1 + 0x3c);
  memset(&local_a0,0,0x88);
  if (2 < DebugLevel) {
    printk("RTMPIoctlStaticWepCopy-IF(ra%d)\n",uVar3 & 0xff);
  }
  if (*(short *)(param_2 + 0x14) == 6) {
    uVar4 = *(uint *)(param_2 + 0x10);
    uVar2 = *(uint *)(((uint)auStack_a8 & 0xffffe000) + 8);
    if (uVar4 < 0xfffffffa && uVar4 + 6 <= uVar2) {
      uVar2 = 0;
    }
    if (uVar2 == 0) {
      __copy_from_user(auStack_a6,uVar4);
    }
    else {
      __memzero(auStack_a6,6);
    }
    iVar1 = MacTableLookup(param_1,auStack_a6);
    if (iVar1 == 0) {
      if (-1 < DebugLevel) {
        printk("RTMPIoctlStaticWepCopy: the mac address isn\'t match\n");
      }
    }
    else {
      uVar3 = uVar3 & 0xff;
      if (*(char *)((int)param_1 +
                   (int)(
                        "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                        + (uint)*(byte *)(param_1 + uVar3 * 0x160d + 0xadcf0) * 0x51 +
                          uVar3 * 0x5834 + 0x160)) == '\0') {
        if (-1 < DebugLevel) {
          printk("ERROR: Can not get Default shared-key (index-%d)\n");
        }
      }
      else {
        *(int *)(iVar1 + 0x17c) = param_1[uVar3 * 0x160d + 0xadc9d];
        *(int *)(iVar1 + 0x2c4) = param_1[uVar3 * 0x160d + 0xadcef];
        *(char *)(iVar1 + 0x2c8) = (char)param_1[uVar3 * 0x160d + 0xadcf0];
        memmove((void *)(iVar1 + 0x180),param_1 + uVar3 * 0x160d + 0xadc9e,0x144);
        os_zero_mem(&local_a0,0x88);
        local_94 = *(undefined2 *)(iVar1 + 0xe0);
        local_92 = *(undefined1 *)(iVar1 + 0xe4);
        local_98 = *(undefined4 *)(iVar1 + 0x2c4);
        local_91 = *(undefined1 *)(iVar1 + 0x2c8);
        local_a0 = 0;
        local_9c = 2;
        os_move_mem(auStack_1e,(void *)(iVar1 + 0xec),6);
        HW_ADDREMOVE_KEYTABLE(param_1,&local_a0);
      }
    }
  }
  else if (-1 < DebugLevel) {
    printk("RTMPIoctlStaticWepCopy: the length isn\'t match (%d)\n",*(short *)(param_2 + 0x14));
  }
  return;
}

