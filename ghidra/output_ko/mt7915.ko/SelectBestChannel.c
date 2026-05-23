// module: mt7915.ko
// function: SelectBestChannel @ 0x1fd90
// size: 12112 bytes
//

uint SelectBestChannel(int *param_1,undefined4 param_2,int param_3)

{
  byte *pbVar1;
  char cVar2;
  undefined4 uVar3;
  int iVar4;
  byte *pbVar5;
  int *piVar6;
  int iVar7;
  int iVar8;
  undefined4 uVar9;
  int *piVar10;
  int extraout_r1;
  int iVar11;
  int extraout_r1_00;
  int extraout_r1_01;
  byte *pbVar12;
  int extraout_r1_02;
  uint uVar13;
  uint uVar14;
  int iVar15;
  byte bVar16;
  undefined4 *puVar17;
  int iVar18;
  uint uVar19;
  int iVar20;
  undefined *puVar21;
  uint uVar22;
  int iVar23;
  uint uVar24;
  uint uVar25;
  undefined4 uVar26;
  undefined4 *puVar27;
  int iVar28;
  byte *pbVar29;
  uint *puVar30;
  char *pcVar31;
  uint uVar32;
  uint uVar33;
  uint uVar34;
  char cVar35;
  undefined4 uVar36;
  char *pcVar37;
  bool bVar38;
  bool bVar39;
  uint local_a0;
  char *local_9c;
  uint local_98;
  uint local_94;
  uint local_8c;
  undefined4 *local_70;
  int local_6c;
  int local_68;
  undefined4 local_64;
  
  uVar3 = HcGetBandByWdev(param_3);
  iVar4 = HcGetAutoChCtrlbyBandIdx(param_1,uVar3);
  CheckPhyModeIsABand(param_1,uVar3);
  switch(param_2) {
  case 0:
  case 1:
    uVar3 = HcGetBandByWdev(param_3);
    piVar6 = (int *)HcGetAutoChCtrlbyBandIdx(param_1,uVar3);
    iVar23 = *piVar6;
    iVar7 = wlan_operate_get_ht_bw(param_3);
    iVar8 = wlan_operate_get_ext_cha(param_3);
    iVar18 = hc_get_channel_ctrl(param_1[0x29e5e8],uVar3);
    if (iVar23 == 0) {
joined_r0x000215a8:
      if (-1 < DebugLevel) {
        printk("pAd->pChannelInfo equal NULL.\n");
      }
      uVar19 = FirstChannel(param_1,param_3);
      goto LAB_00020e9c;
    }
    uVar19 = (uint)*(byte *)(iVar18 + 0x49c);
    if (uVar19 != 0) {
      uVar22 = 0;
LAB_00020674:
      do {
        while( true ) {
          iVar28 = (int)(short)uVar22;
          piVar6 = (int *)(iVar23 + iVar28 * 4);
          if (piVar6[0x3c] == 0) {
            uVar24 = uVar22 + 1;
            goto LAB_00020750;
          }
          *(int *)(iVar23 + iVar28 * 4) = *(int *)(iVar23 + iVar28 * 4) + 0x1e;
          if (*(char *)(iVar23 + 0x510) != '\0') break;
          if (iVar8 == 3 && iVar7 == 1) {
            iVar20 = 8;
          }
          else {
            iVar20 = 4;
          }
          uVar24 = uVar22 + iVar20 + 1;
          uVar19 = uVar22 + 1;
          if (uVar22 + 1 < uVar24) {
            do {
              uVar34 = uVar19 + 1;
              piVar6 = piVar6 + 1;
              if ((int)uVar19 < 0x3b) {
                *piVar6 = *piVar6 + 1;
              }
              uVar19 = uVar34;
            } while ((int)uVar34 < (int)uVar24);
          }
          if (iVar8 == 1 && iVar7 == 1) {
            iVar20 = 8;
          }
          else {
            iVar20 = 4;
          }
          uVar19 = (uVar22 - iVar20) - 1;
          if ((int)uVar19 < (int)(uVar22 - 1)) {
            piVar6 = (int *)(iVar23 + iVar28 * 4);
            uVar24 = uVar22 - 1;
            do {
              uVar34 = uVar24 - 1;
              piVar6 = piVar6 + -1;
              if (uVar24 < 0x3c) {
                *piVar6 = *piVar6 + 1;
              }
              uVar24 = uVar34;
            } while (uVar34 != uVar19);
          }
LAB_000209fc:
          uVar19 = (uint)*(byte *)(iVar18 + 0x49c);
          uVar22 = uVar22 + 1 & 0xff;
          if (uVar19 <= uVar22) goto LAB_0002075c;
        }
        uVar19 = (uint)*(byte *)(iVar18 + iVar28 * 0x14);
        iVar28 = iVar18 + iVar28 * 0x14;
        if (uVar19 < 0xf || iVar7 != 1) {
LAB_00020a10:
          uVar19 = (uint)*(byte *)(iVar18 + 0x49c);
          uVar22 = uVar22 + 1 & 0xff;
          if (uVar19 <= uVar22) break;
          goto LAB_00020674;
        }
        if ((((uVar19 & 0xe7) == 0x24) || ((uVar19 & 0xe7) == 100)) ||
           ((uVar19 & 0xf7) == 0x95 || uVar19 == 0x84)) {
          uVar24 = uVar22 + 1;
          if ((uVar24 < 0x3b) && (*(byte *)(iVar28 + 0x14) - uVar19 == 4)) {
            piVar6[1] = piVar6[1] + 1;
            uVar19 = (uint)*(byte *)(iVar18 + 0x49c);
            goto LAB_00020750;
          }
          goto LAB_000209fc;
        }
        if (((((uVar19 & 0xbf) != 0x30 && (uVar19 & 0xaf) != 0x28) && (uVar19 != 0x40)) &&
            ((uVar19 & 0xf7) != 0x80)) && ((uVar19 + 0x67 & 0xf7) != 0)) goto LAB_00020a10;
        if (uVar22 == 0) {
          uVar19 = (uint)*(byte *)(iVar18 + 0x49c);
          uVar24 = 1;
        }
        else {
          if (uVar19 - *(byte *)(iVar28 + -0x14) != 4) goto LAB_00020a10;
          uVar24 = uVar22 + 1;
          piVar6[-1] = piVar6[-1] + 1;
          uVar19 = (uint)*(byte *)(iVar18 + 0x49c);
        }
LAB_00020750:
        uVar22 = uVar24 & 0xff;
      } while (uVar22 < uVar19);
    }
LAB_0002075c:
    if ((*(int *)(*param_1 + 0x38) - 0x100U & 0xfffffeff) == 0) {
      uVar3 = HcGetBandByWdev(param_1 + *(int *)(*param_1 + 0x3c) * 0x160d + 0xadc92);
      iVar8 = hc_get_channel_ctrl(param_1[0x29e5e8],uVar3);
      piVar6 = (int *)HcGetAutoChCtrlbyBandIdx(param_1,uVar3);
      if (*(char *)((int)param_1 + 0x36b862) != '\0') {
        uVar19 = 0;
        do {
          cVar2 = (&DAT_0036b863)[(int)param_1 + uVar19];
          pcVar31 = (char *)hc_get_channel_ctrl(param_1[0x29e5e8],uVar3);
          uVar24 = (uint)(byte)pcVar31[0x49c];
          uVar22 = uVar24;
          if (uVar24 != 0) {
            if (*pcVar31 == cVar2) {
              uVar24 = 0;
              uVar22 = 0;
            }
            else {
              uVar34 = 0;
              do {
                uVar34 = uVar34 + 1;
                if (uVar34 == uVar24) goto LAB_00020e14;
                pcVar31 = pcVar31 + 0x14;
              } while (*pcVar31 != cVar2);
              uVar24 = uVar34 & 0xff;
              uVar22 = uVar34;
            }
          }
LAB_00020e14:
          uVar19 = uVar19 + 1 & 0xff;
          if (*(byte *)(iVar8 + 0x49c) != uVar24) {
            *(undefined1 *)(*piVar6 + uVar22 + 0x2d0) = 1;
          }
        } while (uVar19 < *(byte *)((int)param_1 + 0x36b862));
      }
    }
    if (DebugLevel < 3) {
      uVar19 = (uint)*(byte *)(iVar18 + 0x49c);
      if (uVar19 != 0) {
LAB_000207a0:
        uVar22 = 0;
        iVar8 = DebugLevel;
        do {
          if (2 < iVar8) {
            iVar8 = iVar23 + (short)uVar22 * 4;
            pcVar31 = "TRUE";
            if (*(char *)(iVar23 + uVar22 + 0x2d0) != '\x01') {
              pcVar31 = "FALSE";
            }
            printk("Channel %d : Dirty = %ld, ApCnt=%ld, Busy Time = %d, Skip Channel = %s\n",
                   *(undefined1 *)(iVar18 + uVar22 * 0x14),
                   *(undefined4 *)(iVar23 + (short)uVar22 * 4),*(undefined4 *)(iVar8 + 0xf0),
                   *(undefined4 *)(iVar8 + 0x32c),pcVar31);
            uVar19 = (uint)*(byte *)(iVar18 + 0x49c);
            iVar8 = DebugLevel;
          }
          uVar22 = uVar22 + 1 & 0xff;
        } while (uVar22 < uVar19);
        goto LAB_000207cc;
      }
    }
    else {
      printk("=====================================================\n");
      uVar19 = (uint)*(byte *)(iVar18 + 0x49c);
      iVar8 = DebugLevel;
      if (uVar19 != 0) goto LAB_000207a0;
LAB_000207cc:
      if (2 < iVar8) {
        printk("=====================================================\n");
      }
    }
    uVar19 = 0;
    *(undefined1 *)(param_1 + 0xdae18) = 0;
    uVar22 = (uint)*(byte *)(iVar18 + 0x49c);
    if (uVar22 != 0) {
      do {
        if (*(char *)(iVar23 + uVar19 + 0x2d0) != '\x01') {
          if (((((char)param_1[0xdae16] != '\x01') || (*(char *)(iVar23 + 0x510) != '\x01')) ||
              (iVar8 = RadarChannelCheck(param_1,*(undefined1 *)(iVar18 + uVar19 * 0x14)),
              iVar8 == 0)) &&
             ((iVar8 = QBSS_LoadIsBusyTimeAccepted
                                 (param_1,*(undefined4 *)(iVar23 + (short)uVar19 * 4 + 0x32c)),
              iVar8 != 0 && (*(int *)(iVar23 + (short)uVar19 * 4) == 0)))) {
            if (uVar19 < *(byte *)(iVar18 + 0x49c)) {
              if (2 < DebugLevel) {
                printk("Rule 1 APCnt : dirtiness == 0 (no one used and no interference) ==> Select Channel %d\n"
                       ,*(undefined1 *)(iVar18 + uVar19 * 0x14));
              }
              uVar19 = (uint)*(byte *)(iVar18 + uVar19 * 0x14);
              goto LAB_00020e9c;
            }
            break;
          }
          uVar22 = (uint)*(byte *)(iVar18 + 0x49c);
        }
        uVar19 = uVar19 + 1 & 0xff;
      } while (uVar19 < uVar22);
    }
    uVar22 = 0x1e;
    do {
      __memzero(&local_64,0x3c);
      cVar2 = *(char *)(iVar18 + 0x49c);
      if (cVar2 != '\0') {
        iVar8 = 0;
        pcVar31 = (char *)(iVar23 + 0x2cf);
        cVar35 = '\0';
        do {
          pcVar31 = pcVar31 + 1;
          if ((*pcVar31 != '\x01') && (*(uint *)(iVar23 + iVar8 * 4) == uVar22)) {
            cVar35 = cVar35 + '\x01';
            *(undefined1 *)((int)&local_64 + iVar8) = 1;
          }
          iVar8 = iVar8 + 1;
        } while (iVar8 != (byte)(cVar2 - 1) + 1);
        if (cVar35 != '\0') {
          uVar19 = 0;
          uVar24 = 0;
          local_a0 = 0xff;
          do {
            iVar28 = iVar23 + uVar24 * 4;
            iVar8 = QBSS_LoadIsBusyTimeAccepted(param_1,*(undefined4 *)(iVar28 + 0x32c));
            if ((((iVar8 != 0) && (*(char *)((int)&local_64 + uVar24) != '\0')) &&
                (uVar34 = *(uint *)(iVar28 + 0xf0), uVar34 < local_a0)) &&
               ((uVar13 = (uint)*(byte *)(iVar18 + uVar24 * 0x14), iVar7 != 1 ||
                ((uVar13 != 0x8c && (uVar13 != 0xa5)))))) {
              if (((char)param_1[0xdae16] == '\x01') && (*(char *)(iVar23 + 0x510) == '\x01')) {
                iVar8 = RadarChannelCheck(param_1);
                if (iVar8 != 0) goto LAB_00021408;
                uVar34 = *(uint *)(iVar28 + 0xf0);
                uVar13 = (uint)*(byte *)(iVar18 + uVar24 * 0x14);
              }
              local_a0 = uVar34 & 0xff;
              uVar19 = uVar13;
            }
LAB_00021408:
            uVar24 = uVar24 + 1 & 0xff;
          } while (uVar24 < *(byte *)(iVar18 + 0x49c));
          if (uVar19 != 0) {
            if ((2 < DebugLevel) &&
               (printk("Rule 2 APCnt : minimum APCnt with  minimum interference(dirtiness: 30~32) ==> Select Channel %d\n"
                       ,uVar19), 2 < DebugLevel)) {
              printk(" Dirtiness = %d ,  Min ApCnt = %d\n",uVar22 & 0xff,local_a0);
            }
            goto LAB_00020e9c;
          }
        }
      }
      uVar22 = uVar22 + 1;
    } while (uVar22 != 0x21);
    iVar7 = RandomByte2(param_1);
    uVar22 = (uint)*(byte *)(iVar18 + 0x49c);
    if (uVar22 == 0) {
      uVar19 = 0;
    }
    else {
      uVar24 = 0;
      do {
        __aeabi_idivmod(uVar24 + iVar7,uVar22);
        uVar19 = (uint)*(byte *)(iVar18 + extraout_r1 * 0x14);
        if (*(char *)((int)param_1 + 0x36b862) == '\0') {
LAB_000214c0:
          if ((((char)param_1[0xdae16] != '\x01') || (*(char *)(iVar23 + 0x510) != '\x01')) ||
             (iVar8 = RadarChannelCheck(param_1,uVar19), iVar8 == 0)) break;
          uVar22 = (uint)*(byte *)(iVar18 + 0x49c);
        }
        else if (*(byte *)((int)param_1 + 0x36b863) != uVar19) {
          pbVar12 = (byte *)((int)param_1 + 0x36b863);
          do {
            if (pbVar12 ==
                (byte *)((int)param_1 +
                        (int)(&DAT_0036b863 + (byte)(*(char *)((int)param_1 + 0x36b862) - 1))))
            goto LAB_000214c0;
            pbVar12 = pbVar12 + 1;
          } while (*pbVar12 != uVar19);
        }
        uVar24 = uVar24 + 1 & 0xff;
      } while (uVar24 < uVar22);
    }
    if (2 < DebugLevel) {
      printk("Rule 3 APCnt : Randomly Select  ==> Select Channel %d\n",uVar19);
    }
    goto LAB_00020e9c;
  case 2:
    piVar10 = param_1 + 0xadc92;
    uVar3 = HcGetBandByWdev(piVar10);
    iVar7 = hc_get_channel_ctrl(param_1[0x29e5e8],uVar3);
    piVar6 = (int *)HcGetAutoChCtrlbyBandIdx(param_1,uVar3);
    pbVar12 = (byte *)piVar6[1];
    puVar17 = (undefined4 *)*piVar6;
    local_64 = (int *)((uint)local_64._2_2_ << 0x10);
    iVar8 = wlan_config_get_ht_bw(piVar10);
    if (pbVar12 == (byte *)0x0) {
      if (-1 < DebugLevel) {
        printk("pAd->pBssInfoTab equal NULL.\n");
      }
    }
    else {
      if (puVar17 != (undefined4 *)0x0) {
        if (*pbVar12 != 0) {
          local_a0 = 0;
          pbVar29 = pbVar12;
          do {
            bVar16 = pbVar29[0x28];
            pbVar5 = (byte *)hc_get_channel_ctrl(param_1[0x29e5e8],uVar3);
            uVar19 = (uint)pbVar5[0x49c];
            if (uVar19 == 0) {
              uVar13 = 0xffffffff;
              uVar34 = 1;
              uVar22 = 0;
              uVar24 = uVar19;
LAB_00020234:
              bVar16 = pbVar29[0x2a];
              if ('E' < (char)bVar16) goto LAB_00020244;
LAB_00020898:
              if ((char)bVar16 < ')') {
                iVar18 = puVar17[uVar24] + 0x1e;
              }
              else {
                iVar18 = puVar17[uVar24] + 0x28;
              }
              puVar17[uVar24] = iVar18;
            }
            else {
              if (*pbVar5 == bVar16) {
                uVar22 = 0;
                uVar13 = 0xffffffff;
                uVar34 = 1;
                uVar24 = uVar22;
                goto LAB_00020234;
              }
              uVar24 = 0;
              do {
                uVar13 = uVar24;
                uVar24 = uVar13 + 1;
                if (uVar24 == uVar19) {
                  uVar34 = uVar19 + 1;
                  uVar13 = uVar19 - 1;
                  if (uVar34 < 0x3b) {
                    uVar22 = 0;
                    uVar24 = uVar19;
                  }
                  else {
                    uVar22 = 1;
                    uVar24 = uVar19;
                  }
                  goto LAB_00020234;
                }
                pbVar5 = pbVar5 + 0x14;
              } while (*pbVar5 != bVar16);
              uVar34 = uVar13 + 2;
              bVar16 = pbVar29[0x2a];
              uVar22 = (uint)(0x3a < (int)uVar34);
              if ((char)bVar16 < 'F') goto LAB_00020898;
LAB_00020244:
              iVar18 = puVar17[uVar24] + 0x32;
              puVar17[uVar24] = iVar18;
            }
            puVar17[uVar24] = iVar18 + 0x28;
            if (pbVar29[0x29] == 1) {
              if (*(char *)(puVar17 + 0x144) == '\0') {
                uVar19 = uVar24 + 8;
LAB_000208c4:
                local_8c = 4;
                bVar38 = (int)uVar19 < (int)uVar34;
              }
              else {
                uVar19 = uVar24 + 2;
                bVar38 = (int)uVar19 < (int)uVar34;
                local_8c = 1;
              }
            }
            else {
              uVar19 = uVar34;
              if (pbVar29[0x29] == 3) {
                if (*(char *)(puVar17 + 0x144) == '\0') {
                  uVar19 = uVar24 + 4;
                  local_8c = 8;
                  if ((int)uVar19 < (int)uVar34) {
                    bVar38 = true;
                  }
                  else {
                    bVar38 = false;
                  }
                }
                else {
                  bVar38 = false;
                  local_8c = 2;
                }
              }
              else {
                if (*(char *)(puVar17 + 0x144) == '\0') {
                  uVar19 = uVar24 + 4;
                  goto LAB_000208c4;
                }
                bVar38 = false;
                local_8c = 1;
              }
            }
            if ((!bVar38 && uVar22 == 0) &&
               ((int)((uint)*(byte *)(iVar7 + uVar34 * 0x14) -
                     (uint)*(byte *)(iVar7 + uVar24 * 0x14)) < 5)) {
              uVar22 = uVar34 + 1;
              iVar18 = ((uVar24 - uVar34) + 9) * 4;
              piVar10 = puVar17 + uVar34 + 0x3fffffff;
              pbVar5 = (byte *)(iVar7 + uVar22 * 0x14);
              do {
                piVar10 = piVar10 + 1;
                bVar39 = SBORROW4(uVar22,0x3a);
                iVar23 = uVar22 - 0x3a;
                bVar38 = uVar22 == 0x3a;
                if ((int)uVar22 < 0x3b) {
                  bVar39 = SBORROW4(uVar22,uVar19);
                  iVar23 = uVar22 - uVar19;
                  bVar38 = uVar22 == uVar19;
                }
                uVar22 = uVar22 + 1;
                *piVar10 = *piVar10 + iVar18;
              } while ((bVar38 || iVar23 < 0 != bVar39) &&
                      (bVar16 = *pbVar5, iVar18 = iVar18 + -4, pbVar1 = pbVar5 + -0x14,
                      pbVar5 = pbVar5 + 0x14, (int)((uint)bVar16 - (uint)*pbVar1) < 5));
            }
            if (((int)(uVar24 - local_8c) <= (int)uVar13) && (uVar13 < 0x3b)) {
              piVar10 = puVar17 + uVar13;
              do {
                iVar23 = uVar13 + 1;
                iVar18 = (int)uVar13 % 0x3b;
                uVar13 = uVar13 - 1;
                if ((int)((uint)*(byte *)(iVar7 + (iVar23 % 0x3b) * 0x14) -
                         (uint)*(byte *)(iVar7 + iVar18 * 0x14)) < 5) {
                  *piVar10 = (int)piVar10 + *piVar10 + (0x24 - (int)(puVar17 + uVar24));
                }
              } while (((int)(uVar24 - local_8c) <= (int)uVar13) &&
                      (piVar10 = piVar10 + -1, uVar13 < 0x3b));
            }
            if (2 < DebugLevel) {
              printk(" ch%d bssid=%02x:%02x:%02x:%02x:%02x:%02x\n",pbVar29[0x28],pbVar29[1],
                     pbVar29[2],pbVar29[3],pbVar29[4],pbVar29[5],pbVar29[6]);
            }
            pbVar29 = pbVar29 + 0x2a;
            local_a0 = local_a0 + 1;
          } while ((int)local_a0 < (int)(uint)*pbVar12);
        }
        if ((*(int *)(*param_1 + 0x38) - 0x100U & 0xfffffeff) == 0) {
          uVar3 = HcGetBandByWdev(param_1 + *(int *)(*param_1 + 0x3c) * 0x160d + 0xadc92);
          iVar18 = hc_get_channel_ctrl(param_1[0x29e5e8],uVar3);
          piVar10 = (int *)HcGetAutoChCtrlbyBandIdx(param_1,uVar3);
          if (*(char *)((int)param_1 + 0x36b862) != '\0') {
            uVar19 = 0;
            do {
              cVar2 = (&DAT_0036b863)[(int)param_1 + uVar19];
              pcVar31 = (char *)hc_get_channel_ctrl(param_1[0x29e5e8],uVar3);
              uVar24 = (uint)(byte)pcVar31[0x49c];
              uVar22 = uVar24;
              if (uVar24 != 0) {
                if (*pcVar31 == cVar2) {
                  uVar24 = 0;
                  uVar22 = 0;
                }
                else {
                  uVar34 = 0;
                  do {
                    uVar34 = uVar34 + 1;
                    if (uVar34 == uVar24) goto LAB_00020fec;
                    pcVar31 = pcVar31 + 0x14;
                  } while (*pcVar31 != cVar2);
                  uVar24 = uVar34 & 0xff;
                  uVar22 = uVar34;
                }
              }
LAB_00020fec:
              uVar19 = uVar19 + 1 & 0xff;
              if (*(byte *)(iVar18 + 0x49c) != uVar24) {
                *(undefined1 *)(*piVar10 + uVar22 + 0x2d0) = 1;
              }
            } while (uVar19 < *(byte *)((int)param_1 + 0x36b862));
          }
        }
        if (DebugLevel < 3) {
          uVar19 = (uint)*(byte *)(iVar7 + 0x49c);
          if (uVar19 != 0) {
LAB_00020424:
            pcVar31 = (char *)(puVar17 + 0xb4);
            iVar23 = 0;
            iVar18 = DebugLevel;
            puVar27 = puVar17;
            do {
              if (2 < iVar18) {
                pcVar37 = "TRUE";
                if (*pcVar31 != '\x01') {
                  pcVar37 = "FALSE";
                }
                printk("Channel %d : Dirty = %ld, False CCA = %u, Busy Time = %u, Skip Channel = %s\n"
                       ,*(undefined1 *)(iVar7 + iVar23 * 0x14),*puVar27,puVar27[0x78],puVar27[0xcb],
                       pcVar37);
                uVar19 = (uint)*(byte *)(iVar7 + 0x49c);
                iVar18 = DebugLevel;
              }
              iVar23 = iVar23 + 1;
              puVar27 = puVar27 + 1;
              pcVar31 = pcVar31 + 1;
            } while (iVar23 < (int)uVar19);
            goto LAB_00020460;
          }
LAB_00021e64:
          uVar19 = 1;
        }
        else {
          printk("=====================================================\n");
          uVar19 = (uint)*(byte *)(iVar7 + 0x49c);
          iVar18 = DebugLevel;
          if (uVar19 != 0) goto LAB_00020424;
LAB_00020460:
          if (2 < iVar18) {
            printk("=====================================================\n");
            uVar19 = (uint)*(byte *)(iVar7 + 0x49c);
          }
          if (uVar19 == 0) goto LAB_00021e64;
          local_8c = 0;
          local_94 = 0;
          local_9c = (char *)0xffffffff;
          uVar19 = 1;
          local_98 = 0xffffffff;
          uVar22 = 0;
          do {
            while ((uVar24 = uVar22, *(char *)((int)puVar17 + uVar24 + 0x2d0) == '\x01' ||
                   (100 < (uint)puVar17[uVar24 + 0x78]))) {
LAB_000204a0:
              uVar13 = (uint)*(byte *)(iVar7 + 0x49c);
LAB_000204a8:
              uVar22 = uVar24 + 1;
              if ((int)uVar13 <= (int)(uVar24 + 1)) goto LAB_00020544;
            }
            iVar23 = iVar7 + uVar24 * 0x14;
            uVar19 = (uint)*(byte *)(iVar7 + uVar24 * 0x14);
            uVar34 = puVar17[uVar24];
            iVar18 = QBSS_LoadIsBusyTimeAccepted(param_1,puVar17[uVar24 + 0xcb]);
            if (iVar18 == 0) goto LAB_000204a0;
            if (iVar8 != 1) {
LAB_00020508:
              uVar13 = (uint)*(byte *)(iVar7 + 0x49c);
LAB_00020510:
              if (uVar34 < local_9c) goto LAB_00020520;
              goto LAB_000204a8;
            }
            if (*(char *)(puVar17 + 0x144) == '\0') {
              if (*(char *)(*piVar6 + 0x510) != '\0') {
                if ((uVar19 & 0xf7) == 0x24) goto LAB_00021624;
LAB_00021220:
                uVar22 = uVar19 & 0xf7;
                if ((uVar19 & 0xb7) == 0x34) {
                  if (uVar24 != 0xfffffffe) {
LAB_00021e34:
                    iVar18 = 1;
                    goto LAB_000212b8;
                  }
                }
                else {
                  if (uVar22 != 100) {
                    if (uVar22 == 0x95 || uVar19 == 0x84) goto LAB_00022028;
                    if ((((uVar19 & 0xbf) == 0x30 || (uVar19 & 0xaf) == 0x28) || (uVar19 == 0x40))
                       || ((uVar22 == 0x80 || ((uVar19 + 0x67 & 0xf7) == 0)))) {
                      iVar18 = -1;
                      goto LAB_0002202c;
                    }
                    goto LAB_00021270;
                  }
                  if (uVar24 != 0xfffffffe) {
                    uVar13 = (uint)*(byte *)(iVar7 + 0x49c);
                    if ((int)(uVar24 + 1) < (int)uVar13) goto LAB_000212dc;
                    goto LAB_00020510;
                  }
                }
                goto LAB_00020508;
              }
LAB_0002119c:
              if (*(char *)(iVar7 + uVar24 * 0x14) != '\x0e') {
                __memzero(&local_64,2);
                uVar13 = (uint)*(byte *)(iVar7 + 0x49c);
                if (((int)(uVar24 - 4) < 0) || ((int)uVar13 <= (int)(uVar24 - 4))) {
                  iVar18 = 0;
                }
                else {
                  iVar18 = 1;
                  uVar34 = uVar34 + puVar17[uVar24 - 4];
                  local_64 = (int *)CONCAT31(local_64._1_3_,*(undefined1 *)(iVar23 + -0x50));
                }
                if ((int)(uVar24 + 4) < (int)uVar13) {
                  uVar34 = uVar34 + puVar17[uVar24 + 4];
                  *(undefined1 *)((int)&local_64 + iVar18) = *(undefined1 *)(iVar23 + 0x50);
                }
                goto LAB_00020510;
              }
              break;
            }
            uVar22 = uVar19 & 0xf7;
            if (uVar22 != 0x24) {
              if (((uVar19 & 0xbf) == 0x3c) || (uVar22 == 100)) {
LAB_0002118c:
                if (*(char *)(*piVar6 + 0x510) != '\0') goto LAB_00021220;
                goto LAB_0002119c;
              }
              if (uVar22 != 0x95) {
                if (((((uVar19 & 0xbb) != 0x30 && (uVar19 & 0xaf) != 0x28) && (uVar19 != 0x40)) &&
                    ((uVar19 & 0xfb) != 0x80)) && (uVar19 != 0x88 && (uVar19 + 0x67 & 0xf7) != 0))
                goto LAB_000204a0;
                goto LAB_0002118c;
              }
              if (*(char *)(*piVar6 + 0x510) == '\0') goto LAB_0002119c;
LAB_00022028:
              iVar18 = 1;
LAB_0002202c:
              if (uVar24 + iVar18 == -1) goto LAB_00020508;
LAB_00021270:
              if ((uVar19 & 0xf7) == 0x95 || uVar19 == 0x84) goto LAB_00021e34;
              if (((uVar19 & 0xbf) == 0x30 || (uVar19 & 0xaf) == 0x28) ||
                 ((uVar19 - 0x40 & 0xbf) == 0)) {
                iVar18 = -1;
              }
              else {
                uVar22 = (uint)((uVar19 + 0x67 & 0xf7) == 0);
                if (uVar19 == 0x88) {
                  uVar22 = 1;
                }
                iVar18 = -uVar22;
              }
LAB_000212b8:
              uVar22 = uVar19 & 0xf7;
              uVar13 = (uint)*(byte *)(iVar7 + 0x49c);
              if ((int)(uVar24 + iVar18) < (int)uVar13) {
                if ((uVar22 == 0x34) || (uVar22 == 100)) goto LAB_000212dc;
                if ((uVar22 == 0x74) || (uVar19 == 0x84 || uVar22 == 0x95)) {
                  iVar18 = uVar24 + 1;
                }
                else if ((((uVar19 & 0xef) == 0x28 || (uVar19 & 0xbf) == 0x30) ||
                         ((uVar19 - 0x40 & 0xbf) == 0)) || ((uVar19 & 0xef) == 0x68)) {
                  iVar18 = uVar24 - 1;
                }
                else {
                  uVar22 = (uint)((uVar19 + 0x67 & 0xf7) == 0);
                  if (uVar19 == 0x88) {
                    uVar22 = 1;
                  }
                  iVar18 = uVar24 - uVar22;
                }
                goto LAB_000212e0;
              }
              goto LAB_00020510;
            }
            if (*(char *)(*piVar6 + 0x510) == '\0') goto LAB_0002119c;
LAB_00021624:
            uVar13 = (uint)*(byte *)(iVar7 + 0x49c);
            if ((int)(uVar24 + 1) < (int)uVar13) {
LAB_000212dc:
              iVar18 = uVar24 + 1;
LAB_000212e0:
              uVar34 = uVar34 + puVar17[iVar18];
              goto LAB_00020510;
            }
            if (local_9c <= uVar34) break;
LAB_00020520:
            local_94 = (uint)local_64 & 0xff;
            local_8c = (uint)local_64 >> 8 & 0xff;
            uVar22 = uVar24 + 1;
            local_9c = (char *)uVar34;
            local_98 = uVar24;
          } while ((int)(uVar24 + 1) < (int)uVar13);
LAB_00020544:
          if (local_98 != 0xffffffff) {
            uVar19 = (uint)*(byte *)(iVar7 + local_98 * 0x14);
            if (((2 < DebugLevel) &&
                (printk("Rule 1 CCA value : Min Dirtiness (Include extension channel) ==> Select Channel %d\n"
                        ,uVar19), 2 < DebugLevel)) &&
               ((printk("Min Dirty = %u\n",local_9c), 2 < DebugLevel &&
                (printk("ExChannel = %d , %d\n",local_94,local_8c), 2 < DebugLevel)))) {
              puVar21 = &_LC9;
              if (iVar8 != 1) {
                puVar21 = &_LC10;
              }
              printk("BW        = %s\n",puVar21);
            }
            goto LAB_00020e9c;
          }
          uVar22 = (uint)*(byte *)(iVar7 + 0x49c);
          if (uVar22 != 0) {
            local_a0 = local_98;
            iVar23 = 0;
            iVar18 = -1;
            do {
              if ((*(char *)((int)puVar17 + iVar23 + 0x2d0) != '\x01') &&
                 (100 < (uint)puVar17[iVar23 + 0x78])) {
                local_9c._0_1_ = *(byte *)(iVar7 + iVar23 * 0x14);
                uVar19 = (uint)(byte)local_9c;
                uVar24 = puVar17[iVar23 + 0x78] + puVar17[iVar23];
                if ((iVar8 == 1) && (*(char *)(puVar17 + 0x144) != '\0')) {
                  uVar34 = uVar19 & 0xf7;
                  if (uVar34 != 0x24) {
                    if ((uVar19 & 0xffffffbf) == 0x3c) {
LAB_000218b4:
                      if ((uVar19 & 0xb7) == 0x34) {
LAB_000217a0:
                        if (iVar23 == -2) goto LAB_000216b8;
                        goto LAB_000217a8;
                      }
                      if ((uVar19 & 0xf7) != 100) goto LAB_000218c8;
                    }
                    else if (uVar34 != 100) {
                      if (uVar34 != 0x95) {
                        if (((((uVar19 & 0xffffffbb) == 0x30 || (uVar19 & 0xffffffaf) == 0x28) ||
                             (uVar19 == 0x40)) || ((uVar19 & 0xfffffffb) == 0x80)) ||
                           (uVar19 == 0x88 || (uVar19 + 0x67 & 0xf7) == 0)) goto LAB_0002174c;
                        goto LAB_000216e8;
                      }
LAB_000218c8:
                      if ((uVar19 & 0xf7) == 0x95 || uVar19 == 0x84) goto LAB_00021fb0;
                      if ((((uVar19 & 0xffffffbf) == 0x30 || (uVar19 & 0xaf) == 0x28) ||
                          (uVar19 == 0x40)) ||
                         (((uVar19 & 0xf7) == 0x80 || ((uVar19 + 0x67 & 0xf7) == 0)))) {
                        iVar28 = -1;
                        goto LAB_00021fb4;
                      }
                      goto LAB_00021900;
                    }
LAB_000218a4:
                    if (iVar23 == -2) goto LAB_000216b8;
                  }
LAB_00021688:
                  if (iVar23 + 1 < (int)uVar22) {
LAB_00021694:
                    uVar22 = iVar23 + 1;
LAB_00021698:
                    if (uVar22 < 0x3c) {
                      uVar24 = uVar24 + puVar17[uVar22 + 0x78] + puVar17[uVar22];
                    }
                  }
                }
                else {
                  uVar34 = uVar19 & 0xf7;
                  if (uVar34 == 0x24) goto LAB_00021688;
                  if ((uVar19 & 0xffffffbf) == 0x3c) goto LAB_000218b4;
                  if (uVar34 == 100) goto LAB_000218a4;
                  if (uVar34 != 0x95) {
LAB_0002174c:
                    local_9c._0_1_ = (byte)local_9c & 0xfb;
                    if ((((uVar19 & 0xffffffbb) == 0x30 || (uVar19 & 0xffffffaf) == 0x28) ||
                        (uVar19 == 0x40)) ||
                       (((byte)local_9c == 0x80 || (uVar19 == 0x88 || (uVar19 + 0x67 & 0xf7) == 0)))
                       ) {
                      if ((uVar19 & 0xb7) != 0x34) goto LAB_000218c8;
                      goto LAB_000217a0;
                    }
                    goto LAB_000216b8;
                  }
LAB_00021fb0:
                  iVar28 = 1;
LAB_00021fb4:
                  if (iVar23 + iVar28 != -1) {
LAB_00021900:
                    if ((uVar19 & 0xf7) == 0x95 || uVar19 == 0x84) {
LAB_000217a8:
                      iVar28 = 1;
                    }
                    else if (((uVar19 & 0xffffffbf) == 0x30 || (uVar19 & 0xaf) == 0x28) ||
                            ((uVar19 - 0x40 & 0xbf) == 0)) {
                      iVar28 = -1;
                    }
                    else {
                      uVar34 = (uint)((uVar19 + 0x67 & 0xf7) == 0);
                      if (uVar19 == 0x88) {
                        uVar34 = 1;
                      }
                      iVar28 = -uVar34;
                    }
                    uVar34 = uVar19 & 0xf7;
                    if ((int)uVar22 <= iVar23 + iVar28) goto LAB_000216b8;
                    if ((uVar34 == 0x34) || (uVar34 == 100)) goto LAB_00021694;
                    if ((uVar34 == 0x74) || (uVar19 == 0x84 || uVar34 == 0x95)) {
                      uVar22 = iVar23 + 1;
                    }
                    else if ((((uVar19 & 0xef) == 0x28 || (uVar19 & 0xffffffbf) == 0x30) ||
                             ((uVar19 - 0x40 & 0xbf) == 0)) || ((uVar19 & 0xef) == 0x68)) {
                      uVar22 = iVar23 - 1;
                    }
                    else {
                      uVar22 = (uint)((uVar19 + 0x67 & 0xf7) == 0);
                      if (uVar19 == 0x88) {
                        uVar22 = 1;
                      }
                      uVar22 = iVar23 - uVar22;
                    }
                    goto LAB_00021698;
                  }
                }
LAB_000216b8:
                iVar28 = QBSS_LoadIsBusyTimeAccepted(param_1,puVar17[iVar23 + 0xcb]);
                if (iVar28 == 0 || local_a0 <= uVar24) {
                  uVar22 = (uint)*(byte *)(iVar7 + 0x49c);
                }
                else {
                  uVar22 = (uint)*(byte *)(iVar7 + 0x49c);
                  iVar18 = iVar23;
                  local_a0 = uVar24;
                }
              }
LAB_000216e8:
              iVar23 = iVar23 + 1;
            } while (iVar23 < (int)uVar22);
            if (iVar18 != -1) {
              uVar19 = (uint)*(byte *)(iVar7 + iVar18 * 0x14);
              if (2 < DebugLevel) {
                printk("Rule 2 CCA value : Min False CCA value ==> Select Channel %d, min falsecca = %d\n"
                       ,uVar19,local_a0);
              }
              goto LAB_00020e9c;
            }
          }
        }
        iVar8 = RandomByte2(param_1);
        uVar22 = (uint)*(byte *)(iVar7 + 0x49c);
        if (uVar22 != 0) {
          iVar18 = 0;
          do {
            __aeabi_idivmod(iVar18 + iVar8,uVar22);
            uVar19 = (uint)*(byte *)(iVar7 + extraout_r1_00 * 0x14);
            if (*(char *)((int)param_1 + 0x36b862) == '\0') {
LAB_00021f08:
              if ((((char)param_1[0xdae16] != '\x01') || (*(char *)(puVar17 + 0x144) != '\x01')) ||
                 (iVar23 = RadarChannelCheck(param_1), iVar23 == 0)) break;
              uVar22 = (uint)*(byte *)(iVar7 + 0x49c);
            }
            else if (*(byte *)((int)param_1 + 0x36b863) != uVar19) {
              pbVar12 = (byte *)((int)param_1 + 0x36b863);
              do {
                if (pbVar12 ==
                    (byte *)((int)param_1 +
                            (int)(&DAT_0036b863 + (byte)(*(char *)((int)param_1 + 0x36b862) - 1))))
                goto LAB_00021f08;
                pbVar12 = pbVar12 + 1;
              } while (*pbVar12 != uVar19);
            }
            iVar18 = iVar18 + 1;
          } while (iVar18 < (int)uVar22);
        }
        if (2 < DebugLevel) {
          printk("Rule 3 CCA value : Randomly Select ==> Select Channel %d\n",uVar19);
        }
        goto LAB_00020e9c;
      }
      if (-1 < DebugLevel) {
        printk("pAd->pChannelInfo equal NULL.\n");
      }
    }
    uVar19 = FirstChannel(param_1,piVar10);
    goto LAB_00020e9c;
  case 3:
    break;
  default:
    uVar3 = HcGetBandByWdev(param_3);
    piVar6 = (int *)HcGetAutoChCtrlbyBandIdx(param_1,uVar3);
    iVar18 = *piVar6;
    iVar7 = wlan_config_get_ht_bw(param_3);
    iVar8 = wlan_config_get_vht_bw(param_3);
    uVar9 = wlan_config_get_ch_band(param_3);
    local_70 = (undefined4 *)0x0;
    local_6c = 0;
    local_68 = 0;
    local_64 = (int *)0x0;
    if (2 < DebugLevel) {
      printk("[SelectClearChannelBusyTime] - cfg_ht_bw = %d vht_bw = %d\n",iVar7,iVar8);
    }
    if (iVar18 == 0) goto joined_r0x000215a8;
    if (DebugLevel < 1) {
      uVar19 = (uint)*(byte *)((int)piVar6 + 0xe);
      if (uVar19 != 0) {
LAB_00020acc:
        uVar22 = 0;
        uVar24 = 0;
        local_9c = "FALSE";
        iVar23 = DebugLevel;
        piVar10 = piVar6;
        puVar30 = (uint *)(iVar18 + 0x32c);
        do {
          if (0 < iVar23) {
            pcVar31 = local_9c;
            if (*(char *)((int)piVar10 + 0x7b) == '\x01') {
              pcVar31 = "TRUE";
            }
            pcVar37 = local_9c;
            if (*(char *)((int)piVar10 + 0x7a) == '\x01') {
              pcVar37 = "TRUE";
            }
            printk("Channel %3d : change Busy Time = %6u, ApCnt=%lu, Skip Channel = %s, BwCap = %s\n"
                   ,(char)piVar10[0x1d],*puVar30,*(undefined4 *)(*piVar6 + (uVar24 + 0x3c) * 4),
                   pcVar31,pcVar37);
            uVar19 = (uint)*(byte *)((int)piVar6 + 0xe);
            iVar23 = DebugLevel;
          }
          uVar24 = uVar24 + 1;
          piVar10 = piVar10 + 2;
          if (uVar22 < *puVar30) {
            uVar22 = *puVar30;
          }
          puVar30 = puVar30 + 1;
        } while (uVar24 < uVar19);
        if (uVar19 != 0) {
          uVar24 = 0;
          puVar30 = (uint *)(iVar18 + 0x32c);
          piVar10 = piVar6;
          do {
            pcVar31 = (char *)((int)piVar10 + 0x7b);
            uVar24 = uVar24 + 1;
            piVar10 = piVar10 + 2;
            if (*pcVar31 != '\0') {
              *puVar30 = *puVar30 + uVar22 * 2;
              uVar19 = (uint)*(byte *)((int)piVar6 + 0xe);
            }
            puVar30 = puVar30 + 1;
          } while (uVar24 < uVar19);
        }
        goto LAB_00020b64;
      }
    }
    else {
      printk("====================================================================\n");
      uVar19 = (uint)*(byte *)((int)piVar6 + 0xe);
      iVar23 = DebugLevel;
      if (uVar19 != 0) goto LAB_00020acc;
LAB_00020b64:
      if (0 < iVar23) {
        printk("====================================================================\n");
      }
    }
    uVar19 = *(uint *)(iVar18 + 0x32c);
    os_alloc_mem(param_1,&local_70,0xf0);
    if (local_70 == (undefined4 *)0x0) {
      uVar19 = 0;
      if (0 < DebugLevel) {
        printk("alloc buf for pSubGroupMaxBusyTimeTable failed!\n");
        puVar17 = local_70;
        goto LAB_00021dcc;
      }
LAB_00020e5c:
      if (local_6c != 0) {
        os_free_mem();
      }
    }
    else {
      os_alloc_mem(param_1,&local_6c,0xf0);
      if (local_6c != 0) {
        os_alloc_mem(param_1,&local_68,0xf0);
        if (local_68 == 0) {
          if (DebugLevel < 1) {
LAB_00021dec:
            uVar19 = 0;
            puVar17 = local_70;
          }
          else {
            printk("alloc buf for pSubGroupMinBusyTimeTable failed!\n");
            uVar19 = 0;
            puVar17 = local_70;
          }
        }
        else {
          os_alloc_mem(param_1,&local_64,0xf0);
          if (local_64 == (int *)0x0) {
            if (DebugLevel < 1) goto LAB_00021dec;
            printk("alloc buf for pSubGroupMinBusyTimeChIdxTable failed!\n");
            uVar19 = 0;
            puVar17 = local_70;
          }
          else {
            __memzero(local_70,0xf0);
            __memzero(local_6c,0xf0);
            __memzero(local_68,0xf0);
            __memzero(local_64,0xf0);
            uVar22 = (uint)*(byte *)((int)piVar6 + 0xe);
            if (1 < uVar22) {
              uVar24 = 0;
              puVar30 = (uint *)(iVar18 + 0x330);
              uVar34 = 0;
              uVar25 = 1;
              iVar18 = 0;
              piVar10 = piVar6;
              uVar13 = uVar19;
              do {
                if (*(char *)((int)piVar10 + 0x7e) == *(char *)((int)piVar10 + 0x76)) {
                  uVar33 = uVar25;
                  if (DebugLevel < 3) {
                    uVar14 = *puVar30;
                    uVar32 = uVar14;
                    if ((uVar14 <= uVar19) && (uVar32 = uVar19, uVar33 = uVar24, uVar14 < uVar13)) {
                      uVar34 = uVar25;
                      uVar13 = uVar14;
                    }
                  }
                  else {
                    printk("pChannelInfo->chanbusytime[%d] = %d, SubGroupMaxBusyTime = %d, SubGroupMinBusyTime = %d\n"
                           ,uVar25,*puVar30,uVar19,uVar13);
                    uVar22 = *puVar30;
                    uVar32 = uVar22;
                    if ((uVar22 <= uVar19) && (uVar32 = uVar19, uVar33 = uVar24, uVar22 < uVar13)) {
                      uVar34 = uVar25;
                      uVar13 = uVar22;
                    }
                    if (DebugLevel < 3) {
                      uVar22 = (uint)*(byte *)((int)piVar6 + 0xe);
                    }
                    else {
                      printk("SubGroupMaxBusyTime = %d, SubGroupMaxBusyTimeChIdx = %d,SubGroupMinBusyTime = %d SubGroupMinBusyTimeChIdx = %d\n"
                             ,uVar32,uVar33,uVar13,uVar34);
                      uVar22 = (uint)*(byte *)((int)piVar6 + 0xe);
                    }
                  }
                  iVar23 = iVar18;
                  uVar19 = uVar32;
                  uVar24 = uVar33;
                  if (uVar25 == uVar22 - 1) {
                    local_70[iVar18] = uVar32;
                    *(uint *)(local_6c + iVar18 * 4) = uVar33;
                    *(uint *)(local_68 + iVar18 * 4) = uVar13;
                    local_64[iVar18] = uVar34;
                    if (2 < DebugLevel) {
                      printk("SubGroupMaxBusyTimeTable[%d] = %d, SubGroupMaxBusyTimeChIdxTable[%d] = %d, SubGroupMinBusyTimeTable[%d] = %d, SubGroupMinBusyTimeChIdxTable[%d] = %d\n"
                             ,iVar18,local_70[iVar18],iVar18,*(undefined4 *)(local_6c + iVar18 * 4),
                             iVar18,*(undefined4 *)(local_68 + iVar18 * 4),iVar18,local_64[iVar18]);
                    }
                    iVar23 = iVar18 + 1;
                    uVar22 = (uint)*(byte *)((int)piVar6 + 0xe);
                  }
                }
                else {
                  local_70[iVar18] = uVar19;
                  *(uint *)(local_6c + iVar18 * 4) = uVar24;
                  *(uint *)(local_68 + iVar18 * 4) = uVar13;
                  local_64[iVar18] = uVar34;
                  if (2 < DebugLevel) {
                    printk("SubGroupMaxBusyTimeTable[%d] = %d, SubGroupMaxBusyTimeChIdxTable[%d] = %d, SubGroupMinBusyTimeTable[%d] = %d, SubGroupMinBusyTimeChIdxTable[%d] = %d\n"
                           ,iVar18,local_70[iVar18],iVar18,*(undefined4 *)(local_6c + iVar18 * 4),
                           iVar18,*(undefined4 *)(local_68 + iVar18 * 4),iVar18,local_64[iVar18]);
                  }
                  iVar23 = iVar18 + 1;
                  uVar22 = (uint)*(byte *)((int)piVar6 + 0xe);
                  if ((uVar25 == uVar22 - 1) && (*(char *)((int)piVar10 + 0x7f) == '\0')) {
                    iVar28 = iVar18 * 4 + 4;
                    local_70[iVar18 + 1] = *puVar30;
                    *(uint *)(local_6c + iVar28) = uVar25;
                    *(uint *)(local_68 + iVar28) = *puVar30;
                    local_64[iVar18 + 1] = uVar25;
                    if (2 < DebugLevel) {
                      printk("SubGroupMaxBusyTimeTable[%d] = %d, SubGroupMaxBusyTimeChIdxTable[%d] = %d, SubGroupMinBusyTimeTable[%d] = %d, SubGroupMinBusyTimeChIdxTable[%d] = %d\n"
                             ,iVar23,local_70[iVar18 + 1],iVar23,*(undefined4 *)(local_6c + iVar28),
                             iVar23,*(undefined4 *)(local_68 + iVar28),iVar23,local_64[iVar18 + 1]);
                    }
                    iVar23 = iVar18 + 2;
                    uVar22 = (uint)*(byte *)((int)piVar6 + 0xe);
                  }
                  else {
                    uVar19 = *puVar30;
                    uVar24 = uVar25;
                    uVar34 = uVar25;
                    uVar13 = uVar19;
                  }
                }
                uVar25 = uVar25 + 1;
                piVar10 = piVar10 + 2;
                puVar30 = puVar30 + 1;
                iVar18 = iVar23;
              } while (uVar25 < uVar22);
              if (iVar23 != 0) {
                iVar18 = 0;
                do {
                  if (2 < DebugLevel) {
                    printk("SubGroupMaxBusyTimeTable[%d] = %d, pSubGroupMaxBusyTimeChIdxTable[%d] = %d,\nSubGroupMinBusyTimeTable[%d] = %d, pSubGroupMinBusyTimeChIdxTable[%d] = %d\n"
                           ,iVar18,local_70[iVar18],iVar18,*(undefined4 *)(local_6c + iVar18 * 4),
                           iVar18,*(undefined4 *)(local_68 + iVar18 * 4),iVar18,local_64[iVar18]);
                  }
                  iVar18 = iVar18 + 1;
                } while (iVar18 != iVar23);
                iVar28 = 4;
                iVar18 = iVar23;
                do {
                  if (1 < iVar18) {
                    iVar15 = iVar28 + -4;
                    iVar11 = 1;
                    iVar20 = iVar28;
                    do {
                      iVar11 = iVar11 + 1;
                      uVar19 = *(uint *)((int)local_70 + iVar20);
                      if (uVar19 < *(uint *)((int)local_70 + iVar15)) {
                        *(uint *)((int)local_70 + iVar20) = *(uint *)((int)local_70 + iVar15);
                        *(uint *)((int)local_70 + iVar15) = uVar19;
                        uVar36 = *(undefined4 *)(local_6c + iVar20);
                        *(undefined4 *)(local_6c + iVar20) = *(undefined4 *)(local_6c + iVar15);
                        *(undefined4 *)(local_6c + iVar15) = uVar36;
                        uVar36 = *(undefined4 *)(local_68 + iVar20);
                        *(undefined4 *)(local_68 + iVar20) = *(undefined4 *)(local_68 + iVar15);
                        *(undefined4 *)(local_68 + iVar15) = uVar36;
                        uVar36 = *(undefined4 *)((int)local_64 + iVar20);
                        *(undefined4 *)((int)local_64 + iVar20) =
                             *(undefined4 *)((int)local_64 + iVar15);
                        *(undefined4 *)((int)local_64 + iVar15) = uVar36;
                      }
                      iVar20 = iVar20 + 4;
                    } while (iVar11 != iVar18);
                  }
                  iVar18 = iVar18 + -1;
                  iVar28 = iVar28 + 4;
                } while (iVar18 != 0);
                iVar18 = 0;
                puVar17 = local_70;
                do {
                  if (2 < DebugLevel) {
                    printk("SubGroupMaxBusyTimeTable[%d] = %d, pSubGroupMaxBusyTimeChIdxTable[%d] = %d,\nSubGroupMinBusyTimeTable[%d] = %d, pSubGroupMinBusyTimeChIdxTable[%d] = %d\n"
                           ,iVar18,puVar17[iVar18],iVar18,*(undefined4 *)(local_6c + iVar18 * 4),
                           iVar18,*(undefined4 *)(local_68 + iVar18 * 4),iVar18,local_64[iVar18]);
                    puVar17 = local_70;
                  }
                  iVar18 = iVar18 + 1;
                } while (iVar18 < iVar23);
                if ((iVar23 < 3 || (iVar7 != 1 || iVar8 != 3)) ||
                   ((*(ushort *)(param_3 + 0x18) & 0x20) == 0)) {
                  uVar9 = *puVar17;
                  iVar7 = *local_64;
                  uVar19 = (uint)*(byte *)(piVar6 + iVar7 * 2 + 0x1d);
                  if ((0 < DebugLevel) &&
                     ((printk("Rule 3 Channel Busy time value : Select Primary Channel %d\n",uVar19)
                      , puVar17 = local_70, 0 < DebugLevel &&
                      (printk("Rule 3 Channel Busy time value : Min Channel Busy = %u\n",uVar9),
                      puVar17 = local_70, 0 < DebugLevel)))) {
                    cVar2 = *(char *)((int)piVar6 + iVar7 * 8 + 0x77);
                    if (cVar2 == '\x03') {
                      puVar21 = &_LC11;
                    }
                    else if (cVar2 == '\x02') {
                      puVar21 = &_LC12;
                    }
                    else {
                      puVar21 = &_LC9;
                      if (cVar2 != '\x01') {
                        puVar21 = &_LC10;
                      }
                    }
                    printk("Rule 3 Channel Busy time value : BW = %s\n",puVar21);
                    puVar17 = local_70;
                  }
                }
                else {
                  uVar26 = *puVar17;
                  uVar36 = puVar17[1];
                  uVar19 = (uint)*(byte *)(piVar6 + *local_64 * 2 + 0x1d);
                  uVar9 = vht_cent_ch_freq((char)piVar6[*(int *)(local_6c + 4) * 2 + 0x1d],1,uVar9);
                  iVar7 = DebugLevel;
                  *(char *)(param_3 + 0x3fe1) = (char)uVar9;
                  puVar17 = local_70;
                  if ((((0 < iVar7) &&
                       (printk("Rule 3 Channel Busy time value : Select Primary Channel %d\n",uVar19
                              ), puVar17 = local_70, 0 < DebugLevel)) &&
                      (printk("Rule 3 Channel Busy time value : Select Secondary Central Channel %d\n"
                              ,uVar9), puVar17 = local_70, 0 < DebugLevel)) &&
                     ((printk("Rule 3 Channel Busy time value : Min Channel Busy = %u\n",uVar26),
                      puVar17 = local_70, 0 < DebugLevel &&
                      (printk("Rule 3 Channel Busy time value : MinorMin Channel Busy = %u\n",uVar36
                             ), puVar17 = local_70, 0 < DebugLevel)))) {
                    printk("Rule 3 Channel Busy time value : BW = %s\n","80+80");
                    puVar17 = local_70;
                  }
                }
                goto LAB_00021dcc;
              }
            }
            iVar7 = RandomByte2(param_1);
            uVar22 = (uint)*(byte *)((int)piVar6 + 0xe);
            if (uVar22 == 0) {
              uVar19 = 0;
            }
            else {
              uVar24 = 0;
              do {
                __aeabi_uidivmod(iVar7 + uVar24,uVar22);
                uVar19 = (uint)*(byte *)(piVar6 + extraout_r1_01 * 2 + 0x1d);
                if (*(char *)((int)param_1 + 0x36b862) == '\0') {
LAB_000223a4:
                  if ((((char)param_1[0xdae16] != '\x01') || ((char)piVar6[5] != '\x01')) ||
                     (iVar8 = RadarChannelCheck(param_1,uVar19), iVar8 == 0)) break;
                  uVar22 = (uint)*(byte *)((int)piVar6 + 0xe);
                }
                else if (*(byte *)((int)param_1 + 0x36b863) != uVar19) {
                  pbVar12 = (byte *)((int)param_1 + 0x36b863);
                  do {
                    if (pbVar12 ==
                        (byte *)((int)param_1 +
                                (int)(&DAT_0036b863 + (byte)(*(char *)((int)param_1 + 0x36b862) - 1)
                                     ))) goto LAB_000223a4;
                    pbVar12 = pbVar12 + 1;
                  } while (*pbVar12 != uVar19);
                }
                uVar24 = uVar24 + 1;
              } while (uVar24 < uVar22);
            }
            puVar17 = local_70;
            if (0 < DebugLevel) {
              printk("Randomly Select : Select Channel %d\n",uVar19);
              puVar17 = local_70;
            }
          }
        }
LAB_00021dcc:
        if (puVar17 != (undefined4 *)0x0) {
LAB_00021dd4:
          os_free_mem();
        }
        goto LAB_00020e5c;
      }
      uVar19 = 0;
      if (0 < DebugLevel) {
        printk("alloc buf for pSubGroupMaxBusyTimeChIdxTable failed!\n");
        puVar17 = local_70;
        goto LAB_00021dcc;
      }
      if (local_70 != (undefined4 *)0x0) goto LAB_00021dd4;
      uVar19 = 0;
    }
    if (local_68 != 0) {
      os_free_mem();
    }
    if (local_64 != (int *)0x0) {
      os_free_mem();
    }
    if (0 < DebugLevel) {
      printk("SelectClearChannelBusyTime[%d]:Select Channel %d\n",uVar3,uVar19);
    }
    goto LAB_00020e9c;
  }
  uVar3 = HcGetBandByWdev(param_3);
  piVar6 = (int *)HcGetAutoChCtrlbyBandIdx(param_1,uVar3);
  iVar18 = *piVar6;
  iVar7 = wlan_config_get_ht_bw(param_3);
  iVar8 = wlan_config_get_vht_bw(param_3);
  uVar9 = wlan_config_get_ch_band(param_3);
  local_70 = (undefined4 *)0x0;
  local_6c = 0;
  local_68 = 0;
  local_64 = (int *)0x0;
  if (2 < DebugLevel) {
    printk("[SelectClearChannelBusyTime] - cfg_ht_bw = %d vht_bw = %d\n",iVar7,iVar8);
  }
  if (iVar18 == 0) goto joined_r0x000215a8;
  if (DebugLevel < 1) {
    uVar19 = (uint)*(byte *)((int)piVar6 + 0xe);
    if (uVar19 != 0) {
LAB_0001fe90:
      uVar22 = 0;
      uVar24 = 0;
      local_9c = "FALSE";
      iVar23 = DebugLevel;
      piVar10 = piVar6;
      puVar30 = (uint *)(iVar18 + 0x32c);
      do {
        if (0 < iVar23) {
          pcVar31 = local_9c;
          if (*(char *)((int)piVar10 + 0x7b) == '\x01') {
            pcVar31 = "TRUE";
          }
          pcVar37 = local_9c;
          if (*(char *)((int)piVar10 + 0x7a) == '\x01') {
            pcVar37 = "TRUE";
          }
          printk("Channel %3d : change Busy Time = %6u, ApCnt=%lu, Skip Channel = %s, BwCap = %s\n",
                 (char)piVar10[0x1d],*puVar30,*(undefined4 *)(*piVar6 + (uVar24 + 0x3c) * 4),pcVar31
                 ,pcVar37);
          uVar19 = (uint)*(byte *)((int)piVar6 + 0xe);
          iVar23 = DebugLevel;
        }
        uVar24 = uVar24 + 1;
        piVar10 = piVar10 + 2;
        if (uVar22 < *puVar30) {
          uVar22 = *puVar30;
        }
        puVar30 = puVar30 + 1;
      } while (uVar24 < uVar19);
      if (uVar19 != 0) {
        uVar24 = 0;
        piVar10 = piVar6;
        puVar30 = (uint *)(iVar18 + 0x32c);
        do {
          pcVar31 = (char *)((int)piVar10 + 0x7b);
          uVar24 = uVar24 + 1;
          piVar10 = piVar10 + 2;
          if (*pcVar31 != '\0') {
            *puVar30 = *puVar30 + uVar22 * 2;
            uVar19 = (uint)*(byte *)((int)piVar6 + 0xe);
          }
          puVar30 = puVar30 + 1;
        } while (uVar24 < uVar19);
      }
      goto LAB_0001ff24;
    }
  }
  else {
    printk("====================================================================\n");
    uVar19 = (uint)*(byte *)((int)piVar6 + 0xe);
    iVar23 = DebugLevel;
    if (uVar19 != 0) goto LAB_0001fe90;
LAB_0001ff24:
    if (0 < iVar23) {
      printk("====================================================================\n");
    }
  }
  uVar19 = *(uint *)(iVar18 + 0x32c);
  os_alloc_mem(param_1,&local_70,0xf0);
  if (local_70 == (undefined4 *)0x0) {
    uVar19 = 0;
    if (0 < DebugLevel) {
      printk("alloc buf for pSubGroupMaxBusyTimeTable failed!\n");
      puVar17 = local_70;
      goto LAB_000215d8;
    }
LAB_00020ecc:
    if (local_6c != 0) {
      os_free_mem();
    }
  }
  else {
    os_alloc_mem(param_1,&local_6c,0xf0);
    if (local_6c != 0) {
      os_alloc_mem(param_1,&local_68,0xf0);
      if (local_68 == 0) {
        if (DebugLevel < 1) {
LAB_000215cc:
          uVar19 = 0;
          puVar17 = local_70;
        }
        else {
          printk("alloc buf for pSubGroupMinBusyTimeTable failed!\n");
          uVar19 = 0;
          puVar17 = local_70;
        }
      }
      else {
        os_alloc_mem(param_1,&local_64,0xf0);
        if (local_64 == (int *)0x0) {
          if (DebugLevel < 1) goto LAB_000215cc;
          printk("alloc buf for pSubGroupMinBusyTimeChIdxTable failed!\n");
          uVar19 = 0;
          puVar17 = local_70;
        }
        else {
          __memzero(local_70,0xf0);
          __memzero(local_6c,0xf0);
          __memzero(local_68,0xf0);
          __memzero(local_64,0xf0);
          uVar22 = (uint)*(byte *)((int)piVar6 + 0xe);
          if (1 < uVar22) {
            uVar24 = 0;
            puVar30 = (uint *)(iVar18 + 0x330);
            uVar34 = 0;
            uVar25 = 1;
            iVar18 = 0;
            piVar10 = piVar6;
            uVar13 = uVar19;
            do {
              if (*(char *)((int)piVar10 + 0x7e) == *(char *)((int)piVar10 + 0x76)) {
                uVar33 = uVar25;
                if (DebugLevel < 3) {
                  uVar14 = *puVar30;
                  uVar32 = uVar14;
                  if ((uVar14 <= uVar19) && (uVar32 = uVar19, uVar33 = uVar24, uVar14 < uVar13)) {
                    uVar34 = uVar25;
                    uVar13 = uVar14;
                  }
                }
                else {
                  printk("pChannelInfo->chanbusytime[%d] = %d, SubGroupMaxBusyTime = %d, SubGroupMinBusyTime = %d\n"
                         ,uVar25,*puVar30,uVar19,uVar13);
                  uVar22 = *puVar30;
                  uVar32 = uVar22;
                  if ((uVar22 <= uVar19) && (uVar32 = uVar19, uVar33 = uVar24, uVar22 < uVar13)) {
                    uVar34 = uVar25;
                    uVar13 = uVar22;
                  }
                  if (DebugLevel < 3) {
                    uVar22 = (uint)*(byte *)((int)piVar6 + 0xe);
                  }
                  else {
                    printk("SubGroupMaxBusyTime = %d, SubGroupMaxBusyTimeChIdx = %d,SubGroupMinBusyTime = %d SubGroupMinBusyTimeChIdx = %d\n"
                           ,uVar32,uVar33,uVar13,uVar34);
                    uVar22 = (uint)*(byte *)((int)piVar6 + 0xe);
                  }
                }
                iVar23 = iVar18;
                uVar19 = uVar32;
                uVar24 = uVar33;
                if (uVar25 == uVar22 - 1) {
                  local_70[iVar18] = uVar32;
                  *(uint *)(local_6c + iVar18 * 4) = uVar33;
                  *(uint *)(local_68 + iVar18 * 4) = uVar13;
                  local_64[iVar18] = uVar34;
                  if (2 < DebugLevel) {
                    printk("SubGroupMaxBusyTimeTable[%d] = %d, SubGroupMaxBusyTimeChIdxTable[%d] = %d, SubGroupMinBusyTimeTable[%d] = %d, SubGroupMinBusyTimeChIdxTable[%d] = %d\n"
                           ,iVar18,local_70[iVar18],iVar18,*(undefined4 *)(local_6c + iVar18 * 4),
                           iVar18,*(undefined4 *)(local_68 + iVar18 * 4),iVar18,local_64[iVar18]);
                  }
                  iVar23 = iVar18 + 1;
                  uVar22 = (uint)*(byte *)((int)piVar6 + 0xe);
                }
              }
              else {
                local_70[iVar18] = uVar19;
                *(uint *)(local_6c + iVar18 * 4) = uVar24;
                *(uint *)(local_68 + iVar18 * 4) = uVar13;
                local_64[iVar18] = uVar34;
                if (2 < DebugLevel) {
                  printk("SubGroupMaxBusyTimeTable[%d] = %d, SubGroupMaxBusyTimeChIdxTable[%d] = %d, SubGroupMinBusyTimeTable[%d] = %d, SubGroupMinBusyTimeChIdxTable[%d] = %d\n"
                         ,iVar18,local_70[iVar18],iVar18,*(undefined4 *)(local_6c + iVar18 * 4),
                         iVar18,*(undefined4 *)(local_68 + iVar18 * 4),iVar18,local_64[iVar18]);
                }
                iVar23 = iVar18 + 1;
                uVar22 = (uint)*(byte *)((int)piVar6 + 0xe);
                if ((uVar25 == uVar22 - 1) && (*(char *)((int)piVar10 + 0x7f) == '\0')) {
                  iVar28 = iVar18 * 4 + 4;
                  local_70[iVar18 + 1] = *puVar30;
                  *(uint *)(local_6c + iVar28) = uVar25;
                  *(uint *)(local_68 + iVar28) = *puVar30;
                  local_64[iVar18 + 1] = uVar25;
                  if (2 < DebugLevel) {
                    printk("SubGroupMaxBusyTimeTable[%d] = %d, SubGroupMaxBusyTimeChIdxTable[%d] = %d, SubGroupMinBusyTimeTable[%d] = %d, SubGroupMinBusyTimeChIdxTable[%d] = %d\n"
                           ,iVar23,local_70[iVar18 + 1],iVar23,*(undefined4 *)(local_6c + iVar28),
                           iVar23,*(undefined4 *)(local_68 + iVar28),iVar23,local_64[iVar18 + 1]);
                  }
                  iVar23 = iVar18 + 2;
                  uVar22 = (uint)*(byte *)((int)piVar6 + 0xe);
                }
                else {
                  uVar19 = *puVar30;
                  uVar24 = uVar25;
                  uVar34 = uVar25;
                  uVar13 = uVar19;
                }
              }
              uVar25 = uVar25 + 1;
              piVar10 = piVar10 + 2;
              puVar30 = puVar30 + 1;
              iVar18 = iVar23;
            } while (uVar25 < uVar22);
            if (iVar23 != 0) {
              iVar18 = 0;
              do {
                if (2 < DebugLevel) {
                  printk("SubGroupMaxBusyTimeTable[%d] = %d, pSubGroupMaxBusyTimeChIdxTable[%d] = %d,\nSubGroupMinBusyTimeTable[%d] = %d, pSubGroupMinBusyTimeChIdxTable[%d] = %d\n"
                         ,iVar18,local_70[iVar18],iVar18,*(undefined4 *)(local_6c + iVar18 * 4),
                         iVar18,*(undefined4 *)(local_68 + iVar18 * 4),iVar18,local_64[iVar18]);
                }
                iVar18 = iVar18 + 1;
              } while (iVar18 != iVar23);
              iVar28 = 4;
              iVar18 = iVar23;
              do {
                if (1 < iVar18) {
                  iVar15 = iVar28 + -4;
                  iVar11 = 1;
                  iVar20 = iVar28;
                  do {
                    iVar11 = iVar11 + 1;
                    uVar19 = *(uint *)((int)local_70 + iVar20);
                    if (uVar19 < *(uint *)((int)local_70 + iVar15)) {
                      *(uint *)((int)local_70 + iVar20) = *(uint *)((int)local_70 + iVar15);
                      *(uint *)((int)local_70 + iVar15) = uVar19;
                      uVar36 = *(undefined4 *)(local_6c + iVar20);
                      *(undefined4 *)(local_6c + iVar20) = *(undefined4 *)(local_6c + iVar15);
                      *(undefined4 *)(local_6c + iVar15) = uVar36;
                      uVar36 = *(undefined4 *)(local_68 + iVar20);
                      *(undefined4 *)(local_68 + iVar20) = *(undefined4 *)(local_68 + iVar15);
                      *(undefined4 *)(local_68 + iVar15) = uVar36;
                      uVar36 = *(undefined4 *)((int)local_64 + iVar20);
                      *(undefined4 *)((int)local_64 + iVar20) =
                           *(undefined4 *)((int)local_64 + iVar15);
                      *(undefined4 *)((int)local_64 + iVar15) = uVar36;
                    }
                    iVar20 = iVar20 + 4;
                  } while (iVar11 != iVar18);
                }
                iVar18 = iVar18 + -1;
                iVar28 = iVar28 + 4;
              } while (iVar18 != 0);
              iVar18 = 0;
              puVar17 = local_70;
              do {
                if (2 < DebugLevel) {
                  printk("SubGroupMaxBusyTimeTable[%d] = %d, pSubGroupMaxBusyTimeChIdxTable[%d] = %d,\nSubGroupMinBusyTimeTable[%d] = %d, pSubGroupMinBusyTimeChIdxTable[%d] = %d\n"
                         ,iVar18,puVar17[iVar18],iVar18,*(undefined4 *)(local_6c + iVar18 * 4),
                         iVar18,*(undefined4 *)(local_68 + iVar18 * 4),iVar18,local_64[iVar18]);
                  puVar17 = local_70;
                }
                iVar18 = iVar18 + 1;
              } while (iVar18 < iVar23);
              if ((iVar23 < 3 || (iVar7 != 1 || iVar8 != 3)) ||
                 ((*(ushort *)(param_3 + 0x18) & 0x20) == 0)) {
                uVar9 = *puVar17;
                iVar7 = *local_64;
                uVar19 = (uint)*(byte *)(piVar6 + iVar7 * 2 + 0x1d);
                if ((0 < DebugLevel) &&
                   ((printk("Rule 3 Channel Busy time value : Select Primary Channel %d\n",uVar19),
                    puVar17 = local_70, 0 < DebugLevel &&
                    (printk("Rule 3 Channel Busy time value : Min Channel Busy = %u\n",uVar9),
                    puVar17 = local_70, 0 < DebugLevel)))) {
                  cVar2 = *(char *)((int)piVar6 + iVar7 * 8 + 0x77);
                  if (cVar2 == '\x03') {
                    puVar21 = &_LC11;
                  }
                  else if (cVar2 == '\x02') {
                    puVar21 = &_LC12;
                  }
                  else {
                    puVar21 = &_LC9;
                    if (cVar2 != '\x01') {
                      puVar21 = &_LC10;
                    }
                  }
                  printk("Rule 3 Channel Busy time value : BW = %s\n",puVar21);
                  puVar17 = local_70;
                }
              }
              else {
                uVar26 = *puVar17;
                uVar36 = puVar17[1];
                uVar19 = (uint)*(byte *)(piVar6 + *local_64 * 2 + 0x1d);
                uVar9 = vht_cent_ch_freq((char)piVar6[*(int *)(local_6c + 4) * 2 + 0x1d],1,uVar9);
                iVar7 = DebugLevel;
                *(char *)(param_3 + 0x3fe1) = (char)uVar9;
                puVar17 = local_70;
                if ((((0 < iVar7) &&
                     (printk("Rule 3 Channel Busy time value : Select Primary Channel %d\n",uVar19),
                     puVar17 = local_70, 0 < DebugLevel)) &&
                    (printk("Rule 3 Channel Busy time value : Select Secondary Central Channel %d\n"
                            ,uVar9), puVar17 = local_70, 0 < DebugLevel)) &&
                   ((printk("Rule 3 Channel Busy time value : Min Channel Busy = %u\n",uVar26),
                    puVar17 = local_70, 0 < DebugLevel &&
                    (printk("Rule 3 Channel Busy time value : MinorMin Channel Busy = %u\n",uVar36),
                    puVar17 = local_70, 0 < DebugLevel)))) {
                  printk("Rule 3 Channel Busy time value : BW = %s\n","80+80");
                  puVar17 = local_70;
                }
              }
              goto LAB_000215d8;
            }
          }
          iVar7 = RandomByte2(param_1);
          uVar22 = (uint)*(byte *)((int)piVar6 + 0xe);
          if (uVar22 == 0) {
            uVar19 = 0;
          }
          else {
            uVar24 = 0;
            do {
              __aeabi_uidivmod(iVar7 + uVar24,uVar22);
              uVar19 = (uint)*(byte *)(piVar6 + extraout_r1_02 * 2 + 0x1d);
              if (*(char *)((int)param_1 + 0x36b862) == '\0') {
LAB_000225d8:
                if ((((char)param_1[0xdae16] != '\x01') || ((char)piVar6[5] != '\x01')) ||
                   (iVar8 = RadarChannelCheck(param_1,uVar19), iVar8 == 0)) break;
                uVar22 = (uint)*(byte *)((int)piVar6 + 0xe);
              }
              else if (*(byte *)((int)param_1 + 0x36b863) != uVar19) {
                pbVar12 = (byte *)((int)param_1 + 0x36b863);
                do {
                  if (pbVar12 ==
                      (byte *)((int)param_1 +
                              (int)(&DAT_0036b863 + (byte)(*(char *)((int)param_1 + 0x36b862) - 1)))
                     ) goto LAB_000225d8;
                  pbVar12 = pbVar12 + 1;
                } while (*pbVar12 != uVar19);
              }
              uVar24 = uVar24 + 1;
            } while (uVar24 < uVar22);
          }
          puVar17 = local_70;
          if (0 < DebugLevel) {
            printk("Randomly Select : Select Channel %d\n",uVar19);
            puVar17 = local_70;
          }
        }
      }
LAB_000215d8:
      if (puVar17 != (undefined4 *)0x0) {
LAB_000215e0:
        os_free_mem();
      }
      goto LAB_00020ecc;
    }
    uVar19 = 0;
    if (0 < DebugLevel) {
      printk("alloc buf for pSubGroupMaxBusyTimeChIdxTable failed!\n");
      puVar17 = local_70;
      goto LAB_000215d8;
    }
    if (local_70 != (undefined4 *)0x0) goto LAB_000215e0;
    uVar19 = 0;
  }
  if (local_68 != 0) {
    os_free_mem();
  }
  if (local_64 != (int *)0x0) {
    os_free_mem();
  }
  if (0 < DebugLevel) {
    printk("SelectClearChannelBusyTime[%d]:Select Channel %d\n",uVar3,uVar19);
  }
LAB_00020e9c:
  *(char *)(iVar4 + 0xd) = (char)uVar19;
  *(undefined4 *)(iVar4 + 0x10) = 1;
  return uVar19;
}

