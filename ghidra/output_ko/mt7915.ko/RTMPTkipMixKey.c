// module: mt7915.ko
// function: RTMPTkipMixKey @ 0x11798c
// size: 1220 bytes
//

void RTMPTkipMixKey(byte *param_1,byte *param_2,uint param_3,uint param_4,byte *param_5,
                   uint *param_6)

{
  int iVar1;
  byte bVar2;
  byte bVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  bool bVar11;
  uint local_38;
  
  uVar4 = param_4 >> 0x10;
  param_4 = param_4 & 0xffff;
  param_3 = param_3 & 0xffff;
  uVar7 = 0;
  param_6[1] = uVar4;
  *param_6 = param_4;
  local_38 = (uint)*param_2 + (uint)param_2[1] * 0x100;
  param_6[2] = local_38;
  uVar8 = (uint)param_2[2] + (uint)param_2[3] * 0x100;
  param_6[3] = uVar8;
  uVar9 = (uint)param_2[4] + (uint)param_2[5] * 0x100;
  param_6[4] = uVar9;
  do {
    uVar5 = uVar7 & 1;
    iVar1 = uVar5 * 2;
    uVar10 = (uint)param_1[uVar5 * 2] + (uint)param_1[iVar1 + 1] * 0x100 ^ uVar9;
    uVar6 = uVar10 & 0xff;
    uVar10 = uVar10 >> 8;
    param_4 = param_4 + (*(int *)(Tkip_Sbox_Lower + uVar6 * 4) +
                         *(int *)(Tkip_Sbox_Upper + uVar6 * 4) * 0x100 ^
                        *(int *)(Tkip_Sbox_Upper + uVar10 * 4) +
                        *(int *)(Tkip_Sbox_Lower + uVar10 * 4) * 0x100) & 0xffff;
    *param_6 = param_4;
    uVar10 = (uint)param_1[iVar1 + 4] + (uint)param_1[iVar1 + 5] * 0x100 ^ param_4;
    uVar6 = uVar10 & 0xff;
    uVar10 = uVar10 >> 8;
    uVar4 = uVar4 + (*(int *)(Tkip_Sbox_Lower + uVar6 * 4) +
                     *(int *)(Tkip_Sbox_Upper + uVar6 * 4) * 0x100 ^
                    *(int *)(Tkip_Sbox_Upper + uVar10 * 4) +
                    *(int *)(Tkip_Sbox_Lower + uVar10 * 4) * 0x100) & 0xffff;
    param_6[1] = uVar4;
    uVar10 = (uint)param_1[iVar1 + 8] + (uint)param_1[iVar1 + 9] * 0x100 ^ uVar4;
    uVar6 = uVar10 & 0xff;
    uVar10 = uVar10 >> 8;
    local_38 = local_38 +
               (*(int *)(Tkip_Sbox_Lower + uVar6 * 4) +
                *(int *)(Tkip_Sbox_Upper + uVar6 * 4) * 0x100 ^
               *(int *)(Tkip_Sbox_Upper + uVar10 * 4) +
               *(int *)(Tkip_Sbox_Lower + uVar10 * 4) * 0x100) & 0xffff;
    param_6[2] = local_38;
    uVar10 = (uint)param_1[iVar1 + 0xc] + (uint)param_1[iVar1 + 0xd] * 0x100 ^ local_38;
    uVar6 = uVar10 & 0xff;
    uVar10 = uVar10 >> 8;
    uVar8 = uVar8 + (*(int *)(Tkip_Sbox_Lower + uVar6 * 4) +
                     *(int *)(Tkip_Sbox_Upper + uVar6 * 4) * 0x100 ^
                    *(int *)(Tkip_Sbox_Upper + uVar10 * 4) +
                    *(int *)(Tkip_Sbox_Lower + uVar10 * 4) * 0x100) & 0xffff;
    param_6[3] = uVar8;
    uVar10 = (uint)param_1[uVar5 * 2] + (uint)param_1[iVar1 + 1] * 0x100 ^ uVar8;
    uVar5 = uVar10 & 0xff;
    uVar10 = uVar10 >> 8;
    uVar9 = uVar7 + ((*(int *)(Tkip_Sbox_Lower + uVar5 * 4) +
                      *(int *)(Tkip_Sbox_Upper + uVar5 * 4) * 0x100 ^
                     *(int *)(Tkip_Sbox_Upper + uVar10 * 4) +
                     *(int *)(Tkip_Sbox_Lower + uVar10 * 4) * 0x100) + uVar9 & 0xffff);
    uVar7 = uVar7 + 1;
    uVar9 = uVar9 & 0xffff;
    param_6[4] = uVar9;
  } while (uVar7 != 8);
  uVar10 = uVar9 + param_3 & 0xffff;
  uVar7 = (uint)*param_1 + (uint)param_1[1] * 0x100 ^ uVar10;
  uVar5 = uVar7 & 0xff;
  uVar7 = uVar7 >> 8;
  param_4 = (*(int *)(Tkip_Sbox_Lower + uVar5 * 4) + *(int *)(Tkip_Sbox_Upper + uVar5 * 4) * 0x100 ^
            *(int *)(Tkip_Sbox_Upper + uVar7 * 4) + *(int *)(Tkip_Sbox_Lower + uVar7 * 4) * 0x100) +
            param_4;
  uVar7 = param_4 ^ (uint)param_1[2] + (uint)param_1[3] * 0x100;
  uVar5 = (uVar7 << 0x10) >> 0x18;
  uVar7 = uVar7 & 0xff;
  uVar4 = (*(int *)(Tkip_Sbox_Lower + uVar7 * 4) + *(int *)(Tkip_Sbox_Upper + uVar7 * 4) * 0x100 ^
          *(int *)(Tkip_Sbox_Upper + uVar5 * 4) + *(int *)(Tkip_Sbox_Lower + uVar5 * 4) * 0x100) +
          uVar4;
  uVar7 = (uint)param_1[4] + (uint)param_1[5] * 0x100 ^ uVar4;
  uVar5 = (uVar7 << 0x10) >> 0x18;
  uVar7 = uVar7 & 0xff;
  local_38 = (*(int *)(Tkip_Sbox_Lower + uVar7 * 4) + *(int *)(Tkip_Sbox_Upper + uVar7 * 4) * 0x100
             ^ *(int *)(Tkip_Sbox_Upper + uVar5 * 4) + *(int *)(Tkip_Sbox_Lower + uVar5 * 4) * 0x100
             ) + local_38;
  uVar7 = (uint)param_1[6] + (uint)param_1[7] * 0x100 ^ local_38;
  uVar5 = (uVar7 << 0x10) >> 0x18;
  uVar7 = uVar7 & 0xff;
  uVar8 = (*(int *)(Tkip_Sbox_Lower + uVar7 * 4) + *(int *)(Tkip_Sbox_Upper + uVar7 * 4) * 0x100 ^
          *(int *)(Tkip_Sbox_Upper + uVar5 * 4) + *(int *)(Tkip_Sbox_Lower + uVar5 * 4) * 0x100) +
          uVar8;
  uVar5 = (uint)param_1[8] + (uint)param_1[9] * 0x100 ^ uVar8;
  uVar7 = (uVar5 << 0x10) >> 0x18;
  uVar5 = uVar5 & 0xff;
  uVar9 = (*(int *)(Tkip_Sbox_Lower + uVar5 * 4) + *(int *)(Tkip_Sbox_Upper + uVar5 * 4) * 0x100 ^
          *(int *)(Tkip_Sbox_Upper + uVar7 * 4) + *(int *)(Tkip_Sbox_Lower + uVar7 * 4) * 0x100) +
          uVar9;
  uVar7 = (uint)param_1[10] + (uint)param_1[0xb] * 0x100 ^ uVar9;
  uVar5 = (uVar7 << 0x10) >> 0x18;
  uVar7 = uVar7 & 0xff;
  uVar10 = (*(int *)(Tkip_Sbox_Lower + uVar7 * 4) + *(int *)(Tkip_Sbox_Upper + uVar7 * 4) * 0x100 ^
           *(int *)(Tkip_Sbox_Upper + uVar5 * 4) + *(int *)(Tkip_Sbox_Lower + uVar5 * 4) * 0x100) +
           uVar10;
  uVar7 = (uint)param_1[0xc] + (uint)param_1[0xd] * 0x100 ^ uVar10;
  if ((uVar7 & 1) == 0) {
    uVar7 = (uVar7 << 0x10) >> 0x11;
  }
  else {
    uVar7 = uVar7 >> 1 | 0x8000;
  }
  param_4 = param_4 + (uVar7 & 0xffff);
  uVar7 = (uint)param_1[0xe] + (uint)param_1[0xf] * 0x100 ^ param_4;
  if ((uVar7 & 1) == 0) {
    uVar7 = (uVar7 << 0x10) >> 0x11;
  }
  else {
    uVar7 = uVar7 >> 1 | 0x8000;
  }
  uVar4 = uVar4 + (uVar7 & 0xffff);
  if ((uVar4 & 1) == 0) {
    uVar7 = uVar4 * 0x10000 >> 0x11;
  }
  else {
    uVar7 = uVar4 >> 1 | 0x8000;
  }
  local_38 = local_38 + (uVar7 & 0xffff);
  if ((local_38 & 1) == 0) {
    uVar7 = local_38 * 0x10000 >> 0x11;
  }
  else {
    uVar7 = local_38 >> 1 | 0x8000;
  }
  uVar8 = uVar8 + (uVar7 & 0xffff);
  if ((uVar8 & 1) == 0) {
    uVar7 = uVar8 * 0x10000 >> 0x11;
  }
  else {
    uVar7 = uVar8 >> 1 | 0x8000;
  }
  uVar9 = uVar9 + (uVar7 & 0xffff);
  bVar11 = (uVar9 & 1) != 0;
  if (bVar11) {
    uVar7 = uVar9 >> 1;
  }
  else {
    uVar7 = uVar9 * 0x10000 >> 0x11;
  }
  param_5[2] = (byte)param_3;
  bVar2 = (byte)(param_3 >> 8);
  if (bVar11) {
    uVar7 = uVar7 | 0x8000;
  }
  *param_5 = bVar2;
  param_5[1] = bVar2 & 0x5f | 0x20;
  uVar10 = uVar10 + (uVar7 & 0xffff);
  bVar2 = param_1[1];
  bVar3 = *param_1;
  param_5[0xe] = (byte)uVar10;
  param_5[4] = (byte)param_4;
  param_5[6] = (byte)uVar4;
  param_5[7] = (byte)(uVar4 >> 8);
  param_5[0xf] = (byte)(uVar10 >> 8);
  param_5[5] = (byte)(param_4 >> 8);
  param_5[3] = (byte)((uVar10 ^ (uint)bVar3 + (uint)bVar2 * 0x100) >> 1);
  param_5[8] = (byte)local_38;
  param_5[9] = (byte)(local_38 >> 8);
  param_5[10] = (byte)uVar8;
  param_5[0xb] = (byte)(uVar8 >> 8);
  param_5[0xc] = (byte)uVar9;
  param_5[0xd] = (byte)(uVar9 >> 8);
  return;
}

