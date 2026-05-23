// module: mt7915.ko
// function: WscInitRegistrarPair @ 0x1e1324
// size: 1540 bytes
//

void WscInitRegistrarPair(int param_1,int param_2,uint param_3)

{
  byte bVar1;
  undefined4 uVar2;
  undefined2 uVar3;
  ushort uVar4;
  char *pcVar5;
  uint uVar6;
  int iVar7;
  bool bVar8;
  
  if (2 < DebugLevel) {
    printk("-----> WscInitRegistrarPair\n");
  }
  if (*(char *)(param_1 + 0x286285) == '\x01') {
    *(undefined4 *)(param_2 + 0x2a20) = 0;
    *(undefined4 *)(param_2 + 0x72) = *(undefined4 *)(param_2 + 0x2a24);
    *(undefined4 *)(param_2 + 0x76) = *(undefined4 *)(param_2 + 0x2a28);
    *(undefined4 *)(param_2 + 0x7a) = *(undefined4 *)(param_2 + 0x2a2c);
    *(undefined4 *)(param_2 + 0x7e) = *(undefined4 *)(param_2 + 0x2a30);
    uVar6 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    bVar8 = 0x1e < param_3;
    if (param_3 < 0x20) {
      bVar8 = uVar6 <= param_3;
    }
    if (bVar8) {
      if (DebugLevel < 0) {
        param_3 = 0;
      }
      else {
        param_3 = 0;
        uVar2 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
        printk("%s: apidx >= cap(%d)!\n","WscInitRegistrarPair",uVar2);
      }
    }
    uVar6 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    if (param_3 < uVar6) {
      memmove((void *)(param_2 + 0x82),
              "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
              + param_1 + param_3 * 0x5834 + 0x101,6);
      pcVar5 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
               + param_1 + param_3 * 0x5834 + 0xe0;
    }
    else {
      pcVar5 = (char *)0x0;
    }
    bVar1 = *(byte *)(param_2 + 0x2a5a);
    if ((bVar1 & 4) == 0) {
      __memzero((char *)(param_2 + 0x88),0x20);
      snprintf((char *)(param_2 + 0x88),0x20,"%s_%d","RalinkAPS",param_3);
      bVar1 = *(byte *)(param_2 + 0x2a5a);
    }
    uVar6 = (uint)bVar1;
    if ((bVar1 & 1) == 0) {
      builtin_strncpy((char *)(param_2 + 0xcb),"Rali",4);
      builtin_strncpy((char *)(param_2 + 0xcf),"nk T",4);
      builtin_strncpy((char *)(param_2 + 0xd7),"olog",4);
      builtin_strncpy((char *)(param_2 + 0xd3),"echn",4);
      builtin_strncpy((char *)(param_2 + 0xdb),"y, C",4);
      builtin_strncpy((char *)(param_2 + 0xdf),"orp.",4);
      *(char *)(param_2 + 0xe3) = '\0';
    }
    if ((bVar1 & 2) == 0) {
      builtin_strncpy((char *)(param_2 + 0x10b),"Rali",4);
      builtin_strncpy((char *)(param_2 + 0x10f),"nk W",4);
      builtin_strncpy((char *)(param_2 + 0x113),"irel",4);
      builtin_strncpy((char *)(param_2 + 0x117),"ess ",4);
      builtin_strncpy((char *)(param_2 + 0x11b),"Acce",4);
      builtin_strncpy((char *)(param_2 + 0x11f),"ss P",4);
      *(char *)(param_2 + 0x127) = '\0';
      builtin_strncpy((char *)(param_2 + 0x123),"oint",4);
    }
    iVar7 = 0;
  }
  else if (*(char *)(param_1 + 0x286285) == '\0') {
    *(undefined4 *)(param_2 + 0x2a20) = 0;
    *(undefined4 *)(param_2 + 0x72) = *(undefined4 *)(param_2 + 0x2a24);
    *(undefined4 *)(param_2 + 0x7a) = *(undefined4 *)(param_2 + 0x2a2c);
    *(undefined4 *)(param_2 + 0x76) = *(undefined4 *)(param_2 + 0x2a28);
    *(undefined4 *)(param_2 + 0x7e) = *(undefined4 *)(param_2 + 0x2a30);
    memmove((void *)(param_2 + 0x82),&DAT_0036db73 + param_1 + param_3 * 0x2137b0,6);
    bVar1 = *(byte *)(param_2 + 0x2a5a);
    uVar6 = (uint)bVar1;
    if ((bVar1 & 4) == 0) {
      builtin_strncpy((char *)(param_2 + 0x88),"Rali",4);
      builtin_strncpy((char *)(param_2 + 0x8c),"nkLi",4);
      ((char *)(param_2 + 0x98))[0] = 't';
      ((char *)(param_2 + 0x98))[1] = '\0';
      builtin_strncpy((char *)(param_2 + 0x90),"nuxC",4);
      builtin_strncpy((char *)(param_2 + 0x94),"lien",4);
    }
    pcVar5 = &DAT_0036db58 + param_1 + param_3 * 0x2137b0;
    if ((bVar1 & 1) == 0) {
      iVar7 = 2;
LAB_001e165c:
      builtin_strncpy((char *)(param_2 + 0xcb),"Rali",4);
      builtin_strncpy((char *)(param_2 + 0xcf),"nk T",4);
      builtin_strncpy((char *)(param_2 + 0xd7),"olog",4);
      builtin_strncpy((char *)(param_2 + 0xd3),"echn",4);
      builtin_strncpy((char *)(param_2 + 0xdb),"y, C",4);
      builtin_strncpy((char *)(param_2 + 0xdf),"orp.",4);
      *(char *)(param_2 + 0xe3) = '\0';
      if (iVar7 != 2) goto LAB_001e1408;
    }
    if ((uVar6 & 2) == 0) {
      iVar7 = 2;
      builtin_strncpy((char *)(param_2 + 0x10b),"Rali",4);
      builtin_strncpy((char *)(param_2 + 0x10f),"nk W",4);
      builtin_strncpy((char *)(param_2 + 0x113),"irel",4);
      builtin_strncpy((char *)(param_2 + 0x117),"ess ",4);
      builtin_strncpy((char *)(param_2 + 0x11b),"Linu",4);
      builtin_strncpy((char *)(param_2 + 0x11f),"x Cl",4);
      builtin_strncpy((char *)(param_2 + 0x123),"ient",4);
      *(char *)(param_2 + 0x127) = '\0';
    }
    else {
      iVar7 = 2;
    }
  }
  else {
    pcVar5 = (char *)0x0;
    *(undefined4 *)(param_2 + 0x2a20) = 0;
    *(undefined4 *)(param_2 + 0x72) = *(undefined4 *)(param_2 + 0x2a24);
    *(undefined4 *)(param_2 + 0x76) = *(undefined4 *)(param_2 + 0x2a28);
    *(undefined4 *)(param_2 + 0x7a) = *(undefined4 *)(param_2 + 0x2a2c);
    *(undefined4 *)(param_2 + 0x7e) = *(undefined4 *)(param_2 + 0x2a30);
    uVar6 = (uint)*(byte *)(param_2 + 0x2a5a);
    if ((*(byte *)(param_2 + 0x2a5a) & 1) == 0) {
      iVar7 = 0xff;
      pcVar5 = (char *)(uVar6 & 1);
      goto LAB_001e165c;
    }
    iVar7 = 0xff;
  }
LAB_001e1408:
  if ((uVar6 & 8) == 0) {
    *(undefined4 *)(param_2 + 299) = 0x38325452;
    *(undefined2 *)(param_2 + 0x12f) = 0x3036;
    *(undefined1 *)(param_2 + 0x131) = 0;
  }
  if ((uVar6 & 0x10) == 0) {
    *(undefined4 *)(param_2 + 0x14b) = 0x34333231;
    *(undefined4 *)(param_2 + 0x14f) = 0x38373635;
    *(undefined1 *)(param_2 + 0x153) = 0;
  }
  bVar8 = *(char *)(param_2 + 0x2b31) != '\0';
  if (bVar8) {
    uVar3 = 0x900;
  }
  else {
    uVar3 = 0xf00;
  }
  *(undefined2 *)(param_2 + 0xc4) = uVar3;
  if (bVar8) {
    uVar3 = 0x2100;
  }
  else {
    uVar3 = 0x3f00;
  }
  *(undefined2 *)(param_2 + 0xc2) = uVar3;
  if ((s__RB_FULL__Free_Queue_List___00371ba4[param_1 + 0x14] == '\0') &&
     (*(char *)(param_1 + 0x286285) == '\0')) {
    *(undefined1 *)(param_2 + 0xc6) = 2;
  }
  else {
    *(undefined1 *)(param_2 + 0xc6) = 1;
  }
  *(undefined2 *)(param_2 + 0x174) = 0;
  *(undefined2 *)(param_2 + 0x178) = 0;
  *(undefined1 *)(param_2 + 0x16b) = 0;
  *(undefined4 *)(param_2 + 0x16c) = 0x80;
  if (pcVar5 != (char *)0x0) {
    uVar4 = *(ushort *)(pcVar5 + 0x18);
    if ((uVar4 & 0xb1) != 0) {
      *(undefined1 *)(param_2 + 0x16b) = 2;
      uVar4 = *(ushort *)(pcVar5 + 0x18);
    }
    if ((uVar4 & 0x4e) != 0) {
      *(byte *)(param_2 + 0x16b) = *(byte *)(param_2 + 0x16b) | 1;
    }
  }
  *(ushort *)(param_2 + 200) = *(ushort *)(param_2 + 10) << 8 | *(ushort *)(param_2 + 10) >> 8;
  if (iVar7 == 0) {
    *(undefined1 *)(param_2 + 0xca) = *(undefined1 *)(param_2 + 8);
  }
  else if (iVar7 == 2) {
    *(undefined1 *)(param_2 + 0xca) = 1;
  }
  if (*(int *)(param_2 + 4) == 2) {
    uVar3 = 0x400;
  }
  else {
    uVar3 = 0;
  }
  *(undefined2 *)(param_2 + 0x176) = uVar3;
  if (iVar7 == 0) {
    uVar6 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    if (param_3 < 0x20 && param_3 < uVar6) {
      memmove((void *)(param_2 + 0x17a),
              "Set::OID_802_11_SET_PASSPHRASE, Failed (len less than 8 or greater than 64)!!\n" +
              param_1 + param_3 * 0x5834 + 0x34,
              (uint)(byte)"pStaCfg->WpaPassPhrase"[param_1 + param_3 * 0x5834 + 5]);
    }
    uVar2 = AP_Wsc_Pri_Dev_Type._4_4_;
    if ((*(byte *)(param_2 + 0x1c54) & 0x30) == 0) {
      *(undefined4 *)(param_2 + 0xa8) = (undefined4)AP_Wsc_Pri_Dev_Type;
      *(undefined4 *)(param_2 + 0xac) = uVar2;
      goto LAB_001e14f8;
    }
  }
  else {
    if (iVar7 != 2) goto LAB_001e14f8;
    memmove((void *)(param_2 + 0x17a),(void *)(param_1 + 0x57ff5e),
            (uint)(byte)(&DAT_0057ff7e)[param_1]);
  }
  uVar2 = STA_Wsc_Pri_Dev_Type._4_4_;
  *(undefined4 *)(param_2 + 0xa8) = (undefined4)STA_Wsc_Pri_Dev_Type;
  *(undefined4 *)(param_2 + 0xac) = uVar2;
LAB_001e14f8:
  if (2 < DebugLevel) {
    printk("<----- WscInitRegistrarPair\n");
    return;
  }
  return;
}

