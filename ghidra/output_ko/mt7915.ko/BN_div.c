// module: mt7915.ko
// function: BN_div @ 0x211688
// size: 1624 bytes
//

int BN_div(BIGNUM *dv,BIGNUM *rem,BIGNUM *m,BIGNUM *d,BN_CTX *ctx)

{
  BIGNUM *pBVar1;
  BIGNUM *r;
  BIGNUM *r_00;
  int iVar2;
  ulong *puVar3;
  int iVar4;
  uint uVar5;
  BIGNUM *pBVar6;
  int words;
  uint uVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  uint uVar12;
  ulong uVar13;
  uint uVar14;
  int iVar15;
  uint uVar16;
  ulong *puVar17;
  uint uVar18;
  bool bVar19;
  uint *local_70;
  int local_68;
  ulong *local_3c;
  int local_38;
  int local_34;
  undefined4 local_30;
  
  if (d == (BIGNUM *)0x0 || m == (BIGNUM *)0x0) {
    return 0;
  }
  if ((0 < m->top) && (m->d[m->top + 0x3fffffff] == 0)) {
    return 0;
  }
  iVar8 = d->top;
  if ((0 < iVar8) && (d->d[iVar8 + 0x3fffffff] == 0)) {
    return 0;
  }
  if (((m->flags & 4U) == 0) && ((d->flags & 4U) == 0)) {
    if (iVar8 == 0) {
      return 0;
    }
    iVar8 = FUN_0020cef8(m,d);
    if (iVar8 < 0) {
      if ((rem != (BIGNUM *)0x0) && (pBVar1 = BN_copy(rem,m), pBVar1 == (BIGNUM *)0x0)) {
        return 0;
      }
      if (dv != (BIGNUM *)0x0) {
        dv->top = 0;
        dv->neg = 0;
      }
      return 1;
    }
    local_68 = 0;
  }
  else {
    if (iVar8 == 0) {
      return 0;
    }
    local_68 = 1;
  }
  BN_CTX_start(ctx);
  pBVar1 = BN_CTX_get(ctx);
  r = BN_CTX_get(ctx);
  r_00 = BN_CTX_get(ctx);
  if (dv == (BIGNUM *)0x0) {
    dv = BN_CTX_get(ctx);
  }
  if ((dv != (BIGNUM *)0x0 && r_00 != (BIGNUM *)0x0) &&
     (r != (BIGNUM *)0x0 && pBVar1 != (BIGNUM *)0x0)) {
    iVar8 = BN_num_bits(d);
    iVar2 = BN_lshift(r_00,d,0x20 - iVar8 % 0x20);
    if (iVar2 != 0) {
      iVar2 = 0x40 - iVar8 % 0x20;
      r_00->neg = 0;
      iVar8 = BN_lshift(r,m,iVar2);
      if (iVar8 != 0) {
        r->neg = 0;
        if (local_68 == 0) {
          iVar15 = r->top;
        }
        else {
          iVar15 = r_00->top;
          iVar8 = r->top;
          if (iVar15 + 1 < iVar8) {
            if (r->dmax < iVar8 + 1) {
              pBVar6 = bn_expand2(r,iVar8 + 1);
              if (pBVar6 == (BIGNUM *)0x0) goto LAB_0021176c;
              iVar8 = r->top;
            }
            r->d[iVar8] = 0;
            iVar15 = r->top + 1;
            r->top = iVar15;
          }
          else {
            if (r->dmax < iVar15 + 2) {
              pBVar6 = bn_expand2(r,iVar15 + 2);
              if (pBVar6 == (BIGNUM *)0x0) goto LAB_0021176c;
              iVar8 = r->top;
              iVar15 = r_00->top;
            }
            iVar15 = iVar15 + 2;
            if (iVar8 < iVar15) {
              iVar11 = iVar8 << 2;
              do {
                iVar8 = iVar8 + 1;
                *(undefined4 *)((int)r->d + iVar11) = 0;
                iVar11 = iVar11 + 4;
                iVar15 = r_00->top + 2;
              } while (iVar8 < iVar15);
            }
            r->top = iVar15;
          }
        }
        iVar11 = r_00->top;
        uVar16 = 0;
        iVar8 = iVar15 - iVar11;
        local_30 = 0;
        puVar3 = r->d;
        local_34 = r->dmax - iVar8;
        puVar17 = puVar3 + iVar8;
        uVar18 = r_00->d[iVar11 + 0x3fffffff];
        if (iVar11 != 1) {
          uVar16 = r_00->d[iVar11 + 0x3ffffffe];
        }
        local_3c = puVar17;
        local_38 = iVar11;
        if ((iVar8 + 1 <= dv->dmax) || (pBVar6 = bn_expand2(dv,iVar8 + 1), pBVar6 != (BIGNUM *)0x0))
        {
          uVar9 = d->neg;
          uVar12 = m->neg;
          dv->top = iVar8 - local_68;
          words = iVar11 + 1;
          dv->neg = uVar12 ^ uVar9;
          local_70 = dv->d + iVar8 + -1;
          if ((words <= pBVar1->dmax) ||
             (pBVar6 = bn_expand2(pBVar1,words), pBVar6 != (BIGNUM *)0x0)) {
            if (local_68 == 0) {
              iVar4 = FUN_0020cef8(&local_3c,r_00);
              if (iVar4 < 0) {
                iVar4 = dv->top + -1;
                dv->top = iVar4;
              }
              else {
                FUN_0020cd98(puVar17,puVar17,r_00->d,iVar11);
                *local_70 = 1;
                iVar4 = dv->top;
              }
            }
            else {
              iVar4 = dv->top;
            }
            if (iVar4 == 0) {
              dv->neg = 0;
              local_70 = local_70 + 1;
            }
            if (0 < iVar8 + -1) {
              iVar4 = 0;
              puVar3 = puVar3 + iVar15 + 0x3fffffff;
              puVar17 = local_3c;
              do {
                uVar13 = puVar3[-1];
                if (*puVar3 == uVar18) {
                  uVar9 = 0xffffffff;
                }
                else {
                  if (uVar18 == 0) {
                    uVar12 = 0xffff;
                    uVar9 = 0xffffffff;
                    uVar10 = uVar12;
                  }
                  else {
                    uVar9 = FUN_0020d060(*puVar3,uVar13,uVar18);
                    uVar10 = uVar9 & 0xffff;
                    uVar12 = uVar9 >> 0x10;
                  }
                  uVar14 = uVar13 - uVar18 * uVar9;
                  uVar5 = (uVar16 >> 0x10) * uVar10;
                  uVar7 = (uVar16 & 0xffff) * uVar12 + uVar5;
                  iVar15 = (uVar16 >> 0x10) * uVar12;
                  uVar10 = (uVar16 & 0xffff) * uVar10;
                  if (uVar7 <= uVar5 && uVar5 - uVar7 != 0) {
                    iVar15 = iVar15 + 0x10000;
                  }
                  uVar12 = iVar15 + (uVar7 >> 0x10);
                  if (CARRY4(uVar7 * 0x10000,uVar10)) {
                    uVar12 = uVar12 + 1;
                  }
                  uVar10 = uVar7 * 0x10000 + uVar10;
                  if (uVar14 <= uVar12) {
                    do {
                      if ((uVar12 == uVar14) && (uVar10 <= puVar3[-2])) break;
                      bVar19 = CARRY4(uVar14,uVar18);
                      uVar14 = uVar14 + uVar18;
                      uVar9 = uVar9 - 1;
                      if (bVar19) break;
                      if (uVar10 < uVar16) {
                        uVar12 = uVar12 - 1;
                      }
                      uVar10 = uVar10 - uVar16;
                    } while (uVar14 <= uVar12);
                  }
                }
                puVar17 = puVar17 + -1;
                uVar13 = FUN_0020cb1c(pBVar1->d,r_00->d,iVar11,uVar9);
                pBVar1->d[iVar11 + 0x40000000] = uVar13;
                local_3c = puVar17;
                iVar15 = FUN_0020cd98(puVar17,puVar17,pBVar1->d,words);
                if (iVar15 != 0) {
                  uVar9 = uVar9 - 1;
                  iVar15 = FUN_0020cc88(puVar17,puVar17,r_00->d,iVar11);
                  if (iVar15 != 0) {
                    *puVar3 = *puVar3 + 1;
                  }
                }
                iVar4 = iVar4 + 1;
                local_70 = local_70 + -1;
                *local_70 = uVar9;
                puVar3 = puVar3 + -1;
              } while (iVar4 != iVar8 + -1);
            }
            bn_correct_top(r);
            if (rem != (BIGNUM *)0x0) {
              iVar8 = m->neg;
              BN_rshift(rem,r,iVar2);
              if (rem->top != 0) {
                rem->neg = iVar8;
              }
            }
            if (local_68 != 0) {
              bn_correct_top(dv);
            }
            BN_CTX_end(ctx);
            return 1;
          }
        }
      }
    }
  }
LAB_0021176c:
  BN_CTX_end(ctx);
  return 0;
}

