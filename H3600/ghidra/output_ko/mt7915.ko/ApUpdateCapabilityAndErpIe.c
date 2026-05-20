// module: mt7915.ko
// function: ApUpdateCapabilityAndErpIe @ 0x10634
// size: 1024 bytes
//

void ApUpdateCapabilityAndErpIe(int param_1,int param_2)

{
  bool bVar1;
  byte bVar2;
  byte bVar3;
  bool bVar4;
  char cVar5;
  uint uVar6;
  undefined *puVar7;
  int iVar8;
  undefined *puVar9;
  ushort uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  char cVar14;
  bool bVar15;
  
  bVar2 = *(byte *)(param_2 + 0x1a);
  cVar14 = *(char *)(param_1 + 0x795070);
  if (*(ushort *)(param_2 + 0x18) == 2) {
    return;
  }
  uVar13 = 0;
  bVar1 = 0xe < bVar2;
  bVar15 = (*(ushort *)(param_2 + 0x18) & 0xb1) == 0;
  uVar12 = 0;
  bVar4 = !bVar1;
  while( true ) {
    uVar6 = HcGetMaxStaNum(param_1);
    uVar11 = uVar13 & 0xffff;
    uVar13 = uVar13 + 1;
    iVar8 = uVar11 * 0x14c0 + param_1;
    if (uVar6 <= uVar11) break;
    if (((*(int *)(iVar8 + 0xa1d20) == 0x20001) && (*(int *)(iVar8 + 0xa1e1c) == 2)) &&
       (*(int *)(iVar8 + 0xa1d28) == param_2)) {
      if ((bVar15 || bVar4) && (*(byte *)(iVar8 + 0xa289d) < 4)) {
        uVar12 = 1;
        cVar14 = '\0';
      }
      if ((*(ushort *)(uVar11 * 0x14c0 + param_1 + 0xa2816) & 0x400) == 0) {
        cVar14 = '\0';
      }
    }
  }
  if (bVar15 || bVar4) {
    if (*(int *)(param_1 + 0x79506c) == 0) {
      if (uVar12 != 0) {
        uVar12 = 3;
      }
      if (*(uint *)(param_1 + 0x7960e8) < *(int *)(&DAT_0036b8a4 + param_1) + 500U) {
        uVar13 = 1;
        uVar12 = uVar12 | 2;
        if (3 < DebugLevel) goto LAB_00010990;
      }
      else {
        uVar13 = -((int)(uVar12 << 0x1e) >> 0x1f);
        if (3 < DebugLevel) {
          if (uVar13 == 0) {
            puVar7 = &_LC17;
            goto LAB_0001099c;
          }
LAB_00010990:
          uVar13 = 1;
          puVar7 = &_LC16;
          goto LAB_0001099c;
        }
      }
      goto LAB_000108a0;
    }
    if (*(int *)(param_1 + 0x79506c) == 1) {
      uVar12 = uVar12 | 2;
      if (3 < DebugLevel) {
        puVar7 = &_LC16;
        uVar13 = 1;
        goto LAB_0001099c;
      }
      uVar6 = *(uint *)(param_1 + 0x795124);
      if ((int)(uVar6 << 0x1d) < 0) goto LAB_00010780;
      goto LAB_000108b8;
    }
    if (3 < DebugLevel) goto LAB_00010a18;
    uVar6 = *(uint *)(param_1 + 0x795124);
    if ((uVar6 & 4) == 0) goto LAB_00010780;
LAB_00010968:
    *(uint *)(param_1 + 0x795124) = uVar6 & 0xfffffffb;
  }
  else {
    if (DebugLevel < 4) goto LAB_00010780;
LAB_00010a18:
    uVar13 = 0;
    puVar7 = &_LC17;
LAB_0001099c:
    puVar9 = &_LC16;
    if ((*(uint *)(param_1 + 0x795124) & 4) == 0) {
      puVar9 = &_LC17;
    }
    printk("-- bUseBGProtection: %s, BG_PROTECT_INUSED: %s, ERP IE Content: 0x%x\n",puVar7,puVar9,
           uVar12);
    if (bVar15 || bVar4) {
LAB_000108a0:
      uVar6 = *(uint *)(param_1 + 0x795124);
      if (uVar13 != (uVar6 << 0x1d) >> 0x1f) {
        if (uVar13 == 0) goto LAB_00010968;
LAB_000108b8:
        *(uint *)(param_1 + 0x795124) = uVar6 | 4;
        iVar8 = *(int *)(param_1 + 0x795064);
        goto joined_r0x00010788;
      }
    }
  }
LAB_00010780:
  iVar8 = *(int *)(param_1 + 0x795064);
joined_r0x00010788:
  if (iVar8 != 0) {
    uVar13 = 0;
    do {
      uVar6 = HcGetMaxStaNum(param_1);
      uVar11 = uVar13 & 0xffff;
      uVar13 = uVar13 + 1;
      iVar8 = uVar11 * 0x14c0 + param_1;
      if (uVar6 <= uVar11) goto LAB_00010794;
    } while (((*(int *)(iVar8 + 0xa1d20) != 0x20001) || (*(int *)(iVar8 + 0xa1e1c) != 2)) ||
            ((*(ushort *)(iVar8 + 0xa2816) & 0x20) != 0));
  }
  uVar12 = uVar12 | 4;
LAB_00010794:
  if (bVar15 || bVar4) {
    bVar3 = (&DAT_0036b8a1)[param_1];
    (&DAT_0036b8a1)[param_1] = (char)uVar12;
    bVar4 = false;
    if (bVar3 != uVar12) {
      bVar4 = true;
    }
  }
  else {
    bVar4 = false;
  }
  cVar5 = cVar14;
  if (bVar1) {
    cVar5 = '\x01';
  }
  if (bVar1 || cVar14 == '\0') {
    uVar10 = *(ushort *)(param_2 + 0x408c) & 0xfbff;
  }
  else {
    uVar10 = *(ushort *)(param_2 + 0x408c) | 0x400;
  }
  *(ushort *)(param_2 + 0x408c) = uVar10;
  if (*(int *)(param_1 + 0x795064) == 0) {
    uVar10 = uVar10 & 0xffdf;
  }
  else {
    uVar10 = uVar10 | 0x20;
  }
  *(ushort *)(param_2 + 0x408c) = uVar10;
  if (*(char *)(param_1 + 0x795070) != cVar5) {
    HW_SET_SLOTTIME(param_1,cVar5,bVar2,0);
    *(char *)(param_1 + 0x795070) = cVar5;
  }
  if (!bVar4) {
    return;
  }
  UpdateBeaconHandler(param_1,param_2,2);
  return;
}

