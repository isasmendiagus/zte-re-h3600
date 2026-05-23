// module: mt7915.ko
// function: BN_bn2hex @ 0x216f74
// size: 232 bytes
//

char * BN_bn2hex(BIGNUM *a)

{
  uint uVar1;
  char cVar2;
  char *pcVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  bool bVar8;
  char *local_1c;
  
  if ((a == (BIGNUM *)0x0) || (a->top != 0)) {
    os_alloc_mem(0,&local_1c,a->top * 8 + 2);
    if (local_1c != (char *)0x0) {
      bVar8 = a->neg != 0;
      if (bVar8) {
        *local_1c = '-';
      }
      pcVar3 = local_1c;
      if (bVar8) {
        pcVar3 = local_1c + 1;
      }
      iVar7 = a->top + -1;
      if (-1 < iVar7) {
        iVar6 = iVar7 * 4;
        bVar8 = false;
        do {
          uVar4 = 0x18;
          do {
            uVar1 = *(uint *)((int)a->d + iVar6) >> (uVar4 & 0xff);
            uVar4 = uVar4 - 8;
            uVar5 = uVar1 & 0xff;
            if (bVar8 || uVar5 != 0) {
              cVar2 = "0123456789ABCDEF"[uVar1 & 0xf];
              *pcVar3 = "0123456789ABCDEF"[uVar5 >> 4];
              pcVar3[1] = cVar2;
              pcVar3 = pcVar3 + 2;
            }
            bVar8 = bVar8 || uVar5 != 0;
          } while (uVar4 != 0xfffffff8);
          iVar7 = iVar7 + -1;
          iVar6 = iVar6 + -4;
        } while (iVar7 != -1);
      }
      *pcVar3 = '\0';
    }
  }
  else {
    local_1c = (char *)0x0;
  }
  return local_1c;
}

