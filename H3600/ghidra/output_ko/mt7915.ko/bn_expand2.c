// module: mt7915.ko
// function: bn_expand2 @ 0x20d3b4
// size: 372 bytes
//

BIGNUM * bn_expand2(BIGNUM *a,int words)

{
  int iVar1;
  ulong *puVar2;
  ulong *puVar3;
  ulong *puVar4;
  ulong uVar5;
  uint uVar6;
  ulong uVar7;
  ulong uVar8;
  int iVar9;
  ulong *puVar10;
  ulong *local_24 [2];
  
  if (words <= a->dmax) {
    return a;
  }
  if ((0xffffff < words) || ((a != (BIGNUM *)0x0 && ((a->flags & 2U) != 0)))) {
    return (BIGNUM *)0x0;
  }
  iVar1 = words * 4;
  os_alloc_mem(0,local_24,iVar1);
  puVar3 = local_24[0];
  if (local_24[0] == (ulong *)0x0) {
    return (BIGNUM *)0x0;
  }
  if (iVar1 != 0) {
    __memzero(local_24[0],iVar1);
  }
  puVar4 = a->d;
  if (puVar4 == (ulong *)0x0) goto LAB_0020d4b8;
  uVar6 = a->top;
  iVar1 = (int)uVar6 >> 2;
  iVar9 = iVar1;
  puVar2 = puVar4;
  if (0 < iVar1) {
    do {
      iVar9 = iVar9 + -1;
      uVar8 = puVar2[1];
      uVar7 = puVar2[3];
      uVar5 = puVar2[2];
      *local_24[0] = *puVar2;
      puVar10 = local_24[0] + 4;
      local_24[0][1] = uVar8;
      local_24[0][2] = uVar5;
      local_24[0][3] = uVar7;
      puVar2 = puVar2 + 4;
      local_24[0] = puVar10;
    } while (iVar9 != 0);
    uVar6 = a->top;
    puVar4 = puVar4 + iVar1 * 4;
  }
  uVar6 = uVar6 & 3;
  if (uVar6 == 2) {
LAB_0020d4fc:
    local_24[0][1] = puVar4[1];
LAB_0020d504:
    *local_24[0] = *puVar4;
  }
  else {
    if (uVar6 == 3) {
      local_24[0][2] = puVar4[2];
      goto LAB_0020d4fc;
    }
    if (uVar6 == 1) goto LAB_0020d504;
  }
  if ((a->d != (ulong *)0x0) &&
     (((a->dmax & 0x3fffffffU) == 0 || (__memzero(), a->d != (ulong *)0x0)))) {
    os_free_mem();
  }
LAB_0020d4b8:
  a->d = puVar3;
  a->dmax = words;
  return a;
}

