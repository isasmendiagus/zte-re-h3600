// module: mt7915.ko
// function: rtmp_nv_init @ 0x25f928
// size: 1300 bytes
//

undefined4 rtmp_nv_init(int param_1)

{
  ushort uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 *puVar4;
  int iVar5;
  undefined4 uVar6;
  bool bVar7;
  undefined8 uVar8;
  ushort local_22 [3];
  
  if (2 < DebugLevel) {
    printk("--> rtmp_nv_init\n");
  }
  if (*(int *)("Set_IRR_TTGOnOff" + param_1 + 4) != 0) {
    os_free_mem();
  }
  uVar2 = get_dev_eeprom_size(param_1);
  os_alloc_mem(param_1,"Set_IRR_TTGOnOff" + param_1 + 4,uVar2);
  if (0 < DebugLevel) {
    uVar2 = get_dev_eeprom_size(param_1);
    printk(&_LC16,"rtmp_nv_init",uVar2);
  }
  iVar5 = *(int *)("Set_IRR_TTGOnOff" + param_1 + 4);
  if (iVar5 == 0) {
    if (-1 < DebugLevel) {
      uVar2 = get_dev_eeprom_size(param_1);
      printk("Allocate %d-byte-of EEPROMImage failed.\n",uVar2);
      return 1;
    }
    return 1;
  }
  iVar3 = get_dev_eeprom_size(param_1);
  if (iVar3 != 0) {
    __memzero(iVar5);
  }
  uVar6 = *(undefined4 *)("Set_IRR_TTGOnOff" + param_1 + 4);
  uVar2 = get_dev_eeprom_offset(param_1);
  uVar8 = get_dev_eeprom_size(param_1);
  ra_mtd_read_nm(uVar6,(int)((ulonglong)uVar8 >> 0x20),uVar2,0,(int)uVar8);
  iVar5 = DebugLevel;
  if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7915) {
    iVar3 = *(int *)("Set_IRR_TTGOnOff" + param_1 + 4);
    *(int *)("RTMPSetSTAPassPhrase" + param_1 + 4) = iVar3 + 0xe00;
    *(int *)("RTMPSetSTAPassPhrase" + param_1 + 0x10) = iVar3 + 0xd220;
    *(int *)("RTMPSetSTAPassPhrase" + param_1 + 8) = iVar3 + 0xe10;
    if (0 < iVar5) {
      printk(&_LC17,iVar3,iVar3 + 0xe00,iVar3 + 0xe10,iVar3 + 0xd220);
      iVar3 = *(int *)("Set_IRR_TTGOnOff" + param_1 + 4);
      if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) != 0x7915)
      goto LAB_0025f9ec;
    }
    *(int *)("SetPartProfileParameters" + param_1 + 0xc) = iVar3 + 0x308;
    *(int *)("SetPartProfileParameters" + param_1 + 4) = iVar3 + 0xafc;
    *(int *)("SetPartProfileParameters" + param_1 + 0x14) = iVar3 + 0x380;
  }
  else {
    iVar3 = *(int *)("Set_IRR_TTGOnOff" + param_1 + 4);
  }
LAB_0025f9ec:
  "cp_support_is_enabled"[param_1 + 5] = '\x02';
  "cp_support_is_enabled"[param_1 + 6] = '\x02';
  uVar2 = 1;
  iVar5 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  *(undefined1 *)(iVar5 + 0xf8) = 1;
  iVar5 = FUN_0025f32c(param_1);
  if (iVar5 == 0) {
    iVar5 = FUN_0025ed80(param_1,iVar3);
    if (iVar5 == 0) {
      rtmp_ee_flash_read(param_1,8,local_22);
      local_22[0] = local_22[0] & 0xff;
      uVar1 = RandomByte(param_1);
      bVar7 = -1 < DebugLevel;
      local_22[0] = local_22[0] | (uVar1 & 0xf8) << 8;
      *(ushort *)(*(int *)("Set_IRR_TTGOnOff" + param_1 + 4) + 8) = local_22[0];
      if (bVar7) {
        printk("The EEPROM in Flash is wrong, use default\n");
      }
      iVar5 = FUN_0025f32c(param_1);
      uVar2 = 0;
      if (iVar5 == 0) {
        if (DebugLevel < 0) {
          uVar2 = 1;
        }
        else {
          uVar2 = 1;
          printk("rtmp_ee_flash_init(): invalid eeprom\n");
        }
      }
    }
    else if (DebugLevel < 0) {
      uVar2 = 1;
    }
    else {
      printk("rtmp_ee_init(): rtmp_ee_flash_init() failed\n");
    }
  }
  else {
    uVar2 = 0;
  }
  iVar5 = DebugLevel;
  puVar4 = EEPROMValChange;
  do {
    *(undefined1 *)((int)puVar4 + 5) = 0;
    puVar4 = (undefined1 *)((int)puVar4 + 8);
  } while ((undefined4 *)puVar4 != &_LANCHOR1);
  if (-1 < iVar5) {
    printk("--> rtmp_nv_init workMode0=%d, workMode1=%d\n",*(undefined4 *)(param_1 + 0xa7d18c),
           *(undefined4 *)(param_1 + 0xa7d1b0));
  }
  if ((*(uint *)(param_1 + 0xa7d18c) & 0x40) != 0) {
    SetEEPROMTxPowerPlus(param_1,0x252,3);
    SetEEPROMTxPowerPlus(param_1,0x253,3);
    SetEEPROMTxPowerPlus(param_1,0x254,3);
    SetEEPROMTxPowerPlus(param_1,0x255,3);
    SetEEPROMTxPowerPlus(param_1,0x259,3);
    SetEEPROMTxPowerPlus(param_1,0x25b,3);
    SetEEPROMTxPowerPlus(param_1,0x262,3);
    SetEEPROMTxPowerPlus(param_1,0x263,3);
    SetEEPROMTxPowerPlus(param_1,0x26b,3);
    SetEEPROMTxPowerPlus(param_1,0x26c,3);
    SetEEPROMTxPowerPlus(param_1,0x275,3);
    SetEEPROMTxPowerPlus(param_1,0x276,3);
  }
  if ((*(uint *)(param_1 + 0xa7d1b0) & 0x40) != 0) {
    SetEEPROMTxPowerPlus(param_1,0x29d,3);
    SetEEPROMTxPowerPlus(param_1,0x29e,3);
    SetEEPROMTxPowerPlus(param_1,0x2a2,3);
    SetEEPROMTxPowerPlus(param_1,0x2a4,3);
    SetEEPROMTxPowerPlus(param_1,0x2a5,3);
    SetEEPROMTxPowerPlus(param_1,0x2ab,3);
    SetEEPROMTxPowerPlus(param_1,0x2ac,3);
    SetEEPROMTxPowerPlus(param_1,0x2ad,3);
    SetEEPROMTxPowerPlus(param_1,0x2b4,3);
    SetEEPROMTxPowerPlus(param_1,0x2b5,3);
    SetEEPROMTxPowerPlus(param_1,0x2b6,3);
    SetEEPROMTxPowerPlus(param_1,0x2bf,3);
    SetEEPROMTxPowerPlus(param_1,0x2c0,3);
    SetEEPROMTxPowerPlus(param_1,0x2c1,3);
    SetEEPROMTxPowerPlus(param_1,0x2c9,3);
    SetEEPROMTxPowerPlus(param_1,0x2ca,3);
    SetEEPROMTxPowerPlus(param_1,0x2d3,3);
    SetEEPROMTxPowerPlus(param_1,0x2d4,3);
  }
  return uVar2;
}

