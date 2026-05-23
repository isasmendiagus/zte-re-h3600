// module: mt7915.ko
// function: BN_mask_bits @ 0x20e714
// size: 92 bytes
//

int BN_mask_bits(BIGNUM *a,int n)

{
  int iVar1;
  
  if (n < 0) {
    return 0;
  }
  iVar1 = n >> 5;
  if (a->top <= iVar1) {
    return 0;
  }
  if ((n & 0x1fU) == 0) {
    a->top = iVar1;
  }
  else {
    a->top = iVar1 + 1;
    a->d[iVar1] = a->d[iVar1] & ~(-1 << (n & 0x1fU));
  }
  bn_correct_top();
  return 1;
}

