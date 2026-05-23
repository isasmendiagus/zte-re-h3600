// module: mt7915.ko
// function: parse_RXV_packet_v2 @ 0xc5e48
// size: 1060 bytes
//

void parse_RXV_packet_v2(int param_1,int param_2,int param_3,byte *param_4)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  ushort uVar4;
  byte bVar5;
  bool bVar6;
  uint uVar7;
  uint *puVar8;
  short sVar9;
  byte *pbVar10;
  byte *pbVar11;
  int iVar12;
  uint *puVar13;
  uint *puVar14;
  uint *puVar15;
  undefined4 uVar16;
  uint uVar17;
  
  if (param_2 == 2) {
    pbVar11 = param_4 + 4;
    pbVar10 = param_4;
    if (((**(byte **)(param_3 + 0x1c) & 0xc) == 8) &&
       (((*(char *)(param_1 + 0xa37233) == '\0' ||
         (uVar4 = *(ushort *)(param_3 + 0x4e),
         uVar7 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0)), uVar7 <= uVar4)) ||
        (*(int *)((uint)*(ushort *)(param_3 + 0x4e) * 0x14c0 + param_1 + 0xa1d20) != 0x10))))
    goto LAB_000c5ef0;
  }
  else {
    if (param_2 != 1) {
      if (DebugLevel < 3) {
        return;
      }
      printk("%s(): invalid Type %u\n","parse_RXV_packet_v2",param_2);
      return;
    }
    *(undefined4 *)(param_3 + 100) = *(undefined4 *)(param_4 + 0x20);
    pbVar10 = param_4 + 8;
    pbVar11 = param_4 + 0xc;
    *(undefined4 *)(param_3 + 0x68) = *(undefined4 *)(param_4 + 0x24);
    uVar16 = *(undefined4 *)(param_4 + 0x28);
    *(undefined4 *)(param_3 + 0x6c) = uVar16;
    *(undefined4 *)(param_1 + (int)(&UNK_0029e278 + (uint)param_4[6] % 10) * 4 + 4) = uVar16;
    if (*(int *)(param_1 + 0xa7c228) != 0) {
      if ((param_4[9] & 0x70) == 0) {
        sVar9 = (short)(((uint)param_4[0x19] << 2 | (uint)(param_4[0x18] >> 6) |
                        (param_4[0x1a] & 1) << 10) * 0x7d >> 8);
      }
      else {
        uVar17 = (uint)param_4[0x19] << 2 | (uint)(param_4[0x18] >> 6);
        uVar7 = (uint)(short)(ushort)(((uVar17 | (uint)param_4[0x1a] << 10) << 0x14) >> 0x14);
        if (0x7ff < uVar7) {
          uVar7 = (uVar17 | (uint)param_4[0x1a] << 10 & 0xfff) - 0x1000;
        }
        sVar9 = (short)((1 << ((param_4[10] & 1) << 1 | (uint)(param_4[9] >> 7)) + 1 & 0xfU) * 10000
                        * uVar7 * 2 >> 0x10);
      }
      *(int *)(param_1 + 0xa7bf44) = (int)sVar9;
      *(uint *)(param_1 + 0xa7bfd4) = (uint)param_4[0x14];
      puVar8 = (uint *)(param_1 + 0xa7bff4);
      puVar13 = (uint *)(param_1 + 0xa7bfe4);
      *(uint *)(param_1 + 0xa7bfd8) = (uint)param_4[0x15];
      *(uint *)(param_1 + 0xa7bfdc) = (uint)param_4[0x16];
      *(uint *)(param_1 + 0xa7bfe0) = (uint)param_4[0x17];
      uVar7 = (uint)param_4[0x12];
      *(uint *)(param_1 + 0xa7bfe4) = uVar7;
      uVar17 = (uint)param_4[0x13];
      *(uint *)(param_1 + 0xa7bff4) = uVar17;
      *(uint *)(param_1 + 0xa7bfe8) = (uint)param_4[0x12];
      *(uint *)(param_1 + 0xa7bff8) = (uint)param_4[0x13];
      *(uint *)(param_1 + 0xa7bfec) = (uint)param_4[0x12];
      *(uint *)(param_1 + 0xa7bffc) = (uint)param_4[0x13];
      *(uint *)(param_1 + 0xa7bff0) = (uint)param_4[0x12];
      *(uint *)(param_1 + 0xa7c000) = (uint)param_4[0x13];
      iVar12 = 0;
      *(uint *)(param_1 + 0xa7bf94) = (((uint)param_4[0x1b] << 0x19) >> 0x1a) - 0x10;
      puVar14 = puVar13;
      puVar15 = puVar8;
      while( true ) {
        iVar12 = iVar12 + 1;
        if (0x7f < (int)uVar7) {
          *puVar13 = uVar7 - 0x100;
        }
        if (0x7f < (int)uVar17) {
          *puVar8 = uVar17 - 0x100;
        }
        puVar13 = puVar13 + 1;
        puVar8 = puVar8 + 1;
        if (iVar12 == 4) break;
        puVar14 = puVar14 + 1;
        uVar7 = *puVar14;
        puVar15 = puVar15 + 1;
        uVar17 = *puVar15;
      }
    }
    if (((*(uint *)(param_1 + 0xa3ac14) & 1) != 0) ||
       ((*(int *)(param_1 + 0xa77bb4) == 1 &&
        ((*(uint *)(*(int *)(param_1 + 0xa77bb8) + 0x4e0) & 1) != 0)))) {
      MT_ATEUpdateRxStatistic(param_1,0,param_4);
    }
  }
  *(char *)(param_3 + 0x58) = (char)((int)(param_4[0xc] - 0xdc) / 2);
  *(char *)(param_3 + 0x59) = (char)((int)(param_4[0xd] - 0xdc) / 2);
  *(char *)(param_3 + 0x5a) = (char)((int)(param_4[0xe] - 0xdc) / 2);
  *(char *)(param_3 + 0x5b) = (char)((int)(param_4[0xf] - 0xdc) / 2);
  param_4 = pbVar10;
LAB_000c5ef0:
  uVar7 = ((uint)param_4[1] << 0x19) >> 0x1d;
  *(byte *)(param_3 + 99) = *(byte *)(param_3 + 99) & 0x1f | (byte)(uVar7 << 5);
  bVar1 = *param_4;
  *(byte *)(param_3 + 0x62) = *(byte *)(param_3 + 0x62) & 0xc0 | bVar1 & 0x3f;
  *(byte *)(param_3 + 0x62) =
       *(byte *)(param_3 + 0x62) & 0xbf | (byte)((((uint)param_4[1] << 0x1e) >> 0x1f) << 6);
  *(ushort *)(param_3 + 0x62) =
       *(ushort *)(param_3 + 0x62) & 0xfe7f |
       ((param_4[2] & 1) << 1 | (ushort)(param_4[1] >> 7)) << 7;
  bVar2 = *param_4;
  bVar3 = *(byte *)(param_3 + 99);
  bVar6 = (param_4[1] & 1) != 0;
  bVar5 = (bVar6 || (char)bVar2 < '\0') << 2;
  *(byte *)(param_3 + 99) = bVar3 & 0xfb | bVar5;
  *(byte *)(param_3 + 99) = bVar3 & 0xf9 | bVar5 | (byte)((((uint)param_4[2] << 0x1c) >> 0x1f) << 1)
  ;
  if ((3 < uVar7) && (!bVar6 && (char)bVar2 >= '\0')) {
    *(byte *)(param_3 + 0x62) =
         *(byte *)(param_3 + 0x62) & 0xc0 |
         bVar1 & 0x3f | (byte)((((uint)pbVar11[3] << 0x1b) >> 0x1e) << 4);
    return;
  }
  return;
}

