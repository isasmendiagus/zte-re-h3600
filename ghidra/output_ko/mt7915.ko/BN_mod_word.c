// module: mt7915.ko
// function: BN_mod_word @ 0x2112f8
// size: 176 bytes
//

ulong BN_mod_word(BIGNUM *a,ulong w)

{
  BIGNUM *a_00;
  ulong uVar1;
  int extraout_r1;
  ulong extraout_r1_00;
  uint uVar2;
  ulong *puVar3;
  ulong *puVar4;
  
  if (w != 0) {
    if (w < 0x10001) {
      if (a->top + -1 < 0) {
        uVar1 = 0;
      }
      else {
        puVar4 = a->d;
        uVar1 = 0;
        puVar3 = puVar4 + a->top;
        do {
          puVar3 = puVar3 + -1;
          uVar2 = *puVar3;
          __aeabi_uidivmod(uVar1 << 0x10 | uVar2 >> 0x10,w);
          __aeabi_uidivmod(uVar2 & 0xffff | extraout_r1 << 0x10,w);
          uVar1 = extraout_r1_00;
        } while (puVar3 != puVar4);
      }
      return uVar1;
    }
    a_00 = BN_dup(a);
    if (a_00 != (BIGNUM *)0x0) {
      uVar1 = 0;
      if (a_00->top != 0) {
        uVar1 = FUN_00210b14(a_00,w);
      }
      BN_free(a_00);
      return uVar1;
    }
  }
  return 0xffffffff;
}

