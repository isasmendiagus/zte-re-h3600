// module: mt7915.ko
// function: rtmp_ee_write_to_bin @ 0x1280c0
// size: 552 bytes
//

undefined4 rtmp_ee_write_to_bin(int param_1)

{
  int iVar1;
  size_t sVar2;
  uint uVar3;
  undefined4 uVar4;
  uint uVar5;
  uint uVar6;
  undefined1 auStack_88 [12];
  char local_7c [4];
  char acStack_78 [4];
  char acStack_74 [4];
  char acStack_70 [4];
  char acStack_6c [4];
  char acStack_68 [80];
  
  memset(local_7c,0,100);
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if ((iVar1 == 0) || (*(code **)(iVar1 + 0x58) == (code *)0x0)) {
    sVar2 = strlen(local_7c);
    builtin_strncpy(local_7c + sVar2,"/etc",4);
    builtin_strncpy(acStack_78 + sVar2,"/RT3",4);
    builtin_strncpy(acStack_74 + sVar2,"0xxE",4);
    builtin_strncpy(acStack_70 + sVar2,"EPRO",4);
    builtin_strncpy(acStack_6c + sVar2,"M.bi",4);
    (acStack_68 + sVar2)[0] = 'n';
    (acStack_68 + sVar2)[1] = '\0';
    if (2 < DebugLevel) {
      printk("%s::src FileName=%s\n","rtmp_ee_write_to_bin",local_7c);
    }
  }
  else {
    (**(code **)(iVar1 + 0x58))(param_1,local_7c);
    if (2 < DebugLevel) {
      printk("%s::bin FileName=%s\n","rtmp_ee_write_to_bin",local_7c);
    }
  }
  RtmpOSFSInfoChange(auStack_88,1);
  if (local_7c[0] == '\0') {
    if (-1 < DebugLevel) {
      printk("%s::Error src or srcf is null\n","rtmp_ee_write_to_bin");
    }
  }
  else {
    iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
    uVar3 = RtmpOSFileOpen(local_7c,0x41,0);
    if ((uVar3 != 0) && (uVar3 < 0xfffff001)) {
      uVar4 = get_dev_eeprom_offset(param_1);
      RtmpOSFileSeek(uVar3,uVar4);
      uVar4 = *(undefined4 *)("Set_IRR_TTGOnOff" + param_1 + 4);
      uVar5 = get_dev_eeprom_size(param_1);
      uVar6 = (uint)*(ushort *)(iVar1 + 0xf4);
      if (uVar6 < uVar5) {
        uVar6 = get_dev_eeprom_size(param_1);
      }
      RtmpOSFileWrite(uVar3,uVar4,uVar6);
      iVar1 = RtmpOSFileClose(uVar3);
      if ((iVar1 != 0) && (-1 < DebugLevel)) {
        printk("%s::Error %d closing %s\n","rtmp_ee_write_to_bin",-iVar1,local_7c);
      }
      RtmpOSFSInfoChange(auStack_88,0);
      return 1;
    }
    if (-1 < DebugLevel) {
      printk("%s::Error opening %s\n","rtmp_ee_write_to_bin",local_7c);
    }
  }
  RtmpOSFSInfoChange(auStack_88,0);
  return 0;
}

