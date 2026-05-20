// module: mt7915.ko
// function: sae_reflection_check_ecc @ 0x207484
// size: 128 bytes
//

short sae_reflection_check_ecc(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  puVar2 = *(undefined4 **)(param_1 + 0x54);
  puVar3 = *(undefined4 **)(param_1 + 0x58);
  if (((*(BIGNUM **)(param_1 + 0x50) != (BIGNUM *)0x0) &&
      (iVar1 = Bignum_UnsignedCompare(*(BIGNUM **)(param_1 + 0x50),*(BIGNUM **)(param_1 + 0x28)),
      iVar1 == 0 && puVar2 != (undefined4 *)0x0)) &&
     (iVar1 = Bignum_UnsignedCompare((BIGNUM *)*puVar2,(BIGNUM *)*puVar3), iVar1 == 0)) {
    iVar1 = Bignum_UnsignedCompare((BIGNUM *)puVar2[1],(BIGNUM *)puVar3[1]);
    return -(ushort)(iVar1 == 0);
  }
  return 0;
}

