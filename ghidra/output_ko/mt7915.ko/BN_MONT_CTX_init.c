// module: mt7915.ko
// function: BN_MONT_CTX_init @ 0x20eb2c
// size: 108 bytes
//

void BN_MONT_CTX_init(BN_MONT_CTX *ctx)

{
  ulong *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  ctx->ri = 0;
  iVar4 = DAT_005f4ad4;
  iVar3 = DAT_005f4ad0;
  iVar2 = DAT_005f4acc;
  (ctx->RR).d = DAT_005f4ac8;
  (ctx->RR).top = iVar2;
  (ctx->RR).dmax = iVar3;
  (ctx->RR).neg = iVar4;
  iVar5 = DAT_005f4ad8;
  iVar4 = DAT_005f4ad4;
  iVar3 = DAT_005f4ad0;
  iVar2 = DAT_005f4acc;
  puVar1 = DAT_005f4ac8;
  (ctx->RR).flags = DAT_005f4ad8;
  (ctx->N).d = puVar1;
  (ctx->N).top = iVar2;
  (ctx->N).dmax = iVar3;
  (ctx->N).neg = iVar4;
  iVar4 = DAT_005f4ad4;
  iVar3 = DAT_005f4ad0;
  iVar2 = DAT_005f4acc;
  puVar1 = DAT_005f4ac8;
  (ctx->N).flags = iVar5;
  (ctx->Ni).d = puVar1;
  (ctx->Ni).top = iVar2;
  (ctx->Ni).dmax = iVar3;
  (ctx->Ni).neg = iVar4;
  (ctx->Ni).flags = iVar5;
  ctx->n0[1] = 0;
  ctx->n0[0] = 0;
  ctx->flags = 0;
  return;
}

