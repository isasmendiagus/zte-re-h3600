// module: mt7915.ko
// function: rtmp_ee_flash_write_all @ 0x25f608
// size: 104 bytes
//

void rtmp_ee_flash_write_all(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(char *)(iVar1 + 0xf8) == '\0') {
    return;
  }
  iVar1 = *(int *)("Set_IRR_TTGOnOff" + param_1 + 4);
  if (iVar1 == 0) {
    return;
  }
  uVar4 = *(undefined4 *)(param_1 + 0xa797a0);
  uVar2 = get_dev_eeprom_offset(param_1);
  uVar3 = get_dev_eeprom_size(param_1);
  RtmpFlashWrite(uVar4,iVar1,uVar2,uVar3);
  return;
}

