// module: mt7915.ko
// function: RtmpChipOpsEepromHook @ 0x127760
// size: 1140 bytes
//

/* WARNING: Type propagation algorithm not settling */

undefined4 RtmpChipOpsEepromHook(int param_1,int param_2,uint param_3)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  char cVar8;
  undefined4 uVar9;
  uint local_2c [2];
  
  iVar2 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  iVar3 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if ((*(uint *)(param_1 + 0xa39f84) & 0x100) != 0) {
    return 0xffffffff;
  }
  efuse_probe(param_1);
  if (param_3 != 0 && (int)param_3 < 5) {
    param_3 = param_3 & 0xff;
    if ((0 < DebugLevel) &&
       (printk("%s::forceMode: %d , infType: %d\n","RtmpChipOpsEepromHook",param_3,param_2),
       0 < DebugLevel)) {
      uVar5 = 0;
LAB_0012789c:
      printk("%s: E2P type(%d), E2pAccessMode = %d, E2P default = %d\n","RtmpChipOpsEepromHook",
             param_3,"cp_support_is_enabled"[param_1 + 4],uVar5);
    }
    if (param_3 == 1) goto LAB_00127914;
LAB_001277fc:
    iVar6 = *(int *)("Set_IRR_TTGOnOff" + param_1 + 4);
    "cp_support_is_enabled"[param_1 + 5] = (char)param_3;
    pcVar1 = "Get_System_Bw_Info" + param_1 + 0x10;
    pcVar1[0] = '\x02';
    pcVar1[1] = '\0';
    pcVar1[2] = '\0';
    pcVar1[3] = '\0';
    if (iVar6 == 0) goto LAB_00127ae8;
LAB_00127814:
    iVar3 = DebugLevel;
    switch(param_3) {
    case 1:
      goto switchD_0012781c_caseD_1;
    case 2:
      *(code **)(iVar2 + 4) = rtmp_nv_init;
      *(code **)(iVar2 + 8) = rtmp_ee_flash_read;
      *(code **)(iVar2 + 0xc) = rtmp_ee_flash_write;
      *(code **)(iVar2 + 0x10) = rtmp_ee_flash_read_with_range;
      *(code **)(iVar2 + 0x14) = rtmp_ee_flash_write_with_range;
      if (0 < iVar3) {
        uVar9 = *(undefined4 *)("Get_System_CapNode_Info" + param_1 + 4);
        uVar4 = get_dev_eeprom_offset(param_1);
        printk("NVM is FLASH mode. dev_idx [%d] FLASH OFFSET [0x%X]\n",uVar9,uVar4);
        return 0;
      }
      return 0;
    case 3:
      goto switchD_0012781c_caseD_3;
    case 4:
      *(code **)(iVar2 + 4) = rtmp_ee_bin_init;
      *(code **)(iVar2 + 8) = rtmp_ee_bin_read16;
      *(code **)(iVar2 + 0xc) = rtmp_ee_bin_write16;
      break;
    default:
      if (DebugLevel < 0) {
        *(code **)(iVar2 + 4) = rtmp_ee_bin_init;
        *(code **)(iVar2 + 8) = rtmp_ee_bin_read16;
        *(code **)(iVar2 + 0xc) = rtmp_ee_bin_write16;
        return 0;
      }
      printk("%s: Do not support E2P type(%d), change to BIN mode\n","RtmpChipOpsEepromHook",param_3
            );
      iVar3 = DebugLevel;
      *(code **)(iVar2 + 4) = rtmp_ee_bin_init;
      *(code **)(iVar2 + 8) = rtmp_ee_bin_read16;
      *(code **)(iVar2 + 0xc) = rtmp_ee_bin_write16;
    }
    if (iVar3 < 1) {
      return 0;
    }
    printk("NVM is BIN mode\n");
    return 0;
  }
  param_3 = (uint)(byte)"cp_support_is_enabled"[param_1 + 4];
  if (0 < DebugLevel) {
    printk("%s::e2p_type=%d, inf_Type=%d\n","RtmpChipOpsEepromHook",param_3,param_2);
  }
  uVar5 = RtmpEepromGetDefault(param_1);
  if (3 < (param_3 - 1 & 0xff)) {
    param_3 = uVar5;
  }
  if ("cp_support_is_enabled"[param_1 + 4] == '\0') {
    "cp_support_is_enabled"[param_1 + 4] = (char)uVar5;
  }
  iVar6 = DebugLevel;
  if (param_2 == 4) {
    param_3 = 2;
LAB_00127888:
    "Set_IRR_TTGOnOff"[param_1 + 1] = '\0';
    if (0 < iVar6) goto LAB_0012789c;
    goto LAB_001277fc;
  }
  if (param_3 != 1) goto LAB_00127888;
  if (0 < DebugLevel) goto LAB_0012789c;
LAB_00127914:
  iVar6 = *(int *)("Set_IRR_TTGOnOff" + param_1 + 4);
  param_3 = 1;
  pcVar1 = "Get_System_Bw_Info" + param_1 + 0x10;
  pcVar1[0] = '\x01';
  pcVar1[1] = '\0';
  pcVar1[2] = '\0';
  pcVar1[3] = '\0';
  "cp_support_is_enabled"[param_1 + 5] = '\x01';
  if (iVar6 == 0) {
LAB_00127ae8:
    uVar5 = get_dev_eeprom_size(param_1);
    uVar7 = (uint)*(ushort *)(iVar3 + 0xf6);
    if (uVar7 < uVar5) {
      uVar7 = get_dev_eeprom_size(param_1);
    }
    os_alloc_mem(param_1,"Set_IRR_TTGOnOff" + param_1 + 4,uVar7);
    goto LAB_00127814;
  }
switchD_0012781c_caseD_1:
  iVar3 = DebugLevel;
  if ("Set_IRR_TTGOnOff"[param_1 + 1] != '\0') {
    *(code **)(iVar2 + 4) = eFuse_init;
    *(code **)(iVar2 + 8) = rtmp_ee_efuse_read16;
    *(code **)(iVar2 + 0xc) = rtmp_ee_efuse_write16;
    if (0 < iVar3) {
      printk("NVM is EFUSE mode\n");
      return 0;
    }
    return 0;
  }
  if (DebugLevel < 0) {
    if ((param_2 != 1) && (param_2 != 5)) {
      return 0;
    }
  }
  else {
    printk("%s::hook efuse mode failed\n","RtmpChipOpsEepromHook");
switchD_0012781c_caseD_3:
    if ((param_2 != 1) && (param_2 != 5)) {
      if (DebugLevel < 0) {
        return 0;
      }
      printk("%s::hook failed\n","RtmpChipOpsEepromHook");
      iVar3 = DebugLevel;
      goto LAB_001279a0;
    }
  }
  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),4,local_2c);
  iVar3 = DebugLevel;
  if ((local_2c[0] & 0x30) == 0) {
    cVar8 = '\x06';
  }
  else {
    cVar8 = '\b';
  }
  "Set_IRR_TTG"[param_1 + 10] = cVar8;
  *(code **)(iVar2 + 8) = rtmp_ee_prom_read16;
  *(code **)(iVar2 + 0xc) = rtmp_ee_prom_write16;
  *(undefined4 *)(iVar2 + 4) = 0;
LAB_001279a0:
  if (0 < iVar3) {
    printk("NVM is EEPROM mode\n");
  }
  return 0;
}

