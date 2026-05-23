// module: mt7915.ko
// function: rtmp_ee_load_from_bin @ 0x127cc8
// size: 840 bytes
//

undefined4 rtmp_ee_load_from_bin(int param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  size_t sVar6;
  undefined4 uVar7;
  undefined1 auStack_90 [12];
  char local_84 [4];
  char acStack_80 [4];
  char acStack_7c [4];
  char acStack_78 [4];
  char acStack_74 [4];
  char acStack_70 [80];
  
  memset(local_84,0,100);
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  iVar2 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  "cp_support_is_enabled"[param_1 + 5] = '\x04';
  if ((iVar2 == 0) || (*(code **)(iVar2 + 0x58) == (code *)0x0)) {
    sVar6 = strlen(local_84);
    builtin_strncpy(local_84 + sVar6,"/etc",4);
    builtin_strncpy(acStack_80 + sVar6,"/RT3",4);
    builtin_strncpy(acStack_7c + sVar6,"0xxE",4);
    builtin_strncpy(acStack_78 + sVar6,"EPRO",4);
    builtin_strncpy(acStack_74 + sVar6,"M.bi",4);
    (acStack_70 + sVar6)[0] = 'n';
    (acStack_70 + sVar6)[1] = '\0';
    if (0 < DebugLevel) {
      printk("%s::FileName=%s\n","rtmp_ee_load_from_bin",local_84);
    }
  }
  else {
    (**(code **)(iVar2 + 0x58))(param_1,local_84);
    if (0 < DebugLevel) {
      printk("%s::bin FileName=%s\n","rtmp_ee_load_from_bin",local_84);
    }
  }
  RtmpOSFSInfoChange(auStack_90,1);
  if (local_84[0] == '\0') {
    if (-1 < DebugLevel) {
      printk("%s::Error src or srcf is null\n","rtmp_ee_load_from_bin");
    }
  }
  else {
    iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
    uVar3 = RtmpOSFileOpen(local_84,0,0);
    if ((uVar3 == 0) || (0xfffff000 < uVar3)) {
      if (2 < DebugLevel) {
        printk("%s::Error opening %s\n","rtmp_ee_load_from_bin",local_84);
      }
    }
    else {
      uVar7 = *(undefined4 *)("Set_IRR_TTGOnOff" + param_1 + 4);
      uVar4 = get_dev_eeprom_size(param_1);
      uVar5 = (uint)*(ushort *)(iVar2 + 0xf4);
      if (uVar5 < uVar4) {
        uVar5 = get_dev_eeprom_size(param_1);
      }
      if (uVar5 != 0) {
        __memzero(uVar7);
      }
      uVar7 = get_dev_eeprom_offset(param_1);
      RtmpOSFileSeek(uVar3,uVar7);
      uVar7 = *(undefined4 *)("Set_IRR_TTGOnOff" + param_1 + 4);
      uVar4 = get_dev_eeprom_size(param_1);
      uVar5 = (uint)*(ushort *)(iVar2 + 0xf4);
      if (uVar5 < uVar4) {
        uVar5 = get_dev_eeprom_size(param_1);
      }
      iVar2 = RtmpOSFileRead(uVar3,uVar7,uVar5);
      if (0 < iVar2) {
        if (-1 < DebugLevel) {
          printk("Load EEPROM Buffer from %s\n",local_84);
        }
        iVar1 = RtmpOSFileClose(uVar3);
        if ((iVar1 != 0) && (-1 < DebugLevel)) {
          printk("%s::Error %d closing %s\n","rtmp_ee_load_from_bin",-iVar1,local_84);
        }
        "cp_support_is_enabled"[param_1 + 6] = '\b';
        strcpy("cp_support_is_enabled" + param_1 + 7,local_84);
        RtmpOSFSInfoChange(auStack_90,0);
        return 1;
      }
      if (-1 < DebugLevel) {
        printk("%s::Read file \"%s\" failed(errCode=%d)!\n","rtmp_ee_load_from_bin",local_84);
      }
    }
  }
  if (*(void **)(iVar1 + 0xf0) != (void *)0x0) {
    sVar6 = (size_t)*(ushort *)(iVar1 + 0xf4);
    if (sVar6 < 0x401) {
      sVar6 = 0x400;
    }
    memmove(*(void **)("Set_IRR_TTGOnOff" + param_1 + 4),*(void **)(iVar1 + 0xf0),sVar6);
    if (-1 < DebugLevel) {
      printk("Load EEPROM Buffer from default BIN.\n");
    }
    "cp_support_is_enabled"[param_1 + 6] = '\b';
    builtin_strncpy("cp_support_is_enabled" + param_1 + 7,"Defa",4);
    builtin_strncpy("cp_support_is_enabled" + param_1 + 0xb,"ult ",4);
    builtin_strncpy("cp_support_is_enabled" + param_1 + 0xf,"BIN",4);
  }
  RtmpOSFSInfoChange(auStack_90,0);
  return 0;
}

