// module: mt7915.ko
// function: RtmpIoctl_rt_private_get_statistics @ 0x656e0
// size: 4172 bytes
//

undefined4 RtmpIoctl_rt_private_get_statistics(int *param_1,char *param_2,uint param_3)

{
  uint uVar1;
  ushort uVar2;
  ushort uVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  size_t sVar7;
  int iVar8;
  undefined4 uVar9;
  char *pcVar10;
  int iVar11;
  undefined4 uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  int *piVar16;
  char *pcVar17;
  int *piVar18;
  uint uVar19;
  undefined4 *puVar20;
  byte *pbVar21;
  int *piVar22;
  int *piVar23;
  char *pcVar24;
  undefined *puVar25;
  bool bVar26;
  uint local_c0;
  undefined4 local_a4;
  undefined4 local_9d;
  undefined2 local_99;
  undefined1 auStack_8d [33];
  int local_6c [10];
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
  
  iVar8 = *(int *)(*param_1 + 0x3c);
  iVar4 = get_wdev_by_ioctl_idx_and_iftype(param_1,iVar8,*(undefined4 *)(*param_1 + 0x38));
  iVar5 = hc_get_chip_cap(param_1[0x29e5e8]);
  uVar6 = 0;
  if (iVar4 != 0) {
    uVar6 = HcGetBandByWdev(iVar4);
  }
  param_2[0] = '\n';
  param_2[1] = '\n';
  param_2[2] = '\0';
  if (*(char *)(iVar5 + 0x150) == '\x01') {
    MtCmdGetTxStatistic(param_1,3,uVar6,0,local_6c);
    uVar14 = local_44 & 7;
    uVar19 = (uint)local_42;
    uVar15 = uVar19 & 1;
    if (3 < uVar14) {
      uVar19 = (uint)local_3e;
    }
    uVar13 = param_1[0x28e704] + local_6c[3];
    param_1[0x28e704] = uVar13;
    if (3 < uVar14) {
      uVar13 = (uint)local_3d;
    }
    if (uVar14 < 4) {
      uVar13 = (uint)local_3e;
    }
    else {
      uVar13 = uVar13 - 1;
    }
    param_1[0x28e700] = (local_6c[2] + param_1[0x28e700]) - local_6c[3];
    if (3 < uVar14) {
      uVar13 = uVar19 + (uVar13 & 3) * 0x10;
    }
    param_1[0x28e7e7] =
         uVar14 << 0xd | (local_40 & 3) << 7 | (uint)(local_3f != '\0') << 6 |
         (uint)(local_41 != '\0') << 9 | uVar15 << 10 | uVar13 & 0x3f;
  }
  if (((param_1[0x28eb05] & 1U) == 0) &&
     ((param_1[0x29deed] != 1 || ((*(uint *)(param_1[0x29deee] + 0x4e0) & 1) == 0)))) {
    local_c0 = param_1[0x28e700];
  }
  else {
    local_c0 = param_1[0x28eb60];
  }
  RTMP_GET_TEMPERATURE(param_1,uVar6,&local_a4);
  sVar7 = strlen(param_2);
  sprintf(param_2 + sVar7,"CurrentTemperature              = %d\n",local_a4);
  sVar7 = strlen(param_2);
  sprintf(param_2 + sVar7,"Tx success                      = %lu\n",local_c0);
  iVar4 = hc_get_hif_type(param_1[0x29e5e8]);
  if (iVar4 == 2) {
    if (local_c0 == 0) {
      iVar4 = param_1[0x28e704];
      uVar15 = 0;
    }
    else {
      iVar4 = param_1[0x28e704];
      local_c0 = __aeabi_uidiv(iVar4 * 1000,local_c0 + iVar4);
      uVar15 = local_c0 / 10;
      local_c0 = local_c0 % 10;
    }
    sVar7 = strlen(param_2);
    sprintf(param_2 + sVar7,"Tx fail count                   = %ld, PER=%ld.%1ld%%\n",iVar4,uVar15,
            local_c0);
  }
  else {
    if (local_c0 == 0) {
      sVar7 = strlen(param_2);
      sprintf(param_2 + sVar7,"Tx retry count                  = %lu, PER=%ld.%1ld%%\n",
              param_1[0x28e706],0,0);
      iVar4 = param_1[0x28e704];
      uVar15 = 0;
    }
    else {
      iVar11 = param_1[0x28e706];
      iVar4 = iVar11 + param_1[0x28e704];
      uVar15 = __aeabi_uidiv(iVar4 * 1000,local_c0 + iVar4);
      sVar7 = strlen(param_2);
      sprintf(param_2 + sVar7,"Tx retry count                  = %lu, PER=%ld.%1ld%%\n",iVar11,
              uVar15 / 10,uVar15 % 10);
      iVar4 = param_1[0x28e704];
      local_c0 = __aeabi_uidiv(iVar4 * 10000,local_c0 + iVar4);
      uVar15 = local_c0 / 100;
      local_c0 = local_c0 % 100;
    }
    sVar7 = strlen(param_2);
    sprintf(param_2 + sVar7,"Tx fail to Rcv ACK after retry  = %lu, PLR=%ld.%02ld%%\n",iVar4,uVar15,
            local_c0);
  }
  sVar7 = strlen(param_2);
  sprintf(param_2 + sVar7,"Rx success                      = %lu\n",param_1[0x28e712],
          param_1 + 0x28e714,local_c0);
  if (param_1[0x28e712] == 0) {
    iVar4 = param_1[0x28e716];
    uVar19 = 0;
    uVar15 = 0;
  }
  else {
    iVar4 = param_1[0x28e716];
    uVar19 = __aeabi_uidiv(iVar4 * 1000,iVar4 + param_1[0x28e712]);
    uVar15 = uVar19 / 10;
    uVar19 = uVar19 % 10;
  }
  sVar7 = strlen(param_2);
  sprintf(param_2 + sVar7,"Rx with CRC                     = %ld, PER=%ld.%1ld%%\n",iVar4,uVar15,
          uVar19);
  sVar7 = strlen(param_2);
  sprintf(param_2 + sVar7,"Rx drop due to out of resource  = %lu\n",param_1[0x28e6fd]);
  sVar7 = strlen(param_2);
  sprintf(param_2 + sVar7,"Rx duplicate frame              = %lu\n",param_1[0x28e710]);
  sVar7 = strlen(param_2);
  sprintf(param_2 + sVar7,"False CCA                       = %lu\n",param_1[0x28e79f]);
  if (((param_1[0x28eb05] & 1U) == 0) &&
     ((param_1[0x29deed] != 1 || ((*(uint *)(param_1[0x29deee] + 0x4e0) & 1) == 0)))) {
    local_c0 = iVar8 * 0x20;
    sVar7 = strlen(param_2);
    iVar4 = (int)*(char *)((int)param_1 + 0x296e62);
    piVar16 = (int *)(*(char *)((int)param_1 + iVar8 * 0x2137b0 + 0x580d22) - iVar4);
    puVar25 = (undefined *)(*(char *)((int)param_1 + iVar8 * 0x2137b0 + 0x580d23) - iVar4);
    sprintf(param_2 + sVar7,"RSSI                            = %ld %ld %ld %ld\n",
            (char)param_1[iVar8 * 0x84dec + 0x160348] - iVar4,
            *(char *)((int)param_1 + iVar8 * 0x2137b0 + 0x580d21) - iVar4,piVar16,puVar25);
    if ((short)param_1[0xa1648] != 0) {
      piVar18 = param_1 + 0x28787;
      for (iVar4 = 0; iVar11 = HcGetMaxStaNum(param_1), iVar4 < iVar11; iVar4 = iVar4 + 1) {
        if ((piVar18[-0x3f] == 0x20001) && (*piVar18 == 2)) {
          uVar19 = param_1[iVar4 * 0x530 + 0x28796];
          uVar15 = param_1[iVar4 * 0x530 + 0x28795];
          if ((*(char *)(iVar5 + 0x150) == '\x01') &&
             (*(char *)((int)param_1 + iVar4 * 0x14c0 + 0xa289e) == '\x01')) {
            piVar16 = local_6c;
            MtCmdGetTxStatistic(param_1,4,0,(short)param_1[iVar4 * 0x530 + 0x28780],piVar16);
            uVar13 = local_3b & 7;
            uVar15 = (uint)(local_38 != '\0');
            uVar14 = uVar13;
            if (3 < uVar13) {
              uVar14 = (uint)local_34;
            }
            if (3 < uVar13) {
              uVar14 = uVar14 - 1;
            }
            uVar1 = uVar15 << 9;
            if (uVar13 < 4) {
              uVar14 = (uint)local_35;
            }
            else {
              uVar14 = uVar14 & 3;
              uVar15 = (uint)local_35;
            }
            if (3 < uVar13) {
              uVar14 = uVar15 + uVar14 * 0x10;
            }
            uVar15 = uVar13 << 0xd | (local_37 & 3) << 7 | (uint)(local_36 != '\0') << 6 | uVar1 |
                     (local_39 & 1) << 10 | uVar14 & 0x3f;
          }
          iVar4 = hc_get_hif_type(param_1[0x29e5e8]);
          if (iVar4 == 2) {
            StatRateToString(param_1,param_2,0,uVar15);
            StatRateToString(param_1,param_2,1,uVar19);
          }
          else {
            sVar7 = strlen(param_2);
            if ((uVar15 & 0x80) == 0) {
              uVar6 = 0x14;
            }
            else {
              uVar6 = 0x28;
            }
            if ((uVar15 & 0x100) == 0) {
              uVar9 = 0x4c;
            }
            else {
              uVar9 = 0x53;
            }
            pcVar10 = ", STBC";
            if ((uVar15 & 0x600) == 0) {
              pcVar10 = " ";
            }
            sprintf(param_2 + sVar7,"Last TX Rate                    = MCS%d, %2dM, %cGI, %s%s\n",
                    uVar15 & 0x7f,uVar6,uVar9,(&PTR_DAT_00291150)[(uVar15 << 0x10) >> 0x1e],pcVar10)
            ;
            sVar7 = strlen(param_2);
            if ((uVar19 & 0x80) == 0) {
              uVar6 = 0x14;
            }
            else {
              uVar6 = 0x28;
            }
            puVar25 = (&PTR_DAT_00291150)[(uVar19 << 0x10) >> 0x1e];
            if ((uVar19 & 0x100) == 0) {
              piVar16 = (int *)0x4c;
            }
            else {
              piVar16 = (int *)0x53;
            }
            pcVar10 = ", STBC";
            if ((uVar19 & 0x600) == 0) {
              pcVar10 = " ";
            }
            sprintf(param_2 + sVar7,"Last RX Rate                    = MCS %d, %2dM, %cGI, %s%s\n",
                    uVar19 & 0x7f,uVar6,piVar16,puVar25,pcVar10);
          }
          break;
        }
        piVar18 = piVar18 + 0x530;
      }
    }
    iVar4 = hc_get_hif_type(param_1[0x29e5e8]);
    if (iVar4 == 2) {
      piVar18 = param_1 + 0x28e71e;
      iVar4 = 0;
      do {
        sVar7 = strlen(param_2);
        sprintf(param_2 + sVar7,"BandIdx: %d\n",iVar4);
        sVar7 = strlen(param_2);
        sprintf(param_2 + sVar7,"TX AGG Range 1 (1)              = %ld\n",*piVar18);
        sVar7 = strlen(param_2);
        sprintf(param_2 + sVar7,"TX AGG Range 2 (2~5)            = %ld\n",piVar18[2]);
        sVar7 = strlen(param_2);
        sprintf(param_2 + sVar7,"TX AGG Range 3 (6~15)           = %ld\n",piVar18[4]);
        sVar7 = strlen(param_2);
        sprintf(param_2 + sVar7,"TX AGG Range 4 (>15)            = %ld\n",piVar18[6]);
        sVar7 = strlen(param_2);
        iVar5 = piVar18[10];
        sprintf(param_2 + sVar7,"AMPDU Tx success                = %ld\n",iVar5);
        iVar11 = piVar18[8];
        if (iVar5 == 0) {
          uVar15 = 0;
          piVar16 = (int *)0x0;
        }
        else {
          uVar19 = __aeabi_uidiv(iVar11 * 1000,iVar11 + iVar5);
          uVar15 = uVar19 / 10;
          piVar16 = (int *)(uVar19 % 10);
        }
        piVar18 = piVar18 + 0x42;
        sVar7 = strlen(param_2);
        sprintf(param_2 + sVar7,"AMPDU Tx fail count             = %ld, PER=%ld.%1ld%%\n",iVar11,
                uVar15,piVar16);
        bVar26 = iVar4 != 1;
        iVar4 = 1;
      } while (bVar26);
      if (*(char *)((int)param_1 + 0x795b0d) != '\0') {
        sVar7 = strlen(param_2);
        pcVar10 = "/* Condition Number should enable mode4 of 0x6020_426c */\n";
        pcVar24 = param_2 + sVar7;
        do {
          pcVar17 = pcVar24;
          uVar6 = *(undefined4 *)(pcVar10 + 4);
          uVar9 = *(undefined4 *)(pcVar10 + 8);
          uVar12 = *(undefined4 *)(pcVar10 + 0xc);
          bVar26 = pcVar10 != "e mode4 of 0x6020_426c */\n";
          *(undefined4 *)pcVar17 = *(undefined4 *)pcVar10;
          *(undefined4 *)(pcVar17 + 4) = uVar6;
          *(undefined4 *)(pcVar17 + 8) = uVar9;
          *(undefined4 *)(pcVar17 + 0xc) = uVar12;
          pcVar10 = pcVar10 + 0x10;
          pcVar24 = pcVar17 + 0x10;
        } while (bVar26);
        builtin_strncpy(pcVar17 + 0x10,"0_426c */\n",0xb);
        puVar25 = (undefined *)(uint)*(byte *)(param_1 + 0x29e27c);
        piVar16 = (int *)(uint)*(byte *)(param_1 + 0x29e27b);
        sprintf(param_2 + sVar7 + 0x3a,
                "--10 packets Condition Number   = [%d|%d|%d|%d|%d|%d|%d|%d|%d|%d]\n",
                (uint)*(byte *)(param_1 + 0x29e279),(uint)*(byte *)(param_1 + 0x29e27a),piVar16,
                puVar25,(uint)*(byte *)(param_1 + 0x29e27d),(uint)*(byte *)(param_1 + 0x29e27e),
                (uint)*(byte *)(param_1 + 0x29e27f),(uint)*(byte *)(param_1 + 0x29e280),
                (uint)*(byte *)(param_1 + 0x29e281),(uint)*(byte *)(param_1 + 0x29e282));
      }
    }
    sVar7 = strlen(param_2);
    sprintf(param_2 + sVar7,"SNR-A                          = %ld\n",
            (int)(char)param_1[iVar8 * 0x84dec + 0x16034d],param_1 + iVar8 * 0x84dec + 0x16034c,
            piVar16,puVar25);
    sVar7 = strlen(param_2);
    sprintf(param_2 + sVar7,"SNR-B (if available)           = %ld\n\n",
            (int)*(char *)((int)param_1 + iVar8 * 0x2137b0 + 0x580d35));
  }
  else {
    local_c0 = iVar8 << 5;
  }
  iVar4 = local_c0 * 4 + iVar8 * 5;
  if ((char)param_1[iVar4 * 0xffc + 0xdbb97] == '\b') {
    sVar7 = strlen(param_2);
    sprintf(param_2 + sVar7,"RT2860 Linux STA PinCode\t%08u\n",param_1[iVar4 * 0xffc + 0xdbb96]);
  }
  else {
    sVar7 = strlen(param_2);
    sprintf(param_2 + sVar7,"RT2860 Linux STA PinCode\t%04u\n",param_1[iVar4 * 0xffc + 0xdbb96]);
  }
  memset(&local_9d,0,0x10);
  iVar4 = local_c0 * 4 + iVar8 * 5;
  iVar5 = param_1[iVar4 * 0xffc + 0xdbb93];
  uVar15 = param_1[iVar4 * 0xffc + 0xdbb92];
  if (param_1[iVar4 * 0xffc + 0xdbb90] == 1) {
    pcVar10 = "PIN -";
  }
  else {
    pcVar10 = "PBC -";
  }
  local_9d = *(undefined4 *)pcVar10;
  local_99 = *(undefined2 *)(pcVar10 + 4);
  sVar7 = strlen(param_2);
  pcVar10 = "Disabled";
  if ((char)param_1[(local_c0 * 4 + iVar8 * 5) * 0xffc + 0xdc5d7] != '\0') {
    pcVar10 = "Enabled";
  }
  sprintf(param_2 + sVar7,"WPS Information(Driver Auto-Connect is %s - %d):\n",pcVar10);
  if (iVar5 == 0) {
    if (uVar15 == 0x22) {
      sVar7 = strlen(param_2);
      pcVar10 = param_2 + sVar7;
      pcVar24 = "WPS messages exchange successfully !!!\n";
      do {
        pcVar17 = pcVar10;
        uVar6 = *(undefined4 *)(pcVar24 + 4);
        uVar9 = *(undefined4 *)(pcVar24 + 8);
        uVar12 = *(undefined4 *)(pcVar24 + 0xc);
        bVar26 = pcVar24 != "hange successfully !!!\n";
        *(undefined4 *)pcVar17 = *(undefined4 *)pcVar24;
        *(undefined4 *)(pcVar17 + 4) = uVar6;
        *(undefined4 *)(pcVar17 + 8) = uVar9;
        *(undefined4 *)(pcVar17 + 0xc) = uVar12;
        pcVar10 = pcVar17 + 0x10;
        pcVar24 = pcVar24 + 0x10;
      } while (bVar26);
      builtin_strncpy(pcVar17 + 0x10,"ly !!!\n",8);
      goto LAB_00065e58;
    }
    if (uVar15 == 0) {
      sVar7 = strlen(param_2);
      builtin_strncpy(param_2 + sVar7,"WPS not used.\n",0xf);
      goto LAB_00065e58;
    }
    if ((uVar15 & 0xff00) == 0) goto LAB_00065e58;
  }
  else if ((uVar15 & 0xff00) == 0) {
    sVar7 = strlen(param_2);
    sprintf(param_2 + sVar7,"%s WPS Proceed. Please wait...\n",&local_9d);
    goto LAB_00065e58;
  }
  if (uVar15 == 0x101) {
    sVar7 = strlen(param_2);
    sprintf(param_2 + sVar7,"%s Too many PBC AP. Stop WPS.\n",&local_9d);
  }
  else if (uVar15 == 0x102) {
    sVar7 = strlen(param_2);
    sprintf(param_2 + sVar7,"%s No available PBC AP. Please wait...\n",&local_9d);
  }
  else if ((uVar15 & 0x100) == 0) {
    sVar7 = strlen(param_2);
    builtin_strncpy(param_2 + sVar7,"WPS didn\'t complete !!!\n",0x19);
  }
  else {
    sVar7 = strlen(param_2);
    sprintf(param_2 + sVar7,"%s Proceed to get the Registrar profile. Please wait...\n",&local_9d);
  }
LAB_00065e58:
  sVar7 = strlen(param_2);
  (param_2 + sVar7)[0] = '\n';
  (param_2 + sVar7)[1] = '\0';
  iVar4 = local_c0 * 4 + iVar8 * 5;
  sprintf(param_2 + sVar7 + 1,"WPS Profile Count               = %d\n",
          param_1[iVar4 * 0xffc + 0xdc2b3]);
  if (param_1[iVar4 * 0xffc + 0xdc2b3] != 0) {
    uVar15 = 0;
    piVar16 = param_1 + iVar4 * 0xffc + 0xdc2bf;
    do {
      __memzero(auStack_8d,0x21);
      sVar7 = strlen(param_2);
      if (param_3 <= sVar7 + 0x74) break;
      sprintf(param_2 + sVar7,"Profile[%d]:\n",uVar15);
      memcpy(auStack_8d,piVar16 + -9,piVar16[-10]);
      sVar7 = strlen(param_2);
      sprintf(param_2 + sVar7,"SSID                            = %s\n",auStack_8d);
      sVar7 = strlen(param_2);
      sprintf(param_2 + sVar7,"MAC                             = %02x:%02x:%02x:%02x:%02x:%02x\n",
              (uint)*(byte *)((int)piVar16 + 0x42),(uint)*(byte *)((int)piVar16 + 0x43),
              (uint)*(byte *)(piVar16 + 0x11),(uint)*(byte *)((int)piVar16 + 0x45),
              (uint)*(byte *)((int)piVar16 + 0x46),(uint)*(byte *)((int)piVar16 + 0x47));
      sVar7 = strlen(param_2);
      uVar6 = WscGetAuthTypeStr((short)piVar16[-1]);
      sprintf(param_2 + sVar7,"AuthType                        = %s\n",uVar6);
      sVar7 = strlen(param_2);
      uVar6 = WscGetEncryTypeStr(*(undefined2 *)((int)piVar16 + -2));
      sprintf(param_2 + sVar7,"EncrypType                      = %s\n",uVar6);
      sVar7 = strlen(param_2);
      sprintf(param_2 + sVar7,"KeyIndex                        = %d\n",
              (uint)*(byte *)(piVar16 + 0x12));
      uVar2 = *(ushort *)(piVar16 + 0x10);
      if (uVar2 != 0) {
        uVar3 = *(ushort *)(piVar16 + -1);
        if ((uVar3 & 0xa2) == 0) {
          if (uVar3 == 1 || uVar3 == 4) {
            iVar4 = RTMPCheckStrPrintAble(piVar16,uVar2 & 0xff);
            if (iVar4 != 0) goto LAB_000661ac;
            sVar7 = strlen(param_2);
            puVar20 = &_LC374;
            pcVar10 = param_2 + sVar7;
            do {
              pcVar24 = pcVar10;
              uVar6 = puVar20[1];
              uVar9 = puVar20[2];
              uVar12 = puVar20[3];
              pcVar10 = pcVar24 + 0x10;
              bVar26 = puVar20 != &DAT_002bdc8c;
              *(undefined4 *)pcVar24 = *puVar20;
              *(undefined4 *)(pcVar24 + 4) = uVar6;
              *(undefined4 *)(pcVar24 + 8) = uVar9;
              *(undefined4 *)(pcVar24 + 0xc) = uVar12;
              puVar20 = puVar20 + 4;
            } while (bVar26);
            pcVar24[0x12] = '\0';
            pcVar10[0] = '=';
            pcVar10[1] = ' ';
            if ((short)piVar16[0x10] != 0) {
              pbVar21 = (byte *)((int)piVar16 + -1);
              iVar4 = 0;
              do {
                iVar4 = iVar4 + 1;
                sVar7 = strlen(param_2);
                pbVar21 = pbVar21 + 1;
                sprintf(param_2 + sVar7,"%02X",(uint)*pbVar21);
                if ((int)(uint)*(ushort *)(piVar16 + 0x10) <= iVar4) break;
              } while (iVar4 != 0x40);
            }
            sVar7 = strlen(param_2);
            (param_2 + sVar7)[0] = '\n';
            (param_2 + sVar7)[1] = '\0';
          }
        }
        else if (uVar2 < 0x40) {
LAB_000661ac:
          sVar7 = strlen(param_2);
          sprintf(param_2 + sVar7,"Key                             = %s\n",piVar16);
        }
        else {
          memset(local_6c,0,0x41);
          piVar18 = local_6c;
          piVar22 = piVar16;
          do {
            piVar23 = piVar22 + 4;
            iVar4 = piVar22[1];
            iVar5 = piVar22[2];
            iVar11 = piVar22[3];
            *piVar18 = *piVar22;
            piVar18[1] = iVar4;
            piVar18[2] = iVar5;
            piVar18[3] = iVar11;
            piVar18 = piVar18 + 4;
            piVar22 = piVar23;
          } while (piVar23 != piVar16 + 0x10);
          sVar7 = strlen(param_2);
          sprintf(param_2 + sVar7,"Key                             = %s\n",local_6c);
        }
      }
      uVar15 = uVar15 + 1;
      piVar16 = piVar16 + 0x1d;
    } while (uVar15 < (uint)param_1[(local_c0 * 4 + iVar8 * 5) * 0xffc + 0xdc2b3]);
  }
  sVar7 = strlen(param_2);
  (param_2 + sVar7)[0] = '\n';
  (param_2 + sVar7)[1] = '\0';
  iVar4 = hc_get_hif_type(param_1[0x29e5e8]);
  if (iVar4 != 2) {
    DisplayTxAgg(param_1);
  }
  return 0;
}

