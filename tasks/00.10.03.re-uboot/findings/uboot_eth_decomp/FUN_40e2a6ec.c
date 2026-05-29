/* ===== FUN FUN_40e2a6ec @ 40e2a6ec =====
 * callers: 40e27cc4:FUN_40e27cc4, 40e28f54:FUN_40e28f54, 40e2a914:FUN_40e2a914, 40e2afc0:FUN_40e2afc0, 40e2b480:FUN_40e2b480, 40e2b65c:FUN_40e2b65c, 40e38d84:FUN_40e38d84, 40e39034:FUN_40e39034
 * callees: 40e2a5a4:FUN_40e2a5a4
 */


uint FUN_40e2a6ec(uint param_1)

{
  int iVar1;
  bool bVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  
  iVar7 = DAT_40e2a90c/*=0x47f40390*/;
  if (param_1 == 0) {
    return 0;
  }
  iVar6 = param_1 - 8;
  uVar5 = *(uint *)(param_1 - 4) & 0xfffffffe;
  uVar3 = *(uint *)(param_1 - 4) & 1;
  iVar8 = iVar6 + uVar5;
  uVar10 = *(uint *)(iVar8 + 4) & 0xfffffffc;
  if (iVar8 == *(int *)(DAT_40e2a90c/*=0x47f40390*/ + 8)) {
    uVar10 = uVar10 + uVar5;
    if (uVar3 == 0) {
      iVar6 = iVar6 - *(int *)(param_1 - 8);
      uVar10 = uVar10 + *(int *)(param_1 - 8);
      param_1 = *(uint *)(iVar6 + 8);
      iVar8 = *(int *)(iVar6 + 0xc);
      *(int *)(param_1 + 0xc) = iVar8;
      *(uint *)(iVar8 + 8) = param_1;
    }
    *(uint *)(iVar6 + 4) = uVar10 | 1;
    *(int *)(iVar7 + 8) = iVar6;
    iVar6 = DAT_40e2a6e4/*=0x47f40390*/;
    if (uVar10 < *(uint *)(iVar7 + 0x40c)) {
      return param_1;
    }
    uVar3 = *(uint *)(*(int *)(DAT_40e2a6e4/*=0x47f40390*/ + 8) + 4) & 0xfffffffc;
    iVar7 = ((uVar3 - *(int *)(DAT_40e2a910/*=0x47f52890*/ + 0x34)) + 0xfef & 0xfffff000) - 0x1000;
    if ((0xfff < iVar7) && (iVar8 = FUN_40e2a5a4(0), iVar8 == *(int *)(iVar6 + 8) + uVar3)) {
      iVar1 = FUN_40e2a5a4(-iVar7);
      iVar8 = DAT_40e2a6e8/*=0x47f52890*/;
      if (iVar1 != -1) {
        *(uint *)(*(int *)(iVar6 + 8) + 4) = uVar3 - iVar7 | 1;
        *(int *)(iVar8 + 0xc) = *(int *)(iVar8 + 0xc) - iVar7;
        return 1;
      }
      iVar7 = FUN_40e2a5a4(0);
      uVar3 = iVar7 - *(int *)(iVar6 + 8);
      if (0xf < (int)uVar3) {
        *(uint *)(*(int *)(iVar6 + 8) + 4) = uVar3 | 1;
        *(int *)(DAT_40e2a6e8/*=0x47f52890*/ + 0xc) = iVar7 - *(int *)(iVar6 + 0x408);
      }
    }
    return 0;
  }
  *(uint *)(iVar8 + 4) = uVar10;
  if (uVar3 == 0) {
    iVar6 = iVar6 - *(int *)(param_1 - 8);
    uVar5 = uVar5 + *(int *)(param_1 - 8);
    iVar1 = *(int *)(iVar6 + 8);
    if (iVar1 == iVar7 + 8) {
      bVar2 = true;
    }
    else {
      iVar9 = *(int *)(iVar6 + 0xc);
      *(int *)(iVar1 + 0xc) = iVar9;
      *(int *)(iVar9 + 8) = iVar1;
      bVar2 = false;
    }
  }
  else {
    bVar2 = false;
  }
  iVar1 = DAT_40e2a90c/*=0x47f40390*/;
  if ((*(uint *)(iVar8 + uVar10 + 4) & 1) == 0) {
    uVar5 = uVar5 + uVar10;
    iVar9 = *(int *)(iVar8 + 8);
    if ((bVar2) || (iVar9 != DAT_40e2a90c/*=0x47f40390*/ + 8)) {
      iVar8 = *(int *)(iVar8 + 0xc);
      *(int *)(iVar9 + 0xc) = iVar8;
      *(int *)(iVar8 + 8) = iVar9;
    }
    else {
      *(int *)(DAT_40e2a90c/*=0x47f40390*/ + 0x14) = iVar6;
      bVar2 = true;
      *(int *)(iVar1 + 0x10) = iVar6;
      *(int *)(iVar6 + 0xc) = iVar9;
      *(int *)(iVar6 + 8) = iVar9;
    }
  }
  *(uint *)(iVar6 + 4) = uVar5 | 1;
  *(uint *)(iVar6 + uVar5) = uVar5;
  if (bVar2) {
    return uVar5 | 1;
  }
  if (uVar5 < 0x200) {
    uVar3 = *(uint *)(iVar7 + 4);
    *(uint *)(iVar7 + 4) = uVar3 | 1 << ((int)(uVar5 >> 3) >> 2 & 0xffU);
    iVar7 = iVar7 + (uVar5 >> 3) * 8;
    iVar8 = *(int *)(iVar7 + 8);
    *(int *)(iVar6 + 0xc) = iVar7;
    *(int *)(iVar6 + 8) = iVar8;
    *(int *)(iVar7 + 8) = iVar6;
    *(int *)(iVar8 + 0xc) = iVar6;
    return uVar3;
  }
  uVar3 = uVar5 >> 9;
  if (uVar3 < 5) {
    iVar8 = (uVar5 >> 6) + 0x38;
  }
  else if (uVar3 < 0x15) {
    iVar8 = uVar3 + 0x5b;
  }
  else if (uVar3 < 0x55) {
    iVar8 = (uVar5 >> 0xc) + 0x6e;
  }
  else if (uVar3 < 0x155) {
    iVar8 = (uVar5 >> 0xf) + 0x77;
  }
  else if (uVar3 < 0x555) {
    iVar8 = (uVar5 >> 0x12) + 0x7c;
  }
  else {
    iVar8 = 0x7e;
  }
  uVar10 = iVar7 + iVar8 * 8;
  uVar3 = *(uint *)(uVar10 + 8);
  if (uVar3 == uVar10) {
    *(uint *)(DAT_40e2a90c/*=0x47f40390*/ + 4) = *(uint *)(DAT_40e2a90c/*=0x47f40390*/ + 4) | 1 << (iVar8 >> 2 & 0xffU);
    uVar4 = uVar3;
  }
  else {
    do {
      uVar4 = uVar3;
      if ((*(uint *)(uVar3 + 4) & 0xfffffffc) <= uVar5) break;
      uVar3 = *(uint *)(uVar3 + 8);
      uVar4 = uVar3;
    } while (uVar3 != uVar10);
    uVar3 = *(uint *)(uVar4 + 0xc);
  }
  *(uint *)(iVar6 + 0xc) = uVar3;
  *(uint *)(iVar6 + 8) = uVar4;
  *(int *)(uVar3 + 8) = iVar6;
  *(int *)(uVar4 + 0xc) = iVar6;
  return uVar3;
}
