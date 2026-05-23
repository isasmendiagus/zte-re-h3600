// module: mt7915.ko
// function: BN_rand_range @ 0x216654
// size: 408 bytes
//

int BN_rand_range(BIGNUM *rnd,BIGNUM *range)

{
  int bits;
  int iVar1;
  int iVar2;
  
  if (range->neg != 0) {
    return 0;
  }
  if (range == (BIGNUM *)0x0) {
    bits = BN_num_bits((BIGNUM *)0x0);
    if (bits != 1) goto LAB_002166a4;
  }
  else {
    if (range->top == 0) {
      return 0;
    }
    bits = BN_num_bits(range);
    if (bits != 1) {
      if (((-1 < bits + -2) && (iVar2 = FUN_0020cf74(range), iVar2 != 0)) ||
         ((-1 < bits + -3 && (iVar2 = FUN_0020cf74(range), iVar2 != 0)))) {
        iVar2 = 100;
        while( true ) {
          iVar1 = BN_rand(rnd,bits,-1,0);
          if (iVar1 == 0) {
            return 0;
          }
          iVar2 = iVar2 + -1;
          if (iVar2 == 0) break;
          iVar1 = BN_cmp(rnd,range);
          if (iVar1 < 0) {
            return 1;
          }
        }
        return 0;
      }
LAB_002166a4:
      iVar2 = 100;
      while( true ) {
        iVar1 = BN_rand(rnd,bits + 1,-1,0);
        if (iVar1 == 0) {
          return 0;
        }
        iVar1 = BN_cmp(rnd,range);
        if (iVar1 < 0) break;
        iVar1 = BN_sub(rnd,rnd,range);
        if (iVar1 == 0) {
          return 0;
        }
        iVar1 = BN_cmp(rnd,range);
        if (iVar1 < 0) break;
        iVar1 = BN_sub(rnd,rnd,range);
        if (iVar1 == 0) {
          return 0;
        }
        iVar2 = iVar2 + -1;
        if (iVar2 == 0) {
          return 0;
        }
        iVar1 = BN_cmp(rnd,range);
        if (iVar1 < 0) {
          return 1;
        }
      }
      if (iVar2 != 1) {
        return 1;
      }
      return 0;
    }
  }
  if (rnd == (BIGNUM *)0x0) {
    return 1;
  }
  rnd->top = 0;
  rnd->neg = 0;
  return 1;
}

