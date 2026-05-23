// module: mt7915.ko
// function: BN_mod_exp_mont_word @ 0x2157ac
// size: 1196 bytes
//

int BN_mod_exp_mont_word(BIGNUM *r,ulong a,BIGNUM *p,BIGNUM *m,BN_CTX *ctx,BN_MONT_CTX *m_ctx)

{
  int iVar1;
  BIGNUM *pBVar2;
  BIGNUM *a_00;
  BIGNUM *rem;
  ulong uVar3;
  int iVar4;
  ulong extraout_r1;
  ulong w;
  ulong w_00;
  uint uVar5;
  bool bVar6;
  bool bVar7;
  BN_MONT_CTX *local_44;
  
  if ((p != (BIGNUM *)0x0) && ((p->flags & 4U) != 0)) {
    return 0;
  }
  if (m == (BIGNUM *)0x0) {
    return 0;
  }
  if ((m->flags & 4U) != 0) {
    return 0;
  }
  if (m->top < 1) {
    return 0;
  }
  if ((*m->d & 1) == 0) {
    return 0;
  }
  if (m->top == 1) {
    __aeabi_uidivmod(a);
    a = extraout_r1;
  }
  iVar1 = BN_num_bits(p);
  if (iVar1 == 0) {
    iVar1 = BN_is_one(m);
    if (iVar1 == 0) {
      iVar1 = BN_set_word(r,1);
      return iVar1;
    }
LAB_00215840:
    if (r != (BIGNUM *)0x0) {
      r->top = 0;
      r->neg = 0;
      return 1;
    }
    return 1;
  }
  if (a == 0) goto LAB_00215840;
  BN_CTX_start(ctx);
  pBVar2 = BN_CTX_get(ctx);
  a_00 = BN_CTX_get(ctx);
  rem = BN_CTX_get(ctx);
  if (rem == (BIGNUM *)0x0 || (pBVar2 == (BIGNUM *)0x0 || a_00 == (BIGNUM *)0x0)) {
    uVar5 = 0;
    local_44 = (BN_MONT_CTX *)0x0;
    goto LAB_00215a68;
  }
  if (m_ctx == (BN_MONT_CTX *)0x0) {
    local_44 = BN_MONT_CTX_new();
    if ((local_44 != (BN_MONT_CTX *)0x0) && (iVar4 = BN_MONT_CTX_set(local_44,m,ctx), iVar4 != 0))
    goto LAB_002158d4;
    uVar5 = 0;
  }
  else {
    local_44 = m_ctx;
LAB_002158d4:
    iVar1 = iVar1 + -2;
    if (iVar1 < 0) {
      if (a == 1) {
LAB_00215bcc:
        iVar1 = BN_set_word(r,1);
        uVar5 = (uint)(iVar1 != 0);
      }
      else {
LAB_00215b4c:
        rem = a_00;
        iVar1 = BN_set_word(rem,a);
        if ((iVar1 != 0) &&
           (iVar1 = BN_mod_mul_montgomery(rem,rem,&local_44->RR,local_44,ctx), iVar1 != 0))
        goto LAB_00215c0c;
        uVar5 = 0;
      }
    }
    else {
      bVar6 = true;
      w = a;
      do {
        w_00 = w * w;
        uVar3 = __aeabi_uidiv(w_00,w);
        if (w != uVar3) {
          if (bVar6) {
            iVar4 = BN_set_word(a_00,w);
            if ((iVar4 != 0) &&
               (iVar4 = BN_mod_mul_montgomery(a_00,a_00,&local_44->RR,local_44,ctx), pBVar2 = a_00,
               iVar4 != 0)) goto LAB_00215950;
LAB_00215b08:
            uVar5 = 0;
          }
          else {
            iVar4 = BN_mul_word(a_00,w);
            uVar5 = 0;
            if (iVar4 == 0) {
LAB_00215b68:
              uVar5 = 0;
            }
            else {
              iVar4 = BN_div((BIGNUM *)0x0,rem,a_00,m,ctx);
              pBVar2 = rem;
              rem = a_00;
              if (iVar4 != 0) {
LAB_00215950:
                a_00 = pBVar2;
                w_00 = 1;
                goto LAB_00215954;
              }
            }
          }
          goto LAB_00215a68;
        }
        if (bVar6) {
          bVar6 = true;
          pBVar2 = rem;
        }
        else {
LAB_00215954:
          iVar4 = BN_mod_mul_montgomery(a_00,a_00,a_00,local_44,ctx);
          if (iVar4 == 0) goto LAB_00215b08;
          bVar6 = false;
          pBVar2 = rem;
        }
        w = w_00;
        rem = pBVar2;
        if ((p != (BIGNUM *)0x0) && (iVar4 = FUN_0020cf74(p,iVar1), iVar4 != 0)) {
          w = a * w_00;
          uVar3 = __aeabi_uidiv(w);
          if (w_00 != uVar3) {
            if (bVar6) {
              iVar4 = BN_set_word(a_00,w_00);
              if ((iVar4 == 0) ||
                 (iVar4 = BN_mod_mul_montgomery(a_00,a_00,&local_44->RR,local_44,ctx), iVar4 == 0))
              goto LAB_00215b08;
              bVar6 = false;
              w = a;
            }
            else {
              iVar4 = BN_mul_word(a_00,w_00);
              if ((iVar4 == 0) ||
                 (iVar4 = BN_div((BIGNUM *)0x0,pBVar2,a_00,m,ctx), w = a, rem = a_00, a_00 = pBVar2,
                 iVar4 == 0)) goto LAB_00215b68;
            }
          }
        }
        bVar7 = iVar1 != 0;
        iVar1 = iVar1 + -1;
      } while (bVar7);
      if (w == 1) {
        rem = a_00;
        if (bVar6) goto LAB_00215bcc;
      }
      else {
        a = w;
        if (bVar6) goto LAB_00215b4c;
        iVar1 = BN_mul_word(a_00,w);
        if ((iVar1 == 0) || (iVar1 = BN_div((BIGNUM *)0x0,rem,a_00,m,ctx), iVar1 == 0)) {
          uVar5 = 0;
          goto LAB_00215a68;
        }
      }
LAB_00215c0c:
      iVar1 = BN_from_montgomery(r,rem,local_44,ctx);
      uVar5 = (uint)(iVar1 != 0);
    }
LAB_00215a68:
    if (m_ctx != (BN_MONT_CTX *)0x0) goto LAB_00215a70;
  }
  BN_MONT_CTX_free(local_44);
LAB_00215a70:
  BN_CTX_end(ctx);
  return uVar5;
}

