// module: mt7915.ko
// function: WscSendUPnPMessage @ 0x1e210c
// size: 824 bytes
//

undefined4
WscSendUPnPMessage(int param_1,uint param_2,uint param_3,undefined2 param_4,void *param_5,
                  int param_6,int param_7,undefined4 param_8,void *param_9,char param_10)

{
  bool bVar1;
  int iVar2;
  undefined4 *__dest;
  uint uVar3;
  uint __n;
  uint uVar4;
  char *pcVar5;
  undefined4 *puVar6;
  undefined4 *local_50;
  undefined4 local_4a [2];
  undefined4 local_42;
  int local_3e;
  uint local_3a;
  uint local_36;
  undefined4 local_32;
  undefined2 local_2e;
  uint local_2c;
  undefined4 local_28;
  int local_24;
  
  local_50 = (undefined4 *)0x0;
  if (param_9 == (void *)0x0) {
    return 0;
  }
  if ((param_3 & 0x10) == 0) {
    return 0;
  }
  if (param_10 == '\0') {
    if ((param_2 & 0x30) == 0) {
      pcVar5 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
               + param_2 * 0x5834 + param_1 + 0x101;
    }
    else {
      if (1 < (param_2 & 0xcf)) {
        return 0;
      }
      pcVar5 = &DAT_0036db73 + param_1 + (param_2 & 0xcf) * 0x2137b0;
    }
  }
  else {
    if (param_10 != '\x02') goto LAB_001e237c;
    pcVar5 = &DAT_0036db73 + param_1;
  }
  if (pcVar5 != (char *)0x0) {
    uVar3 = param_6 + 0xc;
    __memzero(local_4a,0x2a);
    local_32 = *(undefined4 *)pcVar5;
    local_2e = *(undefined2 *)(pcVar5 + 4);
    local_4a[0] = WSC_MSG_SIGNATURE._0_4_;
    local_4a[1] = WSC_MSG_SIGNATURE._4_4_;
    local_3e = param_7;
    local_42 = jiffies;
    local_3a = uVar3;
    if ((param_3 == 0x12) || (param_3 == 0x13)) {
      local_28 = param_8;
      local_2c = CONCAT22(param_4,(short)param_3);
      local_24 = param_6;
    }
    else {
      if (param_3 != 0x11) {
        return 0;
      }
      local_2c = CONCAT22(param_4,0x11);
      local_28 = param_8;
      local_24 = param_6;
      if ((param_7 == 0) && (iVar2 = memcmp(param_9,&ZERO_MAC_ADDR,6), iVar2 != 0)) {
        local_2c = CONCAT22(param_4,(undefined2)local_2c) | 0x1000000;
        uVar3 = param_6 + 0x12;
        local_24 = param_6 + 6;
        local_3a = uVar3;
      }
    }
    os_alloc_mem(0,&local_50,0xff);
    if (local_50 != (undefined4 *)0x0) {
      if (uVar3 != 0) {
        bVar1 = true;
        do {
          __memzero(local_50,0xff);
          puVar6 = local_50;
          uVar4 = uVar3;
          if (0xe0 < (int)uVar3) {
            uVar4 = 0xe1;
          }
          uVar3 = uVar3 - (uVar4 & 0xffff);
          local_36 = CONCAT22((short)uVar4,(ushort)(0 < (int)uVar3));
          *local_50 = local_4a[0];
          local_50[3] = local_3e;
          local_50[1] = local_4a[1];
          local_50[2] = local_42;
          local_50[6] = local_32;
          local_50[5] = local_36;
          local_50[4] = local_3a;
          *(undefined2 *)(local_50 + 7) = local_2e;
          if (bVar1) {
            __dest = (undefined4 *)((int)local_50 + 0x2a);
            *(uint *)((int)local_50 + 0x1e) = local_2c;
            *(int *)((int)local_50 + 0x26) = local_24;
            *(undefined4 *)((int)local_50 + 0x22) = local_28;
            __n = (uVar4 & 0xffff) - 0xc;
            if ((local_2c & 0x1000000) != 0) {
              __n = (uVar4 & 0xffff) - 0x12;
              memmove(__dest,param_9,6);
              __dest = puVar6 + 0xc;
            }
            memmove(__dest,param_5,__n);
            uVar4 = local_36 >> 0x10;
            puVar6 = local_50;
          }
          else {
            uVar4 = uVar4 & 0xffff;
            memmove((void *)((int)local_50 + 0x1e),param_5,uVar4);
            __n = uVar4;
          }
          param_5 = (void *)((int)param_5 + __n);
          bVar1 = false;
          RtmpOSWrielessEventSend(*(undefined4 *)(param_1 + 4),1,0x109,0,puVar6,uVar4 + 0x1e);
        } while (uVar3 != 0);
      }
      os_free_mem();
    }
    return 1;
  }
LAB_001e237c:
  if (-1 < DebugLevel) {
    printk("pDevAddr == NULL!\n");
  }
  return 0;
}

