// module: mt7915.ko
// function: ap_ieee_802_11_data_tx @ 0x1c8a8
// size: 1692 bytes
//

void ap_ieee_802_11_data_tx(int param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  char cVar1;
  int iVar2;
  int iVar3;
  ushort *puVar4;
  uint uVar5;
  byte bVar6;
  int *piVar7;
  undefined4 *puVar8;
  int iVar9;
  void *__dest;
  undefined6 *__src;
  uint uVar10;
  byte *pbVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  iVar3 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  iVar12 = *(int *)(param_3 + 0x58);
  iVar13 = *(int *)(param_3 + 8);
  iVar14 = *(int *)(param_3 + 0x10);
  uVar10 = (uint)*(byte *)(iVar3 + 2);
  *(undefined1 *)(param_3 + 0x35) = 0x18;
  iVar3 = iVar12 + uVar10;
  *(undefined1 *)(param_3 + 0x2c) = 0x18;
  *(int *)(param_3 + 0x5c) = iVar3;
  __memzero(iVar3,0x18);
  *(byte *)(iVar3 + 1) = *(byte *)(iVar3 + 1) | 2;
  bVar6 = *(byte *)(iVar12 + uVar10);
  *(byte *)(iVar12 + uVar10) = bVar6 & 0xf3 | 8;
  if ((*(uint *)(param_3 + 0x18) & 0x10) == 0) {
    cVar1 = '\0';
  }
  else {
    cVar1 = '\b';
  }
  *(byte *)(iVar12 + uVar10) = bVar6 & 3 | 8 | cVar1 << 4;
  if (iVar13 == 0) {
    puVar4 = (ushort *)(param_1 + 0xa39f90);
    *(byte *)(iVar3 + 0x16) = *(byte *)(iVar3 + 0x16) & 0xf | *(char *)(param_1 + 0xa39f90) << 4;
    *(char *)(iVar3 + 0x17) = (char)(((uint)*puVar4 << 0x14) >> 0x18);
    *puVar4 = *puVar4 + 1 & 0xfff;
  }
  else if ((*(uint *)(param_3 + 0x18) & 0x10) == 0) {
    *(byte *)(iVar3 + 0x16) = *(byte *)(iVar3 + 0x16) & 0xf | *(char *)(iVar13 + 0x12) << 4;
    *(char *)(iVar3 + 0x17) = (char)(((uint)*(ushort *)(iVar13 + 0x12) << 0x14) >> 0x18);
    *(ushort *)(iVar13 + 0x12) = *(short *)(iVar13 + 0x12) + 1U & 0xfff;
  }
  else {
    iVar9 = iVar13 + (*(byte *)(param_3 + 0x1c) + 8) * 2;
    *(byte *)(iVar3 + 0x16) = *(byte *)(iVar3 + 0x16) & 0xf | *(char *)(iVar9 + 4) << 4;
    *(char *)(iVar3 + 0x17) = (char)(((uint)*(ushort *)(iVar9 + 4) << 0x14) >> 0x18);
    iVar13 = iVar13 + (uint)*(byte *)(param_3 + 0x1c) * 2;
    *(ushort *)(iVar13 + 0x14) = *(short *)(iVar13 + 0x14) + 1U & 0xfff;
  }
  *(byte *)(iVar3 + 0x16) = *(byte *)(iVar3 + 0x16) & 0xf0;
  *(byte *)(iVar3 + 1) =
       *(byte *)(iVar3 + 1) & 0xdf | (byte)(((uint)(*(int *)(param_3 + 0x18) << 0x19) >> 0x1f) << 5)
  ;
  uVar5 = *(uint *)(param_3 + 0x18) & 0x8000000;
  if (uVar5 == 0) {
    if ((*(uint *)(param_3 + 0x18) & 0x200) == 0) {
      if ((*(int **)(param_3 + 8) == (int *)0x0) || (**(int **)(param_3 + 8) == 0x400)) {
        puVar8 = *(undefined4 **)(param_3 + 0x24);
        *(undefined4 *)(iVar3 + 4) = *puVar8;
        *(undefined2 *)(iVar3 + 8) = *(undefined2 *)(puVar8 + 1);
      }
      else {
        iVar13 = *(int *)(param_3 + 0x14);
        *(undefined4 *)(iVar3 + 4) = *(undefined4 *)(iVar13 + 0xec);
        *(undefined2 *)(iVar3 + 8) = *(undefined2 *)(iVar13 + 0xf0);
      }
      iVar13 = (uint)*(byte *)(iVar14 + 0xe) * 0x5834 + param_1;
      *(undefined4 *)(iVar3 + 10) =
           *(undefined4 *)
            (
            "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
            + iVar13 + 0x101);
      *(undefined2 *)(iVar3 + 0xe) =
           *(undefined2 *)
            (
            "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
            + iVar13 + 0x105);
      iVar13 = *(int *)(param_3 + 0x24);
      *(undefined4 *)(iVar3 + 0x10) = *(undefined4 *)(iVar13 + 6);
      *(undefined2 *)(iVar3 + 0x14) = *(undefined2 *)(iVar13 + 10);
    }
    else {
      *(byte *)(iVar3 + 1) = *(byte *)(iVar3 + 1) & 0xfd | 1;
      if ((*(uint *)(param_3 + 0x18) & 0x80000) == 0) {
        iVar13 = (uint)*(ushort *)(param_3 + 0x1e) * 0x14c0 + param_1;
        *(undefined4 *)(iVar3 + 4) = *(undefined4 *)(iVar13 + 0xa1e0c);
        *(undefined2 *)(iVar3 + 8) = *(undefined2 *)(iVar13 + 0xa1e10);
      }
      else {
        *(byte *)(iVar3 + 1) = *(byte *)(iVar3 + 1) | 2;
      }
      if (((*(int *)(param_3 + 0x14) == 0) ||
          (iVar13 = *(int *)(*(int *)(param_3 + 0x14) + 0xafc), iVar13 == 0)) ||
         (*(char *)(iVar13 + 5) != '\x02')) {
        iVar13 = *(int *)(param_3 + 0x74);
        *(undefined4 *)(iVar3 + 10) = *(undefined4 *)(iVar13 + 0x1b);
        *(undefined2 *)(iVar3 + 0xe) = *(undefined2 *)(iVar13 + 0x1f);
      }
      else {
        *(undefined4 *)(iVar3 + 10) = *(undefined4 *)(iVar13 + 0x83);
        *(undefined2 *)(iVar3 + 0xe) = *(undefined2 *)(iVar13 + 0x87);
      }
      if ((*(uint *)(param_3 + 0x18) & 0x80000) != 0) {
        iVar13 = *(int *)(param_3 + 0x24);
        *(undefined4 *)(iVar3 + 0x18) = *(undefined4 *)(iVar13 + 6);
        *(undefined2 *)(iVar3 + 0x1c) = *(undefined2 *)(iVar13 + 10);
        *(char *)(param_3 + 0x35) = *(char *)(param_3 + 0x35) + '\x06';
      }
      puVar8 = *(undefined4 **)(param_3 + 0x24);
      *(undefined4 *)(iVar3 + 0x10) = *puVar8;
      *(undefined2 *)(iVar3 + 0x14) = *(undefined2 *)(puVar8 + 1);
    }
  }
  else {
    *(byte *)(iVar3 + 1) = *(byte *)(iVar3 + 1) | 3;
    piVar7 = *(int **)(param_3 + 0x14);
    if (piVar7 == (int *)0x0) {
      if (-1 < DebugLevel) {
        printk("%s pTxBlk->pMacEntry == NULL!\n","ap_build_802_11_header",uVar5,DebugLevel,param_4);
      }
    }
    else {
      if (*piVar7 == 2) {
        iVar13 = (uint)*(ushort *)(param_3 + 0x1e) * 0x14c0 + param_1;
        *(undefined4 *)(iVar3 + 4) = *(undefined4 *)(iVar13 + 0xa1e0c);
        *(undefined2 *)(iVar3 + 8) = *(undefined2 *)(iVar13 + 0xa1e10);
        iVar13 = *(int *)(param_3 + 0x74);
        *(undefined4 *)(iVar3 + 10) = *(undefined4 *)(iVar13 + 0x1b);
        *(undefined2 *)(iVar3 + 0xe) = *(undefined2 *)(iVar13 + 0x1f);
      }
      else if (*piVar7 == 0x20001) {
        *(int *)(iVar3 + 4) = piVar7[0x3b];
        *(short *)(iVar3 + 8) = (short)piVar7[0x3c];
        iVar13 = *(int *)(param_3 + 0x10);
        *(undefined4 *)(iVar3 + 10) = *(undefined4 *)(iVar13 + 0x21);
        *(undefined2 *)(iVar3 + 0xe) = *(undefined2 *)(iVar13 + 0x25);
      }
      puVar8 = *(undefined4 **)(param_3 + 0x24);
      *(undefined4 *)(iVar3 + 0x10) = *puVar8;
      *(undefined2 *)(iVar3 + 0x14) = *(undefined2 *)(puVar8 + 1);
      iVar13 = *(int *)(param_3 + 0x24);
      *(undefined4 *)(iVar3 + 0x18) = *(undefined4 *)(iVar13 + 6);
      *(undefined2 *)(iVar3 + 0x1c) = *(undefined2 *)(iVar13 + 10);
      *(char *)(param_3 + 0x35) = *(char *)(param_3 + 0x35) + '\x06';
      *(char *)(param_3 + 0x2c) = *(char *)(param_3 + 0x2c) + '\x06';
    }
  }
  if ((*(uint *)(param_3 + 100) & 1) == 0) {
    *(byte *)(iVar3 + 1) = *(byte *)(iVar3 + 1) | 0x40;
  }
  iVar3 = *(int *)(param_3 + 0x28);
  *(byte *)(param_3 + 0x83) = (byte)(((uint)*(byte *)(iVar12 + uVar10) << 0x1c) >> 0x1e);
  bVar6 = *(byte *)(iVar12 + uVar10);
  *(int *)(param_3 + 0x28) = iVar3 + -0xe;
  *(int *)(param_3 + 0x30) = *(int *)(param_3 + 0x24) + 0xe;
  *(byte *)(param_3 + 0x84) = bVar6 >> 4;
  iVar12 = (uint)*(byte *)(*(int *)(param_3 + 0xc) + 0x30) << 0x1b;
  if (iVar12 < 0) {
    *(int *)(param_3 + 0x30) = *(int *)(param_3 + 0x24) + 0x12;
    *(int *)(param_3 + 0x28) = iVar3 + -0x12;
  }
  if (*(char *)(param_3 + 5) == '\x01') {
    uVar10 = *(uint *)(param_1 + 0xa39c08);
    *(uint *)(param_1 + 0xa39c08) = uVar10 + 1;
    *(uint *)(param_1 + 0xa39c0c) = *(int *)(param_1 + 0xa39c0c) + (uint)(0xfffffffe < uVar10);
    bVar6 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
            [param_1 + 0xda];
    if (bVar6 != 0) {
      piVar7 = (int *)("Set::RT_OID_802_11_TX_POWER_LEVEL_1 (BAND1) (=%d)\n" + param_1 + 0x18);
      do {
        if (*piVar7 == 1) {
          piVar7[2] = piVar7[2] + *(int *)(param_3 + 0x28);
        }
        piVar7 = piVar7 + 0x160d;
      } while (piVar7 != (int *)("Set::RT_OID_802_11_TX_POWER_LEVEL_1 (BAND1) (=%d)\n" +
                                (uint)bVar6 * 0x5834 + param_1 + 0x18));
    }
  }
  else if ((*(int *)(param_3 + 8) != 0) && (*(char *)(*(int *)(param_3 + 8) + 0x3dc) != '\0')) {
    *(undefined1 *)(param_3 + 0x86) = 6;
  }
  bVar6 = *(byte *)(param_3 + 0x2c);
  pbVar11 = (byte *)(*(int *)(param_3 + 0x5c) + (uint)bVar6);
  if ((*(uint *)(param_3 + 0x18) & 0x10) != 0) {
    cVar1 = *(char *)(param_1 + (uint)*(byte *)(param_3 + 1) + 0x79511c);
    if (*(int *)(param_3 + 0x10) != 0) {
      cVar1 = wlan_config_get_ack_policy(*(int *)(param_3 + 0x10));
    }
    bVar6 = *(byte *)(param_3 + 0x1c) & 0xf;
    *pbVar11 = bVar6 | cVar1 << 5;
    if (((*(uint *)(*(int *)(param_3 + 0x14) + 0xb4) & 0x800) != 0) &&
       ((*(uint *)(param_3 + 0x18) & 0x800) != 0)) {
      *pbVar11 = bVar6 | cVar1 << 5 | 0x10;
    }
    pbVar11[1] = 0;
    iVar3 = DebugLevel;
    pbVar11 = pbVar11 + 2;
    bVar6 = *(char *)(param_3 + 0x2c) + 2;
    *(byte *)(param_3 + 0x2c) = bVar6;
    if (4 < iVar3) {
      printk("%s: tx_bf: %d\n","ap_ieee_802_11_data_tx",*(undefined1 *)(iVar2 + 0x96));
      bVar6 = *(byte *)(param_3 + 0x2c);
    }
  }
  iVar2 = *(int *)(param_3 + 0x24);
  __dest = (void *)((uint)(pbVar11 + 3) & 0xfffffffc);
  *(byte *)(param_3 + 0x35) = bVar6;
  *(char *)(param_3 + 0x34) = (char)__dest - (char)pbVar11;
  if ((uint)*(byte *)(iVar2 + 0xd) + (uint)*(byte *)(iVar2 + 0xc) * 0x100 < 0x5dd) {
    *(undefined4 *)(param_3 + 0x54) = 0;
    return;
  }
  __src = &SNAP_802_1H;
  *(undefined6 **)(param_3 + 0x54) = &SNAP_802_1H;
  iVar3 = memcmp(&IPX,(void *)(iVar2 + 0xc),2);
  if ((iVar3 == 0) || (iVar2 = memcmp(&APPLE_TALK,(void *)(iVar2 + 0xc),2), iVar2 == 0)) {
    __src = &SNAP_BRIDGE_TUNNEL;
    *(undefined6 **)(param_3 + 0x54) = &SNAP_BRIDGE_TUNNEL;
  }
  memmove(__dest,__src,6);
  if (iVar12 < 0) {
    iVar2 = 0x10;
  }
  else {
    iVar2 = 0xc;
  }
  memmove((void *)((int)__dest + 6),(void *)(*(int *)(param_3 + 0x24) + iVar2),2);
  *(char *)(param_3 + 0x35) = *(char *)(param_3 + 0x35) + '\b';
  return;
}

