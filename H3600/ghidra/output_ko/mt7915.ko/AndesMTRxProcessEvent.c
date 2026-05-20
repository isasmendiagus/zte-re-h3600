// module: mt7915.ko
// function: AndesMTRxProcessEvent @ 0x1a8e5c
// size: 8576 bytes
//

void AndesMTRxProcessEvent(int *param_1,int param_2)

{
  char cVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  byte bVar4;
  undefined2 uVar5;
  int *piVar6;
  int iVar7;
  char **__s;
  size_t sVar8;
  undefined4 *puVar9;
  undefined4 *extraout_r1;
  undefined4 *extraout_r1_00;
  undefined4 extraout_r1_01;
  undefined4 *extraout_r1_02;
  undefined4 *extraout_r1_03;
  undefined4 *extraout_r1_04;
  undefined4 *extraout_r1_05;
  undefined4 *extraout_r1_06;
  uint uVar10;
  undefined4 *extraout_r1_07;
  undefined4 *extraout_r1_08;
  uint extraout_r1_09;
  undefined4 *extraout_r1_10;
  undefined4 *extraout_r1_11;
  undefined4 *extraout_r1_12;
  uint extraout_r1_13;
  undefined4 *extraout_r1_14;
  undefined4 *extraout_r1_15;
  undefined4 *extraout_r1_16;
  uint extraout_r1_17;
  undefined4 *extraout_r1_18;
  undefined4 *extraout_r1_19;
  undefined4 *extraout_r1_20;
  uint extraout_r1_21;
  undefined4 *extraout_r1_22;
  undefined4 *extraout_r1_23;
  undefined4 *extraout_r1_24;
  uint extraout_r1_25;
  undefined4 uVar11;
  char *pcVar12;
  undefined4 uVar13;
  code *pcVar14;
  int iVar15;
  char *pcVar16;
  int *piVar17;
  ushort uVar18;
  ushort *puVar19;
  int iVar20;
  short sVar21;
  uint uVar22;
  int iVar23;
  undefined1 *puVar24;
  void *__s1;
  uint uVar25;
  int *piVar26;
  uint uVar27;
  uint uVar28;
  uint uVar29;
  bool bVar30;
  bool bVar31;
  longlong lVar32;
  undefined8 uVar33;
  char *local_7c [4];
  undefined *puStack_6c;
  char *pcStack_68;
  char *local_64 [4];
  char *local_54;
  char *local_50 [11];
  
  iVar23 = *(int *)(param_2 + 0x20);
  puVar19 = *(ushort **)(iVar23 + 0xcc);
  if (3 < DebugLevel) {
    printk("%s: seq_num=%d, ext_eid=%x\n","AndesMTRxProcessEvent",*(undefined1 *)((int)puVar19 + 5),
           (char)puVar19[4]);
  }
  uVar25 = (uint)(byte)puVar19[4];
  if (*(char *)((int)puVar19 + 5) != '\0') {
    pcVar12 = (char *)(uint)(uVar25 == 0x13 || uVar25 == 5);
    if (uVar25 == 0x87) {
      pcVar12 = (char *)0x1;
    }
    if (uVar25 - 0x22 < 2) {
      pcVar12 = (char *)0x1;
    }
    if (pcVar12 == (char *)0x0) {
      local_50[0] = pcVar12;
      OS_SPIN_LOCK_IRQSAVE(param_1 + 0x29e134,local_50);
      piVar26 = *(int **)param_1[0x29e135];
      piVar17 = (int *)param_1[0x29e135];
      do {
        piVar6 = piVar26;
        if (param_1 + 0x29e135 == piVar17) {
LAB_001a9030:
          OS_SPIN_UNLOCK_IRQRESTORE(param_1 + 0x29e134,local_50);
          return;
        }
        piVar26 = piVar17 + -0x12;
        cVar1 = *(char *)((int)puVar19 + 5);
        if (3 < DebugLevel) {
          printk("%s: msg->seq=%x, field.seq_num=%x, msg->attr.ctrl.expect_size=%d\n",
                 "HandleSeqNonZeroNormalEvents",*(undefined1 *)((int)piVar17 + -0x32),cVar1,
                 *(undefined2 *)((int)piVar17 + -0x42));
        }
        if (cVar1 == *(char *)((int)piVar17 + -0x32)) {
          if (DebugLevel < 4) {
            piVar17[-1] = jiffies;
          }
          else {
            printk("%s (seq=%d)\n","HandleSeqNonZeroNormalEvents",cVar1);
            iVar15 = jiffies;
            iVar20 = DebugLevel;
            piVar17[-1] = jiffies;
            if (3 < iVar20) {
              printk("%s: CMD_ID(0x%x 0x%x),total spent %ld ms\n","HandleSeqNonZeroNormalEvents",
                     *(undefined1 *)((int)piVar17 + -0x46),*(undefined1 *)((int)piVar17 + -0x45),
                     (uint)((iVar15 - piVar17[-2]) * 1000) / 100);
            }
          }
          cVar1 = (char)puVar19[2];
          if (cVar1 == -0x13) {
            uVar25 = (uint)*(ushort *)((int)piVar17 + -0x42);
            if (uVar25 != *puVar19 - 0xc || uVar25 == 0) {
              if (uVar25 <= *puVar19 - 0xc && uVar25 != 0) {
LAB_001a9394:
                if ((*(byte *)(piVar17 + -0x11) & 0x20) != 0) goto LAB_001a93a0;
              }
LAB_001a8fc4:
              if (uVar25 != 0xffff) {
                FUN_001a58fc(puVar19,piVar26);
                goto LAB_001a8fe4;
              }
            }
LAB_001a93a0:
            FUN_001a5b04(puVar19,piVar26,iVar23);
          }
          else if (cVar1 == '\x01') {
            FUN_001a5980(1,(char)puVar19[4],*(int *)(iVar23 + 0xcc) + 8);
          }
          else {
            if (cVar1 != -0x11 && (cVar1 - 2U & 0xfd) != 0) {
              uVar25 = (uint)*(ushort *)((int)piVar17 + -0x42);
              if (uVar25 != 0 && uVar25 <= *puVar19 - 0xc) goto LAB_001a9394;
              goto LAB_001a8fc4;
            }
            (*(code *)piVar17[-0xe])(piVar26,*(int *)(iVar23 + 0xcc) + 8,*puVar19 - 8);
          }
LAB_001a8fe4:
          if (3 < DebugLevel) {
            printk("%s: need_wait=%d\n","HandleSeqNonZeroNormalEvents",
                   ((uint)*(byte *)(piVar17 + -0x11) << 0x1d) >> 0x1f);
          }
          if ((*(byte *)(piVar17 + -0x11) & 4) == 0) {
            if (*piVar17 != 0) {
              *(int *)(*piVar17 + 4) = piVar17[1];
            }
            if ((int *)piVar17[1] != (int *)0x0) {
              *(int *)piVar17[1] = *piVar17;
            }
            *piVar17 = 0;
            piVar17[1] = 0;
            AndesFreeCmdMsg(piVar26);
          }
          else {
            complete(piVar17 + 2);
          }
          goto LAB_001a9030;
        }
        piVar26 = (int *)*piVar6;
        piVar17 = piVar6;
      } while( true );
    }
  }
  iVar23 = *(int *)(iVar23 + 0xcc);
  if ((char)puVar19[2] != '\x18') {
    if ((char)puVar19[2] != -0x13) {
      if (DebugLevel < 1) {
        return;
      }
      printk("%s: Unknown Event(%x)\n","UnsolicitedEventHandler");
      return;
    }
    uVar22 = *puVar19 - 0xc;
    __s1 = (void *)(iVar23 + 0xc);
    puVar9 = (undefined4 *)param_1[0x29deee];
    uVar11 = puVar9[0x7d2];
    switch(uVar25) {
    case 0:
      if (DebugLevel < 4) {
        return;
      }
      printk("%s: EventExtCmdResult.ucExTenCID = 0x%x\n","EventExtCmdResult",
             *(undefined1 *)(iVar23 + 0xc));
      if (DebugLevel < 4) {
        return;
      }
      printk("%s: EventExtCmdResult.u4Status = 0x%x\n","EventExtCmdResult",
             *(undefined4 *)(iVar23 + 0x10));
      return;
    default:
      if (DebugLevel < 1) {
        return;
      }
      printk("%s: Unknown Ext Event(%x)\n","EventExtEventHandler",uVar25);
      return;
    case 4:
      if (*(code **)(puVar9[0x7c4] + 0x138) == (code *)0x0) {
        return;
      }
      (**(code **)(puVar9[0x7c4] + 0x138))(*puVar9,puVar9 + 0x7d3,uVar11,__s1,uVar22);
      return;
    case 5:
      iVar20 = param_1[0xa5b10];
      uVar25 = CONCAT11(*(undefined1 *)(iVar23 + 0xe),*(undefined1 *)(iVar23 + 0xc)) & 0x3ff;
      if (3 < DebugLevel) {
        printk("%s: PsSync Event from FW APPS WIdx=%d PSBit=%d len=%d\n","ExtEventPsSyncHandler",
               uVar25,*(undefined1 *)(iVar23 + 0xd),uVar22);
      }
      uVar22 = hc_get_chip_wtbl_max_num(param_1[0x29e5e8]);
      if (uVar22 <= uVar25 || 0x11f < uVar25) {
        if (DebugLevel < 0) {
          return;
        }
        printk("%s: wtbl index(%d) is invalid\n","ExtEventPsSyncHandler",uVar25);
        return;
      }
      _raw_spin_lock_bh(param_1 + uVar25 * 0x188 + 0xbdd2);
      bVar31 = *(char *)(iVar23 + 0xd) != '\0';
      *(bool *)(param_1 + uVar25 * 0x188 + 0xbdcb) = bVar31;
      uVar11 = extraout_r1_01;
      if (!bVar31) {
        iVar23 = 0;
        while( true ) {
          uVar33 = CONCAT44(param_1 + uVar25 * 0x188 + 0xbda8,iVar23);
          pcVar14 = *(code **)(iVar20 + 0x34);
          if (pcVar14 != (code *)0x0) {
            uVar33 = (*pcVar14)(param_1,param_1 + uVar25 * 0x188 + 0xbda8);
          }
          uVar11 = (undefined4)((ulonglong)uVar33 >> 0x20);
          iVar23 = (int)uVar33;
          bVar31 = false;
          if (iVar23 == 0) break;
          uVar2 = *(undefined1 *)(iVar23 + 0x4d);
          iVar15 = param_1[*(byte *)(iVar23 + 0x2d) + 3];
          param_1[0xa5b08] = param_1[0xa5b08] + -1;
          (**(code **)(iVar20 + 0x24))(param_1,iVar15,iVar23,uVar2);
        }
      }
      _raw_spin_unlock_bh(param_1 + uVar25 * 0x188 + 0xbdd2,uVar11,bVar31);
      return;
    case 0x13:
      local_50[0] = (char *)CONCAT22(local_50[0]._2_2_,0x20);
      if (3 < DebugLevel) {
        printk("%s: s2d_index = 0x%x\n","ExtEventFwLog2HostHandler",
               *(undefined1 *)((int)puVar19 + 0xb));
      }
      __s = (char **)RtmpOsGetNetDevName(param_1[1]);
      if ((__s == (char **)0x0) || (sVar8 = strlen((char *)__s), 0xf < sVar8)) {
        __s = local_50;
      }
      if (*(char *)((int)puVar19 + 0xb) != '\0') {
        if (*(char *)((int)puVar19 + 0xb) == '\x02') {
          if (DebugLevel < 1) {
            return;
          }
          printk("CR4 LOG(%s): %s\n",__s,__s1);
          return;
        }
        if (DebugLevel < 1) {
          return;
        }
        printk("unknow MCU LOG(%s): %s",__s,__s1);
        return;
      }
      if (*(int *)(iVar23 + 0xc) != 0x44e98caf) {
        if (DebugLevel < 1) {
          return;
        }
        printk("N9 LOG(%s): %s\n",__s,__s1);
        return;
      }
      bVar4 = *(byte *)((int)param_1 + 0xa7cc32);
      if ((bVar4 & 8) != 0) {
        RTEnqueueInternalCmd(param_1,0x1f,__s1,uVar22);
        bVar4 = *(byte *)((int)param_1 + 0xa7cc32);
      }
      if ((bVar4 & 0x10) == 0) {
        return;
      }
      fw_log_to_ethernet(param_1,__s1,uVar22);
      return;
    case 0x1a:
      if (DebugLevel < 1) {
        switch(*(undefined1 *)(iVar23 + 0x12)) {
        case 0:
          goto switchD_001a9a28_caseD_0;
        default:
          return;
        case 0x12:
          goto switchD_001a9a28_caseD_12;
        }
      }
      printk("%s::FW EVENT (%02x:%02x:%02x:%02x:%02x:%02x), Reason 0x%x\n",
             "ExtEventBeaconLostHandler",*(undefined1 *)(iVar23 + 0xc),*(undefined1 *)(iVar23 + 0xd)
             ,*(undefined1 *)(iVar23 + 0xe),*(undefined1 *)(iVar23 + 0xf),
             *(undefined1 *)(iVar23 + 0x10),*(undefined1 *)(iVar23 + 0x11),
             *(undefined1 *)(iVar23 + 0x12));
      bVar4 = *(byte *)(iVar23 + 0x12);
      if (bVar4 == 0x10) {
        if (DebugLevel < 1) {
          return;
        }
        printk("  AP Beacon OFF!!!\n");
        return;
      }
      if (bVar4 < 0x11) {
        if (bVar4 != 0) {
          return;
        }
        if (0 < DebugLevel) {
          printk("  Beacon lost - STA!!!\n");
        }
switchD_001a9a28_caseD_0:
        if ((char)param_1[0x1e52ae] != '\0') {
          uVar25 = 0;
          do {
            iVar23 = uVar25 * 0x84dec;
            if (param_1 + iVar23 == (int *)0xffc924a8) {
              printk(&_LC195,0xc2);
              dump_stack();
            }
            if (((char)param_1[uVar25 * 0x84dec + 0xdb980] != '\0') &&
               (iVar20 = memcmp(__s1,(undefined *)
                                     ((int)param_1 + (int)(&DAT_0057ff80 + uVar25 * 0x2137b0)),6),
               iVar20 == 0)) {
              if (2 < DebugLevel) {
                printk("%s::Found StaCfg[%d] Bssid matching\n","ExtEventBeaconLostHandler",uVar25);
              }
              uVar22 = (uint)*(byte *)(param_1 + 0x1e52ae);
              break;
            }
            uVar22 = (uint)*(byte *)(param_1 + 0x1e52ae);
            uVar25 = uVar25 + 1 & 0xff;
          } while (uVar25 < uVar22);
          if (uVar25 != uVar22) {
            *(undefined1 *)((int)(param_1 + iVar23) + 0x580012) = 1;
            return;
          }
        }
        printk(&_LC194,0xce);
        dump_stack();
        return;
      }
      if (bVar4 == 0x11) {
        if (DebugLevel < 1) {
          return;
        }
        printk("  SER happened!!!\n");
        return;
      }
      if (bVar4 != 0x12) {
        return;
      }
      if (0 < DebugLevel) {
        printk("  Beacon lost - Error!!! Re-issue BCN_OFFLOAD cmd\n");
      }
switchD_001a9a28_caseD_12:
      uVar11 = get_default_wdev(param_1);
      UpdateBeaconHandler(param_1,uVar11,3);
      return;
    case 0x22:
      EventThermalProtectHandler(param_1,__s1,uVar22);
      return;
    case 0x23:
      if (max_line == 0) {
        return;
      }
      if (max_line == 0x82) {
        if (DebugLevel < 0) {
          max_line = 0x81;
          *(undefined1 *)(iVar23 + uVar22 + 0xc) = 0;
          return;
        }
        printk("**************************************************\n\n");
      }
      bVar31 = DebugLevel < 0;
      max_line = max_line + -1;
      *(undefined1 *)(iVar23 + uVar22 + 0xc) = 0;
      if (bVar31) {
        return;
      }
      printk(&_LC95,__s1);
      return;
    case 0x2c:
      EventThermalHandler(param_1,__s1,uVar22);
      return;
    case 0x2d:
      bVar31 = DebugLevel < 0;
      *(undefined1 *)((int)param_1 + 0x580013) = 1;
      if (bVar31) {
        return;
      }
      printk("%s::FW LOG, ucBssidIdx = %d,  u4RoamReason = %d\n","ExtEventRoamingDetectionHandler",
             *(undefined1 *)(iVar23 + 0xc),*(undefined4 *)(iVar23 + 0x10));
      return;
    case 0x2f:
      piVar17 = param_1 + *(int *)(*param_1 + 0x3c) * 0x160d + 0xadc92;
      if (piVar17 == (int *)0x0 || __s1 == (void *)0x0) {
        if (DebugLevel < 0) {
          return;
        }
        printk("%s:: Data is NULL\n","ExtEventThroughputBurst");
        return;
      }
      cVar1 = *(char *)(iVar23 + 0xc);
      *(char *)((int)param_1 + 0xa39fa1) = cVar1;
      if (cVar1 == '\0') {
        uVar11 = wlan_operate_get_rts_pkt_thld(piVar17,puVar9,0x5834,param_1 + 0x28e400);
        uVar13 = wlan_operate_get_rts_len_thld(piVar17);
      }
      else {
        uVar11 = 0xff;
        uVar13 = 0xfffff;
      }
      HW_SET_RTS_THLD(param_1,piVar17,uVar11,uVar13);
      if (DebugLevel < 3) {
        return;
      }
      printk("%s::%d\n","ExtEventThroughputBurst",cVar1);
      return;
    case 0x30:
      uVar2 = *(undefined1 *)(iVar23 + 0xe);
      uVar3 = *(undefined1 *)(iVar23 + 0xc);
      uVar25 = HcGetMaxStaNum(param_1);
      uVar22 = CONCAT11(uVar2,uVar3) & 0x3ff;
      if (uVar25 <= uVar22) {
        return;
      }
      if (param_1[uVar22 * 0x530 + 0x28748] == 0) {
        return;
      }
      if ((char)param_1[(uint)*(ushort *)((int)param_1 + uVar22 * 0x14c0 + 0xa1e02) * 0x188 + 0xbea2
                       ] != '\x02') {
        return;
      }
      iVar20 = *(int *)(iVar23 + 0x30);
      if (*(char *)((int)param_1 + uVar22 * 0x14c0 + 0xa3149) != '\0') {
        iVar20 = *(int *)(iVar23 + 0x2c) - iVar20;
        param_1[uVar22 * 0x530 + 0x28c26] = iVar20;
        param_1[uVar22 * 0x530 + 0x28c53] = iVar20 + param_1[uVar22 * 0x530 + 0x28c53];
        iVar20 = *(int *)(iVar23 + 0x30);
      }
      iVar15 = DebugLevel;
      param_1[uVar22 * 0x530 + 0x28c14] = iVar20 + param_1[uVar22 * 0x530 + 0x28c14];
      if (3 < iVar15) {
        pcVar12 = "Valid";
        if (*(char *)((int)param_1 + uVar22 * 0x14c0 + 0xa3149) == '\0') {
          pcVar12 = "Invalid";
        }
        printk("%s(): wcid(%d), TotalTxCnt(%u) - TotalTxFail(%u) = %u (%s)\n",
               "event_get_tx_statistic_handle",uVar22,*(undefined4 *)(iVar23 + 0x2c),
               *(undefined4 *)(iVar23 + 0x30),param_1[uVar22 * 0x530 + 0x28c53],pcVar12);
      }
      *(char *)((int)param_1 + uVar22 * 0x14c0 + 0xa3149) =
           *(char *)((int)param_1 + uVar22 * 0x14c0 + 0xa3149) + '\x01';
      return;
    case 0x31:
      if ((param_1[0x28e7e1] & 0x40140U) != 0) {
        return;
      }
      RTMP_HANDLE_PRETBTT_INT_EVENT(param_1);
      return;
    case 0x35:
      if (2 < DebugLevel) {
        printk("%s: EXT_EVENT_ID_BF_STATUS_READ\n","EventExtEventHandler",uVar11);
      }
      ExtEventBfStatusRead(param_1,__s1,uVar22);
      return;
    case 0x3a:
      if (__s1 == (void *)0x0) {
        return;
      }
      uVar2 = *(undefined1 *)(iVar23 + 0xc);
      dfs_update_radar_info(__s1);
      if (*(char *)((int)param_1 + 0x795437) == '\x01') {
        dfs_dump_radar_sw_pls_info(param_1,__s1);
      }
      if (*(char *)((int)param_1 + 0x795436) == '\x01') {
        dfs_dump_radar_hw_pls_info(param_1,__s1);
      }
      if ((((*(char *)((int)param_1 + 0x795439) != '\x01') && (*(char *)(iVar23 + 0xd) != '\x01'))
          && (*(char *)(iVar23 + 0xe) != '\x01')) && (*(char *)(iVar23 + 0xf) != '\x01')) {
        return;
      }
      WrapDfsRddReportHandle(param_1,uVar2);
      return;
    case 0x3f:
      if (2 < DebugLevel) {
        printk("%s: EXT_EVENT_ID_MEC_INFO_READ\n","EventExtEventHandler",uVar11);
      }
      ExtEventMecInfoRead(param_1,__s1,uVar22);
      return;
    case 0x4c:
      uVar22 = (uint)*(byte *)(iVar23 + 0xd);
      uVar25 = (uint)*(byte *)(iVar23 + 0xc);
      if (uVar22 == 0) {
        uVar22 = 1;
      }
      if (2 < DebugLevel) {
        printk("ExtEventMaxAmsduLengthUpdate: wlan_idx = %d,\t\t\t  amsdu_len = %d\n",uVar25,uVar22)
        ;
      }
      uVar28 = HcGetMaxStaNum(param_1);
      if (uVar28 <= uVar25) {
        return;
      }
      uVar28 = param_1[uVar25 * 0x530 + 0x28a8a];
      if (uVar28 == 0) {
        return;
      }
      uVar29 = uVar22 * 0x608;
      if (uVar28 <= uVar22 * 0x608) {
        uVar29 = uVar28;
      }
      param_1[uVar25 * 0x530 + 0x28a8b] = uVar29;
      return;
    case 0x4e:
      uVar25 = CONCAT11(*(undefined1 *)(iVar23 + 0xe),*(undefined1 *)(iVar23 + 0xc)) & 0x3ff;
      if (2 < DebugLevel) {
        printk("RX P_CMD_BA_TRIGGER_EVENT_T: Wcid=%d, Tid=%d\n",uVar25,*(undefined1 *)(iVar23 + 0xd)
              );
      }
      ba_ori_session_start(param_1,param_1 + uVar25 * 0x188 + 0xbda8,*(undefined1 *)(iVar23 + 0xd));
      return;
    case 0x4f:
      iVar20 = wdev_search_by_band_omac_idx
                         (param_1,*(undefined1 *)(iVar23 + 0xe),*(undefined1 *)(iVar23 + 0xc));
      if (iVar20 == 0) {
        return;
      }
      if ((param_1[0x28e7e1] & 0x10040140U) != 0x10000000) {
        return;
      }
      *(undefined1 *)(iVar20 + 0x944) = *(undefined1 *)(iVar23 + 0xd);
      puVar24 = *(undefined1 **)(iVar20 + 0x3fe4);
      if (puVar24 == (undefined1 *)0x0) {
        return;
      }
      piVar17 = param_1 + 2;
      do {
        piVar17 = piVar17 + 1;
        iVar23 = *piVar17;
        if ((iVar23 != 0) && (*(int *)(iVar23 + 0xabc) != 0)) {
          iVar15 = HcGetBandByWdev(iVar23);
          iVar7 = HcGetBandByWdev(iVar20);
          if (iVar15 == iVar7) {
            *(undefined1 *)(iVar23 + 0x944) = *(undefined1 *)(iVar20 + 0x944);
          }
        }
      } while (piVar17 != param_1 + 0x6a);
      iVar23 = HcIsRfSupport(param_1,2);
      if (iVar23 == 0) {
        return;
      }
      if ((char)param_1[0x1e541d] != '\x01') {
        return;
      }
      if (puVar24[4] != '\x01') {
        return;
      }
      *puVar24 = puVar24[1];
      ChannelSwitchingCountDownProc(param_1,iVar20);
      return;
    case 0x50:
      if ((DebugLevel < 3) ||
         (printk("%s----------------->\n","ExtEventWifiSpectrumHandler",uVar11), DebugLevel < 3)) {
        if (*(int *)(iVar23 + 0xc) != 2) {
          return;
        }
      }
      else {
        printk("%s: FuncIndex = %d\n","ExtEventWifiSpectrumHandler",*(undefined4 *)(iVar23 + 0xc));
        if (*(int *)(iVar23 + 0xc) != 2) goto LAB_001a9838;
      }
      RTEnqueueInternalCmd(param_1,0x15,__s1,uVar22);
LAB_001a9838:
      if (DebugLevel < 3) {
        return;
      }
      printk("%s<-----------------\n","ExtEventWifiSpectrumHandler");
      return;
    case 0x51:
      TmrReportParser(param_1,__s1,1,*(undefined4 *)(iVar23 + 0x3c));
      return;
    case 0x52:
      if (3 < DebugLevel) {
        printk("RX ExtEventBssAcQPktNumHandler: u4BssMap=0x%08X\n",*(undefined4 *)(iVar23 + 0xc),
               uVar11);
      }
      uVar25 = 0;
      iVar20 = iVar23;
      do {
        if ((*(uint *)(iVar23 + 0xc) & 1 << (uVar25 & 0xff)) == 0) break;
        iVar15 = *(int *)(iVar20 + 0x18) + *(int *)(iVar20 + 0x10) + *(int *)(iVar20 + 0x1c);
        if (iVar15 != 0) {
          if (3 < DebugLevel) {
            printk("BSS[%d], AC_BK = %d, AC_BE = %d, AC_VI = %d, AC_VO = %d\n",uVar25,
                   *(int *)(iVar20 + 0x10),*(undefined4 *)(iVar20 + 0x14),*(int *)(iVar20 + 0x18),
                   *(int *)(iVar20 + 0x1c));
          }
          param_1[0x29df0b] = iVar15 + param_1[0x29df0b];
        }
        uVar25 = uVar25 + 1;
        iVar20 = iVar20 + 0x10;
      } while (uVar25 != 0x18);
      mt_dynamic_wmm_be_tx_op(param_1,0x32);
      return;
    case 0x58:
      EventTxPowerHandler(param_1,__s1,uVar22);
      return;
    case 0x6b:
      if (__s1 == (void *)0x0) {
        if (DebugLevel < 0) {
          return;
        }
        printk("%s:: Data is NULL\n","ExtEventGBand256QamProbeResule",uVar11);
        return;
      }
      uVar25 = CONCAT11(*(undefined1 *)(iVar23 + 0xe),*(undefined1 *)(iVar23 + 0xc)) & 0x3ff;
      if (param_1[uVar25 * 0x530 + 0x28748] == 0) {
        if (DebugLevel < 0) {
          return;
        }
        printk("%s:: pEntry is NONE\n","ExtEventGBand256QamProbeResule");
        return;
      }
      if (*(char *)(iVar23 + 0xd) == '\x01') {
        *(undefined1 *)((int)param_1 + uVar25 * 0x14c0 + 0xa291d) = 1;
      }
      if (DebugLevel < 3) {
        return;
      }
      printk("%s::Gband256QAMSupport = %d\n","ExtEventGBand256QamProbeResule",
             *(undefined1 *)(iVar23 + 0xd));
      return;
    case 0x74:
      uVar22 = (uint)*(byte *)(iVar23 + 0xc);
      uVar25 = *(uint *)(iVar23 + 0x10);
      param_1[uVar22 * 0x530 + 0x28c1e] = uVar25;
      param_1[uVar22 * 0x530 + 0x28c22] = *(int *)(iVar23 + 0x14);
      if (param_1[uVar22 * 0x530 + 0x28c20] != 0) {
        uVar25 = param_1[uVar22 * 0x530 + 0x28c20] + uVar25 >> 1;
      }
      param_1[uVar22 * 0x530 + 0x28c20] = uVar25;
      if (param_1[uVar22 * 0x530 + 0x28c23] == 0) {
        uVar25 = param_1[uVar22 * 0x530 + 0x28c22];
      }
      else {
        uVar25 = (uint)(param_1[uVar22 * 0x530 + 0x28c23] + param_1[uVar22 * 0x530 + 0x28c22]) >> 1;
      }
      param_1[uVar22 * 0x530 + 0x28c23] = uVar25;
      return;
    case 0x75:
      iVar23 = wdev_search_by_band_omac_idx
                         (param_1,*(undefined1 *)(iVar23 + 0xc),*(undefined1 *)(iVar23 + 0xd));
      if (iVar23 == 0) {
        return;
      }
      bss_color_event_handler();
      return;
    case 0x87:
      goto switchD_001a9098_caseD_87;
    case 0x89:
      iVar23 = *(int *)(iVar23 + 0xc);
      if (DebugLevel < 3) {
        if (iVar23 != 0x18) {
          return;
        }
      }
      else {
        printk("%s: u4EventId = %u, len = %u\n","ExtEventMuruHandler",iVar23,uVar22);
        if (iVar23 != 0x18) {
          return;
        }
        if (2 < DebugLevel) {
          printk("%s: MURU_EVENT_TUNE_AP_MUEDCA\n","ExtEventMuruHandler");
        }
      }
      muru_tune_ap_muedca_handler(param_1,__s1,uVar22 & 0xffff);
      return;
    case 0x8b:
      event_ecc_result(param_1,__s1,uVar22);
      return;
    case 0xa3:
      if (__s1 == (void *)0x0) {
        return;
      }
      if (DebugLevel < 1) {
        return;
      }
      printk("%s(): obss percentage: %d, ipi percentage: %d\n","ExtEventIdlePwrReportHandler",
             *(undefined1 *)(iVar23 + 0xc),*(undefined1 *)(iVar23 + 0xd));
      return;
    case 0xa4:
      if (*(char *)(iVar23 + 0xc) != '\0') {
        return;
      }
      EventRxvReport(param_1,__s1,uVar22);
      return;
    case 0xa5:
      ExtEvenTpcInfoHandler(param_1,__s1,uVar22);
      return;
    case 0xa8:
      EventSrHandler(param_1,__s1,uVar22);
      return;
    case 0xad:
      EventPhyStatHandler(param_1,__s1,uVar22);
      return;
    }
  }
  uVar25 = param_1[0xa5b19] & 0xffff;
  if (uVar25 != 0x7628 && uVar25 != 0x7603) {
    uVar22 = 0x7606;
    bVar31 = 0x7605 < uVar25;
    bVar30 = uVar25 == 0x7606;
    if (!bVar30) {
      bVar31 = uVar25 != 0x7636;
    }
    if (!bVar31 || (bVar30 || uVar25 == 0x7637)) {
      uVar22 = 1;
    }
    if (bVar31 && (!bVar30 && uVar25 != 0x7637)) {
      uVar22 = 0;
    }
    if (uVar25 == 0x7611) {
      uVar22 = uVar22 | 1;
    }
    if (uVar22 == 0) goto LAB_001a9440;
  }
  mac_io_read32(param_1[0x29e5e8],0x820f5020,local_50);
  if (*(char *)((int)param_1 + 0xa7851a) == '\x01') {
    uVar25 = (uint)local_50[0] | 0x400000;
  }
  else {
    uVar25 = (uint)local_50[0] & 0xffbfffff;
  }
  if (*(char *)((int)param_1 + 0xa7851b) == '\x01') {
    local_50[0] = (char *)(uVar25 | 0x800000);
  }
  else {
    local_50[0] = (char *)(uVar25 & 0xff7fffff);
  }
  mac_io_write32(param_1[0x29e5e8],0x820f5020);
LAB_001a9440:
  if (3 < DebugLevel) {
    printk(&_LC95,"EventChPrivilegeHandler");
  }
  return;
switchD_001a9098_caseD_87:
  iVar20 = *(int *)(iVar23 + 0xc);
  if (DebugLevel < 0) {
    if (iVar20 == 0) {
      local_50[0] = "CCK";
      local_50[1] = &DAT_0030519c;
      local_50[2] = "HT-MIX";
      local_50[3] = "HT-GF";
      local_50[4] = &DAT_003051b4;
      local_50[5] = "HE-SU";
      local_50[6] = "HE-EXT-SU";
      local_50[7] = "HE-TB";
      local_50[8] = "HE-MU";
      local_50[9] = "UnKnown";
      local_7c[0] = "";
      local_7c[1] = &DAT_00305194;
      local_7c[2] = &DAT_00305170;
      local_7c[3] = &DAT_00305178;
      puStack_6c = &DAT_00305180;
      pcStack_68 = "BW160";
      local_64[0] = "996-tone";
      local_64[1] = "484-tone";
      local_64[2] = "242-tone";
      local_64[3] = "<106-tone";
      uVar25 = (uint)*(ushort *)(iVar23 + 0x12);
      sVar21 = *(short *)(iVar23 + 0x14);
      local_54 = "UnKnown";
      uVar18 = *(ushort *)(iVar23 + 0x16);
      uVar22 = ((uint)*(ushort *)
                       ((int)param_1 + (uint)*(ushort *)(iVar23 + 0x10) * 0x14c0 + 0xa1dde) << 0x17)
               >> 0x1e;
      goto LAB_001aa1a0;
    }
    if (iVar20 != 1) {
      return;
    }
LAB_001a95c8:
    uVar18 = *(ushort *)(iVar23 + 0x16);
  }
  else {
    printk("%s: u4EventId = %u, len = %u\n","HeRaEventDispatcher",iVar20,uVar22 & 0xffff);
    if (iVar20 == 0) {
      if (DebugLevel < 0) {
        local_50[0] = "CCK";
        local_50[1] = &DAT_0030519c;
        local_50[2] = "HT-MIX";
        local_50[3] = "HT-GF";
        local_50[4] = &DAT_003051b4;
        local_50[5] = "HE-SU";
        local_50[6] = "HE-EXT-SU";
        local_50[7] = "HE-TB";
        local_50[8] = "HE-MU";
        local_50[9] = "UnKnown";
        local_7c[0] = "";
        local_7c[1] = &DAT_00305194;
        local_7c[2] = &DAT_00305170;
        local_7c[3] = &DAT_00305178;
        puStack_6c = &DAT_00305180;
        pcStack_68 = "BW160";
        local_64[0] = "996-tone";
        local_64[1] = "484-tone";
        local_64[2] = "242-tone";
        local_64[3] = "<106-tone";
        sVar21 = *(short *)(iVar23 + 0x14);
        local_54 = "UnKnown";
        uVar25 = (uint)*(ushort *)(iVar23 + 0x12);
        uVar18 = *(ushort *)(iVar23 + 0x16);
        uVar22 = ((uint)*(ushort *)
                         ((int)param_1 + (uint)*(ushort *)(iVar23 + 0x10) * 0x14c0 + 0xa1dde) <<
                 0x17) >> 0x1e;
        if (sVar21 != 0) {
LAB_001aa668:
          if (-1 < DebugLevel) {
            printk(" Uplink\n");
          }
        }
      }
      else {
        printk("%s: HERA_RU_RA_INFO_EVENT\n","HeRaEventDispatcher");
        local_50[0] = "CCK";
        local_50[1] = &DAT_0030519c;
        local_50[2] = "HT-MIX";
        local_50[3] = "HT-GF";
        local_50[4] = &DAT_003051b4;
        local_50[5] = "HE-SU";
        local_50[6] = "HE-EXT-SU";
        local_50[7] = "HE-TB";
        local_50[8] = "HE-MU";
        local_50[9] = "UnKnown";
        local_7c[0] = "";
        local_7c[1] = &DAT_00305194;
        local_7c[2] = &DAT_00305170;
        local_7c[3] = &DAT_00305178;
        puStack_6c = &DAT_00305180;
        pcStack_68 = "BW160";
        local_64[0] = "996-tone";
        local_64[1] = "484-tone";
        local_64[2] = "242-tone";
        local_64[3] = "<106-tone";
        uVar25 = (uint)*(ushort *)(iVar23 + 0x12);
        local_54 = "UnKnown";
        uVar18 = *(ushort *)(iVar23 + 0x16);
        sVar21 = *(short *)(iVar23 + 0x14);
        uVar22 = ((uint)*(ushort *)
                         ((int)param_1 + (uint)*(ushort *)(iVar23 + 0x10) * 0x14c0 + 0xa1dde) <<
                 0x17) >> 0x1e;
        if ((-1 < DebugLevel) &&
           (printk("\nWLAN ID : %d\n",(uint)*(ushort *)(iVar23 + 0x10)), -1 < DebugLevel)) {
          printk("RU Idx : %d",uVar25);
          if (sVar21 != 0) goto LAB_001aa668;
          if (-1 < DebugLevel) {
            printk(" Downlink\n");
          }
        }
      }
LAB_001aa1a0:
      if ((uVar18 & 1) != 0) {
        if (DebugLevel < 0) {
LAB_001aa1bc:
          uVar22 = (uint)*(ushort *)(iVar23 + 0x30);
          if (uVar22 == 0) goto LAB_001aa1ec;
LAB_001aa1c8:
          iVar20 = DebugLevel;
          uVar25 = __aeabi_idiv((uVar22 - *(ushort *)(iVar23 + 0x2e)) * 1000,uVar22);
        }
        else {
          iVar20 = printk("Group: Short-Term RA\n");
          if (-1 < DebugLevel) {
            uVar28 = (uint)*(ushort *)(iVar23 + 0x28);
            uVar29 = (uVar28 << 0x13) >> 0x1c;
            if (uVar25 == 0) {
              uVar27 = uVar29;
              if (4 < uVar29) {
                if (uVar29 == 8) {
                  uVar27 = 5;
                }
                else {
                  uVar27 = 9;
                }
              }
              pcVar12 = local_50[uVar27];
              pcVar16 = local_7c[(uVar22 - ((uVar28 << 0x11) >> 0x1e) & 0xff) + 2];
            }
            else {
              if (sVar21 == 0) {
                iVar15 = 0x20;
              }
              else {
                iVar15 = 0x1c;
              }
              if (uVar25 < 3) {
                iVar20 = 0;
              }
              pcVar12 = *(char **)((int)local_50 + iVar15);
              if (2 < uVar25) {
                if (uVar25 - 3 < 4) {
                  iVar20 = 1;
                }
                else {
                  iVar20 = getTone_part_0(uVar25);
                }
              }
              pcVar16 = local_64[iVar20];
            }
            uVar27 = (uVar28 << 0x1b) >> 0x1f;
            if (uVar29 == 2) {
              uVar10 = uVar28 & 0x3f;
            }
            else {
              uVar10 = uVar28 & 0xf;
            }
            if (uVar29 < 5) {
              uVar27 = 0;
            }
            printk("\tCurrRate : 0x%x %s %s NSS%d MCS%d %s\n",uVar28,pcVar12,pcVar16,
                   ((uVar28 << 0x17) >> 0x1d) + 1,uVar10,local_7c[uVar27]);
            if (-1 < DebugLevel) {
              iVar20 = printk("\tNoRateUpCnt : %d\n",*(undefined1 *)(iVar23 + 0x36));
              if (DebugLevel < 0) goto LAB_001aaaf4;
              uVar28 = *(uint *)(iVar23 + 0x18);
              uVar29 = (uVar28 << 0x13) >> 0x1c;
              if (uVar25 == 0) {
                uVar27 = uVar29;
                if (4 < uVar29) {
                  if (uVar29 == 8) {
                    uVar27 = 5;
                  }
                  else {
                    uVar27 = 9;
                  }
                }
                pcVar12 = local_50[uVar27];
                pcVar16 = local_7c[(uVar22 - ((uVar28 << 0x11) >> 0x1e) & 0xff) + 2];
              }
              else {
                if (sVar21 == 0) {
                  iVar15 = 0x20;
                }
                else {
                  iVar15 = 0x1c;
                }
                if (uVar25 < 3) {
                  iVar20 = 0;
                }
                pcVar12 = *(char **)((int)local_50 + iVar15);
                if (2 < uVar25) {
                  if (uVar25 - 3 < 4) {
                    iVar20 = 1;
                  }
                  else {
                    iVar20 = getTone_part_0(uVar25);
                  }
                }
                pcVar16 = local_64[iVar20];
              }
              uVar27 = (uVar28 << 0x1b) >> 0x1f;
              if (uVar29 == 2) {
                uVar10 = uVar28 & 0x3f;
              }
              else {
                uVar10 = uVar28 & 0xf;
              }
              if (uVar29 < 5) {
                uVar27 = 0;
              }
              printk("\tSuggestTxModeRate : 0x%x %s %s NSS%d MCS%d %s\n",uVar28,pcVar12,pcVar16,
                     ((uVar28 << 0x17) >> 0x1d) + 1,uVar10,local_7c[uVar27]);
              if (-1 < DebugLevel) {
                iVar20 = printk("\tSuggestWF : %d\n",*(undefined1 *)(iVar23 + 0x3b));
                goto LAB_001aaa40;
              }
            }
            goto LAB_001aa1bc;
          }
LAB_001aaa40:
          if (-1 < DebugLevel) {
            uVar28 = (uint)*(ushort *)(iVar23 + 0x34);
            uVar29 = (uVar28 << 0x13) >> 0x1c;
            if (uVar25 == 0) {
              uVar27 = uVar29;
              if (4 < uVar29) {
                if (uVar29 == 8) {
                  uVar27 = 5;
                }
                else {
                  uVar27 = 9;
                }
              }
              pcVar12 = local_50[uVar27];
              pcVar16 = local_7c[(uVar22 - ((uVar28 << 0x11) >> 0x1e) & 0xff) + 2];
            }
            else {
              if (sVar21 == 0) {
                iVar15 = 0x20;
              }
              else {
                iVar15 = 0x1c;
              }
              if (uVar25 < 3) {
                iVar20 = 0;
              }
              pcVar12 = *(char **)((int)local_50 + iVar15);
              if (2 < uVar25) {
                if (uVar25 - 3 < 4) {
                  iVar20 = 1;
                }
                else {
                  iVar20 = getTone_part_0(uVar25);
                }
              }
              pcVar16 = local_64[iVar20];
            }
            uVar27 = (uVar28 << 0x1b) >> 0x1f;
            if (uVar29 == 2) {
              uVar10 = uVar28 & 0x3f;
            }
            else {
              uVar10 = uVar28 & 0xf;
            }
            if (uVar29 < 5) {
              uVar27 = 0;
            }
            printk("\tStartProbeUpMCS : 0x%x %s %s NSS%d MCS%d %s\n",uVar28,pcVar12,pcVar16,
                   ((uVar28 << 0x17) >> 0x1d) + 1,uVar10,local_7c[uVar27]);
            if (-1 < DebugLevel) {
              printk("\tIsProbeUpPeriod : %d\n",*(undefined1 *)(iVar23 + 0x3d));
LAB_001aaaf4:
              if (DebugLevel < 0) goto LAB_001aabe8;
              printk("\tInitRateDownTotalCnt : %d\n",*(undefined2 *)(iVar23 + 0x2a));
              if (-1 < DebugLevel) {
                iVar20 = printk("\tInitRateDownOkCnt : %d\n",*(undefined2 *)(iVar23 + 0x2c));
                goto LAB_001aab34;
              }
            }
            goto LAB_001aa1bc;
          }
LAB_001aab34:
          if (-1 < DebugLevel) {
            uVar28 = *(uint *)(iVar23 + 0x24);
            uVar29 = (uVar28 << 0x13) >> 0x1c;
            if (uVar25 == 0) {
              uVar27 = uVar29;
              if (4 < uVar29) {
                if (uVar29 == 8) {
                  uVar27 = 5;
                }
                else {
                  uVar27 = 9;
                }
              }
              pcVar12 = local_50[uVar27];
              pcVar16 = local_7c[(uVar22 - ((uVar28 << 0x11) >> 0x1e) & 0xff) + 2];
            }
            else {
              if (sVar21 == 0) {
                iVar15 = 0x20;
              }
              else {
                iVar15 = 0x1c;
              }
              if (uVar25 < 3) {
                iVar20 = 0;
              }
              pcVar12 = *(char **)((int)local_50 + iVar15);
              if (2 < uVar25) {
                if (uVar25 - 3 < 4) {
                  iVar20 = 1;
                }
                else {
                  iVar20 = getTone_part_0(uVar25);
                }
              }
              pcVar16 = local_64[iVar20];
            }
            uVar27 = (uVar28 << 0x1b) >> 0x1f;
            if (uVar29 == 2) {
              uVar10 = uVar28 & 0x3f;
            }
            else {
              uVar10 = uVar28 & 0xf;
            }
            if (uVar29 < 5) {
              uVar27 = 0;
            }
            printk("\tInitRateDownMCS : 0x%x %s %s NSS%d MCS%d %s\n",uVar28,pcVar12,pcVar16,
                   ((uVar28 << 0x17) >> 0x1d) + 1,uVar10,local_7c[uVar27]);
            if (-1 < DebugLevel) {
              printk("\tProbeDownPending : %d\n",*(undefined1 *)(iVar23 + 0x3e));
LAB_001aabe8:
              if (DebugLevel < 0) goto LAB_001aace0;
              printk("\tStSucceCnt : %d\n",*(undefined2 *)(iVar23 + 0x2e));
              if (-1 < DebugLevel) {
                iVar20 = printk("\tStTotalTxCnt : %d\n",*(undefined2 *)(iVar23 + 0x30));
                goto LAB_001aac28;
              }
            }
            goto LAB_001aa1bc;
          }
LAB_001aac28:
          if (-1 < DebugLevel) {
            uVar28 = (uint)*(ushort *)(iVar23 + 0x32);
            uVar29 = (uVar28 << 0x13) >> 0x1c;
            if (uVar25 == 0) {
              uVar25 = uVar29;
              if (4 < uVar29) {
                if (uVar29 == 8) {
                  uVar25 = 5;
                }
                else {
                  uVar25 = 9;
                }
              }
              pcVar16 = local_50[uVar25];
              pcVar12 = local_7c[(uVar22 - ((uVar28 << 0x11) >> 0x1e) & 0xff) + 2];
            }
            else {
              if (sVar21 == 0) {
                iVar15 = 0x20;
              }
              else {
                iVar15 = 0x1c;
              }
              if (uVar25 < 3) {
                iVar20 = 0;
              }
              pcVar16 = *(char **)((int)local_50 + iVar15);
              if (2 < uVar25) {
                if (uVar25 - 3 < 4) {
                  iVar20 = 1;
                }
                else {
                  iVar20 = getTone_part_0(uVar25);
                }
              }
              pcVar12 = local_64[iVar20];
            }
            uVar25 = (uVar28 << 0x1b) >> 0x1f;
            if (uVar29 == 2) {
              uVar22 = uVar28 & 0x3f;
            }
            else {
              uVar22 = uVar28 & 0xf;
            }
            if (uVar29 < 5) {
              uVar25 = 0;
            }
            printk("\tRuPrevRate : 0x%x %s %s NSS%d MCS%d %s\n",uVar28,pcVar16,pcVar12,
                   ((uVar28 << 0x17) >> 0x1d) + 1,uVar22,local_7c[uVar25]);
            if (-1 < DebugLevel) {
              printk("\tStTotalPpduCnt : %d\n",*(undefined1 *)(iVar23 + 0x37));
LAB_001aace0:
              if (DebugLevel < 0) goto LAB_001aad64;
              printk("\tGI : %d\n",*(undefined1 *)(iVar23 + 0x38));
              if (-1 < DebugLevel) {
                printk("\tRuTryupFailCnt : %d\n",*(undefined1 *)(iVar23 + 0x39));
                goto LAB_001aad20;
              }
            }
            goto LAB_001aa1bc;
          }
LAB_001aad20:
          if ((DebugLevel < 0) ||
             (printk("\tRuTryupCnt : %d\n",*(undefined1 *)(iVar23 + 0x3a)), DebugLevel < 0))
          goto LAB_001aa1bc;
          printk("\tRuTryupCheck : %d\n",*(undefined1 *)(iVar23 + 0x3c));
LAB_001aad64:
          uVar22 = (uint)*(ushort *)(iVar23 + 0x30);
          uVar25 = 0;
          iVar20 = DebugLevel;
          if (uVar22 != 0) goto LAB_001aa1c8;
        }
        if (iVar20 < 0) goto LAB_001aa1ec;
        printk("\tPER : %d.%d%%\n",uVar25 / 10,uVar25 % 10);
      }
      if ((uVar18 & 2) != 0) {
        if (DebugLevel < 0) {
          return;
        }
        printk("Group: Long-Term RA\n");
      }
LAB_001aa1ec:
      if ((uVar18 & 4) == 0) {
        return;
      }
      if (DebugLevel < 0) {
        return;
      }
      printk("Group: Others\n");
      return;
    }
    if (iVar20 != 1) {
      return;
    }
    puVar9 = extraout_r1_02;
    if (DebugLevel < 0) goto LAB_001a95c8;
    printk("%s: HERA_MU_RA_INFO_EVENT\n","HeRaEventDispatcher");
    puVar9 = (undefined4 *)(uint)*(ushort *)(iVar23 + 0x10);
    uVar5 = *(undefined2 *)(iVar23 + 0x12);
    sVar21 = *(short *)(iVar23 + 0x14);
    uVar18 = *(ushort *)(iVar23 + 0x16);
    if (DebugLevel < 0) {
      if (sVar21 != 0) {
LAB_001aa688:
        if (-1 < DebugLevel) {
          printk(" Uplink\n",puVar9);
          puVar9 = extraout_r1_06;
        }
      }
    }
    else {
      printk("\nMU Group ID : %d\n",puVar9);
      puVar9 = extraout_r1_03;
      if (-1 < DebugLevel) {
        printk("User Idx : %d",uVar5);
        puVar9 = extraout_r1_04;
        if (sVar21 != 0) goto LAB_001aa688;
        if (-1 < DebugLevel) {
          printk(" Downlink\n");
          puVar9 = extraout_r1_05;
        }
      }
    }
  }
  if ((uVar18 & 1) != 0) {
    if (DebugLevel < 0) {
LAB_001a95e8:
      uVar22 = (uint)*(ushort *)(iVar23 + 0x30);
      if (uVar22 == 0) goto LAB_001a9618;
LAB_001a95f4:
      iVar20 = DebugLevel;
      lVar32 = __aeabi_idiv((uVar22 - *(ushort *)(iVar23 + 0x2e)) * 1000,uVar22);
    }
    else {
      printk("Group: Short-Term RA\n",puVar9);
      puVar9 = extraout_r1_07;
      if (-1 < DebugLevel) {
        uVar25 = (uint)*(ushort *)(iVar23 + 0x28);
        uVar22 = (uVar25 << 0x13) >> 0x1c;
        uVar28 = (uVar25 << 0x1b) >> 0x1f;
        if (uVar22 == 2) {
          uVar29 = uVar25 & 0x3f;
        }
        else {
          uVar29 = uVar25 & 0xf;
        }
        if (uVar22 < 5) {
          uVar28 = 0;
        }
        printk("\tCurrRate : 0x%x Mode=%d NSS%d MCS%d DCM=%x\n",uVar25,uVar22,
               ((uVar25 << 0x17) >> 0x1d) + 1,uVar29,uVar28);
        puVar9 = extraout_r1_08;
        if (-1 < DebugLevel) {
          printk("\tNoRateUpCnt : %d\n",*(undefined1 *)(iVar23 + 0x36));
          uVar25 = extraout_r1_09;
          if (DebugLevel < 0) goto LAB_001ab070;
          uVar25 = *(uint *)(iVar23 + 0x18);
          uVar22 = (uVar25 << 0x13) >> 0x1c;
          uVar28 = (uVar25 << 0x1b) >> 0x1f;
          if (uVar22 == 2) {
            uVar29 = uVar25 & 0x3f;
          }
          else {
            uVar29 = uVar25 & 0xf;
          }
          if (uVar22 < 5) {
            uVar28 = 0;
          }
          printk("\tSuggestTxModeRate : 0x%x Mode=%d NSS%d MCS%d DCM=%x\n",uVar25,uVar22,
                 ((uVar25 << 0x17) >> 0x1d) + 1,uVar29,uVar28);
          puVar9 = extraout_r1_10;
          if (-1 < DebugLevel) {
            printk("\tSuggestWF : %d\n",*(undefined1 *)(iVar23 + 0x3b));
            puVar9 = extraout_r1_11;
            goto LAB_001ab030;
          }
        }
        goto LAB_001a95e8;
      }
LAB_001ab030:
      if (-1 < DebugLevel) {
        printk("\tStartProbeUpMCS : %x\n",*(undefined2 *)(iVar23 + 0x34));
        puVar9 = extraout_r1_12;
        if (-1 < DebugLevel) {
          printk("\tIsProbeUpPeriod : %d\n",*(undefined1 *)(iVar23 + 0x3d));
          uVar25 = extraout_r1_13;
LAB_001ab070:
          if (DebugLevel < 0) goto LAB_001ab118;
          printk("\tInitRateDownTotalCnt : %d\n",*(undefined2 *)(iVar23 + 0x2a));
          puVar9 = extraout_r1_14;
          if (-1 < DebugLevel) {
            printk("\tInitRateDownOkCnt : %d\n",*(undefined2 *)(iVar23 + 0x2c));
            puVar9 = extraout_r1_15;
            goto LAB_001ab0b0;
          }
        }
        goto LAB_001a95e8;
      }
LAB_001ab0b0:
      if (-1 < DebugLevel) {
        uVar25 = *(uint *)(iVar23 + 0x24);
        uVar22 = (uVar25 << 0x13) >> 0x1c;
        uVar28 = (uVar25 << 0x1b) >> 0x1f;
        if (uVar22 == 2) {
          uVar29 = uVar25 & 0x3f;
        }
        else {
          uVar29 = uVar25 & 0xf;
        }
        if (uVar22 < 5) {
          uVar28 = 0;
        }
        printk("\tInitRateDownMCS : 0x%x Mode=%d NSS%d MCS%d DCM=%x\n",uVar25,uVar22,
               ((uVar25 << 0x17) >> 0x1d) + 1,uVar29,uVar28);
        puVar9 = extraout_r1_16;
        if (-1 < DebugLevel) {
          printk("\tProbeDownPending : %d\n",*(undefined1 *)(iVar23 + 0x3e));
          uVar25 = extraout_r1_17;
LAB_001ab118:
          if (DebugLevel < 0) goto LAB_001ab1c0;
          printk("\tStSucceCnt : %d\n",*(undefined2 *)(iVar23 + 0x2e));
          puVar9 = extraout_r1_18;
          if (-1 < DebugLevel) {
            printk("\tStTotalTxCnt : %d\n",*(undefined2 *)(iVar23 + 0x30));
            puVar9 = extraout_r1_19;
            goto LAB_001ab158;
          }
        }
        goto LAB_001a95e8;
      }
LAB_001ab158:
      if (-1 < DebugLevel) {
        uVar25 = (uint)*(ushort *)(iVar23 + 0x32);
        uVar22 = (uVar25 << 0x13) >> 0x1c;
        uVar28 = (uVar25 << 0x1b) >> 0x1f;
        if (uVar22 == 2) {
          uVar29 = uVar25 & 0x3f;
        }
        else {
          uVar29 = uVar25 & 0xf;
        }
        if (uVar22 < 5) {
          uVar28 = 0;
        }
        printk("\tRuPrevRate : 0x%x Mode=%d NSS%d MCS%d DCM=%x\n",uVar25,uVar22,
               ((uVar25 << 0x17) >> 0x1d) + 1,uVar29,uVar28);
        puVar9 = extraout_r1_20;
        if (-1 < DebugLevel) {
          printk("\tStTotalPpduCnt : %d\n",*(undefined1 *)(iVar23 + 0x37));
          uVar25 = extraout_r1_21;
LAB_001ab1c0:
          if (DebugLevel < 0) goto LAB_001ab244;
          printk("\tGI : %d\n",*(undefined1 *)(iVar23 + 0x38));
          puVar9 = extraout_r1_22;
          if (-1 < DebugLevel) {
            printk("\tRuTryupFailCnt : %d\n",*(undefined1 *)(iVar23 + 0x39));
            puVar9 = extraout_r1_23;
            goto LAB_001ab200;
          }
        }
        goto LAB_001a95e8;
      }
LAB_001ab200:
      if ((DebugLevel < 0) ||
         (printk("\tRuTryupCnt : %d\n",*(undefined1 *)(iVar23 + 0x3a)), puVar9 = extraout_r1_24,
         DebugLevel < 0)) goto LAB_001a95e8;
      printk("\tRuTryupCheck : %d\n",*(undefined1 *)(iVar23 + 0x3c));
      uVar25 = extraout_r1_25;
LAB_001ab244:
      uVar22 = (uint)*(ushort *)(iVar23 + 0x30);
      lVar32 = (ulonglong)uVar25 << 0x20;
      iVar20 = DebugLevel;
      if (uVar22 != 0) goto LAB_001a95f4;
    }
    puVar9 = (undefined4 *)((ulonglong)lVar32 >> 0x20);
    if (iVar20 < 0) goto LAB_001a9618;
    printk("\tPER : %d.%d%%\n",(uint)lVar32 / 10,(uint)lVar32 % 10);
    puVar9 = extraout_r1;
  }
  if ((uVar18 & 2) != 0) {
    if (DebugLevel < 0) {
      return;
    }
    printk("Group: Long-Term RA\n",puVar9);
    puVar9 = extraout_r1_00;
  }
LAB_001a9618:
  if ((uVar18 & 4) == 0) {
    return;
  }
  if (DebugLevel < 0) {
    return;
  }
  printk("Group: Others\n",puVar9);
  return;
}

