// module: mt7915.ko
// function: sae_derive_key @ 0x209d28
// size: 520 bytes
//

bool sae_derive_key(int param_1,undefined4 param_2)

{
  uint uVar1;
  bool bVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  undefined4 *puVar6;
  undefined4 uVar7;
  int local_ac;
  uint local_a8;
  undefined4 local_a4;
  undefined1 auStack_a0 [32];
  undefined1 auStack_80 [32];
  undefined4 local_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 local_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 local_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  
  local_ac = 0;
  local_a4 = 0;
  local_a8 = 0x400;
  if (4 < DebugLevel) {
    printk("==> %s()\n","sae_derive_key");
  }
  __memzero(auStack_a0);
  RT_HMAC_SHA256(auStack_a0,0x20,param_2,*(undefined4 *)(param_1 + 100),auStack_80,0x20);
  hex_dump_with_lvl("keyseed:",auStack_80,0x20,SAE_DEBUG_LEVEL);
  os_alloc_mem(0,&local_ac,0x400);
  if (local_ac == 0) {
    bVar2 = false;
  }
  else {
    Bignum_Init(&local_a4);
    Bignum_Mod_Add(*(undefined4 *)(param_1 + 0x50),*(undefined4 *)(param_1 + 0x28),
                   *(undefined4 *)(param_1 + 0x78),&local_a4);
    Bignum_BI2Bin_with_pad(local_a4,local_ac,&local_a8,*(undefined4 *)(param_1 + 100));
    hex_dump_with_lvl("(commit-scalar + peer-commit-scalar) modulo r:",local_ac,local_a8,
                      SAE_DEBUG_LEVEL);
    uVar1 = local_a8;
    uVar3 = *(uint *)(param_1 + 100);
    if (local_a8 < uVar3) {
      Bignum_Free(&local_a4);
    }
    else {
      puVar6 = &local_60;
      uVar7 = 0x40;
      iVar4 = local_ac;
      uVar5 = local_a8;
      KDF(auStack_80,0x20,"SAE KCK and PMK",(size_t *)&DAT_0000000f);
      *(undefined4 *)(param_1 + 0x30) = local_60;
      *(undefined4 *)(param_1 + 0x34) = uStack_5c;
      *(undefined4 *)(param_1 + 0x38) = uStack_58;
      *(undefined4 *)(param_1 + 0x3c) = uStack_54;
      *(undefined4 *)(param_1 + 0x40) = local_50;
      *(undefined4 *)(param_1 + 0x44) = uStack_4c;
      *(undefined4 *)(param_1 + 0x48) = uStack_48;
      *(undefined4 *)(param_1 + 0x4c) = uStack_44;
      *(undefined4 *)(param_1 + 8) = local_40;
      *(undefined4 *)(param_1 + 0xc) = uStack_3c;
      *(undefined4 *)(param_1 + 0x10) = uStack_38;
      *(undefined4 *)(param_1 + 0x14) = uStack_34;
      *(undefined4 *)(param_1 + 0x18) = local_30;
      *(undefined4 *)(param_1 + 0x1c) = uStack_2c;
      *(undefined4 *)(param_1 + 0x20) = uStack_28;
      *(undefined4 *)(param_1 + 0x24) = uStack_24;
      hex_dump_with_lvl(&_LC57,param_1 + 0x30,0x20,SAE_DEBUG_LEVEL,iVar4,uVar5,puVar6,uVar7);
      hex_dump_with_lvl(&_LC58,param_1 + 8,0x20,SAE_DEBUG_LEVEL);
    }
    bVar2 = uVar3 <= uVar1;
    Bignum_Free(&local_a4);
    os_free_mem(local_ac);
  }
  return bVar2;
}

