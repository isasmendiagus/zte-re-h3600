// module: mt7915.ko
// function: RT_SHA256_Hash @ 0x125b78
// size: 548 bytes
//

void RT_SHA256_Hash(uint *param_1)

{
  int *piVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint *puVar11;
  int iVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  uint *puVar19;
  uint *puVar20;
  uint uVar21;
  uint uVar22;
  uint uVar23;
  uint local_164 [9];
  uint local_140 [5];
  uint local_12c [66];
  
  puVar11 = local_12c + 1;
  puVar19 = param_1 + 10;
  do {
    puVar20 = puVar19 + 4;
    uVar4 = puVar19[1];
    uVar7 = puVar19[2];
    uVar10 = puVar19[3];
    *puVar11 = *puVar19;
    puVar11[1] = uVar4;
    puVar11[2] = uVar7;
    puVar11[3] = uVar10;
    puVar11 = puVar11 + 4;
    puVar19 = puVar20;
  } while (puVar20 != param_1 + 0x1a);
  puVar11 = local_12c;
  do {
    puVar11 = puVar11 + 1;
    uVar4 = *puVar11;
    *puVar11 = uVar4 << 0x18 | (uVar4 >> 8 & 0xff) << 0x10 | (uVar4 >> 0x10 & 0xff) << 8 |
               uVar4 >> 0x18;
  } while (puVar11 != local_12c + 0x10);
  puVar11 = local_12c + 2;
  uVar8 = *param_1;
  uVar2 = param_1[2];
  uVar5 = param_1[1];
  uVar21 = param_1[3];
  uVar22 = param_1[5];
  uVar9 = param_1[4];
  uVar3 = param_1[6];
  local_12c[0] = param_1[7];
  uVar6 = 0;
  uVar4 = local_12c[0];
  uVar7 = uVar9;
  uVar10 = uVar8;
  uVar23 = uVar2;
  uVar16 = uVar5;
  uVar17 = uVar3;
  uVar18 = uVar21;
  local_164[4] = uVar22;
  while( true ) {
    uVar15 = uVar23;
    uVar14 = uVar10;
    uVar13 = uVar7;
    piVar1 = &DAT_00298744 + uVar6;
    uVar6 = uVar6 + 1;
    iVar12 = ((uVar13 >> 6 | uVar13 << 0x1a) ^ (uVar13 >> 0xb | uVar13 << 0x15) ^
             (uVar13 >> 0x19 | uVar13 << 7)) + (uVar13 & local_164[4] ^ uVar17 & ~uVar13) + *piVar1
             + uVar4 + local_12c[1];
    uVar7 = uVar18 + iVar12;
    uVar10 = ((uVar16 ^ uVar15) & uVar14 ^ uVar16 & uVar15) +
             ((uVar14 >> 2 | uVar14 << 0x1e) ^ (uVar14 >> 0xd | uVar14 << 0x13) ^
             (uVar14 >> 0x16 | uVar14 << 10)) + iVar12;
    if (uVar6 == 0x40) break;
    if (uVar6 < 0x10) {
      local_12c[1] = *puVar11;
    }
    else {
      uVar4 = puVar11[-2];
      uVar23 = puVar11[-0xf];
      local_12c[1] = puVar11[-0x10] + puVar11[-7] +
                     ((uVar4 >> 0x11 | uVar4 << 0xf) ^ (uVar4 >> 0x13 | uVar4 << 0xd) ^ uVar4 >> 10)
                     + ((uVar23 >> 7 | uVar23 << 0x19) ^ (uVar23 >> 0x12 | uVar23 << 0xe) ^
                       uVar23 >> 3);
      *puVar11 = local_12c[1];
    }
    puVar11 = puVar11 + 1;
    uVar4 = uVar17;
    uVar23 = uVar16;
    uVar16 = uVar14;
    uVar17 = local_164[4];
    uVar18 = uVar15;
    local_164[4] = uVar13;
  }
  *param_1 = uVar10 + uVar8;
  param_1[1] = uVar14 + uVar5;
  param_1[6] = local_164[4] + uVar3;
  param_1[2] = uVar16 + uVar2;
  param_1[3] = uVar15 + uVar21;
  param_1[4] = uVar7 + uVar9;
  param_1[5] = uVar13 + uVar22;
  param_1[7] = uVar17 + local_12c[0];
  __memzero(param_1 + 10);
  param_1[0x1a] = 0;
  return;
}

