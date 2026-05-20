// module: mt7915.ko
// function: rtmp_ee_flash_read_all @ 0x25f5b0
// size: 88 bytes
//

void rtmp_ee_flash_read_all(int param_1,void *param_2)

{
  int iVar1;
  size_t __n;
  void *__src;
  
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(char *)(iVar1 + 0xf8) == '\0') {
    return;
  }
  __src = *(void **)("Set_IRR_TTGOnOff" + param_1 + 4);
  if (__src == (void *)0x0) {
    return;
  }
  __n = get_dev_eeprom_size(param_1);
  memcpy(param_2,__src,__n);
  return;
}

