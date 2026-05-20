// module: mt7915.ko
// function: mtf_write_tmac_info_by_wa @ 0x19e430
// size: 616 bytes
//

void mtf_write_tmac_info_by_wa(undefined4 param_1,uint *param_2,int param_3)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  __memzero(param_2,0x20);
  uVar3 = param_2[1];
  uVar4 = *(int *)(param_3 + 0x28) + 0x20 + (uint)*(byte *)(param_3 + 0x35) +
          (uint)*(byte *)(param_3 + 0x34) & 0xffff | *param_2;
  param_2[1] = uVar3 | 0x80000000;
  *param_2 = uVar4;
  if (*(char *)(param_3 + 0x34) != '\0') {
    param_2[1] = uVar3 | 0x800c0000;
  }
  if (*(char *)(param_3 + 0x95) != '\0') {
    uVar3 = (uint)*(byte *)(param_3 + 0x96);
    if (7 < uVar3) {
      uVar3 = 7;
      *(undefined1 *)(param_3 + 0x96) = 7;
      uVar4 = *param_2;
    }
    bVar1 = *(byte *)((int)&WMM_UP2AC_MAP + uVar3);
    uVar3 = param_2[1];
    param_2[1] = uVar3 & 0xff8fffff;
    *param_2 = uVar4 & 0x1ffffff | (uint)bVar1 << 0x19;
    param_2[1] = uVar3 & 0xff8fffff | (uint)*(byte *)(param_3 + 0x96) << 0x14;
  }
  if (wifi_dataretry == 0) {
    if (*(char *)(param_3 + 0x97) != '\0') goto LAB_0019e648;
  }
  else {
    *(char *)(param_3 + 0x98) = (char)wifi_dataretry;
    *(undefined1 *)(param_3 + 0x97) = 1;
    *(undefined1 *)(param_3 + 0x99) = 100;
LAB_0019e648:
    if (0x1f < *(byte *)(param_3 + 0x98)) {
      *(undefined1 *)(param_3 + 0x98) = 0x1f;
    }
    uVar3 = param_2[3];
    uVar4 = param_2[2];
    param_2[3] = uVar3 & 0xffff07ff;
    bVar1 = *(byte *)(param_3 + 0x98);
    param_2[2] = uVar4 & 0xff80ffff;
    param_2[3] = uVar3 & 0xffff07ff | (uint)bVar1 << 0xb;
    param_2[2] = uVar4 & 0xff80ffff | (uint)*(byte *)(param_3 + 0x99) << 0x10;
  }
  if (*(char *)(param_3 + 0x9a) == '\0') goto LAB_0019e5b0;
  param_2[2] = param_2[2] | 0x80000000;
  uVar3 = param_2[6];
  if ((*(byte *)(param_3 + 0x9c) & 0x40) != 0) {
    uVar3 = uVar3 | 0x800;
    param_2[6] = uVar3;
  }
  uVar4 = ((uint)*(byte *)(param_3 + 0x9d) << 0x1d) >> 0x1e;
  uVar3 = uVar3 | uVar4 << 0xe;
  if (uVar4 == 0) {
LAB_0019e550:
    param_2[6] = uVar3;
  }
  else {
    if (2 < uVar4) {
      uVar3 = uVar3 | 0x2000;
      goto LAB_0019e550;
    }
    uVar3 = uVar3 | 0x1000;
    param_2[6] = uVar3;
  }
  bVar1 = *(byte *)(param_3 + 0x9d);
  if (bVar1 >> 4 < 2) {
    uVar4 = 4;
  }
  else {
    uVar4 = ((uint)*(ushort *)(param_3 + 0x9c) << 0x17) >> 0x1e | 4;
  }
  param_2[6] = uVar4 | uVar3;
  iVar2 = mtf_tx_rate_to_tmi_rate
                    (((uint)bVar1 << 0x18) >> 0x1c,*(byte *)(param_3 + 0x9c) & 0xf,
                     (((uint)*(byte *)(param_3 + 0x9c) << 0x1a) >> 0x1e) + 1,
                     ((uint)*(byte *)(param_3 + 0x9d) << 0x1c) >> 0x1f,1);
  param_2[6] = param_2[6] | iVar2 << 0x10;
LAB_0019e5b0:
  if (*(char *)(param_3 + 0x9e) != '\0') {
    uVar3 = param_2[3];
    param_2[3] = uVar3 & 0xefffffff;
    param_2[3] = uVar3 & 0xefffffff | (uint)*(byte *)(param_3 + 0xa1) << 0x1c;
  }
  if (*(char *)(param_3 + 0x9f) != '\0') {
    uVar3 = param_2[2];
    param_2[2] = uVar3 & 0xc0ffffff;
    param_2[2] = uVar3 & 0xc0ffffff | (uint)*(byte *)(param_3 + 0xa2) << 0x18;
  }
  if (*(char *)(param_3 + 0xa0) != '\0') {
    uVar3 = param_2[5];
    param_2[5] = uVar3 & 0xfffffbff;
    uVar3 = uVar3 & 0xfffffb00 | (uint)*(byte *)(param_3 + 0x87) << 10;
    param_2[5] = uVar3;
    param_2[5] = uVar3 | *(byte *)(param_3 + 0x86);
  }
  return;
}

