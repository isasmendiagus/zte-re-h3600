// module: mt7915.ko
// function: Dot1xIoctlQueryRadiusConf @ 0x114b40
// size: 1288 bytes
//

void Dot1xIoctlQueryRadiusConf(int *param_1,int param_2)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  uint extraout_r1;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  bool bVar11;
  undefined8 uVar12;
  int local_50;
  uint local_4c;
  uint local_48;
  uint local_44;
  uint local_40;
  int local_3c;
  int *local_38;
  int local_34;
  int local_2c [2];
  
  local_38 = &DebugLevel;
  local_4c = (uint)*(byte *)(*param_1 + 0x3c);
  local_44 = *(byte *)((int)param_1 + 0x2b7242) - 1 & 0xff;
  local_34 = param_2;
  if (2 < DebugLevel) {
    printk("%s==>\n","Dot1xIoctlQueryRadiusConf");
  }
  if ((local_4c == 0) && (iVar3 = is_multi_profile_enable(param_1), iVar3 == 1)) {
    iVar3 = multi_profile_get_pf1_num(param_1);
    local_44 = iVar3 - 1U & 0xff;
  }
  if (local_44 < local_4c || (int)(*(byte *)((int)param_1 + 0x2b7242) - 1) < (int)local_4c) {
    if (-1 < *local_38) {
      printk("%s():Invalid MBSSID index(%d)!\n","Dot1xIoctlQueryRadiusConf",local_4c);
    }
    return;
  }
  os_alloc_mem(0,local_2c,0xe79);
  if (local_2c[0] == 0) {
    if (*local_38 < 0) {
      return;
    }
    printk("!!!%s: out of resource!!!\n","Dot1xIoctlQueryRadiusConf");
    return;
  }
  __memzero(local_2c[0],0xe79);
  iVar3 = local_2c[0];
  *(char *)(local_2c[0] + 4) = (char)local_44 + ('\x01' - (char)local_4c);
  *(int *)(local_2c[0] + 5) = param_1[local_4c * 0x160d + 0xaddc9];
  *(int *)(local_2c[0] + 9) = param_1[local_4c * 0x160d + 0xaddca];
  *(int *)(local_2c[0] + 0xd) = param_1[local_4c * 0x160d + 0xaddcb];
  *(int *)(local_2c[0] + 0x11) = param_1[local_4c * 0x160d + 0xaddcc];
  *(int *)(local_2c[0] + 0x15) = param_1[local_4c * 0x160d + 0xaddcd];
  if (local_4c <= local_44) {
    local_50 = 0x5834;
    local_48 = 0;
    uVar9 = local_4c;
    do {
      uVar5 = local_48 & 0xff;
      uVar9 = (uint)(byte)(&DAT_003678c8)[(int)param_1 + (uVar9 & 0xff)];
      local_3c = uVar5 * 8;
      iVar8 = local_50 * uVar9;
      *(undefined1 *)(iVar3 + uVar5 * 0xc4 + 0x239) =
           *(undefined1 *)((int)param_1 + iVar8 + 0x2b776c);
      local_40 = uVar5;
      if (*(char *)((int)param_1 + iVar8 + 0x2b776c) != '\0') {
        uVar7 = 0;
        do {
          iVar4 = uVar7 * 0x49 + iVar8;
          iVar10 = iVar3 + uVar7 * 0x49 + uVar5 * 0xc4;
          if (*(int *)((int)param_1 + (int)("Ac1 --> %uus(%u)\n" + iVar4 + 0xd)) != 0) {
            *(int *)(iVar10 + 0x23a) =
                 *(int *)((int)param_1 + (int)("Ac1 --> %uus(%u)\n" + iVar4 + 0xd));
            *(undefined4 *)(iVar10 + 0x23e) =
                 *(undefined4 *)((int)param_1 + (int)("Ac1 --> %uus(%u)\n" + iVar4 + 0x11));
            *(char *)(iVar10 + 0x282) =
                 *(char *)((int)param_1 +
                          (int)("%s: ************** Group%d **********\n" + iVar4 + 5));
            if (*(byte *)((int)param_1 +
                         (int)("%s: ************** Group%d **********\n" + iVar4 + 5)) != 0) {
              memmove((void *)(iVar10 + 0x242),
                      (char *)((int)param_1 + (int)("Ac2 --> %uus(%u)\n" + iVar4 + 1)),
                      (uint)*(byte *)((int)param_1 +
                                     (int)("%s: ************** Group%d **********\n" + iVar4 + 5)));
            }
          }
          uVar7 = uVar7 + 1 & 0xff;
        } while (uVar7 < *(byte *)((int)param_1 + iVar8 + 0x2b776c));
      }
      iVar4 = local_50 * uVar9;
      iVar8 = (local_3c - local_40) * 0x1c;
      iVar10 = iVar3 + iVar8;
      bVar11 = *(char *)((int)param_1 + iVar4 + 0x2b7808) != '\0';
      *(bool *)(iVar10 + 0x2cc) = bVar11;
      if (bVar11) {
        bVar1 = *(byte *)((int)param_1 + iVar4 + 0x2b73c0);
        *(byte *)(iVar10 + 0x2cd) = bVar1;
        iVar4 = (uint)bVar1 * 0x51 + iVar4;
        bVar1 = *(byte *)((int)param_1 +
                         (int)(
                              "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                              + iVar4 + 0x160));
        if ((bVar1 & 0xf7) == 5) {
          *(byte *)(iVar10 + 0x2ce) = bVar1;
          memmove((void *)(iVar3 + iVar8 + 0x2cf),
                  (char *)((int)param_1 +
                          (int)(
                               "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                               + iVar4 + 0x110)),(uint)bVar1);
        }
      }
      iVar8 = local_50 * uVar9;
      cVar2 = *(char *)((int)param_1 + iVar8 + 0x2b776b);
      if (cVar2 != '\0') {
        iVar4 = iVar3 + (local_3c - local_40) * 0x1c;
        *(char *)(iVar4 + 0x2fc) = cVar2;
        memmove((void *)(iVar4 + 0x2dc),(void *)((int)param_1 + iVar8 + 0x2b775b),
                (uint)*(byte *)((int)param_1 + iVar8 + 0x2b776b));
      }
      iVar8 = local_50 * uVar9;
      cVar2 = *(char *)((int)param_1 + iVar8 + 0x2b7748);
      if (cVar2 != '\0') {
        *(char *)(iVar3 + local_40 + 0x119) = cVar2;
        memmove((void *)(iVar3 + local_40 * 0x10 + 0x19),(void *)((int)param_1 + iVar8 + 0x2b7738),
                (uint)*(byte *)((int)param_1 + iVar8 + 0x2b7748));
      }
      iVar8 = local_50 * uVar9;
      cVar2 = *(char *)((int)param_1 + iVar8 + 0x2b7759);
      if (cVar2 != '\0') {
        *(char *)(iVar3 + local_40 + 0x229) = cVar2;
        memmove((void *)(iVar3 + local_40 * 0x10 + 0x129),(void *)((int)param_1 + iVar8 + 0x2b7749),
                (uint)*(byte *)((int)param_1 + iVar8 + 0x2b7759));
      }
      local_48 = local_48 + 1;
      uVar9 = local_4c + local_48;
    } while ((uVar9 & 0xff) <= local_44);
  }
  *(undefined2 *)(local_34 + 0x14) = 0xe79;
  uVar5 = *(uint *)(local_34 + 0x10);
  uVar6 = *(uint *)(((uint)&local_50 & 0xffffe000) + 8);
  uVar7 = uVar5 + 0xe79;
  uVar9 = uVar7;
  if (uVar5 < 0xfffff187) {
    uVar9 = uVar7 - (uVar6 + 1);
  }
  if (uVar5 < 0xfffff187 && uVar7 <= uVar6) {
    uVar6 = 0;
  }
  if (uVar6 == 0) {
    uVar12 = __copy_to_user(uVar5,iVar3);
    uVar9 = (uint)((ulonglong)uVar12 >> 0x20);
    if ((int)uVar12 == 0) goto LAB_00114ef8;
  }
  if (-1 < *local_38) {
    printk("%s: copy_to_user() fail\n","Dot1xIoctlQueryRadiusConf");
    uVar9 = extraout_r1;
  }
LAB_00114ef8:
  os_free_mem(local_2c[0],uVar9);
  return;
}

