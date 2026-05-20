// module: mt7915.ko
// function: RTMPIoctlStatistics @ 0x3a8c4
// size: 3380 bytes
//

void RTMPIoctlStatistics(int *param_1,int param_2)

{
  byte *pbVar1;
  byte *pbVar2;
  uint uVar3;
  byte bVar4;
  undefined4 *puVar5;
  int iVar6;
  size_t sVar7;
  int iVar8;
  undefined4 uVar9;
  uint uVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  int iVar16;
  undefined4 *puVar17;
  int *piVar18;
  char *pcVar19;
  int iVar20;
  int *piVar21;
  undefined4 *puVar22;
  char *pcVar23;
  char *pcVar24;
  bool bVar25;
  char *local_d0;
  undefined *local_cc;
  char *local_c8;
  uint uStack_c4;
  int *local_c0;
  int *local_bc;
  uint local_b8;
  uint local_b4;
  int *local_b0;
  int *local_ac;
  uint local_a8;
  int local_a4;
  int *local_a0;
  int local_9c;
  int *local_98;
  int local_94;
  int local_90;
  uint local_8c;
  byte local_81;
  int *local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  char local_70 [12];
  int local_64;
  int local_60;
  int local_5c;
  int local_54;
  byte local_44;
  byte local_42;
  char local_41;
  byte local_40;
  char local_3f;
  byte local_3e;
  byte local_3d;
  byte local_3b;
  byte local_39;
  char local_38;
  byte local_37;
  char local_36;
  byte local_35;
  byte local_34;
  
  iVar20 = *param_1;
  local_b0 = param_1 + 0x29c000;
  local_ac = param_1 + 0x29e400;
  local_a4 = param_2;
  iVar6 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(iVar20 + 0x3c),*(undefined4 *)(iVar20 + 0x38));
  local_7c = 0;
  local_78 = 0;
  local_74 = 0;
  local_a8 = hc_get_chip_cap(param_1[0x29e5e8]);
  local_70[0] = '\0';
  local_70[1] = '\0';
  local_70[2] = '\0';
  local_70[3] = '\0';
  local_81 = 0;
  os_alloc_mem(param_1,&local_80,0x800);
  if (local_80 != (int *)0x0) {
    if (iVar6 == 0) {
      os_free_mem();
      return;
    }
    iVar6 = HcGetBandByWdev(iVar6);
    __memzero(local_80,0x640);
    local_98 = &DebugLevel;
    *(undefined2 *)local_80 = 10;
    if (4 < DebugLevel) {
      printk("ra offload=%d\n",*(undefined1 *)(local_a8 + 0x150));
    }
    if (*(char *)(local_a8 + 0x150) == '\x01') {
      local_d0 = local_70 + 4;
      MtCmdGetTxStatistic(param_1,3,iVar6,0);
      param_1[iVar6 * 0x42 + 0x28e700] = (local_64 + param_1[iVar6 * 0x42 + 0x28e700]) - local_60;
      param_1[iVar6 * 0x42 + 0x28e704] = param_1[iVar6 * 0x42 + 0x28e704] + local_60;
      param_1[iVar6 * 0x42 + 0x28e72a] = local_5c + param_1[iVar6 * 0x42 + 0x28e72a];
      param_1[iVar6 * 0x42 + 0x28e72c] = local_54 + param_1[iVar6 * 0x42 + 0x28e72c];
      if ((local_44 & 7) < 4) {
        uVar10 = (uint)local_3e;
      }
      else {
        uVar10 = (uint)local_3e + (local_3d - 1 & 3) * 0x10;
      }
      param_1[0x28e7e7] =
           (local_44 & 7) << 0xd | (local_40 & 3) << 7 | (uint)(local_3f != '\0') << 6 |
           (uint)(local_41 != '\0') << 9 | (local_42 & 1) << 10 | uVar10 & 0x3f;
    }
    local_a0 = param_1 + 0x28c000;
    if (((param_1[0x28eb05] & 1U) == 0) &&
       ((local_b0[0x1eed] != 1 || ((*(uint *)(local_b0[0x1eee] + 0x4e0) & 1) == 0)))) {
      iVar16 = param_1[iVar6 * 0x42 + 0x28e700];
      if ((param_1[0xa5b19] & 0xffffU) == 0x7915) {
        uVar10 = 0x9cc8;
      }
      else {
        uVar10 = 0x9c48;
      }
      local_9c = *(int *)((int)param_1 + (uVar10 | 0xa30000) + iVar6 * 0x108);
    }
    else {
      iVar16 = net_ad_wrap_service(param_1);
      local_9c = 0;
      iVar16 = *(int *)(iVar6 * 0xd18 + iVar16 + 0x111c);
    }
    RTMP_GET_TEMPERATURE(param_1,iVar6,&local_74);
    piVar21 = local_80;
    sVar7 = strlen((char *)local_80);
    sprintf((char *)((int)piVar21 + sVar7),"CurrentTemperature              = %d\n",local_74);
    piVar21 = local_80;
    sVar7 = strlen((char *)local_80);
    sprintf((char *)((int)piVar21 + sVar7),"TxPower                         = %d\n",
            (uint)*(byte *)((int)param_1 + iVar6 + 0x794cd8));
    piVar21 = local_80;
    sVar7 = strlen((char *)local_80);
    sprintf((char *)((int)piVar21 + sVar7),"MapEnable                       = %d\n",
            (uint)*(byte *)((int)local_b0 + 0xcbfa));
    piVar21 = local_80;
    sVar7 = strlen((char *)local_80);
    sprintf((char *)((int)piVar21 + sVar7),"Tx success                      = %ld\n",iVar16);
    iVar8 = hc_get_hif_type(local_ac[0x1e8]);
    if (iVar8 == 2) {
      local_94 = iVar6 * 0x20;
      if (iVar16 == 0) {
        local_90 = param_1[iVar6 * 0x42 + 0x28e704];
        local_8c = 0;
        pcVar19 = (char *)0x0;
      }
      else {
        local_90 = param_1[iVar6 * 0x42 + 0x28e704];
        uVar10 = __aeabi_uidiv(local_90 * 1000,iVar16 + local_90);
        local_8c = uVar10 / 10;
        pcVar19 = (char *)(uVar10 % 10);
      }
      piVar21 = local_80;
      sVar7 = strlen((char *)local_80);
      local_d0 = pcVar19;
      sprintf((char *)((int)piVar21 + sVar7),
              "Tx fail count                   = %ld, PER=%ld.%1ld%%\n",local_90,local_8c);
      piVar21 = local_80;
      sVar7 = strlen((char *)local_80);
      iVar16 = local_94 + iVar6;
      sprintf((char *)((int)piVar21 + sVar7),"Current BW Tx count             = %ld\n",
              param_1[iVar16 * 2 + 0x28e72a]);
      piVar21 = local_80;
      sVar7 = strlen((char *)local_80);
      sprintf((char *)((int)piVar21 + sVar7),"Other BW Tx count               = %ld\n",
              param_1[iVar16 * 2 + 0x28e72c]);
    }
    piVar21 = local_80;
    sVar7 = strlen((char *)local_80);
    sprintf((char *)((int)piVar21 + sVar7),"Rx success                      = %lu\n",local_9c);
    if (((param_1[0x28eb05] & 1U) == 0) &&
       ((local_b0[0x1eed] != 1 || ((*(uint *)(local_b0[0x1eee] + 0x4e0) & 1) == 0)))) {
      if ((param_1[0xa5b19] & 0xffffU) == 0x7915) {
        local_94 = iVar6 * 0x20;
        if (local_9c == 0) {
          local_a0 = (int *)param_1[iVar6 * 0x42 + 0x28e72e];
          pcVar19 = (char *)0x0;
          uVar10 = 0;
        }
        else {
          local_a0 = (int *)param_1[iVar6 * 0x42 + 0x28e72e];
          uVar13 = __aeabi_uidiv((int)local_a0 * 1000,local_9c + (int)local_a0);
          uVar10 = uVar13 / 10;
          pcVar19 = (char *)(uVar13 % 10);
        }
        piVar21 = local_80;
        sVar7 = strlen((char *)local_80);
        local_d0 = pcVar19;
        sprintf((char *)((int)piVar21 + sVar7),
                "Rx with CRC                     = %ld, PER=%ld.%1ld%%\n",local_a0,uVar10);
        piVar21 = local_80;
        sVar7 = strlen((char *)local_80);
        sprintf((char *)((int)piVar21 + sVar7),"Rx drop due to out of resource  = %ld\n",
                param_1[(local_94 + iVar6) * 2 + 0x28e730]);
      }
      else {
        if (param_1[iVar6 * 0x42 + 0x28e712] == 0) {
          local_9c = param_1[iVar6 * 0x42 + 0x28e716];
          pcVar19 = (char *)0x0;
          uVar10 = 0;
        }
        else {
          local_9c = param_1[iVar6 * 0x42 + 0x28e716];
          uVar13 = __aeabi_uidiv(local_9c * 1000,local_9c + param_1[iVar6 * 0x42 + 0x28e712]);
          uVar10 = uVar13 / 10;
          pcVar19 = (char *)(uVar13 % 10);
        }
        piVar21 = local_80;
        sVar7 = strlen((char *)local_80);
        local_d0 = pcVar19;
        sprintf((char *)((int)piVar21 + sVar7),
                "Rx with CRC                     = %ld, PER=%ld.%1ld%%\n",local_9c,uVar10);
        piVar21 = local_80;
        sVar7 = strlen((char *)local_80);
        sprintf((char *)((int)piVar21 + sVar7),"Rx drop due to out of resource  = %ld\n",
                local_a0[0x26fd]);
      }
    }
    PhyStatGetRssi(param_1,iVar6,local_70,&local_81);
    piVar21 = local_80;
    sVar7 = strlen((char *)local_80);
    puVar17 = &_LC709;
    puVar5 = (undefined4 *)((int)piVar21 + sVar7);
    do {
      puVar22 = puVar5;
      uVar9 = puVar17[1];
      uVar11 = puVar17[2];
      uVar12 = puVar17[3];
      bVar25 = puVar17 != &DAT_002b0bac;
      *puVar22 = *puVar17;
      puVar22[1] = uVar9;
      puVar22[2] = uVar11;
      puVar22[3] = uVar12;
      puVar17 = puVar17 + 4;
      puVar5 = puVar22 + 4;
    } while (bVar25);
    *(undefined1 *)((int)puVar22 + 0x12) = 0;
    *(undefined2 *)(puVar22 + 4) = 0x203d;
    if (local_81 != 0) {
      uVar10 = 0;
      do {
        piVar21 = local_80;
        sVar7 = strlen((char *)local_80);
        pcVar19 = local_70 + uVar10;
        uVar10 = uVar10 + 1 & 0xff;
        sprintf((char *)((int)piVar21 + sVar7),"%d ",(int)*pcVar19);
      } while (uVar10 < local_81);
    }
    piVar21 = local_80;
    sVar7 = strlen((char *)local_80);
    *(undefined2 *)((int)piVar21 + sVar7) = 10;
    if ((short)param_1[0xa1648] != 0) {
      piVar21 = param_1 + 0x2874a;
      local_a0 = local_80;
      sVar7 = strlen((char *)local_80);
      sprintf((char *)((int)local_a0 + sVar7),"Average Tx Rate (kbps)          = %d\n",
              param_1[*(int *)(iVar20 + 0x3c) * 0x160d + 0xaed86]);
      local_a0 = local_80;
      sVar7 = strlen((char *)local_80);
      sprintf((char *)((int)local_a0 + sVar7),"Average Rx Rate (kbps)          = %d\n",
              param_1[*(int *)(iVar20 + 0x3c) * 0x160d + 0xaed87]);
      for (iVar20 = 0; iVar16 = HcGetMaxStaNum(param_1), iVar20 < iVar16; iVar20 = iVar20 + 1) {
        if ((*piVar21 != 0) && (iVar16 = HcGetBandByWdev(), iVar16 == iVar6)) {
          iVar16 = piVar21[-2];
          uVar10 = (uint)(iVar16 << 0x1d) >> 0x1f;
          if (iVar16 == 0x20001) {
            if (piVar21[0x3d] == 2) goto LAB_0003af44;
          }
          else {
            if (iVar16 == 2) {
              uVar10 = 1;
            }
            if (uVar10 != 0) {
LAB_0003af44:
              uVar13 = param_1[iVar20 * 0x530 + 0x28796];
              uVar10 = param_1[iVar20 * 0x530 + 0x28795];
              if (*(char *)(local_a8 + 0x150) == '\x01') {
                local_d0 = local_70 + 4;
                MtCmdGetTxStatistic(param_1,4,0,(short)param_1[iVar20 * 0x530 + 0x28780]);
                uVar14 = local_3b & 7;
                uVar10 = (uint)(local_38 != '\0');
                uVar15 = uVar14;
                if (3 < uVar14) {
                  uVar15 = (uint)local_34;
                }
                if (3 < uVar14) {
                  uVar15 = uVar15 - 1;
                }
                uVar3 = uVar10 << 9;
                if (uVar14 < 4) {
                  uVar15 = (uint)local_35;
                }
                else {
                  uVar15 = uVar15 & 3;
                  uVar10 = (uint)local_35;
                }
                if (3 < uVar14) {
                  uVar15 = uVar10 + uVar15 * 0x10;
                }
                uVar10 = uVar14 << 0xd | (local_37 & 3) << 7 | (uint)(local_36 != '\0') << 6 | uVar3
                         | (local_39 & 1) << 10 | uVar15 & 0x3f;
              }
              local_a8 = uVar10;
              iVar16 = hc_get_hif_type(local_ac[0x1e8]);
              piVar21 = local_80;
              if (iVar16 == 2) {
                StatRateToString(param_1,local_80,0,local_a8);
                if ((param_1[0xa5b19] & 0xffffU) == 0x7915) {
                  ShowLastRxPhyRate(param_1,iVar6,(short)param_1[iVar20 * 0x530 + 0x28780],&local_7c
                                   );
                  StatMt7915RxRateToString(param_1,local_80,local_7c);
                }
                else {
                  StatRateToString(param_1,local_80,1,uVar13);
                }
              }
              else {
                sVar7 = strlen((char *)local_80);
                if ((local_a8 & 0x80) == 0) {
                  uVar9 = 0x14;
                }
                else {
                  uVar9 = 0x28;
                }
                local_cc = (&PTR_DAT_00290134)[(local_a8 << 0x10) >> 0x1e];
                if ((local_a8 & 0x100) == 0) {
                  local_d0 = (char *)0x4c;
                }
                else {
                  local_d0 = (char *)0x53;
                }
                local_c8 = ", STBC";
                if ((local_a8 & 0x600) == 0) {
                  local_c8 = " ";
                }
                sprintf((char *)((int)piVar21 + sVar7),
                        "Last TX Rate                    = MCS%d, %2dM, %cGI, %s%s\n",
                        local_a8 & 0x7f,uVar9);
                piVar21 = local_80;
                sVar7 = strlen((char *)local_80);
                if ((uVar13 & 0x80) == 0) {
                  uVar9 = 0x14;
                }
                else {
                  uVar9 = 0x28;
                }
                local_cc = (&PTR_DAT_00290134)[(uVar13 << 0x10) >> 0x1e];
                if ((uVar13 & 0x100) == 0) {
                  local_d0 = (char *)0x4c;
                }
                else {
                  local_d0 = (char *)0x53;
                }
                local_c8 = ", STBC";
                if ((uVar13 & 0x600) == 0) {
                  local_c8 = " ";
                }
                sprintf((char *)((int)piVar21 + sVar7),
                        "Last RX Rate                    = MCS%d, %2dM, %cGI, %s%s\n",uVar13 & 0x7f,
                        uVar9);
              }
              break;
            }
          }
        }
        piVar21 = piVar21 + 0x530;
      }
    }
    iVar6 = hc_get_hif_type(local_ac[0x1e8]);
    piVar21 = local_80;
    if ((iVar6 == 2) && (*(char *)((int)param_1 + 0x795b0d) != '\0')) {
      sVar7 = strlen((char *)local_80);
      piVar18 = local_80;
      pcVar19 = (char *)((int)piVar21 + sVar7);
      pcVar24 = "/* Condition Number should enable mode4 of 0x6020_426c */\n";
      do {
        pcVar23 = pcVar19;
        uVar9 = *(undefined4 *)(pcVar24 + 4);
        uVar11 = *(undefined4 *)(pcVar24 + 8);
        uVar12 = *(undefined4 *)(pcVar24 + 0xc);
        bVar25 = pcVar24 != "e mode4 of 0x6020_426c */\n";
        *(undefined4 *)pcVar23 = *(undefined4 *)pcVar24;
        *(undefined4 *)(pcVar23 + 4) = uVar9;
        *(undefined4 *)(pcVar23 + 8) = uVar11;
        *(undefined4 *)(pcVar23 + 0xc) = uVar12;
        pcVar19 = pcVar23 + 0x10;
        pcVar24 = pcVar24 + 0x10;
      } while (bVar25);
      builtin_strncpy(pcVar23 + 0x10,"0_426c */\n",0xb);
      sVar7 = strlen((char *)local_80);
      local_c0 = (int *)(uint)*(byte *)(local_b0 + 0x227f);
      local_bc = (int *)(uint)*(byte *)(local_b0 + 0x2280);
      local_d0 = (char *)(uint)*(byte *)(local_b0 + 0x227b);
      local_cc = (undefined *)(uint)*(byte *)(local_b0 + 0x227c);
      local_c8 = (char *)(uint)*(byte *)(local_b0 + 0x227d);
      uStack_c4 = (uint)*(byte *)(local_b0 + 0x227e);
      local_b8 = (uint)*(byte *)(local_b0 + 0x2281);
      local_b4 = (uint)*(byte *)(local_b0 + 0x2282);
      pbVar1 = (byte *)(local_b0 + 0x2279);
      pbVar2 = (byte *)(local_b0 + 0x227a);
      local_b0 = local_c0;
      local_ac = local_bc;
      sprintf((char *)((int)piVar18 + sVar7),
              "--10 packets Condition Number   = [%d|%d|%d|%d|%d|%d|%d|%d|%d|%d]\n",(uint)*pbVar1,
              (uint)*pbVar2);
    }
    if (*(char *)((int)param_1 + 0x296ce5) == '\x01') {
      eFuseGetFreeBlockCount(param_1,&local_78);
      piVar21 = local_80;
      sVar7 = strlen((char *)local_80);
      sprintf((char *)((int)piVar21 + sVar7),"efuseFreeNumber                 = %d\n",local_78);
    }
    piVar21 = local_80;
    bVar4 = *(byte *)(*param_1 + 0x3c);
    sVar7 = strlen((char *)local_80);
    sprintf((char *)((int)piVar21 + sVar7),"proxy arp enable              = %d\n",
            (uint)*(byte *)(param_1 + (uint)bVar4 * 0x160d + 0xaefb9));
    piVar21 = local_80;
    sVar7 = strlen((char *)local_80);
    sprintf((char *)((int)piVar21 + sVar7),"WNMNotify enable              = %d\n",
            (uint)*(byte *)((int)param_1 + (uint)bVar4 * 0x5834 + 0x2bbee5));
    piVar21 = local_80;
    sVar7 = strlen((char *)local_80);
    sprintf((char *)((int)piVar21 + sVar7),"WNM BSS Transition Management enable = %d\n",
            (uint)*(byte *)((int)param_1 + (uint)bVar4 * 0x5834 + 0x2bbee6));
    piVar21 = local_80;
    sVar7 = strlen((char *)local_80);
    sprintf((char *)((int)piVar21 + sVar7),"GAS come back delay                       = %d\n",
            param_1[(uint)bVar4 * 0x160d + 0xaefa6]);
    piVar21 = local_80;
    sVar7 = strlen((char *)local_80);
    sprintf((char *)((int)piVar21 + sVar7),"GAS MMPDU size                            = %d\n",
            param_1[(uint)bVar4 * 0x160d + 0xaefa7]);
    piVar21 = local_80;
    sVar7 = strlen((char *)local_80);
    sprintf((char *)((int)piVar21 + sVar7),"GAS enable\t\t\t\t= %d\n",
            (uint)*(byte *)(param_1 + (uint)bVar4 * 0x160d + 0xaefa8));
    piVar21 = local_80;
    sVar7 = strlen((char *)local_80);
    piVar18 = local_80;
    *(undefined2 *)((int)piVar21 + sVar7) = 10;
    sVar7 = strlen((char *)local_80);
    uVar10 = *(uint *)(local_a4 + 0x10);
    *(short *)(local_a4 + 0x14) = (short)sVar7;
    uVar13 = *(uint *)(((uint)&local_d0 & 0xffffe000) + 8);
    if (!CARRY4(uVar10,sVar7 & 0xffff) && uVar10 + (sVar7 & 0xffff) <= uVar13) {
      uVar13 = 0;
    }
    if (uVar13 == 0) {
      __copy_to_user(uVar10,piVar18);
      piVar18 = local_80;
    }
    os_free_mem(piVar18);
    if (2 < *local_98) {
      printk("<==RTMPIoctlStatistics\n");
    }
  }
  return;
}

