// module: mt7915.ko
// function: RT_SHA384_Hash @ 0x126000
// size: 1188 bytes
//

void RT_SHA384_Hash(uint *param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint *puVar10;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  uint uVar19;
  uint uVar20;
  uint uVar21;
  uint uVar22;
  uint uVar23;
  int iVar24;
  uint uVar25;
  uint uVar26;
  uint uVar27;
  uint uVar28;
  uint uVar29;
  uint uVar30;
  uint uVar31;
  uint uVar32;
  uint uVar33;
  uint uVar34;
  uint local_388;
  uint uStack_384;
  uint local_380;
  uint uStack_37c;
  uint local_378;
  uint uStack_374;
  uint local_370;
  uint uStack_36c;
  uint local_320 [8];
  uint local_300;
  uint uStack_2fc;
  uint local_2f8;
  uint uStack_2f4;
  uint local_2d8 [10];
  uint local_2b0 [163];
  uint *puVar11;
  
  memcpy(local_2b0 + 2,param_1 + 0x12,0x80);
  puVar10 = local_2b0;
  do {
    puVar11 = puVar10 + 2;
    uVar1 = *puVar11;
    uVar9 = puVar10[3];
    puVar10[3] = uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 |
                 uVar1 >> 0x18;
    *puVar11 = uVar9 << 0x18 | (uVar9 >> 8 & 0xff) << 0x10 | (uVar9 >> 0x10 & 0xff) << 8 |
               uVar9 >> 0x18;
    puVar10 = puVar11;
  } while (puVar11 != local_2b0 + 0x20);
  puVar10 = local_2b0 + 4;
  uVar2 = *param_1;
  uVar6 = param_1[1];
  uVar13 = param_1[2];
  uVar21 = param_1[3];
  uVar25 = param_1[4];
  uVar28 = param_1[5];
  uVar3 = param_1[6];
  uVar7 = param_1[7];
  uVar4 = param_1[0xc];
  uVar8 = param_1[0xd];
  uVar14 = param_1[8];
  uVar22 = param_1[9];
  uVar26 = param_1[10];
  uVar29 = param_1[0xb];
  local_2b0[0] = param_1[0xe];
  local_2b0[1] = param_1[0xf];
  local_2f8 = local_2b0[2];
  uStack_2f4 = local_2b0[3];
  uVar1 = uVar2;
  uVar9 = uVar6;
  uVar16 = uVar14;
  uVar17 = uVar22;
  uVar20 = 0;
  local_388 = uVar13;
  uStack_384 = uVar21;
  local_380 = uVar25;
  uStack_37c = uVar28;
  local_378 = uVar4;
  uStack_374 = uVar8;
  local_370 = uVar26;
  uStack_36c = uVar29;
  local_320[2] = uVar3;
  local_320[3] = uVar7;
  local_300 = local_2b0[0];
  uStack_2fc = local_2b0[1];
  while( true ) {
    uVar33 = uVar17;
    uVar32 = uVar16;
    uVar31 = uVar9;
    uVar30 = uVar1;
    uVar34 = uVar20 + 1;
    uVar27 = (uVar32 << 0x17 | uVar33 >> 9) ^
             (uVar32 >> 0x12 | uVar33 << 0xe) ^ (uVar32 >> 0xe | uVar33 << 0x12);
    uVar1 = local_378 & ~uVar32 ^ local_370 & uVar32;
    uVar16 = uVar1 + uVar27;
    uVar17 = (&DAT_00298888)[uVar20 * 2] + uVar16;
    uVar18 = local_300 + uVar17;
    uVar9 = (uVar30 << 0x19 | uVar31 >> 7) ^
            (uVar30 << 0x1e | uVar31 >> 2) ^ (uVar30 >> 0x1c | uVar31 << 4);
    uVar5 = (local_388 ^ local_380) & uVar30 ^ local_388 & local_380;
    uVar19 = local_2f8 + uVar18;
    iVar24 = uStack_2f4 +
             uStack_2fc +
             (&DAT_0029888c)[uVar20 * 2] +
             (uStack_374 & ~uVar33 ^ uStack_36c & uVar33) +
             ((uVar33 << 0x17 | uVar32 >> 9) ^
             (uVar33 >> 0x12 | uVar32 << 0xe) ^ (uVar33 >> 0xe | uVar32 << 0x12)) +
             (uint)CARRY4(uVar1,uVar27) + (uint)CARRY4((&DAT_00298888)[uVar20 * 2],uVar16) +
             (uint)CARRY4(local_300,uVar17) + (uint)CARRY4(local_2f8,uVar18);
    uVar20 = uVar5 + uVar9;
    uVar16 = local_320[2] + uVar19;
    uVar17 = local_320[3] + iVar24 + (uint)CARRY4(local_320[2],uVar19);
    uVar1 = uVar20 + uVar19;
    uVar9 = ((uStack_384 ^ uStack_37c) & uVar31 ^ uStack_384 & uStack_37c) +
            ((uVar31 << 0x19 | uVar30 >> 7) ^
            (uVar31 << 0x1e | uVar30 >> 2) ^ (uVar31 >> 0x1c | uVar30 << 4)) +
            (uint)CARRY4(uVar5,uVar9) + iVar24 + (uint)CARRY4(uVar20,uVar19);
    if (uVar34 == 0x50) break;
    if (uVar34 < 0x10) {
      local_2f8 = *puVar10;
      uStack_2f4 = puVar10[1];
    }
    else {
      uVar12 = puVar10[-3];
      uVar5 = puVar10[-4];
      uVar15 = puVar10[-0x1e];
      uVar23 = puVar10[-0x1d];
      uVar18 = (uVar5 >> 6 | uVar12 << 0x1a) ^
               (uVar5 << 3 | uVar12 >> 0x1d) ^ (uVar5 >> 0x13 | uVar12 << 0xd);
      uVar19 = puVar10[-0xe] + puVar10[-0x20];
      uVar27 = uVar19 + uVar18;
      uVar20 = (uVar15 >> 7 | uVar23 << 0x19) ^
               (uVar15 >> 8 | uVar23 << 0x18) ^ (uVar15 >> 1 | uVar23 << 0x1f);
      local_2f8 = uVar27 + uVar20;
      uStack_2f4 = puVar10[-0xd] + puVar10[-0x1f] + (uint)CARRY4(puVar10[-0xe],puVar10[-0x20]) +
                   (uVar12 >> 6 ^ (uVar12 << 3 | uVar5 >> 0x1d) ^ (uVar12 >> 0x13 | uVar5 << 0xd)) +
                   (uint)CARRY4(uVar19,uVar18) +
                   (uVar23 >> 7 ^ (uVar23 >> 8 | uVar15 << 0x18) ^ (uVar23 >> 1 | uVar15 << 0x1f)) +
                   (uint)CARRY4(uVar27,uVar20);
      *puVar10 = local_2f8;
      puVar10[1] = uStack_2f4;
    }
    puVar10 = puVar10 + 2;
    local_320[2] = local_380;
    local_320[3] = uStack_37c;
    local_300 = local_378;
    uStack_2fc = uStack_374;
    local_380 = local_388;
    uStack_37c = uStack_384;
    local_378 = local_370;
    uStack_374 = uStack_36c;
    uVar20 = uVar34;
    local_388 = uVar30;
    uStack_384 = uVar31;
    local_370 = uVar32;
    uStack_36c = uVar33;
  }
  *param_1 = uVar1 + uVar2;
  param_1[1] = uVar9 + uVar6 + (uint)CARRY4(uVar1,uVar2);
  param_1[2] = uVar13 + uVar30;
  param_1[3] = uVar21 + uVar31 + (uint)CARRY4(uVar13,uVar30);
  param_1[4] = local_388 + uVar25;
  param_1[5] = uStack_384 + uVar28 + (uint)CARRY4(local_388,uVar25);
  param_1[6] = local_380 + uVar3;
  param_1[7] = uStack_37c + uVar7 + (uint)CARRY4(local_380,uVar3);
  param_1[8] = uVar16 + uVar14;
  param_1[9] = uVar17 + uVar22 + (uint)CARRY4(uVar16,uVar14);
  param_1[10] = uVar26 + uVar32;
  param_1[0xb] = uVar29 + uVar33 + (uint)CARRY4(uVar26,uVar32);
  param_1[0xc] = local_370 + uVar4;
  param_1[0xd] = uStack_36c + uVar8 + (uint)CARRY4(local_370,uVar4);
  param_1[0xe] = local_378 + local_2b0[0];
  param_1[0xf] = uStack_374 + local_2b0[1] + (uint)CARRY4(local_378,local_2b0[0]);
  __memzero(param_1 + 0x12,0x80);
  param_1[0x32] = 0;
  return;
}

