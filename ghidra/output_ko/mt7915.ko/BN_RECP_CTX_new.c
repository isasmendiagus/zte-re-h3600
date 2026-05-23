// module: mt7915.ko
// function: BN_RECP_CTX_new @ 0x20f21c
// size: 100 bytes
//

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

BN_RECP_CTX * BN_RECP_CTX_new(void)

{
  ulong *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  BN_RECP_CTX *local_14;
  
  os_alloc_mem(0,&local_14,0x34);
  iVar5 = DAT_005f4ad8;
  iVar4 = DAT_005f4ad4;
  iVar3 = DAT_005f4ad0;
  iVar2 = DAT_005f4acc;
  if (local_14 != (BN_RECP_CTX *)0x0) {
    (local_14->N).d = DAT_005f4ac8;
    (local_14->N).top = iVar2;
    (local_14->N).dmax = iVar3;
    (local_14->N).neg = iVar4;
    iVar4 = DAT_005f4ad4;
    iVar3 = DAT_005f4ad0;
    iVar2 = DAT_005f4acc;
    puVar1 = DAT_005f4ac8;
    (local_14->N).flags = iVar5;
    (local_14->Nr).d = puVar1;
    (local_14->Nr).top = iVar2;
    (local_14->Nr).dmax = iVar3;
    (local_14->Nr).neg = iVar4;
    (local_14->Nr).flags = iVar5;
    local_14->flags = 1;
  }
  return local_14;
}

