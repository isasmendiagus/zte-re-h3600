// module: mt7915.ko
// function: BN_RECP_CTX_init @ 0x20f1d4
// size: 72 bytes
//

void BN_RECP_CTX_init(BN_RECP_CTX *recp)

{
  ulong *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  __memzero(recp,0x34);
  iVar4 = DAT_005f4ad4;
  iVar3 = DAT_005f4ad0;
  iVar2 = DAT_005f4acc;
  (recp->N).d = DAT_005f4ac8;
  (recp->N).top = iVar2;
  (recp->N).dmax = iVar3;
  (recp->N).neg = iVar4;
  iVar5 = DAT_005f4ad8;
  iVar4 = DAT_005f4ad4;
  iVar3 = DAT_005f4ad0;
  iVar2 = DAT_005f4acc;
  puVar1 = DAT_005f4ac8;
  (recp->N).flags = DAT_005f4ad8;
  (recp->Nr).d = puVar1;
  (recp->Nr).top = iVar2;
  (recp->Nr).dmax = iVar3;
  (recp->Nr).neg = iVar4;
  (recp->Nr).flags = iVar5;
  return;
}

