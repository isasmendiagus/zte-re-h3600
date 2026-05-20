// module: mt7915.ko
// function: mtf_write_tmac_info_fixed_rate @ 0x19dae0
// size: 1076 bytes
//

void mtf_write_tmac_info_fixed_rate(int param_1,uint *param_2,ushort *param_3,ushort *param_4)

{
  byte bVar1;
  byte bVar2;
  ushort uVar3;
  int iVar4;
  uint uVar5;
  uint *puVar6;
  uint uVar7;
  uint uVar8;
  
  uVar8 = (uint)(byte)param_3[0xe];
  iVar4 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  __memzero(param_2,0x20);
  uVar3 = *param_3;
  uVar5 = HcGetMaxStaNum(param_1);
  if (uVar3 < uVar5) {
    puVar6 = (uint *)((uint)*param_3 * 0x14c0 + param_1);
  }
  else {
    puVar6 = (uint *)0x0;
  }
  uVar7 = *(int *)(param_3 + 10) + 0x20U | *param_2;
  *param_2 = uVar7;
  if (uVar3 < uVar5) {
    puVar6 = puVar6 + 0x28748;
  }
  if ((char)param_3[0x16] == '\x01') {
    uVar7 = uVar7 | 0x1800000;
    *param_2 = uVar7;
  }
  if (uVar8 < 4) {
    uVar5 = param_2[1];
    *param_2 = uVar7 | (uint)(byte)(&UNK_0029da48)[(uint)(byte)param_3[0x15] * 4 + uVar8] << 0x19;
  }
  else if (uVar8 - 0x14 < 4) {
    uVar5 = param_2[1] | 0x40000000;
    *param_2 = uVar7 | (uVar8 - 4) * 0x2000000;
    param_2[1] = uVar5;
  }
  else {
    uVar5 = param_2[1];
    *param_2 = uVar7 | uVar8 << 0x19;
  }
  uVar3 = *param_3;
  param_2[1] = uVar5 | uVar3;
  uVar7 = uVar5 | uVar3 | (uint)(byte)((byte)param_3[0xc] >> 1) << 0xb;
  uVar8 = uVar7 | 0x20000;
  param_2[1] = uVar8;
  if (*(char *)((int)param_3 + 0x19) != '\0') {
    uVar8 = uVar7 | 0x60000;
    param_2[1] = uVar8;
  }
  uVar8 = uVar8 | (uint)*(byte *)((int)param_3 + 0xd) << 0x14;
  param_2[1] = uVar8;
  if (puVar6 == (uint *)0x0) {
LAB_0019dc00:
    uVar8 = uVar8 | (uint)*(byte *)((int)param_3 + 0x29) << 0x18;
  }
  else if (*puVar6 == 0x40001) {
    uVar8 = uVar8 | (uint)*(byte *)(param_1 + (uint)(ushort)puVar6[0x38] * 0x620 + 0x2fa7d) << 0x18;
  }
  else {
    if ((*puVar6 & 0xfffffbff) == 0) goto LAB_0019dc00;
    uVar8 = uVar8 | (uint)*(byte *)(puVar6[2] + 0x29) << 0x18;
  }
  uVar8 = uVar8 | 0x80000000;
  param_2[1] = uVar8;
  if ((char)param_3[0x16] == '\x01') {
    uVar7 = (byte)param_3[0x11] & 0xf | param_2[2];
    param_2[2] = uVar7;
    param_2[2] = uVar7 | (*(byte *)((int)param_3 + 0x21) & 0x30) << 4;
  }
  if ((char)param_3[3] != '\0') {
    param_2[2] = param_2[2] | 0x400;
  }
  if (*(char *)((int)param_3 + 0x1d) == '\x02') {
    if (puVar6 == (uint *)0x0) {
      uVar3 = *param_3;
    }
    else {
      uVar3 = *(ushort *)(puVar6[2] + 0x9a0);
      *param_3 = uVar3;
      uVar8 = param_2[1];
    }
    param_2[1] = uVar3 | uVar8;
    param_2[2] = param_2[2] | 0x800;
  }
  if (*(char *)((int)param_3 + 9) != '\0') {
    param_2[2] = param_2[2] | 0x1000;
  }
  if ((*(byte *)((int)param_3 + 0x21) < 2) && (*(char *)(iVar4 + 0x225) != '\0')) {
    *(undefined1 *)(param_3 + 5) = 1;
  }
  else if ((char)param_3[5] == '\0') {
    uVar8 = param_2[2];
    goto LAB_0019dc6c;
  }
  uVar8 = param_2[2] | 0x2000;
  param_2[2] = uVar8;
LAB_0019dc6c:
  if (*(char *)((int)param_3 + 0x31) == '\0') {
    uVar8 = uVar8 | 0x80000000;
  }
  param_2[2] = uVar8 & 0xc0ffffff;
  param_2[2] = uVar8 & 0xc0ffffff | ((byte)param_3[0x18] & 0x3f) << 0x18;
  if (*(char *)((int)param_3 + 5) == '\0') {
    uVar8 = param_2[3] | 0xf801;
  }
  else {
    uVar8 = param_2[3] | 0x7800;
  }
  param_2[3] = uVar8;
  if (*(char *)((int)param_3 + 0x1d) == '\x01') {
    param_2[3] = param_2[3] | 2;
  }
  if ((*(char *)(iVar4 + 0x146) == '\x01') && (*(char *)((int)param_3 + 0x2b) != '\0')) {
    param_2[3] = param_2[3] | 0x20;
  }
  if ((char)param_3[0x14] != '\0') {
    param_2[3] = param_2[3] | 0x20000000;
  }
  if ((char)param_3[2] != '\0') {
    uVar8 = param_2[3];
    param_2[3] = uVar8 | 0x80000000;
    param_2[3] = uVar8 | 0x80000000 | (param_3[7] & 0xfff) << 0x10;
  }
  uVar8 = param_2[5];
  if ((char)param_3[0x17] != '\0') {
    uVar8 = uVar8 | 0x200;
    param_2[5] = uVar8;
  }
  if (*(char *)((int)param_3 + 0x2d) != '\0') {
    uVar8 = uVar8 | 0x400;
    param_2[5] = uVar8;
  }
  uVar8 = uVar8 | (byte)param_3[6];
  param_2[5] = uVar8;
  if (*(char *)((int)param_3 + 0x2f) != '\0') {
    param_2[5] = uVar8 | 0x4000;
  }
  if (*(char *)((int)param_3 + 0x31) == '\0') {
    if ((*param_4 & 0x40) == 0) {
      uVar8 = param_2[6];
    }
    else {
      uVar8 = param_2[6] | 0x800;
      param_2[6] = uVar8;
    }
    uVar8 = uVar8 | (((uint)*(byte *)((int)param_4 + 1) << 0x1e) >> 0x1f) << 0xe;
    param_2[6] = uVar8;
    uVar7 = ((uint)*(byte *)((int)param_4 + 1) << 0x18) >> 0x1d;
    if (*(byte *)((int)param_4 + 1) >> 5 < 2) {
      param_2[6] = uVar8 | 4;
      bVar2 = (byte)*param_4;
      if (uVar7 != 0) {
        uVar5 = 1;
      }
      bVar1 = *(byte *)((int)param_4 + 1);
      if (uVar7 == 0) {
        uVar5 = (uint)(byte)param_3[0x10];
      }
    }
    else {
      uVar5 = 1;
      param_2[6] = uVar8 | ((uint)*param_4 << 0x17) >> 0x1e | 4;
      bVar2 = (byte)*param_4;
      bVar1 = *(byte *)((int)param_4 + 1);
    }
    iVar4 = mtf_tx_rate_to_tmi_rate(uVar7,bVar2 & 0x3f,1,((uint)bVar1 << 0x1d) >> 0x1f,uVar5);
    param_2[6] = param_2[6] | iVar4 << 0x10;
  }
  uVar5 = param_2[7] | (uint)(byte)param_3[0xf] << 0xb;
  param_2[7] = uVar5;
  uVar5 = uVar5 | (uint)(byte)param_3[0x11] << 0x10;
  param_2[7] = uVar5;
  param_2[7] = uVar5 | (uint)*(byte *)((int)param_3 + 0x21) << 0x14;
  return;
}

