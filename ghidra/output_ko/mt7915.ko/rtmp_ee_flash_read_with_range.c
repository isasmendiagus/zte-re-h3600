// module: mt7915.ko
// function: rtmp_ee_flash_read_with_range @ 0x25f474
// size: 176 bytes
//

bool rtmp_ee_flash_read_with_range(int param_1,int param_2,size_t param_3,undefined1 *param_4)

{
  byte *pbVar1;
  int iVar2;
  byte bVar3;
  uint uVar4;
  
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if ((*(char *)(iVar2 + 0xf8) == '\0') || (*(int *)("Set_IRR_TTGOnOff" + param_1 + 4) == 0)) {
    *param_4 = 0xff;
  }
  else {
    memcpy(param_4,(void *)(*(int *)("Set_IRR_TTGOnOff" + param_1 + 4) + param_2),param_3);
  }
  if (param_3 == 0) {
    return true;
  }
  uVar4 = 0;
  bVar3 = 0;
  do {
    pbVar1 = param_4 + uVar4;
    uVar4 = uVar4 + 1 & 0xffff;
    bVar3 = bVar3 | *pbVar1;
  } while (uVar4 < param_3);
  return 0xfd < (byte)(bVar3 - 1);
}

