// module: mt7915.ko
// function: mtf_write_tmac_info_by_host @ 0x19df14
// size: 1308 bytes
//

void mtf_write_tmac_info_by_host(int param_1,uint *param_2,int param_3)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  byte bVar8;
  uint uVar9;
  byte *pbVar10;
  uint uVar11;
  ushort *puVar12;
  uint *puVar13;
  uint uVar14;
  int iVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  
  puVar13 = *(uint **)(param_3 + 0x14);
  iVar15 = *(int *)(param_3 + 0x10);
  iVar3 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  puVar12 = *(ushort **)(param_3 + 0x50);
  if (puVar12 == (ushort *)0x0) {
    if (*(int *)(param_3 + 0x14) == 0) {
      pbVar10 = (byte *)0x0;
    }
    else {
      pbVar10 = (byte *)(*(int *)(param_3 + 0x14) + 0xc4);
    }
  }
  else {
    pbVar10 = (byte *)0x0;
  }
  __memzero(param_2,0x20);
  uVar9 = (int)*(short *)(param_3 + 0x36) | *param_2;
  *param_2 = uVar9;
  uVar5 = (uint)*(byte *)(param_3 + 1);
  if (uVar5 < 4) {
    *param_2 = uVar9 | (uint)(byte)(&UNK_0029da48)[(uint)*(byte *)(param_3 + 0x20) * 4 + uVar5] <<
                       0x19;
    iVar6 = HcGetBandByWdev(iVar15);
    uVar7 = param_2[1];
    if (iVar6 != 0) {
      uVar7 = uVar7 | 0x40000000;
      param_2[1] = uVar7;
    }
  }
  else if (uVar5 - 0x14 < 4) {
    uVar7 = param_2[1] | 0x40000000;
    *param_2 = uVar9 | (uVar5 - 4) * 0x2000000;
    param_2[1] = uVar7;
  }
  else {
    uVar7 = param_2[1];
    *param_2 = uVar9 | uVar5 << 0x19;
  }
  uVar7 = uVar7 | *(ushort *)(param_3 + 0x1e);
  param_2[1] = uVar7;
  uVar5 = *(uint *)(param_3 + 0x18);
  if ((uVar5 & 0x800000) == 0) {
    uVar7 = uVar7 | (uint)(*(byte *)(param_3 + 0x2c) >> 1) << 0xb;
    uVar5 = uVar7 | 0x20000;
    param_2[1] = uVar5;
    uVar9 = (uint)*(byte *)(param_3 + 0x34);
    if (uVar9 != 0) {
      uVar5 = uVar7 | 0x60000;
      param_2[1] = uVar5;
    }
  }
  else {
    if ((uVar5 & 0x40) != 0) {
      uVar7 = uVar7 | 0x800;
      param_2[1] = uVar7;
      uVar5 = *(uint *)(param_3 + 0x18);
    }
    if ((uVar5 & 0x800) != 0) {
      uVar7 = uVar7 | 0x1000;
    }
    uVar5 = uVar7 | 0x2000;
    param_2[1] = uVar5;
    iVar6 = *(int *)(param_3 + 0xc);
    if ((*(byte *)(iVar6 + 0x30) & 0x10) != 0) {
      uVar5 = uVar7 | 0x6000;
      param_2[1] = uVar5;
      iVar6 = *(int *)(param_3 + 0xc);
    }
    uVar9 = (int)*(char *)(iVar6 + 0x35) & 0xffff;
    if (0x5dc < ((int)*(char *)(iVar6 + 0x34) & 0xffffU | uVar9 << 8)) {
      uVar5 = uVar5 | 0x8000;
      param_2[1] = uVar5;
    }
    if (*(char *)(param_3 + 0x34) != '\0') {
      uVar5 = uVar5 | 0xc0000;
      param_2[1] = uVar5;
    }
  }
  uVar5 = uVar5 | (uint)*(byte *)(param_3 + 0x1c) << 0x14;
  param_2[1] = uVar5;
  if (*(char *)(param_3 + 5) == '\x04') {
    uVar5 = uVar5 | 0x800000;
    param_2[1] = uVar5;
  }
  if ((puVar13 == (uint *)0x0) || (uVar9 = *puVar13, uVar9 != 0x40001)) {
    uVar5 = uVar5 | (uint)*(byte *)(iVar15 + 0x29) << 0x18;
  }
  else if (*(int *)(param_3 + 8) != 0) {
    uVar5 = uVar5 | (uint)*(byte *)(*(int *)(param_3 + 8) + 0x3dd) << 0x18;
  }
  param_2[1] = uVar5 | 0x80000000;
  uVar5 = param_2[2];
  if (*(char *)(param_3 + 5) == '\x01') {
    uVar5 = uVar5 | 0x400;
    param_2[2] = uVar5;
  }
  uVar5 = uVar5 | (uint)*(byte *)(param_3 + 0x2f) << 0xe;
  param_2[2] = uVar5;
  uVar7 = *(uint *)(param_3 + 0x18);
  if ((uVar7 & 0x80000) != 0) {
    param_2[2] = uVar5 | 0x80000000;
    uVar7 = *(uint *)(param_3 + 0x18);
  }
  if ((uVar7 & 2) == 0) {
    uVar5 = param_2[3] | 0xf801;
  }
  else {
    uVar5 = param_2[3] | 0x7800;
  }
  param_2[3] = uVar5;
  uVar7 = *(uint *)(param_3 + 0x18);
  if ((uVar7 & 0x20000000) != 0) {
    uVar5 = uVar5 & 0xffff07ff | 0x800;
    param_2[3] = uVar5;
    uVar7 = *(uint *)(param_3 + 0x18);
  }
  if ((uVar7 & 0x80) != 0) {
    uVar5 = uVar5 | 0xf800;
    param_2[3] = uVar5;
  }
  if ((*(uint *)(param_3 + 100) & 1) == 0) {
    uVar5 = uVar5 | 2;
    param_2[3] = uVar5;
  }
  if ((*(uint *)(param_3 + 0x18) & 0x2800000) == 0x2800000) {
    uVar5 = uVar5 | 0x10;
    param_2[3] = uVar5;
  }
  if ((*(char *)(iVar3 + 0x146) == '\x01') && ((*(uint *)(param_3 + 0x18) & 2) != 0)) {
    uVar5 = uVar5 | 0x20;
  }
  param_2[3] = uVar5 | 0x20000000;
  uVar5 = *(uint *)(param_3 + 0x18);
  if ((uVar5 & 0x40000000) != 0) {
    param_2[5] = param_2[5] & 0xfffffdff | 0x500;
    uVar5 = *(uint *)(param_3 + 0x18);
  }
  if ((uVar5 & 0x80000) != 0) {
    if (puVar12 == (ushort *)0x0) {
      uVar16 = (uint)pbVar10[3];
      uVar18 = (uint)pbVar10[5];
      uVar14 = (uint)pbVar10[4];
      uVar11 = (uint)pbVar10[0xc];
      uVar5 = (pbVar10[6] & 3) << 0xc;
      bVar1 = *pbVar10;
      uVar7 = (uint)pbVar10[2];
      bVar8 = pbVar10[7];
      bVar2 = pbVar10[8];
    }
    else {
      bVar1 = *(byte *)((int)puVar12 + 1);
      uVar5 = 0;
      bVar2 = 0;
      uVar9 = (uint)*puVar12;
      uVar18 = ((uint)bVar1 << 0x1e) >> 0x1f;
      uVar16 = ((uint)(byte)*puVar12 << 0x19) >> 0x1f;
      uVar11 = (byte)*puVar12 & 0x3f;
      uVar7 = (uVar9 << 0x17) >> 0x1e;
      uVar14 = ((uint)bVar1 << 0x1d) >> 0x1f;
      bVar1 = bVar1 >> 5;
      bVar8 = 0;
    }
    uVar17 = param_2[6];
    if (uVar16 != 0) {
      uVar17 = uVar17 | 0x800;
    }
    if (uVar16 != 0) {
      param_2[6] = uVar17;
    }
    if (1 < bVar1) {
      uVar9 = uVar7 | 4;
    }
    if (bVar1 < 2) {
      uVar9 = 4;
    }
    uVar9 = (uVar18 & 3) << 0xe | uVar5 | uVar17 | uVar9;
    if (bVar8 != 0) {
      uVar9 = uVar9 | 0x80000000;
    }
    param_2[6] = uVar9;
    if (bVar2 != 0) {
      param_2[6] = param_2[6] | 0x40000000;
    }
    if (pbVar10 == (byte *)0x0) {
      if (bVar1 < 4) {
        uVar4 = mtf_get_nsts_by_mcs(bVar1,uVar11,uVar14,0);
        if (bVar1 == 0) {
          uVar5 = ((*(uint *)(param_1 + 0x795124) ^ 0x10) << 0x1b) >> 0x1f;
        }
        else {
          uVar5 = 1;
        }
      }
      else {
        uVar4 = mtf_get_nsts_by_mcs(bVar1,uVar11,uVar14,((uVar11 << 0x1a) >> 0x1e) + 1);
        uVar5 = 1;
      }
    }
    else {
      if (bVar1 < 4) {
        uVar4 = mtf_get_nsts_by_mcs(bVar1,uVar11,uVar14,0);
        if (bVar1 == 0) {
          uVar5 = ((*(uint *)(param_1 + 0x795124) ^ 0x10) << 0x1b) >> 0x1f;
        }
        else {
          uVar5 = 1;
        }
      }
      else {
        bVar8 = pbVar10[9];
        if (bVar8 == 0) {
          bVar8 = 1;
        }
        uVar4 = mtf_get_nsts_by_mcs(bVar1,uVar11,uVar14,bVar8);
        uVar5 = 1;
      }
      if (pbVar10[0x10] == 0) {
        uVar9 = 0;
      }
      else {
        uVar9 = 0x10;
      }
      if (pbVar10[0x11] == 0) {
        uVar7 = 0;
      }
      else {
        uVar7 = 0x20;
      }
      uVar11 = uVar9 | uVar11 | uVar7;
      if (pbVar10[0x14] != 0) {
        param_2[6] = param_2[6] & 0xfffffbff;
      }
    }
    iVar3 = mtf_tx_rate_to_tmi_rate(bVar1,uVar11,uVar4,uVar14,uVar5);
    param_2[6] = param_2[6] | iVar3 << 0x10;
    uVar5 = *(uint *)(param_3 + 0x18);
  }
  if ((int)uVar5 < 0) {
    param_2[7] = param_2[7] | 0x280000;
    uVar5 = *(uint *)(param_3 + 0x18);
  }
  if ((uVar5 & 0x10000000) != 0) {
    param_2[7] = param_2[7] | 0x400;
  }
  if (pbVar10 != (byte *)0x0) {
    param_2[7] = ((int)(char)pbVar10[0x14] & 0x1fU) << 0xb | param_2[7];
  }
  if (4 < *(byte *)(param_3 + 3)) {
    param_2[7] = param_2[7] | 0x40000000;
  }
  return;
}

