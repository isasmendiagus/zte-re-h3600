// module: mt7915.ko
// function: rtmp_ee_flash_write @ 0x25f398
// size: 216 bytes
//

undefined4 rtmp_ee_flash_write(int param_1,int param_2,undefined2 param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  char *pcVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if ((*(char *)(iVar1 + 0xf8) != '\0') && (*(int *)("Set_IRR_TTGOnOff" + param_1 + 4) != 0)) {
    pcVar4 = EEPROMValChange + 4;
    *(undefined2 *)(*(int *)("Set_IRR_TTGOnOff" + param_1 + 4) + param_2) = param_3;
    do {
      while ((*pcVar4 != '\0' &&
             ((*(int *)(pcVar4 + -4) == param_2 || (*(int *)(pcVar4 + -4) == param_2 + 1))))) {
        pcVar4[1] = '\0';
        pcVar4 = pcVar4 + 8;
        if (pcVar4 == (char *)&DAT_005f662c) goto LAB_0025f434;
      }
      pcVar4 = pcVar4 + 8;
    } while (pcVar4 != (char *)&DAT_005f662c);
LAB_0025f434:
    uVar6 = *(undefined4 *)(param_1 + 0xa797a0);
    uVar5 = *(undefined4 *)("Set_IRR_TTGOnOff" + param_1 + 4);
    uVar2 = get_dev_eeprom_offset(param_1);
    uVar3 = get_dev_eeprom_size(param_1);
    RtmpFlashWrite(uVar6,uVar5,uVar2,uVar3);
  }
  return 0;
}

