// module: mt7915.ko
// function: BN_bin2bn @ 0x20e220
// size: 272 bytes
//

BIGNUM * BN_bin2bn(uchar *s,int len,BIGNUM *ret)

{
  byte bVar1;
  uint uVar2;
  BIGNUM *pBVar3;
  ulong *extraout_r1;
  ulong *puVar4;
  ulong *extraout_r1_00;
  uint uVar5;
  byte *pbVar6;
  byte *pbVar7;
  uint uVar8;
  int words;
  BIGNUM *a;
  bool bVar9;
  
  if (ret == (BIGNUM *)0x0) {
    ret = BN_new();
    puVar4 = extraout_r1_00;
    a = ret;
    if (ret == (BIGNUM *)0x0) {
      return (BIGNUM *)0x0;
    }
  }
  else {
    puVar4 = (ulong *)len;
    a = (BIGNUM *)0x0;
  }
  if (0 < len) {
    bVar1 = *s;
    while (bVar1 == 0) {
      s = s + 1;
      len = len + -1;
      if (len == 0) goto LAB_0020e2f8;
      bVar1 = *s;
    }
  }
  if (len == 0) {
LAB_0020e2f8:
    ret->top = 0;
  }
  else {
    uVar8 = len - 1U & 3;
    words = (len - 1U >> 2) + 1;
    if ((words <= ret->dmax) ||
       (pBVar3 = bn_expand2(ret,words), puVar4 = extraout_r1, pBVar3 != (BIGNUM *)0x0)) {
      uVar5 = 0;
      ret->top = words;
      ret->neg = 0;
      pbVar6 = s;
      do {
        bVar9 = uVar8 == 0;
        pbVar7 = pbVar6 + 1;
        if (bVar9) {
          words = words + -1;
          puVar4 = ret->d;
          uVar2 = uVar8;
        }
        else {
          uVar2 = uVar8 - 1;
        }
        uVar5 = (uint)*pbVar6 | uVar5 << 8;
        uVar8 = uVar2;
        if (bVar9) {
          puVar4[words] = uVar5;
          uVar8 = 3;
          uVar5 = uVar2;
        }
        pbVar6 = pbVar7;
      } while (pbVar7 != s + len);
      bn_correct_top(ret);
      return ret;
    }
    BN_free(a);
    ret = (BIGNUM *)0x0;
  }
  return ret;
}

