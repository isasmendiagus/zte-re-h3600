// module: mt7915.ko
// function: sae_derive_pwe_ffc @ 0x207f10
// size: 1148 bytes
//

undefined4 sae_derive_pwe_ffc(int param_1)

{
  int iVar1;
  size_t sVar2;
  size_t sVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  char *pcVar7;
  undefined4 *puVar8;
  int iVar9;
  char cVar10;
  uint uVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  void *pvVar14;
  undefined4 *local_dc;
  undefined1 local_d5;
  undefined4 local_d4;
  undefined4 local_d0;
  void *local_cc;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_be;
  undefined2 local_ba;
  undefined4 local_b8;
  undefined2 local_b4;
  undefined1 auStack_b2 [32];
  char acStack_92 [110];
  
  local_d4 = 0;
  local_d0 = 0;
  local_cc = (void *)0x0;
  local_c8 = 0;
  local_c4 = 0;
  if (4 < DebugLevel) {
    printk("==> %s()\n","sae_derive_pwe_ffc");
  }
  puVar8 = (undefined4 *)(param_1 + 0x160);
  puVar6 = (undefined4 *)(param_1 + 0x166);
  iVar1 = RTMPCompareMemory(puVar8,puVar6,6);
  if (iVar1 == 1) {
    local_be = *puVar8;
    local_ba = *(undefined2 *)(param_1 + 0x164);
    local_b8 = *puVar6;
    local_b4 = *(undefined2 *)(param_1 + 0x16a);
  }
  else {
    local_be = *puVar6;
    local_ba = *(undefined2 *)(param_1 + 0x16a);
    local_b8 = *puVar8;
    local_b4 = *(undefined2 *)(param_1 + 0x164);
  }
  local_dc = &local_be;
  pcVar7 = *(char **)(param_1 + 0x174);
  sVar2 = strlen(pcVar7);
  hex_dump_with_lvl(&_LC18,pcVar7,sVar2,SAE_DEBUG_LEVEL);
  iVar1 = *(int *)(param_1 + 0x70);
  iVar9 = *(int *)(param_1 + 0x6c);
  Bignum_Init(&local_d0);
  Bignum_Init(&local_c8);
  Bignum_Init(&local_d4);
  Bignum_Init(&local_c4);
  os_alloc_mem(0,&local_cc,0x400);
  if (local_cc == (void *)0x0) {
    if (-1 < DebugLevel) {
      printk("%s: allocate fail. \n","sae_derive_pwe_ffc");
    }
    Bignum_Free(&local_d0);
    Bignum_Free(&local_c8);
    Bignum_Free(&local_d4);
    Bignum_Free(&local_c4);
    return 1;
  }
  cVar10 = '\x01';
  do {
    pcVar7 = *(char **)(param_1 + 0x174);
    sVar2 = strlen(pcVar7);
    memmove(acStack_92,pcVar7,sVar2);
    sVar2 = strlen(pcVar7);
    hex_dump_with_lvl(&_LC20,acStack_92,sVar2,SAE_DEBUG_LEVEL);
    if (*(int *)(param_1 + 0x88) != 0) {
      pcVar7 = (char *)(*(int *)(param_1 + 0x88) + 0x49);
      sVar3 = strlen(pcVar7);
      memmove(acStack_92 + sVar2,pcVar7,sVar3);
      sVar3 = strlen(pcVar7);
      sVar2 = sVar2 + sVar3;
    }
    acStack_92[sVar2] = cVar10;
    hex_dump_with_lvl("addr:",local_dc,0xc,SAE_DEBUG_LEVEL);
    hex_dump_with_lvl(&_LC20,acStack_92,sVar2 + 1,SAE_DEBUG_LEVEL);
    RT_HMAC_SHA256(local_dc,0xc,acStack_92,sVar2 + 1,auStack_b2,0x20);
    if (2 < DebugLevel) {
      uVar12 = Bignum_getlen(*(undefined4 *)(param_1 + 0x74));
      printk("%s(): z = len(p) = %d\n","sae_derive_pwe_ffc",uVar12);
    }
    hex_dump_with_lvl("pwd_seed:",auStack_b2,0x20,SAE_DEBUG_LEVEL);
    hex_dump_with_lvl("prime:",*(undefined4 *)(iVar9 + 0xc),*(undefined4 *)(iVar9 + 0x10),
                      SAE_DEBUG_LEVEL);
    uVar12 = *(undefined4 *)(iVar9 + 0xc);
    uVar11 = (uint)*(ushort *)(param_1 + 100);
    uVar13 = *(undefined4 *)(iVar9 + 0x10);
    pvVar14 = local_cc;
    KDF(auStack_b2,0x20,"SAE Hunting and Pecking",(size_t *)&DAT_00000017);
    hex_dump_with_lvl("pwd_value:",local_cc,*(undefined4 *)(param_1 + 100),SAE_DEBUG_LEVEL,uVar12,
                      uVar13,pvVar14,uVar11);
    iVar4 = memcmp(local_cc,(void *)(*(int *)(iVar9 + 0xc) +
                                    (*(size_t *)(iVar9 + 0x10) - *(int *)(param_1 + 100) & 0xff)),
                   *(size_t *)(iVar9 + 0x10));
    if (iVar4 != 1) {
      if (*(char *)(iVar9 + 0x1c) == '\0') {
        local_d5 = 1;
        Bignum_Bin2BI(&local_d5,1,&local_d0);
        Bignum_Sub(*(undefined4 *)(iVar1 + 8),local_d0,&local_c4);
        Bignum_Mod(local_c4,*(undefined4 *)(iVar1 + 0xc),&local_d0);
      }
      else {
        local_d5 = 2;
        Bignum_Bin2BI(&local_d5,1,&local_d0);
      }
      Bignum_Bin2BI(local_cc,*(undefined4 *)(iVar9 + 0x10),&local_c8);
      Bignum_Montgomery_ExpMod(local_c8,local_d0,*(undefined4 *)(iVar1 + 8),&local_d4);
      iVar4 = Bignum_is_zero(local_d4);
      if ((iVar4 == 0) && (iVar5 = Bignum_is_one(local_d4), iVar4 = DebugLevel, iVar5 == 0)) {
        *(undefined4 *)(param_1 + 0x5c) = local_d4;
        uVar12 = 0;
        if (3 < iVar4) {
          printk("%s(): Success to derive PWE\n","sae_derive_pwe_ffc");
        }
        goto LAB_00208274;
      }
    }
    cVar10 = cVar10 + '\x01';
    if (cVar10 == -0x37) {
      Bignum_Free(&local_d4);
      if (DebugLevel < 0) {
        uVar12 = 1;
      }
      else {
        uVar12 = 1;
        printk("%s(): Failed to derive PWE\n","sae_derive_pwe_ffc");
      }
LAB_00208274:
      os_free_mem(local_cc);
      Bignum_Free(&local_d0);
      Bignum_Free(&local_c8);
      Bignum_Free(&local_c4);
      return uVar12;
    }
  } while( true );
}

