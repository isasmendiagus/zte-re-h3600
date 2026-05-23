// module: mt7915.ko
// function: sae_gen_rand @ 0x20a8f0
// size: 356 bytes
//

BIGNUM * sae_gen_rand(int param_1)

{
  undefined1 uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int local_28;
  BIGNUM *local_24 [2];
  
  local_28 = 0;
  local_24[0] = (BIGNUM *)0x0;
  if (4 < DebugLevel) {
    printk("==> %s()\n","sae_gen_rand");
  }
  if ((*(int *)(param_1 + 0x78) != 0) && (os_alloc_mem(0,&local_28,0x400), local_28 != 0)) {
    iVar5 = 100;
    do {
      uVar3 = 0;
      if (*(int *)(param_1 + 0x68) != 0) {
        uVar4 = 0;
        do {
          iVar2 = local_28;
          uVar1 = RandomByte(*(undefined4 *)(*(int *)(param_1 + 0x180) + 0x1b924));
          *(undefined1 *)(iVar2 + uVar4) = uVar1;
          uVar4 = uVar4 + 1;
          uVar3 = *(uint *)(param_1 + 0x68);
        } while (uVar4 < uVar3);
      }
      hex_dump_with_lvl("rand:",local_28,uVar3,SAE_DEBUG_LEVEL);
      Bignum_Bin2BI(local_28,*(undefined4 *)(param_1 + 0x68),local_24);
      iVar2 = Bignum_is_zero(local_24[0]);
      if (((iVar2 == 0) && (iVar2 = Bignum_is_one(local_24[0]), iVar2 == 0)) &&
         (iVar2 = Bignum_UnsignedCompare(local_24[0],*(BIGNUM **)(param_1 + 0x78)), iVar2 < 0)) {
        os_free_mem(local_28);
        return local_24[0];
      }
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
    if (-1 < DebugLevel) {
      printk("%s(): gen rand fail\n","sae_gen_rand");
    }
    Bignum_Free(local_24);
    os_free_mem(local_28);
  }
  return (BIGNUM *)0x0;
}

