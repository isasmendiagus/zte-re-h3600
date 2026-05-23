// module: mt7915.ko
// function: BN_mod_exp_simple @ 0x215dbc
// size: 988 bytes
//

int BN_mod_exp_simple(BIGNUM *r,BIGNUM *a,BIGNUM *p,BIGNUM *m,BN_CTX *ctx)

{
  bool bVar1;
  int iVar2;
  BIGNUM *r_00;
  BIGNUM *pBVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  BIGNUM **ppBVar9;
  BIGNUM **ppBVar10;
  uint local_bc;
  int local_b8;
  BIGNUM *local_a8 [33];
  
  if ((((p != (BIGNUM *)0x0) && ((p->flags & 4U) != 0)) ||
      ((a != (BIGNUM *)0x0 && ((a->flags & 4U) != 0)))) ||
     ((m != (BIGNUM *)0x0 && ((m->flags & 4U) != 0)))) {
    return 0;
  }
  local_b8 = BN_num_bits(p);
  if (local_b8 == 0) {
    iVar2 = BN_is_one(m);
    if (iVar2 == 0) {
      iVar2 = BN_set_word(r,1);
      return iVar2;
    }
    if (r == (BIGNUM *)0x0) {
      return 1;
    }
    r->top = 0;
    r->neg = 0;
    return 1;
  }
  BN_CTX_start(ctx);
  r_00 = BN_CTX_get(ctx);
  pBVar3 = BN_CTX_get(ctx);
  local_a8[0] = pBVar3;
  if ((pBVar3 == (BIGNUM *)0x0 || r_00 == (BIGNUM *)0x0) ||
     (iVar2 = BN_nnmod(pBVar3,a,m,ctx), iVar2 == 0)) {
LAB_00215fe4:
    iVar2 = 0;
  }
  else {
    if (pBVar3->top == 0) {
      if (r != (BIGNUM *)0x0) {
        r->top = 0;
        r->neg = 0;
        iVar2 = 1;
        goto LAB_00215ec4;
      }
    }
    else {
      if (local_b8 < 0x2a0) {
        if (0xef < local_b8) {
          local_bc = 5;
          goto LAB_00216038;
        }
        if (0x4f < local_b8) {
          local_bc = 4;
          goto LAB_00216038;
        }
        if (0x17 < local_b8) {
          local_bc = 3;
          goto LAB_00216038;
        }
        local_bc = 1;
      }
      else {
        local_bc = 6;
LAB_00216038:
        iVar2 = BN_mod_mul(r_00,pBVar3,pBVar3,m,ctx);
        if (iVar2 == 0) goto LAB_00215fe4;
        ppBVar9 = local_a8;
        do {
          pBVar3 = BN_CTX_get(ctx);
          ppBVar10 = ppBVar9 + 1;
          *ppBVar10 = pBVar3;
          if ((pBVar3 == (BIGNUM *)0x0) ||
             (iVar2 = BN_mod_mul(pBVar3,*ppBVar9,r_00,m,ctx), iVar2 == 0)) goto LAB_00215fe4;
          ppBVar9 = ppBVar10;
        } while (ppBVar10 != local_a8 + (1 << (local_bc - 1 & 0xff)) + 0x3fffffff);
      }
      iVar2 = BN_set_word(r,1);
      if (iVar2 == 0) goto LAB_00215fe4;
      local_b8 = local_b8 + -1;
      bVar1 = true;
LAB_00215f04:
      while ((p != (BIGNUM *)0x0 && -1 < local_b8 && (iVar2 = FUN_0020cf74(p,local_b8), iVar2 != 0))
            ) {
        if ((local_bc == 1) || (iVar2 = local_b8 + -1, local_b8 == 0)) {
          uVar7 = 1;
          uVar5 = uVar7;
          if (!bVar1) {
            uVar6 = 0;
            goto LAB_00215fb0;
          }
          uVar6 = 0;
        }
        else {
          uVar5 = 1;
          uVar7 = 1;
          uVar6 = 0;
          do {
            iVar4 = FUN_0020cf74(p,iVar2);
            iVar2 = iVar2 + -1;
            if (iVar4 != 0) {
              uVar5 = uVar5 << (uVar7 - uVar6 & 0xff) | 1;
              uVar6 = uVar7;
            }
            uVar7 = uVar7 + 1;
          } while ((uVar7 != local_bc) && (iVar2 != -1));
          if ((!bVar1) && (uVar7 = uVar6 + 1, 0 < (int)uVar7)) {
LAB_00215fb0:
            uVar8 = 0;
            do {
              uVar8 = uVar8 + 1;
              iVar2 = BN_mod_mul(r,r,r,m,ctx);
              if (iVar2 == 0) goto LAB_00215fe4;
            } while (uVar8 != uVar7);
          }
        }
        iVar2 = BN_mod_mul(r,r,local_a8[(int)uVar5 >> 1],m,ctx);
        if (iVar2 == 0) goto LAB_00215fe4;
        local_b8 = local_b8 + ~uVar6;
        if (local_b8 < 0) goto LAB_002160c0;
        bVar1 = false;
      }
      if ((!bVar1) && (iVar2 = BN_mod_mul(r,r,r,m,ctx), iVar2 == 0)) goto LAB_00215fe4;
      if (local_b8 != 0) {
        local_b8 = local_b8 + -1;
        goto LAB_00215f04;
      }
    }
LAB_002160c0:
    iVar2 = 1;
  }
LAB_00215ec4:
  BN_CTX_end(ctx);
  return iVar2;
}

