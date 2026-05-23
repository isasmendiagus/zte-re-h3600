// module: mt7915.ko
// function: RTMPSetProfileParameters @ 0xf2030
// size: 59856 bytes
//

/* WARNING: Restarted to delay deadcode elimination for space: stack */

undefined4 RTMPSetProfileParameters(int *param_1,undefined4 param_2)

{
  ushort uVar1;
  undefined1 uVar2;
  char cVar3;
  char cVar4;
  byte bVar5;
  byte bVar6;
  short sVar7;
  undefined2 uVar8;
  ushort uVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  char *pcVar13;
  size_t sVar14;
  char *pcVar15;
  int iVar16;
  byte *pbVar17;
  char *pcVar18;
  uint uVar19;
  undefined4 uVar20;
  undefined4 uVar21;
  uint *puVar22;
  undefined4 *puVar23;
  uint uVar24;
  int *piVar25;
  uint uVar26;
  uint uVar27;
  byte *pbVar28;
  byte *pbVar29;
  ushort uVar30;
  uint uVar31;
  undefined *puVar32;
  undefined1 *puVar33;
  void *__dest;
  undefined1 *puVar34;
  char *pcVar35;
  int *piVar36;
  int iVar37;
  undefined2 *puVar38;
  bool bVar39;
  bool bVar40;
  uint local_b8;
  int *local_ac;
  int local_a8;
  undefined1 *local_90;
  undefined2 local_76;
  char *local_74;
  char *local_70;
  undefined1 auStack_6c [4];
  undefined2 local_68 [8];
  undefined4 local_58;
  undefined2 local_54;
  undefined4 local_48;
  char *local_44;
  char *local_40;
  int local_3c;
  int local_38;
  int local_34;
  undefined4 local_30;
  undefined4 local_2c;
  
  local_70 = (char *)0x0;
  iVar10 = hc_get_chip_cap(param_1[0x29e5e8]);
  iVar11 = hc_get_arch_ops(param_1[0x29e5e8]);
  local_76 = 0;
  os_alloc_mem(0,&local_74,0x800);
  if (local_74 == (char *)0x0) {
    return 1;
  }
  hc_init_ChCtrl(param_1);
  hc_init_ACSChCtrl(param_1);
  iVar12 = RTMPGetKeyParameter("WifiCert",local_74,0x19,param_2,1);
  if (iVar12 != 0) {
    uVar2 = os_str_tol(local_74,0,10);
    iVar12 = DebugLevel;
    *(undefined1 *)(param_1 + 0x1e5413) = uVar2;
    if (3 < iVar12) {
      printk("WifiCert=%d\n",uVar2);
    }
  }
  if (*(char *)((int)param_1 + 0x286285) == '\x01') {
    iVar12 = RTMPGetKeyParameter("BssidNum",local_74,0x19,param_2,1);
    if (iVar12 != 0) {
      bVar6 = os_str_tol(local_74,0,10);
      *(byte *)((int)param_1 + 0x2b7242) = bVar6;
      uVar26 = hc_get_chip_bcn_max_num(param_1[0x29e5e8]);
      if (uVar26 < bVar6) {
        uVar21 = hc_get_chip_bcn_max_num(param_1[0x29e5e8]);
        *(char *)((int)param_1 + 0x2b7242) = (char)uVar21;
        if (3 < DebugLevel) {
          uVar20 = hc_get_chip_bcn_max_num(param_1[0x29e5e8]);
          printk("BssidNum=%d(MAX_MBSSID_NUM is %d)\n",uVar21,uVar20);
        }
      }
      else if (3 < DebugLevel) {
        printk("BssidNum=%d\n",*(undefined1 *)((int)param_1 + 0x2b7242));
      }
    }
    if ((char)param_1[0xdb6d2] == '\0') {
      bVar6 = *(byte *)((int)param_1 + 0x2b7242);
      if (bVar6 != 0) {
        puVar34 = (undefined1 *)((int)param_1 + 0x3678c7);
        uVar26 = 0;
        do {
          puVar34 = puVar34 + 1;
          *puVar34 = (char)uVar26;
          uVar26 = uVar26 + 1;
        } while (uVar26 != bVar6);
        goto LAB_000fc560;
      }
      if (3 < DebugLevel) goto LAB_00100838;
    }
    else {
      iVar12 = 0;
      local_68[0] = 0;
      local_58 = local_58 & 0xffff0000;
      local_48 = (char *)((uint)local_48 & 0xffff0000);
      uVar2 = multi_profile_get_pf1_num(param_1);
      pbVar29 = (byte *)((int)param_1 + 0x2b7242);
      uVar26 = 0;
      local_58 = CONCAT31(local_58._1_3_,uVar2);
      uVar2 = multi_profile_get_pf2_num(param_1);
      local_58._0_2_ = CONCAT11(uVar2,(char)local_58);
      do {
        pbVar29 = pbVar29 + 1;
        bVar6 = *pbVar29;
        *(byte *)((int)local_68 + iVar12) = bVar6;
        uVar26 = uVar26 + bVar6 & 0xff;
        *(byte *)((int)&local_48 + iVar12) = *(byte *)((int)&local_58 + iVar12) - bVar6;
        if (((uint)bVar6 != (uint)*(byte *)((int)&local_58 + iVar12)) && (3 < DebugLevel)) {
          printk("B%d BssidNum change: %d->%d\n",iVar12);
        }
        bVar39 = iVar12 != 1;
        iVar12 = 1;
      } while (bVar39);
      uVar19 = (uint)*(byte *)((int)param_1 + 0x2b7242);
      if ((uVar26 < uVar19) && ((char)param_1[0x1e5413] != '\0')) {
        iVar12 = uVar26 - 1;
        if (0 < iVar12) {
          puVar33 = (undefined1 *)((int)param_1 + ((uint)local_48 & 0xff) + 0x3678c7 + uVar26);
          puVar34 = (undefined1 *)((int)param_1 + uVar26 + 0x3678c7);
          piVar25 = param_1 + uVar26 * 0x160d + 0xac685;
          do {
            iVar16 = *piVar25;
            piVar25 = piVar25 + -0x160d;
            if ((iVar16 != 0) && ((int)(uint)(byte)local_68[0] <= iVar12)) {
              uVar2 = *puVar34;
              *puVar34 = *puVar33;
              *puVar33 = uVar2;
            }
            iVar12 = iVar12 + -1;
            puVar34 = puVar34 + -1;
            puVar33 = puVar33 + -1;
          } while (iVar12 != 0);
        }
        if (uVar19 != 1) {
          piVar25 = param_1 + 0xd9e32;
          do {
            piVar25 = (int *)((int)piVar25 + 1);
            if (*(char *)piVar25 == '\0') {
              *(char *)piVar25 = (char)uVar26;
              uVar26 = uVar26 + 1 & 0xff;
            }
          } while (piVar25 != (int *)((int)param_1 + uVar19 + 0x3678c7));
        }
      }
LAB_000fc560:
      if (DebugLevel < 4) {
        if (*(char *)((int)param_1 + 0x2b7242) == '\0') goto LAB_000fc5bc;
LAB_000fc57c:
        iVar12 = 0;
        piVar25 = param_1 + 0xd9e32;
        do {
          iVar12 = iVar12 + 1;
          if (3 < DebugLevel) {
            printk(&_LC142,(char)*piVar25);
          }
          piVar25 = (int *)((int)piVar25 + 1);
        } while (iVar12 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242));
      }
      else {
LAB_00100838:
        printk("Pf2MbssIdxMap:\n");
        if (*(char *)((int)param_1 + 0x2b7242) != '\0') goto LAB_000fc57c;
      }
      if (3 < DebugLevel) {
        printk(&_LC12);
      }
    }
LAB_000fc5bc:
    if ((*(char *)((int)param_1 + 0x286285) == '\x01') &&
       (iVar12 = RTMPGetKeyParameter("TxCmdMode",local_74,0x19,param_2,1), iVar12 != 0)) {
      uVar2 = os_str_tol(local_74,0,10);
      hc_set_txcmd_mode(param_1[0x29e5e8],uVar2);
    }
  }
  local_ac = &local_48;
  if ((*(char *)((int)param_1 + 0x286285) == '\0') &&
     (iVar12 = RTMPGetKeyParameter("MStaNum",local_74,0x19,param_2,1), iVar12 != 0)) {
    bVar6 = os_str_tol(local_74,0,10);
    *(byte *)((int)param_1 + 0x794ab9) = bVar6;
    if (bVar6 < 3) {
      if (3 < DebugLevel) {
        printk("MStaNum=%d\n");
      }
    }
    else {
      *(undefined1 *)((int)param_1 + 0x794ab9) = 2;
      if (3 < DebugLevel) {
        printk("MStaNum=%d(MAX_MULTI_STA is %d)\n",2,2);
      }
    }
  }
  iVar12 = RTMPGetKeyParameter("MacAddress",local_74,0x40,param_2,1);
  if (iVar12 == 0) {
    cVar4 = *(char *)((int)param_1 + 0x286285);
  }
  else {
    local_48 = (char *)0x0;
    local_44 = (char *)0x0;
    local_40 = (char *)0x0;
    local_3c = 0;
    local_38 = 0;
    local_34 = 0;
    local_30 = 0;
    local_2c = 0;
    RT_CfgSetMacAddress(param_1,local_74,0,1);
    macIncrease(local_74,local_ac);
    RT_CfgSetMacAddress(param_1,local_ac,*(byte *)((int)param_1 + 0x2b7242) >> 1,1);
    cVar4 = *(char *)((int)param_1 + 0x286285);
  }
  if (cVar4 == '\x01') {
    if (1 < *(byte *)((int)param_1 + 0x2b7242)) {
      puVar34 = (undefined1 *)((int)param_1 + 0x794b67);
      uVar26 = 1;
      do {
        snprintf((char *)local_68,0x10,"MacAddress%d",uVar26);
        iVar12 = RTMPGetKeyParameter(local_68,local_74,0x19,param_2,1);
        if (((iVar12 != 0) &&
            (iVar12 = RT_CfgSetMacAddress(param_1,local_74,uVar26 & 0xff,1), iVar12 != 0)) &&
           (3 < DebugLevel)) {
          printk("ExtendMBssAddr[%d] = %02x:%02x:%02x:%02x:%02x:%02x\n",uVar26,*puVar34,puVar34[1],
                 puVar34[2],puVar34[3],puVar34[4],puVar34[5]);
        }
        uVar26 = uVar26 + 1;
        puVar34 = puVar34 + 6;
      } while ((int)uVar26 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242));
    }
    iVar12 = RTMPGetKeyParameter("ApcliMacAddress",local_74,0x19,param_2,1);
    if (((iVar12 != 0) && (iVar12 = RT_CfgSetMacAddress(param_1,local_74,0,0), iVar12 != 0)) &&
       (3 < DebugLevel)) {
      printk("ApcliMacAddress = %02x:%02x:%02x:%02x:%02x:%02x\n",(char)param_1[0x1e5307],
             *(undefined1 *)((int)param_1 + 0x794c1d),*(undefined1 *)((int)param_1 + 0x794c1e),
             *(undefined1 *)((int)param_1 + 0x794c1f),(char)param_1[0x1e5308],
             *(undefined1 *)((int)param_1 + 0x794c21));
    }
    iVar12 = RTMPGetKeyParameter("ApcliMacAddress1",local_74,0x19,param_2,1);
    if (((iVar12 != 0) && (iVar12 = RT_CfgSetMacAddress(param_1,local_74,1,0), iVar12 != 0)) &&
       (3 < DebugLevel)) {
      printk("ApcliMacAddress1 = %02x:%02x:%02x:%02x:%02x:%02x\n",
             *(undefined1 *)((int)param_1 + 0x794c22),*(undefined1 *)((int)param_1 + 0x794c23),
             (char)param_1[0x1e5309],*(undefined1 *)((int)param_1 + 0x794c25),
             *(undefined1 *)((int)param_1 + 0x794c26),*(undefined1 *)((int)param_1 + 0x794c27));
    }
  }
  iVar12 = RTMPGetKeyParameter("CountryRegion",local_74,0x19,param_2,1);
  if ((iVar12 != 0) && (RT_CfgSetCountryRegion(param_1,local_74,2), 3 < DebugLevel)) {
    printk("CountryRegion=%d\n",(char)param_1[0x1e5311]);
  }
  iVar12 = RTMPGetKeyParameter("CountryRegionABand",local_74,0x19,param_2,1);
  if ((iVar12 != 0) && (RT_CfgSetCountryRegion(param_1,local_74,1), 3 < DebugLevel)) {
    printk("CountryRegionABand=%d\n",*(undefined1 *)((int)param_1 + 0x794c45));
  }
  iVar12 = RTMPGetKeyParameter("AntennaGain",local_74,0x19,param_2,1);
  if ((iVar12 != 0) && (local_70 = (char *)rstrtok(local_74,&_LC6), local_70 != (char *)0x0)) {
    piVar25 = param_1 + 0x29f45c;
    uVar26 = 0;
    do {
      if (uVar26 < 2) {
        uVar2 = simple_strtol(local_70,0,10);
        *(undefined1 *)piVar25 = uVar2;
      }
      piVar25 = piVar25 + 9;
      local_70 = (char *)rstrtok(0,&_LC6);
      uVar26 = uVar26 + 1;
    } while (local_70 != (char *)0x0);
  }
  iVar12 = RTMPGetKeyParameter("CombinedGain",local_74,0x19,param_2,1);
  if ((iVar12 != 0) && (local_70 = (char *)rstrtok(local_74,&_LC6), local_70 != (char *)0x0)) {
    puVar34 = (undefined1 *)((int)param_1 + 0xa7d171);
    uVar26 = 0;
    do {
      if (uVar26 < 2) {
        uVar2 = simple_strtol(local_70,0,10);
        *puVar34 = uVar2;
      }
      puVar34 = puVar34 + 0x24;
      local_70 = (char *)rstrtok(0,&_LC6);
      uVar26 = uVar26 + 1;
    } while (local_70 != (char *)0x0);
  }
  iVar12 = RTMPGetKeyParameter("CountryPowerLimitRegion",local_74,0x19,param_2,1);
  if (iVar12 != 0) {
    if (3 < DebugLevel) {
      printk("Set_CountryPowerLimitRegion_Proc\n");
    }
    Set_CountryPowerLimitRegion_Proc(param_1,local_74);
  }
  iVar12 = RTMPGetKeyParameter("CountryPowerLimitRegionABand",local_74,0x19,param_2,1);
  if (iVar12 != 0) {
    Set_CountryPowerLimitRegionABand_Proc(param_1,local_74);
  }
  iVar12 = RTMPGetKeyParameter("PowerEnhance",local_74,0x19,param_2,1);
  if (iVar12 != 0) {
    local_70 = (char *)rstrtok(local_74,&_LC6);
    if (local_70 == (char *)0x0) {
      local_70 = (char *)0x0;
    }
    else {
      piVar25 = param_1 + 0x29f45b;
      uVar26 = 0;
      do {
        if (uVar26 < 2) {
          iVar12 = simple_strtol(local_70,0,10);
          *piVar25 = iVar12;
        }
        piVar25 = piVar25 + 9;
        local_70 = (char *)rstrtok(0,&_LC6);
        uVar26 = uVar26 + 1;
      } while (local_70 != (char *)0x0);
    }
    piVar25 = param_1 + 0x29f45b;
    iVar12 = 0;
    do {
      puVar32 = &_LC164;
      if ((*piVar25 == 0) && (*(byte *)(piVar25 + 1) - 1 < 10)) {
        puVar32 = &_LC163;
      }
      _SetSKUCtrl(param_1,iVar12,puVar32);
      piVar25 = piVar25 + 9;
      _SetBfBackoffCtrl(param_1,iVar12,&_LC164);
      bVar39 = iVar12 != 1;
      iVar12 = 1;
    } while (bVar39);
  }
  iVar12 = RTMPGetKeyParameter("WorkMode",local_74,0x19,param_2,1);
  if ((iVar12 != 0) && (local_70 = (char *)rstrtok(local_74,&_LC6), local_70 != (char *)0x0)) {
    piVar25 = param_1 + 0x29f463;
    uVar26 = 0;
    do {
      if (uVar26 < 2) {
        iVar12 = simple_strtol(local_70,0,10);
        *piVar25 = iVar12;
      }
      piVar25 = piVar25 + 9;
      local_70 = (char *)rstrtok(0,&_LC6);
      uVar26 = uVar26 + 1;
    } while (local_70 != (char *)0x0);
  }
  iVar12 = RTMPGetKeyParameter("E2pAccessMode",local_74,0x19,param_2,1);
  if (iVar12 != 0) {
    uVar2 = os_str_tol(local_74,0,10);
    iVar12 = DebugLevel;
    *(undefined1 *)(param_1 + 0xa5b4e) = uVar2;
    if (3 < iVar12) {
      printk("E2pAccessMode=%d\n",uVar2);
    }
  }
  iVar12 = RTMPGetKeyParameter("DisableCalFree",local_74,0x19,param_2,1);
  if (iVar12 != 0) {
    cVar4 = os_str_tol(local_74,0,10);
    iVar12 = hc_get_chip_ops(param_1[0x29e5e8]);
    if (cVar4 != '\0') {
      *(undefined4 *)(iVar12 + 0x8c) = 0;
    }
    if (3 < DebugLevel) {
      printk("DisableCalFree=%d\n");
    }
  }
  if (((char)param_1[0x1e530c] == '\0') &&
     (iVar12 = RTMPGetKeyParameter("CountryCode",local_74,0x19,param_2,1), iVar12 != 0)) {
    RTMPSetCountryCode(param_1,local_74);
  }
  if (*(char *)((int)param_1 + 0x286285) == '\x01') {
    bVar39 = false;
    pbVar29 = (byte *)(param_1 + 0xd9e32);
    iVar12 = 0;
    pbVar28 = pbVar29;
    while( true ) {
      if ((int)(uint)*(byte *)((int)param_1 + 0x2b7242) <= iVar12) break;
      snprintf((char *)local_68,0x10,"SSID%d",iVar12 + 1);
      iVar16 = RTMPGetKeyParameter(local_68,local_74,0x21,param_2,0);
      pcVar13 = local_74;
      if (iVar16 != 0) {
        bVar39 = true;
        sVar14 = strlen(local_74);
        memmove(param_1 + (uint)*pbVar28 * 0x160d + 0xaecac,pcVar13,sVar14);
        sVar14 = strlen(pcVar13);
        iVar37 = (uint)*pbVar28 * 0x5834;
        *(char *)((int)param_1 +
                 (int)(
                      "Set::OID_802_11_SET_PASSPHRASE, Failed (len less than 8 or greater than 64)!!\n"
                      + sVar14 + iVar37 + 0x34)) = '\0';
        sVar14 = strlen((char *)((int)param_1 +
                                (int)(
                                     "Set::OID_802_11_SET_PASSPHRASE, Failed (len less than 8 or greater than 64)!!\n"
                                     + iVar37 + 0x34)));
        iVar16 = DebugLevel;
        *(char *)((int)param_1 + iVar37 + 0x2bb2d1) = (char)sVar14;
        if (3 < iVar16) {
          printk("SSID[%d]=%s, EdcaIdx=%d\n",iVar12,
                 (char *)((int)param_1 +
                         (int)(
                              "Set::OID_802_11_SET_PASSPHRASE, Failed (len less than 8 or greater than 64)!!\n"
                              + iVar37 + 0x34)),*(undefined1 *)((int)param_1 + iVar37 + 0x2b7b1f));
          bVar39 = true;
        }
      }
      pbVar28 = pbVar28 + 1;
      iVar12 = iVar12 + 1;
    }
    pcVar13 = local_74;
    if ((!bVar39) &&
       (iVar12 = RTMPGetKeyParameter(&_LC171,local_74,0x100,param_2,0), pcVar13 = local_74,
       iVar12 != 0)) {
      cVar4 = '\0';
      pcVar18 = local_74;
      while( true ) {
        pcVar15 = strchr(pcVar18,0x3b);
        pcVar18 = pcVar15 + 1;
        if (pcVar15 == (char *)0x0) break;
        cVar4 = cVar4 + '\x01';
      }
      if ((*(char *)((int)param_1 + 0x2b7242) != (char)(cVar4 + '\x01')) && (-1 < DebugLevel)) {
        printk("Your no. of SSIDs( = %d) does not match your BssidNum( = %d)!\n");
        pcVar13 = local_74;
      }
      if (*(byte *)((int)param_1 + 0x2b7242) < 2) {
        if ((*pcVar13 != '\0') && (sVar14 = strlen(pcVar13), sVar14 < 0x21)) {
          piVar25 = param_1 + 0xaecac;
          memmove(piVar25,pcVar13,sVar14);
          sVar14 = strlen(pcVar13);
          *(char *)((int)param_1 +
                   (int)(
                        "Set::OID_802_11_SET_PASSPHRASE, Failed (len less than 8 or greater than 64)!!\n"
                        + sVar14 + 0x34)) = '\0';
          sVar14 = strlen((char *)piVar25);
          iVar12 = DebugLevel;
          *(char *)((int)param_1 + 0x2bb2d1) = (char)sVar14;
          pcVar13 = local_74;
          if (3 < iVar12) {
            printk("SSID=%s\n",piVar25);
            pcVar13 = local_74;
          }
        }
      }
      else {
        pcVar18 = (char *)rstrtok(pcVar13,&_LC6);
        pcVar13 = local_74;
        if ((pcVar18 != (char *)0x0) && (*(char *)((int)param_1 + 0x2b7242) != '\0')) {
          pbVar28 = (byte *)((int)param_1 + 0x3678c7);
          iVar12 = 0;
          do {
            sVar14 = strlen(pcVar18);
            pbVar28 = pbVar28 + 1;
            memmove(param_1 + (uint)*pbVar28 * 0x160d + 0xaecac,pcVar18,sVar14);
            sVar14 = strlen(pcVar18);
            iVar37 = (uint)*pbVar28 * 0x5834;
            *(char *)((int)param_1 +
                     (int)(
                          "Set::OID_802_11_SET_PASSPHRASE, Failed (len less than 8 or greater than 64)!!\n"
                          + sVar14 + iVar37 + 0x34)) = '\0';
            sVar14 = strlen((char *)((int)param_1 +
                                    (int)(
                                         "Set::OID_802_11_SET_PASSPHRASE, Failed (len less than 8 or greater than 64)!!\n"
                                         + iVar37 + 0x34)));
            iVar16 = DebugLevel;
            *(char *)((int)param_1 + iVar37 + 0x2bb2d1) = (char)sVar14;
            if (3 < iVar16) {
              printk("SSID[%d]=%s\n",iVar12,
                     (char *)((int)param_1 +
                             (int)(
                                  "Set::OID_802_11_SET_PASSPHRASE, Failed (len less than 8 or greater than 64)!!\n"
                                  + iVar37 + 0x34)));
            }
            iVar12 = iVar12 + 1;
            pcVar18 = (char *)rstrtok(0,&_LC6);
            pcVar13 = local_74;
          } while ((pcVar18 != (char *)0x0) &&
                  (iVar12 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242)));
        }
      }
    }
    iVar12 = RTMPGetKeyParameter("EdcaIdx",pcVar13,0x100,param_2,0);
    if (iVar12 != 0) {
      iVar16 = rstrtok(local_74,&_LC6);
      iVar12 = 0;
      while (iVar16 != 0) {
        if (iVar12 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242)) {
          uVar2 = os_str_tol(iVar16,0,10);
          *(undefined1 *)((int)param_1 + (uint)*pbVar29 * 0x5834 + 0x2b7b1f) = uVar2;
        }
        pbVar29 = pbVar29 + 1;
        iVar16 = rstrtok(0,&_LC6);
        iVar12 = iVar12 + 1;
      }
    }
  }
  pcVar13 = local_74;
  if (*(char *)((int)param_1 + 0x286285) == '\0') {
    iVar12 = RTMPGetKeyParameter(&_LC171,local_74,0x100,param_2,0);
    if ((iVar12 != 0) && (pcVar13 = (char *)rstrtok(local_74,&_LC6), pcVar13 != (char *)0x0)) {
      piVar25 = param_1 + 0xdb6d6;
      do {
        sVar14 = strlen(pcVar13);
        if ((sVar14 < 0x21) && (RTMPSetSTASSID(param_1,piVar25,pcVar13), 3 < DebugLevel)) {
          printk("%s::(SSID=%s)\n","RTMPSetProfileParameters",pcVar13);
        }
        pcVar13 = (char *)rstrtok(0,&_LC6);
        piVar25 = piVar25 + 0x84dec;
      } while (pcVar13 != (char *)0x0);
    }
    pcVar13 = local_74;
    if ((*(char *)((int)param_1 + 0x286285) == '\0') &&
       (iVar12 = RTMPGetKeyParameter("NetworkType",local_74,0x19,param_2,1), pcVar13 = local_74,
       iVar12 != 0)) {
      iVar12 = strcmp(local_74,"Adhoc");
      if (iVar12 == 0) {
        *(undefined1 *)(param_1 + 0xdc6ee) = 0;
      }
      else {
        *(undefined1 *)(param_1 + 0xdc6ee) = 1;
        *(undefined1 *)(param_1 + 0x1614da) = 1;
      }
      iVar12 = DebugLevel;
      *(undefined1 *)((int)param_1 + 0x580311) = 0;
      *(undefined1 *)(param_1 + 0x15fff0) = 1;
      *(undefined1 *)((int)param_1 + 0x793ac1) = 0;
      *(undefined1 *)(param_1 + 0x1e4ddc) = 1;
      if (3 < iVar12) {
        printk("%s::(NetworkType=%d)\n","RTMPSetProfileParameters",(char)param_1[0xdc6ee]);
        pcVar13 = local_74;
      }
    }
  }
  iVar12 = RTMPGetKeyParameter("DBDC_MODE",pcVar13,0x19,param_2,1);
  if (iVar12 != 0) {
    iVar16 = os_str_tol(local_74,0,10);
    iVar12 = DebugLevel;
    param_1[0x1e5414] = iVar16;
    *(bool *)((int)param_1 + 0x79504d) = iVar16 != 0;
    if (3 < iVar12) {
      printk("%s(): DBDC Mode=%d, eDBDC_mode = %d\n","RTMPSetProfileParameters");
    }
  }
  if (((param_1[0xa5b19] & 0xffffU) == 0x7626) &&
     (*(undefined1 *)((int)param_1 + 0x79504d) = 1, 3 < DebugLevel)) {
    printk("%s(): MT7626 only support DBDC Mode=%d\n","RTMPSetProfileParameters");
  }
  iVar12 = RTMPGetKeyParameter("DfsCalibration",local_74,0x19,param_2,1);
  if (iVar12 != 0) {
    uVar2 = os_str_tol(local_74,0,10);
    *(undefined1 *)((int)param_1 + 0x7953ed) = uVar2;
  }
  iVar12 = RTMPGetKeyParameter("DfsEnable",local_74,0x19,param_2,1);
  if (iVar12 != 0) {
    uVar2 = os_str_tol(local_74,0,10);
    *(undefined1 *)((int)param_1 + 0x7953ef) = uVar2;
  }
  iVar12 = RTMPGetKeyParameter("WirelessMode",local_74,0x80,param_2,1);
  if (iVar12 != 0) {
    FUN_000ee450(param_1,local_74);
  }
  iVar12 = RTMPGetKeyParameter("AutoChannelSelect",local_74,10,param_2,1);
  if (iVar12 != 0) {
    auto_ch_select_set_cfg(param_1,local_74);
  }
  iVar12 = RTMPGetKeyParameter("ChannelGrp",local_74,0x19,param_2,1);
  if (iVar12 != 0) {
    MTSetChGrp(param_1,local_74);
  }
  iVar12 = RTMPGetKeyParameter("Channel",local_74,0x80,param_2,1);
  if (iVar12 != 0) {
    FUN_000ee7ac(param_1,local_74);
  }
  iVar12 = RTMPGetKeyParameter("EtherTrafficBand",local_74,10,param_2,1);
  if (iVar12 != 0) {
    uVar2 = os_str_tol(local_74,0,10);
    iVar12 = DebugLevel;
    *(undefined1 *)((int)param_1 + 0x794ca5) = uVar2;
    if (3 < iVar12) {
      printk("EtherTrafficBand=%d\n",uVar2);
    }
    if (1 < *(byte *)((int)param_1 + 0x794ca5)) {
      *(undefined1 *)((int)param_1 + 0x794ca5) = 1;
    }
  }
  iVar12 = RTMPGetKeyParameter("WfFwdDisabled",local_74,10,param_2,1);
  if (iVar12 != 0) {
    uVar2 = os_str_tol(local_74,0,10);
    iVar12 = DebugLevel;
    *(undefined1 *)((int)param_1 + 0x794ca6) = uVar2;
    if (3 < iVar12) {
      printk("WfFwdDisabled=%d\n",uVar2);
    }
  }
  iVar12 = RTMPGetKeyParameter("BasicRate",local_74,10,param_2,1);
  if (iVar12 != 0) {
    iVar12 = os_str_tol(local_74,0,10);
    param_1[0x1e5327] = iVar12;
    iVar16 = os_str_tol(local_74,0,10);
    iVar12 = DebugLevel;
    param_1[0x1e5328] = iVar16;
    if (3 < iVar12) {
      printk("BasicRate=%ld\n",param_1[0x1e5327]);
    }
  }
  iVar12 = RTMPGetKeyParameter("BeaconPeriod",local_74,0x80,param_2,1);
  if (iVar12 != 0) {
    uVar9 = os_str_tol(local_74,0,10);
    if (uVar9 - 0x14 < 0x3d5) {
      *(ushort *)(param_1 + 0x1e5314) = uVar9;
    }
    else {
      *(ushort *)(param_1 + 0x1e5314) = 100;
    }
    if (3 < DebugLevel) {
      printk("BeaconPeriod=%d\n",(short)param_1[0x1e5314]);
    }
  }
  if (*(char *)((int)param_1 + 0x286285) == '\x01') {
    WNM_ReadParametersFromFile(param_1,local_74,param_2);
    iVar12 = RTMPGetKeyParameter("DtimPeriod",local_74,0x80,param_2,1);
    if (iVar12 != 0) {
      iVar12 = rstrtok(local_74,&_LC6);
      if (iVar12 != 0) {
        pbVar29 = (byte *)(param_1 + 0xd9e32);
        uVar26 = 0;
        do {
          uVar2 = os_str_tol(iVar12,0,10);
          if (*(char *)((int)param_1 + 0x286285) == '\x01') {
            if (*(byte *)((int)param_1 + 0x2b7242) <= uVar26) break;
            if (uVar26 == 0) {
              *(undefined1 *)(param_1 + 0xdae28) = uVar2;
            }
            *(undefined1 *)((int)param_1 + (uint)*pbVar29 * 0x5834 + 0x2bb2d3) = uVar2;
          }
          iVar12 = rstrtok(0,&_LC6);
          uVar26 = uVar26 + 1;
          pbVar29 = pbVar29 + 1;
        } while (iVar12 != 0);
      }
      if (*(char *)((int)param_1 + 0x2b7242) != '\0') {
        pbVar29 = (byte *)((int)param_1 + 0x3678c7);
        uVar26 = 0;
        do {
          pbVar29 = pbVar29 + 1;
          uVar19 = (uint)*pbVar29;
          if (*(char *)((int)param_1 + uVar19 * 0x5834 + 0x2bb2d3) == '\0') {
            *(char *)((int)param_1 + uVar19 * 0x5834 + 0x2bb2d3) = (char)param_1[0xdae28];
          }
          if (3 < DebugLevel) {
            printk("BSS%d DtimPeriod=%d\n",uVar26,
                   *(undefined1 *)((int)param_1 + uVar19 * 0x5834 + 0x2bb2d3));
          }
          uVar26 = uVar26 + 1;
        } while (uVar26 < *(byte *)((int)param_1 + 0x2b7242));
      }
    }
  }
  iVar12 = RTMPGetKeyParameter("TxPower",local_74,10,param_2,1);
  if (iVar12 != 0) {
    local_70 = (char *)rstrtok(local_74,&_LC6);
    if (local_70 != (char *)0x0) {
      iVar12 = 0;
      do {
        if (*(char *)((int)param_1 + 0x79504d) == '\0') {
          if (iVar12 == 0) {
LAB_000f63b8:
            uVar2 = simple_strtol(local_70,iVar12,10);
            *(undefined1 *)(param_1 + 0x1e5336) = uVar2;
          }
        }
        else {
          if (iVar12 == 0) goto LAB_000f63b8;
          if (iVar12 == 1) {
            uVar2 = simple_strtol(local_70,0,10);
            *(undefined1 *)((int)param_1 + 0x794cd9) = uVar2;
          }
        }
        iVar12 = iVar12 + 1;
        local_70 = (char *)rstrtok(0,&_LC6);
      } while (local_70 != (char *)0x0);
    }
    if (*(char *)((int)param_1 + 0x79504d) == '\0') {
      if (3 < DebugLevel) {
        printk("[TxPower] BAND0: %d\n",(char)param_1[0x1e5336]);
      }
    }
    else if (3 < DebugLevel) {
      printk("[TxPower] BAND0: %d, BAND1: %d\n",(char)param_1[0x1e5336],
             *(undefined1 *)((int)param_1 + 0x794cd9));
    }
    if (*(char *)((int)param_1 + 0x286285) == '\0') {
      *(char *)((int)param_1 + 0x795041) = (char)param_1[0x1e5336];
      *(undefined1 *)((int)param_1 + 0x795042) = *(undefined1 *)((int)param_1 + 0x794cd9);
    }
  }
  iVar12 = RTMPGetKeyParameter("PowerUpenable",local_74,0x20,param_2,1);
  if (iVar12 != 0) {
    local_70 = (char *)rstrtok(local_74,&_LC6);
    if (local_70 != (char *)0x0) {
      iVar12 = 0;
      do {
        if (*(char *)((int)param_1 + 0x79504d) == '\0') {
          if (iVar12 == 0) {
LAB_000f62e4:
            uVar2 = simple_strtol(local_70,iVar12,10);
            *(undefined1 *)(param_1 + 0x1e5336) = uVar2;
          }
        }
        else {
          if (iVar12 == 0) goto LAB_000f62e4;
          if (iVar12 == 1) {
            uVar2 = simple_strtol(local_70,0,10);
            *(undefined1 *)((int)param_1 + 0x794cd9) = uVar2;
          }
        }
        iVar12 = iVar12 + 1;
        local_70 = (char *)rstrtok(0,&_LC6);
      } while (local_70 != (char *)0x0);
    }
    if (*(char *)((int)param_1 + 0x79504d) == '\0') {
      if (3 < DebugLevel) {
        printk("[PowerUpenable] BAND0: %d\n",(char)param_1[0x1e5336]);
      }
    }
    else if (3 < DebugLevel) {
      printk("[PowerUpenable] BAND0: %d, BAND1: %d\n",(char)param_1[0x1e5336],
             *(undefined1 *)((int)param_1 + 0x794cd9));
    }
  }
  iVar12 = RTMPGetKeyParameter("PowerUpCck",local_74,0x20,param_2,1);
  if (iVar12 != 0) {
    if (*(char *)((int)param_1 + 0x79504d) == '\0') {
      local_70 = (char *)rstrtok(local_74,&_LC202);
      if ((local_70 != (char *)0x0) && (*(char *)(iVar10 + 0x202) != '\0')) {
        iVar12 = 0;
        do {
          pcVar13 = strsep(&local_70,":");
          if (pcVar13 != (char *)0x0) {
            uVar26 = 0;
            do {
              uVar2 = simple_strtol(pcVar13,0,10);
              *(undefined1 *)((int)&local_76 + uVar26) = uVar2;
              pcVar13 = strsep(&local_70,":");
              uVar19 = uVar26 ^ 1;
              uVar26 = 1;
              if (pcVar13 == (char *)0x0) {
                uVar19 = 0;
              }
            } while (uVar19 != 0);
          }
          uVar26 = (uint)(byte)local_76;
          if (uVar26 < *(byte *)(iVar10 + 0x202)) {
            if (*(char *)(iVar10 + 0x210) == '\0') {
              *(undefined1 *)((int)param_1 + uVar26 + 0x794cde) = local_76._1_1_;
            }
            else if (*(char *)(iVar10 + 0x210) == '\x01') {
              *(undefined1 *)((int)param_1 + uVar26 + 0x794d68) = local_76._1_1_;
            }
          }
          else if (-1 < DebugLevel) {
            printk("[PowerUpCck] Input parameter incorrect!!\n");
          }
          iVar12 = iVar12 + 1;
          local_70 = (char *)rstrtok(0,&_LC202);
        } while ((local_70 != (char *)0x0) && (iVar12 < (int)(uint)*(byte *)(iVar10 + 0x202)));
      }
    }
    else {
      local_70 = (char *)rstrtok(local_74,&_LC6);
      if ((local_70 == (char *)0x0) ||
         (local_48 = local_70, local_70 = (char *)rstrtok(0,&_LC6), local_70 == (char *)0x0)) {
        if (-1 < DebugLevel) {
          printk("[PowerUpCck] Input parameter incorrect!!\n");
        }
      }
      else {
        local_44 = local_70;
        rstrtok(0,&_LC6);
      }
      local_70 = local_48;
      local_70 = (char *)rstrtok(local_48,&_LC202);
      if ((local_70 != (char *)0x0) && (*(char *)(iVar10 + 0x202) != '\0')) {
        iVar12 = 0;
        do {
          pcVar13 = strsep(&local_70,":");
          if (pcVar13 != (char *)0x0) {
            uVar26 = 0;
            do {
              uVar2 = simple_strtol(pcVar13,0,10);
              *(undefined1 *)((int)&local_76 + uVar26) = uVar2;
              pcVar13 = strsep(&local_70,":");
              uVar19 = uVar26 ^ 1;
              uVar26 = 1;
              if (pcVar13 == (char *)0x0) {
                uVar19 = 0;
              }
            } while (uVar19 != 0);
          }
          uVar26 = (uint)(byte)local_76;
          if (uVar26 < *(byte *)(iVar10 + 0x202)) {
            if (*(char *)(iVar10 + 0x210) == '\0') {
              *(undefined1 *)((int)param_1 + uVar26 + 0x794d23) = local_76._1_1_;
            }
            else if (*(char *)(iVar10 + 0x210) == '\x01') {
              *(undefined1 *)((int)param_1 + uVar26 + 0x794e09) = local_76._1_1_;
            }
          }
          else if (-1 < DebugLevel) {
            printk("[PowerUpCck] Input parameter incorrect!!\n");
          }
          iVar12 = iVar12 + 1;
          local_70 = (char *)rstrtok(0,&_LC202);
        } while ((local_70 != (char *)0x0) && (iVar12 < (int)(uint)*(byte *)(iVar10 + 0x202)));
      }
      local_70 = local_44;
      local_70 = (char *)rstrtok(local_44,&_LC202);
      if ((local_70 != (char *)0x0) && (*(char *)(iVar10 + 0x202) != '\0')) {
        iVar12 = 0;
        do {
          pcVar13 = strsep(&local_70,":");
          if (pcVar13 != (char *)0x0) {
            uVar26 = 0;
            do {
              uVar2 = simple_strtol(pcVar13,0,10);
              *(undefined1 *)((int)&local_76 + uVar26) = uVar2;
              pcVar13 = strsep(&local_70,":");
              uVar19 = uVar26 ^ 1;
              uVar26 = 1;
              if (pcVar13 == (char *)0x0) {
                uVar19 = 0;
              }
            } while (uVar19 != 0);
          }
          uVar26 = (uint)(byte)local_76;
          if (uVar26 < *(byte *)(iVar10 + 0x202)) {
            if (*(char *)(iVar10 + 0x210) == '\0') {
              *(undefined1 *)((int)param_1 + uVar26 + 0x794cde) = local_76._1_1_;
            }
            else if (*(char *)(iVar10 + 0x210) == '\x01') {
              *(undefined1 *)((int)param_1 + uVar26 + 0x794d68) = local_76._1_1_;
            }
          }
          else if (-1 < DebugLevel) {
            printk("[PowerUpCck] Input parameter incorrect!!\n");
          }
          iVar12 = iVar12 + 1;
          local_70 = (char *)rstrtok(0,&_LC202);
        } while ((local_70 != (char *)0x0) && (iVar12 < (int)(uint)*(byte *)(iVar10 + 0x202)));
      }
    }
  }
  iVar12 = RTMPGetKeyParameter("PowerUpOfdm",local_74,0x20,param_2,1);
  if (iVar12 != 0) {
    if (*(char *)((int)param_1 + 0x79504d) == '\0') {
      local_70 = (char *)rstrtok(local_74,&_LC202);
      if ((local_70 != (char *)0x0) && (*(char *)(iVar10 + 0x203) != '\0')) {
        iVar12 = 0;
        do {
          pcVar13 = strsep(&local_70,":");
          if (pcVar13 != (char *)0x0) {
            uVar26 = 0;
            do {
              uVar2 = simple_strtol(pcVar13,0,10);
              *(undefined1 *)((int)&local_76 + uVar26) = uVar2;
              pcVar13 = strsep(&local_70,":");
              uVar19 = uVar26 ^ 1;
              uVar26 = 1;
              if (pcVar13 == (char *)0x0) {
                uVar19 = 0;
              }
            } while (uVar19 != 0);
          }
          uVar26 = (uint)(byte)local_76;
          if (uVar26 < *(byte *)(iVar10 + 0x203)) {
            if (*(char *)(iVar10 + 0x210) == '\0') {
              *(undefined1 *)((int)param_1 + uVar26 + 0x794ce2) = local_76._1_1_;
            }
            else if (*(char *)(iVar10 + 0x210) == '\x01') {
              *(undefined1 *)((int)param_1 + uVar26 + 0x794d6c) = local_76._1_1_;
            }
          }
          else if (-1 < DebugLevel) {
            printk("[PowerUpOfdm] Input parameter incorrect!!\n");
          }
          iVar12 = iVar12 + 1;
          local_70 = (char *)rstrtok(0,&_LC202);
        } while ((local_70 != (char *)0x0) && (iVar12 < (int)(uint)*(byte *)(iVar10 + 0x203)));
      }
    }
    else {
      local_70 = (char *)rstrtok(local_74,&_LC6);
      if ((local_70 == (char *)0x0) ||
         (local_48 = local_70, local_70 = (char *)rstrtok(0,&_LC6), local_70 == (char *)0x0)) {
        if (-1 < DebugLevel) {
          printk("[PowerUpOfdm] Input parameter incorrect!!\n");
        }
      }
      else {
        local_44 = local_70;
        rstrtok(0,&_LC6);
      }
      local_70 = local_48;
      local_70 = (char *)rstrtok(local_48,&_LC202);
      if ((local_70 != (char *)0x0) && (*(char *)(iVar10 + 0x203) != '\0')) {
        iVar12 = 0;
        do {
          pcVar13 = strsep(&local_70,":");
          if (pcVar13 != (char *)0x0) {
            uVar26 = 0;
            do {
              uVar2 = simple_strtol(pcVar13,0,10);
              *(undefined1 *)((int)&local_76 + uVar26) = uVar2;
              pcVar13 = strsep(&local_70,":");
              uVar19 = uVar26 ^ 1;
              uVar26 = 1;
              if (pcVar13 == (char *)0x0) {
                uVar19 = 0;
              }
            } while (uVar19 != 0);
          }
          uVar26 = (uint)(byte)local_76;
          if (uVar26 < *(byte *)(iVar10 + 0x203)) {
            if (*(char *)(iVar10 + 0x210) == '\0') {
              *(undefined1 *)((int)param_1 + uVar26 + 0x794d27) = local_76._1_1_;
            }
            else if (*(char *)(iVar10 + 0x210) == '\x01') {
              *(undefined1 *)((int)param_1 + uVar26 + 0x794e0d) = local_76._1_1_;
            }
          }
          else if (-1 < DebugLevel) {
            printk("[PowerUpOfdm] Input parameter incorrect!!\n");
          }
          iVar12 = iVar12 + 1;
          local_70 = (char *)rstrtok(0,&_LC202);
        } while ((local_70 != (char *)0x0) && (iVar12 < (int)(uint)*(byte *)(iVar10 + 0x203)));
      }
      local_70 = local_44;
      local_70 = (char *)rstrtok(local_44,&_LC202);
      if ((local_70 != (char *)0x0) && (*(char *)(iVar10 + 0x203) != '\0')) {
        iVar12 = 0;
        do {
          pcVar13 = strsep(&local_70,":");
          if (pcVar13 != (char *)0x0) {
            uVar26 = 0;
            do {
              uVar2 = simple_strtol(pcVar13,0,10);
              *(undefined1 *)((int)&local_76 + uVar26) = uVar2;
              pcVar13 = strsep(&local_70,":");
              uVar19 = uVar26 ^ 1;
              uVar26 = 1;
              if (pcVar13 == (char *)0x0) {
                uVar19 = 0;
              }
            } while (uVar19 != 0);
          }
          uVar26 = (uint)(byte)local_76;
          if (uVar26 < *(byte *)(iVar10 + 0x203)) {
            if (*(char *)(iVar10 + 0x210) == '\0') {
              *(undefined1 *)((int)param_1 + uVar26 + 0x794ce2) = local_76._1_1_;
            }
            else if (*(char *)(iVar10 + 0x210) == '\x01') {
              *(undefined1 *)((int)param_1 + uVar26 + 0x794d6c) = local_76._1_1_;
            }
          }
          else if (-1 < DebugLevel) {
            printk("[PowerUpOfdm] Input parameter incorrect!!\n");
          }
          iVar12 = iVar12 + 1;
          local_70 = (char *)rstrtok(0,&_LC202);
        } while ((local_70 != (char *)0x0) && (iVar12 < (int)(uint)*(byte *)(iVar10 + 0x203)));
      }
    }
  }
  iVar12 = RTMPGetKeyParameter("PowerUpHT20",local_74,0x20,param_2,1);
  if (iVar12 != 0) {
    if (*(char *)((int)param_1 + 0x79504d) == '\0') {
      local_70 = (char *)rstrtok(local_74,&_LC202);
      if ((local_70 != (char *)0x0) && (*(char *)(iVar10 + 0x204) != '\0')) {
        iVar12 = 0;
        do {
          pcVar13 = strsep(&local_70,":");
          if (pcVar13 != (char *)0x0) {
            uVar26 = 0;
            do {
              uVar2 = simple_strtol(pcVar13,0,10);
              *(undefined1 *)((int)&local_76 + uVar26) = uVar2;
              pcVar13 = strsep(&local_70,":");
              uVar19 = uVar26 ^ 1;
              uVar26 = 1;
              if (pcVar13 == (char *)0x0) {
                uVar19 = 0;
              }
            } while (uVar19 != 0);
          }
          uVar26 = (uint)(byte)local_76;
          if (uVar26 < *(byte *)(iVar10 + 0x204)) {
            if (*(char *)(iVar10 + 0x210) == '\0') {
              *(undefined1 *)((int)param_1 + uVar26 + 0x794cea) = local_76._1_1_;
            }
            else if (*(char *)(iVar10 + 0x210) == '\x01') {
              *(undefined1 *)((int)param_1 + uVar26 + 0x794d74) = local_76._1_1_;
            }
          }
          else if (-1 < DebugLevel) {
            printk("[PowerUpHT20] Input parameter incorrect!!\n");
          }
          iVar12 = iVar12 + 1;
          local_70 = (char *)rstrtok(0,&_LC202);
        } while ((local_70 != (char *)0x0) && (iVar12 < (int)(uint)*(byte *)(iVar10 + 0x204)));
      }
    }
    else {
      local_70 = (char *)rstrtok(local_74,&_LC6);
      if ((local_70 == (char *)0x0) ||
         (local_48 = local_70, local_70 = (char *)rstrtok(0,&_LC6), local_70 == (char *)0x0)) {
        if (-1 < DebugLevel) {
          printk("[PowerUpHT20] Input parameter incorrect!!\n");
        }
      }
      else {
        local_44 = local_70;
        rstrtok(0,&_LC6);
      }
      local_70 = local_48;
      local_70 = (char *)rstrtok(local_48,&_LC202);
      if ((local_70 != (char *)0x0) && (*(char *)(iVar10 + 0x204) != '\0')) {
        iVar12 = 0;
        do {
          pcVar13 = strsep(&local_70,":");
          if (pcVar13 != (char *)0x0) {
            uVar26 = 0;
            do {
              uVar2 = simple_strtol(pcVar13,0,10);
              *(undefined1 *)((int)&local_76 + uVar26) = uVar2;
              pcVar13 = strsep(&local_70,":");
              uVar19 = uVar26 ^ 1;
              uVar26 = 1;
              if (pcVar13 == (char *)0x0) {
                uVar19 = 0;
              }
            } while (uVar19 != 0);
          }
          uVar26 = (uint)(byte)local_76;
          if (uVar26 < *(byte *)(iVar10 + 0x204)) {
            if (*(char *)(iVar10 + 0x210) == '\0') {
              *(undefined1 *)((int)param_1 + uVar26 + 0x794d2f) = local_76._1_1_;
            }
            else if (*(char *)(iVar10 + 0x210) == '\x01') {
              *(undefined1 *)((int)param_1 + uVar26 + 0x794e15) = local_76._1_1_;
            }
          }
          else if (-1 < DebugLevel) {
            printk("[PowerUpHT20] Input parameter incorrect!!\n");
          }
          iVar12 = iVar12 + 1;
          local_70 = (char *)rstrtok(0,&_LC202);
        } while ((local_70 != (char *)0x0) && (iVar12 < (int)(uint)*(byte *)(iVar10 + 0x204)));
      }
      local_70 = local_44;
      local_70 = (char *)rstrtok(local_44,&_LC202);
      if ((local_70 != (char *)0x0) && (*(char *)(iVar10 + 0x204) != '\0')) {
        iVar12 = 0;
        do {
          pcVar13 = strsep(&local_70,":");
          if (pcVar13 != (char *)0x0) {
            uVar26 = 0;
            do {
              uVar2 = simple_strtol(pcVar13,0,10);
              *(undefined1 *)((int)&local_76 + uVar26) = uVar2;
              pcVar13 = strsep(&local_70,":");
              uVar19 = uVar26 ^ 1;
              uVar26 = 1;
              if (pcVar13 == (char *)0x0) {
                uVar19 = 0;
              }
            } while (uVar19 != 0);
          }
          uVar26 = (uint)(byte)local_76;
          if (uVar26 < *(byte *)(iVar10 + 0x204)) {
            if (*(char *)(iVar10 + 0x210) == '\0') {
              *(undefined1 *)((int)param_1 + uVar26 + 0x794cea) = local_76._1_1_;
            }
            else if (*(char *)(iVar10 + 0x210) == '\x01') {
              *(undefined1 *)((int)param_1 + uVar26 + 0x794d74) = local_76._1_1_;
            }
          }
          else if (-1 < DebugLevel) {
            printk("[PowerUpHT20] Input parameter incorrect!!\n");
          }
          iVar12 = iVar12 + 1;
          local_70 = (char *)rstrtok(0,&_LC202);
        } while ((local_70 != (char *)0x0) && (iVar12 < (int)(uint)*(byte *)(iVar10 + 0x204)));
      }
    }
  }
  iVar12 = RTMPGetKeyParameter("PowerUpHT40",local_74,0x20,param_2,1);
  if (iVar12 != 0) {
    if (*(char *)((int)param_1 + 0x79504d) == '\0') {
      local_70 = (char *)rstrtok(local_74,&_LC202);
      if ((local_70 != (char *)0x0) && (*(char *)(iVar10 + 0x205) != '\0')) {
        iVar12 = 0;
        do {
          pcVar13 = strsep(&local_70,":");
          if (pcVar13 != (char *)0x0) {
            uVar26 = 0;
            do {
              uVar2 = simple_strtol(pcVar13,0,10);
              *(undefined1 *)((int)&local_76 + uVar26) = uVar2;
              pcVar13 = strsep(&local_70,":");
              uVar19 = uVar26 ^ 1;
              uVar26 = 1;
              if (pcVar13 == (char *)0x0) {
                uVar19 = 0;
              }
            } while (uVar19 != 0);
          }
          uVar26 = (uint)(byte)local_76;
          if (uVar26 < *(byte *)(iVar10 + 0x205)) {
            if (*(char *)(iVar10 + 0x210) == '\0') {
              *(undefined1 *)((int)param_1 + uVar26 + 0x794cf2) = local_76._1_1_;
            }
            else if (*(char *)(iVar10 + 0x210) == '\x01') {
              *(undefined1 *)((int)param_1 + uVar26 + 0x794d7c) = local_76._1_1_;
            }
          }
          else if (-1 < DebugLevel) {
            printk("[PowerUpHT40] Input parameter incorrect!!\n");
          }
          iVar12 = iVar12 + 1;
          local_70 = (char *)rstrtok(0,&_LC202);
        } while ((local_70 != (char *)0x0) && (iVar12 < (int)(uint)*(byte *)(iVar10 + 0x205)));
      }
    }
    else {
      local_70 = (char *)rstrtok(local_74,&_LC6);
      if ((local_70 == (char *)0x0) ||
         (local_48 = local_70, local_70 = (char *)rstrtok(0,&_LC6), local_70 == (char *)0x0)) {
        if (-1 < DebugLevel) {
          printk("[PowerUpHT40] Input parameter incorrect!!\n");
        }
      }
      else {
        local_44 = local_70;
        rstrtok(0,&_LC6);
      }
      local_70 = local_48;
      local_70 = (char *)rstrtok(local_48,&_LC202);
      if ((local_70 != (char *)0x0) && (*(char *)(iVar10 + 0x205) != '\0')) {
        iVar12 = 0;
        do {
          pcVar13 = strsep(&local_70,":");
          if (pcVar13 != (char *)0x0) {
            uVar26 = 0;
            do {
              uVar2 = simple_strtol(pcVar13,0,10);
              *(undefined1 *)((int)&local_76 + uVar26) = uVar2;
              pcVar13 = strsep(&local_70,":");
              uVar19 = uVar26 ^ 1;
              uVar26 = 1;
              if (pcVar13 == (char *)0x0) {
                uVar19 = 0;
              }
            } while (uVar19 != 0);
          }
          uVar26 = (uint)(byte)local_76;
          if (uVar26 < *(byte *)(iVar10 + 0x205)) {
            if (*(char *)(iVar10 + 0x210) == '\0') {
              *(undefined1 *)((int)param_1 + uVar26 + 0x794d37) = local_76._1_1_;
            }
            else if (*(char *)(iVar10 + 0x210) == '\x01') {
              *(undefined1 *)((int)param_1 + uVar26 + 0x794e1d) = local_76._1_1_;
            }
          }
          else if (-1 < DebugLevel) {
            printk("[PowerUpHT40] Input parameter incorrect!!\n");
          }
          iVar12 = iVar12 + 1;
          local_70 = (char *)rstrtok(0,&_LC202);
        } while ((local_70 != (char *)0x0) && (iVar12 < (int)(uint)*(byte *)(iVar10 + 0x205)));
      }
      local_70 = local_44;
      local_70 = (char *)rstrtok(local_44,&_LC202);
      if ((local_70 != (char *)0x0) && (*(char *)(iVar10 + 0x205) != '\0')) {
        iVar12 = 0;
        do {
          pcVar13 = strsep(&local_70,":");
          if (pcVar13 != (char *)0x0) {
            uVar26 = 0;
            do {
              uVar2 = simple_strtol(pcVar13,0,10);
              *(undefined1 *)((int)&local_76 + uVar26) = uVar2;
              pcVar13 = strsep(&local_70,":");
              uVar19 = uVar26 ^ 1;
              uVar26 = 1;
              if (pcVar13 == (char *)0x0) {
                uVar19 = 0;
              }
            } while (uVar19 != 0);
          }
          uVar26 = (uint)(byte)local_76;
          if (uVar26 < *(byte *)(iVar10 + 0x205)) {
            if (*(char *)(iVar10 + 0x210) == '\0') {
              *(undefined1 *)((int)param_1 + uVar26 + 0x794cf2) = local_76._1_1_;
            }
            else if (*(char *)(iVar10 + 0x210) == '\x01') {
              *(undefined1 *)((int)param_1 + uVar26 + 0x794d7c) = local_76._1_1_;
            }
          }
          else if (-1 < DebugLevel) {
            printk("[PowerUpHT40] Input parameter incorrect!!\n");
          }
          iVar12 = iVar12 + 1;
          local_70 = (char *)rstrtok(0,&_LC202);
        } while ((local_70 != (char *)0x0) && (iVar12 < (int)(uint)*(byte *)(iVar10 + 0x205)));
      }
    }
  }
  iVar12 = RTMPGetKeyParameter("PowerUpVHT20",local_74,0x20,param_2,1);
  if (iVar12 != 0) {
    if (*(char *)((int)param_1 + 0x79504d) == '\0') {
      local_70 = (char *)rstrtok(local_74,&_LC202);
      if ((local_70 != (char *)0x0) && (*(char *)(iVar10 + 0x206) != '\0')) {
        iVar12 = 0;
        do {
          pcVar13 = strsep(&local_70,":");
          if (pcVar13 != (char *)0x0) {
            uVar26 = 0;
            do {
              uVar2 = simple_strtol(pcVar13,0,10);
              *(undefined1 *)((int)&local_76 + uVar26) = uVar2;
              pcVar13 = strsep(&local_70,":");
              uVar19 = uVar26 ^ 1;
              uVar26 = 1;
              if (pcVar13 == (char *)0x0) {
                uVar19 = 0;
              }
            } while (uVar19 != 0);
          }
          uVar26 = (uint)(byte)local_76;
          if (uVar26 < *(byte *)(iVar10 + 0x206)) {
            if (*(char *)(iVar10 + 0x210) == '\0') {
              *(undefined1 *)((int)param_1 + uVar26 + 0x794cfb) = local_76._1_1_;
            }
            else if (*(char *)(iVar10 + 0x210) == '\x01') {
              *(undefined1 *)((int)param_1 + uVar26 + 0x794d85) = local_76._1_1_;
            }
          }
          else if (-1 < DebugLevel) {
            printk("[PowerUpVHT20] Input parameter incorrect!!\n");
          }
          iVar12 = iVar12 + 1;
          local_70 = (char *)rstrtok(0,&_LC202);
        } while ((local_70 != (char *)0x0) && (iVar12 < (int)(uint)*(byte *)(iVar10 + 0x206)));
      }
    }
    else {
      local_70 = (char *)rstrtok(local_74,&_LC6);
      if ((local_70 == (char *)0x0) ||
         (local_48 = local_70, local_70 = (char *)rstrtok(0,&_LC6), local_70 == (char *)0x0)) {
        if (-1 < DebugLevel) {
          printk("[PowerUpVHT20] Input parameter incorrect!!\n");
        }
      }
      else {
        local_44 = local_70;
        rstrtok(0,&_LC6);
      }
      local_70 = local_48;
      local_70 = (char *)rstrtok(local_48,&_LC202);
      if ((local_70 != (char *)0x0) && (*(char *)(iVar10 + 0x206) != '\0')) {
        iVar12 = 0;
        do {
          pcVar13 = strsep(&local_70,":");
          if (pcVar13 != (char *)0x0) {
            uVar26 = 0;
            do {
              uVar2 = simple_strtol(pcVar13,0,10);
              *(undefined1 *)((int)&local_76 + uVar26) = uVar2;
              pcVar13 = strsep(&local_70,":");
              uVar19 = uVar26 ^ 1;
              uVar26 = 1;
              if (pcVar13 == (char *)0x0) {
                uVar19 = 0;
              }
            } while (uVar19 != 0);
          }
          uVar26 = (uint)(byte)local_76;
          if (uVar26 < *(byte *)(iVar10 + 0x206)) {
            if (*(char *)(iVar10 + 0x210) == '\0') {
              *(undefined1 *)((int)param_1 + uVar26 + 0x794d40) = local_76._1_1_;
            }
            else if (*(char *)(iVar10 + 0x210) == '\x01') {
              *(undefined1 *)((int)param_1 + uVar26 + 0x794e26) = local_76._1_1_;
            }
          }
          else if (-1 < DebugLevel) {
            printk("[PowerUpVHT20] Input parameter incorrect!!\n");
          }
          iVar12 = iVar12 + 1;
          local_70 = (char *)rstrtok(0,&_LC202);
        } while ((local_70 != (char *)0x0) && (iVar12 < (int)(uint)*(byte *)(iVar10 + 0x206)));
      }
      local_70 = local_44;
      local_70 = (char *)rstrtok(local_44,&_LC202);
      if ((local_70 != (char *)0x0) && (*(char *)(iVar10 + 0x206) != '\0')) {
        iVar12 = 0;
        do {
          pcVar13 = strsep(&local_70,":");
          if (pcVar13 != (char *)0x0) {
            uVar26 = 0;
            do {
              uVar2 = simple_strtol(pcVar13,0,10);
              *(undefined1 *)((int)&local_76 + uVar26) = uVar2;
              pcVar13 = strsep(&local_70,":");
              uVar19 = uVar26 ^ 1;
              uVar26 = 1;
              if (pcVar13 == (char *)0x0) {
                uVar19 = 0;
              }
            } while (uVar19 != 0);
          }
          uVar26 = (uint)(byte)local_76;
          if (uVar26 < *(byte *)(iVar10 + 0x206)) {
            if (*(char *)(iVar10 + 0x210) == '\0') {
              *(undefined1 *)((int)param_1 + uVar26 + 0x794cfb) = local_76._1_1_;
            }
            else if (*(char *)(iVar10 + 0x210) == '\x01') {
              *(undefined1 *)((int)param_1 + uVar26 + 0x794d85) = local_76._1_1_;
            }
          }
          else if (-1 < DebugLevel) {
            printk("[PowerUpVHT20] Input parameter incorrect!!\n");
          }
          iVar12 = iVar12 + 1;
          local_70 = (char *)rstrtok(0,&_LC202);
        } while ((local_70 != (char *)0x0) && (iVar12 < (int)(uint)*(byte *)(iVar10 + 0x206)));
      }
    }
  }
  iVar12 = RTMPGetKeyParameter("PowerUpVHT40",local_74,0x20,param_2,1);
  if (iVar12 != 0) {
    if (*(char *)((int)param_1 + 0x79504d) == '\0') {
      local_70 = (char *)rstrtok(local_74,&_LC202);
      if ((local_70 != (char *)0x0) && (*(char *)(iVar10 + 0x207) != '\0')) {
        iVar12 = 0;
        do {
          pcVar13 = strsep(&local_70,":");
          if (pcVar13 != (char *)0x0) {
            uVar26 = 0;
            do {
              uVar2 = simple_strtol(pcVar13,0,10);
              *(undefined1 *)((int)&local_76 + uVar26) = uVar2;
              pcVar13 = strsep(&local_70,":");
              uVar19 = uVar26 ^ 1;
              uVar26 = 1;
              if (pcVar13 == (char *)0x0) {
                uVar19 = 0;
              }
            } while (uVar19 != 0);
          }
          uVar26 = (uint)(byte)local_76;
          if (uVar26 < *(byte *)(iVar10 + 0x207)) {
            if (*(char *)(iVar10 + 0x210) == '\0') {
              *(undefined1 *)((int)param_1 + uVar26 + 0x794d05) = local_76._1_1_;
            }
            else if (*(char *)(iVar10 + 0x210) == '\x01') {
              *(undefined1 *)((int)param_1 + uVar26 + 0x794d91) = local_76._1_1_;
            }
          }
          else if (-1 < DebugLevel) {
            printk("[PowerUpVHT40] Input parameter incorrect!!\n");
          }
          iVar12 = iVar12 + 1;
          local_70 = (char *)rstrtok(0,&_LC202);
        } while ((local_70 != (char *)0x0) && (iVar12 < (int)(uint)*(byte *)(iVar10 + 0x207)));
      }
    }
    else {
      local_70 = (char *)rstrtok(local_74,&_LC6);
      if ((local_70 == (char *)0x0) ||
         (local_48 = local_70, local_70 = (char *)rstrtok(0,&_LC6), local_70 == (char *)0x0)) {
        if (-1 < DebugLevel) {
          printk("[PowerUpVHT40] Input parameter incorrect!!\n");
        }
      }
      else {
        local_44 = local_70;
        rstrtok(0,&_LC6);
      }
      local_70 = local_48;
      local_70 = (char *)rstrtok(local_48,&_LC202);
      if ((local_70 != (char *)0x0) && (*(char *)(iVar10 + 0x207) != '\0')) {
        iVar12 = 0;
        do {
          pcVar13 = strsep(&local_70,":");
          if (pcVar13 != (char *)0x0) {
            uVar26 = 0;
            do {
              uVar2 = simple_strtol(pcVar13,0,10);
              *(undefined1 *)((int)&local_76 + uVar26) = uVar2;
              pcVar13 = strsep(&local_70,":");
              uVar19 = uVar26 ^ 1;
              uVar26 = 1;
              if (pcVar13 == (char *)0x0) {
                uVar19 = 0;
              }
            } while (uVar19 != 0);
          }
          uVar26 = (uint)(byte)local_76;
          if (uVar26 < *(byte *)(iVar10 + 0x207)) {
            if (*(char *)(iVar10 + 0x210) == '\0') {
              *(undefined1 *)((int)param_1 + uVar26 + 0x794d4a) = local_76._1_1_;
            }
            else if (*(char *)(iVar10 + 0x210) == '\x01') {
              *(undefined1 *)((int)param_1 + uVar26 + 0x794e32) = local_76._1_1_;
            }
          }
          else if (-1 < DebugLevel) {
            printk("[PowerUpVHT40] Input parameter incorrect!!\n");
          }
          iVar12 = iVar12 + 1;
          local_70 = (char *)rstrtok(0,&_LC202);
        } while ((local_70 != (char *)0x0) && (iVar12 < (int)(uint)*(byte *)(iVar10 + 0x207)));
      }
      local_70 = local_44;
      local_70 = (char *)rstrtok(local_44,&_LC202);
      if ((local_70 != (char *)0x0) && (*(char *)(iVar10 + 0x207) != '\0')) {
        iVar12 = 0;
        do {
          pcVar13 = strsep(&local_70,":");
          if (pcVar13 != (char *)0x0) {
            uVar26 = 0;
            do {
              uVar2 = simple_strtol(pcVar13,0,10);
              *(undefined1 *)((int)&local_76 + uVar26) = uVar2;
              pcVar13 = strsep(&local_70,":");
              uVar19 = uVar26 ^ 1;
              uVar26 = 1;
              if (pcVar13 == (char *)0x0) {
                uVar19 = 0;
              }
            } while (uVar19 != 0);
          }
          uVar26 = (uint)(byte)local_76;
          if (uVar26 < *(byte *)(iVar10 + 0x207)) {
            if (*(char *)(iVar10 + 0x210) == '\0') {
              *(undefined1 *)((int)param_1 + uVar26 + 0x794d05) = local_76._1_1_;
            }
            else if (*(char *)(iVar10 + 0x210) == '\x01') {
              *(undefined1 *)((int)param_1 + uVar26 + 0x794d91) = local_76._1_1_;
            }
          }
          else if (-1 < DebugLevel) {
            printk("[PowerUpVHT40] Input parameter incorrect!!\n");
          }
          iVar12 = iVar12 + 1;
          local_70 = (char *)rstrtok(0,&_LC202);
        } while ((local_70 != (char *)0x0) && (iVar12 < (int)(uint)*(byte *)(iVar10 + 0x207)));
      }
    }
  }
  iVar12 = RTMPGetKeyParameter("PowerUpVHT80",local_74,0x20,param_2,1);
  if (iVar12 != 0) {
    if (*(char *)((int)param_1 + 0x79504d) == '\0') {
      local_70 = (char *)rstrtok(local_74,&_LC202);
      if ((local_70 != (char *)0x0) && (*(char *)(iVar10 + 0x208) != '\0')) {
        iVar12 = 0;
        do {
          pcVar13 = strsep(&local_70,":");
          if (pcVar13 != (char *)0x0) {
            uVar26 = 0;
            do {
              uVar2 = simple_strtol(pcVar13,0,10);
              *(undefined1 *)((int)&local_76 + uVar26) = uVar2;
              pcVar13 = strsep(&local_70,":");
              uVar19 = uVar26 ^ 1;
              uVar26 = 1;
              if (pcVar13 == (char *)0x0) {
                uVar19 = 0;
              }
            } while (uVar19 != 0);
          }
          uVar26 = (uint)(byte)local_76;
          if (uVar26 < *(byte *)(iVar10 + 0x208)) {
            if (*(char *)(iVar10 + 0x210) == '\0') {
              *(undefined1 *)((int)param_1 + uVar26 + 0x794d0f) = local_76._1_1_;
            }
            else if (*(char *)(iVar10 + 0x210) == '\x01') {
              *(undefined1 *)((int)param_1 + uVar26 + 0x794d9d) = local_76._1_1_;
            }
          }
          else if (-1 < DebugLevel) {
            printk("[PowerUpVHT80] Input parameter incorrect!!\n");
          }
          iVar12 = iVar12 + 1;
          local_70 = (char *)rstrtok(0,&_LC202);
        } while ((local_70 != (char *)0x0) && (iVar12 < (int)(uint)*(byte *)(iVar10 + 0x208)));
      }
    }
    else {
      local_70 = (char *)rstrtok(local_74,&_LC6);
      if ((local_70 == (char *)0x0) ||
         (local_48 = local_70, local_70 = (char *)rstrtok(0,&_LC6), local_70 == (char *)0x0)) {
        if (-1 < DebugLevel) {
          printk("[PowerUpVHT80] Input parameter incorrect!!\n");
        }
      }
      else {
        local_44 = local_70;
        rstrtok(0,&_LC6);
      }
      local_70 = local_48;
      local_70 = (char *)rstrtok(local_48,&_LC202);
      if ((local_70 != (char *)0x0) && (*(char *)(iVar10 + 0x208) != '\0')) {
        iVar12 = 0;
        do {
          pcVar13 = strsep(&local_70,":");
          if (pcVar13 != (char *)0x0) {
            uVar26 = 0;
            do {
              uVar2 = simple_strtol(pcVar13,0,10);
              *(undefined1 *)((int)&local_76 + uVar26) = uVar2;
              pcVar13 = strsep(&local_70,":");
              uVar19 = uVar26 ^ 1;
              uVar26 = 1;
              if (pcVar13 == (char *)0x0) {
                uVar19 = 0;
              }
            } while (uVar19 != 0);
          }
          uVar26 = (uint)(byte)local_76;
          if (uVar26 < *(byte *)(iVar10 + 0x208)) {
            if (*(char *)(iVar10 + 0x210) == '\0') {
              *(undefined1 *)((int)param_1 + uVar26 + 0x794d54) = local_76._1_1_;
            }
            else if (*(char *)(iVar10 + 0x210) == '\x01') {
              *(undefined1 *)((int)param_1 + uVar26 + 0x794e3e) = local_76._1_1_;
            }
          }
          else if (-1 < DebugLevel) {
            printk("[PowerUpVHT80] Input parameter incorrect!!\n");
          }
          iVar12 = iVar12 + 1;
          local_70 = (char *)rstrtok(0,&_LC202);
        } while ((local_70 != (char *)0x0) && (iVar12 < (int)(uint)*(byte *)(iVar10 + 0x208)));
      }
      local_70 = local_44;
      local_70 = (char *)rstrtok(local_44,&_LC202);
      if ((local_70 != (char *)0x0) && (*(char *)(iVar10 + 0x208) != '\0')) {
        iVar12 = 0;
        do {
          pcVar13 = strsep(&local_70,":");
          if (pcVar13 != (char *)0x0) {
            uVar26 = 0;
            do {
              uVar2 = simple_strtol(pcVar13,0,10);
              *(undefined1 *)((int)&local_76 + uVar26) = uVar2;
              pcVar13 = strsep(&local_70,":");
              uVar19 = uVar26 ^ 1;
              uVar26 = 1;
              if (pcVar13 == (char *)0x0) {
                uVar19 = 0;
              }
            } while (uVar19 != 0);
          }
          uVar26 = (uint)(byte)local_76;
          if (uVar26 < *(byte *)(iVar10 + 0x208)) {
            if (*(char *)(iVar10 + 0x210) == '\0') {
              *(undefined1 *)((int)param_1 + uVar26 + 0x794d0f) = local_76._1_1_;
            }
            else if (*(char *)(iVar10 + 0x210) == '\x01') {
              *(undefined1 *)((int)param_1 + uVar26 + 0x794d9d) = local_76._1_1_;
            }
          }
          else if (-1 < DebugLevel) {
            printk("[PowerUpVHT80] Input parameter incorrect!!\n");
          }
          iVar12 = iVar12 + 1;
          local_70 = (char *)rstrtok(0,&_LC202);
        } while ((local_70 != (char *)0x0) && (iVar12 < (int)(uint)*(byte *)(iVar10 + 0x208)));
      }
    }
  }
  iVar12 = RTMPGetKeyParameter("PowerUpVHT160",local_74,0x20,param_2,1);
  if (iVar12 != 0) {
    if (*(char *)((int)param_1 + 0x79504d) == '\0') {
      local_70 = (char *)rstrtok(local_74,&_LC202);
      if ((local_70 != (char *)0x0) && (*(char *)(iVar10 + 0x209) != '\0')) {
        iVar12 = 0;
        do {
          pcVar13 = strsep(&local_70,":");
          if (pcVar13 != (char *)0x0) {
            uVar26 = 0;
            do {
              uVar2 = simple_strtol(pcVar13,0,10);
              *(undefined1 *)((int)&local_76 + uVar26) = uVar2;
              pcVar13 = strsep(&local_70,":");
              uVar19 = uVar26 ^ 1;
              uVar26 = 1;
              if (pcVar13 == (char *)0x0) {
                uVar19 = 0;
              }
            } while (uVar19 != 0);
          }
          uVar26 = (uint)(byte)local_76;
          if (uVar26 < *(byte *)(iVar10 + 0x209)) {
            if (*(char *)(iVar10 + 0x210) == '\0') {
              *(undefined1 *)((int)param_1 + uVar26 + 0x794d19) = local_76._1_1_;
            }
            else if (*(char *)(iVar10 + 0x210) == '\x01') {
              *(undefined1 *)((int)param_1 + uVar26 + 0x794da9) = local_76._1_1_;
            }
          }
          else if (-1 < DebugLevel) {
            printk("[PowerUpVHT160] Input parameter incorrect!!\n");
          }
          iVar12 = iVar12 + 1;
          local_70 = (char *)rstrtok(0,&_LC202);
        } while ((local_70 != (char *)0x0) && (iVar12 < (int)(uint)*(byte *)(iVar10 + 0x209)));
      }
    }
    else {
      local_70 = (char *)rstrtok(local_74,&_LC6);
      if ((local_70 == (char *)0x0) ||
         (local_48 = local_70, local_70 = (char *)rstrtok(0,&_LC6), local_70 == (char *)0x0)) {
        if (-1 < DebugLevel) {
          printk("[PowerUpVHT160] Input parameter incorrect!!\n");
        }
      }
      else {
        local_44 = local_70;
        rstrtok(0,&_LC6);
      }
      local_70 = local_48;
      local_70 = (char *)rstrtok(local_48,&_LC202);
      if ((local_70 != (char *)0x0) && (*(char *)(iVar10 + 0x209) != '\0')) {
        iVar12 = 0;
        do {
          pcVar13 = strsep(&local_70,":");
          if (pcVar13 != (char *)0x0) {
            uVar26 = 0;
            do {
              uVar2 = simple_strtol(pcVar13,0,10);
              *(undefined1 *)((int)&local_76 + uVar26) = uVar2;
              pcVar13 = strsep(&local_70,":");
              uVar19 = uVar26 ^ 1;
              uVar26 = 1;
              if (pcVar13 == (char *)0x0) {
                uVar19 = 0;
              }
            } while (uVar19 != 0);
          }
          uVar26 = (uint)(byte)local_76;
          if (uVar26 < *(byte *)(iVar10 + 0x209)) {
            if (*(char *)(iVar10 + 0x210) == '\0') {
              *(undefined1 *)((int)param_1 + uVar26 + 0x794d5e) = local_76._1_1_;
            }
            else if (*(char *)(iVar10 + 0x210) == '\x01') {
              *(undefined1 *)((int)param_1 + uVar26 + 0x794e4a) = local_76._1_1_;
            }
          }
          else if (-1 < DebugLevel) {
            printk("[PowerUpVHT160] Input parameter incorrect!!\n");
          }
          iVar12 = iVar12 + 1;
          local_70 = (char *)rstrtok(0,&_LC202);
        } while ((local_70 != (char *)0x0) && (iVar12 < (int)(uint)*(byte *)(iVar10 + 0x209)));
      }
      local_70 = local_44;
      local_70 = (char *)rstrtok(local_44,&_LC202);
      if ((local_70 != (char *)0x0) && (*(char *)(iVar10 + 0x209) != '\0')) {
        iVar12 = 0;
        do {
          pcVar13 = strsep(&local_70,":");
          if (pcVar13 != (char *)0x0) {
            uVar26 = 0;
            do {
              uVar2 = simple_strtol(pcVar13,0,10);
              *(undefined1 *)((int)&local_76 + uVar26) = uVar2;
              pcVar13 = strsep(&local_70,":");
              uVar19 = uVar26 ^ 1;
              uVar26 = 1;
              if (pcVar13 == (char *)0x0) {
                uVar19 = 0;
              }
            } while (uVar19 != 0);
          }
          uVar26 = (uint)(byte)local_76;
          if (uVar26 < *(byte *)(iVar10 + 0x209)) {
            if (*(char *)(iVar10 + 0x210) == '\0') {
              *(undefined1 *)((int)param_1 + uVar26 + 0x794d19) = local_76._1_1_;
            }
            else if (*(char *)(iVar10 + 0x210) == '\x01') {
              *(undefined1 *)((int)param_1 + uVar26 + 0x794da9) = local_76._1_1_;
            }
          }
          else if (-1 < DebugLevel) {
            printk("[PowerUpVHT160] Input parameter incorrect!!\n");
          }
          iVar12 = iVar12 + 1;
          local_70 = (char *)rstrtok(0,&_LC202);
        } while ((local_70 != (char *)0x0) && (iVar12 < (int)(uint)*(byte *)(iVar10 + 0x209)));
      }
    }
  }
  if ((iVar11 != 0) && (*(code **)(iVar11 + 0x204) != (code *)0x0)) {
    (**(code **)(iVar11 + 0x204))(param_1,local_74,param_2);
  }
  iVar11 = RTMPGetKeyParameter("SKUenable",local_74,0x20,param_2,1);
  if (iVar11 != 0) {
    local_70 = (char *)rstrtok(local_74,&_LC6);
    if (local_70 != (char *)0x0) {
      iVar11 = 0;
      do {
        if (*(char *)((int)param_1 + 0x79504d) == '\0') {
          if (iVar11 == 0) {
LAB_000f6b34:
            uVar2 = simple_strtol(local_70,iVar11,10);
            *(undefined1 *)((int)param_1 + 0x794eaa) = uVar2;
          }
        }
        else {
          if (iVar11 == 0) goto LAB_000f6b34;
          if (iVar11 == 1) {
            uVar2 = simple_strtol(local_70,0,10);
            *(undefined1 *)((int)param_1 + 0x794eab) = uVar2;
          }
        }
        iVar11 = iVar11 + 1;
        local_70 = (char *)rstrtok(0,&_LC6);
      } while (local_70 != (char *)0x0);
    }
    if (*(char *)((int)param_1 + 0x79504d) == '\0') {
      if (3 < DebugLevel) {
        printk("[SKUenable] BAND0: %d\n",*(undefined1 *)((int)param_1 + 0x794eaa));
      }
    }
    else if (3 < DebugLevel) {
      printk("[SKUenable] BAND0: %d, BAND1: %d\n",*(undefined1 *)((int)param_1 + 0x794eaa),
             *(undefined1 *)((int)param_1 + 0x794eab));
    }
  }
  iVar11 = RTMPGetKeyParameter("SkuTableIdx",local_74,0x20,param_2,1);
  if (iVar11 != 0) {
    uVar2 = simple_strtol(local_74,0,10);
    iVar11 = DebugLevel;
    *(undefined1 *)(param_1 + 0x1e53ab) = uVar2;
    if (3 < iVar11) {
      printk("[SkuTableIdx]: %d\n",uVar2);
    }
  }
  iVar11 = RTMPGetKeyParameter("CCKTxStream",local_74,0x20,param_2,1);
  if (iVar11 != 0) {
    local_70 = (char *)rstrtok(local_74,&_LC6);
    if (local_70 == (char *)0x0) {
      local_70 = (char *)0x0;
    }
    else {
      iVar11 = 0;
      do {
        if (*(char *)((int)param_1 + 0x79504d) == '\0') {
          if (iVar11 == 0) {
LAB_000f6c04:
            uVar2 = simple_strtol(local_70,iVar11,10);
            *(undefined1 *)((int)param_1 + 0x795039) = uVar2;
          }
        }
        else {
          if (iVar11 == 0) goto LAB_000f6c04;
          if (iVar11 == 1) {
            uVar2 = simple_strtol(local_70,0,10);
            *(undefined1 *)((int)param_1 + 0x79503a) = uVar2;
          }
        }
        iVar11 = iVar11 + 1;
        local_70 = (char *)rstrtok(0,&_LC6);
      } while (local_70 != (char *)0x0);
    }
    if (*(char *)((int)param_1 + 0x79504d) == '\0') {
      if (3 < DebugLevel) {
        printk("[CCKTxStream] BAND0: %d\n",*(undefined1 *)((int)param_1 + 0x795039));
      }
    }
    else if (3 < DebugLevel) {
      printk("[CCKTxStream] BAND0: %d, BAND1: %d\n",*(undefined1 *)((int)param_1 + 0x795039),
             *(undefined1 *)((int)param_1 + 0x79503a));
    }
  }
  iVar11 = RTMPGetKeyParameter("PERCENTAGEenable",local_74,0x20,param_2,1);
  if (iVar11 != 0) {
    local_70 = (char *)rstrtok(local_74,&_LC6);
    if (local_70 == (char *)0x0) {
      local_70 = (char *)0x0;
    }
    else {
      iVar11 = 0;
      do {
        if (*(char *)((int)param_1 + 0x79504d) == '\0') {
          if (iVar11 == 0) {
LAB_000f6e98:
            uVar2 = simple_strtol(local_70,iVar11,10);
            *(undefined1 *)((int)param_1 + 0x795035) = uVar2;
          }
        }
        else {
          if (iVar11 == 0) goto LAB_000f6e98;
          if (iVar11 == 1) {
            uVar2 = simple_strtol(local_70,0,10);
            *(undefined1 *)((int)param_1 + 0x795036) = uVar2;
          }
        }
        iVar11 = iVar11 + 1;
        local_70 = (char *)rstrtok(0,&_LC6);
      } while (local_70 != (char *)0x0);
    }
    if (*(char *)((int)param_1 + 0x79504d) == '\0') {
      if (3 < DebugLevel) {
        printk("[PERCENTAGEenable] BAND0: %d\n",*(undefined1 *)((int)param_1 + 0x795035));
      }
    }
    else if (3 < DebugLevel) {
      printk("[PERCENTAGEenable] BAND0: %d, BAND1: %d\n",*(undefined1 *)((int)param_1 + 0x795035),
             *(undefined1 *)((int)param_1 + 0x795036));
    }
  }
  iVar11 = RTMPGetKeyParameter("BFBACKOFFenable",local_74,0x20,param_2,1);
  if (iVar11 != 0) {
    local_70 = (char *)rstrtok(local_74,&_LC6);
    if (local_70 == (char *)0x0) {
      local_70 = (char *)0x0;
    }
    else {
      iVar11 = 0;
      do {
        if (*(char *)((int)param_1 + 0x79504d) == '\0') {
          if (iVar11 == 0) {
LAB_000f6dc8:
            uVar2 = simple_strtol(local_70,iVar11,10);
            *(undefined1 *)((int)param_1 + 0x795037) = uVar2;
          }
        }
        else {
          if (iVar11 == 0) goto LAB_000f6dc8;
          if (iVar11 == 1) {
            uVar2 = simple_strtol(local_70,0,10);
            *(undefined1 *)(param_1 + 0x1e540e) = uVar2;
          }
        }
        iVar11 = iVar11 + 1;
        local_70 = (char *)rstrtok(0,&_LC6);
      } while (local_70 != (char *)0x0);
    }
    if (*(char *)((int)param_1 + 0x79504d) == '\0') {
      if (3 < DebugLevel) {
        printk("[BFBACKOFFenable] BAND0: %d\n",*(undefined1 *)((int)param_1 + 0x795037));
      }
    }
    else if (3 < DebugLevel) {
      printk("[BFBACKOFFenable] BAND0: %d, BAND1: %d\n",*(undefined1 *)((int)param_1 + 0x795037),
             (char)param_1[0x1e540e]);
    }
  }
  iVar11 = RTMPGetKeyParameter("BGProtection",local_74,10,param_2,1);
  if (iVar11 != 0) {
    iVar11 = os_str_tol(local_74,0,10);
    if ((iVar11 == 1) || (iVar11 == 2)) {
      param_1[0x1e541b] = iVar11;
    }
    else {
      param_1[0x1e541b] = 0;
    }
    if (3 < DebugLevel) {
      printk("BGProtection=%ld\n",param_1[0x1e541b]);
    }
  }
  iVar11 = RTMPGetKeyParameter("DisableOLBC",local_74,10,param_2,1);
  if (iVar11 != 0) {
    iVar11 = os_str_tol(local_74,0,10);
    if ((iVar11 == 0) || (iVar11 == 1)) {
      param_1[0x1e541e] = iVar11;
    }
    else {
      param_1[0x1e541e] = 0;
    }
    if (3 < DebugLevel) {
      printk("OLBCDetection=%ld\n",param_1[0x1e541e]);
    }
  }
  iVar11 = RTMPGetKeyParameter("TxPreamble",local_74,10,param_2,1);
  if (iVar11 != 0) {
    iVar11 = os_str_tol(local_74,0,10);
    if ((iVar11 == 1) || (iVar11 == 2)) {
      param_1[0x1e5419] = iVar11;
    }
    else {
      param_1[0x1e5419] = 0;
    }
    if (3 < DebugLevel) {
      printk("TxPreamble=%ld\n",param_1[0x1e5419]);
    }
  }
  pcVar13 = local_74;
  uVar26 = 0;
  iVar11 = RTMPGetKeyParameter("RTSPktThreshold",local_74,0x80,param_2,0);
  if (iVar11 != 0) {
    iVar11 = rstrtok(pcVar13,&_LC6);
    while (iVar11 != 0) {
      uVar19 = os_str_tol(iVar11,0,10);
      if (0xfe < uVar19 - 1) {
        uVar19 = 0xff;
      }
      if (3 < DebugLevel) {
        printk("profile: RTSPktThreshold[%d]=%d\n",uVar26,uVar19);
      }
      iVar11 = FUN_000ee05c(param_1,uVar26 & 0xff);
      uVar26 = uVar26 + 1;
      if (iVar11 != 0) {
        wlan_config_set_rts_pkt_thld(iVar11,uVar19 & 0xff);
      }
      iVar11 = rstrtok(0,&_LC6);
    }
  }
  pcVar13 = local_74;
  uVar26 = 0;
  iVar11 = RTMPGetKeyParameter("RTSThreshold",local_74,0x80,param_2,0);
  if (iVar11 != 0) {
    if (*(char *)((int)param_1 + 0x79504d) == '\0') {
      iVar11 = os_str_tol(pcVar13,0,10);
      if (0xffffe < iVar11 - 1U) {
        iVar11 = 0xfffff;
      }
      if (*(char *)((int)param_1 + 0x2b7242) != '\0') {
        uVar26 = 0;
        do {
          wlan_config_set_rts_len_thld
                    (param_1 + (uint)(byte)(&DAT_003678c8)[(int)param_1 + uVar26] * 0x160d + 0xadc92
                     ,iVar11);
          if (3 < DebugLevel) {
            printk("mbss[idx=%d], RTSThreshold[%d]=%d\n",uVar26,uVar26,iVar11);
          }
          uVar26 = uVar26 + 1 & 0xff;
        } while (uVar26 < *(byte *)((int)param_1 + 0x2b7242));
      }
    }
    else {
      iVar11 = rstrtok(pcVar13,&_LC6);
      while (iVar11 != 0) {
        iVar11 = os_str_tol(iVar11,0,10);
        if (0xffffe < iVar11 - 1U) {
          iVar11 = 0xfffff;
        }
        if (3 < DebugLevel) {
          printk("profile: RTSThreshold[%d]=%d\n",uVar26,iVar11);
        }
        iVar12 = FUN_000ee05c(param_1,uVar26 & 0xff);
        uVar26 = uVar26 + 1;
        if (iVar12 != 0) {
          wlan_config_set_rts_len_thld(iVar12,iVar11);
        }
        iVar11 = rstrtok(0,&_LC6);
      }
    }
  }
  pcVar13 = local_74;
  uVar26 = 0;
  iVar11 = RTMPGetKeyParameter("FragThreshold",local_74,0x100,param_2,0);
  if (iVar11 != 0) {
    iVar11 = rstrtok(pcVar13,&_LC6);
    while (iVar11 != 0) {
      uVar19 = os_str_tol(iVar11,0,10);
      if (uVar19 - 0x100 < 0x82b) {
        if ((uVar19 & 1) != 0) {
          uVar19 = uVar19 - 1;
        }
      }
      else {
        uVar19 = 0x92a;
      }
      if (3 < DebugLevel) {
        printk("profile: FragThreshold[%d]=%d\n",uVar26,uVar19);
      }
      iVar11 = FUN_000ee05c(param_1,uVar26 & 0xff);
      uVar26 = uVar26 + 1;
      if (iVar11 != 0) {
        wlan_config_set_frag_thld(iVar11,uVar19);
      }
      iVar11 = rstrtok(0,&_LC6);
    }
  }
  iVar11 = RTMPGetKeyParameter("VLANTag",local_74,10,param_2,1);
  if (iVar11 != 0) {
    iVar11 = simple_strtol(local_74,0,10);
    if (3 < DebugLevel) {
      printk("wdev->bVlan_tag = %d\n",iVar11 != 0);
    }
    bVar6 = *(byte *)((int)param_1 + 0x2b7242);
    if (bVar6 != 0) {
      pbVar29 = (byte *)((int)param_1 + 0x3678c7);
      do {
        pbVar29 = pbVar29 + 1;
        *(bool *)(param_1 + (uint)*pbVar29 * 0x160d + 0xaded0) = iVar11 != 0;
      } while (pbVar29 != (byte *)((int)param_1 + bVar6 + 0x3678c7));
    }
    iVar11 = RTMPGetKeyParameter("STAVLANTag",local_74,10,param_2,1);
    if (iVar11 != 0) {
      iVar12 = simple_strtol(local_74,0,10);
      iVar11 = DebugLevel;
      bVar39 = iVar12 != 0;
      *(bool *)(param_1 + 0xdb914) = bVar39;
      if (3 < iVar11) {
        printk("SHAILESH: APCLI%d VlanTag=%d\n",0,bVar39);
      }
      iVar11 = DebugLevel;
      *(bool *)(param_1 + 0x160700) = bVar39;
      if (3 < iVar11) {
        printk("SHAILESH: APCLI%d VlanTag=%d\n",1,bVar39);
      }
    }
  }
  iVar11 = RTMPGetKeyParameter("TxBurst",local_74,10,param_2,1);
  if (iVar11 != 0) {
    iVar12 = os_str_tol(local_74,0,10);
    iVar11 = DebugLevel;
    *(bool *)((int)param_1 + 0x795071) = iVar12 != 0;
    if (3 < iVar11) {
      printk("TxBurst=%d\n",*(undefined1 *)((int)param_1 + 0x795071));
    }
  }
  iVar11 = RTMPGetKeyParameter("PktAggregate",local_74,10,param_2,1);
  if (iVar11 != 0) {
    iVar12 = os_str_tol(local_74,0,10);
    iVar11 = DebugLevel;
    bVar39 = iVar12 != 0;
    *(bool *)((int)param_1 + 0x795072) = bVar39;
    *(bool *)((int)param_1 + 0x795073) = bVar39;
    if (3 < iVar11) {
      printk("PktAggregate=%d\n",bVar39);
    }
  }
  pcVar13 = local_74;
  if (*(char *)((int)param_1 + 0x286285) == '\x01') {
    iVar11 = RTMPGetKeyParameter("WmmCapable",local_74,0x40,param_2,1);
    if (((iVar11 != 0) && (iVar11 = rstrtok(pcVar13,&_LC6), iVar11 != 0)) &&
       (*(char *)((int)param_1 + 0x2b7242) != '\0')) {
      bVar39 = false;
      iVar12 = 0;
      pbVar29 = (byte *)(param_1 + 0xd9e32);
      do {
        iVar11 = os_str_tol(iVar11,0,10);
        if (iVar11 == 0) {
          bVar6 = *pbVar29;
          *(undefined1 *)(param_1 + (uint)bVar6 * 0x160d + 0xadec7) = 0;
          if (bVar39) goto LAB_000fdf60;
          *(undefined1 *)(param_1 + 0x1e5421) = 0;
          if (iVar12 == 0) {
            wlan_config_set_edca_valid_all(param_1 + 0x29f156,0);
          }
          else {
            wlan_config_set_edca_valid
                      ((char *)((int)param_1 +
                               (int)(
                                    "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                    + (uint)bVar6 * 0x5834 + 0xe0)),0);
          }
        }
        else {
          *(undefined1 *)(param_1 + (uint)*pbVar29 * 0x160d + 0xadec7) = 1;
LAB_000fdf60:
          bVar39 = true;
          *(undefined1 *)(param_1 + 0x1e5421) = 1;
          if (iVar12 == 0) {
            wlan_config_set_edca_valid_all(param_1 + 0x29f156,1);
          }
          else {
            wlan_config_set_edca_valid(param_1 + (uint)*pbVar29 * 0x160d + 0xadc92,1);
          }
        }
        iVar11 = DebugLevel;
        bVar6 = *pbVar29;
        *(char *)((int)param_1 + (uint)bVar6 * 0x5834 + 0x2bba7a) =
             (char)param_1[(uint)bVar6 * 0x160d + 0xadec7];
        if (3 < iVar11) {
          printk("I/F(ra%d) WmmCapable=%d\n",iVar12,(char)param_1[(uint)bVar6 * 0x160d + 0xadec7]);
        }
        iVar12 = iVar12 + 1;
        iVar11 = rstrtok(0,&_LC6);
      } while ((iVar11 != 0) &&
              (pbVar29 = pbVar29 + 1, iVar12 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242)));
    }
    local_90 = (undefined1 *)((int)param_1 + 0x79509f);
    iVar11 = 0;
    puVar34 = local_90;
    do {
      snprintf((char *)&local_58,0x10,"APEdca%d",iVar11);
      if (3 < DebugLevel) {
        printk(&_LC253,&local_58);
      }
      iVar12 = RTMPGetKeyParameter(&local_58,pcVar13,0x80,param_2,1);
      if (iVar12 != 0) {
        iVar12 = rstrtok(pcVar13,&_LC6);
        if (iVar12 != 0) {
          iVar16 = 0;
          piVar25 = local_ac;
          do {
            *piVar25 = iVar12;
            iVar12 = rstrtok(0,&_LC6);
            iVar16 = iVar16 + 1;
            piVar25 = piVar25 + 1;
          } while (iVar12 != 0);
          if (iVar16 == 6) {
            if (local_48 != (char *)0x0) {
              uVar2 = os_str_tol(local_48,0,10);
              puVar34[-0x1b] = uVar2;
              if (3 < DebugLevel) {
                printk("Valid=%d\n",uVar2);
              }
            }
            if ((local_44 != (char *)0x0) && (iVar12 = rstrtok(local_44,&_LC120), iVar12 != 0)) {
              puVar33 = puVar34 + -0x15;
              iVar16 = 0;
              do {
                uVar2 = os_str_tol(iVar12,0,10);
                puVar33 = puVar33 + 1;
                *puVar33 = uVar2;
                if (3 < DebugLevel) {
                  printk("APAifsn[%d]=%d\n",iVar16,uVar2);
                }
                iVar16 = iVar16 + 1;
                iVar12 = rstrtok(0,&_LC120);
              } while (iVar12 != 0);
            }
            if ((local_40 != (char *)0x0) && (iVar12 = rstrtok(local_40,&_LC120), iVar12 != 0)) {
              puVar33 = puVar34 + -0x11;
              iVar16 = 0;
              do {
                uVar2 = os_str_tol(iVar12,0,10);
                puVar33 = puVar33 + 1;
                *puVar33 = uVar2;
                if (3 < DebugLevel) {
                  printk("APCwmin[%d]=%d\n",iVar16,uVar2);
                }
                iVar16 = iVar16 + 1;
                iVar12 = rstrtok(0,&_LC120);
              } while (iVar12 != 0);
            }
            if ((local_3c != 0) && (iVar12 = rstrtok(local_3c,&_LC120), iVar12 != 0)) {
              puVar33 = puVar34 + -0xd;
              iVar16 = 0;
              do {
                uVar2 = os_str_tol(iVar12,0,10);
                puVar33 = puVar33 + 1;
                *puVar33 = uVar2;
                if (3 < DebugLevel) {
                  printk("APCwmax[%d]=%d\n",iVar16,uVar2);
                }
                iVar16 = iVar16 + 1;
                iVar12 = rstrtok(0,&_LC120);
              } while (iVar12 != 0);
            }
            if ((local_38 != 0) && (iVar12 = rstrtok(local_38,&_LC120), iVar12 != 0)) {
              puVar38 = (undefined2 *)(puVar34 + -9);
              iVar16 = 0;
              do {
                uVar8 = os_str_tol(iVar12,0,10);
                puVar38 = puVar38 + 1;
                *puVar38 = uVar8;
                if (3 < DebugLevel) {
                  printk("APTxop[%d]=%d\n",iVar16,uVar8);
                }
                iVar16 = iVar16 + 1;
                iVar12 = rstrtok(0,&_LC120);
              } while (iVar12 != 0);
            }
            if ((local_34 != 0) && (iVar12 = rstrtok(local_34,&_LC120), iVar12 != 0)) {
              iVar16 = 0;
              puVar33 = puVar34;
              do {
                uVar2 = os_str_tol(iVar12,0,10);
                puVar33 = puVar33 + 1;
                *puVar33 = uVar2;
                if (3 < DebugLevel) {
                  printk("APACM[%d]=%d\n",iVar16,uVar2);
                }
                iVar16 = iVar16 + 1;
                iVar12 = rstrtok(0,&_LC120);
              } while (iVar12 != 0);
            }
            goto LAB_000fbcc0;
          }
        }
        if (-1 < DebugLevel) {
          printk("Input parameter incorrect\n");
        }
        goto LAB_000fc040;
      }
LAB_000fbcc0:
      iVar11 = iVar11 + 1;
      puVar34 = puVar34 + 0x24;
    } while (iVar11 != 4);
    if (*(char *)((int)param_1 + 0x2b7242) != '\0') {
      iVar11 = 0;
      pbVar29 = (byte *)(param_1 + 0xd9e32);
      do {
        snprintf((char *)&local_58,0x10,"APAckPolicy%d",iVar11);
        iVar12 = RTMPGetKeyParameter(&local_58,pcVar13,0x80,param_2,1);
        if (iVar12 != 0) {
          bVar6 = *pbVar29;
          iVar12 = rstrtok(pcVar13,&_LC6);
          puVar34 = auStack_6c;
          while (iVar12 != 0) {
            uVar2 = simple_strtol(iVar12,0,10);
            *puVar34 = uVar2;
            iVar12 = rstrtok(0,&_LC6);
            puVar34 = puVar34 + 1;
          }
          wlan_config_set_ack_policy(param_1 + (uint)bVar6 * 0x160d + 0xadc92,auStack_6c);
        }
        iVar11 = iVar11 + 1;
        pbVar29 = pbVar29 + 1;
      } while (iVar11 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242));
    }
LAB_000fc040:
    iVar11 = RTMPGetKeyParameter("DLSCapable",pcVar13,0x40,param_2,1);
    if (((iVar11 != 0) && (iVar11 = rstrtok(pcVar13,&_LC6), iVar11 != 0)) &&
       (*(char *)((int)param_1 + 0x2b7242) != '\0')) {
      iVar12 = 0;
      pbVar29 = (byte *)(param_1 + 0xd9e32);
      do {
        iVar16 = os_str_tol(iVar11,0,10);
        iVar11 = DebugLevel;
        if (iVar16 == 0) {
          *(undefined1 *)((int)param_1 + (uint)*pbVar29 * 0x5834 + 0x2bba79) = 0;
          iVar11 = DebugLevel;
        }
        else {
          *(undefined1 *)((int)param_1 + (uint)*pbVar29 * 0x5834 + 0x2bba79) = 1;
        }
        if (3 < iVar11) {
          printk("I/F(ra%d) DLSCapable=%d\n",iVar12,
                 *(undefined1 *)((int)param_1 + (uint)*pbVar29 * 0x5834 + 0x2bba79));
        }
        iVar12 = iVar12 + 1;
        iVar11 = rstrtok(0,&_LC6);
        pbVar29 = pbVar29 + 1;
      } while ((iVar11 != 0) && (iVar12 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242)));
    }
    iVar11 = RTMPGetKeyParameter("APAifsn",pcVar13,0x40,param_2,1);
    if ((iVar11 != 0) && (iVar11 = rstrtok(pcVar13,&_LC6), iVar11 != 0)) {
      iVar12 = 0;
      puVar34 = (undefined1 *)((int)param_1 + 0x79508a);
      do {
        uVar2 = os_str_tol(iVar11,0,10);
        puVar34 = puVar34 + 1;
        *puVar34 = uVar2;
        if (3 < DebugLevel) {
          printk("APAifsn[%d]=%d\n",iVar12,uVar2);
        }
        iVar12 = iVar12 + 1;
        iVar11 = rstrtok(0,&_LC6);
      } while (iVar11 != 0);
    }
    iVar11 = RTMPGetKeyParameter("APCwmin",pcVar13,0x20,param_2,1);
    if ((iVar11 != 0) && (iVar11 = rstrtok(pcVar13,&_LC6), iVar11 != 0)) {
      iVar12 = 0;
      puVar34 = (undefined1 *)((int)param_1 + 0x79508e);
      do {
        uVar2 = os_str_tol(iVar11,0,10);
        puVar34 = puVar34 + 1;
        *puVar34 = uVar2;
        if (3 < DebugLevel) {
          printk("APCwmin[%d]=%d\n",iVar12,uVar2);
        }
        iVar12 = iVar12 + 1;
        iVar11 = rstrtok(0,&_LC6);
      } while (iVar11 != 0);
    }
    iVar11 = RTMPGetKeyParameter("APCwmax",pcVar13,0x20,param_2,1);
    if ((iVar11 != 0) && (iVar11 = rstrtok(pcVar13,&_LC6), iVar11 != 0)) {
      iVar12 = 0;
      puVar34 = (undefined1 *)((int)param_1 + 0x795092);
      do {
        uVar2 = os_str_tol(iVar11,0,10);
        puVar34 = puVar34 + 1;
        *puVar34 = uVar2;
        if (3 < DebugLevel) {
          printk("APCwmax[%d]=%d\n",iVar12,uVar2);
        }
        iVar12 = iVar12 + 1;
        iVar11 = rstrtok(0,&_LC6);
      } while (iVar11 != 0);
    }
    iVar11 = RTMPGetKeyParameter("APTxop",pcVar13,0x20,param_2,1);
    if ((iVar11 != 0) && (iVar11 = rstrtok(pcVar13,&_LC6), iVar11 != 0)) {
      iVar12 = 0;
      puVar38 = (undefined2 *)((int)param_1 + 0x795096);
      do {
        uVar8 = os_str_tol(iVar11,0,10);
        puVar38 = puVar38 + 1;
        *puVar38 = uVar8;
        if (3 < DebugLevel) {
          printk("APTxop[%d]=%d\n",iVar12,uVar8);
        }
        iVar12 = iVar12 + 1;
        iVar11 = rstrtok(0,&_LC6);
      } while (iVar11 != 0);
    }
    iVar11 = RTMPGetKeyParameter("APACM",pcVar13,0x20,param_2,1);
    if ((iVar11 != 0) && (iVar11 = rstrtok(pcVar13,&_LC6), iVar11 != 0)) {
      iVar12 = 0;
      do {
        uVar2 = os_str_tol(iVar11,0,10);
        local_90 = local_90 + 1;
        *local_90 = uVar2;
        if (3 < DebugLevel) {
          printk("APACM[%d]=%d\n",iVar12,uVar2);
        }
        iVar12 = iVar12 + 1;
        iVar11 = rstrtok(0,&_LC6);
      } while (iVar11 != 0);
    }
    if (*(char *)((int)param_1 + 0x2b7242) != '\0') {
      iVar11 = 0;
      pbVar29 = (byte *)((int)param_1 + 0x3678c7);
      do {
        if (3 < DebugLevel) {
          printk("BSS[%d]:\n",iVar11);
        }
        pbVar29 = pbVar29 + 1;
        iVar12 = wlan_config_get_ht_edca(param_1 + (uint)*pbVar29 * 0x160d + 0xadc92);
        if (iVar12 != 0) {
          iVar16 = RTMPGetKeyParameter("BSSAifsn",pcVar13,0x20,param_2,1);
          if ((iVar16 != 0) && (iVar16 = rstrtok(pcVar13,&_LC6), iVar16 != 0)) {
            puVar34 = (undefined1 *)(iVar12 + 6);
            iVar37 = 0;
            do {
              uVar2 = simple_strtol(iVar16,0,10);
              puVar34 = puVar34 + 1;
              *puVar34 = uVar2;
              if (3 < DebugLevel) {
                printk("BSSAifsn[%d]=%d\n",iVar37,uVar2);
              }
              iVar37 = iVar37 + 1;
              iVar16 = rstrtok(0,&_LC6);
            } while (iVar16 != 0);
          }
          iVar16 = RTMPGetKeyParameter("BSSCwmin",pcVar13,0x20,param_2,1);
          if ((iVar16 != 0) && (iVar16 = rstrtok(pcVar13,&_LC6), iVar16 != 0)) {
            puVar34 = (undefined1 *)(iVar12 + 10);
            iVar37 = 0;
            do {
              uVar2 = simple_strtol(iVar16,0,10);
              puVar34 = puVar34 + 1;
              *puVar34 = uVar2;
              if (3 < DebugLevel) {
                printk("BSSCwmin[%d]=%d\n",iVar37,uVar2);
              }
              iVar37 = iVar37 + 1;
              iVar16 = rstrtok(0,&_LC6);
            } while (iVar16 != 0);
          }
          iVar16 = RTMPGetKeyParameter("BSSCwmax",pcVar13,0x20,param_2,1);
          if ((iVar16 != 0) && (iVar16 = rstrtok(pcVar13,&_LC6), iVar16 != 0)) {
            puVar34 = (undefined1 *)(iVar12 + 0xe);
            iVar37 = 0;
            do {
              uVar2 = simple_strtol(iVar16,0,10);
              puVar34 = puVar34 + 1;
              *puVar34 = uVar2;
              if (3 < DebugLevel) {
                printk("BSSCwmax[%d]=%d\n",iVar37,uVar2);
              }
              iVar37 = iVar37 + 1;
              iVar16 = rstrtok(0,&_LC6);
            } while (iVar16 != 0);
          }
          iVar16 = RTMPGetKeyParameter("BSSTxop",pcVar13,0x20,param_2,1);
          if ((iVar16 != 0) && (iVar16 = rstrtok(pcVar13,&_LC6), iVar16 != 0)) {
            puVar38 = (undefined2 *)(iVar12 + 0x12);
            iVar37 = 0;
            do {
              uVar8 = simple_strtol(iVar16,0,10);
              puVar38 = puVar38 + 1;
              *puVar38 = uVar8;
              if (3 < DebugLevel) {
                printk("BSSTxop[%d]=%d\n",iVar37,uVar8);
              }
              iVar37 = iVar37 + 1;
              iVar16 = rstrtok(0,&_LC6);
            } while (iVar16 != 0);
          }
          iVar16 = RTMPGetKeyParameter("BSSACM",pcVar13,0x20,param_2,1);
          if ((iVar16 != 0) && (iVar16 = rstrtok(pcVar13,&_LC6), iVar16 != 0)) {
            puVar34 = (undefined1 *)(iVar12 + 0x1b);
            iVar12 = 0;
            do {
              uVar2 = simple_strtol(iVar16,0,10);
              puVar34 = puVar34 + 1;
              *puVar34 = uVar2;
              if (3 < DebugLevel) {
                printk("BSSACM[%d]=%d\n",iVar12,uVar2);
              }
              iVar12 = iVar12 + 1;
              iVar16 = rstrtok(0,&_LC6);
            } while (iVar16 != 0);
          }
        }
        iVar11 = iVar11 + 1;
      } while (iVar11 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242));
      if (*(byte *)((int)param_1 + 0x2b7242) != 0) {
        pbVar29 = (byte *)(param_1 + 0xd9e32);
        iVar11 = 0;
        do {
          snprintf((char *)&local_58,0x10,"BSSEdca%d",iVar11);
          iVar12 = RTMPGetKeyParameter(&local_58,pcVar13,0x80,param_2,1);
          if (iVar12 != 0) {
            iVar12 = wlan_config_get_ht_edca(param_1 + (uint)*pbVar29 * 0x160d + 0xadc92);
            if (iVar12 == 0) {
              if (-1 < DebugLevel) {
                printk("BSS[%d]: Invalid pBssEdca\n",iVar11);
              }
            }
            else {
              iVar16 = rstrtok(pcVar13,&_LC6);
              if (iVar16 != 0) {
                iVar37 = 0;
                piVar25 = local_ac;
                do {
                  *piVar25 = iVar16;
                  iVar16 = rstrtok(0,&_LC6);
                  iVar37 = iVar37 + 1;
                  piVar25 = piVar25 + 1;
                } while (iVar16 != 0);
                if (iVar37 == 5) {
                  if ((local_48 != (char *)0x0) && (iVar16 = rstrtok(local_48,&_LC120), iVar16 != 0)
                     ) {
                    puVar34 = (undefined1 *)(iVar12 + 6);
                    iVar37 = 0;
                    do {
                      uVar2 = simple_strtol(iVar16,0,10);
                      puVar34 = puVar34 + 1;
                      *puVar34 = uVar2;
                      if (3 < DebugLevel) {
                        printk("BSSAifsn[%d]=%d\n",iVar37,uVar2);
                      }
                      iVar37 = iVar37 + 1;
                      iVar16 = rstrtok(0,&_LC120);
                    } while (iVar16 != 0);
                  }
                  if ((local_44 != (char *)0x0) && (iVar16 = rstrtok(local_44,&_LC120), iVar16 != 0)
                     ) {
                    iVar37 = 0;
                    puVar34 = (undefined1 *)(iVar12 + 10);
                    do {
                      uVar2 = simple_strtol(iVar16,0,10);
                      puVar34 = puVar34 + 1;
                      *puVar34 = uVar2;
                      if (3 < DebugLevel) {
                        printk("BSSCwmin[%d]=%d\n",iVar37,uVar2);
                      }
                      iVar37 = iVar37 + 1;
                      iVar16 = rstrtok(0,&_LC120);
                    } while (iVar16 != 0);
                  }
                  if ((local_40 != (char *)0x0) && (iVar16 = rstrtok(local_40,&_LC120), iVar16 != 0)
                     ) {
                    iVar37 = 0;
                    puVar34 = (undefined1 *)(iVar12 + 0xe);
                    do {
                      uVar2 = simple_strtol(iVar16,0,10);
                      puVar34 = puVar34 + 1;
                      *puVar34 = uVar2;
                      if (3 < DebugLevel) {
                        printk("BSSCwmax[%d]=%d\n",iVar37,uVar2);
                      }
                      iVar37 = iVar37 + 1;
                      iVar16 = rstrtok(0,&_LC120);
                    } while (iVar16 != 0);
                  }
                  if ((local_3c != 0) && (iVar16 = rstrtok(local_3c,&_LC120), iVar16 != 0)) {
                    iVar37 = 0;
                    puVar38 = (undefined2 *)(iVar12 + 0x12);
                    do {
                      uVar8 = simple_strtol(iVar16,0,10);
                      puVar38 = puVar38 + 1;
                      *puVar38 = uVar8;
                      if (3 < DebugLevel) {
                        printk("BSSTxop[%d]=%d\n",iVar37,uVar8);
                      }
                      iVar37 = iVar37 + 1;
                      iVar16 = rstrtok(0,&_LC120);
                    } while (iVar16 != 0);
                  }
                  if ((local_38 != 0) && (iVar16 = rstrtok(local_38,&_LC120), iVar16 != 0)) {
                    iVar37 = 0;
                    puVar34 = (undefined1 *)(iVar12 + 0x1b);
                    do {
                      uVar2 = simple_strtol(iVar16,0,10);
                      puVar34 = puVar34 + 1;
                      *puVar34 = uVar2;
                      if (3 < DebugLevel) {
                        printk("BSSACM[%d]=%d\n",iVar37,uVar2);
                      }
                      iVar37 = iVar37 + 1;
                      iVar16 = rstrtok(0,&_LC120);
                    } while (iVar16 != 0);
                  }
                  goto LAB_000fc64c;
                }
              }
              if (-1 < DebugLevel) {
                printk("Input parameter incorrect\n");
              }
            }
            break;
          }
LAB_000fc64c:
          iVar11 = iVar11 + 1;
          pbVar29 = pbVar29 + 1;
        } while (iVar11 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242));
      }
    }
    iVar11 = RTMPGetKeyParameter("AckPolicy",pcVar13,0x20,param_2,1);
    if (iVar11 != 0) {
      iVar11 = rstrtok(pcVar13,&_LC6);
      if (iVar11 != 0) {
        iVar12 = 0;
        puVar34 = (undefined1 *)((int)param_1 + 0x79511b);
        do {
          uVar2 = os_str_tol(iVar11,0,10);
          puVar34 = puVar34 + 1;
          *puVar34 = uVar2;
          if (3 < DebugLevel) {
            printk("AckPolicy[%d]=%d\n",iVar12,uVar2);
          }
          iVar12 = iVar12 + 1;
          iVar11 = rstrtok(0,&_LC6);
        } while (iVar11 != 0);
      }
      wlan_config_set_ack_policy_all(param_1 + 0x29f156,param_1 + 0x1e5447);
    }
    iVar11 = RTMPGetKeyParameter("APSDCapable",pcVar13,0x40,param_2,1);
    if (iVar11 != 0) {
      iVar11 = rstrtok(pcVar13,&_LC6);
      if (iVar11 != 0) {
        iVar12 = 0;
        pbVar28 = (byte *)(param_1 + 0xd9e32);
        pbVar29 = pbVar28;
        do {
          iVar16 = hc_get_chip_bcn_max_num(param_1[0x29e5e8]);
          if (iVar12 < 0x20 && iVar12 < iVar16) {
            bVar6 = *pbVar29;
            uVar2 = os_str_tol(iVar11,0,10);
            iVar11 = DebugLevel;
            *(undefined1 *)(param_1 + (uint)bVar6 * 0x160d + 0xadec8) = uVar2;
            if (3 < iVar11) {
              printk("APSDCapable[%d]=%d\n",iVar12,(char)param_1[(uint)*pbVar29 * 0x160d + 0xadec8])
              ;
            }
          }
          iVar12 = iVar12 + 1;
          iVar11 = rstrtok(0,&_LC6);
          pbVar29 = pbVar29 + 1;
        } while (iVar11 != 0);
        if (iVar12 == 1) {
          iVar11 = 1;
          while( true ) {
            iVar37 = hc_get_chip_bcn_max_num(param_1[0x29e5e8]);
            iVar16 = DebugLevel;
            bVar39 = SBORROW4(iVar11,0x20);
            iVar12 = iVar11 + -0x20;
            if (iVar11 != 0x20) {
              bVar39 = SBORROW4(iVar11,iVar37);
              iVar12 = iVar11 - iVar37;
            }
            if (iVar12 < 0 == bVar39) break;
            pbVar28 = pbVar28 + 1;
            *(char *)(param_1 + (uint)*pbVar28 * 0x160d + 0xadec8) = (char)param_1[0xadec8];
            if (3 < iVar16) {
              printk("APSDCapable[%d]=%d\n",iVar11);
            }
            iVar11 = iVar11 + 1;
          }
        }
      }
      iVar11 = DebugLevel;
      if (*(char *)((int)param_1 + 0x3678fa) == '\0') {
        *(char *)(param_1 + 0xdb90c) = (char)param_1[0xadec8];
        if (3 < iVar11) {
          printk("default ApCliAPSDCapable[%d]=%d\n");
        }
        iVar11 = DebugLevel;
        *(char *)(param_1 + 0x1606f8) = (char)param_1[0xadec8];
        if (3 < iVar11) {
          printk("default ApCliAPSDCapable[%d]=%d\n",1);
        }
      }
    }
    if (*(char *)((int)param_1 + 0x286285) == '\0') goto LAB_000f4b7c;
LAB_000f4bd0:
    if (*(char *)((int)param_1 + 0x286285) == '\x01') {
      iVar11 = RTMPGetKeyParameter("MbssMaxStaNum",local_74,0x80,param_2,1);
      if (((iVar11 != 0) && (iVar11 = rstrtok(local_74,&_LC6), iVar11 != 0)) &&
         (*(char *)((int)param_1 + 0x2b7242) != '\0')) {
        iVar11 = 0;
        do {
          ApCfg_Set_PerMbssMaxStaNum_Proc(param_1,iVar11);
          iVar12 = rstrtok(0,&_LC6);
          iVar11 = iVar11 + 1;
          if (iVar12 == 0) break;
        } while (iVar11 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242));
      }
      iVar11 = RTMPGetKeyParameter("IdleTimeout",local_74,10,param_2,1);
      if (iVar11 != 0) {
        ApCfg_Set_IdleTimeout_Proc(param_1,local_74);
      }
      iVar11 = RTMPGetKeyParameter("NoForwarding",local_74,0x80,param_2,1);
      if (((iVar11 != 0) && (iVar11 = rstrtok(local_74,&_LC6), iVar11 != 0)) &&
         (*(char *)((int)param_1 + 0x2b7242) != '\0')) {
        pbVar29 = (byte *)(param_1 + 0xd9e32);
        iVar12 = 0;
        do {
          iVar16 = os_str_tol(iVar11,0,10);
          iVar11 = DebugLevel;
          if (iVar16 == 0) {
            param_1[(uint)*pbVar29 * 0x160d + 0xaed9b] = 0;
            iVar11 = DebugLevel;
          }
          else {
            param_1[(uint)*pbVar29 * 0x160d + 0xaed9b] = 1;
          }
          if (3 < iVar11) {
            printk("I/F(ra%d) NoForwarding=%ld\n",iVar12,param_1[(uint)*pbVar29 * 0x160d + 0xaed9b])
            ;
          }
          iVar12 = iVar12 + 1;
          iVar11 = rstrtok(0,&_LC6);
          pbVar29 = pbVar29 + 1;
        } while ((iVar11 != 0) && (iVar12 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242)));
      }
      iVar11 = RTMPGetKeyParameter("NoForwardingBTNBSSID",local_74,10,param_2,1);
      if (iVar11 != 0) {
        iVar11 = os_str_tol(local_74,0,10);
        if (iVar11 == 0) {
          param_1[0xd9e3d] = 0;
        }
        else {
          param_1[0xd9e3d] = 1;
        }
        if (3 < DebugLevel) {
          printk("NoForwardingBTNBSSID=%ld\n",param_1[0xd9e3d]);
        }
      }
      iVar11 = RTMPGetKeyParameter("HideSSID",local_74,0x80,param_2,1);
      if (((iVar11 != 0) && (iVar11 = rstrtok(local_74,&_LC6), iVar11 != 0)) &&
         (*(char *)((int)param_1 + 0x2b7242) != '\0')) {
        iVar12 = 0;
        pbVar29 = (byte *)(param_1 + 0xd9e32);
        do {
          iVar16 = os_str_tol(iVar11,0,10);
          iVar11 = DebugLevel;
          if (iVar16 == 0) {
            *(undefined1 *)((int)param_1 + (uint)*pbVar29 * 0x5834 + 0x2bb2d2) = 0;
            iVar11 = DebugLevel;
          }
          else {
            bVar6 = *pbVar29;
            *(undefined1 *)((int)param_1 + (uint)bVar6 * 0x5834 + 0x2bb2d2) = 1;
            *(undefined1 *)(param_1 + (uint)bVar6 * 0x160d + 0xaec17) = 0;
          }
          if (3 < iVar11) {
            printk("I/F(ra%d) HideSSID=%d\n",iVar12,
                   *(undefined1 *)((int)param_1 + (uint)*pbVar29 * 0x5834 + 0x2bb2d2));
          }
          iVar12 = iVar12 + 1;
          iVar11 = rstrtok(0,&_LC6);
          pbVar29 = pbVar29 + 1;
        } while ((iVar11 != 0) && (iVar12 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242)));
      }
      iVar11 = RTMPGetKeyParameter("StationKeepAlive",local_74,0x80,param_2,1);
      if ((iVar11 != 0) &&
         ((iVar11 = rstrtok(local_74,&_LC6), iVar11 != 0 &&
          (*(char *)((int)param_1 + 0x2b7242) != '\0')))) {
        pbVar29 = (byte *)((int)param_1 + 0x3678c7);
        iVar12 = 0;
        do {
          pbVar29 = pbVar29 + 1;
          bVar6 = *pbVar29;
          uVar8 = os_str_tol(iVar11,0,10);
          iVar11 = DebugLevel;
          *(undefined2 *)(param_1 + (uint)bVar6 * 0x160d + 0xaecb6) = uVar8;
          if (3 < iVar11) {
            printk("I/F(ra%d) StationKeepAliveTime=%d\n",iVar12,
                   (short)param_1[(uint)*pbVar29 * 0x160d + 0xaecb6]);
          }
          iVar12 = iVar12 + 1;
          iVar11 = rstrtok(0,&_LC6);
        } while ((iVar11 != 0) && (iVar12 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242)));
      }
      cVar4 = '\0';
      iVar11 = RTMPGetKeyParameter("AutoChannelSkipList",local_74,0x80,param_2,0);
      pcVar13 = local_74;
      pcVar18 = local_74;
      if (iVar11 != 0) {
        while( true ) {
          pcVar18 = strchr(pcVar18,0x3b);
          if (pcVar18 == (char *)0x0) break;
          cVar4 = cVar4 + '\x01';
          pcVar18 = pcVar18 + 1;
        }
        *(char *)((int)param_1 + 0x36b862) = cVar4 + '\x01';
        iVar11 = rstrtok(pcVar13,&_LC6);
        if ((iVar11 != 0) && (*(char *)((int)param_1 + 0x36b862) != '\0')) {
          puVar34 = (undefined1 *)((int)param_1 + 0x36b862);
          iVar12 = 0;
          do {
            uVar2 = os_str_tol(iVar11,0,10);
            puVar34 = puVar34 + 1;
            *puVar34 = uVar2;
            if (3 < DebugLevel) {
              printk(" AutoChannelSkipList[%d]= %d\n",iVar12,uVar2);
            }
            iVar12 = iVar12 + 1;
            iVar11 = rstrtok(0,&_LC6);
          } while ((iVar11 != 0) && (iVar12 < (int)(uint)*(byte *)((int)param_1 + 0x36b862)));
        }
      }
      iVar11 = RTMPGetKeyParameter("DfsZeroWait",local_74,0x32,param_2,0);
      if (iVar11 != 0) {
        cVar4 = os_str_tol(local_74,0,10);
        if ((cVar4 == '\x01') && (*(char *)((int)param_1 + 0x7953ef) == '\x01')) {
          *(undefined1 *)((int)param_1 + 0xa79631) = 1;
          *(undefined1 *)((int)param_1 + 0x7953f6) = 1;
        }
        else {
          *(undefined1 *)((int)param_1 + 0xa79631) = 0;
          *(undefined1 *)((int)param_1 + 0x7953f6) = 0;
        }
        if (3 < DebugLevel) {
          printk("DfsZeroWait Support=%d/%d\n",cVar4,*(undefined1 *)((int)param_1 + 0xa79631));
        }
      }
      iVar11 = RTMPGetKeyParameter("DfsDedicatedZeroWait",local_74,0x19,param_2,1);
      if (iVar11 != 0) {
        cVar4 = simple_strtol(local_74,0,10);
        if (cVar4 == '\x01') {
          *(undefined1 *)((int)param_1 + 0x7953fa) = 1;
          *(undefined1 *)(param_1 + 0x1e5501) = 0;
        }
        else if (cVar4 == '\x02') {
          *(undefined1 *)((int)param_1 + 0x7953fa) = 1;
          *(undefined1 *)(param_1 + 0x1e5501) = 1;
        }
        else if (cVar4 == '\0') {
          *(undefined1 *)((int)param_1 + 0x7953fa) = 0;
          *(undefined1 *)(param_1 + 0x1e5501) = 0;
        }
        else {
          *(undefined1 *)((int)param_1 + 0x7953fa) = 0;
          *(undefined1 *)(param_1 + 0x1e5501) = 0;
        }
      }
      iVar11 = RTMPGetKeyParameter("DfsZeroWaitDefault",local_74,0x19,param_2,1);
      if (iVar11 != 0) {
        uVar2 = simple_strtol(local_74,0,10);
        *(undefined1 *)(param_1 + 0x1e5501) = uVar2;
      }
      iVar11 = RTMPGetKeyParameter("VHT_BW",local_74,0x40,param_2,1);
      pcVar13 = local_74;
      if (iVar11 != 0) {
        do {
          iVar11 = rstrtok(pcVar13,&_LC6);
          if (iVar11 == 0) goto LAB_000f4e4c;
          iVar11 = os_str_tol(iVar11,0,10);
          pcVar13 = (char *)0x0;
        } while (iVar11 != 3);
        *(undefined1 *)((int)param_1 + 0x7953fa) = 0;
        *(undefined1 *)(param_1 + 0x1e5501) = 0;
      }
LAB_000f4e4c:
      cVar4 = '\0';
      iVar11 = RTMPGetKeyParameter("BgndScanSkipCh",local_74,0x32,param_2,0);
      pcVar13 = local_74;
      pcVar18 = local_74;
      if (iVar11 != 0) {
        while( true ) {
          pcVar18 = strchr(pcVar18,0x3b);
          if (pcVar18 == (char *)0x0) break;
          cVar4 = cVar4 + '\x01';
          pcVar18 = pcVar18 + 1;
        }
        *(char *)((int)param_1 + 0xa79755) = cVar4 + '\x01';
        iVar11 = rstrtok(pcVar13,&_LC6);
        if ((iVar11 != 0) && (*(char *)((int)param_1 + 0xa79755) != '\0')) {
          puVar34 = (undefined1 *)((int)param_1 + 0xa79755);
          iVar12 = 0;
          do {
            uVar2 = os_str_tol(iVar11,0,10);
            puVar34 = puVar34 + 1;
            *puVar34 = uVar2;
            if (3 < DebugLevel) {
              printk(" Background Skip Channel list[%d]= %d\n",iVar12,uVar2);
            }
            iVar12 = iVar12 + 1;
            iVar11 = rstrtok(0,&_LC6);
          } while ((iVar11 != 0) && (iVar12 < (int)(uint)*(byte *)((int)param_1 + 0xa79755)));
        }
      }
      uVar26 = 0;
      iVar11 = RTMPGetKeyParameter("EDCCAEnable",local_74,10,param_2,0);
      if ((iVar11 != 0) && (iVar11 = rstrtok(local_74,&_LC6), iVar11 != 0)) {
        puVar34 = (undefined1 *)((int)param_1 + 0x79503a);
        do {
          uVar2 = simple_strtol(iVar11,0,10);
          puVar34 = puVar34 + 1;
          *puVar34 = uVar2;
          if (3 < DebugLevel) {
            printk(" EDCCA band[%d]= %d\n",uVar26,uVar2);
          }
          iVar11 = rstrtok(0,&_LC6);
          uVar19 = uVar26 ^ 1;
          uVar26 = 1;
          if (iVar11 == 0) {
            uVar19 = 0;
          }
        } while (uVar19 != 0);
      }
      iVar11 = RTMPGetKeyParameter("DfsZeroWaitCacTime",local_74,0x32,param_2,0);
      if (iVar11 != 0) {
        uVar2 = os_str_tol(local_74,0,10);
        *(undefined1 *)(param_1 + 0x1e54fe) = uVar2;
        if (3 < DebugLevel) {
          printk("DfsZeroWaitCacTime=%d/%d\n",uVar2,uVar2);
        }
      }
      iVar11 = RTMPGetKeyParameter("ACSCheckTime",local_74,0x20,param_2,1);
      if (iVar11 != 0) {
        iVar11 = rstrtok(local_74,&_LC6);
        if (iVar11 != 0) {
          puVar22 = (uint *)(param_1 + 0xdae12);
          bVar39 = false;
          do {
            uVar26 = simple_strtol(iVar11,0,10);
            if (param_1[0x1e5414] == 2) {
              *puVar22 = uVar26 & 0xff;
            }
            else {
              uVar26 = uVar26 & 0xff;
              if ((*(ushort *)(param_1 + 0xadc98) & 0xb1) == 0) {
                *puVar22 = uVar26;
              }
              else if ((bVar39) || (*(char *)((int)param_1 + 0x79504d) != '\x01')) {
                param_1[0xdae12] = uVar26;
              }
              else {
                param_1[0xdae13] = uVar26;
              }
            }
            puVar22 = puVar22 + 1;
            iVar11 = rstrtok(0,&_LC6);
            bVar40 = bVar39;
            if (iVar11 == 0) {
              bVar40 = true;
            }
            bVar39 = true;
          } while (!bVar40);
        }
        if ((3 < DebugLevel) &&
           (printk("%s(): ACSCheckTime[%d]=%u seconds\n","RTMPSetProfileParameters",0,
                   param_1[0xdae12]), 3 < DebugLevel)) {
          printk("%s(): ACSCheckTime[%d]=%u seconds\n","RTMPSetProfileParameters",1,param_1[0xdae13]
                );
        }
      }
    }
  }
  else if (*(char *)((int)param_1 + 0x286285) == '\0') {
LAB_000f4b7c:
    pcVar13 = local_74;
    iVar11 = RTMPGetKeyParameter("WmmCapable",local_74,0x40,param_2,1);
    if ((iVar11 == 0) || (iVar11 = rstrtok(pcVar13,&_LC6), iVar11 == 0)) {
      iVar11 = RTMPGetKeyParameter("AckPolicy",pcVar13,0x20,param_2,1);
      if (iVar11 == 0) goto LAB_000f4bd0;
      bVar39 = false;
LAB_000fa7e0:
      iVar11 = rstrtok(pcVar13,&_LC6);
      if (iVar11 != 0) {
        puVar34 = (undefined1 *)((int)param_1 + 0x79511b);
        iVar12 = 0;
        do {
          uVar2 = os_str_tol(iVar11,0,10);
          puVar34 = puVar34 + 1;
          *puVar34 = uVar2;
          if (3 < DebugLevel) {
            printk("AckPolicy[%d]=%d\n",iVar12,uVar2);
          }
          iVar12 = iVar12 + 1;
          iVar11 = rstrtok(0,&_LC6);
        } while (iVar11 != 0);
      }
      wlan_config_set_ack_policy_all(param_1 + 0x29f156,param_1 + 0x1e5447);
    }
    else {
      bVar39 = false;
      piVar25 = param_1 + 0xdb90b;
      iVar12 = 0;
      do {
        iVar11 = os_str_tol(iVar11,0,10);
        if (iVar11 == 0) {
          *(undefined1 *)piVar25 = 0;
        }
        else {
          *(undefined1 *)piVar25 = 1;
          bVar39 = true;
        }
        bVar40 = iVar12 == 0;
        iVar12 = iVar12 + 1;
        if (bVar40) {
          *(char *)(param_1 + 0x1606f7) = (char)param_1[0xdb90b];
        }
        if (3 < DebugLevel) {
          printk("WmmCapable=%d\n",(char)*piVar25);
        }
        iVar11 = rstrtok(0,&_LC6);
        piVar25 = piVar25 + 0x84dec;
      } while (iVar11 != 0);
      iVar11 = RTMPGetKeyParameter("AckPolicy",pcVar13,0x20,param_2,1);
      if (iVar11 != 0) goto LAB_000fa7e0;
    }
    if (bVar39) {
      iVar11 = RTMPGetKeyParameter("APSDCapable",pcVar13,10,param_2,1);
      if ((iVar11 != 0) && (iVar11 = rstrtok(pcVar13,&_LC6), iVar11 != 0)) {
        piVar25 = param_1 + 0xdb90c;
        iVar11 = 0;
        do {
          iVar12 = os_str_tol(pcVar13,0,10);
          if (iVar12 == 0) {
            *(undefined1 *)piVar25 = 0;
          }
          else {
            *(undefined1 *)piVar25 = 1;
          }
          bVar39 = iVar11 == 0;
          iVar11 = iVar11 + 1;
          if (bVar39) {
            *(char *)(param_1 + 0x1606f8) = (char)param_1[0xdb90c];
          }
          if (3 < DebugLevel) {
            printk("APSDCapable=%d\n",(char)*piVar25);
          }
          iVar12 = rstrtok(0,&_LC6);
          piVar25 = piVar25 + 0x84dec;
        } while (iVar12 != 0);
      }
      iVar11 = RTMPGetKeyParameter("MaxSPLength",pcVar13,10,param_2,1);
      if (iVar11 != 0) {
        uVar2 = os_str_tol(pcVar13,0,10);
        iVar11 = DebugLevel;
        *(undefined1 *)(param_1 + 0x1e5331) = uVar2;
        if (3 < iVar11) {
          printk("MaxSPLength=%d\n",uVar2);
        }
      }
      iVar11 = RTMPGetKeyParameter("APSDAC",pcVar13,0x20,param_2,1);
      if (iVar11 != 0) {
        iVar11 = 0;
        local_48 = (char *)0x0;
        iVar12 = rstrtok(pcVar13,&_LC6);
        piVar25 = local_ac;
        pcVar13 = local_48;
        while (local_48 = pcVar13, iVar12 != 0) {
          uVar2 = os_str_tol(iVar12,0,10);
          *(undefined1 *)piVar25 = uVar2;
          if (3 < DebugLevel) {
            printk("APSDAC%d  %d\n",iVar11,uVar2);
          }
          iVar11 = iVar11 + 1;
          iVar12 = rstrtok(0,&_LC6);
          piVar25 = (int *)((int)piVar25 + 1);
          pcVar13 = local_48;
        }
        local_48._0_1_ = SUB41(pcVar13,0);
        local_48._1_1_ = (undefined1)((uint)pcVar13 >> 8);
        local_48._2_1_ = (undefined1)((uint)pcVar13 >> 0x10);
        local_48._3_1_ = (undefined1)((uint)pcVar13 >> 0x18);
        *(undefined1 *)((int)param_1 + 0x794ca7) = (undefined1)local_48;
        *(undefined1 *)(param_1 + 0x1e5330) = (undefined1)local_48;
        *(undefined1 *)(param_1 + 0x1e532a) = local_48._1_1_;
        *(undefined1 *)((int)param_1 + 0x794cc1) = local_48._1_1_;
        *(undefined1 *)((int)param_1 + 0x794ca9) = local_48._2_1_;
        *(undefined1 *)((int)param_1 + 0x794cc2) = local_48._2_1_;
        *(undefined1 *)((int)param_1 + 0x794caa) = local_48._3_1_;
        *(undefined1 *)((int)param_1 + 0x794cc3) = local_48._3_1_;
      }
    }
    goto LAB_000f4bd0;
  }
  iVar11 = RTMPGetKeyParameter("ShortSlot",local_74,10,param_2,1);
  if ((iVar11 != 0) && (RT_CfgSetShortSlot(param_1,local_74), 3 < DebugLevel)) {
    printk("ShortSlot=%d\n",(char)param_1[0x1e541c]);
  }
  pcVar13 = local_74;
  if (*(char *)(iVar10 + 0x96) != '\0') {
    piVar25 = (int *)0x0;
    iVar10 = RTMPGetKeyParameter("ITxBfEn",local_74,0x80,param_2,0);
    if (iVar10 != 0) {
      *(byte *)((int)param_1 + 0x794ccd) = *(byte *)((int)param_1 + 0x794ccd) & 0xfb;
      iVar10 = rstrtok(pcVar13,&_LC6);
      if (iVar10 == 0) {
        iVar11 = 0;
        uVar26 = 0;
      }
      else {
        iVar11 = 0;
        pbVar29 = (byte *)(param_1 + 0xd9e32);
        do {
          uVar19 = os_str_tol(iVar10,0,10);
          uVar26 = uVar19 & 0xff;
          *(byte *)((int)param_1 + 0x794ccd) =
               *(byte *)((int)param_1 + 0x794ccd) & 0xfb |
               (byte)((uVar19 & 1 | ((uint)*(byte *)((int)param_1 + 0x794ccd) << 0x1d) >> 0x1f) << 2
                     );
          if (3 < DebugLevel) {
            printk("%s: ITxBfEn = %d\n","read_itxbf",uVar26);
          }
          if ((*(char *)((int)param_1 + 0x286285) == '\x01') &&
             (iVar11 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242))) {
            if (3 < DebugLevel) {
              printk("%s: BSSID[%d]\n","read_itxbf",iVar11);
            }
            piVar25 = param_1 + (uint)*pbVar29 * 0x160d + 0xadc92;
          }
          if ((piVar25 != (int *)0x0) && (wlan_config_set_itxbf(piVar25,uVar26), 3 < DebugLevel)) {
            printk("%s: MBSS[%d] ITxBfEn = %d\n","read_itxbf",iVar11,uVar26);
          }
          iVar11 = iVar11 + 1;
          iVar10 = rstrtok(0,&_LC6);
          pbVar29 = pbVar29 + 1;
        } while (iVar10 != 0);
      }
      if ((*(char *)((int)param_1 + 0x286285) == '\x01') &&
         (iVar11 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242))) {
        pbVar29 = (byte *)((int)param_1 + iVar11 + 0x3678c7);
        do {
          if (-1 < DebugLevel) {
            printk("%s: More BSSID[%d]\n","read_itxbf",iVar11);
          }
          pbVar29 = pbVar29 + 1;
          if ((param_1 + (uint)*pbVar29 * 0x160d + 0xadc92 != (int *)0x0) &&
             (wlan_config_set_itxbf(param_1 + (uint)*pbVar29 * 0x160d + 0xadc92,uVar26),
             3 < DebugLevel)) {
            printk("%s: More MBSS[%d] ITxBfEn = %d\n","read_itxbf",iVar11,uVar26);
          }
          iVar11 = iVar11 + 1;
        } while (iVar11 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242));
      }
    }
    if (-1 < DebugLevel) {
      printk("%s: Common.ITxBfEn = %d\n","read_itxbf",
             ((uint)*(byte *)((int)param_1 + 0x794ccd) << 0x1d) >> 0x1f);
    }
    piVar25 = (int *)0x0;
    iVar10 = RTMPGetKeyParameter("ETxBfEnCond",pcVar13,0x80,param_2,0);
    if (iVar10 != 0) {
      param_1[0x1e5667] = 0;
      iVar10 = rstrtok(pcVar13,&_LC6);
      if (iVar10 == 0) {
        iVar11 = 0;
        uVar26 = 0;
      }
      else {
        piVar36 = param_1 + 0xdb6d6;
        pbVar29 = (byte *)(param_1 + 0xd9e32);
        iVar11 = 0;
        do {
          uVar26 = os_str_tol(iVar10,0,10);
          iVar10 = DebugLevel;
          uVar26 = uVar26 & 0xff;
          param_1[0x1e5667] = uVar26 | param_1[0x1e5667];
          if (3 < iVar10) {
            printk("%s: ETxBfEnCond = %d\n","read_etxbf",uVar26);
          }
          if (*(char *)((int)param_1 + 0x286285) == '\x01') {
            if (iVar11 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242)) {
              if (3 < DebugLevel) {
                printk("%s: BSSID[%d]\n","read_etxbf",iVar11);
              }
              piVar25 = param_1 + (uint)*pbVar29 * 0x160d + 0xadc92;
              goto LAB_000fccec;
            }
          }
          else {
LAB_000fccec:
            bVar39 = iVar11 == 1;
            if (iVar11 < 2) {
              bVar39 = *(char *)((int)param_1 + 0x286285) == '\0';
            }
            if ((bVar39) && (piVar25 = piVar36, 3 < DebugLevel)) {
              printk("%s: STA[%d]\n","read_etxbf",iVar11);
            }
          }
          if ((piVar25 != (int *)0x0) && (wlan_config_set_etxbf(piVar25,uVar26), 3 < DebugLevel)) {
            printk("%s: MBSS[%d] ETxBfEnCond = %d\n","read_etxbf",iVar11,uVar26);
          }
          iVar10 = rstrtok(0,&_LC6);
          piVar36 = piVar36 + 0x84dec;
          iVar11 = iVar11 + 1;
          pbVar29 = pbVar29 + 1;
        } while (iVar10 != 0);
      }
      if (*(char *)((int)param_1 + 0x286285) == '\x01') {
        if ((int)(uint)*(byte *)((int)param_1 + 0x2b7242) <= iVar11) goto LAB_000f7408;
        pbVar29 = (byte *)((int)param_1 + iVar11 + 0x3678c7);
        do {
          if (3 < DebugLevel) {
            printk("%s: More BSSID[%d]\n","read_etxbf",iVar11);
          }
          pbVar29 = pbVar29 + 1;
          if ((param_1 + (uint)*pbVar29 * 0x160d + 0xadc92 != (int *)0x0) &&
             (wlan_config_set_etxbf(param_1 + (uint)*pbVar29 * 0x160d + 0xadc92,uVar26),
             3 < DebugLevel)) {
            printk("%s: More MBSS[%d] ETxBfEnCond = %d\n","read_etxbf",iVar11,uVar26);
          }
          iVar11 = iVar11 + 1;
        } while (iVar11 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242));
      }
      if ((*(char *)((int)param_1 + 0x286285) == '\0') && (iVar11 < 2)) {
        piVar25 = param_1 + iVar11 * 0x84dec + 0xdb6d6;
        do {
          if (3 < DebugLevel) {
            printk("%s: More STA[%d]\n","read_etxbf",iVar11);
          }
          if ((piVar25 != (int *)0x0) && (wlan_config_set_etxbf(piVar25,uVar26), 3 < DebugLevel)) {
            printk("%s: More MBSS[%d] ETxBfEnCond = %d\n","read_etxbf",iVar11,uVar26);
          }
          iVar11 = iVar11 + 1;
          piVar25 = piVar25 + 0x84dec;
        } while (iVar11 != 2);
      }
    }
LAB_000f7408:
    iVar10 = RTMPGetKeyParameter("BfSmthIntlBbypass",pcVar13,0x80,param_2,0);
    if ((iVar10 != 0) && (iVar10 = rstrtok(pcVar13,&_LC6), iVar10 != 0)) {
      puVar34 = (undefined1 *)((int)param_1 + 0x7959a6);
      iVar11 = 0;
      do {
        uVar2 = os_str_tol(iVar10,0,10);
        puVar34 = puVar34 + 1;
        *puVar34 = uVar2;
        if (-1 < DebugLevel) {
          printk("BfSmthIntlBbypass[%d] = %d\n",iVar11,uVar2);
        }
        iVar10 = rstrtok(0,&_LC6);
        if (iVar10 == 0) {
          iVar11 = 1;
        }
        bVar39 = iVar11 == 0;
        iVar11 = 1;
      } while (bVar39);
    }
    iVar10 = RTMPGetKeyParameter("ITxBfTimeout",local_74,0x20,param_2,1);
    if (iVar10 != 0) {
      iVar11 = os_str_tol(local_74,0,10);
      iVar10 = DebugLevel;
      param_1[0x1e5665] = iVar11;
      if (3 < iVar10) {
        printk("ITxBfTimeout = %ld\n",iVar11);
      }
    }
    iVar10 = RTMPGetKeyParameter("ETxBfEnCond",local_74,0x80,param_2,1);
    if (iVar10 != 0) {
      if (3 < DebugLevel) {
        printk("CommnCfg.ETxBfEnCond = %ld\n",param_1[0x1e5667]);
      }
      if (param_1[0x1e5667] == 0) {
        *(byte *)((int)param_1 + 0x794ccd) = *(byte *)((int)param_1 + 0x794ccd) & 0xf7;
      }
      else {
        *(byte *)((int)param_1 + 0x794ccd) = *(byte *)((int)param_1 + 0x794ccd) | 8;
      }
      iVar10 = RTMPGetKeyParameter("MUTxRxEnable",local_74,0x20,param_2,1);
      if (iVar10 != 0) {
        iVar11 = os_str_tol(local_74,0,10);
        iVar10 = DebugLevel;
        param_1[0x1e5668] = iVar11;
        if (3 < iVar10) {
          printk("MUTxRxEnable = %ld\n",iVar11);
        }
      }
    }
    iVar10 = RTMPGetKeyParameter("MuEnable7615HwPatch",local_74,10,param_2,1);
    if (iVar10 != 0) {
      uVar2 = simple_strtol(local_74,0,10);
      *(undefined1 *)((int)param_1 + 0x285a1f) = uVar2;
    }
    iVar10 = RTMPGetKeyParameter("ETxBfTimeout",local_74,0x20,param_2,1);
    if (iVar10 != 0) {
      iVar11 = os_str_tol(local_74,0,10);
      iVar10 = DebugLevel;
      param_1[0x1e5666] = iVar11;
      if (3 < iVar10) {
        printk("ETxBfTimeout = %ld\n",iVar11);
      }
    }
    iVar10 = RTMPGetKeyParameter("ETxBfNoncompress",local_74,0x20,param_2,1);
    if (iVar10 != 0) {
      uVar2 = os_str_tol(local_74,0,10);
      iVar10 = DebugLevel;
      *(undefined1 *)(param_1 + 0x1e5669) = uVar2;
      if (3 < iVar10) {
        printk("ETxBfNoncompress = %d\n",uVar2);
      }
    }
    iVar10 = RTMPGetKeyParameter("ETxBfIncapable",local_74,0x20,param_2,1);
    if (iVar10 != 0) {
      uVar2 = os_str_tol(local_74,0,10);
      iVar10 = DebugLevel;
      *(undefined1 *)((int)param_1 + 0x7959a5) = uVar2;
      if (3 < iVar10) {
        printk("ETxBfIncapable = %d\n",uVar2);
      }
    }
  }
  pcVar13 = local_74;
  iVar10 = hc_get_chip_cap(param_1[0x29e5e8]);
  uVar26 = *(uint *)(iVar10 + 0x2c);
  if ((uVar26 & 0x200000) != 0) {
    piVar25 = (int *)0x0;
    iVar10 = RTMPGetKeyParameter("MuOfdmaDlEnable",pcVar13,0x80,param_2,0);
    if (iVar10 != 0) {
      iVar10 = rstrtok(pcVar13,&_LC6);
      if (iVar10 == 0) {
        iVar11 = 0;
        uVar2 = 0;
      }
      else {
        piVar36 = param_1 + 0xdb6d6;
        pbVar29 = (byte *)(param_1 + 0xd9e32);
        iVar11 = 0;
        do {
          uVar2 = os_str_tol(iVar10,0,10);
          if (*(char *)((int)param_1 + 0x286285) == '\x01') {
            if (iVar11 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242)) {
              piVar25 = param_1 + (uint)*pbVar29 * 0x160d + 0xadc92;
            }
          }
          else {
            bVar39 = iVar11 == 1;
            if (iVar11 < 2) {
              bVar39 = *(char *)((int)param_1 + 0x286285) == '\0';
            }
            if (bVar39) {
              piVar25 = piVar36;
            }
          }
          pbVar29 = pbVar29 + 1;
          if ((piVar25 != (int *)0x0) &&
             (wlan_config_set_mu_dl_ofdma(piVar25,uVar2), 3 < DebugLevel)) {
            printk("MBSS[%d] MuOfdmaDlEnable = %d\n",iVar11,uVar2);
          }
          iVar11 = iVar11 + 1;
          iVar10 = rstrtok(0,&_LC6);
          piVar36 = piVar36 + 0x84dec;
        } while (iVar10 != 0);
      }
      if (*(char *)((int)param_1 + 0x286285) == '\x01') {
        if ((int)(uint)*(byte *)((int)param_1 + 0x2b7242) <= iVar11) goto LAB_000f3b88;
        pbVar29 = (byte *)((int)param_1 + iVar11 + 0x3678c7);
        do {
          pbVar29 = pbVar29 + 1;
          if ((param_1 + (uint)*pbVar29 * 0x160d + 0xadc92 != (int *)0x0) &&
             (wlan_config_set_mu_dl_ofdma(param_1 + (uint)*pbVar29 * 0x160d + 0xadc92,uVar2),
             3 < DebugLevel)) {
            printk("More MBSS[%d] MuOfdmaDlEnable = %d\n",iVar11,uVar2);
          }
          iVar11 = iVar11 + 1;
        } while (iVar11 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242));
      }
      if ((*(char *)((int)param_1 + 0x286285) == '\0') && (iVar11 < 2)) {
        piVar25 = param_1 + iVar11 * 0x84dec + 0xdb6d6;
        do {
          if ((piVar25 != (int *)0x0) &&
             (wlan_config_set_mu_dl_ofdma(piVar25,uVar2), -1 < DebugLevel)) {
            printk("More MBSS[%d] MuOfdmaDlEnable = %d\n",iVar11,uVar2);
          }
          bVar39 = iVar11 != 1;
          piVar25 = piVar25 + 0x84dec;
          iVar11 = 1;
        } while (bVar39);
      }
    }
  }
LAB_000f3b88:
  if ((uVar26 & 0x10000) != 0) {
    piVar25 = (int *)0x0;
    iVar10 = RTMPGetKeyParameter("MuOfdmaUlEnable",pcVar13,0x80,param_2,0);
    if (iVar10 != 0) {
      iVar10 = rstrtok(pcVar13,&_LC6);
      if (iVar10 == 0) {
        iVar11 = 0;
        uVar2 = 0;
      }
      else {
        piVar36 = param_1 + 0xdb6d6;
        pbVar29 = (byte *)(param_1 + 0xd9e32);
        iVar11 = 0;
        do {
          uVar2 = os_str_tol(iVar10,0,10);
          if (*(char *)((int)param_1 + 0x286285) == '\x01') {
            if (iVar11 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242)) {
              piVar25 = param_1 + (uint)*pbVar29 * 0x160d + 0xadc92;
            }
          }
          else {
            bVar39 = iVar11 == 1;
            if (iVar11 < 2) {
              bVar39 = *(char *)((int)param_1 + 0x286285) == '\0';
            }
            if (bVar39) {
              piVar25 = piVar36;
            }
          }
          pbVar29 = pbVar29 + 1;
          if ((piVar25 != (int *)0x0) &&
             (wlan_config_set_mu_ul_ofdma(piVar25,uVar2), 3 < DebugLevel)) {
            printk("MBSS[%d] MuOfdmaUlEnable = %d\n",iVar11,uVar2);
          }
          iVar11 = iVar11 + 1;
          iVar10 = rstrtok(0,&_LC6);
          piVar36 = piVar36 + 0x84dec;
        } while (iVar10 != 0);
      }
      if (*(char *)((int)param_1 + 0x286285) == '\x01') {
        if ((int)(uint)*(byte *)((int)param_1 + 0x2b7242) <= iVar11) goto LAB_000f3b90;
        pbVar29 = (byte *)((int)param_1 + iVar11 + 0x3678c7);
        do {
          pbVar29 = pbVar29 + 1;
          if ((param_1 + (uint)*pbVar29 * 0x160d + 0xadc92 != (int *)0x0) &&
             (wlan_config_set_mu_ul_ofdma(param_1 + (uint)*pbVar29 * 0x160d + 0xadc92,uVar2),
             3 < DebugLevel)) {
            printk("More MBSS[%d] MuOfdmaUlEnable = %d\n",iVar11,uVar2);
          }
          iVar11 = iVar11 + 1;
        } while (iVar11 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242));
      }
      if ((*(char *)((int)param_1 + 0x286285) == '\0') && (iVar11 < 2)) {
        piVar25 = param_1 + iVar11 * 0x84dec + 0xdb6d6;
        do {
          if ((piVar25 != (int *)0x0) &&
             (wlan_config_set_mu_ul_ofdma(piVar25,uVar2), -1 < DebugLevel)) {
            printk("More MBSS[%d] MuOfdmaUlEnable = %d\n",iVar11,uVar2);
          }
          bVar39 = iVar11 != 1;
          piVar25 = piVar25 + 0x84dec;
          iVar11 = 1;
        } while (bVar39);
      }
    }
  }
LAB_000f3b90:
  if ((uVar26 & 0x80) != 0) {
    piVar25 = (int *)0x0;
    iVar10 = RTMPGetKeyParameter("MuMimoDlEnable",pcVar13,0x80,param_2,0);
    if (iVar10 != 0) {
      iVar10 = rstrtok(pcVar13,&_LC6);
      if (iVar10 == 0) {
        iVar11 = 0;
        uVar2 = 0;
      }
      else {
        piVar36 = param_1 + 0xdb6d6;
        pbVar29 = (byte *)(param_1 + 0xd9e32);
        iVar11 = 0;
        do {
          uVar2 = os_str_tol(iVar10,0,10);
          if (*(char *)((int)param_1 + 0x286285) == '\x01') {
            if (iVar11 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242)) {
              piVar25 = param_1 + (uint)*pbVar29 * 0x160d + 0xadc92;
            }
          }
          else {
            bVar39 = iVar11 == 1;
            if (iVar11 < 2) {
              bVar39 = *(char *)((int)param_1 + 0x286285) == '\0';
            }
            if (bVar39) {
              piVar25 = piVar36;
            }
          }
          pbVar29 = pbVar29 + 1;
          if ((piVar25 != (int *)0x0) && (wlan_config_set_mu_dl_mimo(piVar25,uVar2), 3 < DebugLevel)
             ) {
            printk("MBSS[%d] MuMimoDlEnable = %d\n",iVar11,uVar2);
          }
          iVar11 = iVar11 + 1;
          iVar10 = rstrtok(0,&_LC6);
          piVar36 = piVar36 + 0x84dec;
        } while (iVar10 != 0);
      }
      if (*(char *)((int)param_1 + 0x286285) == '\x01') {
        if ((int)(uint)*(byte *)((int)param_1 + 0x2b7242) <= iVar11) goto LAB_000f3b98;
        pbVar29 = (byte *)((int)param_1 + iVar11 + 0x3678c7);
        do {
          pbVar29 = pbVar29 + 1;
          if ((param_1 + (uint)*pbVar29 * 0x160d + 0xadc92 != (int *)0x0) &&
             (wlan_config_set_mu_dl_mimo(param_1 + (uint)*pbVar29 * 0x160d + 0xadc92,uVar2),
             3 < DebugLevel)) {
            printk("More MBSS[%d] MuMimoDlEnable = %d\n",iVar11,uVar2);
          }
          iVar11 = iVar11 + 1;
        } while (iVar11 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242));
      }
      if ((*(char *)((int)param_1 + 0x286285) == '\0') && (iVar11 < 2)) {
        piVar25 = param_1 + iVar11 * 0x84dec + 0xdb6d6;
        do {
          if ((piVar25 != (int *)0x0) &&
             (wlan_config_set_mu_dl_mimo(piVar25,uVar2), -1 < DebugLevel)) {
            printk("More MBSS[%d] MuMimoDlEnable = %d\n",iVar11,uVar2);
          }
          bVar39 = iVar11 != 1;
          piVar25 = piVar25 + 0x84dec;
          iVar11 = 1;
        } while (bVar39);
      }
    }
  }
LAB_000f3b98:
  if ((uVar26 & 0x100000) != 0) {
    piVar25 = (int *)0x0;
    iVar10 = RTMPGetKeyParameter("MuMimoUlEnable",pcVar13,0x80,param_2,0);
    if (iVar10 != 0) {
      iVar10 = rstrtok(pcVar13,&_LC6);
      if (iVar10 == 0) {
        iVar11 = 0;
        uVar2 = 0;
      }
      else {
        piVar36 = param_1 + 0xdb6d6;
        pbVar29 = (byte *)(param_1 + 0xd9e32);
        iVar11 = 0;
        do {
          uVar2 = os_str_tol(iVar10,0,10);
          if (*(char *)((int)param_1 + 0x286285) == '\x01') {
            if (iVar11 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242)) {
              piVar25 = param_1 + (uint)*pbVar29 * 0x160d + 0xadc92;
            }
          }
          else {
            bVar39 = iVar11 == 1;
            if (iVar11 < 2) {
              bVar39 = *(char *)((int)param_1 + 0x286285) == '\0';
            }
            if (bVar39) {
              piVar25 = piVar36;
            }
          }
          pbVar29 = pbVar29 + 1;
          if ((piVar25 != (int *)0x0) && (wlan_config_set_mu_ul_mimo(piVar25,uVar2), 3 < DebugLevel)
             ) {
            printk("MBSS[%d] MuMimoUlEnable = %d\n",iVar11,uVar2);
          }
          iVar11 = iVar11 + 1;
          iVar10 = rstrtok(0,&_LC6);
          piVar36 = piVar36 + 0x84dec;
        } while (iVar10 != 0);
      }
      if (*(char *)((int)param_1 + 0x286285) == '\x01') {
        if ((int)(uint)*(byte *)((int)param_1 + 0x2b7242) <= iVar11) goto LAB_000f3ba0;
        pbVar29 = (byte *)((int)param_1 + iVar11 + 0x3678c7);
        do {
          pbVar29 = pbVar29 + 1;
          if ((param_1 + (uint)*pbVar29 * 0x160d + 0xadc92 != (int *)0x0) &&
             (wlan_config_set_mu_ul_mimo(param_1 + (uint)*pbVar29 * 0x160d + 0xadc92,uVar2),
             3 < DebugLevel)) {
            printk("More MBSS[%d] MuMimoUlEnable = %d\n",iVar11,uVar2);
          }
          iVar11 = iVar11 + 1;
        } while (iVar11 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242));
      }
      if ((*(char *)((int)param_1 + 0x286285) == '\0') && (iVar11 < 2)) {
        piVar25 = param_1 + iVar11 * 0x84dec + 0xdb6d6;
        do {
          if ((piVar25 != (int *)0x0) &&
             (wlan_config_set_mu_ul_mimo(piVar25,uVar2), -1 < DebugLevel)) {
            printk("More MBSS[%d] MuMimoUlEnable = %d\n",iVar11,uVar2);
          }
          bVar39 = iVar11 != 1;
          piVar25 = piVar25 + 0x84dec;
          iVar11 = 1;
        } while (bVar39);
      }
    }
  }
LAB_000f3ba0:
  iVar10 = RTMPGetKeyParameter("IEEE80211H",local_74,10,param_2,1);
  if (iVar10 != 0) {
    iVar10 = rstrtok(local_74,&_LC6);
    while (iVar10 != 0) {
      iVar11 = os_str_tol(iVar10,0,10);
      iVar10 = DebugLevel;
      if (iVar11 == 0) {
        *(undefined1 *)(param_1 + 0x1e541d) = 0;
        *(undefined1 *)((int)param_1 + 0xa79631) = 0;
        *(undefined1 *)((int)param_1 + 0x7953ef) = 0;
        *(undefined1 *)((int)param_1 + 0x7953f6) = 0;
        if (3 < iVar10) {
          printk("[%s]Disable DFS/Zero wait=%d/%d\n","RTMPSetProfileParameters",0,0);
          goto LAB_000f7b3c;
        }
      }
      else {
        *(undefined1 *)(param_1 + 0x1e541d) = 1;
LAB_000f7b3c:
        if (3 < DebugLevel) {
          printk("IEEE80211H=%d\n",(char)param_1[0x1e541d]);
        }
      }
      iVar10 = rstrtok(0,&_LC6);
    }
  }
  iVar10 = RTMPGetKeyParameter("RDRegion",local_74,0x80,param_2,1);
  pcVar13 = local_74;
  if (iVar10 == 0) {
    *(undefined1 *)((int)param_1 + 0x795075) = 0;
  }
  else {
    iVar10 = strncmp(local_74,"JAP_W53",7);
    if ((iVar10 == 0) || (iVar10 = strncmp(pcVar13,"jap_w53",7), iVar10 == 0)) {
      *(undefined1 *)((int)param_1 + 0x795075) = 3;
    }
    else {
      iVar10 = strncmp(pcVar13,"JAP_W56",7);
      if ((iVar10 == 0) || (iVar10 = strncmp(pcVar13,"jap_w56",7), iVar10 == 0)) {
        *(undefined1 *)((int)param_1 + 0x795075) = 4;
      }
      else {
        iVar10 = strncmp(pcVar13,"JAP",3);
        if ((iVar10 == 0) || (iVar10 = strncmp(pcVar13,"jap",3), iVar10 == 0)) {
          *(undefined1 *)((int)param_1 + 0x795075) = 2;
        }
        else {
          iVar10 = strncmp(pcVar13,"FCC",3);
          if ((iVar10 == 0) || (iVar10 = strncmp(pcVar13,"fcc",3), iVar10 == 0)) {
            *(undefined1 *)((int)param_1 + 0x795075) = 1;
          }
          else {
            *(undefined1 *)((int)param_1 + 0x795075) = 0;
          }
        }
      }
    }
    if (3 < DebugLevel) {
      printk("RDRegion=%d\n",*(undefined1 *)((int)param_1 + 0x795075));
      pcVar13 = local_74;
    }
  }
  ReadSecurityParameterFromFile(param_1,pcVar13,param_2);
  pcVar13 = local_74;
  if (*(char *)((int)param_1 + 0x286285) == '\x01') {
    __memzero(&local_58,6);
    if (*(char *)((int)param_1 + 0x2b7242) != '\0') {
      pbVar29 = (byte *)((int)param_1 + 0x3678c7);
      iVar10 = 0;
      do {
        pbVar29 = pbVar29 + 1;
        __memzero((char *)((int)param_1 +
                          (int)("[RTMPSetInformation][BandIdx=%d] Ndis802_11OFDM5\n" +
                               (uint)*pbVar29 * 0x5834 + 0x31)),0x408);
        snprintf((char *)local_ac,0x20,"AccessPolicy%d",iVar10);
        iVar11 = RTMPGetKeyParameter(local_ac,pcVar13,10,param_2,1);
        if (iVar11 != 0) {
          iVar11 = os_str_tol(pcVar13,0,10);
          if ((iVar11 == 1) || (iVar11 == 2)) {
            bVar6 = *pbVar29;
            *(char *)((int)param_1 + (uint)bVar6 * 0x5834 + 0x2bb671) = (char)iVar11;
            *(undefined1 *)((int)param_1 + (uint)bVar6 * 0x5834 + 0x2bb672) = 0;
            *(undefined1 *)((int)param_1 + (uint)bVar6 * 0x5834 + 0x2bb673) = 0;
            *(undefined1 *)(param_1 + (uint)bVar6 * 0x160d + 0xaed9d) = 0;
          }
          else {
            bVar6 = *pbVar29;
            *(undefined1 *)((int)param_1 + (uint)bVar6 * 0x5834 + 0x2bb671) = 0;
            *(undefined1 *)((int)param_1 + (uint)bVar6 * 0x5834 + 0x2bb672) = 0;
            *(undefined1 *)((int)param_1 + (uint)bVar6 * 0x5834 + 0x2bb673) = 0;
            *(undefined1 *)(param_1 + (uint)bVar6 * 0x160d + 0xaed9d) = 0;
          }
          if (3 < DebugLevel) {
            printk("%s=%d\n",local_ac,
                   *(undefined4 *)((int)param_1 + (uint)*pbVar29 * 0x5834 + 0x2bb671));
          }
        }
        snprintf((char *)local_ac,0x20,"AccessControlList%d",iVar10);
        uVar26 = 1;
        iVar11 = RTMPGetKeyParameter(local_ac,pcVar13,0x800,param_2,1);
        if (iVar11 != 0) {
          pcVar18 = (char *)rstrtok(pcVar13,&_LC6);
          while (pcVar18 != (char *)0x0) {
            sVar14 = strlen(pcVar18);
            if (sVar14 == 0x11) {
              if (0x80 < *(uint *)((int)param_1 + (uint)*pbVar29 * 0x5834 + 0x2bb675)) {
                printk(&_LC372,0x58c);
                dump_stack();
              }
              puVar23 = &local_58;
              pcVar15 = pcVar18;
              do {
                pcVar35 = pcVar15 + 3;
                AtoH(pcVar15,puVar23,1);
                puVar23 = (undefined4 *)((int)puVar23 + 1);
                pcVar15 = pcVar35;
              } while (pcVar35 != pcVar18 + 0x12);
              uVar19 = (uint)*pbVar29;
              iVar11 = *(int *)((int)param_1 + uVar19 * 0x5834 + 0x2bb675);
              if (iVar11 == 0x80) {
                if ((1 < DebugLevel) &&
                   (printk("The AccessControlList is full, and no more entry can join the list!\n"),
                   1 < DebugLevel)) {
                  uVar26 = local_58 >> 0x18;
                  printk("The last entry of ACL is %02x:%02x:%02x:%02x:%02x:%02x\n",local_58 & 0xff,
                         local_58._1_1_,local_58._2_1_,uVar26,(undefined1)local_54,local_54._1_1_);
                }
                break;
              }
              uVar27 = 0;
              if (iVar11 != 0) {
                uVar24 = 0;
                uVar31 = uVar24;
                do {
                  iVar11 = memcmp((char *)((int)param_1 +
                                          (int)("Set::OID_802_11_NETWORK_TYPE_IN_USE (=%d)\n" +
                                               uVar19 * 0x5834 + uVar31 * 8 + 5)),&local_58,6);
                  if (iVar11 == 0) {
                    if (3 < DebugLevel) {
                      uVar24 = 1;
                      printk("You have added an entry before :\n");
                      if (3 < DebugLevel) {
                        uVar26 = local_58 >> 0x18;
                        printk("The duplicate entry is %02x:%02x:%02x:%02x:%02x:%02x\n",
                               local_58 & 0xff,local_58._1_1_,local_58._2_1_,uVar26,
                               (undefined1)local_54,local_54._1_1_);
                        uVar19 = (uint)*pbVar29;
                        goto LAB_000fb6dc;
                      }
                      uVar19 = (uint)*pbVar29;
                    }
                    uVar24 = 1;
                  }
LAB_000fb6dc:
                  uVar31 = uVar31 + 1;
                  uVar27 = *(uint *)((int)param_1 + uVar19 * 0x5834 + 0x2bb675);
                } while (uVar31 < uVar27);
                if (uVar24 != 0) goto LAB_000fb5f4;
              }
              iVar11 = uVar19 * 0x5834 + (uVar27 + 0x886) * 8;
              *(uint *)((int)param_1 + uVar19 * 0x5834 + 0x2bb675) = uVar27 + 1;
              *(uint *)((int)param_1 +
                       (int)(
                            "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                            + iVar11 + 0xe1)) = local_58;
              *(undefined2 *)
               ((int)param_1 +
               (int)(
                    "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                    + iVar11 + 0xe5)) = local_54;
            }
LAB_000fb5f4:
            pcVar18 = (char *)rstrtok(0,&_LC6);
          }
          if (3 < DebugLevel) {
            printk("%s=Get %d Mac Address\n",local_ac,
                   *(undefined4 *)((int)param_1 + (uint)*pbVar29 * 0x5834 + 0x2bb675),
                   param_1 + (int)&DAT_000aed9c + (uint)*pbVar29 * 0x160d,uVar26);
          }
        }
        iVar10 = iVar10 + 1;
      } while (iVar10 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242));
    }
    pcVar13 = local_74;
    uVar26 = 0;
    *(undefined1 *)((int)param_1 + 0x36df65) = 0;
    *(undefined1 *)((int)param_1 + 0x36df67) = 0;
    *(undefined1 *)((int)param_1 + 0x36df69) = 0;
    *(undefined1 *)(param_1 + 0xdc6ee) = 1;
    *(undefined1 *)((int)param_1 + 0x581715) = 0;
    *(undefined1 *)((int)param_1 + 0x581717) = 0;
    *(undefined1 *)((int)param_1 + 0x581719) = 0;
    *(undefined1 *)(param_1 + 0x1614da) = 1;
    iVar10 = RTMPGetKeyParameter("ApCliEnable",local_74,0x80,param_2,1);
    if ((iVar10 != 0) && (pcVar18 = (char *)rstrtok(pcVar13,&_LC6), pcVar18 != (char *)0x0)) {
      puVar34 = (undefined1 *)((int)param_1 + 0x580e8d);
      do {
        if ((*pcVar18 == '0') || (*pcVar18 != '1')) {
          *puVar34 = 0;
        }
        else {
          *puVar34 = 1;
        }
        if (3 < DebugLevel) {
          printk("ApCliEntry[%d].Enable=%d\n",uVar26,*puVar34);
        }
        pcVar18 = (char *)rstrtok(0,&_LC6);
        uVar19 = uVar26 ^ 1;
        uVar26 = 1;
        puVar34 = puVar34 + 0x2137b0;
        if (pcVar18 == (char *)0x0) {
          uVar19 = 0;
        }
      } while (uVar19 != 0);
    }
    uVar26 = 0;
    iVar10 = RTMPGetKeyParameter("ApCliSsid",pcVar13,0x800,param_2,0);
    if ((iVar10 != 0) && (pcVar18 = (char *)rstrtok(pcVar13,&_LC6), pcVar18 != (char *)0x0)) {
      do {
        uVar19 = uVar26 ^ 1;
        if (pcVar13 == pcVar18) {
          uVar19 = 0;
        }
        uVar27 = uVar26;
        if (uVar19 != 0) {
          uVar27 = 1;
        }
        sVar14 = strlen(pcVar18);
        iVar10 = uVar27 * 0x2137b0;
        uVar26 = sVar14 & 0xff;
        *(char *)((int)param_1 + iVar10 + 0x580e5a) = (char)sVar14;
        if (uVar26 < 0x21) {
          __dest = (void *)((int)param_1 + iVar10 + 0x580e3a);
          if (uVar26 == 0) {
            __memzero((int)param_1 + iVar10 + 0x580e3a,0x20);
          }
          else {
            memcpy(__dest,pcVar18,uVar26);
            iVar11 = DebugLevel;
            *(undefined1 *)((int)param_1 + iVar10 + 0x580e8e) = 0;
            if (3 < iVar11) {
              printk("ApCliEntry[%d].CfgSsidLen=%d, CfgSsid=%s\n",uVar27,
                     *(undefined1 *)((int)param_1 + iVar10 + 0x580e5a),__dest);
            }
          }
        }
        else {
          *(undefined1 *)((int)param_1 + iVar10 + 0x580e5a) = 0;
        }
        pcVar18 = (char *)rstrtok(0,&_LC6);
        uVar26 = 1;
      } while ((uVar27 == 0 || uVar27 == 0xffffffff) && pcVar18 != (char *)0x0);
    }
    uVar26 = 0;
    iVar10 = RTMPGetKeyParameter("ApCliWirelessMode",pcVar13,0x800,param_2,0);
    if ((iVar10 != 0) && (iVar10 = rstrtok(pcVar13,&_LC6), iVar10 != 0)) {
      piVar25 = param_1 + 0xdb6dc;
      do {
        uVar2 = os_str_tol(iVar10,0,10);
        uVar21 = cfgmode_2_wmode(uVar2);
        *(short *)piVar25 = (short)uVar21;
        piVar25 = piVar25 + 0x84dec;
        if (3 < DebugLevel) {
          printk("ApCliEntry[%d].wdev.PhyMode=%d\n",uVar26,uVar21);
        }
        iVar10 = rstrtok(0,&_LC6);
        uVar19 = uVar26 ^ 1;
        uVar26 = 1;
        if (iVar10 == 0) {
          uVar19 = 0;
        }
      } while (uVar19 != 0);
    }
    bVar39 = (*(ushort *)(param_1 + 0xadc98) & 0x4e) == 0;
    if (*(char *)((int)param_1 + 0x2b7242) == '\0') {
      uVar9 = 0;
      uVar30 = 0;
LAB_000fb9c0:
      if (bVar39) {
        *(ushort *)(param_1 + 0xdb6dc) = uVar30;
      }
      else {
        *(ushort *)(param_1 + 0xdb6dc) = uVar9;
      }
      if (3 < DebugLevel) {
LAB_001002e4:
        printk("Sanity check in DBDC :ApCliEntry[%d].wdev.PhyMode=%d\n",0,(short)param_1[0xdb6dc]);
      }
      cVar4 = *(char *)((int)param_1 + 0x2b7242);
      if (cVar4 != '\0') goto LAB_000fb9f8;
LAB_000fc924:
      if (bVar39) {
        *(ushort *)(param_1 + 0x1604c8) = uVar9;
      }
      else {
        *(ushort *)(param_1 + 0x1604c8) = uVar30;
      }
    }
    else {
      pbVar29 = (byte *)((int)param_1 + 0x3678c7);
      bVar40 = false;
      uVar9 = 0;
      uVar30 = 0;
      do {
        while( true ) {
          pbVar29 = pbVar29 + 1;
          uVar1 = *(ushort *)(param_1 + (int)(WtcGetWcidLinkType + (uint)*pbVar29 * 0x160d));
          if ((uVar1 & 0x4e) != 0) break;
          if (uVar30 < uVar1) {
            uVar30 = uVar1;
          }
          if ((bVar39) && (*(ushort *)(param_1 + 0xdb6dc) == uVar1)) {
            bVar40 = true;
          }
LAB_000fb968:
          if (pbVar29 ==
              (byte *)((int)param_1 +
                      (int)(&DAT_003678c8 + (byte)(*(char *)((int)param_1 + 0x2b7242) - 1))))
          goto LAB_000fb9b8;
        }
        if (uVar9 < uVar1) {
          uVar9 = uVar1;
        }
        if (bVar39) goto LAB_000fb968;
        if (*(ushort *)(param_1 + 0xdb6dc) == uVar1) {
          bVar40 = true;
        }
      } while (pbVar29 !=
               (byte *)((int)param_1 +
                       (int)(&DAT_003678c8 + (byte)(*(char *)((int)param_1 + 0x2b7242) - 1))));
LAB_000fb9b8:
      if (!bVar40) goto LAB_000fb9c0;
      if (3 < DebugLevel) goto LAB_001002e4;
      cVar4 = *(char *)((int)param_1 + 0x2b7242);
LAB_000fb9f8:
      pbVar29 = (byte *)((int)param_1 + 0x3678c7);
      bVar40 = false;
      do {
        pbVar29 = pbVar29 + 1;
        uVar1 = *(ushort *)(param_1 + (int)(WtcGetWcidLinkType + (uint)*pbVar29 * 0x160d));
        if ((uVar1 & 0x4e) == 0) {
          if (uVar30 < uVar1) {
            uVar30 = uVar1;
          }
          if ((!bVar39) && (*(ushort *)(param_1 + 0x1604c8) == uVar1)) {
            bVar40 = true;
          }
        }
        else {
          if (uVar9 < uVar1) {
            uVar9 = uVar1;
          }
          if ((bVar39) && (*(ushort *)(param_1 + 0x1604c8) == uVar1)) {
            bVar40 = true;
          }
        }
      } while (pbVar29 != (byte *)((int)param_1 + (int)(&DAT_003678c8 + (byte)(cVar4 - 1))));
      if (!bVar40) goto LAB_000fc924;
    }
    if (3 < DebugLevel) {
      printk("Sanity check in DBDC :ApCliEntry[%d].wdev.PhyMode=%d\n",1,(short)param_1[0x1604c8]);
    }
    iVar10 = RTMPGetKeyParameter("ApCliBssid",pcVar13,0x800,param_2,1);
    if ((iVar10 != 0) && (pcVar18 = (char *)rstrtok(pcVar13,&_LC6), pcVar18 != (char *)0x0)) {
      uVar26 = 0;
      do {
        uVar19 = uVar26 ^ 1;
        if (pcVar13 == pcVar18) {
          uVar19 = 0;
        }
        if (uVar19 == 0) {
          sVar14 = strlen(pcVar18);
          if ((sVar14 == 0x11) && (iVar10 = strcmp(pcVar18,"00:00:00:00:00:00"), iVar10 != 0))
          goto LAB_000fe898;
        }
        else {
          sVar14 = strlen(pcVar18);
          if (sVar14 != 0x11) {
            rstrtok(0,&_LC6);
            break;
          }
          iVar10 = strcmp(pcVar18,"00:00:00:00:00:00");
          if (iVar10 == 0) {
            rstrtok(0,&_LC6);
            break;
          }
          uVar26 = 1;
LAB_000fe898:
          pcVar15 = pcVar18;
          piVar25 = local_ac;
          do {
            pcVar35 = pcVar15 + 3;
            AtoH(pcVar15,piVar25,1);
            piVar25 = (int *)((int)piVar25 + 1);
            pcVar15 = pcVar35;
          } while (pcVar35 != pcVar18 + 0x12);
          *(char **)((int)param_1 + uVar26 * 0x2137b0 + 0x580e5b) = local_48;
          *(undefined2 *)((int)param_1 + uVar26 * 0x2137b0 + 0x580e5f) = local_44._0_2_;
          *(undefined1 *)((int)param_1 + uVar26 * 0x2137b0 + 0x580e8e) = 0;
        }
        pcVar18 = (char *)rstrtok(0,&_LC6);
        uVar19 = uVar26 ^ 1;
        uVar26 = 1;
        if (pcVar18 == (char *)0x0) {
          uVar19 = 0;
        }
      } while (uVar19 != 0);
    }
    iVar10 = RTMPGetKeyParameter("ApCliTxMode",pcVar13,0x19,param_2,1);
    if ((iVar10 == 0) || (pcVar18 = (char *)rstrtok(pcVar13,&_LC6), pcVar18 == (char *)0x0)) {
      piVar25 = (int *)0x0;
    }
    else {
      uVar26 = 0;
LAB_000fe6f8:
      uVar19 = uVar26 ^ 1;
      if (pcVar13 == pcVar18) {
        uVar19 = 0;
      }
      if (uVar19 == 0) {
        bVar6 = RT_CfgSetFixedTxPhyMode(pcVar18);
        *(byte *)((int)param_1 + uVar26 * 0x2137b0 + 0x36e407) =
             *(byte *)((int)param_1 + uVar26 * 0x2137b0 + 0x36e407) & 199 | (bVar6 & 7) << 3;
        if (3 < DebugLevel) goto LAB_00100304;
LAB_000fe7b0:
        pcVar18 = (char *)rstrtok(0,&_LC6);
        uVar19 = uVar26 ^ 1;
        if (pcVar18 == (char *)0x0) {
          uVar19 = 0;
        }
        if (uVar19 == 0) goto LAB_000fe750;
        uVar26 = 1;
        goto LAB_000fe6f8;
      }
      bVar6 = RT_CfgSetFixedTxPhyMode(pcVar18);
      *(byte *)((int)param_1 + 0x581bb7) =
           *(byte *)((int)param_1 + 0x581bb7) & 199 | (bVar6 & 7) << 3;
      if (3 < DebugLevel) {
        uVar26 = 1;
LAB_00100304:
        printk("I/F(apcli%d) Tx Mode = %d\n",uVar26);
        goto LAB_000fe7b0;
      }
      uVar26 = 1;
      rstrtok(0,&_LC6);
LAB_000fe750:
      piVar25 = param_1 + uVar26 * 0x84dec + 0xdb6d6;
    }
    iVar10 = RTMPGetKeyParameter("ApCliTxMcs",pcVar13,0x32,param_2,1);
    if ((iVar10 != 0) && (pcVar18 = (char *)rstrtok(pcVar13,&_LC6), pcVar18 != (char *)0x0)) {
      uVar26 = 0;
      do {
        uVar19 = uVar26 ^ 1;
        if (pcVar13 == pcVar18) {
          uVar19 = 0;
        }
        uVar27 = uVar26;
        if (uVar19 != 0) {
          uVar27 = 1;
        }
        iVar10 = uVar27 * 0x2137b0;
        bVar6 = RT_CfgSetTxMCSProc(pcVar18,(undefined *)
                                           ((int)param_1 + (int)(&DAT_0036e408 + iVar10)));
        iVar11 = DebugLevel;
        *(byte *)((int)param_1 + iVar10 + 0x36e406) =
             *(byte *)((int)param_1 + iVar10 + 0x36e406) & 0x80 | bVar6 & 0x7f;
        if (3 < iVar11) {
          puVar32 = &_LC126;
          if ((*(byte *)((int)param_1 + iVar10 + 0x36e406) & 0x7f) != 0x21) {
            puVar32 = &_LC127;
          }
          printk("I/F(apcli%d) Tx MCS = %s(%d)\n",uVar27,puVar32);
        }
        pcVar18 = (char *)rstrtok(0,&_LC6);
        uVar19 = uVar27 ^ 1;
        uVar26 = 1;
        if (pcVar18 == (char *)0x0) {
          uVar19 = 0;
        }
      } while (uVar19 != 0);
      piVar25 = param_1 + uVar27 * 0x84dec + 0xdb6d6;
    }
    iVar10 = RTMPGetKeyParameter("ApCli_Wsc4digitPinCode",pcVar13,0x20,param_2,1);
    if ((iVar10 != 0) && (pcVar18 = (char *)rstrtok(pcVar13,&_LC6), pcVar18 != (char *)0x0)) {
      uVar26 = 0;
      do {
        uVar19 = uVar26 ^ 1;
        if (pcVar13 == pcVar18) {
          uVar19 = 0;
        }
        uVar27 = uVar26;
        if (uVar19 != 0) {
          uVar27 = 1;
        }
        iVar11 = os_str_tol(pcVar18,0,10);
        iVar10 = DebugLevel;
        if (iVar11 == 0) {
          *(undefined1 *)((int)param_1 + uVar27 * 0x2137b0 + 0x36ee55) = 0;
          iVar10 = DebugLevel;
        }
        else {
          *(undefined1 *)((int)param_1 + uVar27 * 0x2137b0 + 0x36ee55) = 1;
        }
        if (3 < iVar10) {
          printk("I/F(apcli%d) ApCli_Wsc4digitPinCode=%d\n",uVar27,
                 *(undefined1 *)((int)param_1 + uVar27 * 0x2137b0 + 0x36ee55));
        }
        pcVar18 = (char *)rstrtok(0,&_LC6);
        uVar26 = 1;
      } while ((uVar27 == 0 || uVar27 == 0xffffffff) && pcVar18 != (char *)0x0);
    }
    iVar10 = RTMPGetKeyParameter("ApCliWscScanMode",pcVar13,0x20,param_2,1);
    if ((iVar10 != 0) && (iVar10 = rstrtok(pcVar13,&_LC6), iVar10 != 0)) {
      uVar26 = 0;
      pcVar18 = s_format__t_id_task_id_task_prempt_00371a7c + 0xd + (int)param_1;
      do {
        cVar4 = simple_strtol(iVar10,0,10);
        *pcVar18 = cVar4 == '\x01';
        pcVar18 = pcVar18 + 0x2137b0;
        if (3 < DebugLevel) {
          printk("I/F(apcli%d) WscApCliScanMode=%d\n",uVar26);
        }
        iVar10 = rstrtok(0,&_LC6);
        uVar19 = uVar26 ^ 1;
        uVar26 = 1;
        if (iVar10 == 0) {
          uVar19 = 0;
        }
      } while (uVar19 != 0);
    }
    iVar10 = RTMPGetKeyParameter("ApCliAPSDCapable",pcVar13,10,param_2,1);
    if (iVar10 != 0) {
      *(undefined1 *)((int)param_1 + 0x3678fa) = 1;
      pcVar18 = (char *)rstrtok(pcVar13,&_LC6);
      if (pcVar18 != (char *)0x0) {
        uVar26 = 0;
        do {
          uVar19 = uVar26 ^ 1;
          if (pcVar13 == pcVar18) {
            uVar19 = 0;
          }
          if (uVar19 == 0) {
            uVar2 = os_str_tol(pcVar18,0,10);
            iVar10 = DebugLevel;
            *(undefined1 *)(param_1 + uVar26 * 0x84dec + 0xdb90c) = uVar2;
            if (-1 < iVar10) goto LAB_00100900;
          }
          else {
            uVar2 = os_str_tol(pcVar18,0,10);
            bVar39 = DebugLevel < 0;
            *(undefined1 *)(param_1 + 0x1606f8) = uVar2;
            if (bVar39) {
              rstrtok(0,&_LC6);
              break;
            }
            uVar26 = 1;
LAB_00100900:
            printk("ApCliAPSDCapable[%d]=%d\n",uVar26,uVar2);
          }
          pcVar18 = (char *)rstrtok(0,&_LC6);
          uVar19 = uVar26 ^ 1;
          uVar26 = 1;
          if (pcVar18 == (char *)0x0) {
            uVar19 = 0;
          }
        } while (uVar19 != 0);
      }
    }
    iVar10 = RTMPGetKeyParameter("ApCliNum",pcVar13,10,param_2,1);
    if (iVar10 != 0) {
      iVar10 = os_str_tol(pcVar13,0,10);
      if (iVar10 < 3) {
        uVar2 = os_str_tol(pcVar13,0,10);
        *(undefined1 *)((int)param_1 + 0x3678f9) = uVar2;
      }
      if (3 < DebugLevel) {
        printk("I/F(apcli) ApCliNum=%d\n",*(undefined1 *)((int)param_1 + 0x3678f9));
      }
    }
    *(undefined1 *)((int)param_1 + 0x3678f9) = 2;
    iVar10 = RTMPGetKeyParameter("ApCliPMFMFPC",pcVar13,0x20,param_2,1);
    if ((iVar10 != 0) && (pcVar18 = (char *)rstrtok(pcVar13,&_LC6), pcVar18 != (char *)0x0)) {
      uVar26 = 0;
      do {
        uVar19 = uVar26 ^ 1;
        if (pcVar13 == pcVar18) {
          uVar19 = 0;
        }
        if (uVar19 != 0) {
          iVar10 = *param_1;
          uVar20 = *(undefined4 *)(iVar10 + 0x3c);
          uVar21 = *(undefined4 *)(iVar10 + 0x38);
          *(undefined4 *)(iVar10 + 0x3c) = 1;
          *(undefined4 *)(iVar10 + 0x38) = 0x400;
          Set_ApCliPMFMFPC_Proc(param_1,pcVar18);
          *(undefined4 *)(iVar10 + 0x3c) = uVar20;
          *(undefined4 *)(iVar10 + 0x38) = uVar21;
          rstrtok(0,&_LC6);
          break;
        }
        iVar10 = *param_1;
        uVar20 = *(undefined4 *)(iVar10 + 0x3c);
        uVar21 = *(undefined4 *)(iVar10 + 0x38);
        *(uint *)(iVar10 + 0x3c) = uVar26;
        *(undefined4 *)(iVar10 + 0x38) = 0x400;
        Set_ApCliPMFMFPC_Proc(param_1,pcVar18);
        *(undefined4 *)(iVar10 + 0x3c) = uVar20;
        *(undefined4 *)(iVar10 + 0x38) = uVar21;
        pcVar18 = (char *)rstrtok(0,&_LC6);
        uVar19 = uVar26 ^ 1;
        uVar26 = 1;
        if (pcVar18 == (char *)0x0) {
          uVar19 = 0;
        }
      } while (uVar19 != 0);
    }
    iVar10 = RTMPGetKeyParameter("ApCliPMFMFPR",pcVar13,0x20,param_2,1);
    if ((iVar10 != 0) && (pcVar18 = (char *)rstrtok(pcVar13,&_LC6), pcVar18 != (char *)0x0)) {
      uVar26 = 0;
      do {
        uVar19 = uVar26 ^ 1;
        if (pcVar13 == pcVar18) {
          uVar19 = 0;
        }
        if (uVar19 != 0) {
          iVar10 = *param_1;
          uVar20 = *(undefined4 *)(iVar10 + 0x3c);
          uVar21 = *(undefined4 *)(iVar10 + 0x38);
          *(undefined4 *)(iVar10 + 0x3c) = 1;
          *(undefined4 *)(iVar10 + 0x38) = 0x400;
          Set_ApCliPMFMFPR_Proc(param_1,pcVar18);
          *(undefined4 *)(iVar10 + 0x3c) = uVar20;
          *(undefined4 *)(iVar10 + 0x38) = uVar21;
          rstrtok(0,&_LC6);
          break;
        }
        iVar10 = *param_1;
        uVar20 = *(undefined4 *)(iVar10 + 0x3c);
        uVar21 = *(undefined4 *)(iVar10 + 0x38);
        *(uint *)(iVar10 + 0x3c) = uVar26;
        *(undefined4 *)(iVar10 + 0x38) = 0x400;
        Set_ApCliPMFMFPR_Proc(param_1,pcVar18);
        *(undefined4 *)(iVar10 + 0x3c) = uVar20;
        *(undefined4 *)(iVar10 + 0x38) = uVar21;
        pcVar18 = (char *)rstrtok(0,&_LC6);
        uVar19 = uVar26 ^ 1;
        uVar26 = 1;
        if (pcVar18 == (char *)0x0) {
          uVar19 = 0;
        }
      } while (uVar19 != 0);
    }
    iVar10 = RTMPGetKeyParameter("ApCliPMFSHA256",pcVar13,0x20,param_2,1);
    if ((iVar10 != 0) && (pcVar18 = (char *)rstrtok(pcVar13,&_LC6), pcVar18 != (char *)0x0)) {
      uVar26 = 0;
      do {
        uVar19 = uVar26 ^ 1;
        if (pcVar13 == pcVar18) {
          uVar19 = 0;
        }
        if (uVar19 != 0) {
          iVar10 = *param_1;
          uVar20 = *(undefined4 *)(iVar10 + 0x3c);
          uVar21 = *(undefined4 *)(iVar10 + 0x38);
          *(undefined4 *)(iVar10 + 0x3c) = 1;
          *(undefined4 *)(iVar10 + 0x38) = 0x400;
          Set_ApCliPMFSHA256_Proc(param_1,pcVar18);
          *(undefined4 *)(iVar10 + 0x3c) = uVar20;
          *(undefined4 *)(iVar10 + 0x38) = uVar21;
          rstrtok(0,&_LC6);
          break;
        }
        iVar10 = *param_1;
        uVar20 = *(undefined4 *)(iVar10 + 0x3c);
        uVar21 = *(undefined4 *)(iVar10 + 0x38);
        *(uint *)(iVar10 + 0x3c) = uVar26;
        *(undefined4 *)(iVar10 + 0x38) = 0x400;
        Set_ApCliPMFSHA256_Proc(param_1,pcVar18);
        *(undefined4 *)(iVar10 + 0x3c) = uVar20;
        *(undefined4 *)(iVar10 + 0x38) = uVar21;
        pcVar18 = (char *)rstrtok(0,&_LC6);
        uVar19 = uVar26 ^ 1;
        uVar26 = 1;
        if (pcVar18 == (char *)0x0) {
          uVar19 = 0;
        }
      } while (uVar19 != 0);
    }
    uVar26 = 0;
    iVar10 = RTMPGetKeyParameter("ApCliMuOfdmaDlEnable",pcVar13,0x80,param_2,0);
    if ((iVar10 != 0) && (iVar10 = rstrtok(pcVar13,&_LC6), iVar10 != 0)) {
      piVar36 = param_1 + 0xdb6d6;
      do {
        uVar2 = os_str_tol(iVar10,0,10);
        if ((*(byte *)(param_1 + 0xa18a5) & 3) == 3) {
          piVar25 = piVar36;
        }
        piVar36 = piVar36 + 0x84dec;
        if ((piVar25 != (int *)0x0) && (wlan_config_set_mu_dl_ofdma(piVar25,uVar2), 3 < DebugLevel))
        {
          printk("APCLI[%d] ApCliMuOfdmaDlEnable = %d\n",uVar26,uVar2);
        }
        iVar10 = rstrtok(0,&_LC6);
        uVar19 = uVar26 ^ 1;
        uVar26 = 1;
        if (iVar10 == 0) {
          uVar19 = 0;
        }
      } while (uVar19 != 0);
    }
    uVar26 = 0;
    iVar10 = RTMPGetKeyParameter("ApCliMuOfdmaUlEnable",pcVar13,0x80,param_2,0);
    if ((iVar10 != 0) && (iVar10 = rstrtok(pcVar13,&_LC6), iVar10 != 0)) {
      piVar36 = param_1 + 0xdb6d6;
      do {
        uVar2 = os_str_tol(iVar10,0,10);
        if ((*(byte *)(param_1 + 0xa18a5) & 3) == 3) {
          piVar25 = piVar36;
        }
        piVar36 = piVar36 + 0x84dec;
        if ((piVar25 != (int *)0x0) && (wlan_config_set_mu_ul_ofdma(piVar25,uVar2), 3 < DebugLevel))
        {
          printk("APCLI[%d] ApCliMuOfdmaUlEnable = %d\n",uVar26,uVar2);
        }
        iVar10 = rstrtok(0,&_LC6);
        uVar19 = uVar26 ^ 1;
        uVar26 = 1;
        if (iVar10 == 0) {
          uVar19 = 0;
        }
      } while (uVar19 != 0);
    }
    uVar26 = 0;
    iVar10 = RTMPGetKeyParameter("ApCliMuMimoDlEnable",pcVar13,0x80,param_2,0);
    if ((iVar10 != 0) && (iVar10 = rstrtok(pcVar13,&_LC6), iVar10 != 0)) {
      piVar36 = param_1 + 0xdb6d6;
      do {
        uVar2 = os_str_tol(iVar10,0,10);
        if ((*(byte *)(param_1 + 0xa18a5) & 3) == 3) {
          piVar25 = piVar36;
        }
        piVar36 = piVar36 + 0x84dec;
        if ((piVar25 != (int *)0x0) && (wlan_config_set_mu_dl_mimo(piVar25,uVar2), 3 < DebugLevel))
        {
          printk("APCLI[%d] ApCliMuMimoDlEnable = %d\n",uVar26,uVar2);
        }
        iVar10 = rstrtok(0,&_LC6);
        uVar19 = uVar26 ^ 1;
        uVar26 = 1;
        if (iVar10 == 0) {
          uVar19 = 0;
        }
      } while (uVar19 != 0);
    }
    uVar26 = 0;
    iVar10 = RTMPGetKeyParameter("ApCliMuMimoUlEnable",pcVar13,0x80,param_2,0);
    if ((iVar10 != 0) && (iVar10 = rstrtok(pcVar13,&_LC6), iVar10 != 0)) {
      piVar36 = param_1 + 0xdb6d6;
      do {
        uVar2 = os_str_tol(iVar10,0,10);
        if ((*(byte *)(param_1 + 0xa18a5) & 3) == 3) {
          piVar25 = piVar36;
        }
        piVar36 = piVar36 + 0x84dec;
        if ((piVar25 != (int *)0x0) && (wlan_config_set_mu_ul_mimo(piVar25,uVar2), 3 < DebugLevel))
        {
          printk("APCLI[%d] ApCliMuMimoUlEnable = %d\n",uVar26,uVar2);
        }
        iVar10 = rstrtok(0,&_LC6);
        uVar19 = uVar26 ^ 1;
        uVar26 = 1;
        if (iVar10 == 0) {
          uVar19 = 0;
        }
      } while (uVar19 != 0);
    }
    uVar26 = 0;
    rtmp_read_igmp_snoop_from_file(param_1,local_74,param_2);
    rtmp_read_MWDS_from_file(param_1,local_74,param_2);
    iVar10 = RTMPGetKeyParameter("MACRepeaterEn",local_74,10,param_2,0);
    if (iVar10 != 0) {
      iVar11 = rstrtok(local_74,&_LC6);
      iVar10 = DebugLevel;
      while (DebugLevel = iVar10, iVar11 != 0) {
        iVar10 = os_str_tol(local_74,0,10);
        bVar39 = iVar10 != 0;
        AsicSetReptFuncEnable(param_1,bVar39,uVar26 & 0xff);
        iVar10 = DebugLevel;
        *(bool *)(param_1 + 0xd9e43) = bVar39;
        if (3 < iVar10) {
          printk("MACRepeaterEn=%d Band=%d\n",bVar39,uVar26);
        }
        uVar26 = uVar26 + 1;
        iVar11 = rstrtok(0,&_LC6);
        iVar10 = DebugLevel;
      }
      if ((char)param_1[0xd9e43] != '\0') {
        *(undefined1 *)((int)param_1 + 0xa79631) = 0;
        *(undefined1 *)((int)param_1 + 0x7953f6) = 0;
        if (3 < iVar10) {
          printk(&_LC411,"RTMPSetProfileParameters");
        }
      }
    }
    iVar10 = RTMPGetKeyParameter("MACRepeaterOuiMode",local_74,10,param_2,0);
    if (iVar10 != 0) {
      iVar11 = os_str_tol(local_74,0,10);
      iVar10 = DebugLevel;
      if ((iVar11 != 1) && (iVar11 != 2)) {
        iVar11 = 0;
      }
      *(char *)(param_1 + 0xd9e44) = (char)iVar11;
      if (3 < iVar10) {
        printk("MACRepeaterOuiMode=%d\n",(char)param_1[0xd9e44]);
      }
    }
  }
  iVar10 = RTMPGetKeyParameter("SE_OFF",local_74,0x19,param_2,1);
  if (iVar10 != 0) {
    iVar11 = os_str_tol(local_74,0,10);
    iVar10 = DebugLevel;
    *(bool *)((int)param_1 + 0x795943) = iVar11 != 0;
    if (3 < iVar10) {
      printk("%s(): SE_OFF=%d\n","RTMPSetProfileParameters");
    }
  }
  iVar10 = RTMPGetKeyParameter("AntennaIndex",local_74,0x19,param_2,1);
  if (iVar10 != 0) {
    uVar26 = simple_strtol(local_74,0,10);
    if (uVar26 < 0x1d) {
      if (uVar26 - 0x18 < 2) {
        uVar26 = 0;
      }
      uVar2 = (undefined1)uVar26;
    }
    else {
      uVar2 = 0;
    }
    *(undefined1 *)(param_1 + 0x1e5651) = uVar2;
    if (3 < DebugLevel) {
      printk("%s(): antenna_index=%d\n","RTMPSetProfileParameters");
    }
  }
  pcVar13 = local_74;
  iVar10 = RTMPGetKeyParameter("HT_BW",local_74,0x40,param_2,1);
  if (iVar10 != 0) {
    cVar4 = os_str_tol(pcVar13,0,10);
    wlan_config_set_ht_bw_all(param_1 + 0x29f156,cVar4);
    if (3 < DebugLevel) {
      pcVar18 = "40 MHz";
      if (cVar4 != '\x01') {
        pcVar18 = "20 MHz";
      }
      printk("HT: Channel Width = %s\n",pcVar18);
    }
    if ((*(char *)((int)param_1 + 0x286285) == '\x01') &&
       (iVar10 = rstrtok(pcVar13,&_LC6), iVar10 != 0)) {
      pbVar29 = (byte *)((int)param_1 + 0x3678c7);
      iVar11 = 0;
      do {
        iVar12 = hc_get_chip_bcn_max_num(param_1[0x29e5e8]);
        if (iVar12 <= iVar11) break;
        pbVar29 = pbVar29 + 1;
        uVar26 = (uint)*pbVar29;
        uVar9 = os_str_tol(iVar10,0,10);
        wlan_config_set_ht_bw
                  ((char *)((int)param_1 +
                           (int)(
                                "======== Badnode detector =============\nvow_bn_en = <0/1> 0:dieable, 1:enable\nvow_bn_mon_period = <period> ms\nvow_bn_fallback_th = <count>\nvow_bn_per_th = <TX PER>\n======== Airtime counter test =============\nvow_counter_test = <0/1> 0:dieable, 1:enable\nvow_counter_test_period = <period> ms\nvow_counter_test_band = <band>\nvow_counter_test_avgcnt = <average num> sec\nvow_counter_test_target = <wlanidx>\n======== DVT =============\nvow_dvt_en = <0/1> 0:dieable, 1:enable\nvow_monitor_sta = <STA num>\nvow_show_sta = <STA num>\nvow_monitor_bss = <BSS num>\nvow_monitor_mbss = <MBSS num>\nvow_show_mbss = <MBSS num>\nvow_avg_num = <average num> sec\n======== RED ===========\nvow_set_red_en = <0/1> 0:disable, 1:enable\nvow_set_red_show_sta = <STA num>\nvow_set_red_tar_delay = <tarDelay> us\n======== WATF ===========\nvow_watf_en = <0/1> 0:disable, 1:enable\nvow_watf_q = <level>-<quantum> unit 256us\nvow_watf_add_entry = <level>-<Addr>\nvow_watf_del_entry = <Addr>\n"
                                + uVar26 * 0x5834 + 0xe0)),uVar9 & 0xff);
        *(ushort *)(param_1 + uVar26 * 0x160d + 0xadf55) =
             *(ushort *)(param_1 + uVar26 * 0x160d + 0xadf55) & 0xfe7f | (uVar9 & 3) << 7;
        iVar10 = rstrtok(0,&_LC6);
        iVar11 = iVar11 + 1;
      } while (iVar10 != 0);
    }
  }
  iVar10 = hc_get_chip_cap(param_1[0x29e5e8]);
  if (*(char *)((int)param_1 + 0x286285) == '\x01') {
    uVar26 = (uint)*(byte *)((int)param_1 + 0x2b7242);
  }
  else {
    uVar26 = 2;
  }
  iVar11 = is_multi_profile_enable(param_1);
  if (iVar11 == 0) {
    local_a8 = 0;
  }
  else {
    local_a8 = multi_profile_get_pf1_num(param_1);
  }
  iVar11 = RTMPGetKeyParameter("HT_TxStream",pcVar13,0x80,param_2,1);
  if (iVar11 != 0) {
    iVar11 = rstrtok(pcVar13,&_LC6);
    if (iVar11 == 0) {
      bVar6 = 0;
      uVar19 = 0;
      if (1 < *(byte *)((int)param_1 + 0x2b7242)) goto LAB_000f7f04;
    }
    else {
      uVar27 = 0;
      uVar19 = 0;
      do {
        bVar6 = os_str_tol(iVar11,0,10);
        uVar31 = uVar27;
        if ((int)uVar27 < (int)uVar26) {
          do {
            iVar11 = FUN_000ee05c(param_1,uVar31 & 0xff);
            uVar31 = uVar31 + 1;
            if (iVar11 != 0) {
              bVar5 = bVar6;
              if (*(byte *)(iVar10 + 0x6d) <= bVar6) {
                bVar5 = *(byte *)(iVar10 + 0x6d);
              }
              wlan_config_set_tx_stream(iVar11,bVar5);
            }
          } while (uVar31 != uVar26);
        }
        uVar19 = uVar19 + 1;
        iVar11 = rstrtok(0,&_LC6);
        uVar27 = uVar27 + local_a8;
      } while (iVar11 != 0);
      if ((1 < *(byte *)((int)param_1 + 0x2b7242)) &&
         ((int)uVar19 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242))) {
LAB_000f7f04:
        do {
          iVar11 = FUN_000ee05c(param_1,uVar19 & 0xff);
          uVar19 = uVar19 + 1;
          if (iVar11 != 0) {
            bVar5 = bVar6;
            if (*(byte *)(iVar10 + 0x6d) <= bVar6) {
              bVar5 = *(byte *)(iVar10 + 0x6d);
            }
            wlan_config_set_tx_stream(iVar11,bVar5);
          }
        } while ((int)uVar19 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242));
      }
    }
  }
  iVar11 = RTMPGetKeyParameter("HT_RxStream",pcVar13,0x80,param_2,1);
  if (iVar11 != 0) {
    iVar11 = rstrtok(pcVar13,&_LC6);
    if (iVar11 == 0) {
      bVar6 = 0;
      uVar19 = 0;
      if (1 < *(byte *)((int)param_1 + 0x2b7242)) goto LAB_000f5fdc;
    }
    else {
      uVar27 = 0;
      uVar19 = 0;
      do {
        bVar6 = os_str_tol(iVar11,0,10);
        uVar31 = uVar27;
        if ((int)uVar27 < (int)uVar26) {
          do {
            iVar11 = FUN_000ee05c(param_1,uVar31 & 0xff);
            uVar31 = uVar31 + 1;
            if (iVar11 != 0) {
              bVar5 = bVar6;
              if (*(byte *)(iVar10 + 0x6d) <= bVar6) {
                bVar5 = *(byte *)(iVar10 + 0x6d);
              }
              wlan_config_set_rx_stream(iVar11,bVar5);
            }
          } while (uVar31 != uVar26);
        }
        uVar19 = uVar19 + 1;
        iVar11 = rstrtok(0,&_LC6);
        uVar27 = uVar27 + local_a8;
      } while (iVar11 != 0);
      if ((1 < *(byte *)((int)param_1 + 0x2b7242)) &&
         ((int)uVar19 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242))) {
LAB_000f5fdc:
        do {
          iVar11 = FUN_000ee05c(param_1,uVar19 & 0xff);
          uVar19 = uVar19 + 1;
          if (iVar11 != 0) {
            bVar5 = bVar6;
            if (*(byte *)(iVar10 + 0x6d) <= bVar6) {
              bVar5 = *(byte *)(iVar10 + 0x6d);
            }
            wlan_config_set_rx_stream(iVar11,bVar5);
          }
        } while ((int)uVar19 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242));
      }
    }
  }
  iVar10 = RTMPGetKeyParameter("HT_OpMode",pcVar13,0x80,param_2,1);
  if ((iVar10 != 0) && (iVar10 = rstrtok(pcVar13,&_LC6), iVar10 != 0)) {
    cVar4 = '\0';
    do {
      uVar2 = os_str_tol(iVar10,0,10);
      iVar10 = FUN_000ee05c(param_1,cVar4);
      if (iVar10 != 0) {
        wlan_config_set_ht_mode(iVar10,uVar2);
      }
      iVar10 = rstrtok(0,&_LC6);
      cVar4 = cVar4 + '\x01';
    } while (iVar10 != 0);
  }
  cVar4 = '\0';
  iVar10 = RTMPGetKeyParameter("HT_PROTECT",pcVar13,0x80,param_2,0);
  if ((iVar10 != 0) && (iVar10 = rstrtok(pcVar13,&_LC6), iVar10 != 0)) {
    do {
      cVar3 = os_str_tol(iVar10,0,10);
      if (3 < DebugLevel) {
        pcVar18 = "Enable";
        if (cVar3 == '\0') {
          pcVar18 = "Disable";
        }
        printk("HT_PROTECT=%s\n",pcVar18);
      }
      iVar10 = FUN_000ee05c(param_1,cVar4);
      cVar4 = cVar4 + '\x01';
      if (iVar10 != 0) {
        wlan_config_set_ht_protect_en(iVar10,cVar3);
      }
      iVar10 = rstrtok(0,&_LC6);
    } while (iVar10 != 0);
  }
  cVar4 = '\0';
  iVar10 = RTMPGetKeyParameter("HT_GI",pcVar13,0x80,param_2,0);
  if ((iVar10 != 0) && (iVar10 = rstrtok(pcVar13,&_LC6), iVar10 != 0)) {
    do {
      cVar3 = os_str_tol(iVar10,0,10);
      if (3 < DebugLevel) {
        pcVar18 = "GI_400";
        if (cVar3 != '\x01') {
          pcVar18 = "GI_800";
        }
        printk("HT_GI = %s\n",pcVar18);
      }
      iVar10 = FUN_000ee05c(param_1,cVar4);
      cVar4 = cVar4 + '\x01';
      if (iVar10 != 0) {
        wlan_config_set_ht_gi(iVar10,cVar3);
      }
      iVar10 = rstrtok(0,&_LC6);
    } while (iVar10 != 0);
  }
  iVar10 = RTMPGetKeyParameter("HT_LDPC",pcVar13,0x80,param_2,1);
  if ((iVar10 != 0) && (iVar10 = rstrtok(pcVar13,&_LC6), iVar10 != 0)) {
    cVar4 = '\0';
    do {
      uVar2 = os_str_tol(iVar10,0,10);
      iVar10 = FUN_000ee05c(param_1,cVar4);
      if (iVar10 != 0) {
        wlan_config_set_ht_ldpc(iVar10,uVar2);
      }
      iVar10 = rstrtok(0,&_LC6);
      cVar4 = cVar4 + '\x01';
    } while (iVar10 != 0);
  }
  iVar10 = RTMPGetKeyParameter("HT_STBC",pcVar13,0x80,param_2,1);
  if ((iVar10 != 0) && (iVar10 = rstrtok(pcVar13,&_LC6), iVar10 != 0)) {
    cVar4 = '\0';
    do {
      uVar2 = os_str_tol(iVar10,0,10);
      iVar10 = FUN_000ee05c(param_1,cVar4);
      if (iVar10 != 0) {
        wlan_config_set_ht_stbc(iVar10,uVar2);
      }
      iVar10 = rstrtok(0,&_LC6);
      cVar4 = cVar4 + '\x01';
    } while (iVar10 != 0);
  }
  iVar10 = RTMPGetKeyParameter("HT_MpduDensity",pcVar13,0x80,param_2,1);
  if ((iVar10 != 0) && (iVar10 = rstrtok(pcVar13,&_LC6), iVar10 != 0)) {
    cVar4 = '\0';
    do {
      bVar6 = os_str_tol(iVar10,0,10);
      if (7 < bVar6) {
        bVar6 = 4;
      }
      if (3 < DebugLevel) {
        printk("HT: MPDU Density = %d\n",bVar6);
      }
      iVar10 = FUN_000ee05c(param_1,cVar4);
      cVar4 = cVar4 + '\x01';
      if (iVar10 != 0) {
        wlan_config_set_min_mpdu_start_space(iVar10,bVar6);
      }
      iVar10 = rstrtok(0,&_LC6);
    } while (iVar10 != 0);
  }
  cVar4 = '\0';
  iVar10 = RTMPGetKeyParameter("HT_40MHZ_INTOLERANT",pcVar13,0x80,param_2,0);
  if (iVar10 != 0) {
    iVar10 = rstrtok(pcVar13,&_LC6);
    while (iVar10 != 0) {
      uVar2 = os_str_tol(iVar10,0,10);
      if (3 < DebugLevel) {
        printk("HT: 40MHZ INTOLERANT = %d\n",uVar2);
      }
      iVar10 = FUN_000ee05c(param_1,cVar4);
      cVar4 = cVar4 + '\x01';
      if (iVar10 != 0) {
        wlan_config_set_40M_intolerant(iVar10,uVar2);
      }
      iVar10 = rstrtok(0,&_LC6);
    }
  }
  iVar10 = RTMPGetKeyParameter("HT_AMSDU",pcVar13,0x40,param_2,1);
  if ((iVar10 != 0) && (iVar10 = rstrtok(pcVar13,&_LC6), iVar10 != 0)) {
    cVar4 = '\0';
    do {
      uVar2 = os_str_tol(iVar10,0,10);
      iVar10 = FUN_000ee05c(param_1,cVar4);
      if (iVar10 != 0) {
        wlan_config_set_amsdu_en(iVar10,uVar2);
      }
      iVar10 = rstrtok(0,&_LC6);
      cVar4 = cVar4 + '\x01';
    } while (iVar10 != 0);
  }
  uVar21 = 1;
  iVar10 = RTMPGetKeyParameter("AMSDU_NUM",pcVar13,0x40,param_2,1);
  if ((iVar10 != 0) && (iVar10 = rstrtok(pcVar13,&_LC6), iVar10 != 0)) {
    cVar4 = '\0';
    do {
      bVar6 = os_str_tol(iVar10,0,10);
      if (bVar6 < 3) {
        uVar21 = 0;
      }
      else if (4 < bVar6) {
        uVar21 = 2;
      }
      iVar10 = FUN_000ee05c(param_1,cVar4);
      cVar4 = cVar4 + '\x01';
      if (iVar10 != 0) {
        wlan_config_set_vht_max_mpdu_len(iVar10,uVar21);
      }
      iVar10 = rstrtok(0,&_LC6);
    } while (iVar10 != 0);
  }
  iVar10 = RTMPGetKeyParameter("HT_MIMOPSMode",pcVar13,0x40,param_2,1);
  if ((iVar10 != 0) && (iVar10 = rstrtok(pcVar13,&_LC6), iVar10 != 0)) {
    local_b8 = 0;
    do {
      uVar2 = os_str_tol(iVar10,0,10);
      if (3 < DebugLevel) {
        printk("HT: MIMOPS Mode  = %d\n",uVar2);
      }
      if (*(char *)((int)param_1 + 0x286285) == '\x01') {
        if (*(char *)((int)param_1 + 0x2b7242) != '\0') {
          iVar10 = 0;
          pbVar29 = (byte *)((int)param_1 + 0x3678c7);
          do {
            while( true ) {
              pbVar29 = pbVar29 + 1;
              bVar6 = *pbVar29;
              iVar10 = iVar10 + 1;
              iVar11 = FUN_000edfd8(param_1,param_1 + (uint)bVar6 * 0x160d + 0xadc92,local_b8 & 0xff
                                   );
              if (iVar11 == 0) break;
              wlan_config_set_mmps(param_1 + (uint)bVar6 * 0x160d + 0xadc92,uVar2);
              if ((int)(uint)*(byte *)((int)param_1 + 0x2b7242) <= iVar10) goto LAB_000f5a1c;
            }
          } while (iVar10 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242));
          goto LAB_000f5a1c;
        }
      }
      else {
LAB_000f5a1c:
        if (*(char *)((int)param_1 + 0x286285) == '\0') {
          iVar10 = FUN_000edfd8(param_1,param_1 + 0xdb6d6,local_b8 & 0xff);
          if (iVar10 != 0) {
            wlan_config_set_mmps(param_1 + 0xdb6d6,uVar2);
          }
          iVar10 = FUN_000edfd8(param_1,param_1 + 0x1604c2,local_b8 & 0xff);
          if (iVar10 != 0) {
            wlan_config_set_mmps(param_1 + 0x1604c2,uVar2);
          }
        }
      }
      local_b8 = local_b8 + 1;
      iVar10 = rstrtok(0,&_LC6);
    } while (local_b8 != 3 && iVar10 != 0);
  }
  iVar10 = RTMPGetKeyParameter("HT_BADecline",pcVar13,0x40,param_2,1);
  if (iVar10 == 0) {
LAB_000f3ed8:
    uVar9 = 0;
  }
  else {
    iVar10 = rstrtok(pcVar13,&_LC6);
    if (iVar10 == 0) {
      if (3 < DebugLevel) {
        uVar9 = 0;
        pcVar18 = "Disable";
        goto LAB_000ffd80;
      }
      goto LAB_000f3ed8;
    }
    cVar4 = '\0';
    do {
      uVar9 = os_str_tol(iVar10,0,10);
      iVar10 = FUN_000ee05c(param_1,cVar4);
      if (iVar10 != 0) {
        wlan_config_set_ba_decline(iVar10,uVar9 & 0xff);
      }
      iVar10 = rstrtok(0,&_LC6);
      cVar4 = cVar4 + '\x01';
    } while (iVar10 != 0);
    if (3 < DebugLevel) {
      pcVar18 = "Enable";
      if (uVar9 == 0) {
        pcVar18 = "Disable";
      }
LAB_000ffd80:
      printk("HT: BA Decline  = %s\n",pcVar18);
    }
  }
  iVar10 = RTMPGetKeyParameter("HT_AutoBA",pcVar13,0x40,param_2,1);
  if (iVar10 != 0) {
    iVar10 = rstrtok(pcVar13,&_LC6);
    if (iVar10 != 0) {
      cVar4 = '\0';
      do {
        uVar9 = os_str_tol(iVar10,0,10);
        iVar10 = FUN_000ee05c(param_1,cVar4);
        if (iVar10 != 0) {
          wlan_config_set_ba_enable(iVar10,uVar9 & 0xff);
        }
        iVar10 = rstrtok(0,&_LC6);
        cVar4 = cVar4 + '\x01';
      } while (iVar10 != 0);
    }
    if (3 < DebugLevel) {
      pcVar18 = "Disable";
      if (uVar9 != 0) {
        pcVar18 = "Enable";
      }
      printk("HT: Auto BA  = %s\n",pcVar18);
    }
  }
  iVar10 = RTMPGetKeyParameter("HT_BAWinSize",pcVar13,0x80,param_2,1);
  if ((iVar10 != 0) && (iVar10 = rstrtok(pcVar13,&_LC6), iVar10 != 0)) {
    uVar26 = 0;
    do {
      uVar8 = os_str_tol(iVar10,0,10);
      iVar10 = FUN_000ee05c(param_1,uVar26 & 0xff);
      if (iVar10 != 0) {
        wlan_config_set_ba_txrx_wsize(iVar10,uVar8,uVar8);
      }
      if (3 < DebugLevel) {
        printk("HT_BAWinSize: wdev[%d]: (TX=%d, RX=%d)\n",uVar26,uVar8,uVar8);
      }
      uVar26 = uVar26 + 1;
      iVar10 = rstrtok(0,&_LC6);
    } while (iVar10 != 0);
  }
  iVar10 = RTMPGetKeyParameter("FixedMcs",pcVar13,0x80,param_2,1);
  if ((iVar10 != 0) && (iVar10 = rstrtok(pcVar13,&_LC6), iVar10 != 0)) {
    uVar26 = 0;
    do {
      uVar2 = os_str_tol(iVar10,0,10);
      iVar10 = FUN_000ee05c(param_1,uVar26 & 0xff);
      if (iVar10 != 0) {
        wlan_config_set_fixed_mcs(iVar10,uVar2);
      }
      if (-1 < DebugLevel) {
        printk("WDEV[%d], FixedMcs = %d\n",uVar26,uVar2);
      }
      uVar26 = uVar26 + 1;
      iVar10 = rstrtok(0,&_LC6);
    } while (iVar10 != 0);
  }
  iVar10 = RTMPGetKeyParameter("HT_RDG",pcVar13,0x19,param_2,1);
  if (iVar10 != 0) {
    iVar10 = os_str_tol(pcVar13,0,10);
    if (iVar10 == 0) {
      *(undefined1 *)((int)param_1 + 0x79507d) = 0;
      if (3 < DebugLevel) {
        uVar26 = 0xc6b0;
LAB_000f9fe0:
        printk("HT: RDG = %s\n",uVar26 | 0x2d0000);
      }
    }
    else {
      uVar26 = hc_get_asic_cap(param_1[0x29e5e8]);
      if ((uVar26 & 0x4000) == 0) {
        *(undefined1 *)((int)param_1 + 0x79507d) = 0;
      }
      else {
        *(undefined1 *)((int)param_1 + 0x79507d) = 1;
      }
      if (3 < DebugLevel) {
        uVar26 = 0xd080;
        goto LAB_000f9fe0;
      }
    }
  }
  iVar10 = RTMPGetKeyParameter("FixedTxMode",pcVar13,0x40,param_2,1);
  if (iVar10 != 0) {
    if ((*(char *)((int)param_1 + 0x286285) == '\x01') &&
       (iVar10 = rstrtok(pcVar13,&_LC6), iVar10 != 0)) {
      pbVar29 = (byte *)((int)param_1 + 0x3678c7);
      iVar11 = 0;
      do {
        iVar12 = hc_get_chip_bcn_max_num(param_1[0x29e5e8]);
        if (iVar12 <= iVar11) break;
        pbVar29 = pbVar29 + 1;
        bVar6 = *pbVar29;
        bVar5 = RT_CfgSetFixedTxPhyMode(iVar10);
        *(byte *)((int)param_1 + (uint)bVar6 * 0x5834 + 0x2b7af7) =
             *(byte *)((int)param_1 + (uint)bVar6 * 0x5834 + 0x2b7af7) & 199 | (bVar5 & 7) << 3;
        if (3 < DebugLevel) {
          printk("(IF-ra%d) Fixed Tx Mode = %d\n",iVar11,
                 ((uint)*(byte *)((int)param_1 + (uint)*pbVar29 * 0x5834 + 0x2b7af7) << 0x1a) >>
                 0x1d);
        }
        iVar11 = iVar11 + 1;
        iVar10 = rstrtok(0,&_LC6);
      } while (iVar10 != 0);
    }
    if (*(char *)((int)param_1 + 0x286285) == '\0') {
      bVar6 = RT_CfgSetFixedTxPhyMode(pcVar13);
      *(byte *)((int)param_1 + 0x36e407) =
           *(byte *)((int)param_1 + 0x36e407) & 199 | (bVar6 & 7) << 3;
      if (3 < DebugLevel) {
        printk("Fixed Tx Mode = %d\n");
      }
    }
  }
  iVar10 = RTMPGetKeyParameter("HT_EXTCHA",pcVar13,0x40,param_2,1);
  if (iVar10 != 0) {
    iVar10 = os_str_tol(pcVar13,0,10);
    if (*(char *)((int)param_1 + 0x286285) == '\0') {
      piVar25 = param_1 + 0xdb6d6;
      if (iVar10 == 0) {
        uVar21 = 3;
      }
      else {
        uVar21 = 1;
      }
      wlan_config_set_ext_cha(piVar25,uVar21);
      iVar11 = wlan_config_get_ext_cha(piVar25);
      if (iVar11 == 0xf) {
        wlan_config_set_ext_cha(piVar25,uVar21);
      }
      iVar11 = wlan_config_get_ext_cha(param_1 + 0x1604c2);
      if (iVar11 == 0xf) {
        wlan_config_set_ext_cha(param_1 + 0x1604c2,uVar21);
      }
      if (3 < DebugLevel) {
        pcVar18 = "BELOW";
        if (iVar10 != 0) {
          pcVar18 = "ABOVE";
        }
        printk("HT: Ext Channel = %s\n",pcVar18);
      }
    }
    iVar10 = rstrtok(pcVar13,&_LC6);
    if (iVar10 != 0) {
      pbVar29 = (byte *)(param_1 + 0xd9e32);
      iVar11 = 0;
      do {
        iVar12 = hc_get_chip_bcn_max_num(param_1[0x29e5e8]);
        if (iVar12 <= iVar11) break;
        iVar10 = os_str_tol(iVar10,0,10);
        if (*(char *)((int)param_1 + 0x286285) == '\x01') {
          if (iVar10 == 0) {
            wlan_config_set_ext_cha(param_1 + (uint)*pbVar29 * 0x160d + 0xadc92,3);
            if (3 < DebugLevel) {
              pcVar18 = "BELOW";
LAB_000f7c94:
              printk("HT: WDEV[%x] Ext Channel = %s\n",iVar11,pcVar18);
            }
          }
          else {
            wlan_config_set_ext_cha(param_1 + (uint)*pbVar29 * 0x160d + 0xadc92);
            if (3 < DebugLevel) {
              pcVar18 = "ABOVE";
              goto LAB_000f7c94;
            }
          }
        }
        iVar11 = iVar11 + 1;
        iVar10 = rstrtok(0,&_LC6);
        pbVar29 = pbVar29 + 1;
      } while (iVar10 != 0);
    }
    uVar21 = wlan_config_get_ext_cha(param_1 + 0xadc92);
    if (*(char *)((int)param_1 + 0x2b7242) != '\0') {
      iVar10 = 0;
      pbVar29 = (byte *)((int)param_1 + 0x3678c7);
      do {
        pbVar29 = pbVar29 + 1;
        bVar6 = *pbVar29;
        iVar10 = iVar10 + 1;
        iVar11 = wlan_config_get_ext_cha(param_1 + (uint)bVar6 * 0x160d + 0xadc92);
        if (iVar11 == 0xf) {
          wlan_config_set_ext_cha(param_1 + (uint)bVar6 * 0x160d + 0xadc92,uVar21);
        }
      } while (iVar10 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242));
    }
  }
  iVar10 = RTMPGetKeyParameter("HT_MCS",pcVar13,0x32,param_2,1);
  if (iVar10 != 0) {
    if ((*(char *)((int)param_1 + 0x286285) == '\x01') &&
       (iVar10 = rstrtok(pcVar13,&_LC6), iVar10 != 0)) {
      pbVar29 = (byte *)((int)param_1 + 0x3678c7);
      iVar11 = 0;
      do {
        iVar12 = hc_get_chip_bcn_max_num(param_1[0x29e5e8]);
        if (iVar12 <= iVar11) break;
        pbVar29 = pbVar29 + 1;
        uVar19 = (uint)*pbVar29;
        uVar26 = os_str_tol(iVar10,0,10);
        if (uVar26 < 0x21) {
          *(byte *)((int)param_1 + uVar19 * 0x5834 + 0x2b7af6) =
               *(byte *)((int)param_1 + uVar19 * 0x5834 + 0x2b7af6) & 0x80 | (byte)uVar26 & 0x7f;
        }
        else {
          *(byte *)((int)param_1 + uVar19 * 0x5834 + 0x2b7af6) =
               *(byte *)((int)param_1 + uVar19 * 0x5834 + 0x2b7af6) & 0x80 | 0x21;
        }
        if (3 < DebugLevel) {
          pcVar18 = "AUTO";
          if ((*(byte *)((int)param_1 + uVar19 * 0x5834 + 0x2b7af6) & 0x7f) != 0x21) {
            pcVar18 = "Fixed";
          }
          printk("(IF-ra%d) HT: MCS = %s(%d)\n",iVar11,pcVar18,
                 *(byte *)((int)param_1 + uVar19 * 0x5834 + 0x2b7af6) & 0x7f);
        }
        iVar11 = iVar11 + 1;
        iVar10 = rstrtok(0,&_LC6);
      } while (iVar10 != 0);
    }
    if (*(char *)((int)param_1 + 0x286285) == '\0') {
      uVar26 = os_str_tol(pcVar13,0,10);
      iVar10 = DebugLevel;
      if (uVar26 < 0x21) {
        *(undefined1 *)(param_1 + 0xdb902) = 0;
        *(byte *)((int)param_1 + 0x36e406) =
             *(byte *)((int)param_1 + 0x36e406) & 0x80 | (byte)uVar26 & 0x7f;
        if (3 < iVar10) {
          printk("HT: MCS = %d\n");
        }
      }
      else {
        *(undefined1 *)(param_1 + 0xdb902) = 1;
        *(byte *)((int)param_1 + 0x36e406) = *(byte *)((int)param_1 + 0x36e406) & 0x80 | 0x21;
        if (3 < iVar10) {
          printk("HT: MCS = AUTO\n");
        }
      }
    }
  }
  iVar10 = RTMPGetKeyParameter("GreenAP",pcVar13,10,param_2,1);
  if (iVar10 != 0) {
    iVar10 = os_str_tol(pcVar13,0,10);
    greenap_set_capability(param_1,iVar10 != 0);
    if (3 < DebugLevel) {
      uVar21 = greenap_get_capability(param_1);
      printk("HT: greenap_cap = %d\n",uVar21);
    }
  }
  iVar10 = RTMPGetKeyParameter("PcieAspm",pcVar13,10,param_2,1);
  if (iVar10 != 0) {
    iVar10 = os_str_tol(pcVar13,0,10);
    set_pcie_aspm_dym_ctrl_cap(param_1,iVar10 != 0);
    if (3 < DebugLevel) {
      iVar11 = param_1[0xa5b19];
      uVar21 = get_pcie_aspm_dym_ctrl_cap(param_1);
      printk("ChipI=%x, Value=%d, pcie_aspm in profile=%d\n",iVar11,iVar10,uVar21);
    }
  }
  iVar10 = RTMPGetKeyParameter("TWTSupport",pcVar13,0x10,param_2,1);
  if (iVar10 != 0) {
    bVar6 = os_str_tol(pcVar13,0,10);
    bVar39 = bVar6 == 2;
    if (bVar6 < 3) {
      bVar39 = *(char *)((int)param_1 + 0x286285) == '\0';
    }
    if (bVar39) {
      wlan_config_set_he_twt_support(param_1 + 0xdb6d6,bVar6);
      wlan_config_set_he_twt_support(param_1 + 0x1604c2,bVar6);
    }
    if ((*(char *)((int)param_1 + 0x286285) == '\x01' && bVar6 < 3) &&
       (*(char *)((int)param_1 + 0x2b7242) != '\0')) {
      iVar10 = 0;
      pbVar29 = (byte *)((int)param_1 + 0x3678c7);
      do {
        pbVar29 = pbVar29 + 1;
        iVar10 = iVar10 + 1;
        wlan_config_set_he_twt_support(param_1 + (uint)*pbVar29 * 0x160d + 0xadc92,bVar6);
      } while (iVar10 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242));
    }
    if (3 < DebugLevel) {
      printk("ChipID=%x, TWTSupport in profile=%d\n",param_1[0xa5b19],bVar6);
    }
  }
  iVar10 = RTMPGetKeyParameter("HT_DisallowTKIP",pcVar13,0x19,param_2,1);
  if (iVar10 != 0) {
    iVar10 = os_str_tol(pcVar13,0,10);
    if (iVar10 == 1) {
      *(undefined1 *)(param_1 + 0x1e5661) = 1;
      if (3 < DebugLevel) {
        puVar32 = &_LC132;
        goto LAB_000fa4b8;
      }
    }
    else {
      *(undefined1 *)(param_1 + 0x1e5661) = 0;
      if (3 < DebugLevel) {
        puVar32 = &_LC133;
LAB_000fa4b8:
        printk("HT: Disallow TKIP mode = %s\n",puVar32);
      }
    }
  }
  iVar10 = RTMPGetKeyParameter("OBSSScanParam",pcVar13,0x20,param_2,1);
  if (iVar10 == 0) goto LAB_000f40fc;
  iVar10 = rstrtok(pcVar13,&_LC6);
  if (iVar10 == 0) {
LAB_000fb208:
    if (-1 < DebugLevel) {
      printk("Wrong OBSSScanParamtetrs format in dat file!!!!! Use default value.\n");
    }
    *(undefined2 *)((int)param_1 + 0x79569e) = 0x14;
    *(undefined2 *)(param_1 + 0x1e55a8) = 10;
    *(undefined2 *)((int)param_1 + 0x7956a6) = 0x14;
    *(undefined2 *)((int)param_1 + 0x7956a2) = 300;
    *(undefined2 *)(param_1 + 0x1e55a9) = 200;
    *(undefined2 *)(param_1 + 0x1e55aa) = 5;
    *(undefined2 *)((int)param_1 + 0x7956aa) = 0x19;
  }
  else {
    iVar11 = 0;
    do {
      iVar12 = os_str_tol(iVar10,0,10);
      iVar10 = DebugLevel;
      switch(iVar11) {
      case 0:
        if (iVar12 - 5U < 0x3e4) {
          *(short *)((int)param_1 + 0x79569e) = (short)iVar12;
          if (3 < iVar10) {
            printk("OBSSScanParam for Dot11OBssScanPassiveDwell=%d\n");
          }
        }
        else if (-1 < DebugLevel) {
          printk("Invalid OBSSScanParam for Dot11OBssScanPassiveDwell(%d), should in range 5~1000\n"
                );
        }
        iVar10 = rstrtok(0,&_LC6);
        if (iVar10 == 0) goto LAB_000fb208;
        iVar12 = os_str_tol(iVar10,0,10);
        break;
      case 1:
        break;
      case 2:
        goto switchD_000f8140_caseD_2;
      case 3:
        goto switchD_000f8140_caseD_3;
      case 4:
        goto switchD_000f8140_caseD_4;
      case 5:
        goto switchD_000f8140_caseD_5;
      case 6:
        goto switchD_000f8140_caseD_6;
      default:
        goto switchD_000f8140_default;
      }
      iVar10 = DebugLevel;
      if (iVar12 - 10U < 0x3df) {
        *(short *)(param_1 + 0x1e55a8) = (short)iVar12;
        if (3 < iVar10) {
          printk("OBSSScanParam for Dot11OBssScanActiveDwell=%d\n");
        }
      }
      else if (-1 < DebugLevel) {
        printk("Invalid OBSSScanParam for Dot11OBssScanActiveDwell(%d), should in range 10~1000\n");
      }
      iVar10 = rstrtok(0,&_LC6);
      if (iVar10 == 0) goto LAB_000fb208;
      iVar12 = os_str_tol(iVar10,0,10);
switchD_000f8140_caseD_2:
      iVar10 = DebugLevel;
      *(short *)((int)param_1 + 0x7956a2) = (short)iVar12;
      if (3 < iVar10) {
        printk("OBSSScanParam for Dot11BssWidthTriggerScanInt=%d\n");
      }
      iVar10 = rstrtok(0,&_LC6);
      if (iVar10 == 0) goto LAB_000fb208;
      iVar12 = os_str_tol(iVar10,0,10);
switchD_000f8140_caseD_3:
      iVar10 = DebugLevel;
      if (iVar12 - 200U < 0x2649) {
        *(short *)(param_1 + 0x1e55a9) = (short)iVar12;
        if (3 < iVar10) {
          printk("OBSSScanParam for Dot11OBssScanPassiveTotalPerChannel=%d\n");
        }
      }
      else if (-1 < DebugLevel) {
        printk(
              "Invalid OBSSScanParam for Dot11OBssScanPassiveTotalPerChannel(%d), should in range 200~10000\n"
              );
      }
      iVar10 = rstrtok(0,&_LC6);
      if (iVar10 == 0) goto LAB_000fb208;
      iVar12 = os_str_tol(iVar10,0,10);
switchD_000f8140_caseD_4:
      iVar10 = DebugLevel;
      if (iVar12 - 0x14U < 0x26fd) {
        *(short *)((int)param_1 + 0x7956a6) = (short)iVar12;
        if (3 < iVar10) {
          printk("OBSSScanParam for Dot11OBssScanActiveTotalPerChannel=%d\n");
        }
      }
      else if (-1 < DebugLevel) {
        printk(
              "Invalid OBSSScanParam for Dot11OBssScanActiveTotalPerChannel(%d), should in range 20~10000\n"
              );
      }
      iVar10 = rstrtok(0,&_LC6);
      if (iVar10 == 0) goto LAB_000fb208;
      iVar12 = os_str_tol(iVar10,0,10);
switchD_000f8140_caseD_5:
      iVar10 = DebugLevel;
      *(short *)(param_1 + 0x1e55aa) = (short)iVar12;
      if (3 < iVar10) {
        printk("OBSSScanParam for Dot11BssWidthChanTranDelayFactor=%d\n");
      }
      iVar10 = rstrtok(0,&_LC6);
      if (iVar10 == 0) goto LAB_000fb208;
      iVar12 = os_str_tol(iVar10,0,10);
switchD_000f8140_caseD_6:
      iVar10 = DebugLevel;
      *(short *)((int)param_1 + 0x7956aa) = (short)iVar12;
      if (iVar10 < 4) {
        iVar11 = 6;
      }
      else {
        iVar11 = 6;
        printk("OBSSScanParam for Dot11BssWidthChanTranDelayFactor=%d\n");
      }
switchD_000f8140_default:
      iVar11 = iVar11 + 1;
      iVar10 = rstrtok(0,&_LC6);
    } while (iVar10 != 0);
    if (iVar11 != 7) goto LAB_000fb208;
  }
  iVar10 = DebugLevel;
  param_1[0x1e55ab] =
       (uint)*(ushort *)((int)param_1 + 0x7956a2) * (uint)*(ushort *)(param_1 + 0x1e55aa);
  if (3 < iVar10) {
    printk("OBSSScanParam for Dot11BssWidthChanTranDelay=%ld\n");
  }
LAB_000f40fc:
  iVar10 = RTMPGetKeyParameter("HT_BSSCoexistence",pcVar13,0x19,param_2,1);
  if (iVar10 != 0) {
    iVar11 = os_str_tol(pcVar13,0,10);
    iVar10 = DebugLevel;
    *(bool *)((int)param_1 + 0x79564e) = iVar11 == 1;
    if (3 < iVar10) {
      puVar32 = &_LC132;
      if (iVar11 != 1) {
        puVar32 = &_LC133;
      }
      printk("HT: 20/40 BssCoexSupport = %s\n",puVar32);
    }
  }
  iVar10 = RTMPGetKeyParameter("HT_BSSCoexApCntThr",pcVar13,0x19,param_2,1);
  if (iVar10 != 0) {
    uVar2 = os_str_tol(pcVar13,0,10);
    iVar10 = DebugLevel;
    *(undefined1 *)((int)param_1 + 0x79564f) = uVar2;
    if (3 < iVar10) {
      printk("HT: 20/40 BssCoexApCntThr = %d\n",uVar2);
    }
  }
  iVar10 = RTMPGetKeyParameter("BurstMode",pcVar13,0x19,param_2,1);
  if (iVar10 != 0) {
    iVar11 = os_str_tol(pcVar13,0,10);
    iVar10 = DebugLevel;
    *(bool *)((int)param_1 + 0x795951) = iVar11 == 1;
    if (3 < iVar10) {
      printk("HT: RaBurstMode= %d\n");
    }
  }
  iVar10 = RTMPGetKeyParameter("TXRX_RXV_ON",pcVar13,0x19,param_2,1);
  if (iVar10 != 0) {
    iVar10 = os_str_tol(pcVar13,0,10);
    *(char *)((int)param_1 + 0x795b0d) = (char)iVar10;
    if (3 < DebugLevel) {
      puVar32 = &_LC132;
      if (iVar10 != 1) {
        puVar32 = &_LC133;
      }
      printk("TXRX_RXV_ON = %s\n",puVar32);
    }
  }
  pcVar13 = local_74;
  iVar10 = RTMPGetKeyParameter("VHT_BW",local_74,0x40,param_2,1);
  if ((iVar10 != 0) && (iVar10 = rstrtok(pcVar13,&_LC6), iVar10 != 0)) {
    uVar26 = 0;
    do {
      uVar27 = 0;
      uVar19 = os_str_tol(iVar10,0,10);
      if ((((int)uVar19 < 4) && (uVar27 = uVar19 & 0xff, *(char *)((int)param_1 + 0x79504d) != '\0')
          ) && (1 < uVar27)) {
        uVar27 = 1;
      }
      iVar10 = FUN_000ee05c(param_1,uVar26 & 0xff);
      if (iVar10 != 0) {
        wlan_config_set_vht_bw(iVar10,uVar27);
      }
      if (3 < DebugLevel) {
        uVar21 = VhtBw2Str(uVar27);
        printk("wdev[%d] VHT: Channel Width = %s MHz\n",uVar26,uVar21);
      }
      uVar26 = uVar26 + 1;
      iVar10 = rstrtok(0,&_LC6);
    } while (iVar10 != 0);
  }
  iVar10 = RTMPGetKeyParameter("VHT_SGI",pcVar13,0x80,param_2,1);
  if ((iVar10 != 0) && (iVar10 = rstrtok(pcVar13,&_LC6), iVar10 != 0)) {
    cVar4 = '\0';
    do {
      uVar26 = os_str_tol(iVar10,0,10);
      iVar10 = FUN_000ee05c(param_1,cVar4);
      if ((iVar10 != 0) && (wlan_config_set_vht_sgi(iVar10,uVar26 & 0xff), 3 < DebugLevel)) {
        pcVar18 = "Disabled";
        if (uVar26 != 0) {
          pcVar18 = "Enable";
        }
        printk("VHT: Short GI for 80Mhz/160Mhz  = %s\n",pcVar18);
      }
      iVar10 = rstrtok(0,&_LC6);
      cVar4 = cVar4 + '\x01';
    } while (iVar10 != 0);
  }
  iVar10 = RTMPGetKeyParameter("VHT_STBC",pcVar13,0x80,param_2,1);
  if ((iVar10 != 0) && (iVar10 = rstrtok(pcVar13,&_LC6), iVar10 != 0)) {
    cVar4 = '\0';
    do {
      uVar2 = os_str_tol(iVar10,0,10);
      iVar10 = FUN_000ee05c(param_1,cVar4);
      if (iVar10 != 0) {
        wlan_config_set_vht_stbc(iVar10,uVar2);
      }
      iVar10 = rstrtok(0,&_LC6);
      cVar4 = cVar4 + '\x01';
    } while (iVar10 != 0);
  }
  iVar10 = RTMPGetKeyParameter("VHT_LDPC",pcVar13,0x80,param_2,1);
  if ((iVar10 != 0) && (iVar10 = rstrtok(pcVar13,&_LC6), iVar10 != 0)) {
    cVar4 = '\0';
    do {
      uVar2 = os_str_tol(iVar10,0,10);
      iVar10 = FUN_000ee05c(param_1,cVar4);
      if (iVar10 != 0) {
        wlan_config_set_vht_ldpc(iVar10,uVar2);
      }
      iVar10 = rstrtok(0,&_LC6);
      cVar4 = cVar4 + '\x01';
    } while (iVar10 != 0);
  }
  local_48 = &DAT_002df900;
  local_44 = "STATIC";
  local_40 = "DYNAMIC";
  iVar10 = RTMPGetKeyParameter("VHT_BW_SIGNAL",pcVar13,0x80,param_2,1);
  if ((iVar10 != 0) && (iVar10 = rstrtok(pcVar13,&_LC6), iVar10 != 0)) {
    cVar4 = '\0';
    do {
      uVar26 = os_str_tol(iVar10,0,10);
      iVar10 = FUN_000ee05c(param_1,cVar4);
      if (iVar10 != 0) {
        if (uVar26 < 3) {
          wlan_config_set_vht_bw_sig(iVar10,uVar26 & 0xff);
          if ((param_1[0xa5b19] & 0xffffU) == 0x7615) {
            local_58 = 0;
            if (uVar26 == 0) goto LAB_000f5648;
            mac_io_read32(param_1[0x29e5e8],0x820f4000,&local_58);
            local_58 = local_58 | 0x200000;
            mac_io_write32(param_1[0x29e5e8],0x820f4000);
            if (uVar26 == 2) {
              mac_io_write32(param_1[0x29e5e8],0x820f2040,0x2020202);
            }
            else {
              uVar26 = 1;
            }
          }
        }
        else {
          wlan_config_set_vht_bw_sig(iVar10,0);
          if ((param_1[0xa5b19] & 0xffffU) == 0x7615) {
LAB_000f5648:
            local_58 = 0;
            mac_io_read32(param_1[0x29e5e8],0x820f4000,&local_58);
            uVar26 = 0;
            local_58 = local_58 & 0xffdfffff;
            mac_io_write32(param_1[0x29e5e8],0x820f4000);
            mac_io_write32(param_1[0x29e5e8],0x820f2040,0);
          }
          else {
            uVar26 = 0;
          }
        }
        if (3 < DebugLevel) {
          printk("VHT: BW SIGNALING = %s\n",(&local_48)[uVar26]);
        }
      }
      cVar4 = cVar4 + '\x01';
      iVar10 = rstrtok(0,&_LC6);
    } while (iVar10 != 0);
  }
  iVar10 = RTMPGetKeyParameter("VHT_DisallowNonVHT",pcVar13,0x19,param_2,1);
  if (iVar10 != 0) {
    iVar11 = os_str_tol(pcVar13,0,10);
    iVar10 = DebugLevel;
    *(bool *)(param_1 + 0x1e565b) = iVar11 != 0;
    if (3 < iVar10) {
      printk("VHT: VHT_DisallowNonVHT = %d\n",(char)param_1[0x1e565b]);
    }
  }
  iVar10 = RTMPGetKeyParameter("VHT_Sec80_Channel",pcVar13,0x40,param_2,1);
  if ((iVar10 != 0) && (iVar10 = rstrtok(pcVar13,&_LC6), iVar10 != 0)) {
    uVar21 = 0;
    uVar26 = 0;
    do {
      uVar19 = os_str_tol(pcVar13,0,10);
      iVar10 = FUN_000ee05c(param_1,uVar26 & 0xff);
      if (iVar10 != 0) {
        uVar21 = wlan_config_get_ch_band();
        uVar21 = vht_cent_ch_freq(uVar19 & 0xff,1,uVar21);
        wlan_config_set_cen_ch_2(iVar10,uVar21);
      }
      if (3 < DebugLevel) {
        printk("wdev[%d] VHT: Secondary80 = %ld, Center = %d\n",uVar26,uVar19,uVar21);
      }
      uVar26 = uVar26 + 1;
      iVar10 = rstrtok(0,&_LC6);
    } while (iVar10 != 0);
  }
  iVar10 = RTMPGetKeyParameter("G_BAND_256QAM",pcVar13,0x19,param_2,1);
  if (iVar10 != 0) {
    iVar11 = os_str_tol(pcVar13,0,10);
    iVar10 = DebugLevel;
    *(bool *)((int)param_1 + 0x79505f) = iVar11 != 0;
    if (3 < iVar10) {
      printk("VHT: G_BAND_256QAM = %ld\n",iVar11);
    }
  }
  iVar10 = RTMPGetKeyParameter("UseVhtRateFor2g",pcVar13,0x19,param_2,1);
  if (iVar10 != 0) {
    iVar11 = os_str_tol(pcVar13,0,10);
    iVar10 = DebugLevel;
    *(bool *)(param_1 + 0x1e5418) = iVar11 != 0;
    if (3 < iVar10) {
      printk("VHT: UseVhtRateFor2g = %ld\n",iVar11);
    }
  }
  pcVar13 = local_74;
  iVar10 = RTMPGetKeyParameter("HeLdpc",local_74,0x80,param_2,1);
  if ((iVar10 != 0) && (iVar10 = rstrtok(pcVar13,&_LC6), iVar10 != 0)) {
    uVar26 = 0;
    do {
      uVar19 = os_str_tol(iVar10,0,10);
      iVar10 = FUN_000ee05c(param_1,uVar26 & 0xff);
      if ((iVar10 != 0) && (wlan_config_set_he_ldpc(iVar10,uVar19 & 0xff), 3 < DebugLevel)) {
        printk("WDEV[%d], HeLdpc = %d\n",uVar26,uVar19);
      }
      uVar26 = uVar26 + 1;
      iVar10 = rstrtok(0,&_LC6);
    } while (iVar10 != 0);
  }
  sVar7 = hc_get_chip_bcn_max_num(param_1[0x29e5e8]);
  iVar10 = RTMPGetKeyParameter("FgiFltf",pcVar13,(int)sVar7 << 3,param_2,1);
  if ((iVar10 != 0) && (iVar10 = rstrtok(pcVar13,&_LC6), iVar10 != 0)) {
    uVar26 = 0;
    do {
      uVar21 = os_str_tol(iVar10,0,10);
      iVar10 = FUN_000ee05c(param_1,uVar26 & 0xff);
      if ((iVar10 != 0) && (set_fgi_and_ltf_profile(param_1,iVar10,uVar21), 3 < DebugLevel)) {
        printk("WDEV[%d], FgiFltf = %d\n",uVar26,uVar21);
      }
      uVar26 = uVar26 + 1;
      iVar10 = rstrtok(0,&_LC6);
    } while (iVar10 != 0);
  }
  iVar10 = RTMPGetKeyParameter("HE_TXOP_RTS_THLD",pcVar13,0x80,param_2,1);
  if ((iVar10 != 0) && (iVar10 = rstrtok(pcVar13,&_LC6), iVar10 != 0)) {
    uVar26 = 0;
    do {
      uVar21 = os_str_tol(iVar10,0,10);
      iVar10 = FUN_000ee05c(param_1,uVar26 & 0xff);
      if ((iVar10 != 0) && (wlan_config_set_he_txop_dur_rts_thld(iVar10,uVar21), -1 < DebugLevel)) {
        printk("WDEV[%d], HE_TXOP_RTS_THLD = %d\n",uVar26,uVar21);
      }
      uVar26 = uVar26 + 1;
      iVar10 = rstrtok(0,&_LC6);
    } while (iVar10 != 0);
  }
  iVar10 = RTMPGetKeyParameter("PPDUTxType",pcVar13,0x80,param_2,1);
  if ((iVar10 != 0) && (iVar10 = rstrtok(pcVar13,&_LC6), iVar10 != 0)) {
    uVar26 = 0;
    do {
      uVar2 = os_str_tol(iVar10,0,10);
      iVar10 = FUN_000ee05c(param_1,uVar26 & 0xff);
      if (iVar10 != 0) {
        wlan_config_set_ppdu_tx_type(iVar10,uVar2);
      }
      if (-1 < DebugLevel) {
        printk("WDEV[%d], PPDUTxType = %d\n",uVar26,uVar2);
      }
      uVar26 = uVar26 + 1;
      iVar10 = rstrtok(0,&_LC6);
    } while (iVar10 != 0);
  }
  iVar10 = RTMPGetKeyParameter("NumUsersOFDMA",pcVar13,0x80,param_2,1);
  if ((iVar10 != 0) && (iVar10 = rstrtok(pcVar13,&_LC6), iVar10 != 0)) {
    uVar26 = 0;
    do {
      uVar2 = os_str_tol(iVar10,0,10);
      iVar10 = FUN_000ee05c(param_1,uVar26 & 0xff);
      if (iVar10 != 0) {
        wlan_config_set_ofdma_user_cnt(iVar10,uVar2);
      }
      if (-1 < DebugLevel) {
        printk("WDEV[%d], NumUsersOFDMA = %d\n",uVar26,uVar2);
      }
      uVar26 = uVar26 + 1;
      iVar10 = rstrtok(0,&_LC6);
    } while (iVar10 != 0);
  }
  iVar10 = RTMPGetKeyParameter("NonTxBSSIndex",pcVar13,0x80,param_2,1);
  if ((iVar10 != 0) && (iVar10 = rstrtok(pcVar13,&_LC6), iVar10 != 0)) {
    cVar4 = '\0';
    do {
      uVar2 = os_str_tol(iVar10,0,10);
      iVar10 = FUN_000ee05c(param_1,cVar4);
      if (iVar10 != 0) {
        wlan_config_set_non_tx_bss_idx(iVar10,uVar2);
      }
      if (-1 < DebugLevel) {
        printk("NonTxBSSIndex = %d\n",uVar2);
      }
      iVar10 = rstrtok(0,&_LC6);
      cVar4 = cVar4 + '\x01';
    } while (iVar10 != 0);
  }
  iVar10 = RTMPGetKeyParameter("OFDMA",pcVar13,0x80,param_2,1);
  if ((iVar10 != 0) && (iVar10 = rstrtok(pcVar13,&_LC6), iVar10 != 0)) {
    cVar4 = '\0';
    do {
      uVar2 = os_str_tol(iVar10,0,10);
      iVar10 = FUN_000ee05c(param_1,cVar4);
      if (iVar10 != 0) {
        wlan_config_set_ofdma_direction(iVar10,uVar2);
      }
      if (-1 < DebugLevel) {
        printk("OFDMA = %d\n",uVar2);
      }
      iVar10 = rstrtok(0,&_LC6);
      cVar4 = cVar4 + '\x01';
    } while (iVar10 != 0);
  }
  if (*(char *)((int)param_1 + 0x286285) == '\x01') {
    pbVar28 = (byte *)(param_1 + 0xd9e32);
    local_48 = (undefined *)0x0;
    local_44 = (char *)0x0;
    local_40 = (char *)0x0;
    local_3c = 0;
    iVar10 = 0;
    pbVar29 = pbVar28;
    while (iVar10 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242)) {
      snprintf((char *)local_ac,0x10,"WscDefaultSSID%d",iVar10 + 1);
      iVar11 = RTMPGetKeyParameter(local_ac,local_74,0x21,param_2,0);
      if (iVar11 != 0) {
        __memzero((char *)((int)param_1 +
                          (int)("Set_WscPinCode_Proc:: Checksum is invalid\n" +
                               (uint)*pbVar29 * 0x5834 + 1)),0x24);
        pcVar13 = local_74;
        sVar14 = strlen(local_74);
        memmove((void *)((int)param_1 + (uint)*pbVar29 * 0x5834 + 0x2baf25),pcVar13,sVar14);
        sVar14 = strlen(pcVar13);
        iVar11 = DebugLevel;
        bVar6 = *pbVar29;
        *(size_t *)((int)param_1 + (uint)bVar6 * 0x5834 + 0x2baf21) = sVar14;
        if (3 < iVar11) {
          printk("WscDefaultSSID[%d]=%s\n",iVar10,
                 (char *)((int)param_1 +
                         (int)("Set_WscPinCode_Proc:: Checksum is invalid\n" +
                              (uint)bVar6 * 0x5834 + 5)));
        }
      }
      pbVar29 = pbVar29 + 1;
      iVar10 = iVar10 + 1;
    }
    iVar10 = RTMPGetKeyParameter("WscConfMode",local_74,0x40,param_2,1);
    if ((iVar10 != 0) && (iVar10 = rstrtok(local_74,&_LC6), iVar10 != 0)) {
      iVar11 = 0;
      pbVar29 = pbVar28;
      do {
        iVar12 = os_str_tol(iVar10,0,10);
        iVar10 = DebugLevel;
        if ((int)(uint)*(byte *)((int)param_1 + 0x2b7242) <= iVar11) break;
        if (iVar12 - 1U < 7) {
          param_1[(uint)*pbVar29 * 0x160d + 0xae14b] = iVar12;
        }
        else {
          param_1[(uint)*pbVar29 * 0x160d + 0xae14b] = 0;
          iVar10 = DebugLevel;
        }
        if (3 < iVar10) {
          printk("I/F(ra%d) WscConfMode=%d\n",iVar11,param_1[(uint)*pbVar29 * 0x160d + 0xae14b]);
        }
        iVar11 = iVar11 + 1;
        iVar10 = rstrtok(0,&_LC6);
        pbVar29 = pbVar29 + 1;
      } while (iVar10 != 0);
    }
    iVar10 = RTMPGetKeyParameter("WscConfStatus",local_74,0x40,param_2,1);
    if (((iVar10 != 0) && (iVar10 = rstrtok(local_74,&_LC6), iVar10 != 0)) &&
       (*(char *)((int)param_1 + 0x2b7242) != '\0')) {
      pbVar29 = (byte *)((int)param_1 + 0x3678c7);
      iVar11 = 0;
      do {
        pbVar29 = pbVar29 + 1;
        bVar6 = *pbVar29;
        uVar2 = os_str_tol(iVar10,0,10);
        iVar10 = DebugLevel;
        *(undefined1 *)(param_1 + (uint)bVar6 * 0x160d + 0xae14d) = uVar2;
        if (3 < iVar10) {
          printk("I/F(ra%d) WscConfStatus=%d\n",iVar11,
                 (char)param_1[(uint)*pbVar29 * 0x160d + 0xae14d]);
        }
        iVar11 = iVar11 + 1;
        iVar10 = rstrtok(0,&_LC6);
      } while ((iVar10 != 0) && (iVar11 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242)));
    }
    pbVar29 = (byte *)((int)param_1 + 0x3678c7);
    iVar10 = RTMPGetKeyParameter("WscConfMethods",local_74,0x40,param_2,1);
    if ((iVar10 != 0) &&
       ((iVar10 = rstrtok(local_74,&_LC6), iVar10 != 0 &&
        (*(char *)((int)param_1 + 0x2b7242) != '\0')))) {
      iVar11 = 0;
      pbVar17 = pbVar29;
      do {
        pbVar17 = pbVar17 + 1;
        bVar6 = *pbVar17;
        uVar8 = os_str_tol(iVar10,0,0x10);
        iVar10 = DebugLevel;
        *(undefined2 *)((int)param_1 + (uint)bVar6 * 0x5834 + 0x2b8536) = uVar8;
        if (3 < iVar10) {
          printk("I/F(ra%d) WscConfMethods=0x%x\n",iVar11,
                 *(undefined2 *)((int)param_1 + (uint)*pbVar17 * 0x5834 + 0x2b8536));
        }
        iVar11 = iVar11 + 1;
        iVar10 = rstrtok(0,&_LC6);
      } while ((iVar10 != 0) && (iVar11 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242)));
    }
    iVar10 = RTMPGetKeyParameter("WscKeyASCII",local_74,0x40,param_2,1);
    if ((iVar10 != 0) &&
       ((iVar10 = rstrtok(local_74,&_LC6), iVar10 != 0 &&
        (*(char *)((int)param_1 + 0x2b7242) != '\0')))) {
      iVar10 = 0;
      pbVar17 = pbVar28;
      do {
        uVar26 = os_str_tol(local_74,0,10);
        if (uVar26 < 2) {
          param_1[(uint)*pbVar17 * 0x160d + 0xaebd2] = uVar26;
        }
        else if (uVar26 - 8 < 0x38) {
          param_1[(uint)*pbVar17 * 0x160d + 0xaebd2] = uVar26;
        }
        else {
          param_1[(uint)*pbVar17 * 0x160d + 0xaebd2] = 8;
        }
        iVar10 = iVar10 + 1;
        if (1 < DebugLevel) {
          printk("WscKeyASCII=%d\n",param_1[(uint)*pbVar17 * 0x160d + 0xaebd2]);
        }
        pbVar17 = pbVar17 + 1;
        iVar11 = rstrtok(0,&_LC6);
      } while ((iVar11 != 0) && (iVar10 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242)));
    }
    iVar10 = RTMPGetKeyParameter("WscSecurityMode",local_74,0x40,param_2,1);
    if (iVar10 != 0) {
      bVar6 = *(byte *)((int)param_1 + 0x2b7242);
      if (bVar6 != 0) {
        pbVar17 = pbVar29;
        do {
          pbVar17 = pbVar17 + 1;
          param_1[(uint)*pbVar17 * 0x160d + 0xaec67] = 3;
        } while (pbVar17 != (byte *)((int)param_1 + bVar6 + 0x3678c7));
      }
      iVar10 = rstrtok(local_74,&_LC6);
      if ((iVar10 != 0) && (*(char *)((int)param_1 + 0x2b7242) != '\0')) {
        iVar11 = 0;
        do {
          iVar10 = os_str_tol(iVar10,0,10);
          if (iVar10 < 4) {
            param_1[(uint)*pbVar28 * 0x160d + 0xaec67] = iVar10;
          }
          if (3 < DebugLevel) {
            printk("RTMPSetProfileParameters I/F(ra%d) WscSecurityMode=%d\n",iVar11,
                   param_1[(uint)*pbVar28 * 0x160d + 0xaec67]);
          }
          iVar11 = iVar11 + 1;
          iVar10 = rstrtok(0,&_LC6);
          pbVar28 = pbVar28 + 1;
        } while ((iVar10 != 0) && (iVar11 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242)));
      }
    }
    iVar10 = RTMPGetKeyParameter("WCNTest",local_74,0x40,param_2,1);
    if (iVar10 != 0) {
      cVar4 = *local_74;
      bVar6 = *(byte *)((int)param_1 + 0x2b7242);
      if (bVar6 != 0) {
        pbVar28 = pbVar29;
        do {
          pbVar28 = pbVar28 + 1;
          *(bool *)((int)param_1 +
                   (int)("Set_WscPinCode_Proc:: Checksum is invalid\n" +
                        (uint)*pbVar28 * 0x5834 + 0x25)) = cVar4 != '0';
        } while (pbVar28 != (byte *)((int)param_1 + bVar6 + 0x3678c7));
      }
      if (3 < DebugLevel) {
        printk("WCNTest=%d\n");
      }
    }
    pbVar28 = pbVar29;
    iVar10 = 0;
    while (iVar11 = iVar10 + 1, iVar10 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242)) {
      pbVar28 = pbVar28 + 1;
      bVar6 = *pbVar28;
      snprintf((char *)local_ac,0x10,"WSC_UUID_Str%d",iVar11);
      iVar12 = RTMPGetKeyParameter(local_ac,local_74,0x28,param_2,0);
      pcVar13 = local_74;
      iVar10 = iVar11;
      if (iVar12 != 0) {
        sVar14 = strlen(local_74);
        memmove(param_1 + (uint)bVar6 * 0x160d + 0xaebd8,pcVar13,sVar14);
        if (3 < DebugLevel) {
          printk("UUID_Str[%d]=%s\n",iVar11,param_1 + (uint)bVar6 * 0x160d + 0xaebd8);
        }
      }
    }
    pbVar28 = pbVar29;
    iVar10 = 0;
    while (iVar11 = iVar10 + 1, iVar10 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242)) {
      pbVar28 = pbVar28 + 1;
      bVar6 = *pbVar28;
      snprintf((char *)local_ac,0x10,"WSC_UUID_E%d",iVar11);
      iVar12 = RTMPGetKeyParameter(local_ac,local_74,0x28,param_2,0);
      iVar10 = iVar11;
      if (iVar12 != 0) {
        AtoH(local_74,param_1 + (uint)bVar6 * 0x160d + 0xaebd4,0x10);
        if (3 < DebugLevel) {
          printk("Wsc_Uuid_E[%d]",iVar11);
        }
        hex_dump(&_LC127,param_1 + (uint)bVar6 * 0x160d + 0xaebd4,0x10);
      }
    }
    iVar10 = RTMPGetKeyParameter("WscAutoTriggerDisable",local_74,10,param_2,1);
    if (iVar10 != 0) {
      cVar4 = *local_74;
      bVar6 = *(byte *)((int)param_1 + 0x2b7242);
      if (bVar6 != 0) {
        do {
          pbVar29 = pbVar29 + 1;
          *(bool *)(param_1 + (uint)*pbVar29 * 0x160d + 0xaec5e) = cVar4 != '0';
        } while (pbVar29 != (byte *)((int)param_1 + bVar6 + 0x3678c7));
      }
      if (3 < DebugLevel) {
        printk("bWscAutoTriggerDisable=%d\n");
      }
    }
  }
  if (*(char *)((int)param_1 + 0x286285) == '\0') {
    iVar10 = RTMPGetKeyParameter("PSMode",local_74,0x800,param_2,1);
    if ((iVar10 != 0) && (iVar10 = rstrtok(local_74,&_LC6), iVar10 != 0)) {
      piVar25 = param_1 + 0x160001;
      puVar32 = &DAT_0057fffe + (int)param_1;
      iVar10 = 0;
      do {
        pcVar13 = local_74;
        if (puVar32[-0x20e446] == '\x01') {
          iVar11 = strcmp(local_74,"MAX_PSP");
          if ((iVar11 == 0) || (iVar11 = strcmp(pcVar13,"max_psp"), iVar11 == 0)) {
            param_1[0x1e5449] = param_1[0x1e5449] | 0x20;
            if (puVar32[0xe] == '\0') {
              *(undefined4 *)(puVar32 + 6) = 1;
            }
            *(undefined4 *)(puVar32 + 10) = 1;
            *(undefined2 *)((int)piVar25 + -6) = 5;
          }
          else {
            iVar11 = strcmp(pcVar13,"Fast_PSP");
            if (((iVar11 == 0) || (iVar11 = strcmp(pcVar13,"fast_psp"), iVar11 == 0)) ||
               (iVar11 = strcmp(pcVar13,"FAST_PSP"), iVar11 == 0)) {
              param_1[0x1e5449] = param_1[0x1e5449] | 0x20;
              if (puVar32[0xe] == '\0') {
                *(undefined4 *)(puVar32 + 6) = 2;
              }
              *(undefined4 *)(puVar32 + 10) = 2;
              *(undefined2 *)((int)piVar25 + -6) = 3;
            }
            else {
              iVar11 = strcmp(pcVar13,"Legacy_PSP");
              if (((iVar11 == 0) || (iVar11 = strcmp(pcVar13,"legacy_psp"), iVar11 == 0)) ||
                 (iVar11 = strcmp(pcVar13,"LEGACY_PSP"), iVar11 == 0)) {
                param_1[0x1e5449] = param_1[0x1e5449] | 0x20;
                if (puVar32[0xe] == '\0') {
                  *(undefined4 *)(puVar32 + 6) = 3;
                }
                *(undefined4 *)(puVar32 + 10) = 3;
                *(undefined2 *)((int)piVar25 + -6) = 3;
              }
              else {
                if (2 < DebugLevel) {
                  printk("%s(line=%d): -->\n","RTMPSetProfileParameters",0x1c8f);
                }
                MlmeSetPsmBit(param_1,puVar32 + -0x2124a6,0);
                param_1[0x1e5449] = param_1[0x1e5449] | 0x20;
                if (puVar32[0xe] == '\0') {
                  *(undefined4 *)(puVar32 + 6) = 0;
                }
                *(undefined4 *)(puVar32 + 10) = 0;
              }
            }
          }
          if (3 < DebugLevel) {
            printk("%s::pAd->StaCfg[%d]::PSMode=%ld\n","RTMPSetProfileParameters",iVar10,
                   *(undefined4 *)(puVar32 + 6));
          }
        }
        iVar11 = rstrtok(0,&_LC6);
        piVar25 = piVar25 + 0x84dec;
        puVar32 = puVar32 + 0x2137b0;
        bVar40 = iVar10 == 0;
        bVar39 = iVar10 == -1;
        iVar10 = 1;
      } while ((bVar40 || bVar39) && iVar11 != 0);
    }
    iVar10 = RTMPGetKeyParameter("AutoRoaming",local_74,0x20,param_2,1);
    if (iVar10 != 0) {
      iVar10 = os_str_tol(local_74,0,10);
      if (iVar10 == 0) {
        *(undefined1 *)((int)param_1 + 0x580cce) = 0;
      }
      else {
        *(undefined1 *)((int)param_1 + 0x580cce) = 1;
      }
      if (3 < DebugLevel) {
        printk("AutoRoaming=%d\n",*(undefined1 *)((int)param_1 + 0x580cce));
      }
    }
    iVar10 = RTMPGetKeyParameter("RoamThreshold",local_74,0x20,param_2,1);
    if (iVar10 != 0) {
      iVar10 = os_str_tol(local_74,0,10);
      if (iVar10 - 0x3cU < 0x1f) {
        *(char *)((int)param_1 + 0x580ccf) = -(char)iVar10;
      }
      else {
        *(undefined1 *)((int)param_1 + 0x580ccf) = 0xba;
      }
      if (3 < DebugLevel) {
        printk("RoamThreshold=%d  dBm\n",(int)*(char *)((int)param_1 + 0x580ccf));
      }
    }
    iVar10 = RTMPGetKeyParameter("TGnWifiTest",local_74,10,param_2,1);
    if (iVar10 != 0) {
      iVar10 = os_str_tol(local_74,0,10);
      if (iVar10 == 0) {
        *(undefined1 *)((int)param_1 + 0x57ffc3) = 0;
      }
      else {
        *(undefined1 *)((int)param_1 + 0x57ffc3) = 1;
      }
      if (3 < DebugLevel) {
        printk("TGnWifiTest=%d\n",*(undefined1 *)((int)param_1 + 0x57ffc3));
      }
    }
    iVar10 = RTMPGetKeyParameter("EthConvertMode",local_74,0x20,param_2,1);
    if ((iVar10 != 0) && (Set_EthConvertMode_Proc(param_1,local_74), 3 < DebugLevel)) {
      printk("EthConvertMode=%d\n",*(undefined1 *)((int)param_1 + 0xa77bcf));
    }
    iVar10 = RTMPGetKeyParameter("EthCloneMac",local_74,0x20,param_2,1);
    if ((iVar10 != 0) && (Set_EthCloneMac_Proc(param_1,local_74), 3 < DebugLevel)) {
      printk("EthCloneMac=%02x:%02x:%02x:%02x:%02x:%02x\n",*(undefined1 *)((int)param_1 + 0xa77bc9),
             *(undefined1 *)((int)param_1 + 0xa77bca),*(undefined1 *)((int)param_1 + 0xa77bcb),
             (char)param_1[0x29def3],*(undefined1 *)((int)param_1 + 0xa77bcd),
             *(undefined1 *)((int)param_1 + 0xa77bce));
    }
    iVar10 = RTMPGetKeyParameter("BeaconLostTime",local_74,0x20,param_2,1);
    if (iVar10 != 0) {
      iVar10 = os_str_tol(local_74,0,10);
      if (iVar10 - 1U < 0x3c) {
        param_1[0x15ffec] = iVar10 * 100;
      }
      if (3 < DebugLevel) {
        printk("BeaconLostTime=%ld\n",param_1[0x15ffec]);
      }
    }
    iVar10 = RTMPGetKeyParameter("AutoConnect",local_74,0x20,param_2,1);
    if (iVar10 != 0) {
      iVar10 = os_str_tol(local_74,0,10);
      if (iVar10 == 0) {
        *(undefined1 *)((int)param_1 + 0x580ccb) = 0;
      }
      else {
        *(undefined1 *)((int)param_1 + 0x580ccb) = 1;
      }
    }
    iVar10 = RTMPGetKeyParameter("FastConnect",local_74,0x20,param_2,1);
    if (iVar10 != 0) {
      iVar10 = os_str_tol(local_74,0,10);
      if (iVar10 == 0) {
        *(undefined1 *)(param_1 + 0x160333) = 0;
      }
      else {
        *(undefined1 *)(param_1 + 0x160333) = 1;
      }
      if (3 < DebugLevel) {
        printk("FastConnect=%d\n",(char)param_1[0x160333]);
      }
    }
  }
  iVar10 = RTMPGetKeyParameter("BTApCliAutoBWSupport",local_74,0x80,param_2,1);
  if (iVar10 == 0) {
    cVar4 = *(char *)((int)param_1 + 0x286285);
  }
  else {
    uVar2 = os_str_tol(local_74,0,10);
    *(undefined1 *)(param_1 + 0xd9e3f) = uVar2;
    cVar4 = *(char *)((int)param_1 + 0x286285);
  }
  if (cVar4 == '\x01') {
    iVar10 = RTMPGetKeyParameter("McastPhyMode",local_74,0x80,param_2,1);
    if (((iVar10 != 0) && (iVar10 = rstrtok(local_74,&_LC6), iVar10 != 0)) &&
       (*(char *)((int)param_1 + 0x2b7242) != '\0')) {
      piVar25 = param_1 + 0xadc92;
      iVar11 = 0;
      do {
        uVar9 = wlan_config_get_ht_bw(piVar25);
        uVar2 = os_str_tol(iVar10,0,10);
        *(ushort *)(param_1 + iVar11 * 0x160d + 0xadf55) =
             *(ushort *)(param_1 + iVar11 * 0x160d + 0xadf55) & 0xfe7f | (uVar9 & 3) << 7;
        switch(uVar2) {
        case 0:
          memmove(piVar25 + 0x2c3,param_1 + 0x28777,2);
          if (iVar11 == 0) {
            *(byte *)((int)param_1 + 0x2b7d55) = *(byte *)((int)param_1 + 0x2b7d55) & 0x1f;
            uVar9 = *(ushort *)(param_1 + 0xadf55);
            *(ushort *)(param_1 + 0xadf55) = uVar9 & 0xfe7f;
            *(byte *)(param_1 + 0xadf55) = (byte)uVar9 & 0x40;
          }
          else {
            *(byte *)((int)param_1 + iVar11 * 0x5834 + 0x2b7d55) =
                 *(byte *)((int)param_1 + iVar11 * 0x5834 + 0x2b7d55) & 0x1f | 0x20;
            uVar9 = *(ushort *)(param_1 + iVar11 * 0x160d + 0xadf55);
            *(ushort *)(param_1 + iVar11 * 0x160d + 0xadf55) = uVar9 & 0xfe7f;
            *(byte *)(param_1 + iVar11 * 0x160d + 0xadf55) =
                 (byte)uVar9 & 0x40 | OfdmRateToRxwiMCS[4] & 0x3f;
          }
          break;
        case 1:
          if (iVar11 != 0) {
            if (3 < DebugLevel) {
              printk("Could not set CCK mode for 5G band so set OFDM!\n");
            }
            goto switchD_000fecd8_caseD_2;
          }
          *(byte *)((int)param_1 + 0x2b7d55) = *(byte *)((int)param_1 + 0x2b7d55) & 0x1f;
          *(ushort *)(param_1 + 0xadf55) = *(ushort *)(param_1 + 0xadf55) & 0xfe7f;
          break;
        case 2:
switchD_000fecd8_caseD_2:
          *(byte *)((int)param_1 + iVar11 * 0x5834 + 0x2b7d55) =
               *(byte *)((int)param_1 + iVar11 * 0x5834 + 0x2b7d55) & 0x1f | 0x20;
          *(ushort *)(param_1 + iVar11 * 0x160d + 0xadf55) =
               *(ushort *)(param_1 + iVar11 * 0x160d + 0xadf55) & 0xfe7f;
          break;
        case 3:
          *(byte *)((int)param_1 + iVar11 * 0x5834 + 0x2b7d55) =
               *(byte *)((int)param_1 + iVar11 * 0x5834 + 0x2b7d55) & 0x1f | 0x40;
          break;
        case 4:
          *(byte *)((int)param_1 + iVar11 * 0x5834 + 0x2b7d55) =
               *(byte *)((int)param_1 + iVar11 * 0x5834 + 0x2b7d55) & 0x1f | 0x80;
          break;
        default:
          if ((3 < DebugLevel) && (printk("Unknown Multicast PhyMode %d.\n"), 3 < DebugLevel)) {
            printk("Set the default mode, MCAST_CCK!\n");
          }
          *(byte *)((int)param_1 + iVar11 * 0x5834 + 0x2b7d55) =
               *(byte *)((int)param_1 + iVar11 * 0x5834 + 0x2b7d55) & 0x1f;
          *(ushort *)(param_1 + iVar11 * 0x160d + 0xadf55) =
               *(ushort *)(param_1 + iVar11 * 0x160d + 0xadf55) & 0xfe7f;
        }
        iVar11 = iVar11 + 1;
        iVar10 = rstrtok(0,&_LC6);
      } while ((iVar10 != 0) &&
              (piVar25 = piVar25 + 0x160d, iVar11 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242)));
    }
    iVar10 = RTMPGetKeyParameter("McastMcs",local_74,0x80,param_2,1);
    if ((iVar10 != 0) &&
       ((iVar10 = rstrtok(local_74,&_LC6), iVar10 != 0 &&
        (*(char *)((int)param_1 + 0x2b7242) != '\0')))) {
      iVar11 = 0;
      do {
        bVar5 = os_str_tol(iVar10,0,10);
        bVar6 = *(byte *)((int)param_1 + iVar11 * 0x5834 + 0x2b7d55) >> 5;
        if (bVar6 == 0) {
          if (iVar11 == 1) {
            if (3 < DebugLevel) {
              printk("Could not set CCK mode for 5G band!\n");
            }
          }
          else {
            if ((bVar5 & 0xf7) < 4) goto LAB_000fd90c;
            if (3 < DebugLevel) {
              printk("MCS must in range of 0 ~ 3 and 8 ~ 11 for CCK Mode.\n");
            }
          }
        }
        else if ((bVar6 == 1) && (7 < bVar5)) {
          if (3 < DebugLevel) {
            printk("MCS must in range from 0 to 7 for OFDM Mode.\n");
          }
        }
        else {
LAB_000fd90c:
          *(byte *)(param_1 + iVar11 * 0x160d + 0xadf55) =
               *(byte *)(param_1 + iVar11 * 0x160d + 0xadf55) & 0xc0 | bVar5 & 0x3f;
        }
        iVar11 = iVar11 + 1;
        iVar10 = rstrtok(0,&_LC6);
      } while ((iVar10 != 0) && (iVar11 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242)));
    }
  }
  rtmp_read_wsc_user_parms_from_file(param_1,local_74,param_2);
  iVar10 = RTMPGetKeyParameter("Wsc4digitPinCode",local_74,0x100,param_2,1);
  if (iVar10 != 0) {
    if (((*(char *)((int)param_1 + 0x286285) == '\x01') &&
        (iVar10 = rstrtok(local_74,&_LC6), iVar10 != 0)) &&
       (*(char *)((int)param_1 + 0x2b7242) != '\0')) {
      pbVar29 = (byte *)(param_1 + 0xd9e32);
      iVar11 = 0;
      do {
        iVar10 = os_str_tol(iVar10,0,10);
        if (iVar10 == 0) {
          *(undefined1 *)((int)param_1 + (uint)*pbVar29 * 0x5834 + 0x2b8545) = 0;
        }
        else {
          *(undefined1 *)((int)param_1 + (uint)*pbVar29 * 0x5834 + 0x2b8545) = 1;
        }
        if (3 < DebugLevel) {
          printk("I/F(ra%d) Wsc4digitPinCode=%d\n",iVar11,
                 *(undefined1 *)((int)param_1 + (uint)*pbVar29 * 0x5834 + 0x2b8545));
        }
        iVar11 = iVar11 + 1;
        iVar10 = rstrtok(0,&_LC6);
        pbVar29 = pbVar29 + 1;
      } while ((iVar10 != 0) && (iVar11 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242)));
    }
    if (*(char *)((int)param_1 + 0x286285) == '\0') {
      iVar11 = os_str_tol(local_74,0,10);
      iVar10 = DebugLevel;
      if (iVar11 == 0) {
        *(undefined1 *)((int)param_1 + 0x36ee55) = 0;
      }
      else {
        *(undefined1 *)((int)param_1 + 0x36ee55) = 1;
        iVar10 = DebugLevel;
      }
      if (3 < iVar10) {
        printk("Wsc4digitPinCode=%d\n",*(undefined1 *)((int)param_1 + 0x36ee55));
      }
    }
  }
  iVar10 = RTMPGetKeyParameter("WscVendorPinCode",local_74,0x100,param_2,1);
  if (iVar10 != 0) {
    iVar10 = RT_CfgSetWscPinCode(param_1,local_74);
    if (iVar10 == 0) {
      if (-1 < DebugLevel) {
        printk("%s - WscVendorPinCode: invalid pin code(%s)\n","RTMPSetProfileParameters",local_74);
      }
    }
    else if (3 < DebugLevel) {
      printk("%s - WscVendorPinCode= (%d)\n","RTMPSetProfileParameters");
    }
  }
  iVar10 = RTMPGetKeyParameter("WscV2Support",local_74,0x80,param_2,1);
  if (iVar10 != 0) {
    if (((*(char *)((int)param_1 + 0x286285) == '\x01') &&
        (iVar10 = rstrtok(local_74,&_LC6), iVar10 != 0)) &&
       (*(char *)((int)param_1 + 0x2b7242) != '\0')) {
      pbVar29 = (byte *)((int)param_1 + 0x3678c7);
      iVar11 = 0;
      do {
        uVar2 = os_str_tol(iVar10,0,10);
        iVar10 = DebugLevel;
        pbVar29 = pbVar29 + 1;
        *(undefined1 *)((int)param_1 + (uint)*pbVar29 * 0x5834 + 0x2bb05d) = uVar2;
        if (3 < iVar10) {
          printk("I/F(ra%d) WscV2Support=%d\n",iVar11,uVar2);
        }
        iVar11 = iVar11 + 1;
        iVar10 = rstrtok(0,&_LC6);
      } while ((iVar10 != 0) && (iVar11 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242)));
    }
    if (*(char *)((int)param_1 + 0x286285) == '\0') {
      uVar2 = os_str_tol(local_74,0,10);
      iVar10 = DebugLevel;
      *(undefined1 *)((int)param_1 + 0x37196d) = uVar2;
      if (3 < iVar10) {
        printk("%s - WscV2Support= (%d)\n","RTMPSetProfileParameters",uVar2);
      }
    }
  }
  iVar10 = RTMPGetKeyParameter("EntryLifeCheck",local_74,0x100,param_2,1);
  if (iVar10 != 0) {
    iVar11 = os_str_tol(local_74,0,10);
    iVar10 = iVar11;
    if (iVar11 != 0) {
      iVar10 = iVar11 + -0x10000;
    }
    if (iVar10 < 0 == (iVar11 != 0 && SBORROW4(iVar11,0x10000))) {
      iVar11 = 0x400;
    }
    param_1[0xdae44] = iVar11;
    if (-1 < DebugLevel) {
      printk("EntryLifeCheck=%ld\n",param_1[0xdae44]);
    }
  }
  RRM_ReadParametersFromFile(param_1,local_74,param_2);
  iVar10 = RTMPGetKeyParameter("PS_RETRIEVE",local_74,10,param_2,1);
  if (iVar10 != 0) {
    uVar21 = os_str_tol(local_74,0,10);
    iVar10 = DebugLevel;
    *(char *)(param_1 + 0x29e278) = (char)uVar21;
    if (3 < iVar10) {
      printk("PS_RETRIEVE = %lx\n",uVar21);
    }
  }
  iVar10 = RTMPGetKeyParameter("IcapMode",local_74,10,param_2,1);
  if (iVar10 != 0) {
    uVar2 = simple_strtol(local_74,0,10);
    iVar10 = DebugLevel;
    *(undefined1 *)(param_1 + 0x29e295) = uVar2;
    if (3 < iVar10) {
      printk("ICapMode = %d\n",uVar2);
    }
  }
  rtmp_read_vow_parms_from_file(param_1,local_74,param_2);
  rtmp_read_fw_log_dump_parms_from_file(param_1,local_74,param_2);
  rtmp_read_cp_parms_from_file(param_1,local_74,param_2);
  iVar10 = RTMPGetKeyParameter("Dot11vMbssid",local_74,100,param_2,1);
  if (iVar10 != 0) {
    uVar26 = (uint)*(byte *)((int)param_1 + 0x2b7243);
    bVar6 = *(byte *)(param_1 + 0xadc91);
    iVar10 = rstrtok(local_74,&_LC6);
    if (iVar10 != 0) {
      uVar19 = 0;
      do {
        cVar4 = os_str_tol(iVar10,0,10);
        if (*(char *)((int)param_1 + 0x286285) == '\x01') {
          if (*(byte *)((int)param_1 + 0x2b7242) <= uVar19) break;
          if (cVar4 != '\0') {
            if (uVar19 < uVar26) {
              param_1[0xd9e3a] = param_1[0xd9e3a] | 1 << (uVar19 & 0xff);
            }
            else if (uVar19 < bVar6 + uVar26) {
              param_1[0xd9e3b] = param_1[0xd9e3b] | 1 << (uVar19 - uVar26 & 0xff);
            }
            else if (-1 < DebugLevel) {
              printk("%s, ERROR (idx = %d)\n","rtmp_read_dot11v_mbssid_cfg_from_file",uVar19);
            }
          }
        }
        uVar19 = uVar19 + 1;
        iVar10 = rstrtok(0,&_LC6);
      } while (iVar10 != 0);
    }
    if (param_1[0xd9e3a] != 0) {
      param_1[0xd9e3a] = param_1[0xd9e3a] | 1;
    }
    if (param_1[0xd9e3b] != 0) {
      param_1[0xd9e3b] = param_1[0xd9e3b] | 1;
    }
  }
  iVar10 = RTMPGetKeyParameter("TamArbOpMode",local_74,0x20,param_2,1);
  if (iVar10 != 0) {
    iVar10 = os_str_tol(local_74,0,10);
    bVar39 = -1 < DebugLevel;
    param_1[0x1e566b] = iVar10;
    if (bVar39) {
      printk("TamArbOpMode = %ld\n",iVar10);
    }
  }
  iVar10 = RTMPGetKeyParameter("HE_PpduFmt",local_74,0x20,param_2,1);
  if (iVar10 != 0) {
    iVar10 = os_str_tol(local_74,0,10);
    bVar39 = -1 < DebugLevel;
    param_1[0x1e566c] = iVar10;
    if (bVar39) {
      printk("HE_PpduFmt = %ld\n",iVar10);
    }
  }
  iVar10 = RTMPGetKeyParameter("HE_OfdmaSchType",local_74,0x20,param_2,1);
  if (iVar10 != 0) {
    iVar10 = os_str_tol(local_74,0,10);
    bVar39 = -1 < DebugLevel;
    param_1[0x1e566d] = iVar10;
    if (bVar39) {
      printk("HE_OfdmaSchType = %ld\n",iVar10);
    }
  }
  iVar10 = RTMPGetKeyParameter("HE_OfdmaUserNum",local_74,0x20,param_2,1);
  if (iVar10 != 0) {
    iVar10 = os_str_tol(local_74,0,10);
    bVar39 = -1 < DebugLevel;
    param_1[0x1e566e] = iVar10;
    if (bVar39) {
      printk("HE_OfdmaUserNum = %ld\n",iVar10);
    }
  }
  iVar10 = RTMPGetKeyParameter("HE_TrigPadding",local_74,0x20,param_2,1);
  if (iVar10 != 0) {
    iVar10 = os_str_tol(local_74,0,10);
    bVar39 = -1 < DebugLevel;
    param_1[0x1e566f] = iVar10;
    if (bVar39) {
      printk("HE_TrigPadding = %ld\n",iVar10);
    }
  }
  iVar10 = RTMPGetKeyParameter("SREnable",local_74,0x20,param_2,1);
  if (iVar10 != 0) {
    SrProfileSREnable(param_1,local_74);
  }
  iVar10 = RTMPGetKeyParameter("SRMode",local_74,0x20,param_2,1);
  if (iVar10 != 0) {
    SrProfileSRMode(param_1,local_74);
  }
  iVar10 = RTMPGetKeyParameter("SRSDEnable",local_74,0x20,param_2,1);
  if (iVar10 != 0) {
    SrProfileSRSDEnable(param_1,local_74);
  }
  iVar10 = RTMPGetKeyParameter("PPEnable",local_74,0x20,param_2,1);
  if (iVar10 != 0) {
    pp_profile_pp_en(param_1,local_74);
  }
  os_free_mem(local_74);
  return 0;
}

