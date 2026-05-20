// module: mt7915.ko
// function: BN_num_bits @ 0x20d170
// size: 56 bytes
//

int BN_num_bits(BIGNUM *a)

{
  int iVar1;
  int iVar2;
  
  if (a == (BIGNUM *)0x0) {
    return 0;
  }
  if (a->top == 0) {
    return 0;
  }
  iVar2 = a->top + -1;
  iVar1 = BN_num_bits_word(a->d[iVar2]);
  return iVar1 + iVar2 * 0x20;
}

