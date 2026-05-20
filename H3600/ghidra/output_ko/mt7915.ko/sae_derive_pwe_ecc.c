// module: mt7915.ko
// function: sae_derive_pwe_ecc @ 0x207ac8
// size: 1092 bytes
//

undefined4 sae_derive_pwe_ecc(int param_1)

{
  byte bVar1;
  undefined1 uVar2;
  int iVar3;
  size_t sVar4;
  int iVar5;
  byte bVar6;
  undefined4 *puVar7;
  char *__s;
  undefined4 *puVar8;
  int iVar9;
  uint uVar10;
  undefined1 *puVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  uint uVar14;
  size_t local_198;
  undefined4 *local_190;
  undefined4 *local_184;
  undefined4 *local_178;
  undefined4 local_174;
  undefined4 local_170;
  undefined4 local_169;
  undefined2 local_165;
  undefined4 local_163;
  undefined2 local_15f;
  undefined1 auStack_15d [31];
  byte local_13e;
  undefined1 auStack_13d [65];
  undefined1 auStack_fc [106];
  byte abStack_92 [110];
  
  bVar1 = *(byte *)(*(int *)(param_1 + 0x180) + 0x1b91c);
  local_178 = (undefined4 *)0x0;
  local_198 = strlen(*(char **)(param_1 + 0x174));
  local_174 = 0;
  if (4 < DebugLevel) {
    printk("==> %s()\n","sae_derive_pwe_ecc");
  }
  puVar8 = (undefined4 *)(param_1 + 0x160);
  puVar7 = (undefined4 *)(param_1 + 0x166);
  iVar3 = RTMPCompareMemory(puVar8,puVar7,6);
  if (iVar3 == 1) {
    local_169 = *puVar8;
    local_165 = *(undefined2 *)(param_1 + 0x164);
    local_163 = *puVar7;
    local_15f = *(undefined2 *)(param_1 + 0x16a);
  }
  else {
    local_169 = *puVar7;
    local_165 = *(undefined2 *)(param_1 + 0x16a);
    local_163 = *puVar8;
    local_15f = *(undefined2 *)(param_1 + 0x164);
  }
  local_190 = &local_169;
  memmove(auStack_fc + 1,*(void **)(param_1 + 0x174),local_198);
  if (*(int *)(param_1 + 0x88) != 0) {
    __s = (char *)(*(int *)(param_1 + 0x88) + 0x49);
    sVar4 = strlen(__s);
    memmove(auStack_fc + local_198 + 1,__s,sVar4);
    sVar4 = strlen(__s);
    local_198 = local_198 + sVar4;
  }
  hex_dump_with_lvl("base:",auStack_fc + 1,local_198,SAE_DEBUG_LEVEL2);
  iVar9 = *(int *)(param_1 + 0x6c);
  iVar3 = *(int *)(param_1 + 0x70);
  if (local_178 == (undefined4 *)0x0 || bVar1 != 0) {
    bVar6 = 1;
    while( true ) {
      local_170 = 0;
      memcpy(abStack_92,auStack_fc + 1,local_198);
      abStack_92[local_198] = bVar6;
      RT_HMAC_SHA256(local_190,0xc,abStack_92,local_198 + 1,auStack_15d,0x20);
      uVar10 = (uint)local_13e;
      hex_dump_with_lvl("pwd_seed:",auStack_15d,0x20,SAE_DEBUG_LEVEL);
      uVar12 = *(undefined4 *)(iVar9 + 4);
      uVar14 = (uint)*(ushort *)(param_1 + 100);
      uVar13 = *(undefined4 *)(iVar9 + 8);
      puVar11 = auStack_13d;
      KDF(auStack_15d,0x20,"SAE Hunting and Pecking",(size_t *)&DAT_00000017);
      hex_dump_with_lvl("pwd_value:",auStack_13d,*(undefined4 *)(param_1 + 100),SAE_DEBUG_LEVEL,
                        uVar12,uVar13,puVar11,uVar14);
      sVar4 = *(size_t *)(param_1 + 100);
      iVar5 = memcmp(auStack_13d,
                     (void *)(*(int *)(iVar9 + 4) + (*(int *)(iVar9 + 8) - sVar4 & 0xff)),sVar4);
      if (iVar5 != 1) {
        Bignum_Bin2BI(auStack_13d,sVar4,&local_174);
        iVar5 = ecc_point_find_by_x(iVar3,local_174,&local_170,local_178 == (undefined4 *)0x0);
        if (iVar5 != 0) {
          if (local_178 == (undefined4 *)0x0) {
            ecc_point_init(&local_178);
            if (local_178 == (undefined4 *)0x0) {
              Bignum_Free(&local_174);
              Bignum_Free(&local_170);
              return 1;
            }
            uVar14 = Bignum_is_odd(local_170);
            *local_178 = local_174;
            if ((uVar10 & 1) == uVar14) {
              local_178[1] = local_170;
            }
            else {
              local_178[1] = 0;
              Bignum_Sub(*(undefined4 *)(iVar3 + 4),local_170);
              Bignum_Free(&local_170);
            }
            ecc_point_set_z_to_one(local_178);
            if (2 < DebugLevel) {
              printk("pwe->x\n");
              Bignum_Print(*local_178);
              if (0 < DebugLevel) {
                printk("pwe->y\n");
              }
              Bignum_Print(local_178[1]);
            }
            local_174 = 0;
          }
          else {
            Bignum_Free(&local_170);
            if (local_198 != 0) {
              puVar11 = auStack_fc;
              do {
                uVar2 = RandomByte(*(undefined4 *)(*(int *)(param_1 + 0x180) + 0x1b924));
                puVar11 = puVar11 + 1;
                *puVar11 = uVar2;
              } while (puVar11 != auStack_fc + local_198);
            }
          }
        }
      }
      bVar6 = bVar6 + 1;
      if (local_178 != (undefined4 *)0x0 && bVar1 < bVar6) break;
      local_170 = 0;
      if (bVar6 == 0) {
        Bignum_Free(&local_174);
        return 1;
      }
    }
  }
  local_184 = &local_174;
  Bignum_Free(local_184);
  *(undefined4 **)(param_1 + 0x5c) = local_178;
  return 0;
}

