// module: mt7915.ko
// function: BN_CTX_start @ 0x20f01c
// size: 84 bytes
//

void BN_CTX_start(BN_CTX *ctx)

{
  int iVar1;
  
  if (ctx == (BN_CTX *)0x0) {
    return;
  }
  if ((*(int *)(ctx + 0x24) == 0) && (*(int *)(ctx + 0x28) == 0)) {
    iVar1 = BN_STACK_push(ctx + 0x14,*(undefined4 *)(ctx + 0x20));
    if (iVar1 == 0) {
      *(int *)(ctx + 0x24) = *(int *)(ctx + 0x24) + 1;
    }
    return;
  }
  *(int *)(ctx + 0x24) = *(int *)(ctx + 0x24) + 1;
  return;
}

