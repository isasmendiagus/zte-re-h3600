// module: mt7915.ko
// function: BN_sub_word @ 0x2113d0
// size: 280 bytes
//

int BN_sub_word(BIGNUM *a,ulong w)

{
  int iVar1;
  ulong *puVar2;
  ulong uVar3;
  uint uVar4;
  int iVar5;
  
  if (a == (BIGNUM *)0x0 || w == 0) {
    return 1;
  }
  if (a->top == 0) {
    iVar5 = BN_set_word(a,w);
    if (iVar5 == 0) {
      return 0;
    }
    if (a->top == 0) {
      a->neg = 0;
      return iVar5;
    }
    a->neg = 1;
    return iVar5;
  }
  if (a->neg != 0) {
    a->neg = 0;
    iVar5 = BN_add_word(a,w);
    a->neg = 1;
    return iVar5;
  }
  puVar2 = a->d;
  uVar3 = *puVar2;
  if (a->top == 1) {
    if (uVar3 < w) {
      *puVar2 = w - uVar3;
      a->neg = 1;
      return 1;
    }
  }
  else {
    iVar5 = 0;
    uVar4 = uVar3;
    if (uVar3 < w) {
      do {
        *puVar2 = uVar4 - w;
        iVar5 = iVar5 + 1;
        w = 1;
        iVar1 = iVar5 * 4;
        uVar3 = a->d[iVar5];
        puVar2 = a->d + iVar5;
        uVar4 = 0;
      } while (uVar3 == 0);
      goto LAB_00211448;
    }
  }
  iVar1 = 0;
  iVar5 = 0;
LAB_00211448:
  *puVar2 = uVar3 - w;
  if ((*(int *)((int)a->d + iVar1) == 0) && (iVar5 == a->top + -1)) {
    a->top = iVar5;
    return 1;
  }
  return 1;
}

