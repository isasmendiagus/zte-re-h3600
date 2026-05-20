// module: mt7915.ko
// function: BN_mod_exp_mont @ 0x215744
// size: 1620 bytes
//

int BN_mod_exp_mont(BIGNUM *r,BIGNUM *a,BIGNUM *p,BIGNUM *m,BN_CTX *ctx,BN_MONT_CTX *m_ctx)

{
  int iVar1;
  BIGNUM *pBVar2;
  BIGNUM *a_00;
  BIGNUM *pBVar3;
  int iVar4;
  ulong *puVar5;
  uint uVar6;
  BIGNUM **ppBVar7;
  BIGNUM **ppBVar8;
  uint uVar9;
  uint uVar10;
  int local_c4;
  BN_MONT_CTX *local_c0;
  uint local_bc;
  uint local_b4;
  uint local_b0;
  BIGNUM *local_a8 [34];
  
  local_c0 = m_ctx;
  if ((((p != (BIGNUM *)0x0) && ((p->flags & 4U) != 0)) ||
      ((a != (BIGNUM *)0x0 && ((a->flags & 4U) != 0)))) ||
     ((m != (BIGNUM *)0x0 && ((m->flags & 4U) != 0)))) {
    iVar1 = BN_mod_exp_mont_consttime(r,a,p,m,ctx,m_ctx);
    return iVar1;
  }
  if (m == (BIGNUM *)0x0) {
    return 0;
  }
  if (m->top < 1) {
    return 0;
  }
  if ((*m->d & 1) == 0) {
    return 0;
  }
  local_c4 = BN_num_bits(p);
  if (local_c4 == 0) {
    iVar1 = BN_is_one(m);
    if (iVar1 == 0) {
      iVar1 = BN_set_word(r,1);
      return iVar1;
    }
    if (r != (BIGNUM *)0x0) {
      r->top = 0;
      r->neg = 0;
      return 1;
    }
    return 1;
  }
  BN_CTX_start(ctx);
  pBVar2 = BN_CTX_get(ctx);
  a_00 = BN_CTX_get(ctx);
  pBVar3 = BN_CTX_get(ctx);
  local_a8[0] = pBVar3;
  if (pBVar3 == (BIGNUM *)0x0 || (pBVar2 == (BIGNUM *)0x0 || a_00 == (BIGNUM *)0x0)) {
    local_c0 = (BN_MONT_CTX *)0x0;
    uVar6 = 0;
LAB_00215290:
    if (m_ctx != (BN_MONT_CTX *)0x0) goto LAB_00215298;
  }
  else {
    if ((m_ctx != (BN_MONT_CTX *)0x0) ||
       ((local_c0 = BN_MONT_CTX_new(), local_c0 != (BN_MONT_CTX *)0x0 &&
        (iVar1 = BN_MONT_CTX_set(local_c0,m,ctx), iVar1 != 0)))) {
      if (((a == (BIGNUM *)0x0) || ((a->neg != 0 || (iVar1 = FUN_0020cef8(a,m), -1 < iVar1)))) &&
         (iVar1 = BN_nnmod(pBVar3,a,m,ctx), a = pBVar3, iVar1 == 0)) {
LAB_002152d0:
        uVar6 = 0;
      }
      else {
        if (a->top == 0) {
          if (r == (BIGNUM *)0x0) {
            uVar6 = 1;
          }
          else {
            uVar6 = 1;
            r->top = 0;
            r->neg = 0;
          }
          goto LAB_00215290;
        }
        iVar1 = BN_mod_mul_montgomery(pBVar3,a,&local_c0->RR,local_c0,ctx);
        if (iVar1 == 0) goto LAB_002152d0;
        if (local_c4 < 0x2a0) {
          if (0xef < local_c4) {
            local_b4 = 5;
            goto LAB_00215374;
          }
          if (0x4f < local_c4) {
            local_b4 = 4;
            goto LAB_00215374;
          }
          if (0x17 < local_c4) {
            local_b4 = 3;
            goto LAB_00215374;
          }
          local_b4 = 1;
        }
        else {
          local_b4 = 6;
LAB_00215374:
          iVar1 = BN_mod_mul_montgomery(pBVar2,pBVar3,pBVar3,local_c0,ctx);
          if (iVar1 == 0) goto LAB_002152d0;
          ppBVar7 = local_a8;
          do {
            pBVar3 = BN_CTX_get(ctx);
            ppBVar8 = ppBVar7 + 1;
            *ppBVar8 = pBVar3;
            if (pBVar3 == (BIGNUM *)0x0) {
              uVar6 = 0;
              goto LAB_00215290;
            }
            iVar1 = BN_mod_mul_montgomery(pBVar3,*ppBVar7,pBVar2,local_c0,ctx);
            if (iVar1 == 0) {
              uVar6 = 0;
              goto LAB_00215290;
            }
            ppBVar7 = ppBVar8;
          } while (ppBVar8 != local_a8 + (1 << (local_b4 - 1 & 0xff)) + 0x3fffffff);
        }
        puVar5 = m->d;
        iVar1 = m->top;
        if ((int)puVar5[iVar1 + 0x3fffffff] < 0) {
          if (a_00->dmax < iVar1) {
            pBVar2 = bn_expand2(a_00,iVar1);
            if (pBVar2 == (BIGNUM *)0x0) goto LAB_002152d0;
            puVar5 = m->d;
          }
          *a_00->d = -*puVar5;
          if (1 < iVar1) {
            iVar4 = 1;
            do {
              a_00->d[iVar4] = ~m->d[iVar4];
              iVar4 = iVar4 + 1;
            } while (iVar4 != iVar1);
          }
          a_00->top = iVar1;
          bn_correct_top(a_00);
        }
        else {
          iVar1 = BN_mod_mul_montgomery(a_00,(BIGNUM *)&_LANCHOR1,&local_c0->RR,local_c0,ctx);
          if (iVar1 == 0) goto LAB_002152d0;
        }
        local_c4 = local_c4 + -1;
        local_bc = 1;
LAB_002154cc:
        while ((p != (BIGNUM *)0x0 && -1 < local_c4 &&
               (iVar1 = FUN_0020cf74(p,local_c4), iVar1 != 0))) {
          if ((local_b4 == 1) || (iVar1 = local_c4 + -1, local_c4 == 0)) {
            if (local_bc == 0) {
              local_b0 = local_bc;
              uVar10 = 1;
              uVar6 = uVar10;
              goto LAB_00215564;
            }
            local_b0 = 0;
            uVar6 = 1;
          }
          else {
            uVar10 = 1;
            local_b0 = 0;
            uVar6 = uVar10;
            do {
              iVar4 = FUN_0020cf74(p,iVar1);
              iVar1 = iVar1 + -1;
              if (iVar4 != 0) {
                uVar6 = uVar6 << (uVar10 - local_b0 & 0xff) | 1;
                local_b0 = uVar10;
              }
              uVar10 = uVar10 + 1;
            } while ((uVar10 != local_b4) && (iVar1 != -1));
            if ((local_bc == 0) && (uVar10 = local_b0 + 1, 0 < (int)uVar10)) {
LAB_00215564:
              uVar9 = 0;
              do {
                uVar9 = uVar9 + 1;
                iVar1 = BN_mod_mul_montgomery(a_00,a_00,a_00,local_c0,ctx);
                if (iVar1 == 0) goto LAB_0021559c;
              } while (uVar9 != uVar10);
            }
          }
          iVar1 = BN_mod_mul_montgomery(a_00,a_00,local_a8[(int)uVar6 >> 1],local_c0,ctx);
          if (iVar1 == 0) {
LAB_0021559c:
            uVar6 = 0;
            goto LAB_00215290;
          }
          local_c4 = local_c4 + ~local_b0;
          if (local_c4 < 0) goto LAB_002155cc;
          local_bc = 0;
        }
        if ((local_bc == 0) &&
           (iVar1 = BN_mod_mul_montgomery(a_00,a_00,a_00,local_c0,ctx), iVar1 == 0)) {
          uVar6 = 0;
          goto LAB_00215290;
        }
        if (local_c4 != 0) {
          local_c4 = local_c4 + -1;
          goto LAB_002154cc;
        }
LAB_002155cc:
        iVar1 = BN_from_montgomery(r,a_00,local_c0,ctx);
        uVar6 = (uint)(iVar1 != 0);
      }
      goto LAB_00215290;
    }
    uVar6 = 0;
  }
  BN_MONT_CTX_free(local_c0);
LAB_00215298:
  BN_CTX_end(ctx);
  return uVar6;
}

