// module: mt7915.ko
// function: RT_SHA1_Hash @ 0x125724
// size: 624 bytes
//

void RT_SHA1_Hash(uint *param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint *puVar5;
  uint uVar6;
  int iVar7;
  uint *puVar8;
  uint *puVar9;
  uint *puVar10;
  uint uVar11;
  uint *puVar12;
  uint uVar13;
  uint *puVar14;
  uint uVar15;
  uint uStack_178;
  uint local_174;
  uint local_170;
  uint local_16c;
  uint local_168 [39];
  uint auStack_cc [20];
  uint auStack_7c [20];
  uint auStack_2c [2];
  
  puVar5 = param_1 + 8;
  puVar14 = &uStack_178;
  do {
    puVar8 = puVar5 + 4;
    uVar2 = puVar5[1];
    uVar4 = puVar5[2];
    uVar6 = puVar5[3];
    puVar14[4] = *puVar5;
    puVar14[5] = uVar2;
    puVar14[6] = uVar4;
    puVar14[7] = uVar6;
    puVar5 = puVar8;
    puVar14 = puVar14 + 4;
  } while (puVar8 != param_1 + 0x18);
  puVar5 = &local_16c;
  puVar14 = puVar5;
  do {
    puVar14 = puVar14 + 1;
    uVar2 = *puVar14;
    *puVar14 = uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 |
               uVar2 >> 0x18;
  } while (puVar14 != local_168 + 0xf);
  puVar12 = local_168 + 0xc;
  puVar10 = local_168 + 7;
  puVar9 = local_168 + 1;
  iVar7 = 0x40;
  puVar8 = puVar5;
  do {
    puVar10 = puVar10 + 1;
    iVar7 = iVar7 + -1;
    puVar12 = puVar12 + 1;
    puVar9 = puVar9 + 1;
    puVar8 = puVar8 + 1;
    uVar2 = *puVar12 ^ *puVar10 ^ *puVar9 ^ *puVar8;
    puVar14 = puVar14 + 1;
    *puVar14 = uVar2 >> 0x1f | uVar2 << 1;
  } while (iVar7 != 0);
  local_174 = param_1[2];
  local_170 = param_1[3];
  local_16c = param_1[4];
  uVar3 = local_16c;
  uVar2 = local_174;
  uVar6 = *param_1;
  uVar4 = local_170;
  uVar11 = param_1[1];
  do {
    uVar13 = uVar4;
    uVar1 = uVar6;
    uVar4 = uVar2;
    puVar5 = puVar5 + 1;
    uVar2 = uVar11 >> 2 | uVar11 << 0x1e;
    uVar6 = *puVar5 + 0x5a827999 + (uVar1 >> 0x1b | uVar1 << 5) +
            (uVar13 & ~uVar11 ^ uVar4 & uVar11) + uVar3;
    uVar3 = uVar13;
    uVar11 = uVar1;
  } while (puVar5 != local_168 + 0x13);
  do {
    uVar11 = uVar4;
    uVar3 = uVar6;
    uVar4 = uVar2;
    puVar5 = puVar5 + 1;
    uVar2 = uVar1 >> 2 | uVar1 << 0x1e;
    uVar6 = *puVar5 + 0x6ed9eba1 + (uVar3 >> 0x1b | uVar3 << 5) + (uVar4 ^ uVar1 ^ uVar11) + uVar13;
    uVar1 = uVar3;
    uVar13 = uVar11;
  } while (puVar5 != auStack_cc);
  do {
    uVar15 = uVar6;
    uVar13 = uVar2;
    uVar1 = uVar4;
    puVar5 = puVar5 + 1;
    uVar2 = uVar3 >> 2 | uVar3 << 0x1e;
    uVar6 = *puVar5 + 0x8f1bbcdc + (uVar15 >> 0x1b | uVar15 << 5) +
            (uVar1 & uVar13 ^ (uVar1 ^ uVar13) & uVar3) + uVar11;
    uVar4 = uVar13;
    uVar3 = uVar15;
    uVar11 = uVar1;
  } while (puVar5 != auStack_7c);
  do {
    uVar11 = uVar2;
    uVar3 = uVar13;
    uVar4 = uVar6;
    puVar5 = puVar5 + 1;
    uVar2 = uVar15 >> 2 | uVar15 << 0x1e;
    uVar6 = *puVar5 + 0xca62c1d6 + (uVar4 >> 0x1b | uVar4 << 5) + (uVar11 ^ uVar15 ^ uVar3) + uVar1;
    uVar1 = uVar3;
    uVar13 = uVar11;
    uVar15 = uVar4;
  } while (puVar5 != auStack_2c);
  param_1[1] = uVar4 + param_1[1];
  *param_1 = uVar6 + *param_1;
  param_1[3] = uVar11 + local_170;
  param_1[2] = uVar2 + local_174;
  param_1[4] = uVar3 + local_16c;
  __memzero(param_1 + 8,0x40);
  param_1[0x18] = 0;
  return;
}

