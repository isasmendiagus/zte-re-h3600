// module: mt7915.ko
// function: sae_derive_commit @ 0x20aa58
// size: 376 bytes
//

bool sae_derive_commit(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  bool bVar3;
  int iVar4;
  undefined4 local_24 [2];
  
  local_24[0] = 0;
  if (4 < DebugLevel) {
    printk("==> %s()\n","sae_derive_commit");
  }
  iVar4 = 100;
  log_time_begin(0,param_1 + 0xd8);
  do {
    Bignum_Free(param_1 + 0x60);
    uVar1 = sae_gen_rand(param_1);
    *(undefined4 *)(param_1 + 0x60) = uVar1;
    Bignum_Free(local_24);
    local_24[0] = sae_gen_rand(param_1);
    if ((*(int *)(param_1 + 0x50) == 0) &&
       (Bignum_Init(param_1 + 0x50,local_24[0]), *(int *)(param_1 + 0x50) == 0)) break;
    Bignum_Mod_Add(*(undefined4 *)(param_1 + 0x60),local_24[0],*(undefined4 *)(param_1 + 0x78),
                   param_1 + 0x50);
    iVar2 = Bignum_is_zero(*(undefined4 *)(param_1 + 0x50));
    if ((iVar2 == 0) && (iVar2 = Bignum_is_one(*(undefined4 *)(param_1 + 0x50)), iVar2 == 0)) {
      log_time_end(1,"derive_commit_scalar_time",3,param_1 + 0xd8);
      log_time_begin(0,param_1 + 0xec);
      if ((*(int *)(param_1 + 0x6c) == 0) || (*(int *)(param_1 + 0x98) == 0)) {
        bVar3 = true;
      }
      else {
        iVar4 = (**(code **)(*(int *)(param_1 + 0x98) + 0x10))(param_1,local_24[0]);
        bVar3 = iVar4 == 0;
      }
      log_time_end(1,"derive_commit_element_time",3,param_1 + 0xec);
      goto LAB_0020aba0;
    }
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  bVar3 = true;
LAB_0020aba0:
  Bignum_Free(local_24);
  return bVar3;
}

