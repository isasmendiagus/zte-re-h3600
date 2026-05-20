// module: mt7915.ko
// function: NICReadEEPROMParameters @ 0x126a50
// size: 2012 bytes
//

undefined4 NICReadEEPROMParameters(int param_1,char *param_2)

{
  byte bVar1;
  int iVar2;
  size_t sVar3;
  uint uVar4;
  ushort uVar5;
  short sVar6;
  ushort *puVar7;
  char *pcVar8;
  char *pcVar9;
  uint uVar10;
  uint local_40;
  ushort local_36;
  byte local_34;
  byte local_33;
  undefined2 local_32;
  ushort local_30;
  undefined1 local_2e [2];
  undefined1 local_2c [2];
  ushort local_2a [3];
  
  local_2a[0] = 0;
  iVar2 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (2 < DebugLevel) {
    printk("%s()-->\n","NICReadEEPROMParameters");
  }
  if (*(code **)(iVar2 + 4) != (code *)0x0) {
    (**(code **)(iVar2 + 4))(param_1);
    iVar2 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
    if ((*(code **)(iVar2 + 0x8c) == (code *)0x0) ||
       (iVar2 = (**(code **)(iVar2 + 0x8c))(param_1), iVar2 == 0)) {
      if (2 < DebugLevel) {
        printk("Non Cal Free IC!!\n");
      }
    }
    else {
      if (2 < DebugLevel) {
        printk("Cal Free IC!!\n");
      }
      iVar2 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
      if (*(code **)(iVar2 + 0x90) != (code *)0x0) {
        (**(code **)(iVar2 + 0x90))(param_1);
        "cp_support_is_enabled"[param_1 + 6] = "cp_support_is_enabled"[param_1 + 6] | 1;
      }
    }
  }
  if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7915) {
    iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
    chip_eeprom_read16(param_1,0x62,local_2a);
    if (0 < DebugLevel) {
      printk(&_LC13,"NICReadEEPROMParameters",0x62,local_2a[0]);
    }
    if (("cp_support_is_enabled"[param_1 + 4] - 2U & 0xfd) == 0) {
      if ((local_2a[0] & 1) != 0) {
        if (0 < DebugLevel) {
          printk("%s: Group Pre-Cal finished, load Group Pre-Cal data\n","NICReadEEPROMParameters");
        }
        uVar4 = (uint)*(ushort *)(iVar2 + 0x22c);
        if (uVar4 != 0) {
          sVar6 = 0;
          do {
            uVar10 = uVar4;
            if (0x3ff < uVar4) {
              uVar10 = 0x400;
            }
            MtCmdSetGroupPreCal_7915(param_1,sVar6,uVar10);
            if (2 < DebugLevel) {
              printk("%s: idx=%d, sendLength=%d, remainedLength=%d\n","NICReadEEPROMParameters",
                     sVar6,uVar10,uVar4);
            }
            uVar4 = uVar4 - uVar10;
            sVar6 = sVar6 + 1;
          } while (uVar4 != 0);
        }
      }
      if ((local_2a[0] & 2) != 0) {
        if (DebugLevel < 1) goto LAB_00126b38;
        printk("%s: DPD 5G Pre-Cal finished!\n","NICReadEEPROMParameters");
      }
      if (((local_2a[0] & 4) != 0) && (0 < DebugLevel)) {
        printk("%s: DPD 2G Pre-Cal finished!\n","NICReadEEPROMParameters");
      }
    }
  }
LAB_00126b38:
  DfsSetCalibration(param_1,*(undefined1 *)(param_1 + 0x7953ed));
  if (((*(uint *)(param_1 + 0xa3ac14) & 1) == 0) &&
     ((*(int *)(param_1 + 0xa77bb4) != 1 ||
      ((*(uint *)(*(int *)(param_1 + 0xa77bb8) + 0x4e0) & 1) == 0)))) {
    rtmp_eeprom_info_extract(param_1);
    chip_pa_lna_set(param_1,*(undefined4 *)("Set_IRR_TTGOnOff" + param_1 + 4));
    chip_tssi_set(param_1,*(undefined4 *)("Set_IRR_TTGOnOff" + param_1 + 4));
    MtCmdEfusBufferModeSet(param_1,"Get_System_Bw_Info"[param_1 + 0x10]);
  }
  if (2 < DebugLevel) {
    printk("Initialize MAC Address from E2PROM\n");
  }
  chip_eeprom_read16(param_1,4,&local_30);
  chip_eeprom_read16(param_1,6,local_2e);
  chip_eeprom_read16(param_1,8,local_2c);
  *(char *)(param_1 + 0x794b56) = (char)(local_30 >> 8);
  *(char *)(param_1 + 0x794b55) = (char)local_30;
  *(char *)(param_1 + 0x794b57) = local_2e[0];
  *(char *)(param_1 + 0x794b58) = local_2e[1];
  *(char *)(param_1 + 0x794b59) = local_2c[0];
  *(char *)(param_1 + 0x794b5a) = local_2c[1];
  if ((local_30 & 0xff) == 0xff) {
    bVar1 = RandomByte(param_1);
    *(byte *)(param_1 + 0x794b55) = bVar1 & 0xf8;
  }
  if (DebugLevel < 3) {
    if (*(char *)(param_1 + 0x794b54) != '\0') goto LAB_00126c8c;
  }
  else {
    printk("E2PROM MAC: =%02x:%02x:%02x:%02x:%02x:%02x\n",*(undefined1 *)(param_1 + 0x794b55),
           *(undefined1 *)(param_1 + 0x794b56),*(undefined1 *)(param_1 + 0x794b57),
           *(undefined1 *)(param_1 + 0x794b58),*(undefined1 *)(param_1 + 0x794b59),
           *(undefined1 *)(param_1 + 0x794b5a));
    if (*(char *)(param_1 + 0x794b54) != '\0') {
      if (2 < DebugLevel) {
        printk("Use the MAC address what is assigned from Configuration file(.dat).\n");
      }
      goto LAB_00126c8c;
    }
  }
  if (((param_2 == (char *)0x0) || (sVar3 = strlen(param_2), sVar3 != 0x11)) ||
     (iVar2 = strcmp(param_2,"00:00:00:00:00:00"), iVar2 == 0)) {
    iVar2 = DebugLevel;
    *(undefined4 *)(param_1 + 0x794b5b) = *(undefined4 *)(param_1 + 0x794b55);
    *(undefined2 *)(param_1 + 0x794b5f) = *(undefined2 *)(param_1 + 0x794b59);
    if (2 < iVar2) {
      printk("Use the MAC address what is assigned from EEPROM.\n");
    }
  }
  else {
    iVar2 = param_1 + 0x794b5b;
    pcVar8 = param_2;
    do {
      pcVar9 = pcVar8 + 3;
      AtoH(pcVar8,iVar2,1);
      iVar2 = iVar2 + 1;
      pcVar8 = pcVar9;
    } while (pcVar9 != param_2 + 0x12);
    if (2 < DebugLevel) {
      printk("Use the MAC address what is assigned from Moudle Parameter.\n");
    }
  }
LAB_00126c8c:
  chip_eeprom_read16(param_1,2,&local_34);
  iVar2 = DebugLevel;
  *(uint *)(&DAT_00296cb4 + param_1) = (uint)local_33 + (uint)local_34 * 0x100;
  if (2 < iVar2) {
    printk("E2PROM: Version = %d, FAE release #%d\n");
  }
  chip_eeprom_read16(param_1,0x34,&local_36);
  *(ushort *)("Set_IRR_ADC" + param_1) = local_36;
  chip_eeprom_read16(param_1,0x36,&local_36);
  uVar5 = local_36;
  local_40 = (uint)local_36;
  *(ushort *)("Set_IRR_ADC" + param_1 + 2) = local_36;
  chip_eeprom_read16(param_1,0x38,&local_36);
  iVar2 = DebugLevel;
  *(ushort *)("Set_IRR_ADC" + param_1 + 6) = local_36;
  if (0 < iVar2) {
    printk("Country Region from e2p = %x\n");
  }
  puVar7 = (ushort *)("Set_IRR_ADC" + param_1 + 6);
  do {
    iVar2 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
    if (iVar2 == 1) break;
    iVar2 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
    if (iVar2 == 2) break;
    chip_eeprom_read16(param_1,(char *)((-0x296bd2 - param_1) + (int)puVar7),&local_36);
    puVar7 = puVar7 + 1;
    *puVar7 = local_36;
  } while (puVar7 != (ushort *)("Set_IRR_RxGain" + param_1 + 10));
  local_32 = *(ushort *)("Set_IRR_ADC" + param_1);
  if ((local_32 & 0xff00) == 0xff00) {
    iVar2 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
    if (*(code **)(iVar2 + 0x70) != (code *)0x0) {
      (**(code **)(iVar2 + 0x70))(param_1,&local_32);
    }
  }
  iVar2 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar2 + 0x70) != (code *)0x0) {
    (**(code **)(iVar2 + 0x70))(param_1,&local_32);
  }
  if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 8) & 0xffefffff) == 0x28600100) {
    *(byte *)(param_1 + 0x794b24) = (byte)uVar5 >> 7;
  }
  iVar2 = DebugLevel;
  if (*(char *)(param_1 + 0x286285) == '\x01') {
    if (local_40 == 0xffff) {
      uVar5 = 0;
    }
  }
  else if (*(char *)(param_1 + 0x286285) == '\0') {
    if ((local_40 & 0xff) == 0xff) {
      local_40 = local_40 & 0xff00;
    }
    uVar5 = (ushort)local_40;
    if ((local_40 << 8) >> 0x10 == 0xff) {
      uVar5 = (ushort)local_40 & 0xff;
    }
  }
  local_40._0_2_ = uVar5;
  *(ushort *)("rtmp_read_vow_parms_from_file" + param_1 + 6) = (ushort)local_40;
  if (2 < iVar2) {
    printk("%s(): RxPath = %d, TxPath = %d, RfIcType = %d\n","NICReadEEPROMParameters",
           (byte)local_32 & 0xf,(byte)local_32 >> 4,local_32._1_1_ & 0xf);
  }
  *(ushort *)("SetPartProfileParameters" + param_1 + 0x18) = local_32;
  *(byte *)(param_1 + 0x829220) = (byte)(((uint)(byte)local_32 << 0x1c) >> 0x1c);
  uVar4 = *(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc);
  "rtmp_read_dot11v_mbssid_cfg_from_file"[param_1 + 0x1e] =
       (byte)(((uint)local_32._1_1_ << 0x1c) >> 0x1c);
  if ((uVar4 & 0xffff) == 0x7915) {
    "rtmp_read_dot11v_mbssid_cfg_from_file"[param_1 + 0x1e] = '#';
  }
  rtmp_read_txpwr_from_eeprom(param_1);
  if ((2 < DebugLevel) &&
     (printk("%s: pAd->Antenna.field.BoardType = %d\n","NICReadEEPROMParameters",
             ((uint)(byte)"SetPartProfileParameters"[param_1 + 0x19] << 0x1a) >> 0x1e),
     2 < DebugLevel)) {
    printk("<--%s()\n","NICReadEEPROMParameters");
  }
  return 1;
}

