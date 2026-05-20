// module: mt7915.ko
// function: BN_MONT_CTX_set @ 0x214894
// size: 552 bytes
//

int BN_MONT_CTX_set(BN_MONT_CTX *mont,BIGNUM *mod,BN_CTX *ctx)

{
  BIGNUM *r;
  BIGNUM *pBVar1;
  int iVar2;
  uint uVar3;
  ulong *puVar4;
  BIGNUM *a;
  undefined1 auStack_48 [4];
  ulong local_44;
  undefined4 local_40;
  BIGNUM local_3c;
  
  if ((mod != (BIGNUM *)0x0) && (mod->top == 0)) {
    return 0;
  }
  BN_CTX_start(ctx);
  r = BN_CTX_get(ctx);
  if (r != (BIGNUM *)0x0) {
    a = &mont->RR;
    pBVar1 = BN_copy(&mont->N,mod);
    if (pBVar1 != (BIGNUM *)0x0) {
      local_3c.d = &local_44;
      (mont->N).neg = 0;
      local_3c.top = DAT_005f4acc;
      local_3c.flags = DAT_005f4ad8;
      local_3c.neg = 0;
      local_3c.dmax = 2;
      if ((mod != (BIGNUM *)0x0) && ((mod->flags & 4U) != 0)) {
        local_3c.flags = DAT_005f4ad8 | 4;
      }
      iVar2 = BN_num_bits(mod);
      uVar3 = iVar2 + 0x1f;
      if ((int)uVar3 < 0) {
        uVar3 = iVar2 + 0x3e;
      }
      mont->ri = uVar3 & 0xffffffe0;
      if (a != (BIGNUM *)0x0) {
        (mont->RR).top = 0;
        (mont->RR).neg = 0;
      }
      iVar2 = BN_set_bit(a,0x20);
      if (iVar2 != 0) {
        local_44 = *mod->d;
        local_40 = 0;
        local_3c.top = (int)(local_44 != 0);
        iVar2 = int_bn_mod_inverse(r,a,&local_3c,ctx,auStack_48);
        if ((iVar2 != 0) && (iVar2 = BN_lshift(r,r,0x20), iVar2 != 0)) {
          if (r->top == 0) {
            iVar2 = BN_set_word(r,0xffffffff);
          }
          else {
            iVar2 = BN_sub_word(r,1);
          }
          if ((iVar2 != 0) && (iVar2 = BN_div(r,(BIGNUM *)0x0,r,&local_3c,ctx), iVar2 != 0)) {
            iVar2 = mont->ri;
            if (r->top < 1) {
              puVar4 = (ulong *)0x0;
            }
            else {
              puVar4 = r->d;
            }
            if (0 < r->top) {
              puVar4 = (ulong *)*puVar4;
            }
            mont->n0[0] = (ulong)puVar4;
            if (a != (BIGNUM *)0x0) {
              (mont->RR).top = 0;
              (mont->RR).neg = 0;
            }
            mont->n0[1] = 0;
            iVar2 = BN_set_bit(a,iVar2 << 1);
            if (iVar2 != 0) {
              iVar2 = BN_div((BIGNUM *)0x0,a,a,&mont->N,ctx);
              uVar3 = (uint)(iVar2 != 0);
              goto LAB_0021498c;
            }
          }
        }
      }
    }
  }
  uVar3 = 0;
LAB_0021498c:
  BN_CTX_end(ctx);
  return uVar3;
}

