// module: mt7915.ko
// function: BN_clear_bit @ 0x20e6cc
// size: 72 bytes
//

int BN_clear_bit(BIGNUM *a,int n)

{
  int iVar1;
  
  if ((-1 < n) && (iVar1 = n >> 5, iVar1 < a->top)) {
    a->d[iVar1] = a->d[iVar1] & ~(1 << (n & 0x1fU));
    bn_correct_top();
    return 1;
  }
  return 0;
}

