// module: mt7915.ko
// function: RTMPSetInformation @ 0x5aa58
// size: 12312 bytes
//

/* WARNING: Type propagation algorithm not settling */

uint RTMPSetInformation(int param_1,int param_2,uint param_3,uint param_4)

{
  size_t *psVar1;
  int *piVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined1 uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  undefined *puVar15;
  uint *puVar16;
  void *pvVar17;
  bool bVar18;
  char *local_88;
  char *local_84;
  int *local_80;
  uint local_7c;
  uint local_78;
  uint local_70;
  uint local_6c;
  uint *local_68;
  int local_64;
  uint *local_60;
  int local_5c;
  size_t *local_58;
  uint local_54;
  void *local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined1 local_40;
  uint local_3c;
  undefined1 local_29;
  
  iVar4 = GetStaCfgByWdev(param_1,param_4);
  local_70 = 10;
  local_6c = 0;
  local_68 = (uint *)0x0;
  local_64 = 0;
  local_60 = (uint *)0x0;
  local_5c = 0;
  local_58 = (size_t *)0x0;
  local_54 = 0;
  if (DebugLevel < 3) {
    param_3 = param_3 & 0x7fff;
    if (param_3 != 0x519) {
      if (0x519 < param_3) {
        if (param_3 != 0x649) {
          if (param_3 < 0x64a) {
            if (param_3 == 0x637) {
LAB_0005c204:
              if (*(short *)(param_2 + 0x14) != 4) {
                return 0xffffffea;
              }
              uVar10 = *(uint *)(param_2 + 0x10);
              uVar13 = *(uint *)(((uint)&local_88 & 0xffffe000) + 8);
              uVar11 = uVar10 + 4;
              uVar12 = uVar11;
              if (uVar10 < 0xfffffffc) {
                uVar12 = uVar11 - (uVar13 + 1);
              }
              if (uVar10 < 0xfffffffc && uVar11 <= uVar13) {
                uVar13 = 0;
              }
              if (uVar13 == 0) {
                uVar12 = __copy_from_user(&local_4c,uVar10,4);
              }
              else {
                __memzero(&local_4c,4,uVar12);
                uVar12 = 4;
              }
              iVar6 = DebugLevel;
              *(byte *)(iVar4 + 0x8d8) = (byte)local_4c & 1;
              local_88 = (char *)((uint)((int)local_4c << 0x1d) >> 0x1f);
              local_84 = (char *)((uint)((int)local_4c << 0x1c) >> 0x1f);
              local_80 = (int *)((uint)((int)local_4c << 0x1b) >> 0x1f);
              local_7c = (uint)((int)local_4c << 0x19) >> 0x1e;
              *(byte *)(param_1 + 0x794ca7) = (byte)((uint)((int)local_4c << 0x1e) >> 0x1f);
              *(byte *)(param_1 + 0x794ca8) = (byte)((uint)((int)local_4c << 0x1d) >> 0x1f);
              *(byte *)(param_1 + 0x794ca9) = (byte)((uint)((int)local_4c << 0x1c) >> 0x1f);
              *(byte *)(param_1 + 0x794caa) = (byte)((uint)((int)local_4c << 0x1b) >> 0x1f);
              *(byte *)(param_1 + 0x794cc4) = (byte)((uint)((int)local_4c << 0x19) >> 0x1e);
              if (2 < iVar6) {
                printk("Set::RT_OID_802_11_SET_APSD_SETTING (apsd=0x%lx, APSDCap=%d, [BE,BK,VI,VO]=[%d/%d/%d/%d],\tMaxSPLen=%d)\n"
                       ,local_4c,*(undefined1 *)(iVar4 + 0x8d8));
                return uVar12;
              }
              return uVar12;
            }
            if (param_3 < 0x638) {
              if (param_3 != 0x521) {
                if (0x521 < param_3) {
                  if (param_3 != 0x614) {
                    if (param_3 != 0x634) {
                      return 0xffffffa1;
                    }
LAB_0005aea0:
                    if (*(short *)(param_2 + 0x14) == 0x10) {
                      uVar12 = *(uint *)(((uint)&local_88 & 0xffffe000) + 8);
                      if (*(uint *)(param_2 + 0x10) < 0xfffffff0 &&
                          *(uint *)(param_2 + 0x10) + 0x10 <= uVar12) {
                        uVar12 = 0;
                      }
                      if (uVar12 == 0) {
                        uVar12 = __copy_from_user(&local_4c);
                      }
                      else {
                        __memzero(&local_4c,0x10);
                        uVar12 = 0x10;
                      }
                      if (2 < DebugLevel) {
                        local_88 = (char *)(local_48 >> 0x10 & 0xff);
                        local_84 = (char *)(local_48 >> 0x18);
                        local_80 = (int *)(local_44 & 0xff);
                        local_7c = local_44 >> 8 & 0xff;
                        local_78 = local_44 >> 0x10 & 0xff;
                        printk("Set::pHTPhyMode\t(PhyMode = %d,TransmitNo = %d, HtMode =\t%d,\tExtOffset =\t%d , MCS = %d, BW =\t%d,\tSTBC = %d, SHORTGI = %d)\n"
                               ,local_4c,local_48 & 0xff,local_48._1_1_);
                      }
                      local_40 = HcGetBandByWdev(param_4);
                      local_44 = CONCAT13(*(undefined1 *)(param_4 + 0x1a),(undefined3)local_44);
                      if ((*(ushort *)(param_4 + 0x18) & 0x18) != 0) {
                        RTMPSetHT(param_1,&local_4c,param_4);
                      }
                    }
                    else {
                      uVar12 = 0xffffffea;
                    }
                    if (2 < DebugLevel) {
                      local_88 = (char *)(((uint)*(byte *)(param_4 + 0x8b3) << 0x1d) >> 0x1f);
                      printk("Set::RT_OID_802_11_SET_HT_PHYMODE(MCS=%d,BW=%d,SGI=%d,STBC=%d)\n",
                             *(byte *)(param_4 + 0x8b2) & 0x3f,
                             ((uint)*(ushort *)(param_4 + 0x8b2) << 0x17) >> 0x1e,
                             ((uint)*(byte *)(param_4 + 0x8b3) << 0x1e) >> 0x1f);
                      return uVar12;
                    }
                    return uVar12;
                  }
LAB_0005b85c:
                  if (*(ushort *)(param_2 + 0x14) < 4) {
                    return 0xffffffea;
                  }
                  iVar4 = *(int *)(param_2 + 0x10);
                  uVar11 = *(uint *)(((uint)&local_88 & 0xffffe000) + 8);
                  uVar10 = iVar4 + 1;
                  uVar12 = uVar10;
                  if (iVar4 != -1) {
                    uVar12 = uVar10 - (uVar11 + 1);
                  }
                  if (iVar4 != -1 && uVar10 <= uVar11) {
                    uVar11 = 0;
                  }
                  if (uVar11 == 0) {
                    uVar12 = __copy_from_user(&local_4c,iVar4,1);
                  }
                  else {
                    __memzero(&local_4c,1,uVar12);
                    uVar12 = 1;
                  }
                  iVar4 = DebugLevel;
                  uVar9 = (char)local_4c;
                  if (100 < ((uint)local_4c & 0xff)) {
                    uVar9 = 100;
                    local_4c = (int *)CONCAT31(local_4c._1_3_,100);
                  }
                  *(undefined1 *)(param_1 + 0x795041) = uVar9;
                  *(undefined1 *)(param_1 + 0x794cd8) = uVar9;
                  if (iVar4 < 3) {
                    *(undefined1 *)(param_1 + 0x795042) = uVar9;
                    *(undefined1 *)(param_1 + 0x794cd9) = uVar9;
                    return uVar12;
                  }
                  printk("Set::RT_OID_802_11_TX_POWER_LEVEL_1 (BAND0) (=%d)\n");
                  iVar4 = DebugLevel;
                  *(char *)(param_1 + 0x795042) = (char)local_4c;
                  *(char *)(param_1 + 0x794cd9) = (char)local_4c;
                  if (2 < iVar4) {
                    printk("Set::RT_OID_802_11_TX_POWER_LEVEL_1 (BAND1) (=%d)\n");
                    return uVar12;
                  }
                  return uVar12;
                }
                if (param_3 != 0x520) {
                  return 0xffffffa1;
                }
LAB_0005b27c:
                os_alloc_mem(param_1,&local_68,*(undefined2 *)(param_2 + 0x14));
                if (local_68 == (uint *)0x0) {
                  return 0xfffffff4;
                }
                uVar10 = *(uint *)(param_2 + 0x10);
                uVar12 = (uint)*(ushort *)(param_2 + 0x14);
                uVar11 = *(uint *)(((uint)&local_88 & 0xffffe000) + 8);
                if (!CARRY4(uVar10,uVar12) && uVar10 + uVar12 <= uVar11) {
                  uVar11 = 0;
                }
                if (uVar11 == 0) {
                  uVar12 = __copy_from_user(local_68,uVar10,uVar12);
                  uVar10 = (uint)*(ushort *)(param_2 + 0x14);
                }
                else if (uVar12 == 0) {
                  uVar10 = 0;
                }
                else {
                  __memzero(local_68,uVar12);
                  uVar10 = (uint)*(ushort *)(param_2 + 0x14);
                }
                if ((*local_68 == uVar10) && (local_68[2] < 0x21)) {
                  if (2 < DebugLevel) {
                    printk("Set::OID_802_11_ADD_KEY (id=0x%x, Len=%d-byte)\n",local_68[1]);
                  }
                }
                else if (DebugLevel < 3) {
                  uVar12 = 0xffffffea;
                }
                else {
                  uVar12 = 0xffffffea;
                  printk("Set::OID_802_11_ADD_KEY, Failed!!\n");
                }
                os_free_mem(local_68);
                return uVar12;
              }
LAB_0005bd4c:
              if (*(short *)(param_2 + 0x14) != 0x20) {
                return 0xffffffea;
              }
              os_alloc_mem(0,&local_5c);
              if (local_5c == 0) {
                return 0;
              }
              uVar10 = *(uint *)(param_2 + 0x10);
              uVar12 = (uint)*(ushort *)(param_2 + 0x14);
              uVar11 = *(uint *)(((uint)&local_88 & 0xffffe000) + 8);
              if (!CARRY4(uVar10,uVar12) && uVar10 + uVar12 <= uVar11) {
                uVar11 = 0;
              }
              if (uVar11 == 0) {
                uVar12 = __copy_from_user(local_5c,uVar10,uVar12);
              }
              else if (uVar12 != 0) {
                __memzero(local_5c,uVar12);
              }
              if (*(int *)(local_5c + 4) - 0x14U < 0x17d) {
                *(short *)(&DAT_00794c50 + param_1) = (short)*(int *)(local_5c + 4);
              }
              *(short *)(iVar4 + 0x40b2) = (short)*(undefined4 *)(local_5c + 8);
              RTMP_MapKHZ2ChannelID(*(undefined4 *)(local_5c + 0xc),param_4 + 0x1a);
              iVar6 = DebugLevel;
              *(undefined1 *)(iVar4 + 0x4165) = *(undefined1 *)(param_4 + 0x1a);
              if (2 < iVar6) {
                printk("Set::OID_802_11_CONFIGURATION (BeacnPeriod=%d,AtimW=%d,Ch=%d)\n",
                       *(undefined4 *)(local_5c + 4),*(undefined4 *)(local_5c + 8),
                       *(undefined1 *)(param_4 + 0x1a));
              }
              *(undefined1 *)(iVar4 + 0x212468) = 1;
              os_free_mem(local_5c);
              return uVar12;
            }
            if (param_3 == 0x641) {
LAB_0005bf90:
              if (*(short *)(param_2 + 0x14) != 8) {
                return 0xffffffea;
              }
              uVar10 = *(uint *)(param_2 + 0x10);
              uVar13 = *(uint *)(((uint)&local_88 & 0xffffe000) + 8);
              uVar11 = uVar10 + 8;
              uVar12 = uVar11;
              if (uVar10 < 0xfffffff8) {
                uVar12 = uVar11 - (uVar13 + 1);
              }
              if (uVar10 < 0xfffffff8 && uVar11 <= uVar13) {
                uVar13 = 0;
              }
              if (uVar13 == 0) {
                uVar12 = __copy_from_user(&local_4c,uVar10,8);
              }
              else {
                __memzero(&local_4c,8,uVar12);
                uVar12 = 8;
              }
              uVar7 = wlan_config_get_ba_tx_wsize(param_4);
              uVar10 = wlan_config_get_ba_rx_wsize(param_4);
              if (local_4c._2_1_ < 2) {
                wlan_config_set_ba_enable(param_4,local_48._3_1_);
                wlan_operate_set_min_start_space(param_4,local_4c._3_1_);
                wlan_operate_set_mmps(param_4,local_48._2_1_);
                wlan_operate_set_mmps(param_4,local_48._2_1_);
                wlan_operate_set_max_amsdu_len(param_4,local_48._1_1_);
                wlan_operate_set_min_start_space(param_4,local_4c._3_1_);
                if (0xff < uVar10) {
                  uVar10 = 0x100;
                }
                wlan_config_set_ba_txrx_wsize(param_4,uVar7,uVar10 & 0xffff);
                iVar4 = DebugLevel;
                *(undefined4 *)(param_1 + 0x795048) = *(undefined4 *)(param_1 + 0x795044);
                if (2 < iVar4) {
                  printk("Set::(Orde.AutoBA = %d)(ReBAWinLimit=%d)(TxBAWinLimit=%d)\n",
                         local_48._3_1_,uVar10 & 0xffff,uVar7);
                  if (2 < DebugLevel) {
                    printk("Set::(MimoPs = %d)(AmsduSize=%d)(MpduDensity=%d)\n",local_48._2_1_,
                           local_48._1_1_,local_4c._3_1_);
                    return uVar12;
                  }
                  return uVar12;
                }
                return uVar12;
              }
              return 2;
            }
            if (param_3 < 0x642) {
              if (param_3 != 0x639) {
                if (param_3 != 0x63f) {
                  return 0xffffffa1;
                }
LAB_0005b148:
                if (*(short *)(param_2 + 0x14) != 1) {
                  return 0xffffffea;
                }
                iVar4 = *(int *)(param_2 + 0x10);
                uVar11 = *(uint *)(((uint)&local_88 & 0xffffe000) + 8);
                uVar10 = iVar4 + 1;
                uVar12 = uVar10;
                if (iVar4 != -1) {
                  uVar12 = uVar10 - (uVar11 + 1);
                }
                if (iVar4 != -1 && uVar10 <= uVar11) {
                  uVar11 = 0;
                }
                if (uVar11 == 0) {
                  uVar12 = __copy_from_user(param_4 + 0x8d4,iVar4,1);
                }
                else {
                  __memzero(param_4 + 0x8d4,1,uVar12);
                  uVar12 = 1;
                }
                if (2 < DebugLevel) {
                  printk("Set::RT_OID_802_11_SET_WMM (=%d)\n",*(undefined1 *)(param_4 + 0x8d4));
                  return uVar12;
                }
                return uVar12;
              }
LAB_0005b778:
              if (*(short *)(param_2 + 0x14) != 4) {
                return 0xffffffea;
              }
              uVar10 = *(uint *)(param_2 + 0x10);
              uVar13 = *(uint *)(((uint)&local_88 & 0xffffe000) + 8);
              uVar11 = uVar10 + 4;
              uVar12 = uVar11;
              if (uVar10 < 0xfffffffc) {
                uVar12 = uVar11 - (uVar13 + 1);
              }
              if (uVar10 < 0xfffffffc && uVar11 <= uVar13) {
                uVar13 = 0;
              }
              if (uVar13 == 0) {
                uVar12 = __copy_from_user(param_1 + 0x794cc6,uVar10,4);
              }
              else {
                __memzero(param_1 + 0x794cc6,4,uVar12);
                uVar12 = 4;
              }
              if ((ushort)*(byte *)(param_1 + 0x794cc6) != *(ushort *)(iVar4 + 0x2124b8)) {
                uVar7 = GetAssociatedAPByWdev(param_1,iVar4);
                if (2 < DebugLevel) {
                  printk("%s(line=%d): -->\n","RTMPSetInformation",0xe62);
                }
                MlmeSetPsmBit(param_1,iVar4,*(undefined1 *)(param_1 + 0x794cc6));
                if (*(char *)(param_1 + 0x794cc6) == '\0') {
                  local_88 = (char *)(uint)*(ushort *)(iVar4 + 0x2124b8);
                }
                else {
                  local_88 = (char *)0x1;
                }
                RTMPSendNullFrame(param_1,uVar7,*(undefined1 *)(param_1 + 0x794cd0),1);
              }
              if (2 < DebugLevel) {
                printk("Set::RT_OID_802_11_SET_APSD_PSM (bAPSDForcePowerSave:%d)\n",
                       *(undefined1 *)(param_1 + 0x794cc6));
                return uVar12;
              }
              return uVar12;
            }
            if (param_3 == 0x643) {
LAB_0005b4c8:
              if (*(short *)(param_2 + 0x14) != 0xe) {
                return 0xffffffea;
              }
              uVar10 = *(uint *)(param_2 + 0x10);
              uVar13 = *(uint *)(((uint)&local_88 & 0xffffe000) + 8);
              uVar11 = uVar10 + 0xe;
              uVar12 = uVar11;
              if (uVar10 < 0xfffffff2) {
                uVar12 = uVar11 - (uVar13 + 1);
              }
              if (uVar10 < 0xfffffff2 && uVar11 <= uVar13) {
                uVar13 = 0;
              }
              if (uVar13 == 0) {
                uVar12 = __copy_from_user(&local_4c,uVar10,0xe);
              }
              else {
                __memzero(&local_4c,0xe,uVar12);
                uVar12 = 0xe;
              }
              bVar3 = local_48._3_1_;
              if (7 < local_48._3_1_) {
                return 2;
              }
              iVar4 = MacTableLookup2(param_1,(int)&local_4c + 1,param_4);
              if (iVar4 == 0) {
                if (2 < DebugLevel) {
                  printk("RT_OID_802_11_ADD_IMME_BA. break on no connection.----:%x:%x\n",
                         local_48._1_1_,local_48._2_1_);
                  return uVar12;
                }
                return uVar12;
              }
              if ((char)local_4c == '\0') {
                if (*(char *)(iVar4 + 0xe7) == '\x01') {
                  wlan_config_set_ba_txrx_wsize(*(undefined4 *)(iVar4 + 8),0x10,0x10);
                }
                ba_ori_session_setup(param_1,*(undefined2 *)(iVar4 + 0xe0),bVar3,0);
              }
              if (2 < DebugLevel) {
                local_88 = (char *)((uint)local_4c >> 0x18);
                local_80 = (int *)(uint)local_48._1_1_;
                local_7c = (uint)local_48._2_1_;
                local_84 = local_88;
                printk("Set::RT_OID_802_11_ADD_IMME_BA. Rec = %d. Mac = %02x:%02x:%02x:%02x:%02x:%02x .\n"
                       ,(uint)local_4c & 0xff,local_4c._1_1_,local_4c._2_1_);
                return uVar12;
              }
              return uVar12;
            }
            if (param_3 != 0x644) {
              return 0xffffffa1;
            }
            goto LAB_0005abdc;
          }
          if (param_3 == 0x745) {
LAB_0005c0a0:
            if (*(short *)(param_2 + 0x14) != 0x24) {
              return 0xffffffea;
            }
            __memzero(&local_4c);
            uVar10 = *(uint *)(param_2 + 0x10);
            uVar12 = (uint)*(ushort *)(param_2 + 0x14);
            uVar11 = *(uint *)(((uint)&local_88 & 0xffffe000) + 8);
            if (!CARRY4(uVar10,uVar12) && uVar10 + uVar12 <= uVar11) {
              uVar11 = 0;
            }
            if (uVar11 == 0) {
              uVar12 = __copy_from_user(&local_4c,uVar10,uVar12);
            }
            else if (uVar12 != 0) {
              __memzero(&local_4c,uVar12);
            }
            local_29 = 0;
            Set_WscSsid_Proc(param_1,&local_48);
            return uVar12;
          }
          if (param_3 < 0x746) {
            if (param_3 != 0x740) {
              if (param_3 < 0x741) {
                if (param_3 != 0x739) {
                  return 0xffffffa1;
                }
LAB_0005b304:
                if (*(char *)(iVar4 + 0x21313a) == '\0') {
                  return 0xffffffea;
                }
                if (*(short *)(param_2 + 0x14) != 4) {
                  return 0xffffffea;
                }
                uVar10 = *(uint *)(param_2 + 0x10);
                uVar13 = *(uint *)(((uint)&local_88 & 0xffffe000) + 8);
                uVar11 = uVar10 + 4;
                uVar12 = uVar11;
                if (uVar10 < 0xfffffffc) {
                  uVar12 = uVar11 - (uVar13 + 1);
                }
                if (uVar10 < 0xfffffffc && uVar11 <= uVar13) {
                  uVar13 = 0;
                }
                if (uVar13 == 0) {
                  uVar12 = __copy_from_user(&local_54,uVar10,4);
                }
                else {
                  __memzero(&local_54,4,uVar12);
                  uVar12 = 4;
                }
                uVar10 = local_54;
                if (local_54 < 3) {
                  uVar7 = HcGetBandByWdev(param_4);
                  RTMPSetLED(param_1,uVar10 & 0xff,uVar7);
                  return uVar12;
                }
                if (DebugLevel < 4) {
                  return 2;
                }
                printk("WPS LED Mode 10::Parameter of LED Mode 10 must be 0x00, or 0x01, or 0x02\n")
                ;
                return 2;
              }
              if (param_3 != 0x741) {
                if (param_3 != 0x743) {
                  return 0xffffffa1;
                }
LAB_0005af7c:
                if (*(short *)(param_2 + 0x14) != 4) {
                  return 0xffffffea;
                }
                uVar10 = *(uint *)(param_2 + 0x10);
                local_4c = (int *)0x0;
                uVar13 = *(uint *)(((uint)&local_88 & 0xffffe000) + 8);
                uVar11 = uVar10 + 4;
                uVar12 = uVar11;
                if (uVar10 < 0xfffffffc) {
                  uVar12 = uVar11 - (uVar13 + 1);
                }
                if (uVar10 < 0xfffffffc && uVar11 <= uVar13) {
                  uVar13 = 0;
                }
                if (uVar13 == 0) {
                  uVar12 = __copy_from_user(&local_4c,uVar10,4);
                }
                else {
                  __memzero(&local_4c,4,uVar12);
                  uVar12 = 4;
                }
                if (local_4c < *(uint *)(param_4 + 0x2f74)) {
                  _raw_spin_lock_bh(param_1 + 0x285c50);
                  WscWriteConfToPortCfg
                            (param_1,param_4 + 0x12e4,
                             param_4 + 0x12e4 + (int)local_4c * 0x74 + 0x1c98,1);
                  _raw_spin_unlock_bh(param_1 + 0x285c50);
                  BN_mod_lshift1[iVar4] = (code)0x1;
                  LinkDown(param_1,1,iVar4,0);
                  return uVar12;
                }
                if (2 < DebugLevel) {
                  printk("RT_OID_WSC_SET_CONN_BY_PROFILE_INDEX:: wrong wsc_profile_index(%d)\n");
                  return uVar12;
                }
                return uVar12;
              }
LAB_0005ba60:
              if (*(short *)(param_2 + 0x14) != 1) {
                return 0xffffffea;
              }
              iVar4 = *(int *)(param_2 + 0x10);
              uVar11 = *(uint *)(((uint)&local_88 & 0xffffe000) + 8);
              uVar10 = iVar4 + 1;
              uVar12 = uVar10;
              if (iVar4 != -1) {
                uVar12 = uVar10 - (uVar11 + 1);
              }
              if (iVar4 != -1 && uVar10 <= uVar11) {
                uVar11 = 0;
              }
              if (uVar11 == 0) {
                uVar12 = __copy_from_user(param_4 + 0x3c04,iVar4,1);
              }
              else {
                __memzero(param_4 + 0x3c04,1,uVar12);
                uVar12 = 1;
              }
              if (2 < DebugLevel) {
                printk("RT_OID_WSC_DRIVER_AUTO_CONNECT::WscDriverAutoConnect is %d\n",
                       *(undefined1 *)(param_4 + 0x3c04));
                return uVar12;
              }
              return uVar12;
            }
LAB_0005be10:
            uVar12 = (uint)*(ushort *)(param_2 + 0x14);
            if (0x38 < uVar12 - 8) {
              return 0xffffffea;
            }
            uVar11 = *(uint *)(param_2 + 0x10);
            uVar14 = *(uint *)(((uint)&local_88 & 0xffffe000) + 8);
            iVar4 = param_4 + 0x3c81;
            uVar13 = uVar11 + uVar12;
            uVar10 = uVar13;
            if (!CARRY4(uVar11,uVar12)) {
              uVar10 = uVar13 - (uVar14 + 1);
            }
            if (!CARRY4(uVar11,uVar12) && uVar13 <= uVar14) {
              uVar14 = 0;
            }
            if (uVar14 == 0) {
              uVar12 = __copy_from_user(iVar4,uVar11,uVar12);
            }
            else {
              __memzero(iVar4,uVar12,uVar10);
            }
            __memzero(iVar4,0x40);
            iVar4 = DebugLevel;
            *(uint *)(param_4 + 0x3cc4) = (uint)*(ushort *)(param_2 + 0x14);
            if (2 < iVar4) {
              printk("RT_OID_WSC_SET_PASSPHRASE::KeyLen(%d)\n");
              return uVar12;
            }
            return uVar12;
          }
          if (param_3 == 0x748) {
LAB_0005b5d8:
            if (*(short *)(param_2 + 0x14) != 4) {
              return 0xffffffea;
            }
            uVar10 = *(uint *)(param_2 + 0x10);
            local_4c = (int *)0x0;
            uVar13 = *(uint *)(((uint)&local_88 & 0xffffe000) + 8);
            uVar11 = uVar10 + 4;
            uVar12 = uVar11;
            if (uVar10 < 0xfffffffc) {
              uVar12 = uVar11 - (uVar13 + 1);
            }
            if (uVar10 < 0xfffffffc && uVar11 <= uVar13) {
              uVar13 = 0;
            }
            if (uVar13 == 0) {
              uVar12 = __copy_from_user(&local_4c,uVar10,4);
              if (uVar12 == 0) {
                if (local_4c == (int *)0x2) {
                  local_4c = (int *)0x4;
                }
                else {
                  if (local_4c == (int *)0x1) {
                    Set_WscConfMode_Proc(param_1,&_LC166);
                    goto LAB_0005b624;
                  }
                  if (local_4c != (int *)0x4) {
                    Set_WscConfMode_Proc(param_1,&_LC168);
                    goto LAB_0005b624;
                  }
                }
                Set_WscConfMode_Proc(param_1,&_LC167);
                local_4c = (int *)0x2;
              }
            }
            else {
              __memzero(&local_4c,4,uVar12);
              uVar12 = 4;
            }
LAB_0005b624:
            if (2 < DebugLevel) {
              printk("RT_OID_WSC_SET_CONF_MODE:: WscConfMode = %d\n",local_4c);
              return uVar12;
            }
            return uVar12;
          }
          if (param_3 < 0x749) {
            if (param_3 == 0x746) {
LAB_0005b94c:
              if (*(short *)(param_2 + 0x14) != 8) {
                return 0xffffffea;
              }
              uVar10 = *(uint *)(param_2 + 0x10);
              local_4c = (int *)0x0;
              uVar13 = *(uint *)(((uint)&local_88 & 0xffffe000) + 8);
              uVar11 = uVar10 + 8;
              uVar12 = uVar11;
              if (uVar10 < 0xfffffff8) {
                uVar12 = uVar11 - (uVar13 + 1);
              }
              if (uVar10 < 0xfffffff8 && uVar11 <= uVar13) {
                uVar13 = 0;
              }
              local_48 = 0;
              local_44 = local_44 & 0xffffff00;
              if (uVar13 != 0) {
                __memzero(&local_4c,8,uVar12);
                return 8;
              }
              uVar12 = __copy_from_user(&local_4c,uVar10,8);
              if (uVar12 != 0) {
                return uVar12;
              }
              iVar4 = Set_WscPinCode_Proc(param_1,&local_4c);
              if (iVar4 == 0) {
                return 0xffffffea;
              }
              return 0;
            }
            if (param_3 != 0x747) {
              return 0xffffffa1;
            }
LAB_0005b1c4:
            if (*(short *)(param_2 + 0x14) != 4) {
              return 0xffffffea;
            }
            uVar10 = *(uint *)(param_2 + 0x10);
            local_4c = (int *)0x0;
            uVar13 = *(uint *)(((uint)&local_88 & 0xffffe000) + 8);
            uVar11 = uVar10 + 4;
            uVar12 = uVar11;
            if (uVar10 < 0xfffffffc) {
              uVar12 = uVar11 - (uVar13 + 1);
            }
            if (uVar10 < 0xfffffffc && uVar11 <= uVar13) {
              uVar13 = 0;
            }
            if (uVar13 == 0) {
              uVar12 = __copy_from_user(&local_4c,uVar10,4);
              if (uVar12 == 0) {
                if (local_4c == (int *)0x1) {
                  iVar4 = Set_WscMode_Proc(param_1,&_LC166);
                }
                else if (local_4c == (int *)0x2) {
                  iVar4 = Set_WscMode_Proc(param_1,&_LC167);
                }
                else {
                  if (local_4c != (int *)0x3) {
                    if (DebugLevel < 3) {
                      return 0xffffffea;
                    }
                    uVar12 = 0xffffffea;
                    printk("RT_OID_WSC_SET_MODE::unknown WscMode = %d\n");
                    goto LAB_0005b20c;
                  }
                  iVar4 = Set_WscMode_Proc(param_1,&_LC170);
                }
                if (iVar4 == 0) {
                  uVar12 = 0xffffffea;
                }
              }
            }
            else {
              __memzero(&local_4c,4,uVar12);
              uVar12 = 4;
            }
LAB_0005b20c:
            if (2 < DebugLevel) {
              printk("RT_OID_WSC_SET_MODE::WscMode = %d\n",local_4c);
              return uVar12;
            }
            return uVar12;
          }
          if (param_3 == 0x749) {
LAB_0005bf18:
            if (*(short *)(param_2 + 0x14) != 0x3a8) {
              return 0xffffffea;
            }
            iVar4 = param_4 + 0x2f74;
            __memzero(iVar4);
            uVar10 = *(uint *)(param_2 + 0x10);
            uVar12 = (uint)*(ushort *)(param_2 + 0x14);
            uVar11 = *(uint *)(((uint)&local_88 & 0xffffe000) + 8);
            if (!CARRY4(uVar10,uVar12) && uVar10 + uVar12 <= uVar11) {
              uVar11 = 0;
            }
            if (uVar11 == 0) {
              uVar12 = __copy_from_user(iVar4,uVar10,uVar12);
            }
            else if (uVar12 != 0) {
              __memzero(iVar4,uVar12);
            }
            if (2 < DebugLevel) {
              printk("RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n",*(undefined4 *)(param_4 + 0x2f74))
              ;
              return uVar12;
            }
            return uVar12;
          }
          if (param_3 != 0x755) {
            return 0xffffffa1;
          }
          local_4c = (int *)0x0;
LAB_0005adac:
          uVar12 = (uint)*(ushort *)(param_2 + 0x14);
          os_alloc_mem(param_1,&local_4c,uVar12);
          if (local_4c == (int *)0x0) {
            uVar12 = 0xffffffea;
            goto LAB_0005ae5c;
          }
          if (uVar12 == 0) {
            uVar11 = *(uint *)(param_2 + 0x10);
            uVar10 = *(uint *)(((uint)&local_88 & 0xffffe000) + 8);
            if (uVar11 <= uVar10) {
              uVar10 = 0;
            }
            if (uVar10 == 0) {
LAB_0005cb38:
              __copy_from_user(local_4c,uVar11,uVar12);
            }
          }
          else {
            __memzero(local_4c,uVar12);
            uVar11 = *(uint *)(param_2 + 0x10);
            uVar14 = *(uint *)(((uint)&local_88 & 0xffffe000) + 8);
            uVar13 = uVar11 + uVar12;
            uVar10 = uVar13;
            if (!CARRY4(uVar11,uVar12)) {
              uVar10 = uVar13 - (uVar14 + 1);
            }
            if (!CARRY4(uVar11,uVar12) && uVar13 <= uVar14) {
              uVar14 = 0;
            }
            if (uVar14 == 0) goto LAB_0005cb38;
            __memzero(local_4c,uVar12,uVar10);
          }
          piVar2 = local_4c;
          local_88 = (char *)0x24;
          local_84 = (char *)uVar12;
          local_80 = local_4c;
          local_7c = param_4;
          iVar4 = MlmeEnqueueForWsc(param_1,*local_4c,*(undefined4 *)((int)local_4c + 10),0x11);
          if (iVar4 == 0) {
            if (*piVar2 == 0) {
              uVar12 = 0;
            }
            else if (DebugLevel < 3) {
              uVar12 = 0xffffffea;
            }
            else {
              uVar12 = 0xffffffea;
              printk("MlmeEnqueuForWsc return False and envID=0x%x!\n");
            }
          }
          else {
            uVar12 = 0;
          }
          os_free_mem(local_4c);
LAB_0005ae5c:
          if (2 < DebugLevel) {
            printk("RT_OID_WSC_EAPMSG finished!\n");
            return uVar12;
          }
          return uVar12;
        }
LAB_0005bb44:
        os_alloc_mem(param_1,&local_58,*(undefined2 *)(param_2 + 0x14));
        if (local_58 == (size_t *)0x0) {
          if (DebugLevel < 3) {
            return 0xfffffff4;
          }
          printk("Set::OID_802_11_SET_PASSPHRASE, Failed!!\n");
          return 0xfffffff4;
        }
        uVar12 = (uint)*(ushort *)(param_2 + 0x14);
        uVar10 = *(uint *)(((uint)&local_88 & 0xffffe000) + 8);
        if (!CARRY4(*(uint *)(param_2 + 0x10),uVar12) &&
            *(uint *)(param_2 + 0x10) + uVar12 <= uVar10) {
          uVar10 = 0;
        }
        if (uVar10 == 0) {
          iVar6 = __copy_from_user();
          if (iVar6 != 0) goto LAB_0005cba4;
        }
        else if (uVar12 != 0) {
          __memzero(local_58,uVar12);
LAB_0005cba4:
          if (DebugLevel < 3) {
            uVar12 = 0xffffffea;
          }
          else {
            uVar12 = 0xffffffea;
            printk("Set::OID_802_11_SET_PASSPHRASE, Failed (length mismatch)!!\n");
          }
          goto LAB_0005bbb4;
        }
        if (*local_58 - 8 < 0x39) {
          pvVar17 = (void *)(iVar4 + 0x2124da);
          __memzero(pvVar17,0x40);
          psVar1 = local_58;
          memmove(pvVar17,(void *)((int)local_58 + 10),*local_58);
          *(size_t *)(iVar4 + 0x21251c) = *psVar1;
          hex_dump("pStaCfg->WpaPassPhrase",pvVar17,0x40);
          if (DebugLevel < 3) {
            uVar12 = 0;
          }
          else {
            uVar12 = 0;
            printk("WpaPassPhrase=%s\n",pvVar17);
          }
        }
        else if (DebugLevel < 3) {
          uVar12 = 0xffffffea;
        }
        else {
          uVar12 = 0xffffffea;
          printk("Set::OID_802_11_SET_PASSPHRASE, Failed (len less than 8 or greater than 64)!!\n");
        }
LAB_0005bbb4:
        os_free_mem(local_58);
        return uVar12;
      }
      if (param_3 == 0x50d) {
LAB_0005bbbc:
        if (*(short *)(param_2 + 0x14) != 0x20) {
          return 0xffffffea;
        }
        uVar10 = *(uint *)(param_2 + 0x10);
        uVar13 = *(uint *)(((uint)&local_88 & 0xffffe000) + 8);
        uVar11 = uVar10 + 0x20;
        uVar12 = uVar11;
        if (uVar10 < 0xffffffe0) {
          uVar12 = uVar11 - (uVar13 + 1);
        }
        if (uVar10 < 0xffffffe0 && uVar11 <= uVar13) {
          uVar13 = 0;
        }
        if (uVar13 == 0) {
          uVar12 = __copy_from_user(&local_4c,uVar10,0x20);
        }
        else {
          __memzero(&local_4c,0x20,uVar12);
          uVar12 = 0x20;
        }
        *(uint *)(param_1 + 0x79506c) = local_44;
        *(char *)(param_1 + 0x795071) = (char)local_4c;
        *(undefined1 *)(param_1 + 0x795070) = 1;
        if ((local_3c < 0xc && *(ushort *)(param_4 + 0x18) != local_3c) &&
           (*(char *)(iVar4 + 0x4060) == '\0')) {
          uVar7 = HcGetBandByWdev(param_4);
          uVar7 = hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),uVar7);
          hc_set_ChCtrlChListStat(uVar7,0);
          BuildChannelList(param_1,param_4);
          RTMPSetPhyMode(param_1,param_4,local_3c & 0xffff);
          MlmeUpdateTxRates(param_1,0,0);
          UpdateBeaconHandler(param_1,param_4,1);
          AsicEnableIbssSync(param_1,*(undefined2 *)(&DAT_00794c50 + param_1),0,2);
        }
        if (2 < DebugLevel) {
          printk("Set::RT_OID_802_11_SET_STA_CONFIG (Burst=%d, Protection=%ld,ShortSlot=%d\n",
                 *(undefined1 *)(param_1 + 0x795071),*(undefined4 *)(param_1 + 0x79506c),
                 *(undefined1 *)(param_1 + 0x795070));
        }
        AsicSetRxFilter(param_1);
        return uVar12;
      }
      if (0x50d < param_3) {
        if (param_3 != 0x512) {
          if (0x512 < param_3) {
            if (param_3 != 0x515) {
              if (param_3 < 0x516) {
                if (param_3 != 0x513) {
                  if (param_3 != 0x514) {
                    return 0xffffffa1;
                  }
LAB_0005b244:
                  if (*(short *)(param_2 + 0x14) == 4) {
                    uVar10 = *(uint *)(param_2 + 0x10);
                    uVar13 = *(uint *)(((uint)&local_88 & 0xffffe000) + 8);
                    uVar11 = uVar10 + 4;
                    uVar12 = uVar11;
                    if (uVar10 < 0xfffffffc) {
                      uVar12 = uVar11 - (uVar13 + 1);
                    }
                    if (uVar10 < 0xfffffffc && uVar11 <= uVar13) {
                      uVar13 = 0;
                    }
                    if (uVar13 == 0) {
                      uVar12 = __copy_from_user(&local_6c,uVar10,4);
                    }
                    else {
                      __memzero(&local_6c,4,uVar12);
                      uVar12 = 4;
                    }
                    if (local_6c < 0x100000) {
                      wlan_operate_set_rts_len_thld(param_4);
                    }
                    else {
                      uVar12 = 0xffffffea;
                      local_6c = 0;
                    }
                  }
                  else {
                    uVar12 = 0xffffffea;
                  }
                  if (2 < DebugLevel) {
                    printk("Set::OID_802_11_RTS_THRESHOLD (=%d)\n",local_6c);
                    return uVar12;
                  }
                  return uVar12;
                }
LAB_0005c2ac:
                __memzero(param_1 + 0xa39bf8,0x108);
                __memzero(param_1 + 0xa39be4,0x14);
                __memzero(param_1 + 0xa39e08,0x108);
                *(undefined4 *)(param_1 + 0xa39bf4) = 0;
                *(undefined4 *)(param_1 + 0xa39be8) = 0;
                iVar4 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
                if (*(char *)(iVar4 + 0x96) != '\0') {
                  iVar4 = 0;
                  iVar6 = param_1 + 0xa2934;
                  while( true ) {
                    iVar5 = HcGetMaxStaNum(param_1);
                    if (iVar5 <= iVar4) break;
                    __memzero(iVar6,0x24);
                    iVar4 = iVar4 + 1;
                    iVar6 = iVar6 + 0x14c0;
                  }
                }
                if (2 < DebugLevel) {
                  printk("Set::RT_OID_802_11_RESET_COUNTERS\n");
                  return 0;
                }
                return 0;
              }
              if (param_3 != 0x516) {
                if (param_3 != 0x518) {
                  return 0xffffffa1;
                }
LAB_0005acf0:
                os_alloc_mem(param_1,&local_68,*(undefined2 *)(param_2 + 0x14));
                if (local_68 == (uint *)0x0) {
                  return 0xfffffff4;
                }
                uVar10 = *(uint *)(param_2 + 0x10);
                uVar12 = (uint)*(ushort *)(param_2 + 0x14);
                uVar11 = *(uint *)(((uint)&local_88 & 0xffffe000) + 8);
                if (!CARRY4(uVar10,uVar12) && uVar10 + uVar12 <= uVar11) {
                  uVar11 = 0;
                }
                if (uVar11 == 0) {
                  uVar12 = __copy_from_user(local_68,uVar10,uVar12);
                  uVar10 = (uint)*(ushort *)(param_2 + 0x14);
                }
                else if (uVar12 == 0) {
                  uVar10 = 0;
                }
                else {
                  __memzero(local_68,uVar12);
                  uVar10 = (uint)*(ushort *)(param_2 + 0x14);
                }
                puVar16 = local_68;
                if ((*local_68 == uVar10) && (local_68[2] < 0x21)) {
                  if ((*(uint *)(param_4 + 0x2c) & 0xb0) == 0) {
                    if (DebugLevel < 3) {
                      uVar12 = 0xffffffa1;
                    }
                    else {
                      uVar12 = 0xffffffa1;
                      printk(
                            "Set::RT_OID_802_11_ADD_WPA, Failed!! [AuthMode != WPAPSK/WPA2PSK/WPANONE]\n"
                            );
                      puVar16 = local_68;
                    }
                  }
                  else {
                    memmove((void *)(iVar4 + 0x212520),local_68 + 8,local_68[2]);
                    if ((*(uint *)(param_4 + 0x2c) & 0x20) == 0) {
                      *(undefined1 *)(iVar4 + 0x2127b9) = 1;
                    }
                    if (2 < DebugLevel) {
                      printk("Set::RT_OID_802_11_ADD_WPA (id=0x%x, Len=%d-byte)\n",puVar16[1],
                             puVar16[2]);
                      puVar16 = local_68;
                    }
                  }
                }
                else if (DebugLevel < 3) {
                  uVar12 = 0xffffffea;
                }
                else {
                  uVar12 = 0xffffffea;
                  printk("Set::RT_OID_802_11_ADD_WPA, Failed!!\n");
                  puVar16 = local_68;
                }
                os_free_mem(puVar16);
                return uVar12;
              }
LAB_0005b914:
              if (*(short *)(param_2 + 0x14) == 4) {
                uVar10 = *(uint *)(param_2 + 0x10);
                uVar13 = *(uint *)(((uint)&local_88 & 0xffffe000) + 8);
                uVar11 = uVar10 + 4;
                uVar12 = uVar11;
                if (uVar10 < 0xfffffffc) {
                  uVar12 = uVar11 - (uVar13 + 1);
                }
                if (uVar10 < 0xfffffffc && uVar11 <= uVar13) {
                  uVar13 = 0;
                }
                if (uVar13 == 0) {
                  uVar12 = __copy_from_user(&local_4c,uVar10,4);
                }
                else {
                  __memzero(&local_4c,4,uVar12);
                  uVar12 = 4;
                }
                if (local_4c == (int *)0x0) {
                  Set_PSMode_Proc(param_1,&_LC121);
                }
                else if (local_4c == (int *)0x1) {
                  Set_PSMode_Proc(param_1,"Max_PSP");
                }
                else if (local_4c == (int *)0x2) {
                  Set_PSMode_Proc(param_1,"Fast_PSP");
                }
                else if (local_4c == (int *)0x3) {
                  Set_PSMode_Proc(param_1,"Legacy_PSP");
                }
                else {
                  uVar12 = 0xffffffea;
                }
              }
              else {
                uVar12 = 0xffffffea;
                local_4c = (int *)0x0;
              }
              if (2 < DebugLevel) {
                printk("Set::OID_802_11_POWER_MODE (=%d)\n",local_4c);
                return uVar12;
              }
              return uVar12;
            }
LAB_0005b5a0:
            if (*(short *)(param_2 + 0x14) == 4) {
              uVar10 = *(uint *)(param_2 + 0x10);
              uVar13 = *(uint *)(((uint)&local_88 & 0xffffe000) + 8);
              uVar11 = uVar10 + 4;
              uVar12 = uVar11;
              if (uVar10 < 0xfffffffc) {
                uVar12 = uVar11 - (uVar13 + 1);
              }
              if (uVar10 < 0xfffffffc && uVar11 <= uVar13) {
                uVar13 = 0;
              }
              if (uVar13 == 0) {
                uVar12 = __copy_from_user(&local_4c,uVar10,4);
              }
              else {
                __memzero(&local_4c,4,uVar12);
                uVar12 = 4;
              }
              *(undefined1 *)(param_1 + 0x795068) = 0;
              if ((char *)((int)local_4c + -0x100) < (char *)0x82b) {
                wlan_operate_set_frag_thld(param_4);
              }
              else if (local_4c == (int *)0x0) {
                wlan_operate_set_frag_thld(param_4,0x92a);
                *(undefined1 *)(param_1 + 0x795068) = 1;
              }
              else {
                uVar12 = 0xffffffea;
              }
            }
            else {
              uVar12 = 0xffffffea;
              local_4c = (int *)0x0;
            }
            if (2 < DebugLevel) {
              printk("Set::OID_802_11_FRAGMENTATION_THRESHOLD (=%d)\n",local_4c);
              return uVar12;
            }
            return uVar12;
          }
          if (param_3 != 0x50f) {
            if (0x50e < param_3) {
              if (param_3 != 0x510) {
                if (param_3 != 0x511) {
                  return 0xffffffa1;
                }
LAB_0005b018:
                if (*(short *)(param_2 + 0x14) != 4) {
                  return 0xffffffea;
                }
                uVar10 = *(uint *)(param_2 + 0x10);
                uVar13 = *(uint *)(((uint)&local_88 & 0xffffe000) + 8);
                uVar11 = uVar10 + 4;
                uVar12 = uVar11;
                if (uVar10 < 0xfffffffc) {
                  uVar12 = uVar11 - (uVar13 + 1);
                }
                if (uVar10 < 0xfffffffc && uVar11 <= uVar13) {
                  uVar13 = 0;
                }
                if (uVar13 == 0) {
                  uVar12 = __copy_from_user(&local_70,uVar10,4);
                }
                else {
                  __memzero(&local_70,4,uVar12);
                  uVar12 = 4;
                }
                if (10 < local_70) {
                  return 0xffffffea;
                }
                iVar5 = SecAuthModeOldToNew(local_70 & 0xffff);
                iVar6 = DebugLevel;
                if (*(int *)(param_4 + 0x2c) != iVar5) {
                  *(undefined1 *)(iVar4 + 0x212468) = 1;
                }
                *(int *)(param_4 + 0x2c) = iVar5;
                *(undefined1 *)(param_4 + 0x888) = 2;
                if (2 < iVar6) {
                  printk("Set::OID_802_11_AUTHENTICATION_MODE (=0x%x)\n",iVar5);
                  return uVar12;
                }
                return uVar12;
              }
LAB_0005bffc:
              if (*(short *)(param_2 + 0x14) != 4) {
                return 0xffffffea;
              }
              uVar10 = *(uint *)(param_2 + 0x10);
              uVar13 = *(uint *)(((uint)&local_88 & 0xffffe000) + 8);
              uVar11 = uVar10 + 4;
              uVar12 = uVar11;
              if (uVar10 < 0xfffffffc) {
                uVar12 = uVar11 - (uVar13 + 1);
              }
              if (uVar10 < 0xfffffffc && uVar11 <= uVar13) {
                uVar13 = 0;
              }
              if (uVar13 == 0) {
                uVar12 = __copy_from_user(&local_4c,uVar10,4);
              }
              else {
                __memzero(&local_4c,4,uVar12);
                uVar12 = 4;
              }
              iVar6 = SecEncryModeOldToNew((uint)local_4c & 0xffff);
              if (*(int *)(iVar4 + 0x174) != iVar6) {
                *(undefined1 *)(iVar4 + 0x212468) = 1;
              }
              *(int *)(iVar4 + 0x174) = iVar6;
              *(int *)(iVar4 + 0x2124cc) = iVar6;
              *(int *)(iVar4 + 0x2124d0) = iVar6;
              if (*(char *)(iVar4 + 0x4060) == '\0') {
                uVar7 = HcGetBandByWdev(param_4);
                uVar7 = hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),uVar7);
                hc_set_ChCtrlChListStat(uVar7,0);
                BuildChannelList(param_1,param_4);
                RTMPSetPhyMode(param_1,iVar4,*(undefined1 *)(param_1 + 0x794c48));
              }
              if (2 < DebugLevel) {
                printk("Set::OID_802_11_WEP_STATUS (=0x%x)\n",iVar6);
                return uVar12;
              }
              return uVar12;
            }
LAB_0005b410:
            if (*(short *)(param_2 + 0x14) != 8) {
              return 0xffffffea;
            }
            uVar12 = *(uint *)(((uint)&local_88 & 0xffffe000) + 8);
            if (*(uint *)(param_2 + 0x10) < 0xfffffff8 && *(uint *)(param_2 + 0x10) + 8 <= uVar12) {
              uVar12 = 0;
            }
            if (uVar12 == 0) {
              uVar12 = __copy_from_user(&local_4c);
            }
            else {
              __memzero(&local_4c,8);
              uVar12 = 8;
            }
            __memzero(param_4 + 0xaf8,0xc);
            iVar4 = DebugLevel;
            *(int **)(param_4 + 0xaf8) = local_4c;
            *(uint *)(param_4 + 0xafc) = local_48;
            if (2 < iVar4) {
              local_88 = (char *)(uint)*(byte *)(param_4 + 0xafb);
              local_84 = (char *)(uint)*(byte *)(param_4 + 0xafc);
              local_80 = (int *)(uint)*(byte *)(param_4 + 0xafd);
              local_7c = (uint)*(byte *)(param_4 + 0xafe);
              local_78 = (uint)*(byte *)(param_4 + 0xaff);
              printk("Set::OID_802_11_DESIRED_RATES (%02x,%02x,%02x,%02x,%02x,%02x,%02x,%02x)\n",
                     *(undefined1 *)(param_4 + 0xaf8),*(undefined1 *)(param_4 + 0xaf9),
                     *(undefined1 *)(param_4 + 0xafa));
            }
            MlmeUpdateTxRates(param_1,0,0);
            return uVar12;
          }
LAB_0005be90:
          if (*(short *)(param_2 + 0x14) != 4) {
            return 0xffffffea;
          }
          uVar10 = *(uint *)(param_2 + 0x10);
          uVar13 = *(uint *)(((uint)&local_88 & 0xffffe000) + 8);
          uVar11 = uVar10 + 4;
          uVar12 = uVar11;
          if (uVar10 < 0xfffffffc) {
            uVar12 = uVar11 - (uVar13 + 1);
          }
          if (uVar10 < 0xfffffffc && uVar11 <= uVar13) {
            uVar13 = 0;
          }
          if (uVar13 == 0) {
            uVar12 = __copy_from_user(&local_4c,uVar10,4);
          }
          else {
            __memzero(&local_4c,4,uVar12);
            uVar12 = 4;
          }
          if (local_4c == (int *)0x1) {
            *(undefined4 *)(param_1 + 0x795064) = 1;
            MlmeSetTxPreamble(param_1,1);
          }
          else {
            if (((uint)local_4c & 0xfffffffd) != 0) {
              return 0xffffffea;
            }
            *(int **)(param_1 + 0x795064) = local_4c;
            MlmeSetTxPreamble(param_1);
          }
          if (2 < DebugLevel) {
            printk("Set::RT_OID_802_11_PREAMBLE (=%d)\n",local_4c);
            return uVar12;
          }
          return uVar12;
        }
LAB_0005c10c:
        if (*(short *)(param_2 + 0x14) != 4) {
          return 0xffffffea;
        }
        uVar10 = *(uint *)(param_2 + 0x10);
        uVar13 = *(uint *)(((uint)&local_88 & 0xffffe000) + 8);
        uVar11 = uVar10 + 4;
        uVar12 = uVar11;
        if (uVar10 < 0xfffffffc) {
          uVar12 = uVar11 - (uVar13 + 1);
        }
        if (uVar10 < 0xfffffffc && uVar11 <= uVar13) {
          uVar13 = 0;
        }
        if (uVar13 == 0) {
          uVar12 = __copy_from_user(&local_4c,uVar10,4);
        }
        else {
          __memzero(&local_4c,4,uVar12);
          uVar12 = 4;
        }
        if (local_4c == (int *)0x0) {
          Set_NetworkType_Proc(param_1,"Adhoc");
          return uVar12;
        }
        if (local_4c == (int *)0x1) {
          Set_NetworkType_Proc(param_1,"Infra");
          return uVar12;
        }
        if (local_4c != (int *)0x3) {
          if (DebugLevel < 3) {
            return 0xffffffea;
          }
          printk("Set::OID_802_11_INFRASTRUCTURE_MODE (unknown)\n");
          return 0xffffffea;
        }
        Set_NetworkType_Proc(param_1,"Monitor");
        return uVar12;
      }
      if (param_3 == 0x507) {
LAB_0005bc64:
        uVar12 = (uint)*(ushort *)(param_2 + 0x14);
        if (uVar12 == 0) {
          return 0xffffffea;
        }
        if ((-1 < *(char *)(param_1 + 0x794c44)) && (-1 < *(char *)(param_1 + 0x794c45))) {
          uVar10 = *(uint *)(param_2 + 0x10);
          if (3 < uVar12) {
            uVar12 = 4;
          }
          uVar11 = *(uint *)(((uint)&local_88 & 0xffffe000) + 8);
          if (!CARRY4(uVar10,uVar12) && uVar10 + uVar12 <= uVar11) {
            uVar11 = 0;
          }
          if (uVar11 == 0) {
            uVar12 = __copy_from_user(&local_4c,uVar10,uVar12);
          }
          else {
            __memzero(&local_4c,uVar12);
          }
          *(char *)(param_1 + 0x794c44) = (char)(undefined2)local_4c;
          *(char *)(param_1 + 0x794c45) = (char)((ushort)(undefined2)local_4c >> 8);
          uVar7 = HcGetBandByWdev(param_4);
          uVar7 = hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),uVar7);
          hc_set_ChCtrlChListStat(uVar7,0);
          BuildChannelList(param_1,param_4);
          RTMPSetPhyMode(param_1,param_4,*(undefined2 *)(param_4 + 0x18));
          if (2 < DebugLevel) {
            printk("Set::RT_OID_802_11_COUNTRY_REGION (A:%d  B/G:%d)\n",
                   *(undefined1 *)(param_1 + 0x794c45),*(undefined1 *)(param_1 + 0x794c44));
            return uVar12;
          }
          return uVar12;
        }
        return 0;
      }
      if (0x507 < param_3) {
        if (param_3 != 0x50a) {
          if (0x50a < param_3) {
            if (param_3 != 0x50b) {
              if (param_3 != 0x50c) {
                return 0xffffffa1;
              }
LAB_0005b0c4:
              if (*(short *)(param_2 + 0x14) != 4) {
                return 0xffffffea;
              }
              uVar10 = *(uint *)(param_2 + 0x10);
              uVar13 = *(uint *)(((uint)&local_88 & 0xffffe000) + 8);
              uVar11 = uVar10 + 4;
              uVar12 = uVar11;
              if (uVar10 < 0xfffffffc) {
                uVar12 = uVar11 - (uVar13 + 1);
              }
              if (uVar10 < 0xfffffffc && uVar11 <= uVar13) {
                uVar13 = 0;
              }
              if (uVar13 == 0) {
                uVar12 = __copy_from_user(&local_4c,uVar10,4);
              }
              else {
                __memzero(&local_4c,4,uVar12);
                uVar12 = 4;
              }
              if (local_4c < &DAT_0000000c) {
                *(char *)(param_1 + 0x794c48) = (char)local_4c;
                uVar7 = HcGetBandByWdev(param_4);
                uVar7 = hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),uVar7);
                hc_set_ChCtrlChListStat(uVar7,0);
                BuildChannelList(param_1,param_4);
                RTMPSetPhyMode(param_1,param_4,(uint)local_4c & 0xffff);
              }
              if (2 < DebugLevel) {
                printk("Set::RT_OID_802_11_PHY_MODE (=%d)\n",local_4c);
                return uVar12;
              }
              return uVar12;
            }
LAB_0005b6c0:
            if (*(short *)(param_2 + 0x14) != 1) {
              return 0xffffffea;
            }
            iVar6 = *(int *)(param_2 + 0x10);
            uVar11 = *(uint *)(((uint)&local_88 & 0xffffe000) + 8);
            uVar10 = iVar6 + 1;
            uVar12 = uVar10;
            if (iVar6 != -1) {
              uVar12 = uVar10 - (uVar11 + 1);
            }
            if (iVar6 != -1 && uVar10 <= uVar11) {
              uVar11 = 0;
            }
            if (uVar11 == 0) {
              uVar12 = __copy_from_user(&local_4c,iVar6,1);
            }
            else {
              __memzero(&local_4c,1,uVar12);
              uVar12 = 1;
            }
            if (2 < DebugLevel) {
              printk("Set::RT_OID_802_11_RADIO (=%d)\n",(uint)local_4c & 0xff);
            }
            uVar10 = (uint)local_4c & 0xff;
            if (*(byte *)(iVar4 + 0x213138) == uVar10) {
              return uVar12;
            }
            bVar18 = *(char *)(iVar4 + 0x213139) != '\0';
            *(char *)(iVar4 + 0x213138) = (char)local_4c;
            if ((bool)*(char *)(iVar4 + 0x21313a) == (bVar18 && uVar10 != 0)) {
              return uVar12;
            }
            if (!bVar18 || uVar10 == 0) {
              *(undefined1 *)(iVar4 + 0x21313a) = 0;
              MlmeRestartStateMachine(param_1,iVar4);
              MlmeRadioOff(param_1,param_4);
              *(undefined4 *)(param_1 + 0xa39fa4) = 3;
              return uVar12;
            }
            *(undefined1 *)(iVar4 + 0x21313a) = 1;
            MlmeRadioOn(param_1,param_4);
            *(undefined4 *)(param_1 + 0xa39fa4) = 0xffffffff;
            return uVar12;
          }
          if (param_3 != 0x508) {
            if (param_3 != 0x509) {
              return 0xffffffa1;
            }
LAB_0005ab14:
            if (*(short *)(param_2 + 0x14) != 0x24) {
              return 0xffffffea;
            }
            uVar10 = *(uint *)(param_2 + 0x10);
            local_50 = (void *)0x0;
            uVar13 = *(uint *)(((uint)&local_88 & 0xffffe000) + 8);
            uVar11 = uVar10 + 0x24;
            uVar12 = uVar11;
            if (uVar10 < 0xffffffdc) {
              uVar12 = uVar11 - (uVar13 + 1);
            }
            if (uVar10 < 0xffffffdc && uVar11 <= uVar13) {
              uVar13 = 0;
            }
            if (uVar13 == 0) {
              uVar12 = __copy_from_user(&local_4c,uVar10,0x24);
            }
            else {
              __memzero(&local_4c,0x24,uVar12);
              uVar12 = 0x24;
            }
            if (2 < DebugLevel) {
              printk("Set::OID_802_11_SSID (Len=%d,Ssid=%s)\n",local_4c,&local_48);
            }
            if ((char *)0x20 < local_4c) {
              return 0xffffffea;
            }
            if (local_4c == (int *)0x0) {
              Set_SSID_Proc(param_1,&_LC93);
              return uVar12;
            }
            os_alloc_mem(param_1,&local_50,0x21);
            if (local_50 == (void *)0x0) {
              return 0xfffffff4;
            }
            __memzero(local_50,0x21);
            memmove(local_50,&local_48,(size_t)local_4c);
            *(undefined1 *)((int)local_50 + 0x20) = 0;
            Set_SSID_Proc(param_1,local_50);
            os_free_mem(local_50);
            return uVar12;
          }
LAB_0005ba28:
          RTMP_GetCurrentSystemTick(&local_4c);
          if (DebugLevel < 3) {
            if ("hif_set_WPDMA"[param_1 + 0xc] == '\x01') {
              return 0;
            }
          }
          else {
            printk("Set::OID_802_11_BSSID_LIST_SCAN, TxCnt = %d\n",
                   *(undefined4 *)(param_1 + 0xa39e80));
            if ("hif_set_WPDMA"[param_1 + 0xc] == '\x01') {
              if (DebugLevel < 3) {
                return 0;
              }
              printk("!!! Driver is in Monitor Mode now !!!\n");
              return 0;
            }
          }
          iVar6 = IsHcRadioCurStatOffByWdev(param_4);
          if (iVar6 != 0) {
            return 0;
          }
          if (100 < *(uint *)(param_1 + 0xa39e80)) {
            if (DebugLevel < 3) {
              return 0;
            }
            printk("!!! Link UP, ignore this set::OID_802_11_BSSID_LIST_SCAN\n");
            return 0;
          }
          if ((((*(uint *)(iVar4 + 0x212464) & 0x80) != 0) &&
              ((*(uint *)(param_4 + 0x2c) & 0x12cf8) != 0)) &&
             (*(char *)(param_4 + 0x888) == '\x02')) {
            if (DebugLevel < 3) {
              return 0;
            }
            printk("!!! Link UP, Port Not Secured! ignore this set::OID_802_11_BSSID_LIST_SCAN\n");
            return 0;
          }
          if ((*(int *)(iVar4 + 0x12e4) != 0) && (4 < *(int *)(iVar4 + 0x12f4))) {
            if (DebugLevel < 3) {
              return 0;
            }
            printk("!!! WPS processing now! ignore this set::OID_802_11_BSSID_LIST_SCAN\n");
            return 0;
          }
          StaSiteSurvey(param_1,0,0,iVar4);
          return 0;
        }
LAB_0005b9a0:
        if (*(short *)(param_2 + 0x14) != 6) {
          return 0xffffffea;
        }
        uVar12 = *(uint *)(((uint)&local_88 & 0xffffe000) + 8);
        if (*(uint *)(param_2 + 0x10) < 0xfffffffa && *(uint *)(param_2 + 0x10) + 6 <= uVar12) {
          uVar12 = 0;
        }
        if (uVar12 == 0) {
          __copy_from_user(&local_4c);
        }
        else {
          __memzero(&local_4c,6);
        }
        BN_mod_lshift1[iVar4] = (code)0x0;
        *(undefined1 *)(iVar4 + 0x4160) = 0x20;
        cntl_connect_request(param_4,1,6,&local_4c);
        if (DebugLevel < 3) {
          return 0;
        }
        local_88 = (char *)((uint)local_4c >> 0x18);
        local_84 = (char *)(local_48 & 0xff);
        local_80 = (int *)(local_48 >> 8 & 0xff);
        printk("Set::OID_802_11_BSSID %02x:%02x:%02x:%02x:%02x:%02x\n",(uint)local_4c & 0xff,
               local_4c._1_1_,local_4c._2_1_);
        return 0;
      }
      if (param_3 != 0x112) {
        if (param_3 < 0x113) {
          if (param_3 != 0x104) {
            return 0xffffffa1;
          }
LAB_0005b390:
          if (*(short *)(param_2 + 0x14) != 4) {
            return 0xffffffea;
          }
          uVar10 = *(uint *)(param_2 + 0x10);
          uVar13 = *(uint *)(((uint)&local_88 & 0xffffe000) + 8);
          uVar11 = uVar10 + 4;
          uVar12 = uVar11;
          if (uVar10 < 0xfffffffc) {
            uVar12 = uVar11 - (uVar13 + 1);
          }
          if (uVar10 < 0xfffffffc && uVar11 <= uVar13) {
            uVar13 = 0;
          }
          if (uVar13 == 0) {
            uVar12 = __copy_from_user(&local_4c,uVar10,4);
          }
          else {
            __memzero(&local_4c,4,uVar12);
            uVar12 = 4;
          }
          if (local_4c == (int *)0x1) {
            uVar7 = HcGetBandByWdev(param_4);
            uVar8 = hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),uVar7);
            hc_set_ChCtrlChListStat(uVar8,0);
            BuildChannelList(param_1,param_4);
            if (2 < DebugLevel) {
              printk("[RTMPSetInformation][BandIdx=%d] Ndis802_11DS\n",uVar7);
            }
            RTMPSetPhyMode(param_1,param_4,2);
          }
          else if (local_4c == (int *)0x3) {
            uVar7 = HcGetBandByWdev(param_4);
            uVar8 = hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),uVar7);
            hc_set_ChCtrlChListStat(uVar8,0);
            BuildChannelList(param_1,param_4);
            if (2 < DebugLevel) {
              printk("[RTMPSetInformation][BandIdx=%d] Ndis802_11OFDM24\n",uVar7);
            }
            RTMPSetPhyMode(param_1,param_4,6);
          }
          else if (local_4c == (int *)0x2) {
            uVar7 = HcGetBandByWdev(param_4);
            uVar8 = hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),uVar7);
            hc_set_ChCtrlChListStat(uVar8,0);
            BuildChannelList(param_1,param_4);
            if (2 < DebugLevel) {
              printk("[RTMPSetInformation][BandIdx=%d] Ndis802_11OFDM5\n",uVar7);
            }
            RTMPSetPhyMode(param_1,param_4,1);
          }
          else {
            uVar12 = 0xffffffea;
          }
          if (2 < DebugLevel) {
            printk("Set::OID_802_11_NETWORK_TYPE_IN_USE (=%d)\n",local_4c);
            return uVar12;
          }
          return uVar12;
        }
        if (param_3 != 0x113) {
          if (param_3 != 0x114) {
            return 0xffffffa1;
          }
          *(undefined1 *)(param_1 + 0x795128) = 1;
          BN_mod_lshift1[iVar4] = (code)0x1;
LAB_0005af30:
          if (*(char *)(iVar4 + 0x3c10) == '\0') {
            uVar7 = HcGetBandByWdev(iVar4);
            RTMPSetLED(param_1,0xc,uVar7);
            RTMPCancelTimer(iVar4 + 0x3c14,&local_4c);
          }
          if ((*(uint *)(iVar4 + 0x212464) & 1) == 0) {
            return 0;
          }
          local_84 = (char *)0xec1;
          local_88 = "RTMPSetInformation";
          __cntl_disconnect_request(param_4,1,iVar4 + 0x212428,8);
          return 0;
        }
LAB_0005c1a0:
        if (*(short *)(param_2 + 0x14) != 4) {
          return 0xffffffea;
        }
        uVar12 = **(uint **)(param_2 + 0x10);
        if ((int)uVar12 < 0) {
          return 0xffffffea;
        }
        if (3 < (uVar12 & 0xfffffff)) {
          return 0xffffffea;
        }
        iVar4 = param_1 + (uVar12 & 0xfffffff) * 0x49;
        *(undefined1 *)(iVar4 + 0xa377a5) = 0;
        *(undefined1 *)(iVar4 + 0xa377a4) = 0;
        AsicRemoveSharedKeyEntry(param_1,0,uVar12 & 0xff);
        return 0;
      }
LAB_0005bac8:
      os_alloc_mem(param_1,&local_64,*(undefined2 *)(param_2 + 0x14));
      if (local_64 == 0) {
        if (DebugLevel < 3) {
          return 0xfffffff4;
        }
        printk("Set::OID_802_11_ADD_WEP, Failed!!\n");
        return 0xfffffff4;
      }
      uVar12 = (uint)*(ushort *)(param_2 + 0x14);
      uVar10 = *(uint *)(((uint)&local_88 & 0xffffe000) + 8);
      if (!CARRY4(*(uint *)(param_2 + 0x10),uVar12) && *(uint *)(param_2 + 0x10) + uVar12 <= uVar10)
      {
        uVar10 = 0;
      }
      if (uVar10 == 0) {
        iVar4 = __copy_from_user(local_64);
        if (iVar4 != 0) goto LAB_0005cb20;
      }
      else if (uVar12 != 0) {
        __memzero(local_64,uVar12);
LAB_0005cb20:
        if (DebugLevel < 3) {
          uVar12 = 0xffffffea;
        }
        else {
          uVar12 = 0xffffffea;
          printk("Set::OID_802_11_ADD_WEP, Failed (length mismatch)!!\n");
        }
        goto LAB_0005bb38;
      }
      uVar10 = *(uint *)(local_64 + 4);
      uVar11 = uVar10 & 0xfffffff;
      if (uVar11 < 4) {
        pvVar17 = (void *)(param_4 + uVar11 * 0x51 + 0x30);
        __memzero(pvVar17,0x49);
        iVar4 = local_64;
        *(char *)(param_4 + uVar11 * 0x51 + 0x80) = (char)*(undefined4 *)(local_64 + 8);
        memmove(pvVar17,(void *)(local_64 + 0xc),*(size_t *)(local_64 + 8));
        if (*(int *)(iVar4 + 8) == 5) {
          uVar9 = 1;
          uVar12 = 0;
        }
        else if (*(int *)(iVar4 + 8) == 0xd) {
          uVar9 = 2;
          uVar12 = 0;
        }
        else if (DebugLevel < 3) {
          uVar9 = 0;
          uVar12 = 0xffffffea;
        }
        else {
          uVar12 = 0xffffffea;
          printk(
                "Set::OID_802_11_ADD_WEP, only support CIPHER_WEP64(len:5) & CIPHER_WEP128(len:13)!!\n"
                );
          uVar9 = 0;
        }
        *(undefined1 *)(param_1 + uVar11 * 0x49 + 0xa377a4) = uVar9;
        if (*(int *)(local_64 + 4) < 0) {
          *(char *)(param_4 + 0x178) = (char)uVar11;
        }
        AsicAddSharedKeyEntry(param_1,0,uVar10 & 0xff,param_1 + uVar11 * 0x49 + 0xa37764);
        if (2 < DebugLevel) {
          puVar15 = &_LC93;
          if (*(char *)(param_4 + 0x888) != '\x01') {
            puVar15 = &_LC94;
          }
          printk("Set::OID_802_11_ADD_WEP (id=0x%x, Len=%d-byte), Port %s Secured\n",
                 *(undefined4 *)(local_64 + 4),*(undefined4 *)(local_64 + 8),puVar15);
        }
      }
      else if (DebugLevel < 3) {
        uVar12 = 0xffffffea;
      }
      else {
        uVar12 = 0xffffffea;
        printk("Set::OID_802_11_ADD_WEP, Failed (KeyIdx must be smaller than 4)!!\n");
      }
LAB_0005bb38:
      os_free_mem(local_64);
      return uVar12;
    }
  }
  else {
    uVar12 = param_3 & 0x7fff;
    printk("-->RTMPSetInformation(),\t0x%08x\n",uVar12);
    iVar6 = DebugLevel;
    if (uVar12 != 0x519) {
      if (uVar12 < 0x51a) {
        if (uVar12 == 0x50d) goto LAB_0005bbbc;
        if (0x50d < uVar12) {
          if (uVar12 == 0x512) goto LAB_0005c10c;
          if (uVar12 < 0x513) {
            if (uVar12 == 0x50f) goto LAB_0005be90;
            if (uVar12 < 0x50f) goto LAB_0005b410;
            if (uVar12 == 0x510) goto LAB_0005bffc;
            if (uVar12 == 0x511) goto LAB_0005b018;
          }
          else {
            if (uVar12 == 0x515) goto LAB_0005b5a0;
            if (uVar12 < 0x516) {
              if (uVar12 == 0x513) goto LAB_0005c2ac;
              if (uVar12 == 0x514) goto LAB_0005b244;
            }
            else {
              if (uVar12 == 0x516) goto LAB_0005b914;
              if (uVar12 == 0x518) goto LAB_0005acf0;
            }
          }
          goto LAB_0005d494;
        }
        if (uVar12 == 0x507) goto LAB_0005bc64;
        if (0x507 < uVar12) {
          if (uVar12 == 0x50a) goto LAB_0005b9a0;
          if (uVar12 < 0x50b) {
            if (uVar12 == 0x508) goto LAB_0005ba28;
            if (uVar12 == 0x509) goto LAB_0005ab14;
          }
          else {
            if (uVar12 == 0x50b) goto LAB_0005b6c0;
            if (uVar12 == 0x50c) goto LAB_0005b0c4;
          }
LAB_0005d494:
          if (DebugLevel < 3) {
            return 0xffffffa1;
          }
          printk("Set::unknown IOCTL\'s subcmd = 0x%08x\n",param_3);
          return 0xffffffa1;
        }
        if (uVar12 != 0x112) {
          if (uVar12 < 0x113) {
            if (uVar12 == 0x104) goto LAB_0005b390;
          }
          else {
            if (uVar12 == 0x113) {
              if (2 < DebugLevel) {
                printk("Set::OID_802_11_REMOVE_WEP\n");
              }
              goto LAB_0005c1a0;
            }
            if (uVar12 == 0x114) {
              *(undefined1 *)(param_1 + 0x795128) = 1;
              BN_mod_lshift1[iVar4] = (code)0x1;
              if (2 < iVar6) {
                printk("Set::OID_802_11_DISASSOCIATE\n");
              }
              goto LAB_0005af30;
            }
          }
          goto LAB_0005d494;
        }
        goto LAB_0005bac8;
      }
      if (uVar12 == 0x649) goto LAB_0005bb44;
      if (0x649 < uVar12) {
        if (uVar12 == 0x745) goto LAB_0005c0a0;
        if (uVar12 < 0x746) {
          if (uVar12 == 0x740) goto LAB_0005be10;
          if (uVar12 < 0x741) {
            if (uVar12 == 0x739) goto LAB_0005b304;
          }
          else {
            if (uVar12 == 0x741) goto LAB_0005ba60;
            if (uVar12 == 0x743) goto LAB_0005af7c;
          }
          goto LAB_0005d494;
        }
        if (uVar12 == 0x748) goto LAB_0005b5d8;
        if (uVar12 < 0x749) {
          if (uVar12 == 0x746) goto LAB_0005b94c;
          if (uVar12 != 0x747) goto LAB_0005d494;
          goto LAB_0005b1c4;
        }
        if (uVar12 == 0x749) goto LAB_0005bf18;
        if (uVar12 != 0x755) goto LAB_0005d494;
        local_4c = (int *)0x0;
        if (2 < DebugLevel) {
          printk("WSC::RT_OID_WSC_EAPMSG, wrq->u.data.length=%d!\n",*(undefined2 *)(param_2 + 0x14))
          ;
        }
        goto LAB_0005adac;
      }
      if (uVar12 == 0x637) goto LAB_0005c204;
      if (uVar12 < 0x638) {
        if (uVar12 == 0x521) goto LAB_0005bd4c;
        if (uVar12 < 0x522) {
          if (uVar12 == 0x520) goto LAB_0005b27c;
        }
        else {
          if (uVar12 == 0x614) goto LAB_0005b85c;
          if (uVar12 == 0x634) goto LAB_0005aea0;
        }
        goto LAB_0005d494;
      }
      if (uVar12 == 0x641) goto LAB_0005bf90;
      if (uVar12 < 0x642) {
        if (uVar12 == 0x639) goto LAB_0005b778;
        if (uVar12 == 0x63f) goto LAB_0005b148;
        goto LAB_0005d494;
      }
      if (uVar12 == 0x643) {
        if (2 < DebugLevel) {
          printk(" Set :: RT_OID_802_11_ADD_IMME_BA\n");
        }
        goto LAB_0005b4c8;
      }
      if (uVar12 != 0x644) goto LAB_0005d494;
      if (2 < DebugLevel) {
        printk("Set :: RT_OID_802_11_TEAR_IMME_BA\n");
      }
LAB_0005abdc:
      if (*(short *)(param_2 + 0x14) != 0xe) {
        return 0xffffffea;
      }
      os_alloc_mem(param_1,&local_4c);
      if (local_4c == (int *)0x0) {
        if (DebugLevel < 3) {
          return 1;
        }
        printk("Set :: RT_OID_802_11_TEAR_IMME_BA: can\'t allocate enough memory\n");
        return 1;
      }
      uVar10 = *(uint *)(param_2 + 0x10);
      uVar12 = (uint)*(ushort *)(param_2 + 0x14);
      uVar11 = *(uint *)(((uint)&local_88 & 0xffffe000) + 8);
      if (!CARRY4(uVar10,uVar12) && uVar10 + uVar12 <= uVar11) {
        uVar11 = 0;
      }
      if (uVar11 == 0) {
        uVar12 = __copy_from_user(local_4c,uVar10,uVar12);
      }
      else if (uVar12 != 0) {
        __memzero(local_4c,uVar12);
      }
      if (2 < DebugLevel) {
        printk("Set :: RT_OID_802_11_TEAR_IMME_BA(TID=%d, bAllTid=%d)\n",
               *(char *)((int)local_4c + 7),*(char *)((int)local_4c + 0xc));
      }
      if ((*(char *)((int)local_4c + 0xc) == '\0') && (7 < *(byte *)((int)local_4c + 7))) {
        os_free_mem(local_4c);
        return 2;
      }
      if (*(char *)local_4c == '\0') {
        iVar4 = MacTableLookup2(param_1,(char *)((int)local_4c + 1),param_4);
        if (DebugLevel < 3) {
          if (iVar4 == 0) goto LAB_0005acac;
        }
        else {
          printk(" pBA->IsRecipient == FALSE\n");
          if (iVar4 == 0) goto LAB_0005d118;
          if (2 < DebugLevel) {
            printk(" pBA->pEntry\n");
          }
        }
        ba_ori_session_tear_down
                  (param_1,*(undefined2 *)(iVar4 + 0xe0),*(char *)((int)local_4c + 7),0);
      }
      else {
        iVar4 = MacTableLookup2(param_1,(char *)((int)local_4c + 1),param_4);
        if (iVar4 != 0) {
          ba_rec_session_tear_down
                    (param_1,*(undefined2 *)(iVar4 + 0xe0),*(char *)((int)local_4c + 7),1);
          goto LAB_0005acac;
        }
LAB_0005d118:
        if (2 < DebugLevel) {
          printk("Set :: Not found pEntry\n");
        }
      }
LAB_0005acac:
      os_free_mem(local_4c);
      return uVar12;
    }
  }
  os_alloc_mem(param_1,&local_60,*(undefined2 *)(param_2 + 0x14));
  if (local_60 == (uint *)0x0) {
    return 0xfffffff4;
  }
  uVar11 = *(uint *)(param_2 + 0x10);
  uVar12 = (uint)*(ushort *)(param_2 + 0x14);
  uVar10 = *(uint *)(((uint)&local_88 & 0xffffe000) + 8);
  if (!CARRY4(uVar11,uVar12) && uVar11 + uVar12 <= uVar10) {
    uVar10 = 0;
  }
  if (uVar10 == 0) {
    uVar12 = __copy_from_user(local_60,uVar11,uVar12);
    uVar10 = (uint)*(ushort *)(param_2 + 0x14);
  }
  else if (uVar12 == 0) {
    uVar10 = 0;
  }
  else {
    __memzero(local_60,uVar12);
    uVar10 = (uint)*(ushort *)(param_2 + 0x14);
  }
  iVar4 = DebugLevel;
  if (*local_60 == uVar10) {
    if ((*(uint *)(param_4 + 0x2c) & 0x12cf8) != 0) {
      RTMPWPARemoveKeyProc(param_1,local_60);
      if (2 < DebugLevel) {
        printk("Set::OID_802_11_REMOVE_KEY, Remove WPA Key!!\n");
      }
      goto LAB_0005b6b4;
    }
    if ((int)local_60[1] < 0) {
      if (2 < DebugLevel) {
        uVar12 = 0xffffffea;
        printk(
              "Set::OID_802_11_REMOVE_KEY, Failed!!(Should never set default bit when remove key)\n"
              );
        goto LAB_0005b6b4;
      }
    }
    else {
      uVar10 = local_60[1] & 0xfffffff;
      if (uVar10 < 4) {
        *(undefined1 *)(param_4 + uVar10 * 0x51 + 0x80) = 0;
        if (2 < iVar4) {
          printk("Set::OID_802_11_REMOVE_KEY (id=0x%x, Len=%d-byte)\n",local_60[1],*local_60);
        }
        goto LAB_0005b6b4;
      }
      if (2 < DebugLevel) {
        uVar12 = 0xffffffea;
        printk("Set::OID_802_11_REMOVE_KEY, Failed!!(KeyId[%d] out of range)\n");
        goto LAB_0005b6b4;
      }
    }
  }
  else if (2 < DebugLevel) {
    uVar12 = 0xffffffea;
    printk("Set::OID_802_11_REMOVE_KEY, Failed!!\n");
    goto LAB_0005b6b4;
  }
  uVar12 = 0xffffffea;
LAB_0005b6b4:
  os_free_mem(local_60);
  return uVar12;
}

