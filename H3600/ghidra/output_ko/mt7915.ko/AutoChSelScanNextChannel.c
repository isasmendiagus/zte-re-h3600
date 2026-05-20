// module: mt7915.ko
// function: AutoChSelScanNextChannel @ 0x24478
// size: 7836 bytes
//

void AutoChSelScanNextChannel(int *param_1,int param_2)

{
  byte *pbVar1;
  char cVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int *piVar8;
  int iVar9;
  int *piVar10;
  int iVar11;
  undefined4 uVar12;
  byte *pbVar13;
  uint uVar14;
  int *piVar15;
  uint uVar16;
  uint extraout_r1;
  int iVar17;
  int extraout_r1_00;
  byte *pbVar18;
  int extraout_r1_01;
  uint extraout_r1_02;
  uint extraout_r1_03;
  uint extraout_r1_04;
  char *pcVar19;
  uint uVar20;
  uint *extraout_r2;
  uint *puVar21;
  uint *extraout_r2_00;
  int iVar22;
  byte bVar23;
  uint uVar24;
  int iVar25;
  int iVar26;
  char *pcVar27;
  uint uVar28;
  uint uVar29;
  int iVar30;
  uint uVar31;
  undefined4 uVar32;
  uint uVar33;
  uint uVar34;
  uint uVar35;
  int iVar36;
  byte *pbVar37;
  uint *puVar38;
  undefined4 uVar39;
  int iVar40;
  uint uVar41;
  undefined4 *puVar42;
  undefined4 uVar43;
  int *piVar44;
  bool bVar45;
  bool bVar46;
  uint local_d8;
  uint uStack_d4;
  char *local_d0;
  int local_c0;
  uint local_b4;
  uint local_98;
  uint uStack_94;
  int local_90;
  int local_8c;
  int local_84;
  undefined4 *local_80;
  int local_7c;
  uint local_78 [5];
  int *local_64 [16];
  
  iVar7 = HcGetBandByWdev(param_2);
  piVar8 = (int *)HcGetAutoChCtrlbyBandIdx(param_1,iVar7);
  bVar23 = *(byte *)(piVar8 + 3);
  uVar28 = (uint)bVar23;
  if (2 < DebugLevel) {
    printk("%s----------------->\n","AutoChSelScanNextChannel");
  }
  iVar9 = HcGetQloadCtrl(param_1);
  if (*(char *)(iVar9 + 0xc0) == '\x01') {
    uVar32 = 400;
  }
  else {
    uVar32 = 200;
  }
  if ((char)piVar8[3] != -1) {
    piVar8[0x16] = 1;
    *(byte *)((int)param_1 + 0x36b861) = bVar23;
    if (0x3b < uVar28) {
      return;
    }
    *(char *)(param_1 + 0xdae18) = (char)piVar8[uVar28 * 2 + 0x1d];
    wlan_operate_scan(param_2,(char)piVar8[uVar28 * 2 + 0x1d]);
    AsicGetChBusyCnt(param_1,iVar7,0,0);
    *(undefined4 *)(*piVar8 + 0x50c) = uVar32;
    RTMPSetTimer(piVar8 + 6,uVar32);
    goto LAB_00024560;
  }
  if (param_1[iVar7 + 0xdae0a] == 4) {
    memset(local_64,0,0x3c);
    uVar32 = HcGetBandByWdev(param_2);
    piVar10 = (int *)HcGetAutoChCtrlbyBandIdx(param_1,uVar32);
    if (2 < DebugLevel) {
      printk("----->%s\n","SelectClearChannelBusyTimeOptimization");
    }
    iVar9 = *piVar10;
    if (iVar9 == 0) {
      if (-1 < DebugLevel) {
        printk("pChannelInfo equal NULL.\n");
      }
LAB_000251bc:
      uVar29 = FirstChannel(param_1,param_2);
      goto LAB_000251f0;
    }
    pbVar18 = (byte *)piVar10[1];
    if (pbVar18 == (byte *)0x0) {
      if (-1 < DebugLevel) {
        printk("auto_ch_ctrl->pBssInfoTab equal NULL.\n");
      }
      goto LAB_000251bc;
    }
    if (*pbVar18 != 0) {
      local_c0 = 0;
      pbVar37 = pbVar18;
      do {
        bVar23 = pbVar37[0x28];
        pbVar13 = (byte *)hc_get_channel_ctrl(param_1[0x29e5e8],uVar32);
        uVar28 = (uint)pbVar13[0x49c];
        if (uVar28 == 0) {
          uVar41 = 1;
          uVar35 = 1;
          uVar33 = 0xffffffff;
          uVar29 = 0;
          uVar24 = uVar28;
LAB_000249b0:
          bVar23 = pbVar37[0x2a];
          if (-0x33 < (char)bVar23) goto LAB_000249c0;
LAB_00024f58:
          iVar11 = *(int *)(iVar9 + uVar24 * 4);
          if ((char)bVar23 < -0x4f) {
            iVar11 = iVar11 + 0x1e;
          }
          else {
            iVar11 = iVar11 + 0x28;
          }
          *(int *)(iVar9 + uVar24 * 4) = iVar11;
        }
        else {
          if (*pbVar13 == bVar23) {
            uVar35 = 1;
            uVar29 = 0;
            uVar33 = 0xffffffff;
            uVar24 = uVar29;
            uVar41 = uVar35;
            goto LAB_000249b0;
          }
          uVar24 = 0;
          do {
            uVar33 = uVar24;
            uVar24 = uVar33 + 1;
            if (uVar24 == uVar28) {
              uVar35 = uVar28 + 1;
              uVar33 = uVar28 - 1;
              uVar29 = (uint)(0x3a < uVar35);
              if (uVar33 == 0xffffffff) {
                uVar24 = uVar28;
                uVar41 = 1;
              }
              else {
                uVar24 = uVar28;
                uVar41 = 0;
              }
              goto LAB_000249b0;
            }
            pbVar13 = pbVar13 + 0x14;
          } while (*pbVar13 != bVar23);
          uVar35 = uVar33 + 2;
          bVar23 = pbVar37[0x2a];
          uVar29 = (uint)(0x3a < (int)uVar35);
          uVar41 = (uint)(uVar33 == 0xffffffff);
          if ((char)bVar23 < -0x32) goto LAB_00024f58;
LAB_000249c0:
          iVar11 = *(int *)(iVar9 + uVar24 * 4) + 0x32;
          *(int *)(iVar9 + uVar24 * 4) = iVar11;
        }
        local_d0 = (char *)(uVar24 * 4);
        *(int *)(iVar9 + uVar24 * 4) = iVar11 + 0x28;
        if (pbVar37[0x29] == 1) {
          if (*(char *)(iVar9 + 0x510) == '\0') {
            uVar28 = uVar24 + 8;
            iVar11 = 4;
            bVar45 = (int)uVar28 < (int)uVar35;
          }
          else {
            uVar28 = uVar24 + 2;
            bVar45 = (int)uVar28 < (int)uVar35;
            iVar11 = 1;
          }
        }
        else {
          uVar28 = uVar35;
          if (pbVar37[0x29] == 3) {
            if (*(char *)(iVar9 + 0x510) == '\0') {
              iVar11 = 8;
              bVar45 = (int)(uVar24 + 4) < (int)uVar35;
              uVar28 = uVar24 + 4;
            }
            else {
              bVar45 = false;
              iVar11 = 2;
            }
          }
          else if (*(char *)(iVar9 + 0x510) == '\0') {
            uVar28 = uVar24 + 4;
            iVar11 = 4;
            bVar45 = (int)uVar28 < (int)uVar35;
          }
          else {
            bVar45 = false;
            iVar11 = 1;
          }
        }
        if ((!bVar45 && uVar29 == 0) &&
           ((int)((uint)*(byte *)(piVar10 + uVar35 * 2 + 0x1d) -
                 (uint)*(byte *)(piVar10 + uVar24 * 2 + 0x1d)) < 5)) {
          piVar44 = (int *)(iVar9 + (uVar35 + 0x3fffffff) * 4);
          iVar40 = ((uVar24 - uVar35) + 9) * 4;
          piVar15 = piVar10 + uVar35 * 2;
          do {
            piVar44 = piVar44 + 1;
            uVar29 = uVar35 + 1;
            bVar46 = SBORROW4(uVar29,0x3a);
            iVar30 = uVar35 - 0x39;
            bVar45 = uVar29 == 0x3a;
            if ((int)uVar29 < 0x3b) {
              bVar46 = SBORROW4(uVar29,uVar28);
              iVar30 = uVar29 - uVar28;
              bVar45 = uVar29 == uVar28;
            }
            iVar36 = *piVar44 + iVar40;
            iVar40 = iVar40 + -4;
            *piVar44 = iVar36;
          } while ((bVar45 || iVar30 < 0 != bVar46) &&
                  (pbVar13 = (byte *)(piVar15 + 0x1f), pbVar1 = (byte *)(piVar15 + 0x1d),
                  uVar35 = uVar29, piVar15 = piVar15 + 2, (int)((uint)*pbVar13 - (uint)*pbVar1) < 5)
                  );
        }
        if ((int)uVar33 < (int)(uVar24 - iVar11)) {
          uVar41 = 1;
        }
        if (uVar41 == 0) {
          piVar44 = piVar10 + uVar33 * 2;
          piVar15 = (int *)(iVar9 + uVar33 * 4);
          do {
            pbVar13 = (byte *)(piVar44 + 0x1f);
            uVar33 = uVar33 - 1;
            pbVar1 = (byte *)(piVar44 + 0x1d);
            piVar44 = piVar44 + -2;
            if ((int)((uint)*pbVar13 - (uint)*pbVar1) < 5) {
              *piVar15 = (int)piVar15 + *piVar15 + (0x24 - (iVar9 + (int)local_d0));
            }
            piVar15 = piVar15 + -1;
          } while ((int)(uVar24 - iVar11) <= (int)uVar33 && uVar33 != 0xffffffff);
        }
        pbVar37 = pbVar37 + 0x2a;
        *(byte *)((int)local_64 + uVar24) = *pbVar37;
        local_c0 = local_c0 + 1;
      } while (local_c0 < (int)(uint)*pbVar18);
    }
    if ((*(int *)(*param_1 + 0x38) - 0x100U & 0xfffffeff) == 0) {
      uVar32 = HcGetBandByWdev(param_1 + *(int *)(*param_1 + 0x3c) * 0x160d + 0xadc92);
      iVar11 = hc_get_channel_ctrl(param_1[0x29e5e8],uVar32);
      piVar15 = (int *)HcGetAutoChCtrlbyBandIdx(param_1,uVar32);
      if (*(char *)((int)param_1 + 0x36b862) != '\0') {
        uVar28 = 0;
        do {
          cVar2 = (&DAT_0036b863)[(int)param_1 + uVar28];
          pcVar27 = (char *)hc_get_channel_ctrl(param_1[0x29e5e8],uVar32);
          uVar35 = (uint)(byte)pcVar27[0x49c];
          uVar29 = uVar35;
          if (uVar35 != 0) {
            if (*pcVar27 == cVar2) {
              uVar35 = 0;
              uVar29 = 0;
            }
            else {
              uVar24 = 0;
              do {
                uVar24 = uVar24 + 1;
                if (uVar24 == uVar35) goto LAB_00025868;
                pcVar27 = pcVar27 + 0x14;
              } while (*pcVar27 != cVar2);
              uVar35 = uVar24 & 0xff;
              uVar29 = uVar24;
            }
          }
LAB_00025868:
          uVar28 = uVar28 + 1 & 0xff;
          if (*(byte *)(iVar11 + 0x49c) != uVar35) {
            *(undefined1 *)(*piVar15 + (uVar29 & 0xff) + 0x2d0) = 1;
          }
        } while (uVar28 < *(byte *)((int)param_1 + 0x36b862));
      }
    }
    if (DebugLevel < 0) {
      uVar28 = (uint)*(byte *)((int)piVar10 + 0xe);
      if (uVar28 != 0) {
LAB_00024b74:
        pcVar27 = (char *)(iVar9 + 0x2d0);
        iVar40 = 0;
        local_84 = 0;
        iVar11 = DebugLevel;
        piVar15 = (int *)(iVar9 + 0xf0);
        piVar44 = piVar10;
        do {
          if (-1 < iVar11) {
            pcVar19 = "TRUE";
            if (*pcVar27 != '\x01') {
              pcVar19 = "FALSE";
            }
            printk("[Id %d] Channel %d : Busy Time = %u, False CCA = %u, AP Count = %lu, Dirty = %lu, RSSI = %d, Skip Channel = %s\n"
                   ,iVar40,(char)piVar44[0x1d],piVar15[0x8f],piVar15[0x3c],*piVar15,piVar15[-0x3c],
                   (int)*(char *)((int)local_64 + iVar40),pcVar19);
            uVar28 = (uint)*(byte *)((int)piVar10 + 0xe);
            iVar11 = DebugLevel;
          }
          iVar40 = iVar40 + 1;
          piVar44 = piVar44 + 2;
          pcVar27 = pcVar27 + 1;
          local_84 = local_84 + *piVar15;
          piVar15 = piVar15 + 1;
        } while (iVar40 < (int)uVar28);
        goto LAB_00024bc4;
      }
      local_84 = 0;
    }
    else {
      printk("=====================================================\n");
      uVar28 = (uint)*(byte *)((int)piVar10 + 0xe);
      if (uVar28 != 0) goto LAB_00024b74;
      local_84 = 0;
      iVar11 = DebugLevel;
LAB_00024bc4:
      if (-1 < iVar11) {
        printk("=====================================================\n");
      }
    }
    iVar11 = wlan_config_get_ht_bw(param_2);
    iVar40 = wlan_config_get_ext_cha(param_2);
    uVar28 = (uint)(iVar40 != 0);
    if (iVar11 != 1) {
      uVar28 = 0;
    }
    uVar29 = uVar28;
    if (-1 < DebugLevel) {
      printk("bw=%d,ext_cha=%d,total_apcount=%lu\n",iVar11,iVar40,local_84);
      uVar29 = extraout_r1_04;
    }
    uVar35 = (uint)*(byte *)((int)piVar10 + 0xe);
    if (uVar35 != 0) {
      iVar11 = 0;
      local_98 = 0xffffffff;
      uStack_94 = 0xffffffff;
      local_d8 = 0xffffffff;
      uStack_d4 = 0xffffffff;
      uVar41 = 0xffffffff;
      uVar24 = 0;
      local_b4 = 0xffffffff;
      local_8c = 0;
      uVar33 = 0;
LAB_00024c50:
      iVar40 = iVar9 + uVar33 * 4;
      uVar31 = *(uint *)(iVar40 + 0x32c);
      if (uVar31 <= uVar41) {
        uVar41 = uVar31;
      }
      if (uVar24 < uVar31) {
        uVar24 = uVar31;
      }
      iVar30 = local_8c;
      if (*(char *)(iVar9 + uVar33 + 0x2d0) != '\x01') {
        uVar34 = 0;
        if (uVar33 == 0) {
          uVar20 = 0;
          local_d0 = (char *)0x1;
          uVar29 = *(uint *)(iVar9 + 0x330) + *(uint *)(iVar9 + 0x334);
          bVar45 = CARRY4(uVar31,uVar29);
          uVar31 = uVar31 + uVar29;
          uVar34 = (uint)CARRY4(*(uint *)(iVar9 + 0x330),*(uint *)(iVar9 + 0x334)) + (uint)bVar45;
        }
        else {
          local_d0 = (char *)(uVar33 + 1);
          if ((int)local_d0 < 0x3b) {
            iVar36 = uVar33 + 2;
            bVar45 = CARRY4(uVar31,*(uint *)(iVar40 + 0x330));
            uVar31 = uVar31 + *(uint *)(iVar40 + 0x330);
            uVar34 = (uint)bVar45;
            if (iVar36 <= (int)local_d0) {
              puVar38 = (uint *)(iVar9 + (uVar33 + 0xcc) * 4);
              do {
                puVar38 = puVar38 + 1;
                iVar36 = iVar36 + 1;
                bVar45 = CARRY4(uVar31,*puVar38);
                uVar31 = uVar31 + *puVar38;
                uVar34 = uVar34 + bVar45;
              } while (iVar36 <= (int)local_d0);
            }
          }
          uVar20 = uVar33 - 1;
          if (uVar33 != 0) {
            iVar36 = uVar33 - 2;
            bVar45 = CARRY4(uVar31,*(uint *)(iVar40 + 0x328));
            uVar31 = uVar31 + *(uint *)(iVar40 + 0x328);
            uVar34 = uVar34 + bVar45;
            if ((int)uVar20 <= iVar36) {
              puVar38 = (uint *)(iVar9 + (uVar33 + 0xca) * 4);
              do {
                bVar45 = iVar36 == -1;
                iVar36 = iVar36 + -1;
                if (bVar45) break;
                puVar38 = puVar38 + -1;
                bVar45 = CARRY4(uVar31,*puVar38);
                uVar31 = uVar31 + *puVar38;
                uVar34 = uVar34 + bVar45;
              } while ((int)uVar20 <= iVar36);
            }
          }
        }
        if (uVar28 != 0) {
          uVar29 = uVar33 & 0xff;
          iVar11 = 1;
          uVar35 = uVar29 + 1 & 0xff;
          puVar38 = local_78;
          do {
            *puVar38 = 0xffffffff;
            puVar38[1] = 0xffffffff;
            if (iVar11 == 1) {
              iVar36 = GetExtCh(uVar35,1);
              iVar26 = ExtChCheck(param_1,uVar29,iVar36,param_2);
              if (iVar26 != 0) {
                iVar26 = 2;
                local_90 = 1;
                puVar21 = extraout_r2_00;
                goto LAB_00024d34;
              }
            }
            else {
              iVar36 = GetExtCh(uVar35,3);
              iVar26 = ExtChCheck(param_1,uVar29,iVar36,param_2);
              if (iVar26 != 0) {
                iVar26 = 1;
                local_90 = 2;
                puVar21 = extraout_r2;
LAB_00024d34:
                uVar20 = iVar36 - 1;
                if (uVar20 < 0x3c) {
                  iVar22 = iVar9 + iVar36 * 4;
                  iVar26 = uVar20 + iVar26;
                  bVar46 = SBORROW4(iVar36,0x3a);
                  iVar17 = iVar36 + -0x3a;
                  bVar45 = iVar36 == 0x3a;
                  if (iVar36 < 0x3b) {
                    bVar46 = SBORROW4(iVar36,iVar26);
                    iVar17 = iVar36 - iVar26;
                    bVar45 = iVar36 == iVar26;
                  }
                  uVar16 = 0;
                  uVar14 = *(uint *)(iVar22 + 0x328);
                  if (bVar45 || iVar17 < 0 != bVar46) {
                    puVar21 = (uint *)(iVar9 + (iVar36 + 0xca) * 4);
                    iVar22 = iVar36;
                  }
                  *puVar38 = uVar14;
                  puVar38[1] = 0;
                  if (bVar45 || iVar17 < 0 != bVar46) {
                    do {
                      puVar21 = puVar21 + 1;
                      iVar25 = iVar22 + 1;
                      bVar45 = CARRY4(uVar14,*puVar21);
                      uVar14 = uVar14 + *puVar21;
                      uVar16 = uVar16 + bVar45;
                      bVar46 = SBORROW4(iVar25,0x3a);
                      iVar17 = iVar22 + -0x39;
                      bVar45 = iVar25 == 0x3a;
                      if (iVar25 < 0x3b) {
                        bVar46 = SBORROW4(iVar25,iVar26);
                        iVar17 = iVar25 - iVar26;
                        bVar45 = iVar25 == iVar26;
                      }
                      iVar22 = iVar25;
                    } while (bVar45 || iVar17 < 0 != bVar46);
                    *puVar38 = uVar14;
                    puVar38[1] = uVar16;
                  }
                  iVar26 = iVar36 + -2;
                  if ((int)(uVar20 - local_90) <= iVar26 && -1 < iVar26) {
                    uVar14 = *puVar38;
                    uVar16 = puVar38[1];
                    puVar21 = (uint *)(iVar9 + (iVar36 + 0xca) * 4);
                    do {
                      iVar26 = iVar26 + -1;
                      puVar21 = puVar21 + -1;
                      bVar45 = CARRY4(uVar14,*puVar21);
                      uVar14 = uVar14 + *puVar21;
                      uVar16 = uVar16 + bVar45;
                    } while ((int)(uVar20 - local_90) <= iVar26 && -1 < iVar26);
                    *puVar38 = uVar14;
                    puVar38[1] = uVar16;
                  }
                }
              }
              if (iVar11 == 2) goto code_r0x00024de8;
            }
            iVar11 = iVar11 + 1;
            puVar38 = puVar38 + 2;
          } while( true );
        }
        bVar45 = uStack_d4 <= uVar34;
        if (uVar34 == uStack_d4) {
          bVar45 = local_d8 <= uVar31;
        }
        uVar14 = uVar31;
        uVar29 = uVar34;
        uVar16 = uVar31;
        uVar3 = uVar34;
        uVar4 = uVar33;
        uVar5 = uVar31;
        uVar6 = uVar34;
        if (bVar45) goto LAB_00024e30;
        goto LAB_00024e40;
      }
      local_d0 = (char *)(uVar33 + 1);
      goto LAB_00024e44;
    }
    uVar29 = 0xffffffff;
    local_b4 = 0xffffffff;
    local_d8 = 0xffffffff;
    uStack_d4 = 0xffffffff;
    uVar41 = 0xffffffff;
    uVar24 = 0;
    local_8c = 0;
LAB_00024e58:
    if (DebugLevel < 0) {
      if (uVar28 != 0) {
LAB_00024e74:
        if (local_8c < (int)local_b4) {
          *(byte *)((int)param_1 + 0x794cce) = *(byte *)((int)param_1 + 0x794cce) | 6;
          wlan_config_set_ext_cha(param_2,3);
          uVar29 = extraout_r1_02;
        }
        else if ((int)local_b4 < local_8c) {
          *(byte *)((int)param_1 + 0x794cce) = *(byte *)((int)param_1 + 0x794cce) & 0xf9 | 2;
          wlan_config_set_ext_cha(param_2,1);
          uVar29 = extraout_r1;
        }
        goto LAB_00024eb0;
      }
    }
    else {
      printk("max_busytime[%d] min_busytime[%d],candidate_ch_idx[%d]\n",uVar24,uVar41,local_b4);
      uVar29 = extraout_r1_03;
      if (uVar28 != 0) goto LAB_00024e74;
LAB_00024eb0:
      if (-1 < DebugLevel) {
        printk(" --- after adjust Min Channel Busy = %lld, single Max Channel busytime = %d,total_apcount = %lu\n"
               ,uVar29,local_d8,uStack_d4,uVar24,local_84);
      }
    }
    if (9999 < uVar24) {
      if (local_b4 == 0xffffffff) {
        iVar11 = RandomByte2(param_1);
        uVar28 = (uint)*(byte *)((int)piVar10 + 0xe);
        if (uVar28 == 0) {
          uVar29 = 1;
        }
        else {
          iVar40 = 0;
          do {
            __aeabi_idivmod(iVar40 + iVar11,uVar28);
            uVar29 = (uint)*(byte *)(piVar10 + extraout_r1_01 * 2 + 0x1d);
            if (*(char *)((int)param_1 + 0x36b862) == '\0') {
LAB_00025b2c:
              if ((((char)param_1[0xdae16] != '\x01') || (*(char *)(iVar9 + 0x510) != '\x01')) ||
                 (iVar30 = RadarChannelCheck(param_1,uVar29), iVar30 == 0)) break;
              uVar28 = (uint)*(byte *)((int)piVar10 + 0xe);
            }
            else if (*(byte *)((int)param_1 + 0x36b863) != uVar29) {
              pbVar18 = (byte *)((int)param_1 + 0x36b863);
              do {
                if (pbVar18 ==
                    (byte *)((int)param_1 +
                            (int)(&DAT_0036b863 + (byte)(*(char *)((int)param_1 + 0x36b862) - 1))))
                goto LAB_00025b2c;
                pbVar18 = pbVar18 + 1;
              } while (*pbVar18 != uVar29);
            }
            iVar40 = iVar40 + 1;
          } while (iVar40 < (int)uVar28);
        }
        if (-1 < DebugLevel) {
          printk("Randomly Select ==> Select Channel %d\n",uVar29);
          goto LAB_000251f0;
        }
        goto LAB_000250ac;
      }
      iVar11 = iVar9 + local_b4 * 4;
      uVar28 = *(uint *)(iVar11 + 0x1e0);
      if (local_b4 == 0) {
        if (*(uint *)(iVar9 + 0x1e4) < uVar28) {
          local_b4 = (uint)(*(char *)(iVar9 + 0x2d1) == '\0');
        }
        if (DebugLevel < 0) {
LAB_00024f10:
          uVar29 = (uint)*(byte *)(piVar10 + local_b4 * 2 + 0x1d);
          goto LAB_000251f0;
        }
        printk("FalseCCA_next =%d: FalseCCA_cur = %d\n");
      }
      else {
        uVar29 = local_b4 - 1;
        if (uVar29 < 9) {
          uVar24 = *(uint *)(iVar11 + 0x1dc);
          uVar35 = *(uint *)(iVar11 + 0x1e4);
          if (uVar24 < uVar28 && uVar24 < uVar35) {
            if (*(char *)(iVar9 + uVar29 + 0x2d0) == '\0') {
              local_b4 = uVar29;
            }
          }
          else {
            bVar46 = uVar35 <= uVar24;
            bVar45 = uVar24 == uVar35;
            if (bVar46 && !bVar45) {
              bVar46 = uVar35 <= uVar28;
              bVar45 = uVar28 == uVar35;
            }
            if ((bVar46 && !bVar45) && (*(char *)(iVar9 + local_b4 + 1 + 0x2d0) == '\0')) {
              local_b4 = local_b4 + 1;
            }
          }
          if (DebugLevel < 0) goto LAB_00024f10;
          printk("FalseCCA_next =%d: FalseCCA_cur = %d: FalseCCA_pri = %d\n");
        }
        else if (local_b4 == 10) {
          if (*(uint *)(iVar9 + 0x204) < uVar28) {
            if (*(char *)(iVar9 + 0x2d9) == '\0') {
              local_b4 = 9;
            }
            else {
              local_b4 = 10;
            }
          }
          if (DebugLevel < 0) goto LAB_00024f10;
          printk("FalseCCA_cur = %d: FalseCCA_pri = %d\n",uVar28,*(uint *)(iVar9 + 0x204));
        }
      }
      uVar29 = (uint)*(byte *)(piVar10 + local_b4 * 2 + 0x1d);
      if (DebugLevel < 0) goto LAB_000250ac;
      printk("SelectClearChannelBusyTime: Rule 5 ==> Select Channel %d\n",uVar29);
      goto LAB_000251f0;
    }
    if (*(byte *)((int)piVar10 + 0xe) == 0) {
      uVar28 = 0;
    }
    else {
      pcVar27 = (char *)(iVar9 + 0x2cf);
      puVar38 = (uint *)(iVar9 + 0xf0);
      uVar24 = 0;
      uVar29 = 0;
      uVar35 = 0xffffffff;
      iVar11 = -1;
      do {
        pcVar27 = pcVar27 + 1;
        uVar28 = uVar29;
        uVar41 = uVar35;
        iVar40 = iVar11;
        if (*pcVar27 != '\x01') {
          uVar33 = *puVar38;
          iVar40 = 0;
          bVar45 = iVar11 == 0;
          if (iVar11 == 0) {
            bVar45 = uVar35 <= uVar33;
          }
          uVar28 = uVar24;
          uVar41 = uVar33;
          if (((((bVar45) &&
                (uVar28 = uVar29, uVar41 = uVar35, iVar40 = iVar11, iVar11 == 0 && uVar33 == uVar35)
                ) && (uVar28 = uVar24, uVar24 != 0 && uVar24 != 5)) &&
              ((uVar24 != 10 && (uVar28 = uVar29, iVar11 == 0 && uVar35 < *(uint *)(iVar9 + 0xf0))))
              ) && ((iVar11 == 0 && uVar35 < *(uint *)(iVar9 + 0x104) &&
                    ((iVar11 == 0 && uVar35 < *(uint *)(iVar9 + 0x118) &&
                     ((uVar24 & 0xfffffffb) == 3)))))) {
            iVar40 = 0;
            if (*(uint *)(iVar9 + 0x338) < *(uint *)(iVar9 + 0x348)) {
              uVar28 = 3;
              uVar41 = uVar33;
            }
            else {
              uVar28 = 7;
              uVar41 = uVar33;
            }
          }
        }
        uVar24 = uVar24 + 1;
        puVar38 = puVar38 + 1;
        uVar29 = uVar28;
        uVar35 = uVar41;
        iVar11 = iVar40;
      } while (*(byte *)((int)piVar10 + 0xe) != uVar24);
    }
    uVar29 = (uint)*(byte *)(piVar10 + uVar28 * 2 + 0x1d);
    if (-1 < DebugLevel) {
      printk("SelectBestChannel by apcount ch = %d!\n",uVar29);
      goto LAB_000251f0;
    }
  }
  else {
    uVar32 = HcGetBandByWdev(param_2);
    piVar10 = (int *)HcGetAutoChCtrlbyBandIdx(param_1,uVar32);
    iVar40 = *piVar10;
    iVar9 = wlan_config_get_ht_bw(param_2);
    iVar11 = wlan_config_get_vht_bw(param_2);
    uVar12 = wlan_config_get_ch_band(param_2);
    local_80 = (undefined4 *)0x0;
    local_7c = 0;
    local_78[0] = 0;
    local_64[0] = (int *)0x0;
    if (2 < DebugLevel) {
      printk("[SelectClearChannelBusyTime] - cfg_ht_bw = %d vht_bw = %d\n",iVar9,iVar11);
    }
    if (iVar40 == 0) {
      if (-1 < DebugLevel) {
        printk("pAd->pChannelInfo equal NULL.\n");
      }
      goto LAB_000251bc;
    }
    if (DebugLevel < 1) {
      uVar28 = (uint)*(byte *)((int)piVar10 + 0xe);
      if (uVar28 != 0) {
LAB_00024634:
        uVar29 = 0;
        uVar35 = 0;
        local_d0 = "TRUE";
        iVar30 = DebugLevel;
        piVar15 = piVar10;
        puVar38 = (uint *)(iVar40 + 0x32c);
        do {
          if (0 < iVar30) {
            pcVar27 = local_d0;
            if (*(char *)((int)piVar15 + 0x7b) != '\x01') {
              pcVar27 = "FALSE";
            }
            pcVar19 = local_d0;
            if (*(char *)((int)piVar15 + 0x7a) != '\x01') {
              pcVar19 = "FALSE";
            }
            printk("Channel %3d : change Busy Time = %6u, ApCnt=%lu, Skip Channel = %s, BwCap = %s\n"
                   ,(char)piVar15[0x1d],*puVar38,*(undefined4 *)(*piVar10 + (uVar35 + 0x3c) * 4),
                   pcVar27,pcVar19);
            uVar28 = (uint)*(byte *)((int)piVar10 + 0xe);
            iVar30 = DebugLevel;
          }
          uVar35 = uVar35 + 1;
          piVar15 = piVar15 + 2;
          if (uVar29 < *puVar38) {
            uVar29 = *puVar38;
          }
          puVar38 = puVar38 + 1;
        } while (uVar35 < uVar28);
        if (uVar28 != 0) {
          uVar35 = 0;
          puVar38 = (uint *)(iVar40 + 0x32c);
          piVar15 = piVar10;
          do {
            pcVar27 = (char *)((int)piVar15 + 0x7b);
            uVar35 = uVar35 + 1;
            piVar15 = piVar15 + 2;
            if (*pcVar27 != '\0') {
              *puVar38 = *puVar38 + uVar29 * 2;
              uVar28 = (uint)*(byte *)((int)piVar10 + 0xe);
            }
            puVar38 = puVar38 + 1;
          } while (uVar35 < uVar28);
        }
        goto LAB_000246cc;
      }
    }
    else {
      printk("====================================================================\n");
      uVar28 = (uint)*(byte *)((int)piVar10 + 0xe);
      iVar30 = DebugLevel;
      if (uVar28 != 0) goto LAB_00024634;
LAB_000246cc:
      if (0 < iVar30) {
        printk("====================================================================\n");
      }
    }
    uVar28 = *(uint *)(iVar40 + 0x32c);
    os_alloc_mem(param_1,&local_80,0xf0);
    if (local_80 == (undefined4 *)0x0) {
      uVar29 = 0;
      if (0 < DebugLevel) {
        pcVar27 = "alloc buf for pSubGroupMaxBusyTimeTable failed!\n";
        goto LAB_00025764;
      }
LAB_00025054:
      if (local_7c != 0) {
        os_free_mem();
      }
    }
    else {
      os_alloc_mem(param_1,&local_7c,0xf0);
      if (local_7c != 0) {
        os_alloc_mem(param_1,local_78,0xf0);
        if (local_78[0] == 0) {
          if (DebugLevel < 1) {
LAB_00025228:
            uVar29 = 0;
            puVar42 = local_80;
            goto LAB_00025244;
          }
          pcVar27 = "alloc buf for pSubGroupMinBusyTimeTable failed!\n";
LAB_00025764:
          uVar29 = 0;
          printk(pcVar27);
          puVar42 = local_80;
        }
        else {
          os_alloc_mem(param_1,local_64,0xf0);
          if (local_64[0] == (int *)0x0) {
            if (DebugLevel < 1) goto LAB_00025228;
            pcVar27 = "alloc buf for pSubGroupMinBusyTimeChIdxTable failed!\n";
            goto LAB_00025764;
          }
          __memzero(local_80,0xf0);
          __memzero(local_7c,0xf0);
          __memzero(local_78[0],0xf0);
          __memzero(local_64[0],0xf0);
          uVar29 = (uint)*(byte *)((int)piVar10 + 0xe);
          if (uVar29 < 2) {
LAB_00025990:
            iVar9 = RandomByte2(param_1);
            uVar28 = (uint)*(byte *)((int)piVar10 + 0xe);
            if (uVar28 == 0) {
              uVar29 = 0;
            }
            else {
              uVar35 = 0;
              do {
                __aeabi_uidivmod(uVar35 + iVar9,uVar28);
                uVar29 = (uint)*(byte *)(piVar10 + extraout_r1_00 * 2 + 0x1d);
                if (*(char *)((int)param_1 + 0x36b862) == '\0') {
LAB_00025a38:
                  if ((((char)param_1[0xdae16] != '\x01') || ((char)piVar10[5] != '\x01')) ||
                     (iVar11 = RadarChannelCheck(param_1,uVar29), iVar11 == 0)) break;
                  uVar28 = (uint)*(byte *)((int)piVar10 + 0xe);
                }
                else if (*(byte *)((int)param_1 + 0x36b863) != uVar29) {
                  pbVar18 = (byte *)((int)param_1 + 0x36b863);
                  do {
                    if (pbVar18 ==
                        (byte *)((int)param_1 +
                                (int)(&DAT_0036b863 + (byte)(*(char *)((int)param_1 + 0x36b862) - 1)
                                     ))) goto LAB_00025a38;
                    pbVar18 = pbVar18 + 1;
                  } while (*pbVar18 != uVar29);
                }
                uVar35 = uVar35 + 1;
              } while (uVar35 < uVar28);
            }
            puVar42 = local_80;
            if (0 < DebugLevel) {
              printk("Randomly Select : Select Channel %d\n",uVar29);
              puVar42 = local_80;
            }
          }
          else {
            puVar38 = (uint *)(iVar40 + 0x330);
            uVar41 = 0;
            uVar35 = 0;
            uVar33 = 1;
            iVar40 = 0;
            piVar15 = piVar10;
            uVar24 = uVar28;
            do {
              if (*(char *)((int)piVar15 + 0x7e) == *(char *)((int)piVar15 + 0x76)) {
                uVar31 = uVar33;
                if (DebugLevel < 3) {
                  uVar20 = *puVar38;
                  uVar34 = uVar20;
                  if ((uVar20 <= uVar28) && (uVar34 = uVar28, uVar31 = uVar41, uVar20 < uVar24)) {
                    uVar35 = uVar33;
                    uVar24 = uVar20;
                  }
                }
                else {
                  printk("pChannelInfo->chanbusytime[%d] = %d, SubGroupMaxBusyTime = %d, SubGroupMinBusyTime = %d\n"
                         ,uVar33,*puVar38,uVar28,uVar24);
                  uVar29 = *puVar38;
                  uVar34 = uVar29;
                  if ((uVar29 <= uVar28) && (uVar34 = uVar28, uVar31 = uVar41, uVar29 < uVar24)) {
                    uVar35 = uVar33;
                    uVar24 = uVar29;
                  }
                  if (DebugLevel < 3) {
                    uVar29 = (uint)*(byte *)((int)piVar10 + 0xe);
                  }
                  else {
                    printk("SubGroupMaxBusyTime = %d, SubGroupMaxBusyTimeChIdx = %d,SubGroupMinBusyTime = %d SubGroupMinBusyTimeChIdx = %d\n"
                           ,uVar34,uVar31,uVar24,uVar35);
                    uVar29 = (uint)*(byte *)((int)piVar10 + 0xe);
                  }
                }
                iVar30 = iVar40;
                uVar28 = uVar34;
                uVar41 = uVar31;
                if (uVar33 == uVar29 - 1) {
                  local_80[iVar40] = uVar34;
                  *(uint *)(local_7c + iVar40 * 4) = uVar31;
                  *(uint *)(local_78[0] + iVar40 * 4) = uVar24;
                  local_64[0][iVar40] = uVar35;
                  if (2 < DebugLevel) {
                    printk("SubGroupMaxBusyTimeTable[%d] = %d, SubGroupMaxBusyTimeChIdxTable[%d] = %d, SubGroupMinBusyTimeTable[%d] = %d, SubGroupMinBusyTimeChIdxTable[%d] = %d\n"
                           ,iVar40,local_80[iVar40],iVar40,*(undefined4 *)(local_7c + iVar40 * 4),
                           iVar40,*(undefined4 *)(local_78[0] + iVar40 * 4),iVar40,
                           local_64[0][iVar40]);
                  }
                  iVar30 = iVar40 + 1;
                  uVar29 = (uint)*(byte *)((int)piVar10 + 0xe);
                }
              }
              else {
                local_80[iVar40] = uVar28;
                *(uint *)(local_7c + iVar40 * 4) = uVar41;
                *(uint *)(local_78[0] + iVar40 * 4) = uVar24;
                local_64[0][iVar40] = uVar35;
                if (2 < DebugLevel) {
                  printk("SubGroupMaxBusyTimeTable[%d] = %d, SubGroupMaxBusyTimeChIdxTable[%d] = %d, SubGroupMinBusyTimeTable[%d] = %d, SubGroupMinBusyTimeChIdxTable[%d] = %d\n"
                         ,iVar40,local_80[iVar40],iVar40,*(undefined4 *)(local_7c + iVar40 * 4),
                         iVar40,*(undefined4 *)(local_78[0] + iVar40 * 4),iVar40,local_64[0][iVar40]
                        );
                }
                iVar30 = iVar40 + 1;
                uVar29 = (uint)*(byte *)((int)piVar10 + 0xe);
                if ((uVar33 == uVar29 - 1) && (*(char *)((int)piVar15 + 0x7f) == '\0')) {
                  iVar36 = iVar40 * 4 + 4;
                  local_80[iVar40 + 1] = *puVar38;
                  *(uint *)(local_7c + iVar36) = uVar33;
                  *(uint *)(local_78[0] + iVar36) = *puVar38;
                  local_64[0][iVar40 + 1] = uVar33;
                  if (2 < DebugLevel) {
                    printk("SubGroupMaxBusyTimeTable[%d] = %d, SubGroupMaxBusyTimeChIdxTable[%d] = %d, SubGroupMinBusyTimeTable[%d] = %d, SubGroupMinBusyTimeChIdxTable[%d] = %d\n"
                           ,iVar30,local_80[iVar40 + 1],iVar30,*(undefined4 *)(local_7c + iVar36),
                           iVar30,*(undefined4 *)(local_78[0] + iVar36),iVar30,
                           local_64[0][iVar40 + 1]);
                  }
                  iVar30 = iVar40 + 2;
                  uVar29 = (uint)*(byte *)((int)piVar10 + 0xe);
                }
                else {
                  uVar28 = *puVar38;
                  uVar35 = uVar33;
                  uVar24 = uVar28;
                  uVar41 = uVar33;
                }
              }
              uVar33 = uVar33 + 1;
              piVar15 = piVar15 + 2;
              puVar38 = puVar38 + 1;
              iVar40 = iVar30;
            } while (uVar33 < uVar29);
            if (iVar30 == 0) goto LAB_00025990;
            iVar40 = 0;
            do {
              if (2 < DebugLevel) {
                printk("SubGroupMaxBusyTimeTable[%d] = %d, pSubGroupMaxBusyTimeChIdxTable[%d] = %d,\nSubGroupMinBusyTimeTable[%d] = %d, pSubGroupMinBusyTimeChIdxTable[%d] = %d\n"
                       ,iVar40,local_80[iVar40],iVar40,*(undefined4 *)(local_7c + iVar40 * 4),iVar40
                       ,*(undefined4 *)(local_78[0] + iVar40 * 4),iVar40,local_64[0][iVar40]);
              }
              iVar40 = iVar40 + 1;
            } while (iVar40 != iVar30);
            iVar36 = 4;
            iVar40 = iVar30;
            do {
              if (1 < iVar40) {
                iVar22 = iVar36 + -4;
                iVar17 = 1;
                iVar26 = iVar36;
                do {
                  iVar17 = iVar17 + 1;
                  uVar28 = *(uint *)((int)local_80 + iVar26);
                  if (uVar28 < *(uint *)((int)local_80 + iVar22)) {
                    *(uint *)((int)local_80 + iVar26) = *(uint *)((int)local_80 + iVar22);
                    *(uint *)((int)local_80 + iVar22) = uVar28;
                    uVar43 = *(undefined4 *)(local_7c + iVar26);
                    *(undefined4 *)(local_7c + iVar26) = *(undefined4 *)(local_7c + iVar22);
                    *(undefined4 *)(local_7c + iVar22) = uVar43;
                    uVar43 = *(undefined4 *)(local_78[0] + iVar26);
                    *(undefined4 *)(local_78[0] + iVar26) = *(undefined4 *)(local_78[0] + iVar22);
                    *(undefined4 *)(local_78[0] + iVar22) = uVar43;
                    uVar43 = *(undefined4 *)((int)local_64[0] + iVar26);
                    *(undefined4 *)((int)local_64[0] + iVar26) =
                         *(undefined4 *)((int)local_64[0] + iVar22);
                    *(undefined4 *)((int)local_64[0] + iVar22) = uVar43;
                  }
                  iVar26 = iVar26 + 4;
                } while (iVar17 != iVar40);
              }
              iVar40 = iVar40 + -1;
              iVar36 = iVar36 + 4;
            } while (iVar40 != 0);
            iVar40 = 0;
            puVar42 = local_80;
            do {
              if (2 < DebugLevel) {
                printk("SubGroupMaxBusyTimeTable[%d] = %d, pSubGroupMaxBusyTimeChIdxTable[%d] = %d,\nSubGroupMinBusyTimeTable[%d] = %d, pSubGroupMinBusyTimeChIdxTable[%d] = %d\n"
                       ,iVar40,puVar42[iVar40],iVar40,*(undefined4 *)(local_7c + iVar40 * 4),iVar40,
                       *(undefined4 *)(local_78[0] + iVar40 * 4),iVar40,local_64[0][iVar40]);
                puVar42 = local_80;
              }
              iVar40 = iVar40 + 1;
            } while (iVar40 < iVar30);
            if ((iVar30 < 3 || (iVar9 != 1 || iVar11 != 3)) ||
               ((*(ushort *)(param_2 + 0x18) & 0x20) == 0)) {
              uVar12 = *puVar42;
              iVar9 = *local_64[0];
              uVar29 = (uint)*(byte *)(piVar10 + iVar9 * 2 + 0x1d);
              if ((0 < DebugLevel) &&
                 ((printk("Rule 3 Channel Busy time value : Select Primary Channel %d\n",uVar29),
                  puVar42 = local_80, 0 < DebugLevel &&
                  (printk("Rule 3 Channel Busy time value : Min Channel Busy = %u\n",uVar12),
                  puVar42 = local_80, 0 < DebugLevel)))) {
                cVar2 = *(char *)((int)piVar10 + iVar9 * 8 + 0x77);
                if (cVar2 == '\x03') {
                  pcVar27 = "160";
                }
                else if (cVar2 == '\x02') {
                  pcVar27 = "80";
                }
                else {
                  pcVar27 = "40";
                  if (cVar2 != '\x01') {
                    pcVar27 = "20";
                  }
                }
                goto LAB_00025f6c;
              }
            }
            else {
              uVar39 = *puVar42;
              uVar43 = puVar42[1];
              uVar29 = (uint)*(byte *)(piVar10 + *local_64[0] * 2 + 0x1d);
              uVar12 = vht_cent_ch_freq((char)piVar10[*(int *)(local_7c + 4) * 2 + 0x1d],1,uVar12);
              iVar9 = DebugLevel;
              *(char *)(param_2 + 0x3fe1) = (char)uVar12;
              puVar42 = local_80;
              if ((((0 < iVar9) &&
                   (printk("Rule 3 Channel Busy time value : Select Primary Channel %d\n",uVar29),
                   puVar42 = local_80, 0 < DebugLevel)) &&
                  (printk("Rule 3 Channel Busy time value : Select Secondary Central Channel %d\n",
                          uVar12), puVar42 = local_80, 0 < DebugLevel)) &&
                 ((printk("Rule 3 Channel Busy time value : Min Channel Busy = %u\n",uVar39),
                  puVar42 = local_80, 0 < DebugLevel &&
                  (printk("Rule 3 Channel Busy time value : MinorMin Channel Busy = %u\n",uVar43),
                  puVar42 = local_80, 0 < DebugLevel)))) {
                pcVar27 = "80+80";
LAB_00025f6c:
                printk("Rule 3 Channel Busy time value : BW = %s\n",pcVar27);
                puVar42 = local_80;
              }
            }
          }
        }
LAB_00025244:
        if (puVar42 != (undefined4 *)0x0) {
LAB_0002524c:
          os_free_mem();
        }
        goto LAB_00025054;
      }
      uVar29 = 0;
      if (0 < DebugLevel) {
        pcVar27 = "alloc buf for pSubGroupMaxBusyTimeChIdxTable failed!\n";
        goto LAB_00025764;
      }
      if (local_80 != (undefined4 *)0x0) goto LAB_0002524c;
      uVar29 = 0;
    }
    if (local_78[0] != 0) {
      os_free_mem();
    }
    if (local_64[0] != (int *)0x0) {
      os_free_mem();
    }
    if (0 < DebugLevel) {
      printk("SelectClearChannelBusyTime[%d]:Select Channel %d\n",uVar32,uVar29);
LAB_000251f0:
      if (0 < DebugLevel) {
        printk("%s : Current channel = %d , selected new channel = %d\n","AutoChSelScanNextChannel",
               *(undefined1 *)(param_2 + 0x1a),uVar29);
      }
    }
  }
LAB_000250ac:
  scan_ch_restore(param_1,1,param_2);
  if (*(byte *)(param_2 + 0x1a) != uVar29) {
    iVar9 = rtmp_set_channel(param_1,param_2,uVar29);
    if (iVar9 == 0) {
      if (-1 < DebugLevel) {
        printk("%s : Fail to set channel !!\n","AutoChSelScanNextChannel");
      }
    }
    else if (*(char *)((int)param_1 + 0x79564e) != '\0' && iVar7 == 0) {
      iVar9 = scan_in_run_state(param_1,param_2);
      if (iVar9 == 0) {
        if (-1 < DebugLevel) {
          printk("Trigger AP ReScan !!!\n");
        }
        APOverlappingBSSScan(param_1,param_2);
        SetCommonHtVht(param_1,param_2);
      }
      else if (-1 < DebugLevel) {
        printk("in scanning!!!\n");
      }
    }
  }
  piVar8[4] = 1;
  if (((char)param_1[0xdae0c] == '\0') && (piVar8[0x16] = 0, (char)param_1[0xdae11] != '\0')) {
    complete(param_1 + 0xdae0d);
  }
  *(undefined1 *)((int)param_1 + 0xa7c349) = 1;
  *(undefined1 *)((int)param_1 + iVar7 + 0xa7c304) = 1;
LAB_00024560:
  if (2 < DebugLevel) {
    printk("%s<-----------------\n","AutoChSelScanNextChannel");
  }
  return;
code_r0x00024de8:
  bVar45 = local_78[3] <= local_78[1];
  if (local_78[1] == local_78[3]) {
    bVar45 = local_78[2] <= local_78[0];
  }
  if (bVar45) {
    iVar11 = uVar33 - 4;
    uVar29 = local_78[3] + uVar34 + (uint)CARRY4(local_78[2],uVar31);
    uVar14 = local_78[2];
  }
  else {
    iVar11 = uVar33 + 4;
    uVar29 = uVar34 + local_78[1] + (uint)CARRY4(uVar31,local_78[0]);
    uVar14 = local_78[0];
  }
  uVar14 = uVar31 + uVar14;
  bVar45 = uVar29 <= uStack_d4;
  if (uStack_d4 == uVar29) {
    bVar45 = uVar14 <= local_d8;
  }
  if (bVar45 && (uStack_d4 != uVar29 || local_d8 != uVar14)) {
    uVar35 = (uint)*(byte *)((int)piVar10 + 0xe);
    local_d8 = uVar14;
    uStack_d4 = uVar29;
    local_b4 = uVar33;
    local_98 = uVar31;
    uStack_94 = uVar34;
    iVar30 = iVar11;
    goto LAB_00024e44;
  }
  uVar35 = (uint)*(byte *)((int)piVar10 + 0xe);
LAB_00024e30:
  uVar20 = uVar29;
  uVar16 = local_d8;
  uVar3 = uStack_d4;
  uVar4 = local_b4;
  uVar5 = local_98;
  uVar6 = uStack_94;
  if (uVar29 == uStack_d4 && uVar14 == local_d8) {
    bVar45 = uStack_94 <= uVar34;
    if (uVar34 == uStack_94) {
      bVar45 = local_98 <= uVar31;
    }
    if (!bVar45) {
      local_b4 = uVar33;
      local_98 = uVar31;
      uStack_94 = uVar34;
      if (uVar28 != 0) {
        iVar30 = iVar11;
      }
      goto LAB_00024e44;
    }
    if ((((uVar34 == uStack_94 && uVar31 == local_98) && (local_b4 != 0xffffffff)) &&
        (*(uint *)(iVar40 + 0x32c) < *(uint *)(iVar9 + local_b4 * 4 + 0x32c))) &&
       (uVar4 = uVar33, local_b4 = uVar33, iVar30 = iVar11, uVar28 != 0)) goto LAB_00024e44;
  }
LAB_00024e40:
  uStack_94 = uVar6;
  local_98 = uVar5;
  local_b4 = uVar4;
  uStack_d4 = uVar3;
  local_d8 = uVar16;
  uVar29 = uVar20;
  iVar30 = local_8c;
LAB_00024e44:
  local_8c = iVar30;
  uVar33 = (uint)local_d0;
  if ((int)uVar35 <= (int)local_d0) goto LAB_00024e58;
  goto LAB_00024c50;
}

