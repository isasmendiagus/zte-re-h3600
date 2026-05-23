// module: mt7915.ko
// function: BuildChannelList @ 0x10213c
// size: 3884 bytes
//

/* WARNING: Removing unreachable block (ram,0x00102528) */
/* WARNING: Removing unreachable block (ram,0x00102f64) */

void BuildChannelList(int param_1,int param_2)

{
  byte *pbVar1;
  ushort uVar2;
  byte bVar3;
  undefined1 uVar4;
  int iVar5;
  char *pcVar6;
  int iVar7;
  undefined4 uVar8;
  int iVar9;
  char *pcVar10;
  uint uVar11;
  char cVar12;
  ushort uVar13;
  uint uVar14;
  uint uVar15;
  undefined4 uVar16;
  char *pcVar17;
  uint uVar18;
  uint *puVar19;
  uint uVar20;
  char cVar21;
  uint local_54;
  uint local_50;
  int local_40;
  undefined4 local_3c;
  int local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  
  iVar5 = HcGetBandByWdev(param_2);
  uVar2 = *(ushort *)(param_2 + 0x18);
  pcVar6 = (char *)hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),iVar5);
  iVar7 = hc_check_ChCtrlChListStat(pcVar6,1);
  if (iVar7 != 0) {
    if (DebugLevel < 3) {
      return;
    }
    printk("%s(): BandIdx %d, channel list is already DONE\n","BuildChannelList",iVar5);
    return;
  }
  os_zero_mem(pcVar6,0x49c);
  pcVar6[0x49c] = '\0';
  uVar13 = uVar2 & 0x4e;
  if ((uVar2 & 0x4e) == 0) {
    if ((uVar2 & 0xb1) != 0) {
      if (2 < DebugLevel) {
        printk("[BuildChannelListFor5G] \n");
      }
      bVar3 = *(byte *)(param_1 + 0x794c45) & 0x7f;
      if (Country_Region_ChDesc_5GHZ[0] == bVar3) {
        uVar11 = 0;
      }
      else {
        uVar11 = 0;
        do {
          uVar11 = uVar11 + 1 & 0xff;
          if (0x22 < uVar11) {
            if (DebugLevel < 0) goto LAB_00102418;
            printk("CountryRegionABand=%d not support",*(undefined1 *)(param_1 + 0x794c45));
            goto LAB_00102354;
          }
        } while (Country_Region_ChDesc_5GHZ[uVar11 * 8] != bVar3);
      }
      uVar16 = *(undefined4 *)(Country_Region_ChDesc_5GHZ + uVar11 * 8 + 4);
      uVar11 = TotalChNum(uVar16);
      *(undefined4 *)(param_1 + 0x794c40) = uVar16;
      uVar11 = uVar11 & 0xff;
      if (uVar11 != 0) {
        local_38 = 0x403c3834;
        uStack_34 = 0x706c6864;
        uStack_30 = 0x807c7874;
        uStack_2c = 0x908c8884;
        os_alloc_mem(0,&local_40,uVar11);
        if (local_40 == 0) {
          if (-1 < DebugLevel) {
            pcVar10 = "BuildChannelListFor5G";
            goto LAB_00102d68;
          }
          goto LAB_00102418;
        }
        os_alloc_mem(0,&local_3c,uVar11);
        if (local_3c == 0) {
          if (-1 < DebugLevel) {
            printk("%s:Allocate memory for ChannelListFlag failed\n","BuildChannelListFor5G");
          }
          os_free_mem(local_40);
        }
        else {
          uVar15 = 0;
          uVar18 = 0;
          do {
            iVar7 = local_40;
            uVar4 = GetChannel_5GHZ(uVar16,uVar18);
            iVar9 = local_3c;
            *(undefined1 *)(iVar7 + uVar15) = uVar4;
            uVar4 = GetChannelFlag(uVar16,uVar18);
            *(undefined1 *)(iVar9 + uVar15) = uVar4;
            uVar15 = uVar15 + 1;
            uVar18 = uVar15 & 0xff;
          } while (uVar18 < uVar11);
          local_54 = 0;
          uVar18 = 0;
          uVar15 = 0;
          do {
            if ((*(char *)(param_1 + 0x795074) == '\0') ||
               ((*(char *)(param_1 + 0x795074) == '\x01' &&
                (*(char *)(param_1 + 0x795075) != '\x01')))) {
              iVar7 = MTChGrpValid(pcVar6);
              if (iVar7 == 0) {
LAB_00102814:
                iVar7 = local_40;
                uVar4 = GetChannel_5GHZ(uVar16,uVar18);
                iVar9 = local_3c;
                *(undefined1 *)(iVar7 + local_54) = uVar4;
                uVar4 = GetChannelFlag(uVar16,uVar18);
                *(undefined1 *)(iVar9 + local_54) = uVar4;
                local_54 = local_54 + 1 & 0xff;
              }
              else {
                uVar8 = GetChannel_5GHZ(uVar16,uVar18);
                iVar7 = MTChGrpChannelChk(pcVar6,uVar8);
                if (iVar7 != 0) goto LAB_00102814;
              }
              if (2 < DebugLevel) {
                printk("[BuildChannelListFor5G] - RDDurRegion != FCC - q=%d!\n",local_54);
              }
            }
            else if (*(short *)(param_1 + 0x795074) == 0x101) {
              if (*(char *)(param_1 + 0xa37730) == '\x01') {
                iVar7 = MTChGrpValid(pcVar6);
joined_r0x00102e9c:
                if (iVar7 != 0) goto LAB_00102aa8;
LAB_00102ac8:
                iVar7 = local_40;
                uVar4 = GetChannel_5GHZ(uVar16,uVar18);
                iVar9 = local_3c;
                *(undefined1 *)(iVar7 + local_54) = uVar4;
                uVar4 = GetChannelFlag(uVar16,uVar18);
                *(undefined1 *)(iVar9 + local_54) = uVar4;
                local_54 = local_54 + 1 & 0xff;
              }
              else {
                if (*(char *)(param_1 + 0xa37730) != '\0') goto LAB_00102728;
                uVar20 = GetChannel_5GHZ(uVar16,uVar18);
                if ((uVar20 < 100) || (uVar20 = GetChannel_5GHZ(uVar16,uVar18), 0x8c < uVar20)) {
                  iVar7 = MTChGrpValid(pcVar6);
                  goto joined_r0x00102e9c;
                }
              }
            }
            else {
LAB_00102728:
              iVar7 = MTChGrpValid(pcVar6);
              if (iVar7 != 0) {
LAB_00102aa8:
                uVar8 = GetChannel_5GHZ(uVar16,uVar18);
                iVar7 = MTChGrpChannelChk(pcVar6,uVar8);
                if (iVar7 != 0) goto LAB_00102ac8;
              }
            }
            uVar15 = uVar15 + 1;
            uVar18 = uVar15 & 0xff;
          } while (uVar18 < uVar11);
          if (local_54 == 0) {
            iVar9 = MTChGrpValid(pcVar6);
            iVar7 = local_40;
            if (iVar9 != 0) {
              if (-1 < DebugLevel) {
                printk("[%s] Build channel list based on channel group to avoid NULL channel list!\n"
                       ,"BuildChannelListFor5G");
              }
              if (pcVar6[0x4d9] != '\0') {
                uVar11 = 0;
                do {
                  *(char *)(local_40 + uVar11) = pcVar6[uVar11 + 0x49e];
                  *(undefined1 *)(local_3c + uVar11) = 0;
                  uVar11 = uVar11 + 1 & 0xff;
                  local_54 = (uint)(byte)pcVar6[0x4d9];
                } while (uVar11 < local_54);
                if (local_54 != 0) goto LAB_00102b10;
              }
              local_54 = 0;
              iVar7 = local_40;
            }
          }
          else {
LAB_00102b10:
            uVar15 = 0;
            uVar11 = 0;
            pcVar10 = pcVar6;
            iVar7 = local_40;
            do {
              uVar18 = 0;
              pcVar17 = "get_channel_by_reference" + param_1 + 0xc;
              do {
                cVar12 = *pcVar17;
                uVar20 = uVar18 & 0xff;
                cVar21 = *(char *)(iVar7 + uVar15);
                uVar18 = uVar18 + 1;
                pcVar17 = pcVar17 + 0x14;
                if (cVar12 == cVar21) {
                  hc_set_ChCtrl(pcVar6,param_1,uVar11,uVar20);
                  cVar21 = *(char *)(local_40 + uVar15);
                }
                iVar7 = local_40;
                *pcVar10 = cVar21;
                *(uint *)(pcVar10 + 0x10) = (uint)*(byte *)(local_3c + uVar15);
              } while (uVar18 != 0x3b);
              pcVar17 = (char *)((int)&local_3c + 3);
              do {
                pcVar17 = pcVar17 + 1;
                if (*(char *)(local_40 + uVar15) == *pcVar17) {
                  pcVar10[5] = '\x01';
                }
              } while (pcVar17 != (char *)((int)&uStack_2c + 3));
              iVar9 = strncmp((char *)(param_1 + 0x794c31),"CN",2);
              uVar15 = uVar15 + 1;
              uVar11 = uVar15 & 0xff;
              if (iVar9 == 0) {
                cVar12 = "auth_fsm_peer_auth_rsp_at_seq2_action"[param_1];
              }
              else {
                cVar12 = '\x14';
              }
              pcVar10[4] = cVar12;
              pcVar10 = pcVar10 + 0x14;
            } while (uVar11 < local_54);
          }
          pcVar6[0x49c] = (char)local_54;
          os_free_mem(iVar7);
          os_free_mem(local_3c);
        }
      }
      goto LAB_00102354;
    }
    if ((uVar2 & 0x100) != 0) {
      if (2 < DebugLevel) {
        printk("%s()\n","build_ch_list_for_6G");
      }
      bVar3 = *(byte *)(param_1 + 0x794c45) & 0x7f;
      if (Country_Region_ChDesc_6GHZ[0] == bVar3) {
        uVar11 = 0;
      }
      else {
        uVar11 = 0;
        do {
          uVar11 = uVar11 + 1 & 0xff;
          if (8 < uVar11) {
            if (2 < DebugLevel) {
              printk("%s() ch_num %d\n","build_ch_list_for_6G",0);
            }
            if (DebugLevel < 0) goto LAB_00102418;
            printk("%s() CountryRegionABand=%d not support","build_ch_list_for_6G",
                   *(undefined1 *)(param_1 + 0x794c45));
            goto LAB_00102354;
          }
        } while (Country_Region_ChDesc_6GHZ[uVar11 * 8] != bVar3);
      }
      uVar16 = *(undefined4 *)(Country_Region_ChDesc_6GHZ + uVar11 * 8 + 4);
      uVar11 = TotalChNum(uVar16);
      iVar7 = DebugLevel;
      *(undefined4 *)(param_1 + 0x794c40) = uVar16;
      uVar15 = uVar11 & 0xff;
      if (2 < iVar7) {
        printk("%s() ch_num %d\n","build_ch_list_for_6G",uVar15);
      }
      if (uVar15 == 0) {
        if (-1 < DebugLevel) {
          printk("%s() ch_num=%d ch list is empty","build_ch_list_for_6G",0);
          goto LAB_00102354;
        }
      }
      else {
        os_alloc_mem(0,&local_3c,uVar15);
        if (local_3c != 0) {
          os_alloc_mem(0,&local_38,uVar15);
          if (local_38 == 0) {
            if (-1 < DebugLevel) {
              printk("%s:Allocate memory for ChannelListFlag failed\n","build_ch_list_for_6G");
            }
            goto LAB_00102e08;
          }
          uVar20 = 0;
          uVar18 = 0;
          do {
            iVar7 = local_3c;
            uVar4 = GetChannel_5GHZ(uVar16,uVar18);
            iVar9 = local_38;
            *(undefined1 *)(iVar7 + uVar20) = uVar4;
            uVar4 = GetChannelFlag(uVar16,uVar18);
            *(undefined1 *)(iVar9 + uVar20) = uVar4;
            if ((2 < DebugLevel) &&
               (printk("%s() ch_idx %d, ch_valid_idx %d!\n","build_ch_list_for_6G",uVar20,uVar20),
               2 < DebugLevel)) {
              printk("%s() ch %d, ch_flag %d!\n","build_ch_list_for_6G",
                     *(undefined1 *)(local_3c + uVar20),*(undefined1 *)(local_38 + uVar20));
            }
            uVar20 = uVar20 + 1;
            uVar18 = uVar20 & 0xff;
          } while (uVar18 < uVar15);
          iVar7 = 0;
          pcVar10 = pcVar6;
          do {
            *pcVar10 = *(char *)(local_3c + iVar7);
            pbVar1 = (byte *)(local_38 + iVar7);
            iVar7 = iVar7 + 1;
            *(uint *)(pcVar10 + 0x10) = (uint)*pbVar1;
            pcVar10 = pcVar10 + 0x14;
          } while (iVar7 != (uVar15 - 1 & 0xff) + 1);
          pcVar6[0x49c] = (char)uVar11;
          os_free_mem(local_3c);
          os_free_mem(local_38);
          goto LAB_00102354;
        }
        if (-1 < DebugLevel) {
          pcVar10 = "build_ch_list_for_6G";
          goto LAB_00102d68;
        }
      }
      goto LAB_00102418;
    }
    if (0 < DebugLevel) goto LAB_00102360;
    uVar11 = 0;
  }
  else {
    if (2 < DebugLevel) {
      printk("[BuildChannelListFor2G]\n");
    }
    bVar3 = *(byte *)(param_1 + 0x794c44) & 0x7f;
    if (Country_Region_ChDesc_2GHZ[0] == bVar3) {
      uVar11 = 0;
    }
    else {
      uVar11 = 0;
      do {
        uVar11 = uVar11 + 1 & 0xff;
        if (0xb < uVar11) {
          if (DebugLevel < 0) goto LAB_00102418;
          printk("CountryRegion=%d not support",*(undefined1 *)(param_1 + 0x794c44));
          goto LAB_00102354;
        }
      } while (Country_Region_ChDesc_2GHZ[uVar11 * 8] != bVar3);
    }
    uVar16 = *(undefined4 *)(Country_Region_ChDesc_2GHZ + uVar11 * 8 + 4);
    uVar11 = TotalChNum(uVar16);
    *(undefined4 *)(param_1 + 0x794c3c) = uVar16;
    uVar11 = uVar11 & 0xff;
    if (uVar11 != 0) {
      os_alloc_mem(0,&local_3c,uVar11);
      if (local_3c == 0) {
        if (DebugLevel < 0) goto LAB_00102418;
        pcVar10 = "BuildChannelListFor2G";
LAB_00102d68:
        printk("%s:Allocate memory for ChannelList failed\n",pcVar10);
      }
      else {
        os_alloc_mem(0,&local_38,uVar11);
        if (local_38 == 0) {
          if (-1 < DebugLevel) {
            printk("%s:Allocate memory for ChannelListFlag failed\n","BuildChannelListFor2G");
          }
LAB_00102e08:
          os_free_mem(local_3c);
        }
        else {
          uVar15 = 0;
          uVar18 = 0;
          do {
            iVar7 = local_3c;
            uVar4 = GetChannel_2GHZ(uVar16,uVar18);
            iVar9 = local_38;
            *(undefined1 *)(iVar7 + uVar15) = uVar4;
            uVar4 = GetChannelFlag(uVar16,uVar18);
            *(undefined1 *)(iVar9 + uVar15) = uVar4;
            uVar15 = uVar15 + 1;
            uVar18 = uVar15 & 0xff;
          } while (uVar18 < uVar11);
          uVar15 = uVar11 - 1 & 0xff;
          uVar18 = 0;
          puVar19 = (uint *)(pcVar6 + 0x10);
          do {
            uVar20 = 0;
            iVar7 = local_3c;
            pcVar10 = "get_channel_by_reference" + param_1 + 0xc;
            do {
              while( true ) {
                cVar12 = *pcVar10;
                uVar14 = uVar20 & 0xff;
                uVar20 = uVar20 + 1;
                pcVar10 = pcVar10 + 0x14;
                if (*(char *)(iVar7 + uVar18) != cVar12) break;
                hc_set_ChCtrl(pcVar6,param_1,uVar18 & 0xff,uVar14);
                iVar7 = local_3c;
                if (uVar20 == 0x3b) goto LAB_00102970;
              }
            } while (uVar20 != 0x3b);
LAB_00102970:
            cVar12 = *(char *)(iVar7 + uVar18);
            if ((cVar12 == '\x0e') &&
               ((iVar9 = strncmp((char *)(param_1 + 0x794c31),"JP",2), local_50 = uVar15, iVar9 != 0
                || (uVar2 != 2)))) break;
            *(char *)(puVar19 + -4) = cVar12;
            iVar7 = strncmp((char *)(param_1 + 0x794c31),"CN",2);
            if (iVar7 == 0) {
              cVar12 = "auth_fsm_peer_auth_rsp_at_seq2_action"[param_1];
            }
            else {
              cVar12 = '\x14';
            }
            *(char *)(puVar19 + -3) = cVar12;
            pbVar1 = (byte *)(local_38 + uVar18);
            uVar18 = uVar18 + 1;
            *puVar19 = (uint)*pbVar1;
            iVar7 = local_3c;
            puVar19 = puVar19 + 5;
            local_50 = uVar11;
          } while (uVar18 != uVar15 + 1);
          pcVar6[0x49c] = (char)local_50;
          os_free_mem(iVar7);
          os_free_mem(local_38);
        }
      }
    }
LAB_00102354:
    if (0 < DebugLevel) {
      uVar13 = (ushort)(byte)pcVar6[0x49c];
LAB_00102360:
      printk("%s() BandIdx = %d, PhyMode = %d, ChListNum = %d:\n","BuildChannelList",iVar5,uVar2,
             uVar13);
    }
LAB_00102418:
    uVar11 = 0;
    if (pcVar6[0x49c] != '\0') {
      uVar15 = 0;
      do {
        iVar7 = N_ChannelGroupCheck(param_1,pcVar6[uVar15 * 0x14],param_2);
        if (iVar7 != 0) {
          hc_set_ChCtrlFlags_CAP(pcVar6,0x40,uVar15);
        }
        iVar7 = vht80_channel_group(param_1,pcVar6[uVar15 * 0x14],param_2);
        if (iVar7 != 0) {
          hc_set_ChCtrlFlags_CAP(pcVar6,0x80,uVar15);
        }
        iVar7 = vht160_channel_group(param_1,pcVar6[uVar15 * 0x14],param_2);
        if (iVar7 != 0) {
          hc_set_ChCtrlFlags_CAP(pcVar6,0x100,uVar15);
        }
        uVar11 = (uint)(byte)pcVar6[0x49c];
        uVar15 = uVar15 + 1 & 0xff;
      } while (uVar15 < uVar11);
    }
    if ((uVar2 & 0x4e) != 0) {
      if (2 < DebugLevel) {
        printk("CountryCode(2.4G)=%d, RFIC=%d, support %d channels\n",
               *(undefined1 *)(param_1 + 0x794c44),
               "rtmp_read_dot11v_mbssid_cfg_from_file"[param_1 + 0x1e],uVar11);
      }
      goto LAB_00102210;
    }
  }
  if (((uVar2 & 0xb1) != 0) && (2 < DebugLevel)) {
    printk("CountryCode(5G)=%d, RFIC=%d, support %d channels\n",*(undefined1 *)(param_1 + 0x794c45),
           "rtmp_read_dot11v_mbssid_cfg_from_file"[param_1 + 0x1e],uVar11);
  }
LAB_00102210:
  *(undefined1 *)(param_1 + iVar5 + 0x7953e9) = 1;
  DfsBuildChannelList(param_1,param_2);
  hc_set_ChCtrlChListStat(pcVar6,1);
  if (2 < DebugLevel) {
    printk("%s() SupportedChannelList (ChCtrlStat = DONE):\n","BuildChannelList");
  }
  uVar11 = (uint)(byte)pcVar6[0x49c];
  if (uVar11 != 0) {
    uVar15 = 0;
    do {
      if (2 < DebugLevel) {
        printk("\tChannel # %d: Pwr0/1 = %d/%d, Flags = %x\n ",pcVar6[uVar15 * 0x14],
               (int)pcVar6[uVar15 * 0x14 + 2],(int)pcVar6[uVar15 * 0x14 + 3],
               *(undefined4 *)(pcVar6 + uVar15 * 0x14 + 0x10));
        uVar11 = (uint)(byte)pcVar6[0x49c];
      }
      uVar15 = uVar15 + 1 & 0xff;
    } while (uVar15 < uVar11);
  }
  return;
}

