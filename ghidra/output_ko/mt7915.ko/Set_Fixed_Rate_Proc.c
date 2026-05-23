// module: mt7915.ko
// function: Set_Fixed_Rate_Proc @ 0x1da9ec
// size: 1668 bytes
//

undefined4 Set_Fixed_Rate_Proc(int param_1,char *param_2)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  uint uVar7;
  int iVar8;
  char *pcVar9;
  byte bVar10;
  uint uVar11;
  bool bVar12;
  bool bVar13;
  bool bVar14;
  uint local_7c;
  uint local_78;
  uint local_74;
  uint local_70;
  uint local_6c;
  int local_68;
  uint local_64;
  uint local_60;
  int local_5c;
  uint local_58;
  undefined1 auStack_51 [3];
  undefined1 local_4e;
  undefined1 local_4d;
  undefined1 local_4c;
  uint local_48;
  uint local_44;
  uint local_40;
  undefined4 local_3c;
  uint local_38;
  undefined4 local_34;
  uint local_30;
  uint local_2c;
  
  local_7c = 0;
  local_78 = 0;
  local_74 = 0;
  local_70 = 0;
  local_6c = 0;
  local_68 = 0;
  local_64 = 0;
  local_60 = 0;
  local_5c = 0;
  local_58 = 0;
  iVar4 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if (param_2 == (char *)0x0) goto LAB_001dad10;
  iVar5 = sscanf(param_2,"%u-%u-%u-%u-%u-%u-%u-%u-%u-%u",&local_7c,&local_78,&local_74,&local_70,
                 &local_6c,&local_68,&local_64,&local_60,&local_5c,&local_58);
  if (2 < DebugLevel) {
    printk("%s():WCID = %u, Mode = %u, BW = %u, MCS = %u, VhtNss = %u\n\t\t\t\tSGI = %u, Preamble = %u, STBC = %u, LDPC = %u, SpeEn = %u\n"
           ,"Set_Fixed_Rate_Proc",local_7c,local_78,local_74,local_70,local_6c,local_68,local_64,
           local_60,local_5c,local_58);
  }
  if (iVar5 != 10) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("Format Error!\n");
    goto LAB_001dad68;
  }
  uVar7 = HcGetMaxStaNum(param_1);
  if (uVar7 <= local_7c) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("WCID exceed pAd->MaxUcastEntryNum!\n");
    goto LAB_001dad68;
  }
  bVar14 = local_78 != 8;
  bVar13 = local_78 - 8 == 1;
  if (1 < local_78 - 8) {
    bVar14 = 3 < local_78;
    bVar13 = local_78 == 4;
  }
  if (bVar14 && !bVar13) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("Unknown Mode!\n");
    goto LAB_001dad68;
  }
  if (4 < local_74) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("Unknown BW!\n");
    goto LAB_001dad68;
  }
  if (local_78 == 0) {
    if (3 < local_70) {
LAB_001dae14:
      if (DebugLevel < 0) {
        return 0;
      }
      printk("Unknown MCS!\n");
LAB_001dad68:
      if (-1 < DebugLevel) {
        printk(
              "iwpriv ra0 set FixedRate=[WCID]-[Mode]-[BW]-[MCS]-[VhtNss]-[SGI]-[Preamble]-[STBC]-[LDPC]-[SPE_EN]\n"
              );
        if (-1 < DebugLevel) {
          printk("[WCID]Wireless Client ID\n");
          if (DebugLevel < 0) {
            return 0;
          }
          printk("[Mode]CCK=0, OFDM=1, HT=2, GF=3, VHT=4, HE_SU=8, HE_EXT_SU=9, HE_TRIG_MODE=10\n");
          if (DebugLevel < 0) {
            return 0;
          }
          printk("[BW]BW20=0, BW40=1, BW80=2,BW160=3\n");
          if (DebugLevel < 0) {
            return 0;
          }
          printk("[MCS]CCK=0~4, OFDM=0~7, HT=0~32, VHT=0~9, HE=0~11\n");
        }
        if ((-1 < DebugLevel) && (printk("[VhtNss]VHT/HE=1~4, Other=ignore\n"), -1 < DebugLevel)) {
          printk("[Preamble]Long=0, Other=Short\n");
        }
      }
      return 0;
    }
  }
  else if (local_78 == 1) {
    if (7 < local_70) goto LAB_001dae14;
  }
  else if (local_78 == 2) {
    if (0x20 < local_70) goto LAB_001dae14;
  }
  else if (local_78 == 4) {
    if (9 < local_70) goto LAB_001dae14;
    if (4 < local_6c) {
      if (DebugLevel < 0) {
        return 0;
      }
      printk("Unknown VhtNss!\n");
      goto LAB_001dad68;
    }
  }
  else if (local_78 == 8) {
    if (0x1b < local_70) goto LAB_001dae14;
    if (4 < local_6c) {
      if (DebugLevel < 0) {
        return 0;
      }
      printk("Unknown HeNss!\n");
      goto LAB_001dad68;
    }
  }
  down_interruptible(param_1 + 0x285d58);
  uVar7 = local_7c;
  if (*(int *)(local_7c * 0x14c0 + param_1 + 0xa1d20) != 0) {
    os_zero_mem(auStack_51,9);
    local_4c = 0;
    if (local_5c != 0) {
      local_4c = 7;
    }
    local_4d = (undefined1)local_74;
    local_4e = (undefined1)local_68;
    local_64 = (uint)(local_64 == 0);
    local_60 = raStbcSettingCheck(local_60 & 0xff,local_78 & 0xff,local_70 & 0xff,local_6c & 0xff,0,
                                  0);
    iVar5 = uVar7 * 0x14c0 + param_1;
    uVar11 = local_78 - 8;
    *(byte *)(iVar5 + 0xa1ddd) =
         *(byte *)(iVar5 + 0xa1ddd) & 3 | (byte)((local_78 & 7) << 5) | (local_60 != 0) << 2;
    *(byte *)(iVar5 + 0xa1ddd) = *(byte *)(iVar5 + 0xa1ddd) & 0xfd | (local_68 != 0) << 1;
    *(ushort *)(iVar5 + 0xa1ddc) =
         *(ushort *)(iVar5 + 0xa1ddc) & 0xfe7f | (ushort)((local_74 & 3) << 7);
    bVar13 = 3 < local_78;
    bVar14 = local_78 == 4;
    if (!bVar14) {
      bVar13 = uVar11 != 0;
    }
    bVar12 = uVar11 != 1;
    bVar2 = (local_5c != 0) << 6;
    bVar1 = *(byte *)(iVar5 + 0xa1ddc) & 0xbf;
    *(byte *)(iVar5 + 0xa1ddc) = bVar1 | bVar2;
    if (!bVar13 || (bVar14 || !bVar12)) {
      uVar11 = local_6c;
    }
    bVar10 = (byte)uVar11;
    uVar11 = local_78;
    if (bVar13 && (!bVar14 && bVar12)) {
      uVar11 = (uint)*(byte *)(iVar5 + 0xa1ddc);
    }
    bVar3 = (byte)uVar11;
    if (!bVar13 || (bVar14 || !bVar12)) {
      bVar3 = bVar1 | bVar2;
    }
    if (!bVar13 || (bVar14 || !bVar12)) {
      bVar10 = bVar10 - 1;
    }
    uVar11 = (uint)(local_5c != 0);
    if (!bVar13 || (bVar14 || !bVar12)) {
      uVar11 = local_70;
    }
    if (!bVar13 || (bVar14 || !bVar12)) {
      bVar10 = bVar10 & 3;
    }
    if (bVar13 && (!bVar14 && bVar12)) {
      uVar11 = local_70;
    }
    if (!bVar13 || (bVar14 || !bVar12)) {
      bVar10 = (byte)uVar11 + bVar10 * '\x10';
    }
    if (bVar13 && (!bVar14 && bVar12)) {
      bVar3 = bVar3 & 0xc0 | (byte)uVar11 & 0x3f;
    }
    if (!bVar13 || (bVar14 || !bVar12)) {
      bVar3 = bVar3 & 0xc0 | bVar10 & 0x3f;
    }
    *(byte *)(iVar5 + 0xa1ddc) = bVar3;
    iVar5 = uVar7 * 0x14c0;
    iVar8 = param_1 + iVar5;
    *(uint *)(iVar8 + 0xa1e54) = (uint)*(ushort *)(iVar8 + 0xa1ddc);
    *(uint *)(param_1 + 0xa39f9c) = (uint)*(ushort *)(iVar8 + 0xa1ddc);
    if (*(char *)(iVar4 + 0x150) == '\x01') {
      *(undefined1 *)(iVar8 + 0xa289e) = 0;
      __memzero(&local_48,0x1c);
      local_3c = CONCAT31(local_3c._1_3_,(char)local_78);
      local_3c = CONCAT13((char)local_68,CONCAT12((char)local_60,(undefined2)local_3c));
      local_38 = CONCAT13((char)local_6c,CONCAT12((char)local_70,CONCAT11(local_4c,(char)local_74)))
      ;
      local_34 = CONCAT22(CONCAT11(local_34._3_1_,(char)local_64),
                          CONCAT11((undefined1)local_58,(undefined1)local_34));
      local_44 = 3;
      RAParamUpdate(param_1,param_1 + iVar5 + 0xa1d20,&local_48);
    }
    else {
      if (*(char *)(param_1 + 0x286285) == '\0') {
        (&DAT_0036e408)[param_1] = 0;
      }
      else if ((*(char *)(param_1 + 0x286285) == '\x01') &&
              (bVar1 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                       [param_1 + 0xda], bVar1 != 0)) {
        pcVar9 = "%s: period = %d\n" + param_1;
        do {
          *pcVar9 = '\0';
          pcVar9 = pcVar9 + 0x5834;
        } while (pcVar9 != "%s: period = %d\n" + (uint)bVar1 * 0x5834 + param_1);
      }
      uVar6 = asic_get_nsts_by_mcs(param_1,local_78 & 0xff,uVar11 & 0xff,local_60,local_6c & 0xff);
      local_48 = asic_tx_rate_to_tmi_rate
                           (param_1,local_78 & 0xff,local_70 & 0xff,uVar6,local_60 & 0xff,
                            local_64 & 0xff);
      local_48 = local_48 & 0xfff;
      local_44 = local_48;
      local_40 = local_48;
      local_3c = local_48;
      local_38 = local_48;
      local_34 = local_48;
      local_30 = local_48;
      local_2c = local_48;
      AsicTxCapAndRateTableUpdate(param_1,local_7c & 0xffff,auStack_51,&local_48,local_58 & 0xff);
    }
  }
  up(param_1 + 0x285d58);
LAB_001dad10:
  asic_dump_wtbl_info(param_1,local_7c & 0xffff);
  return 1;
}

