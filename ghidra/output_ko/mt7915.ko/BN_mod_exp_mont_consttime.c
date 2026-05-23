// module: mt7915.ko
// function: BN_mod_exp_mont_consttime @ 0x214ac0
// size: 1688 bytes
//

int BN_mod_exp_mont_consttime
              (BIGNUM *rr,BIGNUM *a,BIGNUM *p,BIGNUM *m,BN_CTX *ctx,BN_MONT_CTX *in_mont)

{
  ulong *puVar1;
  int iVar2;
  int iVar3;
  BIGNUM *rem;
  int extraout_r1;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  int local_70;
  BN_MONT_CTX *local_6c;
  int local_68;
  uint local_54;
  BIGNUM local_50;
  BIGNUM local_3c;
  
  if (m == (BIGNUM *)0x0) {
    rr = (BIGNUM *)0x0;
  }
  local_54 = 0;
  if (m == (BIGNUM *)0x0) {
    return (int)rr;
  }
  iVar8 = m->top;
  if (iVar8 < 1) {
    return 0;
  }
  if ((*m->d & 1) == 0) {
    return 0;
  }
  iVar2 = BN_num_bits(p);
  if (iVar2 == 0) {
    iVar8 = BN_is_one(m);
    if (iVar8 == 0) {
      iVar8 = BN_set_word(rr,1);
      return iVar8;
    }
    if (rr != (BIGNUM *)0x0) {
      rr->top = 0;
      rr->neg = 0;
      return 1;
    }
    return 1;
  }
  BN_CTX_start(ctx);
  if (in_mont == (BN_MONT_CTX *)0x0) {
    local_6c = BN_MONT_CTX_new();
    if ((local_6c != (BN_MONT_CTX *)0x0) && (iVar11 = BN_MONT_CTX_set(local_6c,m,ctx), iVar11 != 0))
    goto LAB_00214b68;
    iVar11 = 0;
    local_70 = 0;
    uVar10 = 0;
LAB_00215130:
    BN_MONT_CTX_free(local_6c);
  }
  else {
    local_6c = in_mont;
LAB_00214b68:
    if (iVar2 < 0x3aa) {
      if (iVar2 < 0x133) {
        if (iVar2 < 0x5a) {
          if (iVar2 < 0x17) {
            local_68 = 1;
            uVar10 = 2;
          }
          else {
            local_68 = 3;
            uVar10 = 8;
          }
        }
        else {
          uVar10 = 0x10;
          local_68 = 4;
        }
      }
      else {
        uVar10 = 0x20;
        local_68 = 5;
      }
    }
    else {
      uVar10 = 0x40;
      local_68 = 6;
    }
    uVar9 = iVar8 * 2;
    if (iVar8 * 2 <= (int)uVar10) {
      uVar9 = uVar10;
    }
    local_70 = (uVar10 * iVar8 + uVar9) * 4;
    os_alloc_mem(0,&local_54,local_70 + 0x40);
    if (local_54 == 0) {
      if (in_mont != (BN_MONT_CTX *)0x0) {
        uVar10 = 0;
        goto LAB_00214cb4;
      }
      uVar10 = 0;
      iVar11 = 0;
      goto LAB_00215130;
    }
    iVar11 = (local_54 & 0xffffffc0) + 0x40;
    if (local_70 != 0) {
      __memzero(iVar11,local_70);
    }
    iVar3 = iVar8 * 4 * uVar10;
    local_3c.top = 0;
    local_50.d = (ulong *)(iVar11 + iVar3);
    local_50.top = 0;
    local_3c.d = local_50.d + iVar8;
    local_3c.neg = 0;
    local_50.neg = 0;
    local_3c.flags = 2;
    local_50.flags = 2;
    local_50.dmax = iVar8;
    local_3c.dmax = iVar8;
    if ((int)m->d[iVar8 + -1] < 0) {
      *(ulong *)(iVar11 + iVar3) = -*m->d;
      local_50.top = iVar8;
      if (iVar8 != 1) {
        iVar3 = 1;
        do {
          local_50.d[iVar3] = ~m->d[iVar3];
          iVar3 = iVar3 + 1;
        } while (iVar3 != iVar8);
      }
LAB_00214d04:
      rem = a;
      if ((a != (BIGNUM *)0x0) && ((a->neg != 0 || (iVar3 = FUN_0020cef8(a,m), -1 < iVar3)))) {
        rem = &local_3c;
        iVar3 = BN_div((BIGNUM *)0x0,rem,a,m,ctx);
        if (iVar3 == 0) goto LAB_00214c88;
      }
      iVar3 = BN_mod_mul_montgomery(&local_3c,rem,&local_6c->RR,local_6c,ctx);
      if (iVar3 != 0) {
        iVar3 = local_50.top;
        if (iVar8 <= local_50.top) {
          iVar3 = iVar8;
        }
        if (0 < iVar3) {
          iVar5 = 0;
          iVar6 = iVar5;
          do {
            puVar1 = local_50.d + iVar6;
            iVar6 = iVar6 + 1;
            *(ulong *)(iVar11 + iVar5 * 4) = *puVar1;
            iVar5 = iVar5 + uVar10;
          } while (iVar6 != iVar3);
        }
        iVar3 = local_3c.top;
        if (iVar8 <= local_3c.top) {
          iVar3 = iVar8;
        }
        if (0 < iVar3) {
          iVar5 = 0;
          iVar6 = iVar11;
          do {
            puVar1 = local_3c.d + iVar5;
            iVar5 = iVar5 + 1;
            *(ulong *)(iVar6 + 4) = *puVar1;
            iVar6 = iVar6 + uVar10 * 4;
          } while (iVar5 != iVar3);
        }
        if (local_68 == 1) {
          iVar3 = 0;
LAB_00214eec:
          iVar6 = iVar2 + -1;
          iVar3 = iVar3 - iVar6;
          iVar2 = 0;
          do {
            iVar5 = 0;
            if (p != (BIGNUM *)0x0 && -1 < iVar6) {
              iVar5 = FUN_0020cf74(p,iVar6);
            }
            iVar6 = iVar6 + -1;
            iVar2 = iVar2 * 2 + iVar5;
          } while (-1 < iVar3 + iVar6);
        }
        else {
          iVar3 = BN_mod_mul_montgomery(&local_50,&local_3c,&local_3c,local_6c,ctx);
          if (iVar3 == 0) goto LAB_00214c88;
          iVar3 = local_50.top;
          if (iVar8 <= local_50.top) {
            iVar3 = iVar8;
          }
          if (0 < iVar3) {
            iVar5 = 0;
            iVar6 = iVar11;
            do {
              puVar1 = local_50.d + iVar5;
              iVar5 = iVar5 + 1;
              *(ulong *)(iVar6 + 8) = *puVar1;
              iVar6 = iVar6 + uVar10 * 4;
            } while (iVar5 != iVar3);
          }
          if (3 < uVar10) {
            uVar9 = 3;
            do {
              iVar3 = BN_mod_mul_montgomery(&local_50,&local_3c,&local_50,local_6c,ctx);
              if (iVar3 == 0) goto LAB_00214c88;
              iVar3 = local_50.top;
              if (iVar8 <= local_50.top) {
                iVar3 = iVar8;
              }
              if (0 < iVar3) {
                iVar6 = 0;
                uVar4 = uVar9;
                do {
                  puVar1 = local_50.d + iVar6;
                  iVar6 = iVar6 + 1;
                  *(ulong *)(iVar11 + uVar4 * 4) = *puVar1;
                  uVar4 = uVar4 + uVar10;
                } while (iVar6 != iVar3);
              }
              uVar9 = uVar9 + 1;
            } while (uVar9 != uVar10);
          }
          iVar6 = iVar2 + -1;
          __aeabi_idivmod(iVar6,local_68);
          iVar3 = extraout_r1;
          if (-1 < extraout_r1) goto LAB_00214eec;
          iVar2 = 0;
        }
        iVar2 = FUN_0020e90c(&local_50,iVar8,iVar11,iVar2,local_68);
        while (iVar2 != 0) {
          if (iVar6 < 0) {
            iVar8 = BN_from_montgomery(rr,&local_50,local_6c,ctx);
            uVar10 = (uint)(iVar8 != 0);
            goto LAB_00214c8c;
          }
          iVar3 = 0;
          iVar2 = iVar6 - local_68;
          do {
            iVar5 = BN_mod_mul_montgomery(&local_50,&local_50,&local_50,local_6c,ctx);
            iVar7 = 0;
            if (iVar5 == 0) goto LAB_00214c88;
            if (p != (BIGNUM *)0x0 && -1 < iVar6) {
              iVar7 = FUN_0020cf74(p,iVar6);
            }
            iVar6 = iVar6 + -1;
            iVar3 = iVar3 * 2 + iVar7;
          } while (iVar6 != iVar2);
          iVar2 = FUN_0020e90c(&local_3c,iVar8,iVar11,iVar3,local_68);
          if (iVar2 == 0) break;
          iVar2 = BN_mod_mul_montgomery(&local_50,&local_50,&local_3c,local_6c,ctx);
        }
      }
    }
    else {
      iVar3 = BN_mod_mul_montgomery(&local_50,(BIGNUM *)&_LANCHOR1,&local_6c->RR,local_6c,ctx);
      if (iVar3 != 0) goto LAB_00214d04;
    }
LAB_00214c88:
    uVar10 = 0;
LAB_00214c8c:
    if (in_mont == (BN_MONT_CTX *)0x0) goto LAB_00215130;
  }
  if (iVar11 != 0) {
    if (local_70 != 0) {
      __memzero(iVar11,local_70);
    }
    os_free_mem(local_54);
  }
LAB_00214cb4:
  BN_CTX_end(ctx);
  return uVar10;
}

