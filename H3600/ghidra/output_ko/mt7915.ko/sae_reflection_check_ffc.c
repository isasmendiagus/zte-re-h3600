// module: mt7915.ko
// function: sae_reflection_check_ffc @ 0x2085ec
// size: 96 bytes
//

short sae_reflection_check_ffc(int param_1)

{
  int iVar1;
  
  if (*(BIGNUM **)(param_1 + 0x50) == (BIGNUM *)0x0) {
    return 0;
  }
  iVar1 = Bignum_UnsignedCompare(*(BIGNUM **)(param_1 + 0x50),*(BIGNUM **)(param_1 + 0x28));
  if ((iVar1 == 0) && (*(BIGNUM **)(param_1 + 0x54) != (BIGNUM *)0x0)) {
    iVar1 = Bignum_UnsignedCompare(*(BIGNUM **)(param_1 + 0x54),*(BIGNUM **)(param_1 + 0x58));
    return -(ushort)(iVar1 == 0);
  }
  return 0;
}

