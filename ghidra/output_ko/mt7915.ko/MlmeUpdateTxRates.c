// module: mt7915.ko
// function: MlmeUpdateTxRates @ 0x12a1ac
// size: 3004 bytes
//

void MlmeUpdateTxRates(int param_1,uint param_2,uint param_3)

{
  byte bVar1;
  byte bVar2;
  char *pcVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  char cVar7;
  byte *pbVar8;
  byte *pbVar9;
  byte *pbVar10;
  undefined1 *puVar11;
  short sVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  int iVar16;
  uint uVar17;
  uint uVar18;
  bool bVar19;
  int local_34;
  undefined1 auStack_2a [6];
  
  pcVar3 = (char *)get_wdev_by_idx(param_1,param_3);
  if (pcVar3 == (char *)0x0) {
    return;
  }
  iVar4 = GetStaCfgByWdev(param_1,pcVar3);
  uVar15 = 0;
  iVar16 = 0;
  UpdateBasicRateBitmap(param_1,pcVar3);
  pbVar8 = (byte *)(pcVar3 + 0xaf7);
  uVar5 = 4;
  do {
    pbVar8 = pbVar8 + 1;
    switch(*pbVar8 & 0x7f) {
    case 2:
      iVar16 = iVar16 + 1;
      uVar5 = 0;
      goto LAB_0012a3dc;
    case 4:
      iVar16 = iVar16 + 1;
      uVar5 = 1;
      break;
    case 0xb:
      iVar16 = iVar16 + 1;
      uVar5 = 2;
      break;
    case 0xc:
      iVar16 = iVar16 + 1;
      uVar5 = 4;
      break;
    case 0x12:
      iVar16 = iVar16 + 1;
      uVar5 = 5;
      break;
    case 0x16:
      iVar16 = iVar16 + 1;
      uVar5 = 3;
      break;
    case 0x18:
      iVar16 = iVar16 + 1;
      uVar5 = 6;
      break;
    case 0x24:
      iVar16 = iVar16 + 1;
      uVar5 = 7;
      break;
    case 0x30:
      iVar16 = iVar16 + 1;
      uVar5 = 8;
      break;
    case 0x48:
      iVar16 = iVar16 + 1;
      uVar5 = 9;
      break;
    case 0x60:
      iVar16 = iVar16 + 1;
      uVar5 = 10;
      break;
    case 0x6c:
      iVar16 = iVar16 + 1;
      uVar5 = 0xb;
    }
    if (uVar15 < uVar5) {
      uVar15 = uVar5;
    }
LAB_0012a3dc:
  } while (pbVar8 != (byte *)(pcVar3 + 0xb03));
  if (param_3 < 0x30) {
    if (*(char *)(param_1 + 0x286285) != '\x01') {
      if ((*(char *)(param_1 + 0x286285) == '\0' && iVar4 != 0) &&
         (*(char *)(iVar4 + 0x4060) == '\0')) {
        if (*(short *)(pcVar3 + 0x18) == 2 && 3 < uVar15) {
          uVar15 = 3;
        }
        local_34 = DebugLevel;
      }
      else {
        local_34 = DebugLevel;
      }
      goto LAB_0012a50c;
    }
    if (param_3 < (byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                        [param_1 + 0xda]) {
      uVar5 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
      bVar19 = 0x1e < param_3;
      if (param_3 < 0x20) {
        bVar19 = uVar5 <= param_3;
      }
      if (!bVar19) {
        pcVar3 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                 + param_3 * 0x5834 + param_1 + 0xe0;
        goto LAB_0012b04c;
      }
    }
    local_34 = DebugLevel;
    if (-1 < DebugLevel) {
      printk("%s(): invalid apidx(%d)\n","MlmeUpdateTxRates",param_3);
      local_34 = DebugLevel;
    }
  }
  else {
    uVar5 = param_3 - 0x30 & 0xff;
    if (1 < uVar5) {
      if (DebugLevel < 0) {
        return;
      }
      printk("%s(): invalid idx(%d)\n","MlmeUpdateTxRates");
      return;
    }
    pcVar3 = &DAT_0036db58 + param_1 + uVar5 * 0x2137b0;
LAB_0012b04c:
    if (pcVar3 == (char *)0x0) {
      uRam00000b04 = (char)uVar15;
      return;
    }
    local_34 = DebugLevel;
  }
LAB_0012a50c:
  uVar5 = (byte)pcVar3[0x8ae] & 0x7f;
  DebugLevel = local_34;
  pcVar3[0xb04] = (char)uVar15;
  pcVar3[0x8b6] = '\0';
  pcVar3[0x8b7] = '\0';
  pcVar3[0x8b4] = '\0';
  pcVar3[0x8b5] = '\0';
  pcVar3[0x8b2] = '\0';
  pcVar3[0x8b3] = '\0';
  pcVar3[0x8b0] = 1 < iVar16;
  pcVar3[0x8b0] = uVar5 == 0x21;
  if ((iVar4 == 0) ||
     ((((*(uint *)(param_1 + 0x795124) & 2) == 0 && ((*(uint *)(iVar4 + 0x212464) & 1) == 0)) ||
      ((*(int *)(pcVar3 + 0x14) - 2U & 0xfffffffd) != 0)))) {
    pbVar8 = (byte *)(pcVar3 + 0xade);
  }
  else {
    pbVar8 = (byte *)(iVar4 + 0x40c6);
  }
  if (*pbVar8 == 0) {
    uVar14 = 0xb;
    uVar17 = 0;
    uVar18 = 0;
  }
  else {
    uVar17 = 0;
    uVar18 = 0;
    pbVar10 = pbVar8 + 1;
    uVar6 = 0xb;
    do {
      pbVar9 = pbVar10 + 1;
      bVar1 = *pbVar10;
      switch(bVar1 & 0x7f) {
      case 2:
        if ((bVar1 & 0x80) != 0) {
          uVar17 = uVar17 | 1;
        }
      default:
        uVar14 = 0;
        goto LAB_0012a7c0;
      case 4:
        if ((bVar1 & 0x80) != 0) {
          uVar17 = uVar17 | 2;
        }
        uVar14 = 1;
        break;
      case 0xb:
        if ((bVar1 & 0x80) != 0) {
          uVar17 = uVar17 | 4;
        }
        uVar14 = 2;
        break;
      case 0xc:
        uVar17 = uVar17 | 0x10;
        uVar14 = 4;
        break;
      case 0x12:
        if ((bVar1 & 0x80) != 0) {
          uVar17 = uVar17 | 0x20;
        }
        uVar14 = 5;
        break;
      case 0x16:
        if ((bVar1 & 0x80) != 0) {
          uVar17 = uVar17 | 8;
        }
        uVar14 = 3;
        break;
      case 0x18:
        uVar17 = uVar17 | 0x40;
        uVar14 = 6;
        break;
      case 0x24:
        if ((bVar1 & 0x80) != 0) {
          uVar17 = uVar17 | 0x80;
        }
        uVar14 = 7;
        break;
      case 0x30:
        uVar17 = uVar17 | 0x100;
        uVar14 = 8;
        break;
      case 0x48:
        if ((bVar1 & 0x80) != 0) {
          uVar17 = uVar17 | 0x200;
        }
        uVar14 = 9;
        break;
      case 0x60:
        if ((bVar1 & 0x80) != 0) {
          uVar17 = uVar17 | 0x400;
          uVar14 = 10;
          break;
        }
        uVar14 = 10;
        if (9 < uVar18) goto LAB_0012a9b8;
        goto LAB_0012a7b0;
      case 0x6c:
        if ((bVar1 & 0x80) == 0) {
          uVar14 = 0xb;
        }
        else {
          uVar17 = uVar17 | 0x800;
          uVar14 = 0xb;
        }
      }
      if (uVar18 < uVar14) {
LAB_0012a7b0:
        uVar18 = uVar14;
        if (uVar6 <= uVar14) {
          uVar14 = uVar6;
        }
      }
      else {
LAB_0012a9b8:
        if (uVar6 <= uVar14) {
          uVar14 = uVar6;
        }
      }
LAB_0012a7c0:
      pbVar10 = pbVar9;
      uVar6 = uVar14;
    } while (pbVar9 != pbVar8 + 1 + *pbVar8);
  }
  if (pbVar8[0xd] != 0) {
    pbVar10 = pbVar8 + 0xe;
    uVar6 = uVar14;
    do {
      pbVar9 = pbVar10 + 1;
      bVar1 = *pbVar10;
      switch(bVar1 & 0x7f) {
      case 2:
        if ((bVar1 & 0x80) != 0) {
          uVar17 = uVar17 | 1;
        }
      default:
        uVar14 = 0;
        goto LAB_0012aaa0;
      case 4:
        if ((bVar1 & 0x80) != 0) {
          uVar17 = uVar17 | 2;
        }
        uVar14 = 1;
        break;
      case 0xb:
        if ((bVar1 & 0x80) != 0) {
          uVar17 = uVar17 | 4;
        }
        uVar14 = 2;
        break;
      case 0xc:
        uVar17 = uVar17 | 0x10;
        uVar14 = 4;
        break;
      case 0x12:
        if ((bVar1 & 0x80) != 0) {
          uVar17 = uVar17 | 0x20;
        }
        uVar14 = 5;
        break;
      case 0x16:
        if ((bVar1 & 0x80) != 0) {
          uVar17 = uVar17 | 8;
        }
        uVar14 = 3;
        break;
      case 0x18:
        uVar17 = uVar17 | 0x40;
        uVar14 = 6;
        break;
      case 0x24:
        if ((bVar1 & 0x80) != 0) {
          uVar17 = uVar17 | 0x80;
        }
        uVar14 = 7;
        break;
      case 0x30:
        uVar17 = uVar17 | 0x100;
        uVar14 = 8;
        break;
      case 0x48:
        if ((bVar1 & 0x80) != 0) {
          uVar17 = uVar17 | 0x200;
        }
        uVar14 = 9;
        break;
      case 0x60:
        if ((bVar1 & 0x80) != 0) {
          uVar17 = uVar17 | 0x400;
          uVar14 = 10;
          break;
        }
        uVar14 = 10;
        if (9 < uVar18) goto LAB_0012ad7c;
        goto LAB_0012aa90;
      case 0x6c:
        if ((bVar1 & 0x80) == 0) {
          uVar14 = 0xb;
        }
        else {
          uVar17 = uVar17 | 0x800;
          uVar14 = 0xb;
        }
      }
      if (uVar18 < uVar14) {
LAB_0012aa90:
        uVar18 = uVar14;
        if (uVar6 <= uVar14) {
          uVar14 = uVar6;
        }
      }
      else {
LAB_0012ad7c:
        if (uVar6 <= uVar14) {
          uVar14 = uVar6;
        }
      }
LAB_0012aaa0:
      pbVar10 = pbVar9;
      uVar6 = uVar14;
    } while (pbVar9 != pbVar8 + 0xe + pbVar8[0xd]);
  }
  uVar6 = 0;
  puVar11 = (undefined1 *)(param_1 + 0x794c8e);
  uVar13 = 0;
  do {
    if ((uVar17 & 1 << (uVar13 & 0xff)) != 0) {
      uVar6 = uVar13 & 0xff;
    }
    uVar13 = uVar13 + 1;
    puVar11 = puVar11 + 1;
    *puVar11 = (char)uVar6;
  } while (uVar13 != 0xc);
  if (2 < local_34) {
    printk("%s():[MaxSupport = %d] = MaxDesire %d Mbps\n","MlmeUpdateTxRates",RateIdToMbps[uVar18],
           RateIdToMbps[uVar15]);
  }
  if (uVar18 < uVar15) {
    pcVar3[0xb05] = (char)uVar18;
    uVar6 = uVar18;
  }
  else {
    pcVar3[0xb05] = (char)uVar15;
    uVar6 = uVar15;
  }
  pcVar3[0xb07] = (char)uVar14;
  cVar7 = (char)uVar6;
  uVar13 = param_2;
  if (pcVar3[0x8b0] == '\0') {
    pcVar3[0xb08] = cVar7;
    if (iVar16 < 5) {
      uVar15 = uVar5;
      if (3 < uVar5) {
        uVar15 = uVar14;
      }
    }
    else {
      uVar15 = uVar14;
      if (uVar5 < 8) {
        uVar15 = (uint)(byte)RxwiMCSToOfdmRate[uVar5];
      }
    }
    if (param_2 != 0) {
      uVar13 = 1;
    }
    if (*(char *)(param_1 + 0x286285) == '\0') {
      uVar5 = uVar13 & 1;
    }
    else {
      uVar5 = 0;
    }
    uVar14 = uVar6;
    if (uVar5 != 0) {
      iVar4 = GetAssociatedAPByWdev(param_1,pcVar3);
      uVar13 = uVar5;
      if (iVar4 == 0) {
        uVar14 = (uint)(byte)pcVar3[0xb08];
      }
      else {
        *(byte *)(iVar4 + 0xbd) =
             *(byte *)(iVar4 + 0xbd) & 0xfb |
             (byte)((((uint)(byte)pcVar3[0x8b3] << 0x1d) >> 0x1f) << 2);
        bVar1 = *(byte *)(iVar4 + 0xbd);
        bVar2 = (byte)((((uint)(byte)pcVar3[0x8b3] << 0x1e) >> 0x1f) << 1);
        *(byte *)(iVar4 + 0xbd) = bVar1 & 0xfd | bVar2;
        *(byte *)(iVar4 + 0xbc) = *(byte *)(iVar4 + 0xbc) & 0xc0 | pcVar3[0x8b2] & 0x3fU;
        *(byte *)(iVar4 + 0xbd) = bVar1 & 0x1d | bVar2 | pcVar3[0x8b3] & 0xe0U;
        uVar14 = (uint)(byte)pcVar3[0xb08];
      }
    }
  }
  else {
    if (*(char *)(param_1 + 0x286285) == '\0') {
      sVar12 = (short)(char)(&DAT_00580d24)[param_1] -
               (short)"rtmp_read_dot11v_mbssid_cfg_from_file"[param_1 + 0x12];
    }
    else {
      sVar12 = 0;
    }
    if (param_2 == 1) {
      pcVar3[0xb08] = '\b';
    }
    else {
      pcVar3[0xb08] = cVar7;
    }
    if (sVar12 < -0x4b) {
      uVar14 = 3;
      pcVar3[0xb08] = '\x03';
    }
    else if (sVar12 < -0x46) {
      uVar14 = 8;
      pcVar3[0xb08] = '\b';
    }
    else {
      uVar14 = (uint)(byte)pcVar3[0xb08];
    }
    if (uVar6 < uVar14) {
      pcVar3[0xb08] = cVar7;
      uVar14 = uVar6;
    }
    pcVar3[0xb06] = '\0';
    if (param_2 != 0) {
      uVar13 = 1;
    }
  }
  if (uVar14 < 4) {
    pcVar3[0x8b5] = pcVar3[0x8b5] & 0x1f;
    cVar7 = *(char *)(param_1 + 0x286285);
    if (cVar7 == '\0') {
      pcVar3[0x8b4] = pcVar3[0x8b4] & 0xc0U | *(byte *)(param_1 + 0x794cd0) & 0x3f;
      pcVar3[0x8b6] = pcVar3[0x8b6] & 0xc0U | *(byte *)(param_1 + 0x794cd3) & 0x3f;
      cVar7 = *(char *)(param_1 + 0x286285);
    }
    if (cVar7 == '\x01') {
      pcVar3[0x8b4] = pcVar3[0x8b4] & 0xc0U | (byte)uVar15 & 0x3f;
    }
  }
  else {
    pcVar3[0x8b5] = pcVar3[0x8b5] & 0x1fU | 0x20;
    cVar7 = *(char *)(param_1 + 0x286285);
    if (cVar7 == '\0') {
      pcVar3[0x8b4] =
           pcVar3[0x8b4] & 0xc0U | OfdmRateToRxwiMCS[*(byte *)(param_1 + 0x794cd0)] & 0x3f;
      bVar1 = *(byte *)(param_1 + 0x794cd3);
      if (bVar1 - 4 < 8) {
        pcVar3[0x8b6] = pcVar3[0x8b6] & 0xc0U | OfdmRateToRxwiMCS[bVar1] & 0x3f;
      }
      else {
        pcVar3[0x8b6] = pcVar3[0x8b6] & 0xc0U | bVar1 & 0x3f;
      }
      cVar7 = *(char *)(param_1 + 0x286285);
    }
    if (cVar7 == '\x01') {
      pcVar3[0x8b4] = pcVar3[0x8b4] & 0xc0U | OfdmRateToRxwiMCS[uVar15] & 0x3f;
    }
  }
  *(undefined2 *)(pcVar3 + 0x8b2) = *(undefined2 *)(pcVar3 + 0x8b4);
  if ((param_2 == 0) || (*(char *)(param_1 + 0x286285) != '\0')) {
    if (((*(ushort *)(pcVar3 + 0x18) & 2) == 0) || (0xe < (byte)pcVar3[0x1a])) {
      *(undefined1 *)(param_1 + 0x794cd5) = 4;
      *(undefined1 *)(param_1 + 0x794cd4) = 4;
      pcVar3[0xb0b] = pcVar3[0xb0b] & 0x1fU | 0x20;
      pcVar3[0xb0a] =
           pcVar3[0xb0a] & 0xc0U | OfdmRateToRxwiMCS[*(byte *)(param_1 + 0x794cd5)] & 0x3f;
    }
    else {
      *(undefined1 *)(param_1 + 0x794cd5) = 0;
      pcVar3[0xb0b] = pcVar3[0xb0b] & 0x1f;
      pcVar3[0xb0a] = pcVar3[0xb0a] & 0xc0;
      *(undefined1 *)(param_1 + 0x794cd4) = 3;
    }
    *(undefined2 *)(param_1 + 0xa1ddc) = *(undefined2 *)(pcVar3 + 0xb0a);
    if ((pcVar3[0xb0b] & 0xe0U) == 0x20) {
      *(byte *)(param_1 + 0xa1ddc) =
           *(byte *)(param_1 + 0xa1ddc) & 0xc0 | OfdmRateToRxwiMCS[8] & 0x3f;
    }
    else {
      *(byte *)(param_1 + 0xa1ddc) = *(byte *)(param_1 + 0xa1ddc) & 0xc0;
    }
    *(undefined1 *)(param_1 + 0x794cd6) = *(undefined1 *)(param_1 + 0x794cd5);
    __memzero(auStack_2a,2);
    iVar4 = memcmp(pcVar3 + 0xb0c,auStack_2a,2);
    if (iVar4 == 0) {
      memmove(pcVar3 + 0xb0c,(void *)(param_1 + 0xa1ddc),2);
    }
  }
  else {
    iVar4 = GetAssociatedAPByWdev(param_1,pcVar3);
    if (iVar4 != 0) {
      *(undefined2 *)(iVar4 + 0xbc) = *(undefined2 *)(pcVar3 + 0x8b2);
      *(undefined2 *)(iVar4 + 0xbe) = *(undefined2 *)(pcVar3 + 0x8b4);
      *(undefined2 *)(iVar4 + 0xc0) = *(undefined2 *)(pcVar3 + 0x8b6);
    }
  }
  if (2 < DebugLevel) {
    uVar5 = (uint)(byte)RateIdToMbps[(byte)pcVar3[0xb07]];
    uVar14 = (uint)(byte)pcVar3[0x8b0];
    printk(" %s(): (MaxDesire=%d, MaxSupport=%d, MaxTxRate=%d, MinRate=%d, Rate Switching =%d)\n",
           "MlmeUpdateTxRates",RateIdToMbps[uVar15],RateIdToMbps[uVar18],
           RateIdToMbps[(byte)pcVar3[0xb05]],uVar5,uVar14);
    if (2 < DebugLevel) {
      printk(" %s(): (TxRate=%d, RtsRate=%d, BasicRateBitmap=0x%04lx)\n","MlmeUpdateTxRates",
             RateIdToMbps[(byte)pcVar3[0xb08]],RateIdToMbps[*(byte *)(param_1 + 0x794cd4)],uVar17,
             uVar5,uVar14);
    }
  }
  if (*(char *)(param_1 + 0x286285) == '\0') {
    uVar13 = uVar13 & 1;
  }
  else {
    uVar13 = 0;
  }
  if (((uVar13 != 0) && (iVar4 = GetAssociatedAPByWdev(param_1,pcVar3), iVar4 != 0)) &&
     (2 < DebugLevel)) {
    printk("%s(): (MlmeTransmit=0x%x, MinHTPhyMode=%x, MaxHTPhyMode=0x%x, HTPhyMode=0x%x)\n",
           "MlmeUpdateTxRates",*(undefined2 *)(pcVar3 + 0xb0a),*(undefined2 *)(iVar4 + 0xc0),
           *(undefined2 *)(iVar4 + 0xbe),*(undefined2 *)(iVar4 + 0xbc));
  }
  return;
}

