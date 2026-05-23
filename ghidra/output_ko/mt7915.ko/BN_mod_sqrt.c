// module: mt7915.ko
// function: BN_mod_sqrt @ 0x2167ec
// size: 1928 bytes
//

BIGNUM * BN_mod_sqrt(BIGNUM *ret,BIGNUM *a,BIGNUM *n,BN_CTX *ctx)

{
  ulong uVar1;
  BIGNUM *pBVar2;
  BIGNUM *pBVar3;
  BIGNUM *r;
  BIGNUM *r_00;
  BIGNUM *r_01;
  int iVar4;
  BIGNUM *pBVar5;
  BIGNUM *pBVar6;
  int iVar7;
  uint uVar8;
  BIGNUM *r_02;
  int iVar9;
  code *pcVar10;
  code *local_30;
  
  if ((n == (BIGNUM *)0x0) || (iVar9 = n->top, iVar9 < 1)) {
    return (BIGNUM *)0x0;
  }
  uVar8 = *n->d;
  if ((uVar8 & 1) == 0) {
    if (iVar9 != 1) {
      return (BIGNUM *)0x0;
    }
LAB_00216950:
    if (*n->d != 2) {
      return (BIGNUM *)0x0;
    }
    pBVar6 = ret;
    if ((ret != (BIGNUM *)0x0) || (pBVar6 = BN_new(), pBVar6 != (BIGNUM *)0x0)) {
      if (a == (BIGNUM *)0x0) {
        uVar1 = 0;
      }
      else {
        uVar1 = FUN_0020cf74(a,0);
      }
      iVar9 = BN_set_word(pBVar6,uVar1);
      if (iVar9 == 0) {
        if (pBVar6 == ret) {
          return (BIGNUM *)0x0;
        }
        BN_free(pBVar6);
        return (BIGNUM *)0x0;
      }
      return pBVar6;
    }
LAB_00216b40:
    r_02 = (BIGNUM *)0x0;
LAB_00216920:
    if (r_02 != ret) {
      BN_clear_free(r_02);
      r_02 = (BIGNUM *)0x0;
      goto LAB_00216934;
    }
  }
  else {
    if ((iVar9 == 1) && (uVar8 == 1)) goto LAB_00216950;
    if (((a != (BIGNUM *)0x0) && (a->top == 0)) || (iVar9 = BN_is_one(a), iVar9 != 0)) {
      if (ret != (BIGNUM *)0x0) {
        uVar1 = BN_is_one(a);
        iVar9 = BN_set_word(ret,uVar1);
        if (iVar9 == 0) {
          ret = (BIGNUM *)0x0;
        }
        return ret;
      }
      pBVar6 = BN_new();
      if (pBVar6 != (BIGNUM *)0x0) {
        uVar1 = BN_is_one(a);
        iVar9 = BN_set_word(pBVar6,uVar1);
        if (iVar9 == 0) {
          BN_free(pBVar6);
          return (BIGNUM *)0x0;
        }
        return pBVar6;
      }
      goto LAB_00216b40;
    }
    BN_CTX_start(ctx);
    pBVar6 = BN_CTX_get(ctx);
    pBVar2 = BN_CTX_get(ctx);
    pBVar3 = BN_CTX_get(ctx);
    r = BN_CTX_get(ctx);
    r_00 = BN_CTX_get(ctx);
    r_01 = BN_CTX_get(ctx);
    if (r_01 != (BIGNUM *)0x0) {
      r_02 = ret;
      if ((ret == (BIGNUM *)0x0) && (r_02 = BN_new(), r_02 == (BIGNUM *)0x0)) goto LAB_00216b40;
      iVar9 = BN_nnmod(pBVar6,a,n,ctx);
      if (iVar9 != 0) {
        iVar9 = 1;
        while ((iVar9 < 0 || (iVar4 = FUN_0020cf74(n,iVar9), iVar4 == 0))) {
          iVar9 = iVar9 + 1;
        }
        if (iVar9 == 1) {
          iVar9 = BN_rshift(pBVar3,n,2);
          if (iVar9 != 0) {
            if (pBVar3 != (BIGNUM *)0x0) {
              pBVar3->neg = 0;
            }
            iVar9 = BN_add_word(pBVar3,1);
            if (iVar9 != 0) {
              pBVar2 = (BIGNUM *)BN_mod_exp(r_02,pBVar6,pBVar3,n,ctx);
joined_r0x00216cf4:
              if (((pBVar2 != (BIGNUM *)0x0) && (iVar9 = BN_mod_sqr(r_00,r_02,n,ctx), iVar9 != 0))
                 && (iVar9 = BN_cmp(r_00,pBVar6), iVar9 == 0)) goto LAB_00216934;
            }
          }
        }
        else if (iVar9 == 2) {
          iVar9 = BN_mod_lshift1_quick(r,pBVar6,n);
          if ((iVar9 != 0) && (iVar9 = BN_rshift(pBVar3,n,3), iVar9 != 0)) {
            pBVar3->neg = 0;
            iVar9 = BN_mod_exp(pBVar2,r,pBVar3,n,ctx);
            if (((iVar9 != 0) &&
                (((iVar9 = BN_mod_sqr(r_01,pBVar2,n,ctx), iVar9 != 0 &&
                  (iVar9 = BN_mod_mul(r,r,r_01,n,ctx), iVar9 != 0)) &&
                 (iVar9 = BN_sub_word(r,1), iVar9 != 0)))) &&
               ((iVar9 = BN_mod_mul(r_00,pBVar6,pBVar2,n,ctx), iVar9 != 0 &&
                (iVar9 = BN_mod_mul(r_00,r_00,r,n,ctx), iVar9 != 0)))) {
LAB_00216c48:
              pBVar2 = BN_copy(r_02,r_00);
              goto joined_r0x00216cf4;
            }
          }
        }
        else {
          pBVar5 = BN_copy(pBVar3,n);
          if (pBVar5 != (BIGNUM *)0x0) {
            local_30 = BN_add;
            uVar1 = 2;
            pBVar3->neg = 0;
            do {
              if ((int)uVar1 < 0x16) {
LAB_00216a3c:
                iVar4 = BN_set_word(r_01,uVar1);
                if (iVar4 == 0) break;
              }
              else {
                iVar4 = BN_num_bits(n);
                iVar4 = FUN_0020e330(1,r_01,iVar4,0,0);
                if (iVar4 == 0) break;
                iVar4 = FUN_0020cef8(r_01,n);
                if (-1 < iVar4) {
                  pcVar10 = local_30;
                  if (n->neg == 0) {
                    pcVar10 = BN_sub;
                  }
                  iVar4 = (*pcVar10)(r_01,r_01,n);
                  if (iVar4 == 0) break;
                }
                if (r_01->top == 0) goto LAB_00216a3c;
              }
              uVar1 = uVar1 + 1;
              iVar4 = BN_kronecker(r_01,pBVar3,ctx);
              if (iVar4 == 0 || iVar4 < -1) break;
              if (iVar4 != 1) {
                if (((iVar4 != -1) || (iVar4 = BN_rshift(pBVar3,pBVar3,iVar9), iVar4 == 0)) ||
                   ((iVar4 = BN_mod_exp(r_01,r_01,pBVar3,n,ctx), iVar4 == 0 ||
                    ((iVar4 = BN_is_one(r_01), iVar4 != 0 ||
                     (iVar4 = BN_rshift1(r,pBVar3), iVar4 == 0)))))) break;
                if ((r == (BIGNUM *)0x0) || (r->top != 0)) {
                  iVar4 = BN_mod_exp(r_00,pBVar6,r,n,ctx);
                  if (iVar4 == 0) break;
                  if ((r_00 == (BIGNUM *)0x0) || (r_00->top != 0)) goto LAB_00216d10;
                }
                else {
                  iVar4 = BN_nnmod(r,pBVar6,n,ctx);
                  if (iVar4 == 0) break;
                  if (r->top != 0) {
                    iVar4 = BN_set_word(r_00,1);
                    if (iVar4 != 0) {
LAB_00216d10:
                      iVar4 = BN_mod_sqr(pBVar2,r_00,n,ctx);
                      if (((iVar4 != 0) &&
                          (iVar4 = BN_mod_mul(pBVar2,pBVar2,pBVar6,n,ctx), iVar4 != 0)) &&
                         (iVar4 = BN_mod_mul(r_00,r_00,pBVar6,n,ctx), iVar4 != 0))
                      goto LAB_00216d74;
                    }
                    break;
                  }
                }
                r_02->top = 0;
                r_02->neg = 0;
                goto LAB_00216934;
              }
            } while (uVar1 != 0x52);
          }
        }
      }
      goto LAB_00216920;
    }
  }
  r_02 = (BIGNUM *)0x0;
LAB_00216934:
  BN_CTX_end(ctx);
  return r_02;
LAB_00216d74:
  iVar4 = BN_is_one(pBVar2);
  if (iVar4 != 0) goto LAB_00216c48;
  iVar4 = BN_mod_sqr(r,pBVar2,n,ctx);
  if (iVar4 == 0) goto LAB_00216920;
  iVar4 = 1;
  while (iVar7 = BN_is_one(r), iVar7 == 0) {
    iVar4 = iVar4 + 1;
    if ((iVar4 == iVar9) || (iVar7 = BN_mod_mul(r,r,r,n,ctx), iVar7 == 0)) goto LAB_00216920;
  }
  pBVar3 = BN_copy(r,r_01);
  if (pBVar3 == (BIGNUM *)0x0) goto LAB_00216920;
  iVar9 = iVar9 - iVar4;
  while (iVar9 = iVar9 + -1, 0 < iVar9) {
    iVar7 = BN_mod_sqr(r,r,n,ctx);
    if (iVar7 == 0) goto LAB_00216920;
  }
  iVar9 = BN_mod_mul(r_01,r,r,n,ctx);
  if (((iVar9 == 0) || (iVar9 = BN_mod_mul(r_00,r_00,r,n,ctx), iVar9 == 0)) ||
     (iVar7 = BN_mod_mul(pBVar2,pBVar2,r_01,n,ctx), iVar9 = iVar4, iVar7 == 0)) goto LAB_00216920;
  goto LAB_00216d74;
}

