// module: mt7915.ko
// function: Dot1xIoctlAddWPAKey @ 0x1151b8
// size: 1112 bytes
//

/* WARNING: Type propagation algorithm not settling */

void Dot1xIoctlAddWPAKey(int *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  void *pvVar3;
  uint uVar4;
  char cVar5;
  uint uVar6;
  size_t __n;
  uint uVar7;
  undefined1 auStack_b0 [4];
  int local_ac [4];
  undefined2 local_9c;
  undefined1 local_9a;
  byte local_99;
  undefined1 auStack_98 [114];
  undefined1 auStack_26 [6];
  
  uVar7 = *(uint *)(*param_1 + 0x3c);
  if (2 < DebugLevel) {
    printk("%s-IF(ra%d)\n","Dot1xIoctlAddWPAKey",uVar7 & 0xff);
  }
  os_alloc_mem(param_1,local_ac,*(undefined2 *)(param_2 + 0x14));
  if (local_ac[0] != 0) {
    uVar4 = (uint)*(ushort *)(param_2 + 0x14);
    uVar6 = *(uint *)(((uint)auStack_b0 & 0xffffe000) + 8);
    if (!CARRY4(*(uint *)(param_2 + 0x10),uVar4) && *(uint *)(param_2 + 0x10) + uVar4 <= uVar6) {
      uVar6 = 0;
    }
    if (uVar6 == 0) {
      iVar1 = __copy_from_user(local_ac[0]);
      if (iVar1 != 0) goto LAB_00115294;
    }
    else if (uVar4 != 0) {
      __memzero(local_ac[0],uVar4);
LAB_00115294:
      if (2 < DebugLevel) {
        printk("%s: copy from user failed\n","Dot1xIoctlAddWPAKey");
      }
      os_free_mem(local_ac[0]);
      return;
    }
    iVar1 = local_ac[0];
    uVar4 = uVar7 & 0xff;
    if ((param_1[uVar4 * 0x160d + 0xadc9d] & 0x10048U) == 0) {
      memset(local_ac + 1,0,0x88);
      if (*(uint *)(iVar1 + 0x10) < 0x11) {
        uVar6 = *(uint *)(iVar1 + 0xc) & 0xfffffff;
        if (uVar6 < 4) {
          if ((int)*(uint *)(iVar1 + 0xc) < 0) {
            *(char *)(param_1 + uVar4 * 0x160d + 0xadd28) = (char)uVar6;
            if (*(uint *)(iVar1 + 0x10) < 0x11) {
              cVar5 = (char)*(uint *)(iVar1 + 0x10);
            }
            else {
              if (-1 < DebugLevel) {
                printk("%s-IF(ra%d) : Key length too long %d\n","Dot1xIoctlAddWPAKey",uVar4);
                iVar1 = local_ac[0];
              }
              cVar5 = '\x10';
              *(undefined4 *)(iVar1 + 0x10) = 0x10;
            }
            iVar2 = uVar6 * 0x51 + uVar4 * 0x5834;
            *(char *)((int)param_1 +
                     (int)(
                          "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                          + iVar2 + 0x160)) = cVar5;
            memmove((char *)((int)param_1 +
                            (int)(
                                 "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                 + iVar2 + 0x110)),(void *)(iVar1 + 0x14),*(size_t *)(iVar1 + 0x10))
            ;
            if (*(int *)(iVar1 + 0x10) == 5) {
              uVar6 = param_1[uVar4 * 0x160d + 0xadd27] | 2;
            }
            else {
              uVar6 = param_1[uVar4 * 0x160d + 0xadd27] | 4;
            }
            param_1[uVar4 * 0x160d + 0xadd27] = uVar6;
            iVar1 = param_1[uVar4 * 0x160d + 0xadefa];
            os_zero_mem(local_ac + 1,0x88);
            local_99 = *(byte *)(param_1 + uVar4 * 0x160d + 0xadd28);
            local_ac[3] = param_1[uVar4 * 0x160d + 0xadd27];
            local_ac[1] = 2;
            local_ac[2] = 0;
            local_9a = (undefined1)uVar7;
            local_9c = (short)iVar1;
            os_move_mem(auStack_26,&BROADCAST_ADDR,6);
            os_move_mem(auStack_98,
                        (char *)((int)param_1 +
                                (int)(
                                     "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                     + (uint)local_99 * 0x51 + uVar4 * 0x5834 + 0x110)),0x51);
            HW_ADDREMOVE_KEYTABLE(param_1,local_ac + 1);
            iVar1 = local_ac[0];
          }
          else {
            iVar2 = MacTableLookup(param_1,iVar1 + 4);
            iVar1 = local_ac[0];
            if (iVar2 != 0) {
              *(char *)(iVar2 + 0x2c8) = (char)uVar6;
              *(char *)(iVar2 + uVar6 * 0x51 + 0x1d0) = (char)*(undefined4 *)(local_ac[0] + 0x10);
              memmove((void *)(iVar2 + 0x17c + uVar6 * 0x51 + 4),(void *)(local_ac[0] + 0x14),
                      *(size_t *)(local_ac[0] + 0x10));
              if (*(int *)(iVar1 + 0x10) == 5) {
                uVar7 = *(uint *)(iVar2 + 0x2c4) | 2;
              }
              else {
                uVar7 = *(uint *)(iVar2 + 0x2c4) | 4;
              }
              *(uint *)(iVar2 + 0x2c4) = uVar7;
              os_zero_mem(local_ac + 1,0x88);
              local_99 = *(byte *)(iVar2 + 0x2c8);
              local_9c = *(undefined2 *)(iVar2 + 0xe0);
              local_9a = *(undefined1 *)(iVar2 + 0xe4);
              local_ac[3] = *(int *)(iVar2 + 0x2c4);
              local_ac[2] = 2;
              local_ac[1] = 0;
              os_move_mem(auStack_26,(void *)(iVar2 + 0xec),6);
              os_move_mem(auStack_98,(void *)(iVar2 + 0x17c + (uint)local_99 * 0x51 + 4),0x51);
              *(undefined1 *)((int)param_1 + (uint)*(ushort *)(iVar2 + 0xe0) * 0x620 + 0x2f762) = 1;
              *(undefined4 *)(iVar2 + 0xadc) = 0;
              WifiSysUpdatePortSecur(param_1,iVar2,local_ac + 1);
              iVar1 = local_ac[0];
            }
          }
        }
      }
    }
    else if (((*(int *)(local_ac[0] + 0x10) - 0x20U & 0xffffffdf) == 0) &&
            (iVar2 = MacTableLookup(param_1,local_ac[0] + 4), iVar1 = local_ac[0], iVar2 != 0)) {
      if ((param_1[uVar4 * 0x160d + 0xadc9d] & 0x10000U) == 0) {
        __n = 0x20;
      }
      else if (*(int *)(local_ac[0] + 0x10) == 0x40) {
        __n = 0x30;
      }
      else {
        __n = 0x20;
      }
      pvVar3 = memmove((void *)((int)param_1 + uVar4 * 0x5834 + 0x2b7402),
                       (void *)(local_ac[0] + 0x14),__n);
      hex_dump(&_LC84,pvVar3,__n);
      iVar1 = local_ac[0];
    }
    os_free_mem(iVar1);
  }
  return;
}

