// module: mt7915.ko
// function: AutoChSelBuildChannelListFor5G @ 0x23288
// size: 2888 bytes
//

void AutoChSelBuildChannelListFor5G(int param_1,undefined4 param_2)

{
  char cVar1;
  byte bVar2;
  bool bVar3;
  bool bVar4;
  undefined1 uVar5;
  undefined4 uVar6;
  byte *pbVar7;
  byte *pbVar8;
  uint uVar9;
  int iVar10;
  undefined4 uVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  byte *pbVar15;
  int iVar16;
  byte bVar17;
  uint uVar18;
  byte bVar19;
  char *pcVar20;
  int iVar21;
  int iVar22;
  int iVar23;
  int iVar24;
  byte *pbVar25;
  undefined1 *puVar26;
  uint uVar27;
  byte *pbVar28;
  int local_3c;
  int local_2c [2];
  
  uVar6 = wlan_config_get_ch_band(param_2);
  pbVar7 = (byte *)get_ch_array(2,uVar6);
  pbVar8 = (byte *)get_ch_array(3,uVar6);
  uVar9 = wlan_config_get_vht_bw(param_2);
  iVar10 = wlan_config_get_ht_bw(param_2);
  uVar11 = HcGetBandByWdev(param_2);
  iVar12 = hc_get_channel_ctrl(*(undefined4 *)(param_1 + 0xa797a0),uVar11);
  iVar13 = HcGetAutoChCtrlbyBandIdx(param_1,uVar11);
  if ((2 < DebugLevel) &&
     (printk("[AutoChSelBuildChannelListFor5G] cfg_ht_bw = %d, cfg_vht_bw = %d\n",iVar10,uVar9),
     2 < DebugLevel)) {
    printk("%s----------------->\n","AutoChSelBuildChannelListFor5G");
  }
  os_alloc_mem(0,local_2c,0x1e0);
  if (local_2c[0] == 0) {
    if (DebugLevel < 0) {
      return;
    }
    printk("%s-----------------> alloc mem failed\n","AutoChSelBuildChannelListFor5G");
    return;
  }
  os_zero_mem(local_2c[0],0x1e0);
  if (*(char *)(iVar12 + 0x49c) == '\0') {
    iVar22 = 0;
    iVar12 = DebugLevel;
  }
  else {
    iVar22 = 0;
    iVar23 = iVar22;
    iVar24 = iVar22;
    do {
      iVar24 = iVar24 + 1;
      iVar14 = CheckNonOccupancyChannel(param_1,param_2,*(undefined1 *)(iVar12 + iVar23));
      if (iVar14 != 0) {
        *(undefined1 *)(local_2c[0] + iVar22 * 8) = *(undefined1 *)(iVar12 + iVar23);
        iVar22 = iVar22 + 1;
      }
      iVar23 = iVar23 + 0x14;
    } while (iVar24 < (int)(uint)*(byte *)(iVar12 + 0x49c));
    iVar12 = DebugLevel;
    if (iVar22 != 0) {
      iVar23 = 0;
      do {
        if (2 < iVar12) {
          printk("%s : Ch = %3d\n","AutoChSelBuildChannelListFor5G",
                 *(undefined1 *)(local_2c[0] + iVar23 * 8));
          iVar12 = DebugLevel;
        }
        iVar23 = iVar23 + 1;
      } while (iVar23 != iVar22);
    }
  }
  if (2 < iVar12) {
    printk("%s<-----------------\n","AutoChSelBuildChannelListFor5G");
    iVar12 = DebugLevel;
  }
  if (0 < iVar12) {
    printk("[AutoChSelBuildChannelListFor5G] ChListNum5G = %d\n",iVar22);
  }
  if (iVar22 != 0) {
    iVar23 = 0;
    iVar12 = local_2c[0];
    do {
      iVar24 = iVar12 + iVar23 * 8;
      cVar1 = *(char *)(iVar12 + iVar23 * 8);
      if ((&DAT_0036b862)[param_1] == '\0') {
LAB_0002346c:
        *(undefined1 *)(iVar24 + 7) = 0;
        cVar1 = *(char *)(param_1 + 0xa79630);
      }
      else {
        if ((&DAT_0036b863)[param_1] != cVar1) {
          pcVar20 = &DAT_0036b863 + param_1;
          do {
            if (pcVar20 == &DAT_0036b863 + param_1 + (uint)(byte)((&DAT_0036b862)[param_1] - 1))
            goto LAB_0002346c;
            pcVar20 = pcVar20 + 1;
          } while (*pcVar20 != cVar1);
        }
        *(undefined1 *)(iVar24 + 7) = 1;
        cVar1 = *(char *)(param_1 + 0xa79630);
      }
      if (cVar1 != '\0') {
        uVar5 = RadarChannelCheck(param_1);
        *(undefined1 *)(iVar24 + 7) = uVar5;
        iVar12 = local_2c[0];
      }
      iVar23 = iVar23 + 1;
    } while (iVar23 != iVar22);
    iVar23 = 0;
    iVar24 = 0;
    do {
      if (iVar10 == 0) {
        *(undefined1 *)(iVar12 + iVar23 + 3) = 0;
        *(undefined1 *)(local_2c[0] + iVar23 + 6) = 1;
        *(undefined1 *)(local_2c[0] + iVar23 + 2) = *(undefined1 *)(local_2c[0] + iVar23);
        iVar12 = local_2c[0];
      }
      else {
        if (uVar9 == 0 && iVar10 == 1) {
          bVar4 = true;
          iVar14 = N_ChannelGroupCheck(param_1,*(undefined1 *)(iVar12 + iVar23),param_2);
          iVar12 = local_2c[0];
          if (iVar14 != 0) {
            *(undefined1 *)(local_2c[0] + iVar23 + 3) = 1;
            pbVar15 = (byte *)(local_2c[0] + iVar23);
            uVar18 = (uint)*(byte *)(local_2c[0] + iVar23);
            uVar27 = uVar18 & 0xf7;
            if (((uVar27 != 0x24) && ((uVar18 & 0xb7) != 0x34)) && (uVar27 != 100)) {
              if ((uVar27 == 0x95 || uVar18 == 0x84) && ((uint)pbVar15[8] == uVar18 + 4)) {
LAB_00023c80:
                pbVar15[6] = 1;
                goto LAB_00023740;
              }
              if ((uVar27 == 0x95 || uVar18 == 0x84) ||
                 (((((uVar18 & 0xbf) != 0x30 && (uVar18 & 0xaf) != 0x28 && (uVar18 != 0x40)) &&
                   ((uVar27 != 0x80 && ((uVar18 + 0x67 & 0xf7) != 0)))) ||
                  ((uint)pbVar15[-8] != uVar18 - 4)))) goto LAB_00023738;
              pbVar15[6] = 1;
              if (pbVar15[7] == 1) {
LAB_00023abc:
                if (uVar27 == 0x95 || uVar18 == 0x84) goto LAB_00023ae0;
                if (uVar27 != 0x34) {
LAB_00023b08:
                  if ((((uVar27 != 0x74) && (uVar18 != 0x84 && uVar27 != 0x95)) &&
                      (((uVar18 & 0xbf) == 0x30 || (uVar18 & 0xaf) == 0x28 ||
                       (((uVar18 == 0x40 || (uVar27 == 0x80)) || ((uVar18 + 0x67 & 0xf7) == 0))))))
                     && ((uint)*(byte *)(local_2c[0] + iVar23 + -8) == uVar18 - 4)) {
                    *(undefined1 *)(local_2c[0] + iVar23 + -8 + 7) = 1;
                    uVar18 = (uint)*pbVar15;
                    uVar27 = uVar18 & 0xf7;
                    goto LAB_00023750;
                  }
                }
LAB_00023ad4:
                uVar27 = uVar18 & 0xf7;
              }
            }
            else {
              if ((uint)pbVar15[8] == uVar18 + 4) goto LAB_00023c80;
LAB_00023738:
              pbVar15[6] = 0;
LAB_00023740:
              if (pbVar15[7] == 1) {
                if (uVar27 != 0x24) {
                  if ((uVar18 & 0xb7) == 0x34) {
LAB_00023ae0:
                    iVar14 = local_2c[0] + iVar23 + 8;
                    if ((uint)*(byte *)(local_2c[0] + iVar23 + 8) != uVar18 + 4) {
                      if ((uVar27 != 0x34) && (uVar27 != 100)) goto LAB_00023b08;
                      goto LAB_00023ad4;
                    }
                  }
                  else {
                    if (uVar27 != 100) goto LAB_00023abc;
                    iVar14 = local_2c[0] + iVar23 + 8;
                    if ((uint)*(byte *)(local_2c[0] + iVar23 + 8) != uVar18 + 4) goto LAB_00023ad4;
                  }
                }
                else {
                  iVar14 = local_2c[0] + iVar23 + 8;
                  if ((uint)*(byte *)(local_2c[0] + iVar23 + 8) != uVar18 + 4) goto LAB_00023750;
                }
                *(undefined1 *)(iVar14 + 7) = 1;
                uVar18 = (uint)*pbVar15;
                uVar27 = uVar18 & 0xf7;
              }
            }
LAB_00023750:
            if ((((uVar27 & 0xe7) == 0x24) || ((uVar27 & 0xe7) == 100)) ||
               (uVar27 == 0x95 || uVar18 == 0x84)) {
              pbVar15[2] = (char)uVar18 + 2;
            }
            else {
              pbVar15[2] = (char)uVar18 - 2;
            }
            goto joined_r0x000234e8;
          }
        }
        else {
          bVar4 = false;
        }
        bVar3 = (uVar9 & 0xfd) != 1;
        if ((bVar3) ||
           (iVar14 = vht80_channel_group(param_1,*(undefined1 *)(iVar12 + iVar23),param_2),
           iVar12 = local_2c[0], iVar14 == 0)) {
          if ((uVar9 == 2) &&
             (iVar14 = vht80_channel_group(param_1,*(undefined1 *)(iVar12 + iVar23),param_2),
             iVar12 = local_2c[0], iVar14 != 0)) {
            *(undefined1 *)(local_2c[0] + iVar23 + 3) = 3;
            if (pbVar8 == (byte *)0x0) goto LAB_00023ca8;
            bVar19 = pbVar8[1];
            pbVar15 = pbVar8;
            if (bVar19 == 0) {
LAB_000238b4:
              bVar19 = *(byte *)(local_2c[0] + iVar23 + 7);
            }
            else {
              bVar2 = *(byte *)(local_2c[0] + iVar23);
              bVar17 = *pbVar8;
              pbVar25 = (byte *)(local_2c[0] + iVar23);
              pbVar28 = pbVar8;
              if (bVar2 < bVar17 || bVar19 < bVar2) {
                do {
                  pbVar15 = pbVar28 + 3;
                  bVar19 = pbVar28[4];
                  if (bVar19 == 0) goto LAB_000238b4;
                  bVar17 = *pbVar15;
                  pbVar28 = pbVar15;
                } while (bVar19 < bVar2 || bVar2 < bVar17);
              }
              iVar12 = 1;
              iVar14 = 0;
              pbVar28 = pbVar25;
              do {
                iVar16 = iVar12 * 8;
                iVar12 = iVar12 + 1;
                pbVar28 = pbVar28 + -8;
                if (pbVar25[iVar16] <= bVar19 && bVar17 <= pbVar25[iVar16]) {
                  iVar14 = iVar14 + 1;
                }
                if (*pbVar28 <= bVar19 && bVar17 <= *pbVar28) {
                  iVar14 = iVar14 + 1;
                }
              } while (iVar12 != 8);
              bVar19 = pbVar25[7];
              if (iVar14 == 7) {
                pbVar25[6] = 1;
              }
            }
            if (bVar19 == 1) {
              iVar14 = local_2c[0] + iVar23;
              iVar12 = iVar14;
              do {
                bVar19 = *pbVar15;
                if ((bVar19 <= *(byte *)(iVar14 + 8)) && (*(byte *)(iVar14 + 8) <= pbVar15[1])) {
                  *(undefined1 *)(iVar14 + 0xf) = 1;
                  bVar19 = *pbVar15;
                }
                iVar14 = iVar14 + 8;
                if ((bVar19 <= *(byte *)(iVar12 + -8)) && (*(byte *)(iVar12 + -8) <= pbVar15[1])) {
                  *(undefined1 *)(iVar12 + -1) = 1;
                }
                iVar12 = iVar12 + -8;
              } while (iVar12 != local_2c[0] + iVar23 + -0x38);
            }
            puVar26 = (undefined1 *)(local_2c[0] + iVar23);
            uVar5 = vht_cent_ch_freq(*puVar26,2,uVar6);
            puVar26[2] = uVar5;
            iVar12 = local_2c[0];
          }
          else {
            if (2 < DebugLevel) {
              printk("[%s] The channel:%d is undefined\n","AutoChSelBuildChannelListFor5G",
                     *(undefined1 *)(iVar12 + iVar23));
              iVar12 = local_2c[0];
            }
            if (bVar4) {
              *(undefined1 *)(iVar12 + iVar23 + 3) = 1;
              iVar12 = local_2c[0];
            }
            else if (bVar3) {
              if (uVar9 == 2) {
                *(undefined1 *)(iVar12 + iVar23 + 3) = 3;
                iVar12 = local_2c[0];
              }
            }
            else {
              *(undefined1 *)(iVar12 + iVar23 + 3) = 2;
              iVar12 = local_2c[0];
            }
            *(undefined1 *)(iVar12 + iVar23 + 6) = 0;
            *(undefined1 *)(iVar12 + iVar23 + 2) = *(undefined1 *)(iVar12 + iVar23);
            iVar12 = local_2c[0];
          }
        }
        else {
          *(undefined1 *)(local_2c[0] + iVar23 + 3) = 2;
          if (pbVar7 == (byte *)0x0) {
LAB_00023ca8:
            os_free_mem(local_2c[0]);
            return;
          }
          bVar19 = pbVar7[1];
          pbVar15 = pbVar7;
          if (bVar19 == 0) {
LAB_00023800:
            cVar1 = *(char *)(local_2c[0] + iVar23 + 7);
          }
          else {
            bVar17 = *pbVar7;
            iVar12 = local_2c[0] + iVar23;
            bVar2 = *(byte *)(local_2c[0] + iVar23);
            pbVar28 = pbVar7;
            if (bVar2 < bVar17 || bVar19 < bVar2) {
              do {
                pbVar15 = pbVar28 + 3;
                bVar19 = pbVar28[4];
                if (bVar19 == 0) goto LAB_00023800;
                bVar17 = *pbVar15;
                pbVar28 = pbVar15;
              } while (bVar19 < bVar2 || bVar2 < bVar17);
            }
            local_3c = 0;
            iVar14 = 1;
            iVar16 = iVar12;
            do {
              bVar2 = *(byte *)(iVar12 + iVar14 * 8);
              if (bVar2 <= bVar19 && bVar17 <= bVar2) {
                local_3c = local_3c + 1;
              }
              iVar21 = iVar14 + 1;
              if ((iVar14 <= iVar24) &&
                 (*(byte *)(iVar16 + -8) <= bVar19 && bVar17 <= *(byte *)(iVar16 + -8))) {
                local_3c = local_3c + 1;
              }
              iVar16 = iVar16 + -8;
              iVar14 = iVar21;
            } while (iVar21 != 4);
            if (local_3c == 3) {
              *(undefined1 *)(iVar12 + 6) = 1;
            }
            cVar1 = *(char *)(iVar12 + 7);
          }
          if (cVar1 == '\x01') {
            iVar16 = local_2c[0] + iVar23;
            iVar12 = iVar16;
            iVar14 = 1;
            do {
              if ((*pbVar15 <= *(byte *)(iVar12 + 8)) && (*(byte *)(iVar12 + 8) <= pbVar15[1])) {
                *(undefined1 *)(iVar12 + 0xf) = 1;
              }
              iVar12 = iVar12 + 8;
              iVar21 = iVar14 + 1;
              if (((iVar14 <= iVar24) && (*pbVar15 <= *(byte *)(iVar16 + -8))) &&
                 (*(byte *)(iVar16 + -8) <= pbVar15[1])) {
                *(undefined1 *)(iVar16 + -1) = 1;
              }
              iVar16 = iVar16 + -8;
              iVar14 = iVar21;
            } while (iVar21 != 4);
          }
          puVar26 = (undefined1 *)(local_2c[0] + iVar23);
          uVar5 = vht_cent_ch_freq(*puVar26,1,uVar6);
          puVar26[2] = uVar5;
          iVar12 = local_2c[0];
        }
      }
joined_r0x000234e8:
      local_2c[0] = iVar12;
      if (iVar24 + 1 == iVar22) goto LAB_00023578;
      iVar24 = iVar24 + 1;
      iVar23 = iVar23 + 8;
    } while( true );
  }
  uVar5 = 0;
LAB_00023610:
  *(undefined1 *)(iVar13 + 0xe) = uVar5;
  os_free_mem(local_2c[0]);
  return;
LAB_00023578:
  iVar10 = 0;
  do {
    if (2 < DebugLevel) {
      iVar12 = local_2c[0] + iVar10 * 8;
      printk("%s:\tPrimChannel =  %3d, CenChannel = %3d, BW= %d, BwCap= %d, SkipChannel= %d\n",
             "AutoChSelBuildChannelListFor5G",*(undefined1 *)(local_2c[0] + iVar10 * 8),
             *(undefined1 *)(iVar12 + 2),*(undefined1 *)(iVar12 + 3),*(undefined1 *)(iVar12 + 6),
             *(undefined1 *)(iVar12 + 7));
    }
    iVar10 = iVar10 + 1;
  } while (iVar10 < iVar22);
  iVar23 = 0;
  iVar12 = 0;
  iVar10 = local_2c[0];
  do {
    if ((*(char *)(iVar10 + 7) != '\x01') &&
       (iVar24 = iVar13 + iVar23 * 8, *(char *)(iVar10 + 6) != '\0')) {
      iVar23 = iVar23 + 1;
      *(undefined1 *)(iVar24 + 0x74) = *(undefined1 *)(local_2c[0] + iVar12 * 8);
      *(undefined1 *)(iVar24 + 0x77) = *(undefined1 *)(iVar10 + 3);
      *(undefined1 *)(iVar24 + 0x7a) = *(undefined1 *)(iVar10 + 6);
      *(undefined1 *)(iVar24 + 0x76) = *(undefined1 *)(iVar10 + 2);
      *(undefined1 *)(iVar24 + 0x7b) = *(undefined1 *)(iVar10 + 7);
      *(undefined1 *)(iVar24 + 0x75) = *(undefined1 *)(iVar10 + 1);
    }
    iVar12 = iVar12 + 1;
    iVar10 = iVar10 + 8;
  } while (iVar12 < iVar22);
  uVar5 = (undefined1)iVar23;
  goto LAB_00023610;
}

