// module: mt7915.ko
// function: rtmp_ee_flash_write_with_range @ 0x25f524
// size: 140 bytes
//

undefined4 rtmp_ee_flash_write_with_range(int param_1,int param_2,size_t param_3,void *param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  void *pvVar6;
  
  pvVar6 = param_4;
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if ((*(char *)(iVar1 + 0xf8) != '\0') && (*(int *)("Set_IRR_TTGOnOff" + param_1 + 4) != 0)) {
    memcpy((void *)(*(int *)("Set_IRR_TTGOnOff" + param_1 + 4) + param_2),param_4,param_3);
    uVar5 = *(undefined4 *)(param_1 + 0xa797a0);
    uVar4 = *(undefined4 *)("Set_IRR_TTGOnOff" + param_1 + 4);
    uVar2 = get_dev_eeprom_offset(param_1);
    uVar3 = get_dev_eeprom_size(param_1);
    RtmpFlashWrite(uVar5,uVar4,uVar2,uVar3,pvVar6);
  }
  return 0;
}

