// module: mt7915.ko
// function: HQA_WriteBulkEEPROM @ 0x275544
// size: 640 bytes
//

int HQA_WriteBulkEEPROM(int param_1,undefined4 param_2,int param_3)

{
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  uint extraout_r1;
  uint uVar4;
  uint extraout_r1_00;
  uint extraout_r1_01;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  undefined2 *puVar9;
  int local_2c [2];
  
  local_2c[0] = 0;
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if (0 < DebugLevel) {
    printk(&_LC11,"HQA_WriteBulkEEPROM");
  }
  uVar5 = (*(ushort *)(param_3 + 0xc) & 0xff) << 8 | (uint)(*(ushort *)(param_3 + 0xc) >> 8);
  uVar7 = (*(ushort *)(param_3 + 0xe) & 0xff) << 8 | (uint)(*(ushort *)(param_3 + 0xe) >> 8);
  iVar3 = os_alloc_mem(param_1,local_2c,*(undefined2 *)(iVar2 + 0xf4));
  if (iVar3 == 1) {
    if (-1 < DebugLevel) {
      printk("%s: allocate memory for read EEPROM fail\n","HQA_WriteBulkEEPROM");
    }
  }
  else {
    FUN_0026cd64(param_1,local_2c[0] + uVar5,param_3 + 0x10,uVar7);
    if (uVar7 == 0x10) {
      memcpy((void *)(*(int *)("Set_IRR_TTGOnOff" + param_1 + 4) + uVar5),
             (void *)(local_2c[0] + uVar5),0x10);
      if (uVar5 == 0x3f0) {
        rtmp_ee_flash_write_all(param_1);
      }
    }
    else {
      uVar6 = uVar5 + uVar7;
      uVar4 = extraout_r1;
      if (uVar6 == 0x400) {
        rtmp_ee_flash_write_all(param_1);
        uVar4 = extraout_r1_01;
      }
      if (*(ushort *)(iVar2 + 0xf4) < uVar6) {
        if ((((-1 < DebugLevel) &&
             (printk("%s: exceed EEPROM size(%d)\n","HQA_WriteBulkEEPROM",0x400), -1 < DebugLevel))
            && (printk("Offset = %u\n",uVar5), -1 < DebugLevel)) &&
           (printk("Length = %u\n",uVar7), -1 < DebugLevel)) {
          printk("Offset + Length=%u\n",uVar6);
        }
      }
      else if (uVar7 >> 1 != 0) {
        uVar6 = uVar5;
        puVar9 = (undefined2 *)(local_2c[0] + uVar5);
        do {
          uVar1 = *puVar9;
          iVar2 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0),uVar4);
          uVar8 = uVar6 + 2;
          if (*(code **)(iVar2 + 0xc) != (code *)0x0) {
            (**(code **)(iVar2 + 0xc))(param_1,uVar6,uVar1);
            uVar6 = extraout_r1_00;
          }
          uVar4 = uVar6;
          uVar6 = uVar8;
          puVar9 = puVar9 + 1;
        } while (uVar8 != uVar5 + ((uVar7 >> 1) - 1 & 0xffff) * 2 + 2);
      }
    }
  }
  os_free_mem(local_2c[0]);
  FUN_0026cdd0(param_3,param_2,uVar7 + 2,iVar3);
  return iVar3;
}

