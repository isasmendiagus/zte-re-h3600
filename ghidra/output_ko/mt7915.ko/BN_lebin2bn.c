// module: mt7915.ko
// function: BN_lebin2bn @ 0x20e5bc
// size: 272 bytes
//

BIGNUM * BN_lebin2bn(int param_1,ulong *param_2,BIGNUM *param_3)

{
  uint uVar1;
  BIGNUM *pBVar2;
  ulong *extraout_r1;
  ulong *puVar3;
  ulong *extraout_r1_00;
  uint uVar4;
  byte *pbVar5;
  uint uVar6;
  byte *pbVar7;
  int words;
  BIGNUM *a;
  bool bVar8;
  
  if (param_3 == (BIGNUM *)0x0) {
    param_3 = BN_new();
    puVar3 = extraout_r1_00;
    a = param_3;
    if (param_3 == (BIGNUM *)0x0) {
      return (BIGNUM *)0x0;
    }
  }
  else {
    puVar3 = param_2;
    a = (BIGNUM *)0x0;
  }
  pbVar5 = (byte *)(param_1 + (int)param_2);
  if (((int)param_2 < 1) || (pbVar5[-1] != 0)) {
    if (param_2 == (ulong *)0x0) {
LAB_0020e694:
      param_3->top = 0;
      return param_3;
    }
  }
  else {
    pbVar7 = pbVar5 + -1;
    do {
      pbVar5 = pbVar7;
      param_2 = (ulong *)((int)param_2 + -1);
      if (param_2 == (ulong *)0x0) goto LAB_0020e694;
      pbVar7 = pbVar5 + -1;
    } while (pbVar5[-1] == 0);
  }
  uVar6 = (int)param_2 - 1U & 3;
  words = ((int)param_2 - 1U >> 2) + 1;
  if ((param_3->dmax < words) &&
     (pBVar2 = bn_expand2(param_3,words), puVar3 = extraout_r1, pBVar2 == (BIGNUM *)0x0)) {
    BN_free(a);
    return (BIGNUM *)0x0;
  }
  pbVar7 = pbVar5 + -(int)param_2;
  uVar4 = 0;
  param_3->top = words;
  param_3->neg = 0;
  do {
    bVar8 = uVar6 == 0;
    pbVar5 = pbVar5 + -1;
    if (bVar8) {
      words = words + -1;
      puVar3 = param_3->d;
      uVar1 = uVar6;
    }
    else {
      uVar1 = uVar6 - 1;
    }
    uVar4 = (uint)*pbVar5 | uVar4 << 8;
    uVar6 = uVar1;
    if (bVar8) {
      puVar3[words] = uVar4;
      uVar6 = 3;
      uVar4 = uVar1;
    }
  } while (pbVar5 != pbVar7);
  bn_correct_top(param_3);
  return param_3;
}

