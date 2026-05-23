// module: mt7915.ko
// function: RTMP_COM_IoctlHandle @ 0xb8e14
// size: 5108 bytes
//

uint RTMP_COM_IoctlHandle
               (int *param_1,int param_2,int param_3,undefined4 param_4,uint *param_5,int param_6)

{
  byte bVar1;
  char *pcVar2;
  undefined1 uVar3;
  char cVar4;
  char cVar5;
  int *piVar6;
  undefined4 uVar7;
  uint uVar8;
  uint uVar9;
  byte *pbVar10;
  uint uVar11;
  undefined4 extraout_r1;
  ushort uVar12;
  undefined1 *puVar13;
  uint uVar14;
  uint *puVar15;
  int iVar16;
  int iVar17;
  int *piVar18;
  uint uVar19;
  uint uVar20;
  bool bVar21;
  undefined8 uVar22;
  byte *local_50;
  int *piStack_4c;
  uint *local_48;
  uint local_3c;
  ushort local_38;
  undefined1 local_36 [2];
  int local_34;
  byte local_30;
  byte abStack_2f [4];
  undefined1 local_2b;
  
  iVar17 = *param_1;
  piVar6 = (int *)get_wdev_by_ioctl_idx_and_iftype
                            (param_1,*(undefined4 *)(iVar17 + 0x3c),*(undefined4 *)(iVar17 + 0x38));
  uVar9 = (uint)*(byte *)((int)param_1 + 0x286285);
  if (uVar9 == 0) {
    piVar6 = param_1 + *(int *)(iVar17 + 0x3c) * 0x84dec + 0xdb6d6;
    piVar18 = piVar6;
  }
  else {
    piVar18 = (int *)0x0;
  }
  if (param_3 == 0x5032) {
    *param_5 = *(byte *)(param_1 + 0xa5b73) & 0xf;
    return 0;
  }
  if (0x5032 < param_3) {
    if (param_3 == 0x503c) {
      param_5[1] = param_1[0x29def0];
      if (*(char *)((int)param_1 + 0x286285) == '\0') {
        param_5[2] = param_1[0x28e712];
        param_5[3] = param_1[0x28e700];
        param_5[4] = param_1[0x28e795];
        param_5[5] = param_1[0x28e794];
        param_5[6] = param_1[0x28e6fc];
        param_5[7] = param_1[0x28e6fb];
        uVar9 = param_1[0x28e714];
        param_5[9] = 0;
        param_5[8] = uVar9;
        uVar9 = param_1[0x28e6fd];
        param_5[0xb] = 0;
        param_5[0xc] = 0;
        param_5[10] = uVar9;
        param_5[0xd] = param_1[0x28e6fd];
        return 0;
      }
      if (*(char *)((int)param_1 + 0x286285) != '\x01') {
        return 0;
      }
      puVar15 = (uint *)(param_1 + 0xadc92);
      for (iVar17 = 0; iVar16 = hc_get_chip_bcn_max_num(param_1[0x29e5e8]), iVar17 < iVar16;
          iVar17 = iVar17 + 1) {
        uVar9 = *puVar15;
        puVar15 = puVar15 + 0x160d;
        if (uVar9 == *param_5) {
          param_5[2] = param_1[iVar17 * 0x160d + 0xaed8b];
          param_5[3] = param_1[iVar17 * 0x160d + 0xaed8a];
          param_5[4] = param_1[iVar17 * 0x160d + 0xaed8c];
          param_5[5] = param_1[iVar17 * 0x160d + 0xaed8d];
          param_5[6] = param_1[iVar17 * 0x160d + 0xaed8e];
          param_5[7] = param_1[iVar17 * 0x160d + 0xaed90];
          uVar9 = param_1[iVar17 * 0x160d + 0xaed95];
          param_5[9] = 0;
          param_5[10] = 0;
          param_5[8] = uVar9;
          param_5[0xb] = 0;
          param_5[0xc] = 0;
          param_5[0xd] = 0;
          return 0;
        }
      }
      if (param_1[0xdb6d6] == *param_5) {
        iVar17 = 0;
      }
      else {
        if (((*(char *)((int)param_1 + 0x3678f9) == '\0') ||
            (*(char *)((int)param_1 + 0x3678f9) == '\x01')) || (*param_5 != param_1[0x1604c2])) {
          param_5[2] = 0;
          iVar17 = DebugLevel;
          param_5[3] = 0;
          param_5[4] = 0;
          param_5[5] = 0;
          param_5[6] = 0;
          param_5[7] = 0;
          param_5[8] = 0;
          param_5[9] = 0;
          param_5[10] = 0;
          param_5[0xb] = 0;
          param_5[0xc] = 0;
          param_5[0xd] = 0;
          if (iVar17 < 0) {
            return 1;
          }
          printk("CMD_RTPRIV_IOCTL_INF_STATS_GET: can not find mbss I/F\n");
          return 1;
        }
        iVar17 = 1;
      }
      param_5[2] = param_1[iVar17 * 0x84dec + 0x160335];
      param_5[3] = param_1[(int)(map_check_zte_ie + iVar17 * 0x84dec)];
      param_5[4] = param_1[iVar17 * 0x84dec + 0x160336];
      param_5[5] = param_1[iVar17 * 0x84dec + 0x160337];
      param_5[6] = param_1[iVar17 * 0x84dec + 0x160338];
      param_5[7] = param_1[iVar17 * 0x84dec + 0x16033a];
      uVar9 = param_1[iVar17 * 0x84dec + 0x16033f];
      param_5[9] = 0;
      param_5[10] = 0;
      param_5[8] = uVar9;
      param_5[0xb] = 0;
      param_5[0xc] = 0;
      param_5[0xd] = 0;
      param_5[2] = param_1[iVar17 * 0x84dec + 0x160335];
      param_5[3] = param_1[(int)(map_check_zte_ie + iVar17 * 0x84dec)];
      param_5[4] = param_1[iVar17 * 0x84dec + 0x160336];
      param_5[5] = param_1[iVar17 * 0x84dec + 0x160337];
      param_5[6] = param_1[iVar17 * 0x84dec + 0x160338];
      param_5[7] = param_1[iVar17 * 0x84dec + 0x16033a];
      param_5[8] = param_1[iVar17 * 0x84dec + 0x16033f];
      return 0;
    }
    if (param_3 < 0x503d) {
      if (param_3 == 0x5037) {
        if (0 < DebugLevel) {
          printk("%s -> CMD_RTPRIV_IOCTL_VIRTUAL_INF_DOWN\n","RTMP_COM_IoctlHandle");
        }
        VIRTUAL_IF_DEC(param_1);
        uVar9 = (*(code *)param_5[3])(param_5[4]);
        return uVar9;
      }
      if (param_3 < 0x5038) {
        if (param_3 == 0x5034) {
          if (piVar6 == (int *)0x0) {
            uVar7 = 0;
            if (-1 < DebugLevel) {
              printk("[CMD_RTPRIV_IOCTL_CHAN_LIST_GET] wdev = NULL\n",uVar9);
            }
          }
          else {
            uVar7 = HcGetBandByWdev(piVar6);
          }
          iVar17 = hc_get_channel_ctrl(param_1[0x29e5e8],uVar7);
          if (*(char *)(iVar17 + 0x49c) == '\0') {
            return 0;
          }
          iVar16 = 0;
          uVar9 = 1;
          do {
            puVar13 = (undefined1 *)(iVar17 + iVar16);
            uVar9 = uVar9 + 1;
            iVar16 = iVar16 + 0x14;
            *(undefined1 *)param_5 = *puVar13;
            param_5 = (uint *)((int)param_5 + 1);
          } while (uVar9 <= *(byte *)(iVar17 + 0x49c));
          return 0;
        }
        if (param_3 < 0x5034) {
          if (piVar6 == (int *)0x0) {
            if (DebugLevel < 0) {
              uVar7 = 0;
            }
            else {
              printk("[CMD_RTPRIV_IOCTL_CHAN_LIST_NUM_GET] wdev = NULL\n",uVar9);
              uVar7 = 0;
            }
          }
          else {
            uVar7 = HcGetBandByWdev(piVar6);
          }
          iVar17 = hc_get_channel_ctrl(param_1[0x29e5e8],uVar7);
          *param_5 = (uint)*(byte *)(iVar17 + 0x49c);
          return 0;
        }
        if (param_3 == 0x5035) {
          if (piVar6 == (int *)0x0) {
            if (DebugLevel < 0) {
              uVar7 = 0;
            }
            else {
              printk("[CMD_RTPRIV_IOCTL_FREQ_LIST_GET] wdev = NULL\n",uVar9);
              uVar7 = 0;
            }
          }
          else {
            uVar7 = HcGetBandByWdev(piVar6);
          }
          iVar17 = hc_get_channel_ctrl(param_1[0x29e5e8],uVar7);
          if (*(char *)(iVar17 + 0x49c) == '\0') {
            return 0;
          }
          iVar16 = 0;
          uVar9 = 1;
          do {
            local_30 = 0xe0;
            abStack_2f[0] = 0xcd;
            abStack_2f[1] = 0x24;
            abStack_2f[2] = 0;
            uVar9 = uVar9 + 1;
            RTMP_MapChannelID2KHZ(*(undefined1 *)(iVar17 + iVar16),&local_30);
            iVar16 = iVar16 + 0x14;
            *param_5 = CONCAT13(abStack_2f[2],
                                CONCAT12(abStack_2f[1],CONCAT11(abStack_2f[0],local_30)));
            param_5 = param_5 + 1;
          } while (uVar9 <= *(byte *)(iVar17 + 0x49c));
          return 0;
        }
        if (param_3 == 0x5036) {
          if (0 < DebugLevel) {
            printk("%s -> CMD_RTPRIV_IOCTL_VIRTUAL_INF_UP\n","RTMP_COM_IoctlHandle");
          }
          (*(code *)param_5[2])(param_5[4]);
          return 0;
        }
      }
      else {
        if (param_3 == 0x5039) {
          if (0 < DebugLevel) {
            printk("%s -> CMD_RTPRIV_IOCTL_VIRTUAL_INF_DEINIT\n","RTMP_COM_IoctlHandle");
          }
          (*(code *)param_5[1])(param_5[4]);
          return 0;
        }
        if (param_3 < 0x5039) {
          if (0 < DebugLevel) {
            printk("%s -> CMD_RTPRIV_IOCTL_VIRTUAL_INF_INIT\n","RTMP_COM_IoctlHandle");
          }
          (*(code *)*param_5)(param_5[4]);
          return 0;
        }
        if (param_3 == 0x503a) {
          uVar9 = VIRTUAL_IF_NUM(param_1);
          *param_5 = uVar9;
          return 0;
        }
        if (param_3 == 0x503b) {
          *param_5 = param_1[0xa18a0];
          return 0;
        }
      }
    }
    else {
      if (param_3 == 0x5041) {
        if (param_6 == 0x600) {
          return 0;
        }
        return 1;
      }
      if (param_3 < 0x5042) {
        if (param_3 == 0x503e) {
          uVar9 = RtmpPhyNetDevMainCreate(param_1);
          *param_5 = uVar9;
          return 0;
        }
        if (param_3 < 0x503e) {
          *(undefined1 *)(param_5 + 3) = 0;
          *(undefined1 *)((int)param_5 + 0xd) = 0;
          *(undefined1 *)((int)param_5 + 0xe) = 0;
          param_5[2] = param_1[0x29deef];
          if (*(char *)((int)param_1 + 0x286285) != '\0') {
            if ((param_1[0x28e7e1] & 2U) == 0) {
              return 1;
            }
            if (((*param_5 == 0x400) && (iVar17 = ApCliIfLookUp(param_1,param_5[1]), -1 < iVar17))
               && ((uVar12 = *(ushort *)(param_1 + iVar17 * 0x84dec + 0x16038e),
                   uVar9 = hc_get_chip_wtbl_max_num(param_1[0x29e5e8]), uVar12 < uVar9 &&
                   (uVar9 = (uint)*(ushort *)(param_1 + iVar17 * 0x84dec + 0x16038e),
                   param_1 + uVar9 * 0x530 + 0x28748 != (int *)0x0)))) {
              uVar14 = (uint)(param_1[uVar9 * 0x530 + 0x28c33] * 0xc) / 10 + 10;
              *(char *)(param_5 + 3) = (char)uVar14;
              if (100 < (uVar14 & 0xff)) {
                *(undefined1 *)(param_5 + 3) = 100;
              }
              uVar3 = RTMPMaxRssi(param_1,(int)(char)param_1[uVar9 * 0x530 + 0x2878b],
                                  (int)*(char *)((int)param_1 + uVar9 * 0x14c0 + 0xa1e2d),
                                  (int)*(char *)((int)param_1 + uVar9 * 0x14c0 + 0xa1e2e));
              *(undefined1 *)((int)param_5 + 0xd) = uVar3;
            }
            else {
              uVar9 = (uint)(param_1[0x1e5824] * 0xc) / 10 + 10;
              *(char *)(param_5 + 3) = (char)uVar9;
              if (100 < (uVar9 & 0xff)) {
                *(undefined1 *)(param_5 + 3) = 100;
              }
            }
            cVar4 = RTMPMaxRssi(param_1,(int)(char)param_1[0xdae00],
                                (int)*(char *)((int)param_1 + 0x36b801),
                                (int)*(char *)((int)param_1 + 0x36b802));
            cVar5 = RTMPMinSnr(param_1,(int)(char)param_1[0xdae04],
                               (int)*(char *)((int)param_1 + 0x36b811));
            *(char *)((int)param_5 + 0xe) = cVar4 - cVar5;
            return 0;
          }
          if ((param_1[0x28e7e1] & 2U) == 0) {
            return 1;
          }
          uVar9 = (uint)(piVar18[0x84918] * 0xc) / 10 + 10;
          *(char *)(param_5 + 3) = (char)uVar9;
          if (100 < (uVar9 & 0xff)) {
            *(undefined1 *)(param_5 + 3) = 100;
          }
          uVar3 = RTMPMaxRssi(param_1,(int)(char)piVar18[0x84c73],
                              (int)*(char *)((int)piVar18 + 0x2131cd),
                              (int)*(char *)((int)piVar18 + 0x2131ce));
          *(undefined1 *)((int)param_5 + 0xd) = uVar3;
          cVar4 = RTMPMaxRssi(param_1,(int)(char)piVar18[0x84c73],
                              (int)*(char *)((int)piVar18 + 0x2131cd),
                              (int)*(char *)((int)piVar18 + 0x2131ce));
          cVar5 = RTMPMinSnr(param_1,(int)(char)param_1[0x16034d],
                             (int)*(char *)((int)piVar18 + 0x2131dd));
          *(char *)((int)param_5 + 0xe) = cVar4 - cVar5;
          return 0;
        }
        if (param_3 == 0x503f) {
          *param_5 = 0x100;
          return 0;
        }
        if (param_3 == 0x5040) {
          if (param_6 != 0x100) {
            return 1;
          }
          return 0;
        }
      }
      else {
        if (param_3 == 0x5043) {
          *param_5 = 0x49575452;
          param_5[1] = 0x53204946;
          *(undefined2 *)(param_5 + 3) = 0x50;
          param_5[2] = 0x4174666f;
          return 0;
        }
        if (param_3 < 0x5043) {
          if (*(int *)(iVar17 + 0x38) == 0x400) {
            param_6 = param_6 + 0x30;
          }
          iVar17 = get_wdev_by_idx(param_1,param_6);
          if (iVar17 == 0) {
            return 0;
          }
          *param_5 = (uint)*(byte *)(iVar17 + 0x1a);
          return 0;
        }
        if (param_3 == 0x5044) {
          if (*param_5 == 0x400) {
            iVar16 = *(int *)(iVar17 + 0x3c) * 0x2137b0;
            iVar16 = MacTableLookup2(param_1,(int)param_1 + iVar16 + 0x36db79,
                                     (undefined *)((int)param_1 + (int)(&DAT_0036db58 + iVar16)));
            if (iVar16 == 0) {
              iVar17 = *(int *)(iVar17 + 0x3c);
              bVar1 = *(byte *)((int)param_1 + (int)(&DAT_0036e408 + iVar17 * 0x2137b0 + 3));
              uVar19 = ((uint)bVar1 << 0x1e) >> 0x1f;
              uVar9 = (uint)(bVar1 >> 5);
              uVar14 = ((uint)*(ushort *)
                               ((int)param_1 + (int)(&DAT_0036e408 + iVar17 * 0x2137b0 + 2)) << 0x17
                       ) >> 0x1e;
              pbVar10 = (byte *)(*(byte *)((int)param_1 +
                                          (int)(&DAT_0036e408 + iVar17 * 0x2137b0 + 2)) & 0x3f);
              iVar16 = 0;
            }
            else {
              uVar14 = ((uint)*(ushort *)(iVar16 + 0xbc) << 0x17) >> 0x1e;
              uVar19 = ((uint)*(byte *)(iVar16 + 0xbd) << 0x1e) >> 0x1f;
              uVar9 = (uint)(*(byte *)(iVar16 + 0xbd) >> 5);
              pbVar10 = (byte *)(*(byte *)(iVar16 + 0xbc) & 0x3f);
              if (uVar9 == 4) {
                iVar17 = *(int *)(iVar17 + 0x3c);
                iVar16 = ((int)pbVar10 >> 4) + 1;
              }
              else {
                iVar17 = *(int *)(iVar17 + 0x3c);
                iVar16 = 0;
              }
            }
            piVar6 = param_1 + iVar17 * 0x84dec + 0xdb6d6;
          }
          else {
            iVar16 = 0;
            iVar17 = *(int *)(iVar17 + 0x3c) * 0x5834;
            pcVar2 = "%s: period = %d\n";
            piVar6 = (int *)((int)param_1 +
                            (int)(
                                 "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                 + iVar17 + 0xe0));
            uVar19 = ((uint)*(byte *)((int)param_1 + (int)(pcVar2 + iVar17 + 3)) << 0x1e) >> 0x1f;
            uVar9 = (uint)(*(byte *)((int)param_1 + (int)(pcVar2 + iVar17 + 3)) >> 5);
            uVar14 = ((uint)*(ushort *)((int)param_1 + (int)(pcVar2 + iVar17 + 2)) << 0x17) >> 0x1e;
            pbVar10 = (byte *)(*(byte *)((int)param_1 + (int)(pcVar2 + iVar17 + 2)) & 0x3f);
          }
          if ((char)piVar6[0x2aa] != '\0') {
            if (((uVar9 << 0x1d) >> 0x18 & 0xc0) == 0x40) {
              iVar16 = ((int)pbVar10 >> 3) + 1;
            }
            if (uVar9 < 4) {
              uVar8 = uVar14;
              if (1 < uVar9) {
                uVar8 = wlan_operate_get_ht_bw(piVar6);
              }
            }
            else {
              pbVar10 = (byte *)((uint)pbVar10 & 0xf);
              iVar17 = wlan_operate_get_vht_bw(piVar6);
              if (iVar17 == 0) {
                uVar8 = 1;
              }
              else if (iVar17 == 1) {
                uVar8 = 2;
              }
              else {
                uVar8 = 3;
              }
            }
            if (iVar16 == 0) {
              local_3c = uVar8;
              iVar16 = wlan_config_get_tx_stream(piVar6);
              uVar8 = local_3c;
            }
            local_48 = param_5 + 1;
            local_50 = pbVar10;
            piStack_4c = (int *)iVar16;
            RtmpDrvMaxRateGet(param_1,uVar9,uVar19,uVar8);
            if (uVar9 < 5) {
              return 0;
            }
            local_50 = &local_30;
            local_30 = 0;
            abStack_2f[0] = 0;
            abStack_2f[1] = 0;
            abStack_2f[2] = 0;
            get_rate_he(0xb,uVar14,iVar16);
            uVar9 = CONCAT13(abStack_2f[2],CONCAT12(abStack_2f[1],CONCAT11(abStack_2f[0],local_30)))
            ;
            if (uVar9 < 0xf03) {
              uVar9 = uVar9 * 1000000;
            }
            else {
              uVar9 = 0xe50f86c0;
            }
            param_5[1] = uVar9;
            return 0;
          }
          return 0;
        }
        if (param_3 == 0x5048) {
          chip_eeprom_read16(param_1,4,&local_38);
          chip_eeprom_read16(param_1,6,local_36);
          chip_eeprom_read16(param_1,8,&local_34);
          puVar13 = (undefined1 *)((int)param_5 + -1);
          pbVar10 = &local_30;
          uVar12 = local_38 & 0xff;
          abStack_2f[0] = (char)(local_38 >> 8);
          abStack_2f[1] = local_36[0];
          abStack_2f[2] = local_36[1];
          abStack_2f[3] = (char)(undefined2)local_34;
          local_2b = (char)((ushort)(undefined2)local_34 >> 8);
          while( true ) {
            puVar13 = puVar13 + 1;
            *puVar13 = (char)uVar12;
            if (puVar13 == (undefined1 *)((int)param_5 + 5)) break;
            pbVar10 = pbVar10 + 1;
            uVar12 = (ushort)*pbVar10;
          }
          return 0;
        }
      }
    }
    goto LAB_000b9154;
  }
  if (param_3 == 0x500f) {
    iVar17 = hc_get_chip_ops(param_1[0x29e5e8]);
    if (*(code **)(iVar17 + 0xc0) == (code *)0x0) {
      return 0;
    }
    (**(code **)(iVar17 + 0xc0))(param_1,0);
    return 0;
  }
  if (param_3 < 0x5010) {
    if (param_3 == 0x5002) {
      *param_5 = uVar9;
      return 0;
    }
    if (0x5002 < param_3) {
      if (param_3 == 0x5005) {
        param_1[0x28e7e1] = param_1[0x28e7e1] | 0x100;
        return 0;
      }
      if (param_3 < 0x5006) {
        if (param_3 == 0x5003) {
          *param_5 = (uint)(param_1 + 0xa18a6);
          param_5[2] = (uint)(param_1 + 0xa171a);
          param_5[3] = (uint)(param_1 + 0x1e52ba);
          return 0;
        }
      }
      else {
        if (param_3 == 0x5006) {
          param_1[0x28e7e2] = param_1[0x28e7e2] & 0xffffffdf;
          return 0;
        }
        if (param_3 == 0x500e) {
          iVar17 = hc_get_chip_ops(param_1[0x29e5e8]);
          if (*(code **)(iVar17 + 0xc4) == (code *)0x0) {
            return 0;
          }
          (**(code **)(iVar17 + 0xc4))(param_1,1);
          return 0;
        }
      }
      goto LAB_000b9154;
    }
    if (param_3 == 0x5000) {
      *param_5 = param_1[1];
      return 0;
    }
    if (param_3 < 0x5001) {
      if (param_3 != 0x10) goto LAB_000b9154;
      os_alloc_mem_suspend(param_1,&local_34,0x80c);
      if (local_34 == 0) {
        return 0xfffffff4;
      }
      __memzero(local_34,0x80c);
      uVar9 = (uint)*(ushort *)(param_2 + 0x14);
      uVar14 = *(uint *)(((uint)&local_50 & 0xffffe000) + 8);
      if (!CARRY4(*(uint *)(param_2 + 0x10),uVar9) && *(uint *)(param_2 + 0x10) + uVar9 <= uVar14) {
        uVar14 = 0;
      }
      if (uVar14 == 0) {
        uVar22 = __copy_from_user(local_34);
        uVar7 = (undefined4)((ulonglong)uVar22 >> 0x20);
        if ((int)uVar22 != 0) {
          uVar9 = 0xfffffff2;
          goto LAB_000b9a2c;
        }
      }
      else if (uVar9 != 0) {
        __memzero(local_34,uVar9);
        uVar9 = 0xfffffff2;
        uVar7 = extraout_r1;
        goto LAB_000b9a2c;
      }
      abStack_2f[0] = (byte)local_34;
      abStack_2f[1] = (byte)((uint)local_34 >> 8);
      abStack_2f[2] = (byte)((uint)local_34 >> 0x10);
      abStack_2f[3] = (byte)((uint)local_34 >> 0x18);
      local_30 = 0;
      uVar9 = mt_agent_hqa_cmd_handler(param_1 + 0x29deed,&local_30);
      iVar17 = DebugLevel;
      uVar12 = (*(ushort *)(local_34 + 8) << 8 | *(ushort *)(local_34 + 8) >> 8) + 0xc;
      uVar14 = (uint)uVar12;
      *(ushort *)(param_2 + 0x14) = uVar12;
      if (2 < iVar17) {
        printk("wrq->u.data.length=%d, usr_addr=%p, hqa_addr=%p\n",uVar14,
               *(undefined4 *)(param_2 + 0x10));
        uVar14 = (uint)*(ushort *)(param_2 + 0x14);
      }
      uVar8 = *(uint *)(param_2 + 0x10);
      uVar20 = *(uint *)(((uint)&local_50 & 0xffffe000) + 8);
      uVar11 = uVar8 + uVar14;
      uVar19 = uVar11;
      if (!CARRY4(uVar8,uVar14)) {
        uVar19 = uVar11 - (uVar20 + 1);
      }
      uVar22 = CONCAT44(uVar19,uVar14);
      if (!CARRY4(uVar8,uVar14) && uVar11 <= uVar20) {
        uVar20 = 0;
      }
      if (uVar20 == 0) {
        uVar22 = __copy_to_user(uVar8,local_34);
      }
      uVar7 = (undefined4)((ulonglong)uVar22 >> 0x20);
      if ((int)uVar22 != 0) {
        if (DebugLevel < 0) {
          return 0xfffffff2;
        }
        printk("copy_to_user() fail in %s\n","RTMP_COM_IoctlHandle");
        return 0xfffffff2;
      }
LAB_000b9a2c:
      os_free_mem(local_34,uVar7);
      return uVar9;
    }
    iVar17 = hc_get_chip_cap(param_1[0x29e5e8]);
    param_1[1] = (int)param_5;
    if (*(char *)((int)param_1 + 0x286285) == '\x01') {
      piVar6 = param_1 + 0xadc92;
      if (piVar6 == (int *)0x0) {
        printk(&_LC99,0x340);
        dump_stack();
      }
      RtmpOsSetNetDevWdev(param_5,piVar6);
      local_50 = (byte *)0x0;
      piStack_4c = piVar6;
      local_48 = (uint *)param_1;
      iVar16 = wdev_init(param_1,piVar6,1,param_5);
      if (iVar16 == 0) goto LAB_000b9c1c;
      iVar16 = wdev_ops_register(piVar6,1,ap_wdev_ops,*(undefined1 *)(iVar17 + 0x75));
      if (iVar16 != 0) {
        if (*(char *)((int)param_1 + 0x286285) == '\0') goto LAB_000b9bdc;
        goto LAB_000b9d60;
      }
    }
    else {
      if (*(char *)((int)param_1 + 0x286285) != '\0') goto LAB_000b935c;
LAB_000b9bdc:
      piVar6 = param_1 + 0xdb6d6;
      RtmpOsSetNetDevWdev(param_5,piVar6);
      local_50 = (byte *)0x0;
      piStack_4c = piVar6;
      local_48 = (uint *)param_1;
      iVar16 = wdev_init(param_1,piVar6,2,param_5);
      if (iVar16 == 0) {
LAB_000b9c1c:
        if (-1 < DebugLevel) {
          printk("Assign wdev idx for %s failed, free net device!\n",param_1[1]);
        }
        goto LAB_000b9c30;
      }
      iVar17 = wdev_ops_register(piVar6,2,sta_wdev_ops,*(undefined1 *)(iVar17 + 0x75));
      if (iVar17 != 0) {
LAB_000b9d60:
        if (piVar6 != (int *)0x0) {
          iVar17 = register_idm_fdb_node(param_1[0xa5b1d] * 5,param_5);
          piVar6[0x1016] = iVar17;
        }
LAB_000b935c:
        setHwMirrorFlag(param_5);
        return 0;
      }
    }
    if (-1 < DebugLevel) {
      printk("register wdev_ops %s failed, free net device!\n",param_1[1]);
    }
LAB_000b9c30:
    RtmpOSNetDevFree(param_1[1]);
    return 0;
  }
  if (param_3 == 0x502a) {
    iVar17 = hc_get_hif_ctrl(param_1[0x29e5e8]);
    bVar21 = DebugLevel < 0;
    *(int *)(iVar17 + 0x84) = param_6;
    if (bVar21) {
      return 0;
    }
    printk("PCI CSRBaseAddress =0x%lx, csr_addr=0x%lx!\n",param_6,param_6);
    return 0;
  }
  if (param_3 < 0x502b) {
    if (param_3 == 0x5011) {
      if ((param_1[0x28e7e1] & 2U) != 0) {
        return 0;
      }
      if (param_5 != (uint *)0x0) {
        iVar17 = strcmp((char *)param_5,"Debug");
        if (iVar17 == 0) {
          return 0;
        }
        iVar17 = strcmp((char *)param_5,"OpMode");
        if (iVar17 == 0) {
          return 0;
        }
      }
      return 1;
    }
    if (param_3 < 0x5011) {
      if (piVar18 == (int *)0x0) {
        return 1;
      }
      if ((char)piVar18[0x222] != '\x02') {
        return 1;
      }
      *param_5 = *(uint *)((int)piVar18 + 0x413a);
      *(undefined2 *)(param_5 + 1) = *(undefined2 *)((int)piVar18 + 0x413e);
      return 0;
    }
    if (param_3 != 0x5028) {
      if (param_3 != 0x5029) goto LAB_000b9154;
LAB_000b90e8:
      DriverOwn(param_1);
      chip_set_hif_dma(param_1,2,1);
      chip_interrupt_enable(param_1);
      param_1[0x28e7e1] = param_1[0x28e7e1] & 0xffffffbf;
      MlmeRadioOn(param_1,piVar6);
      param_1[0x28e7e1] = param_1[0x28e7e1] & 0xff7fffff;
      if (piVar18 != (int *)0x0) {
        ba_session_tear_down_all(param_1,*(undefined2 *)((int)piVar18 + 0x2124be));
      }
      goto LAB_000b9154;
    }
  }
  else if (param_3 != 0x502c) {
    if (param_3 < 0x502c) {
      RTMPInitPCIeDevice(param_5,param_1);
      return 0;
    }
    if (param_3 != 0x502d) {
      if (param_3 == 0x5031) {
        uVar7 = get_default_wdev(param_1);
        UpdateBeaconHandler(param_1,uVar7,3);
        return 0;
      }
      goto LAB_000b9154;
    }
    goto LAB_000b90e8;
  }
  uVar9 = param_1[0x28e7e1] | 0x800000;
  param_1[0x28e7e1] = uVar9;
  if (piVar6 != (int *)0x0) {
    MlmeRadioOff(param_1,piVar6);
    uVar9 = param_1[0x28e7e1];
  }
  param_1[0x28e7e1] = uVar9 | 0x40;
  chip_interrupt_disable(param_1);
  chip_set_hif_dma(param_1,2,0);
  FwOwn(param_1);
LAB_000b9154:
  return (uint)(0x504c < param_3);
}

