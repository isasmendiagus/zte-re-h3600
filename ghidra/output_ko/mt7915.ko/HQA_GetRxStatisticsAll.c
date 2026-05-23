// module: mt7915.ko
// function: HQA_GetRxStatisticsAll @ 0x274a88
// size: 2048 bytes
//

undefined4 HQA_GetRxStatisticsAll(int param_1,undefined4 param_2,int param_3)

{
  byte bVar1;
  longlong lVar2;
  uint *puVar3;
  undefined4 *puVar4;
  uint *puVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  undefined4 *puVar9;
  byte bVar10;
  int iVar11;
  byte *pbVar12;
  uint *puVar13;
  undefined4 *puVar14;
  uint *puVar15;
  undefined4 *puVar16;
  uint *puVar17;
  uint *puVar18;
  undefined4 *puVar19;
  uint *puVar20;
  undefined4 *puVar21;
  uint *puVar22;
  byte bVar23;
  uint *puVar24;
  uint uVar25;
  byte *pbVar26;
  uint uVar27;
  undefined4 *puVar28;
  uint *puVar29;
  uint *puVar30;
  undefined4 *puVar31;
  undefined1 auStack_274 [2];
  ushort local_272;
  ushort local_270;
  ushort local_26e;
  ushort local_26c;
  uint local_268;
  ushort local_264;
  ushort local_262;
  ushort local_260;
  ushort local_25e;
  ushort local_25c;
  ushort local_25a;
  ushort local_258;
  ushort local_256;
  ushort local_254;
  ushort local_252;
  byte bStack_229;
  byte local_228 [4];
  byte local_224 [4];
  uint local_220;
  uint local_21c;
  uint local_218;
  uint local_214;
  uint local_210;
  uint local_20c;
  uint local_208;
  uint local_204;
  uint local_200;
  uint local_1fc;
  uint local_1e8;
  uint local_1e4;
  uint local_1e0;
  uint local_1dc;
  uint local_1d8;
  uint local_1d4;
  uint local_1d0;
  uint local_1cc;
  uint local_1c8;
  uint local_1c4;
  uint local_1c0;
  uint local_1bc;
  uint local_1b8 [4];
  uint local_1a8 [4];
  uint local_198 [4];
  uint local_188 [6];
  uint local_170;
  uint local_16c;
  uint local_168;
  uint local_164;
  uint local_160;
  uint local_14c;
  uint local_148;
  uint local_144;
  uint local_140;
  uint local_13c;
  uint local_138;
  uint local_134;
  uint local_130;
  uint local_12c;
  uint local_128;
  uint local_11c;
  uint local_118;
  uint local_114;
  uint local_110;
  uint local_10c;
  uint local_e8 [16];
  uint local_a8 [16];
  uint local_68 [17];
  
  net_ad_wrap_service();
  net_ad_wrap_service(param_1);
  if (*(char *)(param_1 + 0x79504d) != '\0') {
    net_ad_wrap_service(param_1);
    net_ad_wrap_service(param_1);
  }
  __memzero(&local_220,0x1f8);
  __memzero(auStack_274,0x54);
  if (*(char *)(param_1 + 0x79504d) == '\0') {
    puVar21 = (undefined4 *)(param_1 + 0xa3b7e0);
    puVar19 = (undefined4 *)(param_1 + 0xa3b7f0);
    puVar14 = (undefined4 *)(param_1 + 0xa7bfe0);
    puVar31 = (undefined4 *)(param_1 + 0xa7bff0);
    puVar28 = (undefined4 *)(param_1 + 0xa7bfd0);
    puVar16 = (undefined4 *)(param_1 + 0xa3b7d0);
    puVar4 = (undefined4 *)(param_1 + 0xa7bf80);
    puVar9 = (undefined4 *)(param_1 + 0xa3b780);
    iVar11 = 0;
    do {
      puVar14 = puVar14 + 1;
      iVar11 = iVar11 + 1;
      puVar21 = puVar21 + 1;
      *puVar21 = *puVar14;
      puVar31 = puVar31 + 1;
      puVar19 = puVar19 + 1;
      *puVar19 = *puVar31;
      puVar28 = puVar28 + 1;
      puVar16 = puVar16 + 1;
      *puVar16 = *puVar28;
      puVar4 = puVar4 + 1;
      puVar9 = puVar9 + 1;
      *puVar9 = *puVar4;
    } while (iVar11 != 4);
    bVar1 = 1;
  }
  else {
    *(undefined4 *)(param_1 + 0xa3b7e4) = *(undefined4 *)(param_1 + 0xa7bfe4);
    bVar1 = 2;
    *(undefined4 *)(param_1 + 0xa3b7f4) = *(undefined4 *)(param_1 + 0xa7bff4);
    *(undefined4 *)(param_1 + 0xa3b7d4) = *(undefined4 *)(param_1 + 0xa7bfd4);
    *(undefined4 *)(param_1 + 0xa3b784) = *(undefined4 *)(param_1 + 0xa7bf84);
    *(undefined4 *)(param_1 + 0xa3b7e8) = *(undefined4 *)(param_1 + 0xa7bfe8);
    *(undefined4 *)(param_1 + 0xa3b7f8) = *(undefined4 *)(param_1 + 0xa7bff8);
    *(undefined4 *)(param_1 + 0xa3b7d8) = *(undefined4 *)(param_1 + 0xa7bfd8);
    *(undefined4 *)(param_1 + 0xa3b788) = *(undefined4 *)(param_1 + 0xa7bf88);
    *(undefined4 *)(param_1 + 0xa3b7ec) = *(undefined4 *)(param_1 + 0xa7c14c);
    *(undefined4 *)(param_1 + 0xa3b7fc) = *(undefined4 *)(param_1 + 0xa7c15c);
    *(undefined4 *)(param_1 + 0xa3b7dc) = *(undefined4 *)(param_1 + 0xa7c13c);
    *(undefined4 *)(param_1 + 0xa3b78c) = *(undefined4 *)(param_1 + 0xa7c0ec);
    *(undefined4 *)(param_1 + 0xa3b7f0) = *(undefined4 *)(param_1 + 0xa7c150);
    *(undefined4 *)(param_1 + 0xa3b800) = *(undefined4 *)(param_1 + 0xa7c160);
    *(undefined4 *)(param_1 + 0xa3b7e0) = *(undefined4 *)(param_1 + 0xa7c140);
    *(undefined4 *)(param_1 + 0xa3b790) = *(undefined4 *)(param_1 + 0xa7c0f0);
  }
  puVar20 = (uint *)(param_1 + 0xa3b7e0);
  puVar18 = (uint *)(param_1 + 0xa3b7f0);
  puVar13 = (uint *)(param_1 + 0xa3b708);
  puVar17 = (uint *)(param_1 + 0xa3b790);
  puVar15 = (uint *)(param_1 + 0xa3b810);
  puVar24 = (uint *)(param_1 + 0xa7bf40);
  puVar3 = (uint *)(param_1 + 0xa7bf90);
  puVar5 = (uint *)(param_1 + 0xa7c010);
  iVar11 = 0;
  puVar30 = puVar15;
  puVar22 = puVar13;
  puVar29 = puVar17;
  do {
    puVar24 = puVar24 + 1;
    iVar11 = iVar11 + 1;
    puVar22 = puVar22 + 1;
    *puVar22 = *puVar24;
    puVar3 = puVar3 + 1;
    puVar29 = puVar29 + 1;
    *puVar29 = *puVar3;
    puVar5 = puVar5 + 1;
    puVar30 = puVar30 + 1;
    *puVar30 = *puVar5;
  } while (iVar11 != 0x10);
  bVar23 = 0;
  do {
    chip_get_rx_stat(param_1,bVar23,auStack_274);
    bVar10 = bVar23 + 1;
    uVar6 = (uint)local_272;
    if (bVar23 == 1) {
      local_1c0 = uVar6 << 0x18 | (uint)(local_272 >> 8) << 0x10;
      *(uint *)(param_1 + 0xa3b760) = uVar6;
      *(uint *)(param_1 + 0xa3b764) = local_268;
      local_1bc = local_268 << 0x18 | (local_268 >> 8 & 0xff) << 0x10 |
                  (local_268 >> 0x10 & 0xff) << 8 | local_268 >> 0x18;
      local_148 = (uint)local_270 << 0x18 | (uint)(local_270 >> 8) << 0x10;
      local_14c = (uint)local_26c << 0x18 | (uint)(local_26c >> 8) << 0x10;
      local_144 = (uint)local_260 << 0x18 | (uint)(local_260 >> 8) << 0x10;
      local_140 = (uint)local_25e << 0x18 | (uint)(local_25e >> 8) << 0x10;
      local_13c = (uint)local_25c << 0x18 | (uint)(local_25c >> 8) << 0x10;
      local_138 = (uint)local_25a << 0x18 | (uint)(local_25a >> 8) << 0x10;
      local_134 = (uint)local_258 << 0x18 | (uint)(local_258 >> 8) << 0x10;
      local_130 = (uint)local_256 << 0x18 | (uint)(local_256 >> 8) << 0x10;
      local_12c = (uint)local_254 << 0x18 | (uint)(local_254 >> 8) << 0x10;
      local_128 = (uint)local_252 << 0x18 | (uint)(local_252 >> 8) << 0x10;
      break;
    }
    *(uint *)(param_1 + 0xa3b758) = uVar6;
    local_220 = uVar6 << 0x18 | (uint)(local_272 >> 8) << 0x10;
    *(uint *)(param_1 + 0xa3b75c) = local_268;
    local_21c = local_268 << 0x18 | (local_268 >> 8 & 0xff) << 0x10 |
                (local_268 >> 0x10 & 0xff) << 8 | local_268 >> 0x18;
    local_1c4 = (uint)local_270 << 0x18 | (uint)(local_270 >> 8) << 0x10;
    local_1c8 = (uint)local_26c << 0x18 | (uint)(local_26c >> 8) << 0x10;
    local_210 = (uint)local_260 << 0x18 | (uint)(local_260 >> 8) << 0x10;
    local_20c = (uint)local_25e << 0x18 | (uint)(local_25e >> 8) << 0x10;
    local_208 = (uint)local_25c << 0x18 | (uint)(local_25c >> 8) << 0x10;
    local_204 = (uint)local_25a << 0x18 | (uint)(local_25a >> 8) << 0x10;
    local_200 = (uint)local_258 << 0x18 | (uint)(local_258 >> 8) << 0x10;
    local_1fc = (uint)local_256 << 0x18 | (uint)(local_256 >> 8) << 0x10;
    local_1e8 = (uint)local_254 << 0x18 | (uint)(local_254 >> 8) << 0x10;
    local_1e4 = (uint)local_252 << 0x18 | (uint)(local_252 >> 8) << 0x10;
    bVar23 = bVar10;
  } while (bVar10 < bVar1);
  local_10c = (uint)local_26e << 0x18 | (uint)(local_26e >> 8) << 0x10;
  uVar6 = *(uint *)(param_1 + 0xa3b74c);
  uVar25 = *(uint *)(param_1 + 0xa3b804);
  local_1e0 = uVar6 << 0x18 | (uVar6 >> 8 & 0xff) << 0x10 | (uVar6 >> 0x10 & 0xff) << 8 |
              uVar6 >> 0x18;
  local_218 = (uint)local_264 << 0x18 | (uint)(local_264 >> 8) << 0x10;
  local_11c = uVar25 << 0x18 | (uVar25 >> 8 & 0xff) << 0x10 | (uVar25 >> 0x10 & 0xff) << 8 |
              uVar25 >> 0x18;
  local_214 = (uint)local_262 << 0x18 | (uint)(local_262 >> 8) << 0x10;
  local_170 = 0;
  if (*(char *)(param_1 + 0x79504d) != '\0') {
    uVar6 = *(uint *)(param_1 + 0xa3b750);
    local_170 = uVar6 << 0x18 | (uVar6 >> 8 & 0xff) << 0x10 | (uVar6 >> 0x10 & 0xff) << 8 |
                uVar6 >> 0x18;
  }
  pbVar26 = &bStack_229;
  pbVar12 = local_228 + 3;
  iVar11 = 0;
  do {
    puVar20 = puVar20 + 1;
    uVar6 = *puVar20;
    iVar7 = iVar11 + 1;
    local_1b8[iVar11] =
         uVar6 << 0x18 | (uVar6 >> 8 & 0xff) << 0x10 | (uVar6 >> 0x10 & 0xff) << 8 | uVar6 >> 0x18;
    puVar18 = puVar18 + 1;
    uVar25 = *puVar18;
    pbVar26 = pbVar26 + 1;
    bVar1 = *pbVar26;
    uVar6 = (uint)(char)bVar1;
    local_1a8[iVar11] =
         uVar25 << 0x18 | (uVar25 >> 8 & 0xff) << 0x10 | (uVar25 >> 0x10 & 0xff) << 8 |
         uVar25 >> 0x18;
    pbVar12 = pbVar12 + 1;
    bVar23 = *pbVar12;
    uVar25 = (uint)(char)bVar23;
    local_198[iVar11] =
         (uint)bVar1 << 0x18 | (uVar6 >> 8 & 0xff) << 0x10 | (uVar6 >> 0x10 & 0xff) << 8 |
         uVar6 >> 0x18;
    local_188[iVar11] =
         (uint)bVar23 << 0x18 | (uVar25 >> 8 & 0xff) << 0x10 | (uVar25 >> 0x10 & 0xff) << 8 |
         uVar25 >> 0x18;
    iVar11 = iVar7;
  } while (iVar7 != 4);
  uVar6 = *(uint *)(param_1 + 0xa3b7dc);
  uVar25 = *(uint *)(param_1 + 0xa3b7d4);
  uVar8 = *(uint *)(param_1 + 0xa3b7d8);
  uVar27 = *(uint *)(param_1 + 0xa3b7e0);
  local_1dc = uVar25 << 0x18 | (uVar25 >> 8 & 0xff) << 0x10 | (uVar25 >> 0x10 & 0xff) << 8 |
              uVar25 >> 0x18;
  local_16c = uVar6 << 0x18 | (uVar6 >> 8 & 0xff) << 0x10 | (uVar6 >> 0x10 & 0xff) << 8 |
              uVar6 >> 0x18;
  uVar6 = *(uint *)(param_1 + 0xa3b784);
  local_1d8 = uVar8 << 0x18 | (uVar8 >> 8 & 0xff) << 0x10 | (uVar8 >> 0x10 & 0xff) << 8 |
              uVar8 >> 0x18;
  local_168 = uVar27 << 0x18 | (uVar27 >> 8 & 0xff) << 0x10 | (uVar27 >> 0x10 & 0xff) << 8 |
              uVar27 >> 0x18;
  uVar25 = *(uint *)(param_1 + 0xa3b788);
  local_1d0 = uVar6 << 0x18 | (uVar6 >> 8 & 0xff) << 0x10 | (uVar6 >> 0x10 & 0xff) << 8 |
              uVar6 >> 0x18;
  uVar6 = *(uint *)(param_1 + 0xa3b78c);
  local_1cc = uVar25 << 0x18 | (uVar25 >> 8 & 0xff) << 0x10 | (uVar25 >> 0x10 & 0xff) << 8 |
              uVar25 >> 0x18;
  uVar25 = *(uint *)(param_1 + 0xa3b790);
  local_164 = uVar6 << 0x18 | (uVar6 >> 8 & 0xff) << 0x10 | (uVar6 >> 0x10 & 0xff) << 8 |
              uVar6 >> 0x18;
  local_160 = uVar25 << 0x18 | (uVar25 >> 8 & 0xff) << 0x10 | (uVar25 >> 0x10 & 0xff) << 8 |
              uVar25 >> 0x18;
  do {
    puVar13 = puVar13 + 1;
    uVar6 = *puVar13;
    if (uVar6 != 0) {
      iVar11 = *(byte *)(param_1 + 0xa3ad65) + 1;
      lVar2 = (longlong)iVar11 * (longlong)(int)uVar6;
      uVar25 = (uint)lVar2;
      uVar8 = (int)((ulonglong)lVar2 >> 0x20) << 3 | uVar25 >> 0x1d;
      iVar7 = (uVar8 << 5 | uVar25 * 8 >> 0x1b) - (uVar8 + (uVar25 * 0x100 < uVar25 * 8));
      lVar2 = lVar2 + CONCAT44((iVar7 * 0x40 | uVar25 * 0xf8 >> 0x1a) -
                               (iVar7 + (uint)(uVar25 * 0x3e00 < uVar25 * 0xf8)),uVar25 * 0x3d08);
      lVar2 = lVar2 + CONCAT44((int)((ulonglong)lVar2 >> 0x20) * 4 | (uint)lVar2 >> 0x1e,
                               (uint)lVar2 * 4);
      uVar25 = (uint)lVar2;
      uVar25 = uVar25 * 0x80 >> 0x17 |
               ((int)((ulonglong)lVar2 >> 0x20) * 0x80 | uVar25 >> 0x19) << 9;
      if (0x80000 < (int)uVar6) {
        uVar25 = uVar25 - (iVar11 * 10000000 >> 3);
      }
      *puVar13 = uVar25;
    }
  } while (puVar13 != (uint *)(param_1 + 0xa3b748));
  puVar30 = (uint *)(param_1 + 0xa3b70c);
  uVar25 = *(uint *)(param_1 + 0xa3b70c);
  uVar8 = *(uint *)(param_1 + 0xa3b808);
  uVar6 = *(uint *)(param_1 + 0xa3b80c);
  local_1d4 = uVar25 << 0x18 | (uVar25 >> 8 & 0xff) << 0x10 | (uVar25 >> 0x10 & 0xff) << 8 |
              uVar25 >> 0x18;
  uVar25 = *(uint *)(param_1 + 0xa3b810);
  local_118 = uVar8 << 0x18 | (uVar8 >> 8 & 0xff) << 0x10 | (uVar8 >> 0x10 & 0xff) << 8 |
              uVar8 >> 0x18;
  local_114 = uVar6 << 0x18 | (uVar6 >> 8 & 0xff) << 0x10 | (uVar6 >> 0x10 & 0xff) << 8 |
              uVar6 >> 0x18;
  local_110 = uVar25 << 0x18 | (uVar25 >> 8 & 0xff) << 0x10 | (uVar25 >> 0x10 & 0xff) << 8 |
              uVar25 >> 0x18;
  uVar6 = local_1d4;
  iVar11 = 0;
  while( true ) {
    puVar17 = puVar17 + 1;
    uVar25 = *puVar17;
    local_e8[iVar11] = uVar6;
    local_a8[iVar11] =
         uVar25 << 0x18 | (uVar25 >> 8 & 0xff) << 0x10 | (uVar25 >> 0x10 & 0xff) << 8 |
         uVar25 >> 0x18;
    if (iVar11 + 1 == 0x10) break;
    puVar30 = puVar30 + 1;
    uVar6 = *puVar30;
    uVar6 = uVar6 << 0x18 | (uVar6 >> 8 & 0xff) << 0x10 | (uVar6 >> 0x10 & 0xff) << 8 |
            uVar6 >> 0x18;
    iVar11 = iVar11 + 1;
  }
  iVar11 = 0;
  do {
    iVar7 = iVar11 + 1;
    puVar15 = puVar15 + 1;
    uVar6 = *puVar15;
    local_68[iVar11] =
         uVar6 << 0x18 | (uVar6 >> 8 & 0xff) << 0x10 | (uVar6 >> 0x10 & 0xff) << 8 | uVar6 >> 0x18;
    iVar11 = iVar7;
  } while (iVar7 != 0x10);
  puVar16 = (undefined4 *)(param_1 + 0xa3b7d4);
  iVar7 = 0;
  iVar11 = DebugLevel;
  do {
    if (2 < iVar11) {
      printk("%s(): Report[0]: RCPI[%d]:%d\n","HQA_GetRxStatisticsAll",iVar7,*puVar16);
      iVar11 = DebugLevel;
    }
    iVar7 = iVar7 + 1;
    puVar16 = puVar16 + 1;
  } while (iVar7 != 4);
  iVar7 = 0;
  puVar16 = (undefined4 *)(param_1 + 0xa3b7e4);
  do {
    if (2 < iVar11) {
      printk("%s(): Report[1]: FAGC_RSSI_IB[%d]:%d\n","HQA_GetRxStatisticsAll",iVar7,*puVar16);
      iVar11 = DebugLevel;
    }
    iVar7 = iVar7 + 1;
    puVar16 = puVar16 + 1;
  } while (iVar7 != 4);
  iVar7 = 0;
  puVar16 = (undefined4 *)(param_1 + 0xa3b7f4);
  do {
    if (2 < iVar11) {
      printk("%s(): Report[2]: FAGC_RSSI_WB[%d]:%d\n","HQA_GetRxStatisticsAll",iVar7,*puVar16);
      iVar11 = DebugLevel;
    }
    iVar7 = iVar7 + 1;
    puVar16 = puVar16 + 1;
  } while (iVar7 != 4);
  iVar7 = 0;
  puVar16 = (undefined4 *)(param_1 + 0xa3b814);
  do {
    if (2 < iVar11) {
      printk("%s(): Report[3]: user idx: %d, fcs_error_cnt: %d, FreqOffsetFromRX: %d, SNR: %d\n",
             "HQA_GetRxStatisticsAll",iVar7,*puVar16,puVar16[-0x42],puVar16[-0x20]);
    }
    iVar7 = iVar7 + 1;
    puVar16 = puVar16 + 1;
    iVar11 = DebugLevel;
  } while (iVar7 != 0x10);
  memcpy((void *)(param_3 + 0xe),&local_220,0x1f8);
  FUN_0026cdd0(param_3,param_2,0x1fa,0);
  return 0;
}

