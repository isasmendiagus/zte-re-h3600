// module: mt7915.ko
// function: RTMPAPSetInformation @ 0x3cfbc
// size: 7668 bytes
//

char * RTMPAPSetInformation(int *param_1,undefined4 *param_2,uint param_3)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  undefined1 uVar4;
  char *pcVar5;
  int iVar6;
  undefined4 uVar7;
  size_t sVar8;
  uint uVar9;
  undefined4 uVar10;
  undefined2 uVar11;
  ushort uVar12;
  char *pcVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  char *pcVar17;
  uint uVar18;
  char *pcVar19;
  int iVar20;
  int iVar21;
  int *piVar22;
  undefined4 uVar23;
  undefined4 uVar24;
  char *local_68;
  uint local_64;
  uint local_60;
  int local_5c;
  uint local_54;
  char *local_50;
  undefined4 local_4c;
  uint local_48;
  int local_44;
  int local_40;
  int local_3c;
  int local_38;
  byte local_34;
  undefined1 local_33;
  
  uVar15 = param_3 & 0x7fff;
  iVar20 = *param_1;
  local_54 = 10;
  if (uVar15 == 0x94c) {
    iVar20 = rrm_MsgHandle();
    return (char *)-(uint)(iVar20 != 0);
  }
  if (0x94c < uVar15) {
    if (uVar15 == 0x968) {
      pcVar5 = (char *)RTMPIoctlVowGroupMinRatio();
      return pcVar5;
    }
    if (uVar15 < 0x969) {
      if (uVar15 == 0x962) {
        pcVar5 = (char *)RTMPIoctlVowBwTputEn();
        return pcVar5;
      }
      if (uVar15 < 0x963) {
        if (uVar15 == 0x956) {
          piVar22 = param_1;
          if (*(int *)(iVar20 + 0x38) == 0x200) {
            piVar22 = param_1 + *(int *)(iVar20 + 0x3c) * 0x160d;
          }
          if ((*(ushort *)(piVar22 + 0xadc98) & 0xb1) == 0) {
            uVar23 = 1;
          }
          else {
            uVar23 = 2;
          }
          iVar6 = HcGetBandByWdev();
          uVar24 = param_2[1];
          uVar10 = param_2[3];
          uVar7 = param_2[2];
          *(undefined4 *)((int)param_1 + iVar6 * 0xaf5d8 + 0x82929a) = *param_2;
          iVar20 = DebugLevel;
          *(undefined4 *)((int)param_1 + iVar6 * 0xaf5d8 + 0x82929e) = uVar24;
          *(undefined4 *)((int)param_1 + iVar6 * 0xaf5d8 + 0x8292a2) = uVar7;
          *(undefined4 *)((int)param_1 + iVar6 * 0xaf5d8 + 0x8292a6) = uVar10;
          if (3 < iVar20) {
            printk("[%d][%s] : (sync) Msg received for current channel info!! \n",0x13fb,
                   "RTMPAPSetInformation");
          }
          uVar23 = HcGetChannelByRf(param_1,uVar23);
          local_4c = CONCAT31(local_4c._1_3_,(char)uVar23);
          pcVar5 = (char *)Channel2Index(param_1,uVar23,iVar6);
          local_38 = param_1[iVar6 + 0xa165e];
          local_40 = param_1[iVar6 * 3 + 0xa1659];
          local_44 = param_1[iVar6 * 3 + 0xa1658];
          local_4c._0_2_ = CONCAT11((char)pcVar5,(undefined1)local_4c);
          local_33 = (undefined1)((uint)param_1[0xa1667] / 1000);
          local_34 = *(byte *)((int)param_1 + (int)pcVar5 * 0x14 + 0x297355);
          local_3c = param_1[iVar6 * 3 + 0xa165a];
          if (2 < DebugLevel) {
            local_60 = local_48;
            local_68 = pcVar5;
            local_64 = (uint)local_34;
            local_5c = local_38;
            printk("[%d][%s] : Current channel : %d Current channel_id : %d Current ch dfs_req : %d NF : %d Ch_bsy_time : %u!! \n"
                   ,0x1407,"RTMPAPSetInformation",(undefined1)local_4c);
          }
LAB_0003ddfc:
          uVar15 = param_2[4];
          pcVar5 = (char *)(uint)*(ushort *)(param_2 + 5);
          pcVar19 = *(char **)(((uint)&local_68 & 0xffffe000) + 8);
          if (!CARRY4(uVar15,(uint)pcVar5) && pcVar5 + uVar15 <= pcVar19) {
            pcVar19 = (char *)0x0;
          }
          if (pcVar19 == (char *)0x0) {
            pcVar5 = (char *)__copy_to_user(uVar15,&local_4c);
            return pcVar5;
          }
          return pcVar5;
        }
        if (uVar15 < 0x957) {
          if (uVar15 == 0x950) {
            BndStrg_MsgHandle(param_1,param_2,*(undefined4 *)(iVar20 + 0x3c));
            return (char *)0x0;
          }
          if (uVar15 == 0x955) {
            if (3 < DebugLevel) {
              printk("[%d][%s] : Msg received !! \n",0x1b95,"RTMPAPSetInformation");
            }
            pcVar5 = (char *)Channel_Info_MsgHandle(param_1,param_2,iVar20);
            if (pcVar5 == (char *)0x0) {
              if (DebugLevel < 0) {
                return (char *)0xffffffff;
              }
              printk("%s Channel_Info_MsgHandle return status received = failure changing it to negative for application \n"
                     ,"RTMPAPSetInformation");
              return (char *)0xffffffff;
            }
            return pcVar5;
          }
        }
        else {
          if (uVar15 == 0x957) {
            piVar22 = param_1;
            if (*(int *)(iVar20 + 0x38) == 0x200) {
              piVar22 = param_1 + *(int *)(iVar20 + 0x3c) * 0x160d;
            }
            if ((*(ushort *)(piVar22 + 0xadc98) & 0xb1) == 0) {
              uVar23 = 1;
            }
            else {
              uVar23 = 2;
            }
            if (3 < DebugLevel) {
              printk("[%d][%s] : (sync) Msg received for current channel info!! \n",0x1418,
                     "RTMPAPSetInformation");
            }
            uVar4 = wlan_config_get_ht_bw(piVar22 + 0xadc92);
            local_4c._0_2_ = CONCAT11(uVar4,(undefined1)local_4c);
            uVar4 = wlan_config_get_vht_bw(piVar22 + 0xadc92);
            local_4c = CONCAT13(*(undefined1 *)((int)param_1 + 0x795075),
                                CONCAT12(uVar4,(undefined2)local_4c));
            uVar4 = GetCountryRegionFromCountryCode((int)param_1 + 0x794c31);
            local_48 = CONCAT31(local_48._1_3_,uVar4);
            uVar23 = HcGetChannelByRf(param_1,uVar23);
            uVar15 = local_4c;
            local_4c = CONCAT31(local_4c._1_3_,(char)uVar23);
            if (-1 < DebugLevel) {
              local_68 = (char *)(uVar15 >> 8 & 0xff);
              local_64 = uVar15 >> 0x10 & 0xff;
              printk("[%d][%s] : Channel: %d Info.cfg_ht_bw : %d Info.cfg_vht_bw : %d !! \n",0x1420,
                     "RTMPAPSetInformation",uVar23);
            }
            goto LAB_0003ddfc;
          }
          if (uVar15 == 0x961) {
            pcVar5 = (char *)RTMPIoctlVowBwAtEn(param_1,param_2,param_3);
            return pcVar5;
          }
        }
      }
      else {
        if (uVar15 == 0x965) {
          pcVar5 = (char *)RTMPIoctlVowGroupMaxRate();
          return pcVar5;
        }
        if (uVar15 < 0x966) {
          if (uVar15 == 0x963) {
            pcVar5 = (char *)RTMPIoctlVowAtfEn();
            return pcVar5;
          }
          if (uVar15 == 0x964) {
            pcVar5 = (char *)RTMPIoctlVowRxEn(param_1,param_2,param_3);
            return pcVar5;
          }
        }
        else {
          if (uVar15 == 0x966) {
            pcVar5 = (char *)RTMPIoctlVowGroupMinRate();
            return pcVar5;
          }
          if (uVar15 == 0x967) {
            pcVar5 = (char *)RTMPIoctlVowGroupMaxRatio(param_1,param_2,param_3);
            return pcVar5;
          }
        }
      }
      goto LAB_0003d784;
    }
    if (uVar15 == 0x992) {
      if (0x20 < *(ushort *)(param_2 + 5)) {
        return (char *)0xffffffea;
      }
      if (*(int *)(iVar20 + 0x38) == 0x400) {
        uVar15 = (uint)*(byte *)(iVar20 + 0x3c);
        cVar2 = *(char *)((int)param_1 + uVar15 * 0x2137b0 + 0x580e8d);
        if (cVar2 == '\x01') {
          *(undefined1 *)((int)param_1 + uVar15 * 0x2137b0 + 0x580e8d) = 0;
          ApCliIfDown();
        }
        iVar20 = (int)param_1 + uVar15 * 0x2137b0 + 0x580e3a;
        *(undefined1 *)(param_1 + uVar15 * 0x84dec + 0x1603a7) = 0;
        __memzero(iVar20,0x20);
        pcVar5 = (char *)(uint)*(ushort *)(param_2 + 5);
        pcVar19 = *(char **)(((uint)&local_68 & 0xffffe000) + 8);
        if (!CARRY4(param_2[4],(uint)pcVar5) && pcVar5 + param_2[4] <= pcVar19) {
          pcVar19 = (char *)0x0;
        }
        if (pcVar19 == (char *)0x0) {
          pcVar5 = (char *)__copy_from_user(iVar20);
          uVar12 = *(ushort *)(param_2 + 5);
        }
        else {
          uVar12 = 0;
          if (pcVar5 != (char *)0x0) {
            __memzero(iVar20,pcVar5);
            uVar12 = *(ushort *)(param_2 + 5);
          }
        }
        iVar6 = DebugLevel;
        *(char *)((int)param_1 + uVar15 * 0x2137b0 + 0x580e5a) = (char)uVar12;
        if (2 < iVar6) {
          printk("I/F(apcli%d) OID_APCLI_SSID::(Len=%d,Ssid=%s)\n",uVar15,uVar12 & 0xff,iVar20);
        }
        *(char *)((int)param_1 + uVar15 * 0x2137b0 + 0x580e8d) = cVar2;
        return pcVar5;
      }
      iVar21 = *(int *)(iVar20 + 0x3c);
      iVar6 = hc_get_chip_bcn_max_num(param_1[0x29e5e8]);
      if (iVar6 <= iVar21) {
        return (char *)0x0;
      }
      iVar6 = *(int *)(iVar20 + 0x3c);
      pcVar13 = (char *)((int)param_1 +
                        (int)(
                             "Set::OID_802_11_SET_PASSPHRASE, Failed (len less than 8 or greater than 64)!!\n"
                             + iVar6 * 0x5834 + 0x34));
      pcVar17 = (char *)((int)param_1 +
                        (int)(
                             "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                             + iVar6 * 0x5834 + 0xe0));
      __memzero(pcVar13,0x20);
      pcVar5 = (char *)(uint)*(ushort *)(param_2 + 5);
      pcVar19 = *(char **)(((uint)&local_68 & 0xffffe000) + 8);
      if (!CARRY4(param_2[4],(uint)pcVar5) && pcVar5 + param_2[4] <= pcVar19) {
        pcVar19 = (char *)0x0;
      }
      if (pcVar19 == (char *)0x0) {
        pcVar5 = (char *)__copy_from_user(pcVar13);
        uVar4 = (undefined1)*(undefined2 *)(param_2 + 5);
      }
      else {
        uVar4 = 0;
        if (pcVar5 != (char *)0x0) {
          __memzero(pcVar13,pcVar5);
          uVar4 = (undefined1)*(undefined2 *)(param_2 + 5);
        }
      }
      *(undefined1 *)((int)param_1 + iVar6 * 0x5834 + 0x2bb2d1) = uVar4;
      if (pcVar17 != (char *)0x0) {
        if (param_1[iVar6 * 0x160d + 0xaec8b] == 0) {
          return (char *)0xffffffea;
        }
        ap_send_broadcast_deauth(param_1,pcVar17);
        if ((param_1[iVar6 * 0x160d + 0xadc9d] == 1) && (param_1[iVar6 * 0x160d + 0xadcef] == 1)) {
          *(ushort *)(param_1 + iVar6 * 0x160d + 0xaecb5) =
               *(ushort *)(param_1 + iVar6 * 0x160d + 0xaecb5) & 0xffef;
        }
        else {
          *(ushort *)(param_1 + iVar6 * 0x160d + 0xaecb5) =
               *(ushort *)(param_1 + iVar6 * 0x160d + 0xaecb5) | 0x10;
        }
        APSecInit(param_1,pcVar17);
        restart_ap(pcVar17);
        if (2 < DebugLevel) {
          printk("I/F(ra%d) Set_SSID::(Len=%d,Ssid=%s)\n",*(undefined4 *)(iVar20 + 0x3c),
                 *(undefined1 *)((int)param_1 + iVar6 * 0x5834 + 0x2bb2d1),pcVar13);
          return pcVar5;
        }
        return pcVar5;
      }
      return (char *)0xffffffea;
    }
    if (0x992 < uVar15) {
      if (uVar15 == 0x1280) {
        ZTE_StartAirMonitor();
        return (char *)0x0;
      }
      if (uVar15 < 0x1281) {
        if (uVar15 == 0x993) {
          iVar6 = *(int *)(iVar20 + 0x40);
          if (iVar6 == 0) {
            if (DebugLevel < 3) {
              return (char *)0x0;
            }
            printk("%s:: pSecConfig == NULL \n","RTMPAPSetInformation");
            return (char *)0x0;
          }
          pcVar5 = (char *)(uint)*(ushort *)(param_2 + 5);
          if (pcVar5 < (char *)0x41) {
            uVar15 = param_2[4];
            pcVar19 = *(char **)(((uint)&local_68 & 0xffffe000) + 8);
            if (!CARRY4(uVar15,(uint)pcVar5) && pcVar5 + uVar15 <= pcVar19) {
              pcVar19 = (char *)0x0;
            }
            if (pcVar19 == (char *)0x0) {
              pcVar5 = (char *)__copy_from_user(iVar6 + 0x14d,uVar15,pcVar5);
              uVar15 = (uint)*(ushort *)(param_2 + 5);
            }
            else if (pcVar5 == (char *)0x0) {
              uVar15 = 0;
            }
            else {
              __memzero(iVar6 + 0x14d,pcVar5);
              uVar15 = (uint)*(ushort *)(param_2 + 5);
            }
            *(undefined1 *)(iVar6 + uVar15 + 0x14d) = 0;
          }
          else {
            pcVar5 = (char *)0x0;
            *(undefined1 *)(iVar6 + 0x14d) = 0;
          }
          if (2 < DebugLevel) {
            printk("%s: PSK = %s\n","RTMPAPSetInformation",iVar6 + 0x14d);
          }
          if (*(char *)((int)param_1 + 0x286285) == '\x01') {
            if ((*(int *)(iVar20 + 0x38) - 0x100U & 0xfffffeff) == 0) {
              iVar20 = (uint)*(byte *)(iVar20 + 0x3c) * 0x160d + 0xae14b;
            }
            else {
              if (*(int *)(iVar20 + 0x38) != 0x400) {
                return pcVar5;
              }
              iVar20 = (uint)*(byte *)(iVar20 + 0x3c) * 0x84dec + 0xdbb8f;
            }
            param_1 = param_1 + iVar20;
            if (param_1 != (int *)0x0) {
              iVar20 = (int)param_1 + 0x299d;
              __memzero(iVar20,0x40);
              param_1[0xa78] = 0;
              param_1[0xa78] = (uint)*(ushort *)(param_2 + 5);
              uVar15 = param_2[4];
              pcVar19 = (char *)(uint)*(ushort *)(param_2 + 5);
              pcVar17 = *(char **)(((uint)&local_68 & 0xffffe000) + 8);
              pcVar13 = pcVar19 + uVar15;
              pcVar5 = pcVar13;
              if (!CARRY4(uVar15,(uint)pcVar19)) {
                pcVar5 = pcVar13 + -(int)(pcVar17 + 1);
              }
              if (!CARRY4(uVar15,(uint)pcVar19) && pcVar13 <= pcVar17) {
                pcVar17 = (char *)0x0;
              }
              if (pcVar17 == (char *)0x0) {
                pcVar19 = (char *)__copy_from_user(iVar20,uVar15,pcVar19);
              }
              else if (pcVar19 != (char *)0x0) {
                __memzero(iVar20,pcVar19,pcVar5);
              }
              if (2 < DebugLevel) {
                printk("%s: PSK = %s\n","RTMPAPSetInformation",iVar20);
                return pcVar19;
              }
              return pcVar19;
            }
            return pcVar5;
          }
          return pcVar5;
        }
        if (uVar15 == 0x999) {
          iVar6 = *(int *)(iVar20 + 0x3c);
          os_alloc_mem(0,&local_4c,0x690);
          if (local_4c == 0) {
            if (DebugLevel < 1) {
              return (char *)0xfffffff2;
            }
            printk("%s()::alloc memory fail\n","RTMPAPSetInformation");
            return (char *)0xfffffff2;
          }
          piVar22 = param_1;
          if (*(int *)(iVar20 + 0x38) == 0x200) {
            piVar22 = param_1 + iVar6 * 0x160d;
          }
          uVar23 = HcGetBandByWdev(piVar22 + 0xadc92);
          iVar20 = hc_get_channel_ctrl(param_1[0x29e5e8],uVar23);
          __memzero(local_4c,0x690);
          if (3 < DebugLevel) {
            printk("[%d][%s] : (sync) Msg received !! \n",0x13d8,"RTMPAPSetInformation");
          }
          *(undefined1 *)((int)param_1 + 0x2977ee) = *(undefined1 *)(iVar20 + 0x49c);
          if (*(char *)(iVar20 + 0x49c) != '\0') {
            iVar21 = 0;
            iVar6 = iVar21;
            do {
              *(undefined1 *)(local_4c + iVar21 * 0x1c) = *(undefined1 *)(iVar20 + iVar6);
              iVar3 = iVar6 + 4;
              pcVar5 = (char *)(iVar20 + iVar6);
              iVar6 = iVar6 + 0x14;
              *(char *)((int)param_1 + (int)("sync_fsm_join_req_action" + iVar3)) = *pcVar5;
              *(char *)(local_4c + iVar21 * 0x1c + 1) = (char)iVar21;
              iVar3 = DebugLevel;
              bVar1 = pcVar5[5];
              *(byte *)(local_4c + iVar21 * 0x1c + 0x18) = bVar1;
              if (3 < iVar3) {
                local_68 = (char *)(uint)*(byte *)(local_4c + iVar21 * 0x1c + 1);
                local_64 = (uint)bVar1;
                printk("[%d][%s] : channel : %d channel_id : %d dfs_req : %d\t!! \n",0x13e2,
                       "RTMPAPSetInformation",*(undefined1 *)(local_4c + iVar21 * 0x1c));
              }
              iVar21 = iVar21 + 1;
            } while (iVar21 < (int)(uint)*(byte *)(iVar20 + 0x49c));
          }
          uVar15 = param_2[4];
          pcVar5 = (char *)(uint)*(ushort *)(param_2 + 5);
          pcVar19 = *(char **)(((uint)&local_68 & 0xffffe000) + 8);
          if (!CARRY4(uVar15,(uint)pcVar5) && pcVar5 + uVar15 <= pcVar19) {
            pcVar19 = (char *)0x0;
          }
          if (pcVar19 == (char *)0x0) {
            pcVar5 = (char *)__copy_to_user(uVar15,local_4c,pcVar5);
          }
          if (-1 < DebugLevel) {
            local_68 = pcVar5;
            printk("[%d][%s] OID_802_11_CHANNELINFO: channel count: %d  IOCTL_Call_Status:%d!! \n",
                   0x13e7,"RTMPAPSetInformation",*(undefined1 *)(iVar20 + 0x49c));
          }
          goto LAB_0003d194;
        }
LAB_0003d784:
        if (DebugLevel < 3) {
          return (char *)0xffffffa1;
        }
        printk("Set::unknown IOCTL\'s subcmd = 0x%08x\n",param_3);
        return (char *)0xffffffa1;
      }
      if (uVar15 == 0x7000) {
        uVar16 = *(uint *)(((uint)&local_68 & 0xffffe000) + 8);
        uVar15 = (uint)*(ushort *)(param_2 + 5);
        if (!CARRY4(param_2[4],uVar15) && param_2[4] + uVar15 <= uVar16) {
          uVar16 = 0;
        }
        if (uVar16 != 0) {
          if (uVar15 == 0) {
            return (char *)0x0;
          }
          __memzero(param_1 + *(int *)(iVar20 + 0x3c) * 0x160d + 0xaf1af,uVar15);
          return (char *)0xfffffff2;
        }
        iVar20 = __copy_from_user(param_1 + *(int *)(iVar20 + 0x3c) * 0x160d + 0xaf1af);
        if (iVar20 == 0) {
          return (char *)0x0;
        }
        return (char *)0xfffffff2;
      }
      if (uVar15 != 0x7001) goto LAB_0003d784;
      iVar20 = get_wdev_by_ioctl_idx_and_iftype
                         (param_1,*(undefined4 *)(iVar20 + 0x3c),*(undefined4 *)(iVar20 + 0x38));
      if (iVar20 == 0) {
        return (char *)0x0;
      }
      iVar20 = HcGetBandByWdev();
      uVar15 = (uint)*(ushort *)(param_2 + 5);
      uVar16 = *(uint *)(((uint)&local_68 & 0xffffe000) + 8);
      if (!CARRY4(param_2[4],uVar15) && param_2[4] + uVar15 <= uVar16) {
        uVar16 = 0;
      }
      if (uVar16 == 0) {
        iVar6 = __copy_from_user(param_1 + (int)("MtCmdGetCfgOnOff" + iVar20 * 0x32 + 4));
        if (iVar6 != 0) {
          pcVar5 = (char *)0xfffffff2;
          goto LAB_0003d5cc;
        }
      }
      else if (uVar15 != 0) {
        __memzero(param_1 + (int)("MtCmdGetCfgOnOff" + iVar20 * 0x32 + 4),uVar15);
        pcVar5 = (char *)0xfffffff2;
        goto LAB_0003d5cc;
      }
      pcVar5 = (char *)0x0;
LAB_0003d5cc:
      ZTE_APUnAssocStaInfoReportAll(param_1,iVar20);
      return pcVar5;
    }
    if (uVar15 != 0x972) {
      if (0x972 < uVar15) {
        if (uVar15 == 0x985) {
          pcVar5 = (char *)ZeroWaitDfsCmdHandler();
          return pcVar5;
        }
        if (uVar15 == 0x990) goto LAB_0003e170;
        goto LAB_0003d784;
      }
      if (uVar15 == 0x970) {
        RTMPIoctlWifiSpectrumSetParameter();
        return (char *)0x0;
      }
      if (uVar15 != 0x971) goto LAB_0003d784;
      iVar20 = hc_get_chip_ops(param_1[0x29e5e8]);
      if (*(code **)(iVar20 + 0x1a4) == (code *)0x0) {
        if (-1 < DebugLevel) {
          printk("%s : The function is not hooked !!\n","RTMPAPSetInformation");
        }
      }
      else {
        iVar20 = (**(code **)(iVar20 + 0x1a4))(param_1);
        if (iVar20 != 0) {
          pcVar5 = (char *)0xffffffff;
          goto LAB_0003d4c4;
        }
      }
      pcVar5 = (char *)0x0;
LAB_0003d4c4:
      if (2 < DebugLevel) {
        printk("OID_802_11_WIFISPECTRUM_GET_CAPTURE_STATUS Status : %d\n");
        return pcVar5;
      }
      return pcVar5;
    }
    iVar20 = hc_get_chip_ops(param_1[0x29e5e8]);
    if (*(code **)(iVar20 + 0x1a8) == (code *)0x0) {
      if (-1 < DebugLevel) {
        printk("%s : The function is not hooked !!\n","RTMPAPSetInformation");
      }
    }
    else {
      iVar20 = (**(code **)(iVar20 + 0x1a8))(param_1);
      if (iVar20 != 0) {
        pcVar5 = (char *)0xffffffff;
        goto LAB_0003d940;
      }
    }
    pcVar5 = (char *)0x0;
LAB_0003d940:
    if (2 < DebugLevel) {
      printk("OID_802_11_WIFISPECTRUM_DUMP_DATA Status : %d\n");
    }
    return pcVar5;
  }
  if (uVar15 == 0x544) {
    Dot1xIoctlStaticWepCopy();
    return (char *)0x0;
  }
  if (uVar15 < 0x545) {
    if (uVar15 == 0x510) {
      if (*(short *)(param_2 + 5) != 4) {
        return (char *)0xffffffea;
      }
      uVar16 = param_2[4];
      uVar14 = *(uint *)(((uint)&local_68 & 0xffffe000) + 8);
      uVar9 = uVar16 + 4;
      uVar15 = uVar9;
      if (uVar16 < 0xfffffffc) {
        uVar15 = uVar9 - (uVar14 + 1);
      }
      if (uVar16 < 0xfffffffc && uVar9 <= uVar14) {
        uVar14 = 0;
      }
      if (uVar14 == 0) {
        pcVar5 = (char *)__copy_from_user(&local_4c,uVar16,4);
      }
      else {
        __memzero(&local_4c,4,uVar15);
        pcVar5 = (char *)0x4;
      }
      uVar15 = SecEncryModeOldToNew(local_4c & 0xffff);
      if (uVar15 != 0) {
        uVar16 = *(uint *)(iVar20 + 0x3c) & 0xff;
        if (param_1[uVar16 * 0x160d + 0xadcef] != uVar15) {
          *(undefined1 *)(param_1 + 0x28e7e8) = 1;
        }
        param_1[uVar16 * 0x160d + 0xadcef] = uVar15;
        if ((uVar15 & 0x30) == 0x30) {
          param_1[uVar16 * 0x160d + 0xadd27] = param_1[uVar16 * 0x160d + 0xadd27] | 0x10;
        }
        else {
          param_1[uVar16 * 0x160d + 0xadd27] = uVar15;
        }
        APStop(param_1,param_1 + uVar16 * 0x160d + 0xadc92,2);
        APStartUp(param_1,param_1 + uVar16 * 0x160d + 0xadc92,2);
        if (2 < DebugLevel) {
          printk("Set::OID_802_11_WEP_STATUS (=0x%x)\n",uVar15);
          return pcVar5;
        }
        return pcVar5;
      }
      return (char *)0xffffffea;
    }
    if (uVar15 < 0x511) {
      if (uVar15 == 0x405) {
        if (*(short *)(param_2 + 5) == 4) {
          uVar15 = *(uint *)(((uint)&local_68 & 0xffffe000) + 8);
          if ((uint)param_2[4] < 0xfffffffc && param_2[4] + 4 <= uVar15) {
            uVar15 = 0;
          }
          if (uVar15 != 0) {
            __memzero(&local_4c,4);
            return (char *)0xfffffff2;
          }
          iVar6 = __copy_from_user(&local_4c);
          if (iVar6 == 0) {
            *(undefined4 *)(iVar20 + 0x28) =
                 *(undefined4 *)(*(int *)(((uint)&local_68 & 0xffffe000) + 0xc) + 0x234);
            iVar6 = DebugLevel;
            *(uint *)(iVar20 + 0x2c) = local_4c;
            if (iVar6 < 3) {
              return (char *)0x0;
            }
            printk("RT_SET_APD_PID::(ApdPid=%u)\n");
            return (char *)0x0;
          }
        }
        return (char *)0xfffffff2;
      }
      if (uVar15 < 0x406) {
        if (uVar15 == 0x404) {
          if (*(short *)(param_2 + 5) != 4) {
            return (char *)0xfffffff2;
          }
          uVar16 = param_2[4];
          uVar14 = *(uint *)(((uint)&local_68 & 0xffffe000) + 8);
          uVar9 = uVar16 + 4;
          uVar15 = uVar9;
          if (uVar16 < 0xfffffffc) {
            uVar15 = uVar9 - (uVar14 + 1);
          }
          if (uVar16 < 0xfffffffc && uVar9 <= uVar14) {
            uVar14 = 0;
          }
          if (uVar14 != 0) {
            __memzero(&local_4c,4,uVar15);
            return (char *)0xfffffff2;
          }
          iVar6 = __copy_from_user(&local_4c,uVar16,4);
          if (iVar6 != 0) {
            return (char *)0xfffffff2;
          }
          *(undefined4 *)(iVar20 + 0x30) =
               *(undefined4 *)(*(int *)(((uint)&local_68 & 0xffffe000) + 0xc) + 0x234);
          iVar6 = DebugLevel;
          *(uint *)(iVar20 + 0x34) = local_4c;
          if (2 < iVar6) {
            printk("RT_SET_APD_PID::(IappPid=%u)\n");
            return (char *)0x0;
          }
          return (char *)0x0;
        }
      }
      else {
        if (uVar15 == 0x406) {
          if (*(short *)(param_2 + 5) != 6) {
            return (char *)0xfffffff2;
          }
          uVar16 = param_2[4];
          uVar14 = *(uint *)(((uint)&local_68 & 0xffffe000) + 8);
          uVar9 = uVar16 + 6;
          uVar15 = uVar9;
          if (uVar16 < 0xfffffffa) {
            uVar15 = uVar9 - (uVar14 + 1);
          }
          if (uVar16 < 0xfffffffa && uVar9 <= uVar14) {
            uVar14 = 0;
          }
          if (uVar14 != 0) {
            __memzero(&local_4c,6,uVar15);
            return (char *)0xfffffff2;
          }
          iVar6 = __copy_from_user(&local_4c,uVar16,6);
          if (iVar6 != 0) {
            return (char *)0xfffffff2;
          }
          if (2 < DebugLevel) {
            local_68 = (char *)(local_4c >> 0x18);
            local_64 = local_48 & 0xff;
            local_60 = local_48 >> 8 & 0xff;
            printk("RT_SET_DEL_MAC_ENTRY::(%02x:%02x:%02x:%02x:%02x:%02x)\n",local_4c & 0xff,
                   local_4c._1_1_,local_4c._2_1_);
          }
          if ((*(int *)(iVar20 + 0x38) - 0x100U & 0xfffffeff) == 0) {
            iVar20 = MacTableLookup2(param_1,&local_4c,
                                     param_1 + *(int *)(iVar20 + 0x3c) * 0x160d + 0xadc92);
          }
          else {
            iVar20 = MacTableLookup(param_1,&local_4c);
          }
          if (iVar20 == 0) {
            return (char *)0x0;
          }
          if (*(char *)((int)param_1 + 0x36790d) != '\0') {
            uVar23 = RTMPLookupRepeaterCliEntry(param_1,1,iVar20 + 0xec,1);
            if (0 < DebugLevel) {
              local_68 = (char *)(local_4c >> 0x18);
              local_64 = local_48 & 0xff;
              local_60 = local_48 >> 8 & 0xff;
              printk("Delete (%02x:%02x:%02x:%02x:%02x:%02x) mac repeater entry\n",local_4c & 0xff,
                     local_4c._1_1_,local_4c._2_1_);
            }
            RepeaterDisconnectRootAP(param_1,uVar23,8);
          }
          local_68 = "RTMPAPSetInformation";
          local_64 = 0x1834;
          __MlmeDeAuthAction(param_1,iVar20,8,0);
          return (char *)0x0;
        }
        if (uVar15 == 0x509) {
          if (*(short *)(param_2 + 5) != 0x24) {
            return (char *)0xffffffea;
          }
          uVar16 = param_2[4];
          local_50 = (char *)0x0;
          uVar14 = *(uint *)(((uint)&local_68 & 0xffffe000) + 8);
          uVar9 = uVar16 + 0x24;
          uVar15 = uVar9;
          if (uVar16 < 0xffffffdc) {
            uVar15 = uVar9 - (uVar14 + 1);
          }
          if (uVar16 < 0xffffffdc && uVar9 <= uVar14) {
            uVar14 = 0;
          }
          if (uVar14 == 0) {
            pcVar5 = (char *)__copy_from_user(&local_4c,uVar16,0x24);
          }
          else {
            __memzero(&local_4c,0x24,uVar15);
            pcVar5 = (char *)0x24;
          }
          if (local_4c - 1 < 0x20) {
            os_alloc_mem(0,&local_50,0x21);
            if (local_50 == (char *)0x0) {
              return (char *)0xfffffff4;
            }
            __memzero(local_50,0x21);
            memmove(local_50,&local_48,local_4c);
            __memzero(param_1 + *(int *)(iVar20 + 0x3c) * 0x160d + 0xaecac,0x20);
            pcVar19 = local_50;
            strncpy((char *)(param_1 + *(int *)(iVar20 + 0x3c) * 0x160d + 0xaecac),local_50,0x20);
            *(undefined1 *)(param_1 + *(int *)(iVar20 + 0x3c) * 0x160d + 0xaecb4) = 0;
            sVar8 = strlen(pcVar19);
            *(char *)((int)param_1 + *(int *)(iVar20 + 0x3c) * 0x5834 + 0x2bb2d1) = (char)sVar8;
            os_free_mem(pcVar19);
            return pcVar5;
          }
          return (char *)0xffffffea;
        }
      }
    }
    else {
      if (uVar15 == 0x541) {
        RTMPIoctlAddPMKIDCache();
        return (char *)0x0;
      }
      if (uVar15 < 0x542) {
        if (uVar15 == 0x511) {
          uVar15 = *(uint *)(iVar20 + 0x3c);
          if (*(short *)(param_2 + 5) != 4) {
            return (char *)0xffffffea;
          }
          uVar9 = param_2[4];
          uVar18 = *(uint *)(((uint)&local_68 & 0xffffe000) + 8);
          uVar14 = uVar9 + 4;
          uVar16 = uVar14;
          if (uVar9 < 0xfffffffc) {
            uVar16 = uVar14 - (uVar18 + 1);
          }
          if (uVar9 < 0xfffffffc && uVar14 <= uVar18) {
            uVar18 = 0;
          }
          if (uVar18 == 0) {
            pcVar5 = (char *)__copy_from_user(&local_54,uVar9,4);
          }
          else {
            pcVar5 = (char *)0x4;
            __memzero(&local_54,4,uVar16);
          }
          if (local_54 < 0xb) {
            uVar15 = uVar15 & 0xff;
            iVar20 = SecAuthModeOldToNew(local_54 & 0xffff);
            if (param_1[uVar15 * 0x160d + 0xadc9d] != iVar20) {
              *(undefined1 *)(param_1 + 0x28e7e8) = 1;
            }
            iVar6 = DebugLevel;
            param_1[uVar15 * 0x160d + 0xadc9d] = iVar20;
            *(undefined1 *)(param_1 + uVar15 * 0x160d + 0xadeb4) = 2;
            if (2 < iVar6) {
              printk("Set::OID_802_11_AUTHENTICATION_MODE (=0x%x)\n",
                     param_1[uVar15 * 0x160d + 0xadc9d]);
            }
            piVar22 = param_1 + uVar15 * 0x160d + 0xadc92;
            if (piVar22 != (int *)0x0) {
              APStop(param_1,piVar22,2);
              APStartUp(param_1,piVar22,2);
              return pcVar5;
            }
            return pcVar5;
          }
          return (char *)0xffffffea;
        }
        if (uVar15 == 0x526) {
          if (2 < DebugLevel) {
            printk("Set::OID_802_11_DEAUTHENTICATION\n");
          }
          if (*(short *)(param_2 + 5) != 8) {
            return (char *)0xffffffea;
          }
          os_alloc_mem(param_1,&local_4c,0x930);
          uVar15 = local_4c;
          if (local_4c == 0) {
            if (DebugLevel < 3) {
              return (char *)0xfffffff4;
            }
            printk("Set::OID_802_11_DEAUTHENTICATION, Failed!!\n");
            return (char *)0xfffffff4;
          }
          uVar16 = param_2[4];
          pcVar5 = (char *)(uint)*(ushort *)(param_2 + 5);
          pcVar17 = *(char **)(((uint)&local_68 & 0xffffe000) + 8);
          pcVar13 = pcVar5 + uVar16;
          pcVar19 = pcVar13;
          if (!CARRY4(uVar16,(uint)pcVar5)) {
            pcVar19 = pcVar13 + -(int)(pcVar17 + 1);
          }
          if (!CARRY4(uVar16,(uint)pcVar5) && pcVar13 <= pcVar17) {
            pcVar17 = (char *)0x0;
          }
          if (pcVar17 == (char *)0x0) {
            pcVar5 = (char *)__copy_from_user(local_4c,uVar16,pcVar5);
          }
          else if (pcVar5 != (char *)0x0) {
            __memzero(local_4c,pcVar5,pcVar19);
          }
          iVar20 = MacTableLookup(param_1,uVar15);
          if (iVar20 != 0) {
            *(undefined2 *)(local_4c + 0x920) = *(undefined2 *)(iVar20 + 0xe0);
            local_68 = "RTMPAPSetInformation";
            local_64 = 0x173e;
            __cntl_disconnect_request
                      (*(undefined4 *)(iVar20 + 8),0,iVar20 + 0xec,*(undefined2 *)(uVar15 + 6));
            if (2 < DebugLevel) {
              printk("Set::OID_802_11_DEAUTHENTICATION (Reason=%d)\n",*(undefined2 *)(uVar15 + 6));
            }
          }
LAB_0003d194:
          os_free_mem(local_4c);
          return pcVar5;
        }
      }
      else {
        if (uVar15 == 0x542) {
          Dot1xIoctlRadiusData();
          return (char *)0x0;
        }
        if (uVar15 == 0x543) {
          Dot1xIoctlAddWPAKey();
          return (char *)0x0;
        }
      }
    }
    goto LAB_0003d784;
  }
  if (uVar15 == 0x754) {
    uVar15 = *(uint *)(iVar20 + 0x3c);
    if (2 < DebugLevel) {
      printk("WSC::RT_OID_WSC_SET_SELECTED_REGISTRAR, wrq->u.data.length=%d!\n",
             *(undefined2 *)(param_2 + 5));
    }
    os_alloc_mem(param_1,&local_4c,*(undefined2 *)(param_2 + 5));
    if (local_4c == 0) {
      return (char *)0xffffffea;
    }
    uVar16 = (uint)*(ushort *)(param_2 + 5);
    uVar9 = *(uint *)(((uint)&local_68 & 0xffffe000) + 8);
    if (!CARRY4(param_2[4],uVar16) && param_2[4] + uVar16 <= uVar9) {
      uVar9 = 0;
    }
    if (uVar9 == 0) {
      iVar20 = __copy_from_user();
      if (iVar20 != 0) goto LAB_0003d770;
      uVar11 = *(undefined2 *)(param_2 + 5);
    }
    else {
      uVar11 = 0;
      if (uVar16 != 0) {
        __memzero(local_4c,uVar16);
        goto LAB_0003d770;
      }
    }
    uVar15 = uVar15 & 0xff;
    if ((param_1[uVar15 * 0x160d + 0xae14b] & 2U) != 0) {
      WscSelectedRegistrar(param_1,local_4c,uVar11,uVar15);
      if (*(char *)((int)param_1 + uVar15 * 0x5834 + 0x2ba187) == '\x01') {
        RTMPCancelTimer(param_1 + uVar15 * 0x160d + 0xae862,&local_50);
      }
      RTMPSetTimer(param_1 + uVar15 * 0x160d + 0xae862,120000);
      *(undefined1 *)((int)param_1 + uVar15 * 0x5834 + 0x2ba187) = 1;
    }
LAB_0003d770:
    os_free_mem(local_4c);
    return (char *)0x0;
  }
  if (uVar15 < 0x755) {
    if (uVar15 < 0x681) {
      if (0x67d < uVar15) {
        pcVar5 = (char *)RTMPIoctlVendorIeRemove();
        return pcVar5;
      }
      if (uVar15 == 0x545) {
        RTMPIoctlSetIdleTimeout();
        return (char *)0x0;
      }
    }
    else {
      if (uVar15 == 0x681) {
        if (DebugLevel < 3) {
          return (char *)0x0;
        }
        printk("OID_802_11_VENDOR_IE_SHOW not finish yet\n");
        return (char *)0x0;
      }
      if (uVar15 == 0x753) {
LAB_0003e170:
        if (*(short *)(param_2 + 5) != 0x24) {
          if (*(short *)(param_2 + 5) != 0x10) {
            return (char *)0xffffffea;
          }
          bVar1 = *(byte *)(iVar20 + 0x3c);
          uVar15 = param_2[4];
          uVar16 = *(uint *)(((uint)&local_68 & 0xffffe000) + 8);
          if (uVar15 < 0xfffffff0 && uVar15 + 0x10 <= uVar16) {
            uVar16 = 0;
          }
          if (uVar16 == 0) {
            pcVar5 = (char *)__copy_from_user(param_1 + (uint)bVar1 * 0x160d + 0xaebd4,uVar15,0x10);
          }
          else {
            __memzero(param_1 + (uint)bVar1 * 0x160d + 0xaebd4,0x10);
            pcVar5 = (char *)0x10;
          }
          iVar20 = (uint)bVar1 * 0x5834;
          pcVar19 = (char *)((int)param_1 +
                            (int)("IF(ra0) Set_WscPinCode_Proc::(PinCode=%d)\n" + iVar20 + 4));
          do {
            if (2 < DebugLevel) {
              printk(&_LC795,*pcVar19);
            }
            pcVar19 = pcVar19 + 1;
          } while (pcVar19 !=
                   (char *)((int)param_1 +
                           (int)("IF(ra0) Set_WscPinCode_Proc::(PinCode=%d)\n" + iVar20 + 0x14)));
          return pcVar5;
        }
        piVar22 = param_1 + (uint)*(byte *)(iVar20 + 0x3c) * 0x160d + 0xaebd8;
        *(undefined1 *)(param_1 + (uint)*(byte *)(iVar20 + 0x3c) * 0x160d + 0xaebd8) = 0;
        pcVar17 = *(char **)(((uint)&local_68 & 0xffffe000) + 8);
        pcVar19 = (char *)(uint)*(ushort *)(param_2 + 5);
        uVar15 = param_2[4];
        pcVar13 = pcVar19 + uVar15;
        pcVar5 = pcVar13;
        if (!CARRY4(uVar15,(uint)pcVar19)) {
          pcVar5 = pcVar13 + -(int)(pcVar17 + 1);
        }
        if (!CARRY4(uVar15,(uint)pcVar19) && pcVar13 <= pcVar17) {
          pcVar17 = (char *)0x0;
        }
        if (pcVar17 == (char *)0x0) {
          pcVar19 = (char *)__copy_from_user(piVar22,uVar15,pcVar19);
        }
        else if (pcVar19 != (char *)0x0) {
          __memzero(piVar22,pcVar19,pcVar5);
        }
        if (2 < DebugLevel) {
          printk("UUID ASCII string: %s\n",piVar22);
          return pcVar19;
        }
        return pcVar19;
      }
    }
    goto LAB_0003d784;
  }
  if (uVar15 == 0x75b) {
    if (*(ushort *)(param_2 + 5) == 0) {
      return (char *)0xffffffea;
    }
    local_4c = 0;
    uVar15 = *(uint *)(iVar20 + 0x3c);
    os_alloc_mem(param_1,&local_4c,*(ushort *)(param_2 + 5) + 1);
    if (local_4c == 0) {
      return (char *)0xfffffff4;
    }
    RTMPZeroMemory(local_4c,*(ushort *)(param_2 + 5) + 1);
    uVar16 = (uint)*(ushort *)(param_2 + 5);
    uVar9 = *(uint *)(((uint)&local_68 & 0xffffe000) + 8);
    if (!CARRY4(param_2[4],uVar16) && param_2[4] + uVar16 <= uVar9) {
      uVar9 = 0;
    }
    if (uVar9 == 0) {
      iVar20 = __copy_from_user(local_4c);
      if (iVar20 != 0) {
LAB_0003e930:
        pcVar5 = (char *)0xfffffff2;
        goto LAB_0003d420;
      }
    }
    else if (uVar16 != 0) {
LAB_0003e860:
      __memzero(local_4c,uVar16);
      pcVar5 = (char *)0xfffffff2;
      goto LAB_0003d420;
    }
    uVar15 = uVar15 & 0xff;
    if (DebugLevel < 3) {
      if ((char)param_1[uVar15 * 0x160d + 0xae14d] != '\x02') goto LAB_0003d41c;
    }
    else {
      printk("RT_OID_WSC_WRITE_UFD_FILE (WscUfdFileName=%s)\n",local_4c);
      if ((char)param_1[uVar15 * 0x160d + 0xae14d] != '\x02') {
        if (2 < DebugLevel) {
          pcVar5 = (char *)0xffffffea;
          printk("RT_OID_WSC_WRITE_UFD_FILE: AP is un-configured.\n");
          goto LAB_0003d420;
        }
        goto LAB_0003ec4c;
      }
    }
    pcVar5 = (char *)0x0;
    WscWriteProfileToUfdFile(param_1,uVar15,local_4c);
  }
  else {
    if (0x75b < uVar15) {
      if (uVar15 == 0x764) {
        pcVar5 = (char *)RTMPIoctlWscSetConWpsStop();
        return pcVar5;
      }
      if (uVar15 == 0x94a) {
        pcVar5 = (char *)RTMPIoctlWnmCommand();
        return pcVar5;
      }
      goto LAB_0003d784;
    }
    if (uVar15 == 0x755) {
      pcVar5 = (char *)RTMPIoctlWscEapMsg();
      return pcVar5;
    }
    if (uVar15 != 0x75a) goto LAB_0003d784;
    if (*(ushort *)(param_2 + 5) == 0) {
      return (char *)0xffffffea;
    }
    local_4c = 0;
    uVar15 = *(uint *)(iVar20 + 0x3c);
    os_alloc_mem(param_1,&local_4c,*(ushort *)(param_2 + 5) + 1);
    if (local_4c == 0) {
      return (char *)0xfffffff4;
    }
    RTMPZeroMemory(local_4c,*(ushort *)(param_2 + 5) + 1);
    uVar16 = (uint)*(ushort *)(param_2 + 5);
    uVar9 = *(uint *)(((uint)&local_68 & 0xffffe000) + 8);
    if (!CARRY4(param_2[4],uVar16) && param_2[4] + uVar16 <= uVar9) {
      uVar9 = 0;
    }
    if (uVar9 == 0) {
      iVar20 = __copy_from_user(local_4c);
      if (iVar20 != 0) goto LAB_0003e930;
    }
    else if (uVar16 != 0) goto LAB_0003e860;
    uVar15 = uVar15 & 0xff;
    if (DebugLevel < 3) {
      if ((char)param_1[uVar15 * 0x160d + 0xae14d] != '\x01') {
LAB_0003d41c:
        pcVar5 = (char *)0xffffffea;
        goto LAB_0003d420;
      }
    }
    else {
      printk("RT_OID_WSC_READ_UFD_FILE (WscUfdFileName=%s)\n",local_4c);
      if ((char)param_1[uVar15 * 0x160d + 0xae14d] != '\x01') {
        if (2 < DebugLevel) {
          pcVar5 = (char *)0xffffffea;
          printk("RT_OID_WSC_READ_UFD_FILE: AP is configured.\n");
          goto LAB_0003d420;
        }
LAB_0003ec4c:
        pcVar5 = (char *)0xffffffea;
        goto LAB_0003d420;
      }
    }
    iVar20 = WscReadProfileFromUfdFile(param_1,uVar15,local_4c);
    if (iVar20 == 0) {
      pcVar5 = (char *)0x0;
    }
    else {
      pcVar5 = (char *)0x0;
      *(undefined1 *)(param_1 + uVar15 * 0x160d + 0xae14d) = 2;
      APStop(param_1,(char *)((int)param_1 +
                             (int)(
                                  "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                  + uVar15 * 0x5834 + 0xe0)),2);
      APStartUp(param_1,(char *)((int)param_1 +
                                (int)(
                                     "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                     + uVar15 * 0x5834 + 0xe0)),2);
    }
  }
LAB_0003d420:
  os_free_mem(local_4c);
  return pcVar5;
}

