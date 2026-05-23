// module: mt7915.ko
// function: HQA_ReadBulkEEPROM @ 0x275900
// size: 492 bytes
//

int HQA_ReadBulkEEPROM(int param_1,undefined4 param_2,int param_3)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int local_2c [2];
  
  local_2c[0] = 0;
  hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  uVar1 = *(ushort *)(param_3 + 0xe);
  uVar4 = (uVar1 & 0xff) << 8 | (uint)(uVar1 >> 8);
  uVar7 = (*(ushort *)(param_3 + 0xc) & 0xff) << 8 | (uint)(*(ushort *)(param_3 + 0xc) >> 8);
  if (2 < DebugLevel) {
    printk("%s: Offset = %x, Length = %x\n","HQA_ReadBulkEEPROM",uVar7);
  }
  if ("cp_support_is_enabled"[param_1 + 4] == '\x02') {
    uVar6 = get_dev_eeprom_size(param_1);
    iVar2 = *(int *)(*(int *)(param_1 + 4) + 0x240);
  }
  else {
    uVar6 = 0x400;
    iVar2 = *(int *)(*(int *)(param_1 + 4) + 0x240);
  }
  if (iVar2 == 0) {
    warn_slowpath_null("include/linux/netdevice.h",0xa06);
    printk(&_LC116);
  }
  else {
    _set_bit(0,iVar2 + 0x50);
  }
  iVar2 = os_alloc_mem(param_1,local_2c,uVar6);
  if (iVar2 == 1) {
    if (-1 < DebugLevel) {
      printk("%s: allocate memory for read EEPROM fail\n","HQA_ReadBulkEEPROM");
    }
    iVar5 = 2;
  }
  else {
    EEReadAll(param_1,local_2c[0],uVar6);
    uVar3 = uVar7 + uVar4;
    if (uVar6 < uVar3) {
      if (-1 < DebugLevel) {
        printk("%s: exceed EEPROM size (offset:%d, size:%d)\n","HQA_ReadBulkEEPROM",uVar3,uVar6);
      }
      iVar5 = 2;
      iVar2 = -1;
    }
    else {
      FUN_0026cd64(param_1,(ushort *)(param_3 + 0xe),local_2c[0] + uVar7);
      iVar5 = uVar4 + 2;
    }
    os_free_mem(local_2c[0]);
    _clear_bit(0,*(int *)(*(int *)(param_1 + 4) + 0x240) + 0x50);
  }
  FUN_0026cdd0(param_3,param_2,iVar5,iVar2);
  return iVar2;
}

