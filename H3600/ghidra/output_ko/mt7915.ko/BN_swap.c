// module: mt7915.ko
// function: BN_swap @ 0x20d78c
// size: 112 bytes
//

void BN_swap(BIGNUM *a,BIGNUM *b)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  ulong *puVar5;
  int iVar6;
  
  uVar1 = b->flags;
  puVar5 = a->d;
  a->d = b->d;
  iVar4 = a->top;
  uVar2 = a->flags;
  a->top = b->top;
  iVar3 = a->dmax;
  iVar6 = a->neg;
  a->dmax = b->dmax;
  a->neg = b->neg;
  b->d = puVar5;
  b->top = iVar4;
  b->dmax = iVar3;
  b->neg = iVar6;
  a->flags = uVar1 & 2 | uVar2 & 1;
  b->flags = uVar2 & 2 | uVar1 & 1;
  return;
}

