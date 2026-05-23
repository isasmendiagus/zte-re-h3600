// module: mt7915.ko
// function: MacTableMaintenance @ 0x11b08
// size: 13896 bytes
//

void MacTableMaintenance(int param_1)

{
  char cVar1;
  byte bVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  undefined4 uVar9;
  ushort *puVar10;
  uint uVar11;
  undefined4 uVar12;
  byte bVar13;
  int iVar14;
  int iVar15;
  uint *puVar16;
  undefined1 uVar17;
  uint *puVar18;
  uint uVar19;
  char *pcVar20;
  byte *pbVar21;
  int *piVar22;
  undefined1 uVar23;
  bool bVar24;
  char cVar25;
  byte bVar26;
  ushort uVar27;
  uint uVar28;
  int iVar29;
  int *piVar30;
  char *pcVar31;
  int *piVar32;
  int iVar33;
  uint *puVar34;
  int iVar35;
  uint uVar36;
  uint *puVar37;
  bool bVar38;
  int iVar39;
  bool bVar40;
  bool bVar41;
  uint *local_118;
  uint *local_114;
  uint *local_110;
  uint *local_10c;
  uint *local_108;
  int local_104;
  uint *local_100;
  byte *local_fc;
  ushort *local_f8;
  undefined1 *local_f4;
  undefined1 *local_f0;
  undefined1 *local_ec;
  undefined1 *local_e8;
  undefined1 *local_e4;
  undefined1 *local_e0;
  int local_dc;
  int local_d4;
  int local_d0;
  uint local_c4;
  uint local_bc;
  uint local_b0;
  int *local_ac;
  uint local_8c;
  uint local_88;
  undefined4 local_70;
  uint local_6c;
  int local_68;
  int local_60;
  undefined2 local_4a;
  undefined4 local_48;
  undefined4 local_44;
  uint local_40;
  undefined2 local_3c;
  
  iVar14 = param_1 + 0xa1000;
  piVar32 = (int *)(param_1 + 8);
  hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  *(undefined1 *)(param_1 + 0x28593c) = 0;
  *(undefined1 *)(param_1 + 0x28593d) = 0;
  *(undefined1 *)(param_1 + 0x28593e) = 0;
  *(undefined1 *)(param_1 + 0x285941) = 0;
  *(undefined1 *)(param_1 + 0x285945) = 0;
  *(undefined1 *)(param_1 + 0x285942) = 0;
  *(undefined1 *)(param_1 + 0x285946) = 0;
  *(undefined1 *)(param_1 + 0x285948) = 0;
  *(undefined1 *)(param_1 + 0x28593f) = 1;
  *(undefined1 *)(param_1 + 0x285940) = 1;
  *(undefined1 *)(param_1 + 0x285949) = 1;
  *(undefined1 *)(param_1 + 0xa7c245) = 0;
  *(undefined4 *)(param_1 + 0xa7c258) = 0;
  *(undefined4 *)(param_1 + 0xa7c250) = 0;
  *(undefined1 *)(param_1 + 0xa7c246) = 0;
  *(undefined4 *)(param_1 + 0xa7c25c) = 0;
  *(undefined4 *)(param_1 + 0xa7c254) = 0;
  do {
    piVar32 = piVar32 + 1;
    iVar33 = *piVar32;
    if (iVar33 != 0) {
      wlan_operate_set_non_gf_sta(iVar33);
    }
  } while (piVar32 != (int *)(param_1 + 0x1a8));
  puVar18 = (uint *)(param_1 + 0xa1d20);
  local_70 = 0;
  *(undefined1 *)(param_1 + 0x285943) = 0;
  *(undefined1 *)(param_1 + 0x285944) = 0;
  vow_avg_pkt_len_reset(param_1);
  piVar32 = (int *)(param_1 + 0xa1d28);
  bVar40 = false;
  *(undefined4 *)(param_1 + 0xa7c43c) = 0;
  *(undefined1 *)(param_1 + 0xa7c440) = 0;
  *(undefined4 *)(param_1 + 0xa7c444) = 0;
  *(undefined1 *)(param_1 + 0xa7c448) = 0;
  *(undefined4 *)(param_1 + 0xa7c4ac) = 0;
  *(undefined1 *)(param_1 + 0xa7c4b0) = 0;
  *(undefined4 *)(param_1 + 0xa7c4b4) = 0;
  *(undefined1 *)(param_1 + 0xa7c4b8) = 0;
  bVar13 = 0;
  bVar2 = 0;
  local_6c = 0;
  local_60 = 0;
  local_68 = 0;
  local_88 = 0;
  local_8c = 0;
  local_fc = (byte *)(param_1 + 0xa1e04);
  local_f4 = (undefined1 *)(param_1 + 0xa1e0c);
  local_e0 = (undefined1 *)(param_1 + 0xa1e0d);
  local_e4 = (undefined1 *)(param_1 + 0xa1e0e);
  local_ec = (undefined1 *)(param_1 + 0xa1e0f);
  local_f0 = (undefined1 *)(param_1 + 0xa1e11);
  local_100 = (uint *)(param_1 + 0xa2808);
  puVar34 = (uint *)(param_1 + 0xa307c);
  local_110 = (uint *)(param_1 + 0xa3080);
  local_114 = (uint *)(param_1 + 0xa3084);
  local_108 = (uint *)(param_1 + 0xa30a4);
  local_10c = (uint *)(param_1 + 0xa308c);
  local_118 = (uint *)(param_1 + 0xa3078);
  local_f8 = (ushort *)(param_1 + 0xa1e00);
  local_e8 = (undefined1 *)(param_1 + 0xa1e10);
  local_d0 = 0x40001;
  local_dc = 2;
  iVar35 = param_1;
  puVar37 = puVar18;
  local_104 = param_1;
  for (uVar36 = 0; iVar6 = HcGetMaxStaNum(param_1), (int)uVar36 < iVar6; uVar36 = uVar36 + 1) {
    uVar28 = *puVar37;
    if ((uVar28 & 0xfffffbff) != 0) {
      if (puVar37 == (uint *)0x0) {
LAB_00012114:
        if (*piVar32 != 0) {
LAB_00012018:
          local_dc = HcGetBandByWdev();
        }
        if (*puVar37 == 2 || (*puVar37 - 0x20001 & 0xfffdffff) == 0) {
LAB_00012048:
          iVar29 = param_1 + local_dc * 4;
          iVar6 = param_1 + local_dc;
          *(uint *)(iVar29 + 0xa7c258) = *(int *)(iVar29 + 0xa7c258) + *puVar34;
          *(uint *)(iVar29 + 0xa7c250) = *(int *)(iVar29 + 0xa7c250) + *local_118;
          if (((&DAT_00a7c241)[iVar6] == '\x01') &&
             (iVar29 = RTMPMinRssi(param_1,(int)*(char *)(iVar35 + 0xa1e2c),
                                   (int)*(char *)(iVar35 + 0xa1e2d),(int)*(char *)(iVar35 + 0xa1e2e)
                                   ,(int)*(char *)(iVar35 + 0xa1e2f)),
             iVar29 < *(char *)(iVar6 + 0xa7c245))) {
            *(char *)(iVar6 + 0xa7c245) = (char)iVar29;
          }
          uVar28 = *puVar37;
          goto LAB_0001209c;
        }
LAB_00011db0:
        uVar28 = *local_118;
      }
      else {
        if (uVar28 == 2 || (uVar28 - 0x20001 & 0xfffdffff) == 0) {
          if (*(int *)(iVar35 + 0xa3158) != 0) {
            *(int *)(iVar35 + 0xa3158) = *(int *)(iVar35 + 0xa3158) + -1;
            goto LAB_00012114;
          }
          if (*piVar32 != 0) goto LAB_00012018;
          goto LAB_00012048;
        }
        if (*piVar32 != 0) goto LAB_00012018;
LAB_0001209c:
        if ((uVar28 != 2) || (*(char *)(local_104 + 0x2f762) != '\x01')) goto LAB_00011db0;
        uVar28 = *local_118;
        iVar6 = param_1 + (uint)*local_fc * 0x2137b0;
        *(uint *)(&DAT_00580d08 + iVar6) = uVar28;
        *(uint *)(&DAT_00580d0c + iVar6) = *puVar34;
      }
      if (*local_110 != 0) {
        uVar28 = uVar28 + *local_110 >> 1;
      }
      *local_110 = uVar28;
      *local_118 = 0;
      if (*local_10c == 0) {
        uVar28 = *(uint *)(iVar35 + 0xa3088);
      }
      else {
        uVar28 = *local_10c + *(int *)(iVar35 + 0xa3088) >> 1;
      }
      *local_10c = uVar28;
      *(undefined4 *)(iVar35 + 0xa3088) = 0;
      if (*local_114 == 0) {
        uVar28 = *puVar34;
      }
      else {
        uVar28 = *local_114 + *puVar34 >> 1;
      }
      *local_114 = uVar28;
      *puVar34 = 0;
      if (*local_108 == 0) {
        uVar28 = *(uint *)(iVar35 + 0xa30a8);
      }
      else {
        uVar28 = *local_108 + *(int *)(iVar35 + 0xa30a8) >> 1;
      }
      *local_108 = uVar28;
      *(undefined4 *)(iVar35 + 0xa30a8) = 0;
      if (((*puVar37 == 2) &&
          (iVar6 = param_1 + (uint)*local_fc * 0x2137b0, (&DAT_00580e8e)[iVar6] == '\x01')) &&
         (iVar29 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0)),
         *(char *)(iVar29 + 0x150) == '\x01')) {
        if (*(char *)(iVar35 + 0xa3148) == '\0') {
          if ((*(int *)(&DAT_00580e98 + iVar6) - *(int *)(param_1 + 0x7960e8)) + 100 < 0) {
            *(undefined1 *)(iVar35 + 0xa3148) = 1;
            *(undefined4 *)(iVar35 + 0xa314c) = 0;
            *(undefined1 *)(iVar35 + 0xa3149) = 0;
          }
        }
        else if ((*(char *)(iVar35 + 0xa3149) != '\0') && (*(int *)(iVar35 + 0xa314c) != 0)) {
          *(undefined4 *)(&DAT_00580e98 + iVar6) = *(undefined4 *)(param_1 + 0x7960e8);
          *(undefined1 *)(iVar35 + 0xa3148) = 0;
        }
      }
      HW_GET_TX_STATISTIC(param_1,8,uVar36 & 0xffff);
      call_traffic_notifieriers(7,param_1,puVar37);
      iVar6 = local_d0;
      if ((*puVar37 == 2 || *puVar37 == 0x40001) &&
         (iVar6 = local_104, *(char *)(local_104 + 0x2f762) == '\x01')) {
        iVar29 = GetStaCfgByWdev(param_1,*piVar32);
        iVar6 = *(int *)(iVar35 + 0xa281c);
        if ((iVar6 != 0) && (*(char *)(iVar6 + 5) == '\x02')) {
          *(int *)(iVar6 + 0x4148) = *(int *)(iVar6 + 0x4148) + 1;
          iVar6 = *(int *)(iVar35 + 0xa281c);
          if ((((iVar6 != 0) && ((*(byte *)(iVar6 + 3) & 1) != 0)) &&
              (299 < *(uint *)(iVar6 + 0x4148))) && ((*(byte *)(iVar6 + 3) & 2) == 0)) {
            RepeaterDisconnectRootAP(param_1,iVar6,3);
            goto LAB_00011ef4;
          }
        }
        iVar6 = *piVar32;
        if (*puVar37 == 2) {
          local_68 = iVar6;
        }
        local_8c = local_8c + *local_110;
        local_88 = local_88 + *local_114;
        if (iVar6 != 0) {
          uVar28 = *local_114 >> 0x11;
          uVar19 = *local_110 >> 0x11;
          uVar7 = uVar28 + uVar19;
          if (uVar7 == 0) {
            iVar8 = param_1 + local_dc * 0x20;
            if (*(int *)(iVar8 + 0xa7c3e0) == 0) {
              uVar23 = 0;
              goto LAB_00014270;
            }
            *(char *)(iVar8 + 0xa7c3dc) = *(char *)(iVar8 + 0xa7c3dc) + '\x01';
          }
          else {
            uVar11 = __aeabi_uidiv(uVar19 * 100,uVar7);
            if (uVar11 < 0x47) {
              uVar11 = __aeabi_uidiv(uVar28 * 100,uVar7);
              if (uVar11 < 0x47) {
                uVar23 = 0;
              }
              else {
                uVar23 = 2;
              }
            }
            else {
              uVar23 = 1;
            }
            if (*(int *)(param_1 + local_dc * 0x20 + 0xa7c3e0) == 0) {
LAB_00014270:
              *(int *)(param_1 + local_dc * 0x20 + 0xa7c3e0) = iVar6;
            }
            iVar8 = param_1 + local_dc * 0x20;
            *(char *)(iVar8 + 0xa7c3dc) = *(char *)(iVar8 + 0xa7c3dc) + '\x01';
            if ((uint)(*(int *)(iVar8 + 0xa7c3ec) + *(int *)(iVar8 + 0xa7c3f0)) < uVar7) {
              *(uint *)(iVar8 + 0xa7c3ec) = uVar19;
              *(uint *)(iVar8 + 0xa7c3f0) = uVar28;
              *(undefined1 *)(iVar8 + 0xa7c3f4) = uVar23;
              *(uint **)(param_1 + (local_dc + 0x53e1f) * 0x20 + 4) = puVar37;
              *(int *)(iVar8 + 0xa7c3e0) = iVar6;
            }
          }
        }
        iVar6 = *(uint *)(param_1 + 0x82921c) * -0x33333333;
        if (*(uint *)(param_1 + 0x82921c) % 10 == 8) {
          if ((iVar29 != 0) && (*(char *)(iVar29 + 0x2124c0) == '\0')) {
            ApCliRTMPSendNullFrame
                      (param_1,*(undefined1 *)(iVar35 + 0xa289f),*(uint *)(iVar35 + 0xa1dd4) & 1,
                       puVar37,0);
          }
          goto LAB_00011ef4;
        }
      }
      wlan_update_txrxrate(param_1,puVar37,iVar6);
      if (*puVar37 == 0x20001) {
        if ((&DAT_0036b920)[param_1] != '\0') {
          piVar22 = (int *)(iVar35 + 0xa30ac);
          do {
            piVar30 = piVar22 + 1;
            *piVar22 = *piVar30;
            piVar22 = piVar30;
          } while (piVar30 != (int *)(iVar35 + 0xa30c8));
          *piVar30 = *(int *)(iVar35 + 0xa3070) + *(int *)(iVar35 + 0xa3068);
        }
        if ((*(char *)(iVar35 + 0xa291d) == '\0') || (*(short *)(iVar35 + 0xa29de) == 0)) {
          if (*piVar32 == 0) goto LAB_00012be0;
LAB_00012278:
          local_bc = *local_110;
          uVar28 = local_bc >> 0x11;
          local_c4 = *local_114;
          local_d4 = HcGetBandByWdev();
          local_b0 = local_c4 >> 0x11;
          uVar19 = local_b0 + uVar28;
          if (uVar19 == 0) {
            iVar6 = local_d4 * 0x20;
            iVar29 = param_1 + iVar6;
            if (*(int *)(iVar29 + 0xa7c3e0) == 0) {
              uVar23 = 0;
              goto LAB_000136c0;
            }
            *(char *)(iVar29 + 0xa7c3dc) = *(char *)(iVar29 + 0xa7c3dc) + '\x01';
          }
          else {
            uVar7 = __aeabi_uidiv(uVar28 * 100,uVar19);
LAB_000122d8:
            if (uVar7 < 0x47) {
              uVar7 = __aeabi_uidiv(local_b0 * 100,uVar19);
              if (uVar7 < 0x47) {
                uVar23 = 0;
              }
              else {
                uVar23 = 2;
              }
            }
            else {
              uVar23 = 1;
            }
LAB_00012318:
            iVar6 = local_d4 * 0x20;
            if (*(int *)(param_1 + iVar6 + 0xa7c3e0) == 0) {
LAB_000136c0:
              *(int *)(param_1 + iVar6 + 0xa7c3e0) = *piVar32;
            }
            iVar6 = param_1 + iVar6;
            *(char *)(iVar6 + 0xa7c3dc) = *(char *)(iVar6 + 0xa7c3dc) + '\x01';
            if ((uint)(*(int *)(iVar6 + 0xa7c3ec) + *(int *)(iVar6 + 0xa7c3f0)) < uVar19) {
              *(uint *)(iVar6 + 0xa7c3ec) = uVar28;
              *(uint *)(iVar6 + 0xa7c3f0) = local_b0;
              *(undefined1 *)(iVar6 + 0xa7c3f4) = uVar23;
              *(uint **)(param_1 + (local_d4 + 0x53e1f) * 0x20 + 4) = puVar37;
              *(int *)(iVar6 + 0xa7c3e0) = *piVar32;
            }
          }
          iVar29 = *(int *)(param_1 + 0x286280);
          iVar6 = iVar29;
          if (iVar29 != 1) {
            iVar6 = iVar29 + -4;
          }
          if ((iVar6 == 0 || (iVar29 == 1 || iVar29 + -4 == 1)) &&
             ((uVar19 = hc_get_asic_cap(*(undefined4 *)(param_1 + 0xa797a0)), (uVar19 & 0x8000) != 0
              || (uVar19 = hc_get_asic_cap(*(undefined4 *)(param_1 + 0xa797a0)),
                 (uVar19 & 0x80000) != 0)))) {
            pci_dynamic_dly_int_adjust(*(undefined4 *)(param_1 + 0xa797a0),uVar28,local_b0);
          }
          if (local_c4 + local_bc == 0) {
            bVar38 = false;
            bVar41 = false;
          }
          else {
            if (*(uint *)(iVar35 + 0xa3094) < 0x100) {
              iVar6 = 5;
              local_70 = 0x32;
            }
            else {
              iVar6 = 7;
              local_70 = 0x46;
            }
            uVar28 = (local_c4 + local_bc) / 10;
            bVar41 = uVar28 * 7 < local_bc;
            if (uVar28 * iVar6 < local_c4) {
              bVar38 = true;
            }
            else {
              bVar38 = false;
            }
          }
          local_ac = (int *)(iVar35 + 0xa3094);
          if (((*(uint *)(param_1 + local_d4 * 0x70 + 0xa7c474) & 2) != 0) && (0 < DebugLevel)) {
            printk("STA%d:avg_tx_b:%lu,avg_rx_b:%lu,avg_tx_pkts:%lu,avg_rx_pkts:%lu,rx_ratio:%u\n",
                   *local_f8,local_bc,local_c4,*local_10c,*local_108,local_70);
          }
          iVar6 = *piVar32;
          uVar27 = *(ushort *)(iVar6 + 0x18);
          if ((uVar27 & 0xb1) != 0) {
            iVar29 = param_1 + local_d4 * 0x10;
            if (*(byte *)(iVar29 + 0xa7c41c) < 0x10) {
              *(int *)(param_1 + (local_d4 + 0xa7c42) * 0x10 + 4) = iVar6;
              bVar24 = bVar41;
              if (*local_10c < 0x15) {
                bVar24 = false;
              }
              if (bVar24) {
                *(char *)(iVar29 + 0xa7c41c) = *(char *)(iVar29 + 0xa7c41c) + '\x01';
              }
              uVar27 = *(ushort *)(iVar6 + 0x18);
              if ((uVar27 & 0xb1) == 0) goto LAB_00012564;
            }
            iVar29 = param_1 + local_d4 * 0x10;
            if (*(byte *)(iVar29 + 0xa7c41d) < 0x10) {
              *(int *)(param_1 + (local_d4 + 0xa7c42) * 0x10 + 4) = iVar6;
              bVar24 = bVar38;
              if (*local_108 < 0x15) {
                bVar24 = false;
              }
              if (bVar24) {
                *(char *)(iVar29 + 0xa7c41d) = *(char *)(iVar29 + 0xa7c41d) + '\x01';
              }
              uVar27 = *(ushort *)(iVar6 + 0x18);
            }
          }
LAB_00012564:
          if ((uVar27 & 0x4e) != 0) {
            iVar29 = param_1 + local_d4 * 0x10;
            if (*(byte *)(iVar29 + 0xa7c41c) < 0x10) {
              *(int *)(param_1 + (local_d4 + 0xa7c42) * 0x10 + 4) = iVar6;
              if (*local_10c < 0x15) {
                bVar41 = false;
              }
              if (bVar41) {
                *(char *)(iVar29 + 0xa7c41c) = *(char *)(iVar29 + 0xa7c41c) + '\x01';
              }
              if ((*(ushort *)(iVar6 + 0x18) & 0x4e) == 0) goto LAB_00012638;
            }
            iVar29 = param_1 + local_d4 * 0x10;
            if (*(byte *)(iVar29 + 0xa7c41d) < 0x10) {
              *(int *)(param_1 + (local_d4 + 0xa7c42) * 0x10 + 4) = iVar6;
              if (*local_108 < 0x15) {
                bVar38 = false;
              }
              if (bVar38) {
                *(char *)(iVar29 + 0xa7c41d) = *(char *)(iVar29 + 0xa7c41d) + '\x01';
              }
            }
          }
LAB_00012638:
          if (((*(char *)(param_1 + 0xa797a4) == '\x02') && (*(char *)(param_1 + 0xa7a319) == '\0'))
             && (*(char *)(param_1 + local_d4 * 0x10 + 0xa7c420) == '\0')) {
            piVar22 = (int *)(local_104 + 0x2f6cc);
            iVar29 = local_104 + 0x2f734;
            iVar6 = 0;
            do {
              if (*piVar22 != 0) {
                OS_SPIN_LOCK(iVar29);
                if (((piVar22[-2] != 0) &&
                    (iVar8 = *(int *)(piVar22[-2] + 0xcc), *(short *)(iVar8 + 0xc) == 8)) &&
                   (*(char *)(iVar8 + 0x17) == '\x06')) {
                  iVar6 = param_1 + local_d4 * 0x10;
                  OS_SPIN_UNLOCK(iVar29);
                  *(char *)(iVar6 + 0xa7c420) = *(char *)(iVar6 + 0xa7c420) + '\x01';
                  break;
                }
                OS_SPIN_UNLOCK(iVar29);
              }
              iVar6 = iVar6 + 1;
              piVar22 = piVar22 + 4;
              iVar29 = iVar29 + 4;
            } while (iVar6 != 4);
          }
          iVar6 = *(int *)(*piVar32 + 8);
          vow_avg_pkt_len_calculate(puVar37);
          if (*local_10c == 0) {
            if (*local_108 != 0) {
              uVar28 = 0xffffffd8;
              iVar29 = 0;
              goto LAB_0001269c;
            }
            *(undefined4 *)(iVar35 + 0xa3090) = 0;
            iVar8 = 0;
          }
          else {
            iVar29 = __aeabi_uidiv(*local_110,*local_10c);
            if (*local_108 == 0) {
              uVar28 = iVar29 - 0x28;
              iVar8 = 0;
            }
            else {
              uVar28 = iVar29 - 0x28;
LAB_0001269c:
              iVar8 = __aeabi_uidiv(*local_114);
            }
            if (uVar28 < 0x7a9) {
              iVar15 = iVar6 + local_d4 * 0x70;
              iVar39 = *(byte *)(iVar15 + 0xa7c440) + 1;
              uVar9 = __aeabi_uidiv(*(int *)(iVar15 + 0xa7c43c) * (uint)*(byte *)(iVar15 + 0xa7c440)
                                    + iVar29,iVar39);
              *(undefined4 *)(iVar15 + 0xa7c43c) = uVar9;
              *(char *)(iVar15 + 0xa7c440) = (char)iVar39;
            }
            *(int *)(iVar35 + 0xa3090) = iVar29;
            if (iVar8 != 0) {
              iVar6 = iVar6 + local_d4 * 0x70;
              iVar29 = *(byte *)(iVar6 + 0xa7c448) + 1;
              uVar9 = __aeabi_uidiv(*(int *)(iVar6 + 0xa7c444) * (uint)*(byte *)(iVar6 + 0xa7c448) +
                                    iVar8,iVar29);
              *(undefined4 *)(iVar6 + 0xa7c444) = uVar9;
              *(char *)(iVar6 + 0xa7c448) = (char)iVar29;
            }
          }
          *local_ac = iVar8;
          cVar25 = "rtmp_read_dot11v_mbssid_cfg_from_file"[param_1 + 0x12];
          puVar16 = &local_40;
          pcVar20 = (char *)(param_1 + 0x36b7fb);
          do {
            pcVar20 = pcVar20 + 1;
            *(char *)puVar16 = *pcVar20 - cVar25;
            puVar16 = (uint *)((int)puVar16 + 1);
          } while (pcVar20 != (char *)(param_1 + 0x36b7ff));
          iVar6 = 0;
          pcVar20 = (char *)(iVar35 + 0xa1e2b);
          do {
            pcVar20 = pcVar20 + 1;
            iVar8 = (int)*pcVar20;
            bVar41 = SCARRY4(iVar8,0x7f);
            iVar29 = iVar8 + 0x7f;
            if (iVar8 != -0x7f) {
              bVar41 = SCARRY4(iVar8,0x46);
              iVar29 = iVar8 + 0x46;
            }
            if ((iVar29 < 0 != bVar41) && (9 < *(char *)((int)&local_40 + iVar6) - iVar8)) {
              *(char *)(param_1 + 0xa7cbec) = *(char *)(param_1 + 0xa7cbec) + '\x01';
              break;
            }
            iVar6 = iVar6 + 1;
          } while (iVar6 != 4);
          local_dc = local_d4;
          if (*(uint *)(iVar35 + 0xa3098) < 2) goto LAB_00012be0;
          if (*local_100 != 0) {
            *local_100 = 0;
            bVar40 = true;
          }
LAB_00012824:
          *(undefined2 *)(iVar35 + 0xa2814) = 0;
          uVar28 = *local_100;
        }
        else {
          if (local_6c < 2 && *(short *)(iVar35 + 0xa29e0) != 0) {
            iVar6 = *piVar32;
            if ((*(ushort *)(iVar6 + 0x18) & 0x4e) == 0) goto LAB_00012270;
            local_bc = *local_110;
            local_c4 = *local_114;
            uVar28 = local_bc >> 0x11;
            if (uVar28 < 0x33) goto LAB_00012270;
            local_b0 = local_c4 >> 0x11;
            uVar19 = local_b0 + uVar28;
            if (uVar19 != 0) {
              uVar7 = __aeabi_uidiv(uVar28 * 100,uVar19);
              if (0x46 < uVar7) {
                if (local_6c == 0) {
                  local_6c = 1;
                  local_60 = iVar6;
                }
                else {
                  local_6c = 2;
                }
              }
              if (iVar6 == 0) goto LAB_00012be0;
              local_d4 = HcGetBandByWdev(iVar6);
              goto LAB_000122d8;
            }
            if (iVar6 == 0) goto LAB_00012be0;
            local_d4 = HcGetBandByWdev(iVar6);
            uVar23 = 0;
            goto LAB_00012318;
          }
          iVar6 = *piVar32;
LAB_00012270:
          if (iVar6 != 0) goto LAB_00012278;
LAB_00012be0:
          uVar28 = *local_100;
          if (uVar28 == 0) goto LAB_00012824;
        }
        *local_100 = uVar28 + 1;
        iVar6 = param_1 + (uint)*local_f8 * 0x620;
        *(int *)(iVar6 + 0x2f954) = *(int *)(iVar6 + 0x2f954) + 1;
        *(int *)(iVar35 + 0xa2824) = *(int *)(iVar35 + 0xa2824) + 1;
        uVar28 = (uint)*local_fc;
        if (((*(int *)(iVar35 + 0xa1e1c) == 2) || (*local_100 < *(uint *)(iVar35 + 0xa2810))) ||
           (*(char *)(iVar35 + 0xa282c) != '\0')) {
          bVar41 = bVar40;
          if (*piVar32 == 0) {
            bVar41 = false;
          }
          if ((bVar41) &&
             (*(uint *)(param_1 + 0x829214) == (*(uint *)(param_1 + 0x829214) / 0x3c) * 0x3c)) {
            IAPP_L2_Update_Frame_Send(param_1,local_f4,*(undefined1 *)(*piVar32 + 0xc));
          }
          pcVar20 = (char *)(iVar35 + 0xa2818);
          if (*pcVar20 == '\x01') {
            *(undefined1 *)(param_1 + 0x28593c) = 1;
            iVar6 = *piVar32;
            if ((iVar6 != 0) && (*(int *)(iVar6 + 0x14) == 1 || *(int *)(iVar6 + 0x14) == 0x20)) {
              *(undefined1 *)(param_1 + (uint)*(ushort *)(iVar6 + 0x10) * 0x620 + 0x2f763) = 1;
              if (*(char *)(local_104 + 0x2fa7c) != '\0') {
                bVar26 = *(char *)(local_104 + 0x2fa7c) + 1;
                if (2 < bVar26) {
                  bVar26 = 0;
                }
                *(byte *)(local_104 + 0x2fa7c) = bVar26;
              }
            }
          }
          if (*(char *)(iVar35 + 0xa2a30) == '\x01') {
            *(undefined1 *)(param_1 + 0x285946) = 1;
          }
          if ((*(ushort *)(uVar36 * 0x14c0 + iVar14 + 0xdde) & 0x180) == 0) {
            *(undefined1 *)(param_1 + 0x285945) = 1;
          }
          if ((*(byte *)(uVar36 * 0x14c0 + iVar14 + 0xddf) & 0xe0) != 0x60) {
            if (*piVar32 != 0) {
              iVar6 = HcGetBandByWdev();
              sVar5 = wlan_operate_get_non_gf_sta(iVar33);
              wlan_operate_set_non_gf_sta(iVar33,sVar5 + 1);
              *(undefined1 *)(iVar14 + iVar6 + 0x1e4943) = 1;
            }
            if ((*(byte *)(uVar36 * 0x14c0 + iVar14 + 0xddf) & 0xc0) == 0) {
              *(undefined1 *)(param_1 + 0x285942) = 1;
            }
          }
          if (*(char *)(iVar35 + 0xa2a32) != '\0') {
            *(undefined1 *)(param_1 + 0x285948) = 1;
          }
          uVar19 = (uint)*(ushort *)("pStaCfg->WpaPassPhrase" + uVar28 * 0x5834 + param_1 + 0xc);
          if (uVar19 == 0) {
LAB_00012c00:
            uVar7 = *local_100;
          }
          else {
            uVar7 = *local_100;
            if (uVar19 <= uVar7) {
              puVar10 = (ushort *)(iVar35 + 0xa2814);
              uVar27 = *puVar10;
              uVar7 = uVar27 + 1;
              *puVar10 = (ushort)uVar7;
              if (uVar27 != 0) {
                if (uVar19 <= (uVar7 & 0xffff)) {
                  *puVar10 = 0;
                }
                goto LAB_00012c00;
              }
              if (*pcVar20 == '\x01') {
                iVar6 = (uint)*local_fc * 0x5834 + param_1 +
                        (((uint)*(ushort *)(iVar35 + 0xa1e18) << 0x15) >> 0x18);
                "vow_watf_q_lv1: %d\n"[iVar6 + 0x13] =
                     *(byte *)((int)&NUM_BIT8 + (*(ushort *)(iVar35 + 0xa1e18) & 7)) |
                     "vow_watf_q_lv1: %d\n"[iVar6 + 0x13];
                uVar7 = *local_100;
              }
              else {
                RtmpEnqueueNullFrame
                          (param_1,local_f4,*(undefined1 *)(iVar35 + 0xa289f),*local_f8,*local_fc,
                           *(uint *)(iVar35 + 0xa1dd4) & 1,1,0);
                uVar7 = *local_100;
              }
            }
          }
          if (uVar7 < *(uint *)(iVar35 + 0xa2828)) {
            if (*(uint *)(iVar35 + 0xa299c) < *(uint *)(&DAT_0036b910 + param_1)) {
              if ((&DAT_0036b920)[param_1] != '\0') {
                bVar26 = *local_fc;
                iVar29 = (uint)bVar26 * 0x5834;
                iVar6 = Get_BndStrgTable(param_1,"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                                 [param_1 + iVar29 + 0xee]);
                if (((iVar6 != 0) && (*(char *)(iVar6 + 5) != '\0')) &&
                   (uVar19 = BndStrg_IsClientStay(param_1,iVar6,puVar37), uVar19 == 0)) {
                  if ((*(char *)(iVar35 + 0xa2a42) == '\0') ||
                     (pbVar21 = (byte *)(iVar35 + 0xa2a43), 3 < *pbVar21)) goto LAB_00012b20;
                  local_3c = 0;
                  local_40 = uVar19;
                  local_dc = HcGetBandByWdev("======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                             + param_1 + iVar29 + 0xe0);
                  if (local_dc == 0) {
                    uVar19 = (uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                         [param_1 + 0xdb];
                  }
                  else {
                    uVar19 = 0;
                  }
                  pcVar31 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                            + param_1 + uVar19 * 0x5834 + 0xe0;
                  if (pcVar31 == (char *)0x0) {
                    cVar25 = '\x01';
                  }
                  else {
                    local_40 = *(uint *)(pcVar31 + 0x21);
                    local_3c = *(undefined2 *)(pcVar31 + 0x25);
                    cVar25 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                             [param_1 + uVar19 * 0x5834 + 0xfa];
                  }
                  ZTE_Send_Btm_Req(param_1,"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                           [(uint)bVar26 * 0x5834 + param_1 + 0xee],local_f4,cVar25,
                                   &local_40);
                  *pbVar21 = *pbVar21 + 1;
                }
              }
            }
            else if (*pcVar20 != '\x01') {
              if (1 < DebugLevel) {
                printk("STA-%02x:%02x:%02x:%02x:%02x:%02x had left (%d %lu)\n",*local_f4,*local_e0,
                       *local_e4,*local_ec,*local_e8,*local_f0,*(uint *)(iVar35 + 0xa299c),
                       *(uint *)(&DAT_0036b910 + param_1));
              }
              goto LAB_00012b20;
            }
LAB_00012e08:
            iVar6 = RTMPAvgRssi(param_1,iVar35 + 0xa1e28);
            if ("RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n"[uVar28 * 0x5834 + param_1 + 0x19] !=
                '\0') {
              iVar8 = (int)"RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n"
                           [uVar28 * 0x5834 + param_1 + 0x19];
              bVar41 = SCARRY4(iVar6,0x7f);
              iVar29 = iVar6 + 0x7f;
              if (iVar6 != -0x7f) {
                bVar41 = SBORROW4(iVar8,iVar6);
                iVar29 = iVar8 - iVar6;
              }
              if ((iVar6 != -0x7f && iVar8 != iVar6) && iVar29 < 0 == bVar41) goto LAB_00012b64;
            }
            if ((*pcVar20 == '\x01') &&
               (*(char *)(local_104 + 0x2f72c) == '\x05' || *(char *)(local_104 + 0x2f72c) == '\0'))
            {
              if (*(int *)(local_104 + 0x2f714) != 0) {
                uVar19 = *(int *)(local_104 + 0x2f754) + 1;
                *(uint *)(local_104 + 0x2f754) = uVar19;
                if (5 < uVar19) {
                  if (*(code **)(*(int *)("Get_RBIST_Raw_Data_Proc" + param_1 + 0x14) + 8) !=
                      (code *)0x0) {
                    (**(code **)(*(int *)("Get_RBIST_Raw_Data_Proc" + param_1 + 0x14) + 8))
                              (param_1,*local_f8);
                  }
                  *(undefined4 *)(local_104 + 0x2f754) = 0;
                  iVar6 = DebugLevel;
                  iVar29 = (uint)*local_fc * 0x5834 + param_1 +
                           (((uint)*(ushort *)(iVar35 + 0xa1e18) << 0x15) >> 0x18);
                  "vow_watf_q_lv1: %d\n"[iVar29 + 0x13] =
                       "vow_watf_q_lv1: %d\n"[iVar29 + 0x13] &
                       ~*(byte *)((int)&NUM_BIT8 + (*(ushort *)(iVar35 + 0xa1e18) & 7));
                  if (2 < iVar6) {
                    printk("%s():Clear WCID[%d] packets\n","MacTableMaintenance",*local_f8);
                  }
                }
              }
            }
            else {
              *(undefined4 *)(local_104 + 0x2f754) = 0;
            }
            UAPSD_QueueMaintenance(param_1,puVar37);
            if ((*(uint *)(iVar35 + 0xa1dd4) & 0x100000) == 0) {
              iVar6 = HcGetBandByWdev(*piVar32);
              *(undefined1 *)(iVar14 + iVar6 + 0x1e493f) = 0;
            }
            if (((*(char *)(iVar35 + 0xa2a31) != '\0') && ((*(byte *)(param_1 + 0x795652) & 4) != 0)
                ) && (*(char *)(param_1 + 0x79564e) == '\x01')) {
              SendNotifyBWActionFrame(param_1,*local_f8,*local_fc);
            }
            iVar6 = uVar36 * 0x14c0 + iVar14;
            if (((*(byte *)(iVar6 + 0xddc) & 0x3f) != 0x20) && ((*(byte *)(iVar6 + 0xddc) & 7) < 2))
            {
              *(undefined1 *)(param_1 + 0x285949) = 0;
            }
            iVar6 = uVar28 * 0x5834 + param_1;
            *(bool *)(param_1 + 0x285941) =
                 (*(ushort *)(uVar36 * 0x14c0 + iVar14 + 0xddc) & 0x180) == 0x80;
            if (("Query::OID_802_11_STATISTICS\n"[iVar6 + 0x18] != '\0') &&
               ("%s: per %u.\n"[iVar6] != '\0')) {
              uVar19 = *(uint *)(param_1 + 0x82921c) % 10;
              if (uVar19 == 0) {
                if (*(char *)(param_1 + 0xa7cbe8) == '\x01') {
                  if (("Query::OID_802_11_STATISTICS(mem alloc failed)\n"[iVar6 + 8] != '\0') &&
                     ("Query::OID_802_11_STATISTICS(mem alloc failed)\n"[iVar6 + 0xc] == '\0')) {
                    "Query::OID_802_11_STATISTICS(mem alloc failed)\n"[iVar6 + 0xc] = '\x01';
                    "Query::OID_802_11_STATISTICS(mem alloc failed)\n"[iVar6 + 8] =
                         "Query::OID_802_11_STATISTICS(mem alloc failed)\n"[iVar6 + 8] + -1;
                  }
                  bVar41 = (bool)(bVar2 ^ 1);
                  if (*(char *)(param_1 + 0xa7cbe9) == '\0') {
                    bVar41 = false;
                  }
                  if (bVar41) {
                    bVar2 = 1;
                    *(char *)(param_1 + 0xa7cbe9) = *(char *)(param_1 + 0xa7cbe9) + -1;
                  }
                  iVar6 = uVar28 * 0x5834 + param_1;
                  if ((("Query::OID_802_11_STATISTICS(mem alloc failed)\n"[iVar6 + 9] == '\0') &&
                      ("Query::OID_802_11_STATISTICS(mem alloc failed)\n"[iVar6 + 8] == '\0')) &&
                     (*(char *)(param_1 + 0xa7cbe9) == '\0')) {
                    send_igmpv3_gen_query_pkt(param_1,puVar37);
                    "Query::OID_802_11_STATISTICS(mem alloc failed)\n"[iVar6 + 9] = '\x01';
                  }
                }
                if (*(char *)(param_1 + 0xa7cbea) == '\x01') {
                  iVar6 = uVar28 * 0x5834 + param_1;
                  if (("Query::OID_802_11_STATISTICS(mem alloc failed)\n"[iVar6 + 10] != '\0') &&
                     ("Query::OID_802_11_STATISTICS(mem alloc failed)\n"[iVar6 + 0xd] == '\0')) {
                    "Query::OID_802_11_STATISTICS(mem alloc failed)\n"[iVar6 + 0xd] = '\x01';
                    "Query::OID_802_11_STATISTICS(mem alloc failed)\n"[iVar6 + 10] =
                         "Query::OID_802_11_STATISTICS(mem alloc failed)\n"[iVar6 + 10] + -1;
                  }
                  bVar41 = (bool)(bVar13 ^ 1);
                  if (*(char *)(param_1 + 0xa7cbeb) == '\0') {
                    bVar41 = false;
                  }
                  if (bVar41) {
                    bVar13 = 1;
                    *(char *)(param_1 + 0xa7cbeb) = *(char *)(param_1 + 0xa7cbeb) + -1;
                  }
                  iVar6 = uVar28 * 0x5834 + param_1;
                  if ((("Query::OID_802_11_STATISTICS(mem alloc failed)\n"[iVar6 + 0xb] == '\0') &&
                      ("Query::OID_802_11_STATISTICS(mem alloc failed)\n"[iVar6 + 10] == '\0')) &&
                     (*(char *)(param_1 + 0xa7cbeb) == '\0')) {
                    send_mldv2_gen_query_pkt(param_1,puVar37);
                    "Query::OID_802_11_STATISTICS(mem alloc failed)\n"[iVar6 + 0xb] = '\x01';
                  }
                }
              }
              else if (uVar19 == 1) {
                if (*(char *)(param_1 + 0xa7cbe9) == '\0') {
                  *(undefined1 *)(param_1 + 0xa7cbe9) = 6;
                }
                if (*(char *)(param_1 + 0xa7cbeb) == '\0') {
                  *(undefined1 *)(param_1 + 0xa7cbeb) = 6;
                }
                iVar6 = uVar28 * 0x5834 + param_1;
                if ("Query::OID_802_11_STATISTICS(mem alloc failed)\n"[iVar6 + 9] == '\x01') {
                  "Query::OID_802_11_STATISTICS(mem alloc failed)\n"[iVar6 + 9] = '\0';
                }
                iVar6 = uVar28 * 0x5834 + param_1;
                if ("Query::OID_802_11_STATISTICS(mem alloc failed)\n"[iVar6 + 0xb] == '\x01') {
                  "Query::OID_802_11_STATISTICS(mem alloc failed)\n"[iVar6 + 0xb] = '\0';
                }
                iVar6 = uVar28 * 0x5834 + param_1;
                "Query::OID_802_11_STATISTICS(mem alloc failed)\n"[iVar6 + 0xc] = '\0';
                "Query::OID_802_11_STATISTICS(mem alloc failed)\n"[iVar6 + 0xd] = '\0';
              }
            }
            goto LAB_00011ef4;
          }
          if (*(char *)(param_1 + 0xa7d080) == '\x01') {
            if (0 < DebugLevel) {
              printk("skip ageout: %02x:%02x:%02x:%02x:%02x:%02x aleady slient for %d-sece\n",
                     *local_f4,*local_e0,*local_e4,*local_ec,*local_e8,*local_f0,uVar7);
            }
            goto LAB_00012e08;
          }
          if (1 < DebugLevel) {
            printk("ageout %02x:%02x:%02x:%02x:%02x:%02x after %d-sec silence\n",*local_f4,*local_e0
                   ,*local_e4,*local_ec,*local_e8,*local_f0,*(uint *)(iVar35 + 0xa2828));
          }
LAB_00012b20:
          iVar6 = RTMPAvgRssi(param_1,iVar35 + 0xa1e28);
          if ("RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n"[uVar28 * 0x5834 + param_1 + 0x19] != '\0'
             ) {
            iVar8 = (int)"RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n"
                         [uVar28 * 0x5834 + param_1 + 0x19];
            bVar41 = SCARRY4(iVar6,0x7f);
            iVar29 = iVar6 + 0x7f;
            if (iVar6 != -0x7f) {
              bVar41 = SBORROW4(iVar6,iVar8);
              iVar29 = iVar6 - iVar8;
            }
            if (iVar29 < 0 == bVar41) goto LAB_00012b74;
LAB_00012b64:
            if (1 < DebugLevel) {
              printk("Disassoc STA %02x:%02x:%02x:%02x:%02x:%02x , RSSI Kickout Thres[%d]-[%d]\n",
                     *local_f4,*local_e0,*local_e4,*local_ec,*local_e8,*local_f0,iVar8,
                     (int)(char)iVar6);
            }
          }
LAB_00012b74:
          local_4a = 0;
          if (*(int *)(iVar35 + 0xa1e1c) == 2) {
            local_48 = 0;
            local_44 = 0;
            iVar6 = os_alloc_mem(param_1,&local_48,0x900);
            if (iVar6 != 0) {
              if (2 < DebugLevel) {
                printk(" MlmeAllocateMemory fail  ..\n");
              }
              goto LAB_00011ef4;
            }
            local_4a = 3;
            if (1 < DebugLevel) {
              printk("Send DEAUTH - Reason = %d frame  TO %02x:%02x:%02x:%02x:%02x:%02x\n",3,
                     *local_f4,*local_e0,*local_e4,*local_ec,*local_e8,*local_f0);
            }
            iVar6 = param_1 + uVar28 * 0x5834;
            MgtMacHeaderInit(param_1,&local_40,0xc,0,local_f4,
                             "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                             + iVar6 + 0xfb,
                             "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                             + iVar6 + 0x101);
            MakeOutgoingFrame(local_48,&local_44,0x18,&local_40,2,&local_4a,0xffffffff);
            MiniportMMRequest(param_1,0,local_48,local_44);
            os_free_mem(local_48);
            ZTE_Notify_Node_AD(0,puVar37);
            wlan_dbg_save_staoffline_record(puVar37,local_4a,0xbca,"MacTableMaintenance");
          }
          __ZTE_STA_Assoc_Process(param_1,0x11,0,0,local_4a,0,puVar37,"MacTableMaintenance",0xbcf);
        }
        else {
          __ZTE_STA_Assoc_Process(param_1,0x11,0,0,0,0,puVar37,"MacTableMaintenance",0xa6a);
          if (2 < DebugLevel) {
            printk("%02x:%02x:%02x:%02x:%02x:%02x fail to complete ASSOC in %lu sec\n",*local_f4,
                   *local_e0,*local_e4,*local_ec,*local_e8,*local_f0,
                   *(undefined4 *)(iVar35 + 0xa2810));
          }
          iVar6 = memcmp(local_f4,"%s(): FIXME!!!Unexpected frame send to MgmtRing, need to assign the length!\n"
                                  + uVar28 * 0x5834 + param_1 + 0x31,6);
          if (iVar6 == 0) {
            __memzero("%s(): FIXME!!!Unexpected frame send to MgmtRing, need to assign the length!\n"
                      + uVar28 * 0x5834 + param_1 + 0x31,6);
          }
        }
        mac_entry_delete(param_1,puVar37);
      }
      else {
        *(undefined4 *)(iVar35 + 0xa3098) = 0;
      }
    }
LAB_00011ef4:
    puVar37 = puVar37 + 0x530;
    iVar35 = iVar35 + 0x14c0;
    local_110 = local_110 + 0x530;
    piVar32 = piVar32 + 0x530;
    puVar34 = puVar34 + 0x530;
    local_114 = local_114 + 0x530;
    local_104 = local_104 + 0x620;
    local_fc = local_fc + 0x14c0;
    local_108 = local_108 + 0x530;
    local_10c = local_10c + 0x530;
    local_118 = local_118 + 0x530;
    local_f8 = local_f8 + 0xa60;
    local_f4 = local_f4 + 0x14c0;
    local_e0 = local_e0 + 0x14c0;
    local_e4 = local_e4 + 0x14c0;
    local_ec = local_ec + 0x14c0;
    local_e8 = local_e8 + 0x14c0;
    local_f0 = local_f0 + 0x14c0;
    local_100 = local_100 + 0x530;
  }
  if ((*(byte *)(param_1 + 0x795652) & 4) != 0) {
    *(byte *)(param_1 + 0x795652) = *(byte *)(param_1 + 0x795652) & 0xfb;
  }
  if (local_68 != 0) {
    apcli_dync_txop_alg(param_1,local_68,local_8c >> 0x11,local_88 >> 0x11);
  }
  sVar5 = txopfe;
  if (local_6c == 1) {
    if (*(char *)(param_1 + 0xa7c2fe) == '\0') {
      *(int *)(param_1 + 0xa7c300) = local_60;
      *(undefined1 *)(param_1 + 0xa7c2fe) = 1;
      enable_tx_burst(param_1,local_60,2,4,sVar5);
    }
    else if (*(int *)(param_1 + 0xa7c300) != local_60) {
      disable_tx_burst(param_1,*(int *)(param_1 + 0xa7c300),2,4,txop0);
      enable_tx_burst(param_1,local_60,2,4,txopfe);
      *(int *)(param_1 + 0xa7c300) = local_60;
    }
  }
  else if (*(char *)(param_1 + 0xa7c2fe) == '\x01') {
    disable_tx_burst(param_1,*(undefined4 *)(param_1 + 0xa7c300),2,4,txop0);
    *(undefined1 *)(param_1 + 0xa7c2fe) = 0;
    *(undefined4 *)(param_1 + 0xa7c300) = 0;
  }
  bVar13 = *(byte *)(param_1 + 0xa797a4);
  iVar14 = 0;
  pcVar20 = (char *)(param_1 + 0xa7c41c);
  do {
    if ((bVar13 == 2) && (*(char *)(param_1 + 0xa7a319) != '\0')) {
      if (pcVar20[0xc] == '\x01') {
        pcVar20[0xc] = '\0';
        disable_tx_burst(param_1,*(undefined4 *)(pcVar20 + 8),2,2,txop0);
      }
    }
    else if ((pcVar20[1] == '\x10') || (*pcVar20 == '\x10')) {
      if (*(ushort *)(param_1 + 0x285920) < 100) {
        if (pcVar20[4] == '\0') {
          if ((bVar13 < 3) && (pcVar20[0xc] == '\0')) {
            pcVar20[0xc] = '\x01';
            if (2 < DebugLevel) {
              printk("%s[%d] enable_tx_burst TXOP_0\n","dynamic_txop_adjust",0x66c);
            }
            enable_tx_burst(param_1,*(undefined4 *)(pcVar20 + 8),2,2,txop0);
          }
        }
        else if (pcVar20[0xc] == '\x01') {
          pcVar20[0xc] = '\0';
          if (2 < DebugLevel) {
            printk("%s[%d] disable_tx_burst TXOP_0\n","dynamic_txop_adjust",0x663);
          }
          uVar9 = *(undefined4 *)(pcVar20 + 8);
          goto LAB_00014384;
        }
      }
      else {
        bVar13 = *(byte *)(param_1 + iVar14 * 0x20 + 0xa7c3f4);
        if (bVar13 == 2) {
          if (pcVar20[0xc] == '\0') {
            pcVar20[0xc] = '\x01';
            enable_tx_burst(param_1,*(undefined4 *)(pcVar20 + 8),2,2,txop0);
          }
        }
        else if ((bVar13 < 2) && (pcVar20[0xc] == '\x01')) {
          pcVar20[0xc] = '\0';
          enable_tx_burst(param_1,*(undefined4 *)(pcVar20 + 8),2,2,txop80);
        }
      }
    }
    else if (pcVar20[0xc] == '\x01') {
      uVar9 = *(undefined4 *)(pcVar20 + 8);
      pcVar20[0xc] = '\0';
LAB_00014384:
      disable_tx_burst(param_1,uVar9,2,2,txop0);
    }
    pcVar20 = pcVar20 + 0x10;
    if (iVar14 == 1) break;
    bVar13 = *(byte *)(param_1 + 0xa797a4);
    iVar14 = 1;
  } while( true );
  if (*(short *)(param_1 + 0xa7c41c) == 0) {
    iVar14 = 1;
    if (*(short *)(param_1 + 0xa7c42c) != 0) goto LAB_00013810;
  }
  else {
    iVar14 = 0;
    if (*(short *)(param_1 + 0xa7c42c) == 0) {
LAB_00013810:
      iVar33 = *(int *)(param_1 + (iVar14 + 0xa7c42) * 0x10 + 4);
      if ((*(ushort *)(iVar33 + 0x18) & 0x4e) == 0) {
        if ((*(ushort *)(iVar33 + 0x18) & 0xb1) == 0) {
          if (-1 < DebugLevel) {
            printk("%s[%d]\n","dynamic_amsdu_protect_adjust",0x6a7);
          }
          goto LAB_00013a50;
        }
        uVar36 = 0x578;
      }
      else {
        uVar36 = 0x400;
      }
      iVar35 = param_1 + iVar14 * 0x10;
      bVar13 = *(byte *)(iVar35 + 0xa7c41c);
      if ((bVar13 == 0x10) || (*(char *)(iVar35 + 0xa7c41d) == '\x10')) {
        iVar35 = iVar14 * 8;
        bVar40 = true;
        if (*(uint *)(param_1 + iVar14 * 0x70 + 0xa7c43c) < 0x3d) {
          cVar25 = '\x04';
        }
        else {
          cVar25 = '\x02';
        }
      }
      else if (bVar13 < 2) {
        bVar40 = false;
        cVar25 = '\x04';
        iVar35 = iVar14 << 3;
      }
      else {
        iVar35 = iVar14 * 8;
        uVar28 = *(uint *)(param_1 + iVar14 * 0x70 + 0xa7c43c);
        if (uVar36 < uVar28) {
          bVar40 = false;
          cVar25 = '\x01';
        }
        else {
          bVar40 = false;
          if (uVar28 < 0x3d) {
            cVar25 = '\x04';
          }
          else {
            cVar25 = '\x02';
          }
        }
      }
      cVar1 = *(char *)(param_1 + (iVar35 - iVar14) * 0x10 + 0xa7c449);
      if (cVar1 != cVar25) {
        if (2 < DebugLevel) {
          printk("%s(): change amsdu %d to %d\n","dynamic_amsdu_protect_adjust",cVar1,cVar25);
        }
        *(char *)(param_1 + (iVar35 - iVar14) * 0x10 + 0xa7c449) = cVar25;
        uVar36 = hc_get_asic_cap(*(undefined4 *)(param_1 + 0xa797a0));
        if ((uVar36 & 0x400) == 0) {
          *(undefined1 *)(param_1 + 0x285c4c) = 4;
        }
        else {
          MtCmdCr4Set(param_1,0xd,0xff,4);
        }
      }
      *(undefined1 *)(param_1 + 0xa7cbec) = 0;
      if ((((*(char *)(param_1 + 0xa797a4) == '\x02') && (*(char *)(param_1 + 0xa7a319) != '\0')) ||
          (*(char *)(param_1 + iVar14 * 0x10 + 0xa7c420) != '\0')) || (!bVar40)) {
        iVar6 = param_1 + (iVar35 - iVar14) * 0x10;
        if (*(char *)(iVar6 + 0xa7c468) == '\0') {
          iVar29 = param_1 + iVar14 * 0x108;
          *(undefined4 *)(iVar6 + 0xa7c458) = *(undefined4 *)(iVar29 + 0xa39ca0);
          *(undefined4 *)(iVar6 + 0xa7c45c) = *(undefined4 *)(iVar29 + 0xa39c98);
        }
        iVar14 = param_1 + (iVar35 - iVar14) * 0x10;
        if (*(char *)(iVar14 + 0xa7c454) == '\x01') {
          asic_rts_on_off(iVar33);
          *(undefined1 *)(iVar14 + 0xa7c454) = 0;
          if (1 < DebugLevel) {
            printk("%s(): enable RTS\n","dynamic_amsdu_protect_adjust");
          }
        }
      }
      else {
        iVar35 = param_1 + (iVar35 - iVar14) * 0x10;
        iVar14 = param_1 + iVar14 * 0x108;
        iVar8 = *(int *)(iVar14 + 0xa39ca0);
        iVar29 = *(int *)(iVar14 + 0xa39c98);
        iVar6 = iVar8 - *(int *)(iVar35 + 0xa7c458);
        iVar14 = *(int *)(iVar35 + 0xa7c45c);
        *(int *)(iVar35 + 0xa7c458) = iVar8;
        *(int *)(iVar35 + 0xa7c45c) = iVar29;
        if (iVar6 != 0) {
          iVar29 = iVar29 - iVar14;
          uVar36 = __aeabi_uidiv(iVar29 * 100,iVar29 + iVar6);
          if (*(char *)(iVar35 + 0xa7c454) == '\0') {
            if (uVar36 < 3) {
              asic_rts_on_off(iVar33);
              *(undefined1 *)(iVar35 + 0xa7c454) = 1;
              if (1 < DebugLevel) {
                printk("%s(): disable RTS, per=%lu\n","dynamic_amsdu_protect_adjust",uVar36);
              }
            }
          }
          else if (*(char *)(iVar35 + 0xa7c454) == '\x01' && 8 < uVar36) {
            asic_rts_on_off(iVar33,1);
            *(undefined1 *)(iVar35 + 0xa7c454) = 0;
            if (1 < DebugLevel) {
              printk("%s(): enable RTS, per=%lu\n","dynamic_amsdu_protect_adjust",uVar36);
            }
          }
        }
      }
    }
  }
LAB_00013a50:
  uVar36 = *(uint *)(param_1 + 0xa7c424);
  if ((uVar36 == 0) || ((*(ushort *)(uVar36 + 0x18) & 0xb1) == 0)) {
    uVar36 = *(uint *)(param_1 + 0xa7c434);
    if ((uVar36 != 0) && ((*(ushort *)(uVar36 + 0x18) & 0xb1) != 0)) goto LAB_00013b60;
  }
  else {
    uVar28 = *(uint *)(param_1 + 0xa7c434);
    if (uVar28 == 0) {
LAB_00013b60:
      cVar25 = *(char *)(param_1 + 0xa7a312);
    }
    else {
      if ((*(ushort *)(uVar28 + 0x18) & 0xb1) != 0) {
        uVar36 = uVar28;
      }
      cVar25 = *(char *)(param_1 + 0xa7a312);
    }
    if (cVar25 == '\0') {
      if (*(char *)(param_1 + 0xa7c439) == '\x01') {
        disable_tx_burst(param_1,uVar36,2,3,txop0);
        *(undefined1 *)(param_1 + 0xa7c439) = 0;
      }
    }
    else {
      bVar13 = 0;
      bVar2 = 0;
      for (uVar28 = 0; uVar19 = HcGetMaxStaNum(param_1), uVar28 < uVar19; uVar28 = uVar28 + 1) {
        if (((*puVar18 != 0) && (puVar18[2] == uVar36)) && (0x14 < puVar18[0x4db])) {
          getRate(puVar18[0x4d],&local_40);
          if (local_40 < *(ushort *)(param_1 + 0xa7a316)) {
            if (local_40 <= *(ushort *)(param_1 + 0xa7a314)) {
              bVar13 = 1;
            }
          }
          else {
            bVar2 = 1;
          }
        }
        puVar18 = puVar18 + 0x530;
      }
      if ((bool)(bVar2 & bVar13)) {
        if (*(char *)(param_1 + 0xa7c439) == '\0') {
          enable_tx_burst(param_1,uVar36,2,3,txop0);
          iVar14 = DebugLevel;
          *(undefined1 *)(param_1 + 0xa7c439) = 1;
          if (2 < iVar14) {
            printk("%s(): PRIO_NEAR_FAR: start\n","dynamic_near_far_adjust");
          }
        }
      }
      else if (*(char *)(param_1 + 0xa7c439) == '\x01') {
        disable_tx_burst(param_1,uVar36,2,3,txop0);
        iVar14 = DebugLevel;
        *(byte *)(param_1 + 0xa7c439) = bVar2 & bVar13;
        if (2 < iVar14) {
          printk("%s(): PRIO_NEAR_FAR: end\n","dynamic_near_far_adjust");
        }
      }
    }
  }
  if (*(char *)(param_1 + 0xa7a2ea) != '\0') {
    if (*(char *)(param_1 + 0xa7c41c) == '\0') {
      if (*(char *)(param_1 + 0xa7c42c) == '\0') goto LAB_00013c4c;
      iVar14 = 1;
    }
    else {
      iVar14 = 0;
      if (*(char *)(param_1 + 0xa7c42c) != '\0') goto LAB_00013c4c;
    }
    uVar27 = *(ushort *)(*(int *)(param_1 + (iVar14 + 0xa7c42) * 0x10 + 4) + 0x18);
    if ((uVar27 & 0x4e) == 0) {
      if ((uVar27 & 0xb1) == 0) {
        if (-1 < DebugLevel) {
          printk("%s[%d]\n","dynamic_airtime_fairness_adjust",1999);
        }
        goto LAB_00013c4c;
      }
      uVar36 = 0x578;
    }
    else {
      uVar36 = 0x400;
    }
    bVar13 = *(byte *)(param_1 + iVar14 * 0x10 + 0xa7c41c);
    if (bVar13 == 0x10) {
      bVar40 = 0x3c < *(uint *)(param_1 + 0xa7be38);
    }
    else if (bVar13 < 2) {
      bVar40 = false;
    }
    else {
      uVar28 = *(uint *)(param_1 + 0xa7be38);
      bVar41 = 0x3b < uVar28;
      bVar40 = uVar28 == 0x3c;
      if (uVar28 < 0x3d) {
        bVar41 = uVar36 <= uVar28;
        bVar40 = uVar28 == uVar36;
      }
      if (bVar41 && !bVar40) {
        bVar40 = true;
      }
      else {
        bVar40 = false;
      }
    }
    if ((2 < *(byte *)(param_1 + 0xa797a4)) && (0x200 < *(uint *)(param_1 + 0xa7be38))) {
      bVar40 = false;
    }
    if ((((bool)*(char *)(param_1 + 0xa7be36) != bVar40) &&
        (*(bool *)(param_1 + 0xa7be36) = bVar40, *(char *)(param_1 + 0xa7be35) != '\0')) &&
       (iVar14 = vow_watf_is_enabled(param_1), iVar14 == 0)) {
      bVar41 = *(byte *)(param_1 + 0xa7cbec) == 1;
      if (*(byte *)(param_1 + 0xa7cbec) < 2) {
        bVar41 = bVar13 == 0x10;
      }
      if (bVar40 != true) {
        bVar41 = false;
      }
      if (bVar41) {
        uVar23 = *(undefined1 *)(param_1 + 0xa7be35);
      }
      else {
        uVar23 = 0;
      }
      RTMP_SET_STA_DWRR_QUANTUM(param_1,!bVar41,uVar23);
    }
  }
LAB_00013c4c:
  iVar14 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if ((*(char *)(iVar14 + 0x1e0) != '\0') && (*(char *)(iVar14 + 0x15a) != '\0')) {
    pcVar20 = (char *)(param_1 + 0xa7c3dc);
    do {
      if (*pcVar20 != '\0') {
        if (pcVar20[0x18] == '\x02') {
          if (*(uint *)(iVar14 + 0x1e4) < *(uint *)(pcVar20 + 0x14)) goto LAB_00014b54;
        }
        else if ((pcVar20[0x18] == '\x01') &&
                (*(uint *)(iVar14 + 0x1e8) < *(uint *)(pcVar20 + 0x10))) {
LAB_00014b54:
          *(undefined1 *)(param_1 + 0x285bd8) = 1;
          goto LAB_00014540;
        }
        *(undefined1 *)(param_1 + 0x285bd8) = 0;
      }
LAB_00014540:
      pcVar20 = pcVar20 + 0x20;
    } while (pcVar20 != (char *)(param_1 + 0xa7c41c));
  }
  iVar33 = 0;
  iVar35 = 0;
  cVar25 = '\0';
  bVar40 = false;
  iVar14 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  sVar5 = *(short *)(iVar14 + 0x226);
  local_118 = (uint *)0x0;
  do {
    if (3 < DebugLevel) {
      printk("[%s] BandIdx:%d\n","dynamic_ampdu_efficiency_adjust_all",iVar33);
    }
    iVar6 = iVar33 * 0x20;
    if (*(char *)(param_1 + iVar6 + 0xa7c3dc) == '\0') {
      iVar29 = iVar33 << 4;
      goto LAB_00013db8;
    }
    iVar35 = *(int *)(param_1 + iVar6 + 0xa7c3e0);
    iVar8 = *(int *)(param_1 + iVar33 * 0x108 + 0xa39ca0);
    if ((*(ushort *)(iVar35 + 0x18) & 0x4e) == 0) {
      if ((*(ushort *)(iVar35 + 0x18) & 0xb1) != 0) {
        if (*(char *)(param_1 + 0x79504d) == '\0') {
          uVar36 = *(uint *)(iVar14 + 0x1d4);
        }
        else {
          uVar36 = *(uint *)(iVar14 + 0x1dc);
        }
        goto LAB_00013d20;
      }
      if (-1 < DebugLevel) {
        printk("%s[%d]\n","dynamic_ampdu_efficiency_adjust_all",0x10c0);
      }
    }
    else {
      bVar40 = true;
      if (*(char *)(param_1 + 0x79504d) == '\0') {
        uVar36 = *(uint *)(iVar14 + 0x1d0);
      }
      else {
        uVar36 = *(uint *)(iVar14 + 0x1d8);
      }
LAB_00013d20:
      local_10c = (uint *)(uVar36 & 0xffff);
      if (3 < DebugLevel) {
        printk("%s[%d] multi_client_nums = %d\n","dynamic_ampdu_efficiency_adjust_all",0x10c5,
               *(undefined1 *)(param_1 + iVar33 * 0x10 + 0xa7c41c));
      }
      iVar29 = iVar33 * 0x10;
      if (((*(char *)(param_1 + iVar29 + 0xa7c41d) == '\x10') &&
          (99 < *(ushort *)(param_1 + 0x285920))) &&
         (*(char *)(param_1 + iVar6 + 0xa7c3f4) == '\x02')) {
        cVar25 = '\x01';
      }
      if (*(char *)(param_1 + iVar29 + 0xa7c41c) == '\x10') {
LAB_00013db8:
        if (*(char *)(param_1 + iVar6 + 0xa7c3f8) != '\0') {
LAB_000142c0:
          uVar36 = query_tx_burst_prio(param_1,iVar35);
          if (6 < uVar36) {
            iVar8 = HcGetEdca(param_1,iVar35);
            if (iVar8 != 0) {
              AsicAmpduEfficiencyAdjust(iVar35,*(undefined1 *)(iVar8 + 7));
            }
            *(undefined1 *)(param_1 + iVar6 + 0xa7c3f8) = 0;
          }
        }
      }
      else {
        if (iVar8 != 0) {
          iVar15 = *(int *)(param_1 + iVar33 * 0x108 + 0xa39c98);
          local_118 = (uint *)__aeabi_uidiv(iVar15 * 100,iVar15 + iVar8);
        }
        iVar8 = DebugLevel;
        sVar4 = txopfe;
        sVar3 = txop60;
        if (4 < local_118) {
          if (3 < DebugLevel) {
            printk("%s[%d]per=%lu\n","dynamic_ampdu_efficiency_adjust_all",0x10da,local_118);
          }
          goto LAB_00013db8;
        }
        if ((local_10c == (uint *)0x0) ||
           (iVar15 = param_1 + iVar6, *(uint *)(iVar15 + 0xa7c3ec) <= local_10c)) {
          iVar15 = param_1 + iVar6;
          if (*(char *)(iVar15 + 0xa7c3f4) != '\x01') goto LAB_00014408;
          if (0x3a < *(uint *)(iVar15 + 0xa7c3ec) - 0x3d) {
            if (((*(ushort *)(iVar35 + 0x18) & 0xb1) != 0) && (0x78 < *(uint *)(iVar15 + 0xa7c3ec)))
            {
              *(undefined1 *)(param_1 + (iVar33 + 0x53e1f) * 0x20 + 8) = 1;
              if (*(short *)(iVar15 + 0xa7c3f6) == 0x200) {
                sVar5 = 0x200;
                goto LAB_00014e34;
              }
              *(undefined1 *)(iVar15 + 0xa7c3f5) = 0;
              sVar5 = 0x200;
              goto LAB_000145c4;
            }
            goto LAB_00014408;
          }
          *(undefined1 *)(param_1 + (iVar33 + 0x53e1f) * 0x20 + 8) = 1;
          sVar5 = *(short *)(iVar15 + 0xa7c3f6);
          if (sVar3 != sVar5) {
            *(undefined1 *)(iVar15 + 0xa7c3f5) = 0;
            sVar5 = sVar3;
LAB_000145c4:
            if (3 < DebugLevel) {
              uVar17 = 0;
              uVar23 = *(undefined1 *)(param_1 + (iVar33 + 0x53e1f) * 0x20 + 8);
              goto LAB_00014e58;
            }
            goto LAB_000145d0;
          }
LAB_00014e34:
          if (3 < DebugLevel) {
            uVar23 = 1;
            uVar17 = *(undefined1 *)(param_1 + iVar6 + 0xa7c3f5);
            goto LAB_00014e58;
          }
LAB_000145e0:
          iVar8 = param_1 + iVar6;
          if (*(char *)(iVar8 + 0xa7c3f8) == '\0') {
            if (*(char *)(*(int *)(param_1 + (iVar33 + 0x53e1f) * 0x20 + 4) + 0xc9f) == '\0') {
              uVar36 = query_tx_burst_prio(param_1,iVar35);
              if (uVar36 < 7) {
                AsicAmpduEfficiencyAdjust(iVar35,0xf);
                *(undefined1 *)(iVar8 + 0xa7c3f8) = 1;
                goto LAB_000142a4;
              }
              if (*(char *)(iVar8 + 0xa7c3f5) != '\0') goto LAB_00013db8;
            }
            else if (*(char *)(iVar8 + 0xa7c3f5) != '\0') goto LAB_00013dd4;
LAB_0001461c:
            enable_tx_burst(param_1,iVar35,2,6,sVar5);
            *(undefined1 *)(param_1 + iVar6 + 0xa7c3f5) = 1;
            *(short *)(param_1 + iVar6 + 0xa7c3f6) = sVar5;
            goto LAB_00013db8;
          }
LAB_000142a4:
          if (*(char *)(param_1 + iVar6 + 0xa7c3f5) == '\0') goto LAB_0001461c;
          goto LAB_000142c0;
        }
        if (*(char *)(iVar15 + 0xa7c3f4) == '\x01') {
          *(undefined1 *)(param_1 + (iVar33 + 0x53e1f) * 0x20 + 8) = 1;
          sVar5 = *(short *)(iVar15 + 0xa7c3f6);
          if (sVar4 == sVar5) goto LAB_00014e34;
          *(undefined1 *)(iVar15 + 0xa7c3f5) = 0;
          sVar5 = sVar4;
          goto LAB_000145c4;
        }
LAB_00014408:
        uVar23 = 0;
        *(undefined1 *)(param_1 + (iVar33 + 0x53e1f) * 0x20 + 8) = 0;
        if (3 < iVar8) {
          uVar17 = *(undefined1 *)(param_1 + iVar6 + 0xa7c3f5);
LAB_00014e58:
          iVar8 = param_1 + iVar6;
          printk("%s[%d]per=%lu, tx=%d M, (%d, %d, %d, %d)\n\r",
                 "dynamic_ampdu_efficiency_adjust_all",0x1109,local_118,
                 *(undefined4 *)(iVar8 + 0xa7c3ec),uVar23,*(undefined1 *)(iVar8 + 0xa7c3f8),uVar17,
                 *(undefined1 *)(iVar8 + 0xa7c3f4));
LAB_000145d0:
          if (*(char *)(param_1 + (iVar33 + 0x53e1f) * 0x20 + 8) != '\0') goto LAB_000145e0;
        }
        if (*(char *)(param_1 + iVar6 + 0xa7c3f8) != '\0') {
          iVar8 = HcGetEdca(param_1,iVar35);
          if (iVar8 != 0) {
            AsicAmpduEfficiencyAdjust(iVar35,*(undefined1 *)(iVar8 + 7));
          }
          *(undefined1 *)(param_1 + iVar6 + 0xa7c3f8) = 0;
        }
        if (*(char *)(param_1 + iVar6 + 0xa7c3f5) != '\0') {
          disable_tx_burst(param_1,iVar35,2,6,sVar5);
          *(undefined1 *)(param_1 + iVar6 + 0xa7c3f5) = 0;
          goto LAB_00013db8;
        }
      }
LAB_00013dd4:
      iVar29 = param_1 + iVar29;
      if (*(char *)(iVar29 + 0xa7c42a) != cVar25) {
        if (*(char *)(iVar29 + 0xa7c42a) == '\0') {
          *(undefined1 *)(iVar29 + 0xa7c42a) = 1;
          if (bVar40) {
            uVar36 = 0x2040;
          }
          else {
            uVar36 = 0x2044;
          }
          mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),uVar36 | 0x820f0000,0xa00);
        }
        else {
          *(undefined1 *)(iVar29 + 0xa7c42a) = 0;
          if (bVar40) {
            uVar9 = 0x820f2040;
            uVar12 = *(undefined4 *)(param_1 + 0xa797a0);
          }
          else {
            uVar9 = 0x820f2044;
            uVar12 = *(undefined4 *)(param_1 + 0xa797a0);
          }
          mac_io_write32(uVar12,uVar9,0);
        }
      }
      iVar6 = param_1 + iVar6;
      *(undefined1 *)(iVar6 + 0xa7c3dc) = 0;
      *(undefined4 *)(iVar6 + 0xa7c3ec) = 0;
      *(undefined4 *)(iVar6 + 0xa7c3f0) = 0;
    }
    if (iVar33 == 1) {
      if ((*(char *)(param_1 + 0x795951) == '\0') ||
         (uVar36 = 1, *(char *)(param_1 + 0x285949) == '\0')) {
        uVar36 = 0;
      }
      if ((uint)(*(int *)(param_1 + 0xa39f84) << 9) >> 0x1f != uVar36) {
        AsicSetRalinkBurstMode(param_1,uVar36);
      }
      _raw_spin_lock_bh(param_1 + 0x285c50);
      if (*(int *)(param_1 + 0x285924) == 0) {
        *(undefined4 *)(param_1 + 0x285934) = 0;
      }
      else {
        uVar36 = *(int *)(param_1 + 0x285934) + 1;
        *(uint *)(param_1 + 0x285934) = uVar36;
        if (1 < uVar36) {
          APCleanupPsQueue(param_1,param_1 + 0x285924);
          *(undefined4 *)(param_1 + 0x285934) = 0;
          bVar13 = "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                   [param_1 + 0xda];
          uVar36 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
          if (uVar36 < bVar13) {
            uVar36 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
            "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
            [param_1 + 0xda] = (char)uVar36;
          }
          else {
            uVar36 = (uint)(byte)"======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                 [param_1 + 0xda];
          }
          if (uVar36 != 0) {
            bVar13 = ~(byte)NUM_BIT8;
            pbVar21 = (byte *)("vow_watf_q_lv1: %d\n" + param_1 + 0x13);
            do {
              *pbVar21 = *pbVar21 & bVar13;
              pbVar21 = pbVar21 + 0x5834;
            } while (pbVar21 != (byte *)("vow_watf_q_lv1: %d\n" + uVar36 * 0x5834 + param_1 + 0x13))
            ;
          }
        }
      }
      _raw_spin_unlock_bh(param_1 + 0x285c50);
      *(undefined1 *)(param_1 + 0xa7c41c) = 0;
      *(undefined1 *)(param_1 + 0xa7c41d) = 0;
      *(undefined1 *)(param_1 + 0xa7c420) = 0;
      *(undefined4 *)(param_1 + 0xa7c460) = 0;
      *(undefined4 *)(param_1 + 0xa7c464) = 0;
      *(undefined1 *)(param_1 + 0xa7c42c) = 0;
      *(undefined1 *)(param_1 + 0xa7c42d) = 0;
      *(undefined1 *)(param_1 + 0xa7c430) = 0;
      *(undefined4 *)(param_1 + 0xa7c4d0) = 0;
      *(undefined4 *)(param_1 + 0xa7c4d4) = 0;
      return;
    }
    iVar33 = 1;
  } while( true );
}

