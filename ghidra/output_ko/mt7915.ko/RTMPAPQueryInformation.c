// module: mt7915.ko
// function: RTMPAPQueryInformation @ 0x382f0
// size: 7960 bytes
//

/* WARNING: Type propagation algorithm not settling */

uint RTMPAPQueryInformation(int *param_1,int param_2,int param_3)

{
  int iVar1;
  ushort uVar2;
  char *pcVar3;
  undefined1 uVar4;
  undefined2 uVar5;
  undefined4 uVar6;
  uint *puVar7;
  int iVar8;
  uint uVar9;
  byte bVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  int *piVar14;
  int iVar15;
  uint uVar16;
  bool bVar17;
  undefined8 uVar18;
  uint local_1e0;
  uint local_1dc;
  uint local_1d8;
  int *local_1cc;
  int local_1c8;
  uint local_1c4;
  undefined4 local_1c0;
  undefined4 local_1bc;
  char *apcStack_1b8 [7];
  undefined1 auStack_199 [373];
  
  iVar15 = *param_1;
  local_1c8 = 0;
  uVar16 = (uint)*(byte *)(iVar15 + 0x3c);
  local_1c4 = 0;
  local_1c0 = 10;
  if ((*(int *)(iVar15 + 0x38) - 0x100U & 0xfffffeff) == 0) {
    if (*(byte *)((int)param_1 + 0x2b7242) <= uVar16) {
      return 0xfffffff2;
    }
    piVar14 = param_1 + uVar16 * 0x160d + 0xadc92;
    get_scan_tab_by_wdev(param_1,piVar14);
  }
  else {
    piVar14 = (int *)0x0;
  }
  if (param_3 == 0x74a) {
    if (2 < DebugLevel) {
      printk("Query::RT_OID_APCLI_WSC_PIN_CODE\n");
    }
    uVar11 = *(uint *)(param_2 + 0x10);
    uVar12 = *(uint *)(((uint)&local_1e0 & 0xffffe000) + 8);
    *(undefined2 *)(param_2 + 0x14) = 4;
    if (uVar11 < 0xfffffffc && uVar11 + 4 <= uVar12) {
      uVar12 = 0;
    }
    local_1c8 = param_1[uVar16 * 0x84dec + 0xdbb96];
joined_r0x00038ecc:
    if (uVar12 != 0) {
      return 0xfffffff2;
    }
    iVar15 = __copy_to_user(uVar11,&local_1c8);
    goto joined_r0x00038b90;
  }
  if (param_3 < 0x74b) {
    if (param_3 != 0x608) {
      if (param_3 < 0x609) {
        if (param_3 == 0x511) {
          if (2 < DebugLevel) {
            printk("Query::OID_802_11_AUTHENTICATION_MODE\n");
          }
          *(undefined2 *)(param_2 + 0x14) = 4;
          local_1c0 = SecAuthModeNewToOld(param_1[*(int *)(iVar15 + 0x3c) * 0x160d + 0xadc9d]);
          uVar16 = *(uint *)(param_2 + 0x10);
          uVar11 = (uint)*(ushort *)(param_2 + 0x14);
          uVar12 = *(uint *)(((uint)&local_1e0 & 0xffffe000) + 8);
          if (!CARRY4(uVar16,uVar11) && uVar16 + uVar11 <= uVar12) {
            uVar12 = 0;
          }
          if (uVar12 == 0) {
            uVar16 = __copy_to_user(uVar16,&local_1c0);
            return uVar16;
          }
          return uVar11;
        }
        if (param_3 < 0x512) {
          if (param_3 == 0x402) {
            if (DebugLevel < 3) {
              return 0xfffffff2;
            }
            printk("Query::RT_QUERY_SIGNAL_CONTEXT\n");
            return 0xfffffff2;
          }
          if (param_3 < 0x403) {
            if (param_3 == 0x103) {
              if (2 < DebugLevel) {
                printk("Query::OID_802_11_NETWORK_TYPES_SUPPORTED\n");
              }
              iVar15 = *(int *)(param_2 + 0x10);
              *(undefined2 *)(param_2 + 0x14) = 1;
              uVar16 = *(uint *)(((uint)&local_1e0 & 0xffffe000) + 8);
              if (iVar15 != -1 && iVar15 + 1U <= uVar16) {
                uVar16 = 0;
              }
              if (uVar16 != 0) {
                return 0xfffffff2;
              }
              iVar15 = __copy_to_user(iVar15,"om_file" + (int)param_1);
              goto joined_r0x00038b90;
            }
          }
          else {
            if (param_3 == 0x509) {
              uVar16 = *(uint *)(iVar15 + 0x3c);
              __memzero(&local_1bc,0x24);
              if (*(int *)(iVar15 + 0x38) == 0x400) {
                uVar16 = uVar16 & 0xff;
                if (*(char *)((int)param_1 + uVar16 * 0x2137b0 + 0x580e8d) == '\0') {
                  return 0;
                }
                local_1bc = (int *)(uint)*(byte *)((int)param_1 + uVar16 * 0x2137b0 + 0x580e5a);
                memcpy(apcStack_1b8,(void *)((int)param_1 + uVar16 * 0x2137b0 + 0x580e3a),
                       (size_t)local_1bc);
              }
              uVar16 = *(uint *)(param_2 + 0x10);
              *(undefined2 *)(param_2 + 0x14) = 0x24;
              uVar11 = *(uint *)(((uint)&local_1e0 & 0xffffe000) + 8);
              if (uVar16 < 0xffffffdc && uVar16 + 0x24 <= uVar11) {
                uVar11 = 0;
              }
              if (uVar11 == 0) {
                uVar16 = __copy_to_user(uVar16,&local_1bc);
              }
              else {
                uVar16 = 0x24;
              }
              if (2 < DebugLevel) {
                printk("Query OID_802_11_SSID (Len=%d, ssid=%s)\n",local_1bc,apcStack_1b8);
                return uVar16;
              }
              return uVar16;
            }
            if (param_3 == 0x50a) {
              if (*(int *)(iVar15 + 0x38) != 0x400) {
                return 0;
              }
              uVar16 = (uint)*(byte *)(iVar15 + 0x3c);
              if (*(char *)((int)param_1 + uVar16 * 0x2137b0 + 0x580e8d) == '\0') {
                return 0;
              }
              uVar11 = *(uint *)(param_2 + 0x10);
              uVar12 = *(uint *)(((uint)&local_1e0 & 0xffffe000) + 8);
              if (uVar11 < 0xfffffffa && uVar11 + 6 <= uVar12) {
                uVar12 = 0;
              }
              if (uVar12 == 0) {
                uVar11 = __copy_to_user(uVar11,&DAT_00371c92 + (int)(param_1 + uVar16 * 0x84dec),6);
              }
              else {
                uVar11 = 6;
              }
              if (3 < DebugLevel) {
                local_1e0 = (uint)*(byte *)((int)param_1 + uVar16 * 0x2137b0 + 0x371c95);
                local_1dc = (uint)*(byte *)((int)param_1 + uVar16 * 0x2137b0 + 0x371c96);
                local_1d8 = (uint)*(byte *)((int)param_1 + uVar16 * 0x2137b0 + 0x371c97);
                printk("IOCTL::SIOCGIWAP(=%02x:%02x:%02x:%02x:%02x:%02x)\n",
                       *(undefined1 *)((int)param_1 + uVar16 * 0x2137b0 + 0x371c92),
                       *(undefined1 *)((int)param_1 + uVar16 * 0x2137b0 + 0x371c93),
                       (char)param_1[uVar16 * 0x84dec + 0xdc725]);
                return uVar11;
              }
              return uVar11;
            }
          }
        }
        else {
          if (param_3 == 0x540) {
            if (2 < DebugLevel) {
              printk("Query::Get Radius setting(%u)\n",0xe79);
            }
            Dot1xIoctlQueryRadiusConf(param_1,param_2);
            return 0;
          }
          if (param_3 < 0x541) {
            if (param_3 == 0x52a) {
              if (*(ushort *)(param_2 + 0x14) < 0x408) {
                return 0xffffffea;
              }
              uVar16 = *(uint *)(param_2 + 0x10);
              uVar11 = *(uint *)(((uint)&local_1e0 & 0xffffe000) + 8);
              if (uVar16 < 0xfffffbf8 && uVar16 + 0x408 <= uVar11) {
                uVar11 = 0;
              }
              if (uVar11 != 0) {
                return 0x408;
              }
              uVar16 = __copy_to_user(uVar16,(char *)((int)param_1 +
                                                     (int)(
                                                  "[RTMPSetInformation][BandIdx=%d] Ndis802_11OFDM5\n"
                                                  + *(int *)(iVar15 + 0x3c) * 0x5834 + 0x31)));
              return uVar16;
            }
          }
          else {
            if (param_3 == 0x549) {
              RTMPIoctlQueryStaAid(param_1,param_2);
              return 0;
            }
            if (param_3 == 0x551) {
              RTMPIoctlQueryStaRsn(param_1,param_2);
              return 0;
            }
          }
        }
        goto LAB_00039094;
      }
      if (param_3 == 0x67d) {
        iVar15 = *(int *)(iVar15 + 0x3c);
        os_alloc_mem(param_1,&local_1bc,0x70);
        if (local_1bc == (int *)0x0) {
          return 0;
        }
        __memzero(local_1bc,0x70);
        local_1bc[3] = param_1[iVar15 * 0x160d + 0xaed8d];
        local_1bc[2] = param_1[iVar15 * 0x160d + 0xaed8c];
        *local_1bc = param_1[iVar15 * 0x160d + 0xaed8a];
        local_1bc[1] = param_1[iVar15 * 0x160d + 0xaed8b];
        local_1bc[4] = param_1[iVar15 * 0x160d + 0xaed8e];
        local_1bc[5] = param_1[iVar15 * 0x160d + 0xaed8f];
        local_1bc[6] = param_1[iVar15 * 0x160d + 0xaed90];
        local_1bc[7] = param_1[iVar15 * 0x160d + 0xaed91];
        local_1bc[8] = param_1[iVar15 * 0x160d + 0xaed92];
        local_1bc[9] = param_1[iVar15 * 0x160d + 0xaed93];
        local_1bc[10] = param_1[iVar15 * 0x160d + 0xaed94];
        local_1bc[0xb] = param_1[iVar15 * 0x160d + 0xaed95];
        local_1bc[0xc] = param_1[iVar15 * 0x160d + 0xaed96];
        local_1bc[0xd] = param_1[iVar15 * 0x160d + 0xaed97];
        local_1bc[0xe] = param_1[iVar15 * 0x160d + 0xaed98];
        local_1bc[0xf] = param_1[iVar15 * 0x160d + 0xaed99];
        uVar11 = *(uint *)(((uint)&local_1e0 & 0xffffe000) + 8);
        uVar16 = *(uint *)(param_2 + 0x10);
        if (uVar16 < 0xffffff90 && uVar16 + 0x70 <= uVar11) {
          uVar11 = 0;
        }
        *(undefined2 *)(param_2 + 0x14) = 0x70;
        if (uVar11 != 0) {
          uVar16 = 0x70;
          goto LAB_00038e5c;
        }
        uVar6 = 0x70;
      }
      else {
        if (0x67d < param_3) {
          if (param_3 == 0x68a) {
            if (2 < DebugLevel) {
              printk("Query ChipID = %x\n",param_1[0xa5b19]);
            }
            uVar16 = *(uint *)(param_2 + 0x10);
            *(undefined2 *)(param_2 + 0x14) = 4;
            uVar11 = *(uint *)(((uint)&local_1e0 & 0xffffe000) + 8);
            if (uVar16 < 0xfffffffc && uVar16 + 4 <= uVar11) {
              uVar11 = 0;
            }
            if (uVar11 != 0) {
              return 4;
            }
            uVar16 = __copy_to_user(uVar16,param_1 + 0xa5b19);
            return uVar16;
          }
          if (param_3 < 0x68b) {
            if (param_3 == 0x689) {
              memset(&local_1bc,0,0x191);
              if (((*(int *)(iVar15 + 0x38) == 0x400) &&
                  (iVar8 = get_wdev_by_ioctl_idx_and_iftype
                                     (param_1,*(undefined4 *)(iVar15 + 0x3c),0x400), iVar8 != 0)) &&
                 (puVar7 = (uint *)get_scan_tab_by_wdev(param_1), *puVar7 - 1 < 0xff)) {
                uVar16 = 0;
                do {
                  iVar8 = uVar16 * 0x28;
                  uVar11 = uVar16 + 1 & 0xff;
                  *(char *)((int)apcStack_1b8 + iVar8 + -3) = (char)puVar7[uVar16 * 0x2bd + 0x27];
                  memmove((void *)((int)apcStack_1b8 + iVar8 + -2),
                          (void *)((int)puVar7 + uVar16 * 0xaf4 + 0x9d),
                          (uint)(byte)puVar7[uVar16 * 0x2bd + 0x27]);
                  memmove(auStack_199 + iVar8,(void *)((int)puVar7 + uVar16 * 0xaf4 + 0xe),6);
                  bVar10 = (char)local_1bc + 1;
                  local_1bc = (int *)CONCAT31(local_1bc._1_3_,bVar10);
                  if (9 < bVar10) break;
                  uVar16 = *puVar7;
                  bVar17 = 0xfe < uVar16;
                  if (uVar16 < 0x100) {
                    bVar17 = uVar16 <= uVar11;
                  }
                  uVar16 = uVar11;
                } while (!bVar17);
              }
              uVar16 = *(uint *)(param_2 + 0x10);
              *(undefined2 *)(param_2 + 0x14) = 0x191;
              uVar11 = *(uint *)(((uint)&local_1e0 & 0xffffe000) + 8);
              if (uVar16 < 0xfffffe6f && uVar16 + 0x191 <= uVar11) {
                uVar11 = 0;
              }
              if (uVar11 == 0) {
                __copy_to_user(uVar16,&local_1bc);
              }
              if (2 < DebugLevel) {
                printk("Query OID_802_11_GET_SSID_BSSID (Len=%d)\n",*(undefined2 *)(param_2 + 0x14))
                ;
              }
              goto LAB_00038a3c;
            }
          }
          else {
            if (param_3 == 0x68b) {
              if (2 < DebugLevel) {
                printk("Driver Version = %s\n",&_LC646);
              }
              uVar16 = *(uint *)(param_2 + 0x10);
              *(undefined2 *)(param_2 + 0x14) = 8;
              uVar11 = *(uint *)(((uint)&local_1e0 & 0xffffe000) + 8);
              if (uVar16 < 0xfffffff8 && uVar16 + 8 <= uVar11) {
                uVar11 = 0;
              }
              if (uVar11 != 0) {
                return 8;
              }
              uVar16 = __copy_to_user(uVar16,&_LC646);
              return uVar16;
            }
            if (param_3 == 0x713) {
              uVar11 = *(uint *)(param_2 + 0x10);
              *(undefined2 *)(param_2 + 0x14) = 6;
              uVar12 = *(uint *)(((uint)&local_1e0 & 0xffffe000) + 8);
              if (uVar11 < 0xfffffffa && uVar11 + 6 <= uVar12) {
                uVar12 = 0;
              }
              if (uVar12 != 0) {
                return 6;
              }
              uVar16 = __copy_to_user(uVar11,(char *)((int)param_1 +
                                                     (int)(
                                                  "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                                  + uVar16 * 0x5834 + 0x101)));
              return uVar16;
            }
          }
          goto LAB_00039094;
        }
        if (param_3 == 0x60d) {
LAB_00038a3c:
          local_1bc._0_1_ = -0x7f;
          if (*(int *)(iVar15 + 0x38) == 0x400) {
            iVar15 = (*(uint *)(iVar15 + 0x3c) & 0xff) * 0x2137b0;
            iVar8 = GetAssociatedAPByWdev
                              (param_1,(undefined *)((int)param_1 + (int)(&DAT_0036db58 + iVar15)));
            if (*(char *)((int)param_1 + iVar15 + 0x580e8d) == '\0' || iVar8 == 0) {
              return 0;
            }
            local_1bc._0_1_ = *(char *)(iVar8 + 0x10c);
          }
          iVar15 = *(int *)(param_2 + 0x10);
          *(undefined2 *)(param_2 + 0x14) = 1;
          uVar16 = *(uint *)(((uint)&local_1e0 & 0xffffe000) + 8);
          if (iVar15 != -1 && iVar15 + 1U <= uVar16) {
            uVar16 = 0;
          }
          if (uVar16 == 0) {
            uVar16 = __copy_to_user(iVar15,&local_1bc);
          }
          else {
            uVar16 = 1;
          }
          if (2 < DebugLevel) {
            printk("Query OID_802_11_RSSI (Len=%d, Rssi=%d)\n",*(undefined2 *)(param_2 + 0x14),
                   (int)(char)local_1bc);
            return uVar16;
          }
          return uVar16;
        }
        if (param_3 < 0x60e) {
          if (param_3 == 0x60b) {
            uVar16 = *(uint *)(iVar15 + 0x3c);
            if (*(int *)(iVar15 + 0x38) != 0x400) {
              return 0xffffffa1;
            }
            if (1 < uVar16) {
              if (DebugLevel < 0) {
                uVar16 = 0;
              }
              else {
                printk("%s> Error! apcli-idx > MAX_APCLI_NUM!\n","RTMPAPQueryInformation");
                uVar16 = 0;
              }
            }
            uVar2 = *(ushort *)(param_1 + uVar16 * 0x84dec + 0x16038e);
            uVar11 = hc_get_chip_wtbl_max_num(param_1[0x29e5e8]);
            if (uVar11 <= uVar2) {
              return 0xffffffa1;
            }
            if (param_1[(uint)*(ushort *)(param_1 + uVar16 * 0x84dec + 0x16038e) * 0x530 + 0x28748]
                != 0x40001 &&
                param_1[(uint)*(ushort *)(param_1 + uVar16 * 0x84dec + 0x16038e) * 0x530 + 0x28748]
                != 2) {
              return 0xffffffa1;
            }
            if ((*(char *)((int)param_1 + uVar16 * 0x2137b0 + 0x580e8e) == '\x01') &&
               (*(char *)((int)param_1 +
                         (uint)*(ushort *)(param_1 + uVar16 * 0x84dec + 0x16038e) * 0x620 + 0x2f762)
                == '\x01')) {
              local_1bc = (int *)0x1;
            }
            else {
              local_1bc = (int *)0x0;
            }
            uVar16 = *(uint *)(param_2 + 0x10);
            *(undefined2 *)(param_2 + 0x14) = 4;
            uVar11 = *(uint *)(((uint)&local_1e0 & 0xffffe000) + 8);
            if (uVar16 < 0xfffffffc && uVar16 + 4 <= uVar11) {
              uVar11 = 0;
            }
            if (uVar11 != 0) {
              return 4;
            }
            uVar16 = __copy_to_user(uVar16,&local_1bc);
            return uVar16;
          }
          goto LAB_00039094;
        }
        if (param_3 != 0x60e) {
          if (param_3 == 0x617) {
            if (2 < DebugLevel) {
              printk("Query::OID_802_11_SET_IEEE8021X\n");
            }
            *(undefined2 *)(param_2 + 0x14) = 4;
            uVar16 = *(uint *)(param_2 + 0x10);
            local_1c4 = (uint)((char)param_1[*(int *)(iVar15 + 0x3c) * 0x160d + 0xade02] == '\x01');
            uVar11 = *(uint *)(((uint)&local_1e0 & 0xffffe000) + 8);
            if (uVar16 < 0xfffffffc && uVar16 + 4 <= uVar11) {
              uVar11 = 0;
            }
            if (uVar11 != 0) {
              return 4;
            }
            uVar16 = __copy_to_user(uVar16,&local_1c4,4);
            return uVar16;
          }
          goto LAB_00039094;
        }
        os_alloc_mem(param_1,&local_1bc,0xc0);
        if (local_1bc == (int *)0x0) {
          if (DebugLevel < 3) {
            return 0xfffffff2;
          }
          printk("Query::OID_802_11_STATISTICS(mem alloc failed)\n");
          return 0xfffffff2;
        }
        if (2 < DebugLevel) {
          printk("Query::OID_802_11_STATISTICS\n");
        }
        uVar11 = param_1[0x28e700];
        iVar8 = param_1[0x28e701];
        uVar16 = param_1[0x28e702];
        iVar15 = param_1[0x28e703];
        local_1bc[2] = uVar16 + uVar11;
        local_1bc[3] = iVar15 + iVar8 + (uint)CARRY4(uVar16,uVar11);
        iVar15 = param_1[0x28e703];
        local_1bc[4] = param_1[0x28e702];
        local_1bc[5] = iVar15;
        iVar15 = param_1[0x28e705];
        local_1bc[6] = param_1[0x28e704];
        local_1bc[7] = iVar15;
        iVar15 = param_1[0x28e707];
        local_1bc[8] = param_1[0x28e706];
        local_1bc[9] = iVar15;
        iVar15 = param_1[0x28e709];
        local_1cc = param_1 + 0x28e71c;
        local_1bc[10] = param_1[0x28e708];
        local_1bc[0xb] = iVar15;
        iVar15 = param_1[0x28e70b];
        uVar6 = 0xc0;
        local_1bc[0xc] = param_1[0x28e70a];
        local_1bc[0xd] = iVar15;
        iVar15 = param_1[0x28e70d];
        local_1bc[0xe] = param_1[0x28e70c];
        local_1bc[0xf] = iVar15;
        iVar15 = param_1[0x28e70f];
        local_1bc[0x10] = param_1[0x28e70e];
        local_1bc[0x11] = iVar15;
        iVar15 = param_1[0x28e711];
        local_1bc[0x12] = param_1[0x28e710];
        local_1bc[0x13] = iVar15;
        iVar15 = param_1[0x28e713];
        local_1bc[0x14] = param_1[0x28e712];
        local_1bc[0x15] = iVar15;
        iVar15 = param_1[0x28e715];
        local_1bc[0x16] = param_1[0x28e714];
        local_1bc[0x17] = iVar15;
        iVar15 = param_1[0x28e79d];
        local_1bc[0x18] = param_1[0x28e79c];
        local_1bc[0x19] = iVar15;
        iVar15 = param_1[0x28e701];
        local_1bc[0x1a] = param_1[0x28e700];
        local_1bc[0x1b] = iVar15;
        iVar15 = param_1[0x28e71b];
        local_1bc[0x1c] = param_1[0x28e71a];
        local_1bc[0x1d] = iVar15;
        uVar11 = *(uint *)(((uint)&local_1e0 & 0xffffe000) + 8);
        uVar16 = *(uint *)(param_2 + 0x10);
        if (uVar16 < 0xffffff40 && uVar16 + 0xc0 <= uVar11) {
          uVar11 = 0;
        }
        *(undefined2 *)(param_2 + 0x14) = 0xc0;
        if (uVar11 != 0) {
          uVar16 = 0xc0;
          goto LAB_00038e5c;
        }
      }
      uVar16 = __copy_to_user(uVar16,local_1bc,uVar6);
LAB_00038e5c:
      os_free_mem(local_1bc);
      return uVar16;
    }
    if (2 < DebugLevel) {
      printk("Query::RT_OID_VERSION_INFO\n");
    }
    uVar16 = *(uint *)(((uint)&local_1e0 & 0xffffe000) + 8);
    uVar11 = *(uint *)(param_2 + 0x10);
    local_1bc = (int *)0x2e312e37;
    if (uVar11 < 0xfffffff9 && uVar11 + 7 <= uVar16) {
      uVar16 = 0;
    }
    *(undefined2 *)(param_2 + 0x14) = 7;
    apcStack_1b8[0] = "er fail!!\n";
    if (uVar16 != 0) {
      return 0xfffffff2;
    }
    iVar15 = __copy_to_user(uVar11,&local_1bc);
    goto joined_r0x00038b90;
  }
  if (param_3 == 0x973) {
    uVar6 = Get_System_CapNode_Info(param_1);
    uVar4 = Get_System_Bw_Info(param_1,uVar6);
    iVar15 = *(int *)(param_2 + 0x10);
    *(undefined2 *)(param_2 + 0x14) = 1;
    local_1bc = (int *)CONCAT31(local_1bc._1_3_,uVar4);
    uVar16 = *(uint *)(((uint)&local_1e0 & 0xffffe000) + 8);
    if (iVar15 != -1 && iVar15 + 1U <= uVar16) {
      uVar16 = 0;
    }
    if (uVar16 == 0) {
      uVar16 = __copy_to_user(iVar15,&local_1bc);
    }
    else {
      uVar16 = 1;
    }
    if (2 < DebugLevel) {
      printk("Query::OID_802_11_WIFISPECTRUM_GET_CAPTURE_BW CapBw = %d\n",(uint)local_1bc & 0xff);
      return uVar16;
    }
    return uVar16;
  }
  if (param_3 < 0x974) {
    if (param_3 == 0x751) {
      if (2 < DebugLevel) {
        printk("Query::RT_OID_WSC_QUERY_STATUS\n");
      }
      if (*(int *)(iVar15 + 0x38) == 0x400) {
        iVar15 = *(int *)(iVar15 + 0x3c);
        if (1 < iVar15) {
          if (DebugLevel < 0) {
            iVar15 = 0;
          }
          else {
            printk("%s> Error! apcli-idx > MAX_APCLI_NUM!\n","RTMPAPQueryInformation");
            iVar15 = 0;
          }
        }
        local_1bc = (int *)param_1[iVar15 * 0x84dec + 0xdbb92];
      }
      else {
        local_1bc = (int *)param_1[uVar16 * 0x160d + 0xae14e];
      }
      uVar16 = *(uint *)(param_2 + 0x10);
      *(undefined2 *)(param_2 + 0x14) = 4;
      uVar11 = *(uint *)(((uint)&local_1e0 & 0xffffe000) + 8);
      if (uVar16 < 0xfffffffc && uVar16 + 4 <= uVar11) {
        uVar11 = 0;
      }
      if (uVar11 != 0) {
        return 0xfffffff2;
      }
      iVar15 = __copy_to_user(uVar16,&local_1bc);
      if (iVar15 == 0) {
        return 0;
      }
      return 0xfffffff2;
    }
    if (param_3 < 0x752) {
      if (param_3 == 0x74e) {
        if (2 < DebugLevel) {
          printk("Query::RT_OID_WSC_V2_SUPPORT (=%d)\n",
                 *(undefined1 *)((int)param_1 + uVar16 * 0x5834 + 0x2bb05d));
        }
        uVar11 = *(uint *)(param_2 + 0x10);
        *(undefined2 *)(param_2 + 0x14) = 1;
        uVar12 = *(uint *)(((uint)&local_1e0 & 0xffffe000) + 8);
        if (uVar11 != 0xffffffff && uVar11 + 1 <= uVar12) {
          uVar12 = 0;
        }
        if (uVar12 != 0) {
          return 0xfffffff2;
        }
        uVar12 = 0xb05d;
      }
      else if (param_3 < 0x74f) {
        if (param_3 != 0x74d) goto LAB_00039094;
        if (2 < DebugLevel) {
          printk("Query::RT_OID_WSC_FRAGMENT_SIZE (=%d)\n",(short)param_1[uVar16 * 0x160d + 0xaec46]
                );
        }
        uVar11 = *(uint *)(param_2 + 0x10);
        *(undefined2 *)(param_2 + 0x14) = 2;
        uVar12 = *(uint *)(((uint)&local_1e0 & 0xffffe000) + 8);
        if (uVar11 < 0xfffffffe && uVar11 + 2 <= uVar12) {
          uVar12 = 0;
        }
        if (uVar12 != 0) {
          return 0xfffffff2;
        }
        uVar12 = 0xb118;
      }
      else {
        if (param_3 != 0x74f) {
          if (param_3 != 0x750) goto LAB_00039094;
          *(undefined2 *)(param_2 + 0x14) = 0x3a8;
          os_alloc_mem(param_1,&local_1bc);
          if (local_1bc == (int *)0x0) {
            if (DebugLevel < 3) {
              return 0xfffffff2;
            }
            printk("RT_OID_802_11_WSC_QUERY_PROFILE fail!\n");
            return 0xfffffff2;
          }
          if (*(int *)(iVar15 + 0x38) == 0x400) {
            if (1 < uVar16) {
              if (DebugLevel < 0) {
                param_1 = param_1 + 0xdbb8f;
                goto LAB_00038408;
              }
              printk("%s> Error! apcli-idx > MAX_APCLI_NUM!\n","RTMPAPQueryInformation");
              uVar16 = 0;
            }
            param_1 = param_1 + uVar16 * 0x84dec + 0xdbb8f;
            if (2 < DebugLevel) {
              printk(
                    "IF(apcli : %d) RT_OID_802_11_WSC_QUERY_PROFILE :: This command is from apcli interface now.\n"
                    );
            }
          }
          else {
            param_1 = param_1 + uVar16 * 0x160d + 0xae14b;
          }
LAB_00038408:
          RTMPZeroMemory(local_1bc,0x3a8);
          memmove(local_1bc,param_1 + 0x724,0x3a8);
          if (local_1bc[0xb] == 0x10001) {
            *(undefined2 *)(local_1bc + 0x1c) = 0;
            __memzero(local_1bc + 0xc,0x40);
          }
          uVar16 = (uint)*(ushort *)(param_2 + 0x14);
          uVar11 = *(uint *)(((uint)&local_1e0 & 0xffffe000) + 8);
          if (!CARRY4(*(uint *)(param_2 + 0x10),uVar16) &&
              *(uint *)(param_2 + 0x10) + uVar16 <= uVar11) {
            uVar11 = 0;
          }
          if (uVar11 == 0) {
            uVar16 = __copy_to_user();
          }
          if (uVar16 == 0) {
            uVar16 = 0;
          }
          else {
            uVar16 = 0xfffffff2;
          }
          os_free_mem(local_1bc);
          if (2 < DebugLevel) {
            printk("Query::RT_OID_802_11_WSC_QUERY_PROFILE\n");
            return uVar16;
          }
          return uVar16;
        }
        if (2 < DebugLevel) {
          printk("Query::RT_OID_WSC_CONFIG_STATUS\n");
        }
        uVar11 = *(uint *)(param_2 + 0x10);
        *(undefined2 *)(param_2 + 0x14) = 1;
        uVar12 = *(uint *)(((uint)&local_1e0 & 0xffffe000) + 8);
        if (uVar11 != 0xffffffff && uVar11 + 1 <= uVar12) {
          uVar12 = 0;
        }
        if (uVar12 != 0) {
          return 0xfffffff2;
        }
        uVar12 = 0x8534;
      }
    }
    else if (param_3 == 0x753) {
      if (2 < DebugLevel) {
        printk("Query::RT_OID_WSC_QUERY_UUID\n");
      }
      uVar11 = *(uint *)(param_2 + 0x10);
      *(undefined2 *)(param_2 + 0x14) = 0x25;
      uVar12 = *(uint *)(((uint)&local_1e0 & 0xffffe000) + 8);
      if (uVar11 < 0xffffffdb && uVar11 + 0x25 <= uVar12) {
        uVar12 = 0;
      }
      if (uVar12 != 0) {
        return 0xfffffff2;
      }
      uVar12 = 0xaf60;
    }
    else {
      if (param_3 < 0x753) {
        if (2 < DebugLevel) {
          printk("Query::RT_OID_WSC_PIN_CODE\n");
        }
        *(undefined2 *)(param_2 + 0x14) = 4;
        uVar12 = *(uint *)(((uint)&local_1e0 & 0xffffe000) + 8);
        uVar11 = *(uint *)(param_2 + 0x10);
        local_1c8 = param_1[uVar16 * 0x160d + 0xae152];
        if (uVar11 < 0xfffffffc && uVar11 + 4 <= uVar12) {
          uVar12 = 0;
        }
        goto joined_r0x00038ecc;
      }
      if (param_3 == 0x75c) {
        if (2 < DebugLevel) {
          printk("Query::RT_OID_WSC_QUERY_PEER_INFO_ON_RUNNING\n");
        }
        if (param_1[uVar16 * 0x160d + 0xae14f] < 0x10) {
          return 0xfffffff2;
        }
        uVar11 = *(uint *)(param_2 + 0x10);
        *(undefined2 *)(param_2 + 0x14) = 0xc6;
        uVar12 = *(uint *)(((uint)&local_1e0 & 0xffffe000) + 8);
        if (uVar11 < 0xffffff3a && uVar11 + 0xc6 <= uVar12) {
          uVar12 = 0;
        }
        if (uVar12 != 0) {
          return 0xfffffff2;
        }
        iVar15 = __copy_to_user(uVar11,(char *)((int)param_1 +
                                               (int)("%sHT Operating Mode : %d\n" +
                                                    uVar16 * 0x5834 + 0xf)));
        goto joined_r0x00038b90;
      }
      if (param_3 != 0x760) goto LAB_00039094;
      if (2 < DebugLevel) {
        printk("Query::RT_OID_WSC_MAC_ADDRESS\n");
      }
      uVar11 = *(uint *)(param_2 + 0x10);
      *(undefined2 *)(param_2 + 0x14) = 6;
      uVar12 = *(uint *)(((uint)&local_1e0 & 0xffffe000) + 8);
      if (uVar11 < 0xfffffffa && uVar11 + 6 <= uVar12) {
        uVar12 = 0;
      }
      if (uVar12 != 0) {
        return 0xfffffff2;
      }
      uVar12 = 0x7269;
    }
  }
  else {
    if (param_3 == 0x9a2) {
      uVar16 = *(uint *)(param_2 + 0x10);
      uVar11 = (uint)*(ushort *)(param_2 + 0x14);
      uVar12 = *(uint *)(((uint)&local_1e0 & 0xffffe000) + 8);
      if (!CARRY4(uVar16,uVar11) && uVar16 + uVar11 <= uVar12) {
        uVar12 = 0;
      }
      if (uVar12 == 0) {
        uVar16 = __copy_to_user(uVar16,param_1 + 0x29f425);
        return uVar16;
      }
      return uVar11;
    }
    if (0x9a2 < param_3) {
      if (param_3 == 0x1802) {
        local_1bc = (int *)0x0;
        os_alloc_mem(0,&local_1bc,0x440);
        iVar15 = (int)local_1bc;
        if (local_1bc != (int *)0x0) {
          piVar14 = param_1 + 0x28dc8d;
          __memzero(local_1bc,0x440);
          iVar8 = 0;
          do {
            if ((char)*piVar14 != '\0') {
              iVar1 = iVar8 * 0x44;
              iVar8 = iVar8 + 1;
              memcpy((void *)((int)local_1bc + iVar1),piVar14,0x44);
            }
            piVar14 = piVar14 + 0x11;
          } while (piVar14 != param_1 + 0x28dd9d);
          uVar16 = *(uint *)(param_2 + 0x10);
          uVar11 = *(uint *)(((uint)&local_1e0 & 0xffffe000) + 8);
          if (uVar16 < 0xfffffbc0 && uVar16 + 0x440 <= uVar11) {
            uVar11 = 0;
          }
          if (uVar11 == 0) {
            uVar16 = __copy_to_user(uVar16,iVar15,0x440);
          }
          else {
            uVar16 = 0x440;
          }
          if (2 < DebugLevel) {
            printk("Query::OID_GET_AIR_MONITOR_RESULT success!\n");
          }
          os_free_mem(local_1bc);
          return uVar16;
        }
        if (DebugLevel < 0) {
          return 0xfffffff2;
        }
        printk("Query::OID_GET_AIR_MONITOR_RESULT alloc memory failed!\n");
        return 0xfffffff2;
      }
      if (param_3 < 0x1803) {
        if (param_3 == 0x1281) {
          uVar16 = ZTE_QueryNOAssocRssi(param_1,param_2);
          return uVar16;
        }
        goto LAB_00039094;
      }
      if (param_3 != 0x494a) {
        if (param_3 != 0x494c) goto LAB_00039094;
        local_1bc = (int *)0x0;
        if (*(short *)(param_2 + 0x14) != 0x13) {
          if (DebugLevel < 0) {
            return 0x16;
          }
          printk("RT_QUERY_RRM_CAPABILITY: length(%d) check failed\n",*(short *)(param_2 + 0x14));
          return 0x16;
        }
        if (*(char *)((int)param_1 + uVar16 * 0x5834 + 0x2b7d69) == '\0') {
          if (DebugLevel < 0) {
            return 0x16;
          }
          printk("RT_QUERY_RRM_CAPABILITY: rrm off\n");
          return 0x16;
        }
        os_alloc_mem(0,&local_1bc);
        if (local_1bc == (int *)0x0) {
          if (DebugLevel < 0) {
            return 0xc;
          }
          printk("RT_QUERY_RRM_CAPABILITY : no memory!!!\n");
          return 0xc;
        }
        uVar16 = (uint)*(ushort *)(param_2 + 0x14);
        uVar11 = *(uint *)(((uint)&local_1e0 & 0xffffe000) + 8);
        if (!CARRY4(*(uint *)(param_2 + 0x10),uVar16) &&
            *(uint *)(param_2 + 0x10) + uVar16 <= uVar11) {
          uVar11 = 0;
        }
        if (uVar11 == 0) {
          iVar8 = __copy_from_user(local_1bc);
          if (iVar8 == 0) goto LAB_00039b44;
        }
        else {
          if (uVar16 == 0) {
LAB_00039b44:
            pcVar3 = (char *)local_1bc;
            iVar8 = MacTableLookup(param_1,(char *)((int)local_1bc + 5));
            if ((iVar8 == 0) ||
               (((param_1[*(int *)(iVar15 + 0x3c) * 0x160d + 0xadc9d] & 1U) == 0 &&
                (*(short *)(iVar8 + 0x514) != 0x10a)))) {
              if (-1 < DebugLevel) {
                local_1e0 = (uint)(byte)pcVar3[8];
                local_1dc = (uint)(byte)pcVar3[9];
                local_1d8 = (uint)(byte)pcVar3[10];
                printk("RT_QUERY_RRM_CAPABILITY: STA(%02x:%02x:%02x:%02x:%02x:%02x)not associates with AP!\n"
                       ,pcVar3[5],pcVar3[6],pcVar3[7]);
              }
              goto LAB_00039ba4;
            }
            __memzero(pcVar3 + 0xb,8);
            if (*(char *)local_1bc != '\x04') {
              if (0 < DebugLevel) {
                printk("RT_QUERY_WNM_CAPABILITY: only check rrm cap now\n");
              }
              goto LAB_00039ba4;
            }
            uVar6 = *(undefined4 *)(iVar8 + 0x11f0);
            *(undefined4 *)(pcVar3 + 0xb) = *(undefined4 *)(iVar8 + 0x11ec);
            *(undefined4 *)(pcVar3 + 0xf) = uVar6;
            uVar11 = *(uint *)(((uint)&local_1e0 & 0xffffe000) + 8);
            uVar16 = (uint)*(ushort *)(param_2 + 0x14);
            if (!CARRY4(*(uint *)(param_2 + 0x10),uVar16) &&
                *(uint *)(param_2 + 0x10) + uVar16 <= uVar11) {
              uVar11 = 0;
            }
            if (uVar11 == 0) {
              uVar16 = __copy_to_user();
            }
            if (uVar16 == 0) goto LAB_00039f20;
            if (-1 < DebugLevel) {
              printk("RT_QUERY_RRM_CAPABILITY: copy to user failed!\n");
            }
            goto LAB_00039cfc;
          }
          __memzero(local_1bc,uVar16);
        }
        if (-1 < DebugLevel) {
          printk("RT_QUERY_RRM_CAPABILITY: copy from user failed!\n");
        }
        goto LAB_00039cfc;
      }
      local_1bc = (int *)0x0;
      if (*(short *)(param_2 + 0x14) != 0xc) {
        if (DebugLevel < 0) {
          return 0x16;
        }
        printk("RT_QUERY_WNM_CAPABILITY: length(%d) check failed\n");
        return 0x16;
      }
      if (*(char *)((int)param_1 + uVar16 * 0x5834 + 0x2bbee6) == '\0') {
        if (DebugLevel < 0) {
          return 0x16;
        }
        printk("RT_QUERY_WNM_CAPABILITY: btm off\n");
        return 0x16;
      }
      os_alloc_mem(0,&local_1bc,0xc);
      if (local_1bc == (int *)0x0) {
        if (DebugLevel < 0) {
          return 0xc;
        }
        printk("RT_QUERY_WNM_CAPABILITY: no memory!!!\n");
        return 0xc;
      }
      uVar16 = (uint)*(ushort *)(param_2 + 0x14);
      uVar11 = *(uint *)(((uint)&local_1e0 & 0xffffe000) + 8);
      if (!CARRY4(*(uint *)(param_2 + 0x10),uVar16) && *(uint *)(param_2 + 0x10) + uVar16 <= uVar11)
      {
        uVar11 = 0;
      }
      if (uVar11 == 0) {
        iVar8 = __copy_from_user(local_1bc);
        if (iVar8 == 0) {
LAB_00039c04:
          pcVar3 = (char *)local_1bc;
          iVar8 = MacTableLookup(param_1,(char *)((int)local_1bc + 5));
          if ((iVar8 == 0) ||
             (((param_1[*(int *)(iVar15 + 0x3c) * 0x160d + 0xadc9d] & 1U) == 0 &&
              (*(short *)(iVar8 + 0x514) != 0x10a)))) {
            if (-1 < DebugLevel) {
              local_1e0 = (uint)(byte)pcVar3[8];
              local_1dc = (uint)(byte)pcVar3[9];
              local_1d8 = (uint)(byte)pcVar3[10];
              printk("RT_QUERY_WNM_CAPABILITY: STA(%02x:%02x:%02x:%02x:%02x:%02x)not associates with AP!\n"
                     ,pcVar3[5],pcVar3[6],pcVar3[7]);
            }
LAB_00039ba4:
            os_free_mem(local_1bc);
            return 0x16;
          }
          pcVar3[0xb] = '\0';
          if (*(char *)local_1bc != '\x04') {
            if (0 < DebugLevel) {
              printk("RT_QUERY_WNM_CAPABILITY: only check btm cap now\n");
            }
            goto LAB_00039ba4;
          }
          if ((*(char *)(iVar8 + 0xd22) != '\0') && (pcVar3[0xb] = '\x01', 2 < DebugLevel)) {
            printk("RT_QUERY_WNM_CAPABILITY: BTMCap=%d\n");
          }
          uVar11 = *(uint *)(param_2 + 0x10);
          uVar9 = (uint)*(ushort *)(param_2 + 0x14);
          uVar13 = *(uint *)(((uint)&local_1e0 & 0xffffe000) + 8);
          uVar12 = uVar11 + uVar9;
          uVar16 = uVar12;
          if (!CARRY4(uVar11,uVar9)) {
            uVar16 = uVar12 - (uVar13 + 1);
          }
          uVar18 = CONCAT44(uVar16,uVar9);
          if (!CARRY4(uVar11,uVar9) && uVar12 <= uVar13) {
            uVar13 = 0;
          }
          if (uVar13 == 0) {
            uVar18 = __copy_to_user(uVar11,local_1bc);
          }
          if ((int)uVar18 == 0) {
LAB_00039f20:
            os_free_mem(local_1bc);
            return 0;
          }
          if (-1 < DebugLevel) {
            printk("RT_QUERY_WNM_CAPABILITY: copy to user failed!\n",
                   (int)((ulonglong)uVar18 >> 0x20));
          }
          goto LAB_00039cfc;
        }
      }
      else {
        if (uVar16 == 0) goto LAB_00039c04;
        __memzero(local_1bc,uVar16);
      }
      if (-1 < DebugLevel) {
        printk("RT_QUERY_WNM_CAPABILITY: copy from user failed!\n");
      }
LAB_00039cfc:
      os_free_mem(local_1bc);
      return 0xe;
    }
    if (param_3 == 0x985) {
      uVar16 = ZeroWaitDfsQueryCmdHandler(param_1,param_2);
      return uVar16;
    }
    if (param_3 < 0x986) {
      if (param_3 == 0x974) {
        uVar6 = Get_System_CapNode_Info(param_1);
        uVar5 = Get_System_CenFreq_Info(param_1,uVar6);
        *(undefined2 *)(param_2 + 0x14) = 2;
        uVar16 = *(uint *)(param_2 + 0x10);
        local_1bc = (int *)CONCAT22(local_1bc._2_2_,uVar5);
        uVar11 = *(uint *)(((uint)&local_1e0 & 0xffffe000) + 8);
        if (uVar16 < 0xfffffffe && uVar16 + 2 <= uVar11) {
          uVar11 = 0;
        }
        if (uVar11 == 0) {
          uVar16 = __copy_to_user(uVar16,&local_1bc,2);
        }
        else {
          uVar16 = 2;
        }
        if (2 < DebugLevel) {
          printk("Query::OID_802_11_WIFISPECTRUM_GET_CENTRAL_FREQ CenFreq = %d\n",
                 (uint)local_1bc & 0xffff);
          return uVar16;
        }
        return uVar16;
      }
LAB_00039094:
      if (DebugLevel < 3) {
        return 0xffffffa1;
      }
      printk("Query::unknown IOCTL\'s subcmd = 0x%08x, apidx=%d\n",param_3,uVar16);
      return 0xffffffa1;
    }
    if (param_3 != 0x990) {
      if (param_3 == 0x9a1) {
        local_1bc = (int *)0x0;
        uVar6 = HcGetBandByWdev(piVar14);
        RTMP_GET_TEMPERATURE(param_1,uVar6,&local_1bc);
        if (-1 < DebugLevel) {
          printk("CurrentTemperature              = %d\n",local_1bc);
        }
        uVar16 = *(uint *)(param_2 + 0x10);
        *(undefined2 *)(param_2 + 0x14) = 4;
        uVar11 = *(uint *)(((uint)&local_1e0 & 0xffffe000) + 8);
        if (uVar16 < 0xfffffffc && uVar16 + 4 <= uVar11) {
          uVar11 = 0;
        }
        if (uVar11 != 0) {
          return 4;
        }
        uVar16 = __copy_to_user(uVar16,&local_1bc);
        return uVar16;
      }
      goto LAB_00039094;
    }
    if (2 < DebugLevel) {
      printk("Query::OID_WSC_QUERY_UUID\n");
    }
    uVar11 = *(uint *)(param_2 + 0x10);
    *(undefined2 *)(param_2 + 0x14) = 0x10;
    uVar12 = *(uint *)(((uint)&local_1e0 & 0xffffe000) + 8);
    if (uVar11 < 0xfffffff0 && uVar11 + 0x10 <= uVar12) {
      uVar12 = 0;
    }
    if (uVar12 != 0) {
      return 0xfffffff2;
    }
    uVar12 = 0xaf50;
  }
  iVar15 = __copy_to_user(uVar11,(int)param_1 + (uVar12 | 0x2b0000) + uVar16 * 0x5834);
joined_r0x00038b90:
  if (iVar15 == 0) {
    return 0;
  }
  return 0xfffffff2;
}

