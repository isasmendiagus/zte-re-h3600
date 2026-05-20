// module: mt7915.ko
// function: rtmp_ee_flash_read @ 0x25f2b4
// size: 120 bytes
//

bool rtmp_ee_flash_read(int param_1,int param_2,short *param_3)

{
  int iVar1;
  
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if ((*(char *)(iVar1 + 0xf8) != '\0') && (*(int *)("Set_IRR_TTGOnOff" + param_1 + 4) != 0)) {
    *param_3 = *(short *)(*(int *)("Set_IRR_TTGOnOff" + param_1 + 4) + param_2);
    return 0xfffd < (ushort)(*param_3 - 1U);
  }
  *param_3 = -1;
  return true;
}

