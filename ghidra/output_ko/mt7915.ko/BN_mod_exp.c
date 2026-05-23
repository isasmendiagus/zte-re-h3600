// module: mt7915.ko
// function: BN_mod_exp @ 0x215c58
// size: 184 bytes
//

int BN_mod_exp(BIGNUM *r,BIGNUM *a,BIGNUM *p,BIGNUM *m,BN_CTX *ctx)

{
  int iVar1;
  
  if (((m != (BIGNUM *)0x0) && (0 < m->top)) && ((*m->d & 1) != 0)) {
    if (((((a == (BIGNUM *)0x0) || (a->top != 1)) ||
         ((a->neg != 0 || ((p != (BIGNUM *)0x0 && ((p->flags & 4U) != 0)))))) ||
        ((a->flags & 4U) != 0)) || ((m->flags & 4U) != 0)) {
      iVar1 = BN_mod_exp_mont(r,a,p,m,ctx,(BN_MONT_CTX *)0x0);
    }
    else {
      iVar1 = BN_mod_exp_mont_word(r,*a->d,p,m,ctx,(BN_MONT_CTX *)0x0);
    }
    return iVar1;
  }
  iVar1 = BN_mod_exp_recp(r,a,p,m,ctx);
  return iVar1;
}

