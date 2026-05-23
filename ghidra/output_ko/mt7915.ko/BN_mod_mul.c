// module: mt7915.ko
// function: BN_mod_mul @ 0x215d10
// size: 172 bytes
//

int BN_mod_mul(BIGNUM *r,BIGNUM *a,BIGNUM *b,BIGNUM *m,BN_CTX *ctx)

{
  BIGNUM *m_00;
  int iVar1;
  uint uVar2;
  
  BN_CTX_start(ctx);
  m_00 = BN_CTX_get(ctx);
  if (m_00 != (BIGNUM *)0x0) {
    if (a == b) {
      if (a != (BIGNUM *)0x0) {
        iVar1 = FUN_0020f4cc(m_00,a,ctx);
        goto joined_r0x00215db4;
      }
    }
    else if (b != (BIGNUM *)0x0 && a != (BIGNUM *)0x0) {
      iVar1 = FUN_00212078(m_00,a,b,ctx);
joined_r0x00215db4:
      if (iVar1 != 0) {
        iVar1 = BN_nnmod(r,m_00,m,ctx);
        uVar2 = (uint)(iVar1 != 0);
        goto LAB_00215d54;
      }
    }
  }
  uVar2 = 0;
LAB_00215d54:
  BN_CTX_end(ctx);
  return uVar2;
}

