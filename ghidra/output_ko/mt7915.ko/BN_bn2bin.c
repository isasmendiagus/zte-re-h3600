// module: mt7915.ko
// function: BN_bn2bin @ 0x20d8c8
// size: 8 bytes
//

/* WARNING: Removing unreachable block (ram,0x0020d1d0) */
/* WARNING: Removing unreachable block (ram,0x0020d258) */
/* WARNING: Removing unreachable block (ram,0x0020d1d8) */
/* WARNING: Removing unreachable block (ram,0x0020d1dc) */
/* WARNING: Removing unreachable block (ram,0x0020d248) */
/* WARNING: Removing unreachable block (ram,0x0020d1e4) */

int BN_bn2bin(BIGNUM *a,uchar *to)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar1 = BN_num_bits(a);
  iVar2 = iVar1 + 7;
  if (iVar2 < 0) {
    iVar2 = iVar1 + 0xe;
  }
  iVar2 = iVar2 >> 3;
  iVar1 = iVar2 + -1;
  if (iVar2 != 0) {
    do {
      iVar4 = iVar1 + 3;
      if (-1 < iVar1) {
        iVar4 = iVar1;
      }
      iVar3 = iVar1 + -1;
      *to = (uchar)(a->d[iVar4 >> 2] >> ((iVar1 % 4) * 8 & 0xffU));
      iVar1 = iVar3;
      to = to + 1;
    } while (iVar3 != -1);
  }
  return iVar2;
}

