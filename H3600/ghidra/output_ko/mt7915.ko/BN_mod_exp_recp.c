// module: mt7915.ko
// function: BN_mod_exp_recp @ 0x213e50
// size: 1096 bytes
//

int BN_mod_exp_recp(BIGNUM *r,BIGNUM *a,BIGNUM *p,BIGNUM *m,BN_CTX *ctx)

{
  bool bVar1;
  int iVar2;
  BIGNUM *a_00;
  BIGNUM *pBVar3;
  BIGNUM *pBVar4;
  int iVar5;
  uint uVar6;
  BIGNUM **ppBVar7;
  BIGNUM **ppBVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  int local_ec;
  BN_RECP_CTX BStack_dc;
  BIGNUM *local_a8 [33];
  
  if ((((p != (BIGNUM *)0x0) && ((p->flags & 4U) != 0)) ||
      ((a != (BIGNUM *)0x0 && ((a->flags & 4U) != 0)))) ||
     ((m != (BIGNUM *)0x0 && ((m->flags & 4U) != 0)))) {
    return 0;
  }
  local_ec = BN_num_bits(p);
  if (local_ec == 0) {
    iVar2 = BN_is_one(m);
    if (iVar2 != 0) {
      if (r != (BIGNUM *)0x0) {
        r->top = 0;
        r->neg = 0;
      }
      return 1;
    }
    iVar2 = BN_set_word(r,1);
    return iVar2;
  }
  BN_CTX_start(ctx);
  a_00 = BN_CTX_get(ctx);
  pBVar3 = BN_CTX_get(ctx);
  local_a8[0] = pBVar3;
  if (pBVar3 != (BIGNUM *)0x0 && a_00 != (BIGNUM *)0x0) {
    BN_RECP_CTX_init(&BStack_dc);
    if (m->neg == 0) {
      iVar2 = BN_RECP_CTX_set(&BStack_dc,m,ctx);
    }
    else {
      pBVar4 = BN_copy(a_00,m);
      if (pBVar4 == (BIGNUM *)0x0) goto LAB_00213b98;
      a_00->neg = (uint)(pBVar3 == (BIGNUM *)0x0 || a_00 == (BIGNUM *)0x0);
      iVar2 = BN_RECP_CTX_set(&BStack_dc,a_00,ctx);
    }
    if ((0 < iVar2) && (iVar2 = BN_nnmod(pBVar3,a,m,ctx), iVar2 != 0)) {
      if (pBVar3->top == 0) {
        if (r != (BIGNUM *)0x0) {
          r->top = 0;
          r->neg = 0;
          iVar2 = 1;
          goto LAB_00213b9c;
        }
      }
      else {
        if (local_ec < 0x2a0) {
          if (0xef < local_ec) {
            uVar12 = 5;
            goto LAB_00213bfc;
          }
          if (0x4f < local_ec) {
            uVar12 = 4;
            goto LAB_00213bfc;
          }
          if (0x17 < local_ec) {
            uVar12 = 3;
            goto LAB_00213bfc;
          }
          uVar12 = 1;
        }
        else {
          uVar12 = 6;
LAB_00213bfc:
          iVar2 = BN_mod_mul_reciprocal(a_00,pBVar3,pBVar3,&BStack_dc,ctx);
          if (iVar2 == 0) goto LAB_00213b98;
          ppBVar7 = local_a8;
          do {
            pBVar3 = BN_CTX_get(ctx);
            ppBVar8 = ppBVar7 + 1;
            *ppBVar8 = pBVar3;
            if ((pBVar3 == (BIGNUM *)0x0) ||
               (iVar2 = BN_mod_mul_reciprocal(pBVar3,*ppBVar7,a_00,&BStack_dc,ctx), iVar2 == 0))
            goto LAB_00213b98;
            ppBVar7 = ppBVar8;
          } while (ppBVar8 != local_a8 + (1 << (uVar12 - 1 & 0xff)) + 0x3fffffff);
        }
        iVar2 = BN_set_word(r,1);
        if (iVar2 == 0) goto LAB_00213b98;
        local_ec = local_ec + -1;
        bVar1 = true;
LAB_00213ca4:
        while ((p != (BIGNUM *)0x0 && -1 < local_ec &&
               (iVar2 = FUN_0020cf74(p,local_ec), iVar2 != 0))) {
          if ((uVar12 == 1) || (iVar2 = local_ec + -1, local_ec == 0)) {
            if (!bVar1) {
              uVar9 = 1;
              uVar6 = 0;
              uVar10 = uVar9;
              goto LAB_00213d38;
            }
            uVar6 = 0;
            uVar9 = 1;
          }
          else {
            uVar9 = 1;
            uVar6 = 0;
            uVar10 = uVar9;
            do {
              iVar5 = FUN_0020cf74(p,iVar2);
              iVar2 = iVar2 + -1;
              if (iVar5 != 0) {
                uVar9 = uVar9 << (uVar10 - uVar6 & 0xff) | 1;
                uVar6 = uVar10;
              }
              uVar10 = uVar10 + 1;
            } while ((uVar10 != uVar12) && (iVar2 != -1));
            if ((!bVar1) && (uVar10 = uVar6 + 1, 0 < (int)uVar10)) {
LAB_00213d38:
              uVar11 = 0;
              do {
                uVar11 = uVar11 + 1;
                iVar2 = BN_mod_mul_reciprocal(r,r,r,&BStack_dc,ctx);
                if (iVar2 == 0) goto LAB_00213b98;
              } while (uVar11 != uVar10);
            }
          }
          iVar2 = BN_mod_mul_reciprocal(r,r,local_a8[(int)uVar9 >> 1],&BStack_dc,ctx);
          if (iVar2 == 0) goto LAB_00213b98;
          local_ec = local_ec + ~uVar6;
          if (local_ec < 0) goto LAB_00213b5c;
          bVar1 = false;
        }
        if ((!bVar1) && (iVar2 = BN_mod_mul_reciprocal(r,r,r,&BStack_dc,ctx), iVar2 == 0))
        goto LAB_00213b98;
        if (local_ec != 0) {
          local_ec = local_ec + -1;
          goto LAB_00213ca4;
        }
      }
LAB_00213b5c:
      iVar2 = 1;
      goto LAB_00213b9c;
    }
  }
LAB_00213b98:
  iVar2 = 0;
LAB_00213b9c:
  BN_CTX_end(ctx);
  BN_RECP_CTX_free(&BStack_dc);
  return iVar2;
}

