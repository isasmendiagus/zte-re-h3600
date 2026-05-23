// module: mt7915.ko
// function: PeerSpectrumAction @ 0x13f3a4
// size: 2824 bytes
//

void PeerSpectrumAction(int param_1,int param_2,undefined4 param_3,uint param_4)

{
  undefined1 uVar1;
  bool bVar2;
  bool bVar3;
  int *piVar4;
  int iVar5;
  undefined4 uVar6;
  char *pcVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  int *piVar10;
  bool bVar11;
  uint uVar12;
  int iVar13;
  char *pcVar14;
  byte bVar15;
  uint unaff_r7;
  int iVar16;
  int *piVar17;
  char cVar18;
  bool bVar19;
  char *__dest;
  char cVar20;
  char cVar21;
  char *pcVar22;
  ushort local_34;
  char local_32;
  undefined4 local_30;
  undefined4 uStack_2c;
  
  if (*(char *)(param_1 + 0x795074) != '\x01') {
    return;
  }
  switch(*(undefined1 *)(param_2 + 0x19)) {
  case 0:
    uVar12 = (uint)*(byte *)(param_2 + 0x1c);
    pcVar14 = (char *)(param_2 + 0x1b);
    pcVar7 = (char *)(param_2 + *(int *)(param_2 + 0x908));
    if (pcVar14 + uVar12 + 1 < pcVar7) {
      bVar11 = false;
      do {
        if (*pcVar14 == '&') {
          local_34 = *(ushort *)(pcVar14 + 0xe);
          local_30 = *(char **)(pcVar14 + 6);
          param_4 = (uint)(byte)pcVar14[2];
          bVar11 = true;
          unaff_r7 = (uint)(byte)pcVar14[4];
          uStack_2c = *(undefined4 *)(pcVar14 + 10);
        }
        pcVar14 = pcVar14 + uVar12 + 2;
        uVar12 = (uint)(byte)pcVar14[1];
      } while (pcVar14 + uVar12 + 1 < pcVar7);
      if (bVar11) {
        EnqueueMeasurementRep
                  (param_1,param_2 + 10,*(undefined1 *)(param_2 + 0x1a),param_4,2,unaff_r7,0,0);
      }
    }
    break;
  case 1:
    os_alloc_mem(param_1,&local_30,0x13);
    if (local_30 == (char *)0x0) {
      if (DebugLevel < 0) {
        return;
      }
      printk("%s unable to alloc memory for measure report buffer (size=%zu).\n",
             "PeerMeasureReportAction",0x13);
      return;
    }
    __memzero(&local_34,3);
    pcVar14 = (char *)(param_2 + 0x1b);
    __memzero(local_30,0x13);
    pcVar7 = local_30;
    cVar21 = *(char *)(param_2 + 0x1a);
    pcVar22 = (char *)(param_2 + *(int *)(param_2 + 0x908));
    if (pcVar14 + *(byte *)(param_2 + 0x1c) + 1 < pcVar22) {
      __dest = local_30 + 1;
      bVar11 = false;
      do {
        if (*pcVar14 == '\'') {
          local_32 = pcVar14[4];
          bVar11 = true;
          local_34 = *(ushort *)(pcVar14 + 2);
          if (local_32 == '\0') {
            *pcVar7 = pcVar14[5];
            memmove(__dest,pcVar14 + 6,8);
          }
          else {
            if (local_32 != '\x01') {
              if (local_32 == '\x02') {
                *pcVar7 = pcVar14[5];
                memmove(__dest,pcVar14 + 6,8);
                memmove(pcVar7 + 9,pcVar14 + 0xe,2);
                memmove(pcVar7 + 0xb,pcVar14 + 0x10,8);
                bVar11 = true;
              }
              goto LAB_0013f5c4;
            }
            *pcVar7 = pcVar14[5];
            memmove(__dest,pcVar14 + 6,8);
          }
          memmove(pcVar7 + 9,pcVar14 + 0xe,2);
          bVar11 = true;
          pcVar7[0xb] = pcVar14[0x10];
        }
LAB_0013f5c4:
        pcVar14 = pcVar14 + (byte)pcVar14[1] + 2;
      } while (pcVar14 + (byte)pcVar14[1] + 1 < pcVar22);
      if (!bVar11) goto LAB_0013faac;
      iVar5 = MeasureReqLookUp(param_1,cVar21);
      if (cVar21 == '\0') {
        if (iVar5 != 0) {
LAB_0013fb24:
          MeasureReqDelete(param_1,*(undefined1 *)(iVar5 + 9));
        }
        if (((local_32 == '\0') && ((local_30[0xb] & 8U) != 0)) &&
           (iVar5 = FUN_0013df98(param_1,*local_30), iVar5 == 1)) {
          *(undefined1 *)(param_1 + 0xa37728) = 1;
          *(undefined1 *)(param_1 + 0xa37724) = 0;
        }
      }
      else if (iVar5 != 0) goto LAB_0013fb24;
    }
    else {
LAB_0013faac:
      if (2 < DebugLevel) {
        printk("Invalid Measurement Report Frame.\n");
      }
    }
    os_free_mem(local_30);
    break;
  case 2:
    if (*(char *)(param_1 + 0x79507c) == '\0') {
      if (2 < DebugLevel) {
        printk("%s(): (X) b80211TPC=%d\n","PeerTpcReqAction");
      }
    }
    else {
      iVar5 = param_2 + 0x918;
      uVar6 = ConvertToRssi(param_1,iVar5,0);
      uVar8 = ConvertToRssi(param_1,iVar5,1);
      uVar9 = ConvertToRssi(param_1,iVar5,2);
      iVar5 = RTMPMaxRssi(param_1,uVar6,uVar8,uVar9);
      uVar12 = (uint)*(byte *)(param_2 + 0x1c);
      pcVar7 = (char *)(param_2 + 0x1b);
      pcVar14 = (char *)(param_2 + *(int *)(param_2 + 0x908));
      if (pcVar7 + uVar12 + 1 < pcVar14) {
        bVar11 = false;
        do {
          cVar21 = *pcVar7;
          pcVar7 = pcVar7 + uVar12 + 2;
          uVar12 = (uint)(byte)pcVar7[1];
          if (cVar21 == '\"') {
            bVar11 = true;
          }
        } while (pcVar7 + uVar12 + 1 < pcVar14);
        if (bVar11) {
          EnqueueTPCRep(param_1,param_2 + 10,*(undefined1 *)(param_2 + 0x1a),0x16,iVar5 / 100 & 0xff
                       );
        }
      }
    }
    break;
  case 3:
    if (*(char *)(param_1 + 0x79507c) == '\0') {
      if (DebugLevel < 3) {
        return;
      }
      printk("%s(): (X) b80211TPC=%d\n","PeerTpcRepAction");
      return;
    }
    __memzero(&local_30,2);
    uVar12 = (uint)*(byte *)(param_2 + 0x1c);
    pcVar7 = (char *)(param_2 + 0x1b);
    uVar1 = *(undefined1 *)(param_2 + 0x1a);
    pcVar14 = (char *)(param_2 + *(int *)(param_2 + 0x908));
    if (pcVar7 + uVar12 + 1 < pcVar14) {
      bVar2 = false;
      bVar11 = false;
      bVar19 = false;
      cVar21 = (char)local_30;
      cVar20 = local_30._1_1_;
      do {
        cVar18 = *pcVar7;
        if (cVar18 == '#') {
          cVar21 = pcVar7[2];
          bVar2 = true;
          cVar20 = pcVar7[3];
        }
        pcVar7 = pcVar7 + uVar12 + 2;
        if (cVar18 == '#') {
          bVar11 = bVar2;
          bVar19 = bVar2;
        }
        uVar12 = (uint)(byte)pcVar7[1];
      } while (pcVar7 + uVar12 + 1 < pcVar14);
      if (bVar11) {
        local_30 = (char *)CONCAT31(local_30._1_3_,cVar21);
      }
      if (bVar2) {
        local_30._0_2_ = CONCAT11(cVar20,(char)local_30);
      }
      if ((!bVar19) || (iVar5 = FUN_0013e050(param_1,uVar1), iVar5 == 0)) goto LAB_0013fa50;
      pcVar7 = *(char **)(param_1 + 0x795980);
      if (pcVar7 == (char *)0x0) {
        if (-1 < DebugLevel) {
          printk("%s: pTpcReqTab doesn\'t exist.\n","TpcReqDelete");
          goto LAB_0013fd6c;
        }
      }
      else {
        if (*pcVar7 == '\0') {
          if (DebugLevel < 0) goto LAB_0013fc20;
          printk("pTpcReqTab empty.\n");
        }
        else {
          piVar10 = (int *)FUN_0013e050(param_1,*(undefined1 *)(iVar5 + 9));
          if (piVar10 != (int *)0x0) {
            uVar12 = *(byte *)((int)piVar10 + 9) & 0x1f;
            piVar17 = *(int **)(pcVar7 + uVar12 * 4 + 4);
            _raw_spin_lock_bh(param_1 + 0x79597c);
            if (piVar10 == piVar17) {
LAB_0013fe08:
              *(int *)(pcVar7 + uVar12 * 4 + 4) = *piVar10;
            }
            else {
              for (piVar4 = (int *)*piVar17; piVar4 != (int *)0x0; piVar4 = (int *)*piVar4) {
                if (piVar4 == piVar10) {
                  if (piVar17 == (int *)0x0) goto LAB_0013fe08;
                  *piVar17 = *piVar10;
                  break;
                }
                piVar17 = piVar4;
              }
            }
            __memzero(piVar10,0xc);
            *pcVar7 = *pcVar7 + -1;
            _raw_spin_unlock_bh(param_1 + 0x79597c);
          }
        }
LAB_0013fd6c:
        if (2 < DebugLevel) {
          printk("%s: DialogToken=%x, TxPwr=%d, LinkMargin=%d\n","PeerTpcRepAction",uVar1,
                 (int)(char)local_30,(int)local_30._1_1_);
          goto LAB_0013fa50;
        }
      }
LAB_0013fc20:
      iVar5 = (int)(char)local_30 - (int)local_30._1_1_;
      if (0x1e < iVar5) {
        iVar5 = 0x1f;
      }
      iVar5 = iVar5 << 1;
    }
    else {
LAB_0013fa50:
      iVar5 = (int)(char)local_30 - (int)local_30._1_1_;
      if (0x1e < iVar5) {
        iVar5 = 0x1f;
      }
      iVar5 = iVar5 << 1;
      if (2 < DebugLevel) {
        printk("%s: MaxTxPower = %d (unit: 0.5 dBm)\n","PeerTpcRepAction",iVar5);
      }
    }
    iVar13 = MacTableLookup(param_1,param_2 + 10);
    if (iVar13 == 0) {
      pcVar7 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
               + param_1 + 0xe0;
    }
    else {
      pcVar7 = *(char **)(iVar13 + 8);
    }
    TxPowerTpcFeatureCtrl(param_1,pcVar7,(int)(char)iVar5);
    break;
  case 4:
    RTMPMoveMemory(&local_30,param_2 + 0x1c,3);
    if (*(int *)(param_2 + 0x908) == 0x1e) {
      RTMPMoveMemory(&local_34,param_2 + 0x21,1);
    }
    else {
      local_34 = local_34 & 0xff00;
    }
    if (*(short *)(param_2 + 0x1a) == 0x325) {
      ChannelSwitchAction(param_1,*(undefined2 *)(param_2 + 0x920),local_30._1_1_,
                          (undefined1)local_34);
    }
    iVar13 = *(int *)(param_2 + 0x92c);
    iVar5 = GetStaCfgByWdev(param_1,iVar13);
    uVar6 = HcGetBandByWdev(iVar13);
    pcVar7 = (char *)hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),uVar6);
    __memzero(&local_30,3);
    uVar12 = (uint)*(byte *)(param_2 + 0x1b);
    pcVar14 = (char *)(param_2 + 0x1a);
    pcVar22 = (char *)(param_2 + *(int *)(param_2 + 0x908));
    if (pcVar14 + uVar12 + 1 < pcVar22) {
      bVar2 = false;
      bVar3 = false;
      bVar19 = false;
      bVar11 = false;
      cVar21 = (char)local_30;
      cVar20 = local_30._1_1_;
      cVar18 = local_30._2_1_;
      do {
        if (*pcVar14 == '%') {
          bVar11 = true;
          cVar21 = pcVar14[2];
          cVar20 = pcVar14[3];
          cVar18 = pcVar14[4];
          bVar2 = bVar11;
          bVar19 = bVar11;
          bVar3 = bVar11;
        }
        pcVar14 = pcVar14 + uVar12 + 2;
        uVar12 = (uint)(byte)pcVar14[1];
      } while (pcVar14 + uVar12 + 1 < pcVar22);
      if (bVar19) {
        local_30 = (char *)CONCAT31(local_30._1_3_,cVar21);
      }
      if (bVar3) {
        local_30._0_2_ = CONCAT11(cVar20,(char)local_30);
      }
      if (bVar2) {
        local_30._0_3_ = CONCAT12(cVar18,(undefined2)local_30);
      }
      if (bVar11) {
        iVar16 = *(int *)(iVar13 + 0x14);
        if (iVar16 == 1) {
          iVar16 = FUN_0013df98(param_1,local_30._1_1_);
          if (iVar16 == 1) {
            *(undefined1 *)(param_1 + 0xa37728) = 1;
            *(undefined1 *)(param_1 + 0xa37724) = 0;
          }
          iVar16 = *(int *)(iVar13 + 0x14);
        }
        if (iVar16 != 2) {
          return;
        }
        iVar13 = get_scan_tab_by_wdev(param_1,*(undefined4 *)(param_2 + 0x92c));
        if (iVar5 == 0) {
          if (2 < DebugLevel) {
            printk("\nBssidx is %d, Channel = %d\n",0,*(undefined1 *)(iVar13 + 0x14));
          }
          hex_dump(&_LC21,iVar13 + 0xe,6);
          return;
        }
        iVar16 = BssTableSearch(iVar13,param_2 + 0x10,*(undefined1 *)(iVar5 + 0x1a));
        if (iVar16 == -1) {
          if (DebugLevel < 3) {
            return;
          }
          printk("PeerChSwAnnAction - Bssidx is not found\n");
          return;
        }
        if (DebugLevel < 3) {
          hex_dump(&_LC21,iVar16 * 0xaf4 + iVar13 + 0xe,6);
          cVar21 = local_30._1_1_;
        }
        else {
          printk("\nBssidx is %d, Channel = %d\n",0,*(undefined1 *)(iVar13 + iVar16 * 0xaf4 + 0x14))
          ;
          hex_dump(&_LC21,iVar13 + iVar16 * 0xaf4 + 0xe,6);
          cVar21 = local_30._1_1_;
        }
        if (*(char *)(param_1 + 0x795074) != '\x01' || cVar21 == '\0') {
          return;
        }
        *(undefined1 *)(iVar5 + 0x1a) = 1;
        wlan_operate_set_prim_ch(iVar5);
        LinkDown(param_1,0,*(undefined4 *)(param_2 + 0x92c),param_2);
        MlmeQueueInit(param_1,param_1 + 0x7960f8);
        RtmpusecDelay(1000000);
        if (pcVar7[0x49c] != 0) {
          if (*pcVar7 == cVar21) {
            bVar15 = 0;
          }
          else {
            bVar15 = 0;
            pcVar14 = pcVar7;
            do {
              bVar15 = bVar15 + 1;
              if (bVar15 == pcVar7[0x49c]) goto LAB_0013f830;
              pcVar14 = pcVar14 + 0x14;
            } while (*pcVar14 != cVar21);
          }
          *(char *)(iVar16 * 0xaf4 + iVar13 + 0x14) = cVar21;
          *(char *)(iVar5 + 0x1a) = cVar21;
          wlan_operate_set_prim_ch(iVar5,cVar21);
          if (2 < DebugLevel) {
            printk("%s():Receive channel switch announcement IE (New Channel =%d)\n",
                   "PeerChSwAnnAction",cVar21);
          }
          if (bVar15 < (byte)pcVar7[0x49c]) {
            return;
          }
        }
LAB_0013f830:
        if (DebugLevel < 0) {
          return;
        }
        printk("%s():can not find New Channel=%d in ChannelList[%d]\n","PeerChSwAnnAction",
               *(undefined1 *)(iVar5 + 0x1a));
        return;
      }
    }
    if (2 < DebugLevel) {
      printk("Invalid Channel Switch Action Frame.\n");
    }
  }
  return;
}

