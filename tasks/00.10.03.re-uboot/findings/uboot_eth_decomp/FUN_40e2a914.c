/* ===== FUN FUN_40e2a914 @ 40e2a914 =====
 * callers: 40e28f54:FUN_40e28f54, 40e2aeec:FUN_40e2aeec, 40e2afc0:FUN_40e2afc0, 40e2b480:FUN_40e2b480, 40e2b65c:FUN_40e2b65c, 40e2c7b0:FUN_40e2c7b0, 40e2ff74:FUN_40e2ff74, 40e2ffa4:FUN_40e2ffa4
 * callees: 40e2a5a4:FUN_40e2a5a4, 40e2a6ec:FUN_40e2a6ec
 */


int * FUN_40e2a914(int param_1)

{
  uint uVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  int *piVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  int iVar16;
  uint uVar17;
  bool bVar18;
  
  uVar1 = DAT_40e2aee8/*=0x47f40390*/;
  iVar5 = DAT_40e2aee4/*=0x47f52890*/;
  if (((*(int *)(DAT_40e2aee4/*=0x47f52890*/ + 4) == 0) && (*(int *)(DAT_40e2aee4/*=0x47f52890*/ + 8) == 0)) || (param_1 < 0)) {
LAB_40e2a934:
    piVar2 = (int *)0x0;
  }
  else {
    uVar12 = param_1 + 0xb;
    if ((int)uVar12 < 0x17) {
      uVar13 = 0x10;
LAB_40e2a968:
      iVar7 = DAT_40e2aee8/*=0x47f40390*/ + (uVar13 >> 3) * 8;
      iVar3 = *(int *)(iVar7 + 0xc);
      if ((iVar3 == iVar7) && (iVar7 = iVar3 + 8, iVar3 = *(int *)(iVar3 + 0x14), iVar3 == iVar7)) {
        uVar12 = (uVar13 >> 3) + 2;
        goto LAB_40e2aa6c;
      }
      iVar7 = *(int *)(iVar3 + 0xc);
      iVar5 = *(int *)(iVar3 + 8);
      iVar8 = iVar3 + (*(uint *)(iVar3 + 4) & 0xfffffffc);
      *(int *)(iVar5 + 0xc) = iVar7;
      *(int *)(iVar7 + 8) = iVar5;
LAB_40e2aa34:
      *(uint *)(iVar8 + 4) = *(uint *)(iVar8 + 4) | 1;
    }
    else {
      uVar13 = uVar12 & 0xfffffff8;
      if (uVar13 < 0x1f8) goto LAB_40e2a968;
      uVar9 = uVar12 >> 9;
      if (uVar9 == 0) {
        iVar7 = 0x3f;
      }
      else if (uVar9 < 5) {
        iVar7 = (uVar12 >> 6) + 0x38;
      }
      else if (uVar9 < 0x15) {
        iVar7 = uVar9 + 0x5b;
      }
      else if (uVar9 < 0x55) {
        iVar7 = (uVar12 >> 0xc) + 0x6e;
      }
      else if (uVar9 < 0x155) {
        iVar7 = (uVar12 >> 0xf) + 0x77;
      }
      else if (uVar9 < 0x555) {
        iVar7 = (uVar12 >> 0x12) + 0x7c;
      }
      else {
        iVar7 = 0x7e;
      }
      iVar8 = DAT_40e2aee8/*=0x47f40390*/ + iVar7 * 8;
      for (iVar3 = *(int *)(iVar8 + 0xc); iVar3 != iVar8; iVar3 = *(int *)(iVar3 + 0xc)) {
        uVar12 = *(uint *)(iVar3 + 4) & 0xfffffffc;
        iVar16 = uVar12 - uVar13;
        if (0xf < iVar16) {
          iVar7 = iVar7 + -1;
          break;
        }
        if (-1 < iVar16) {
          iVar7 = *(int *)(iVar3 + 0xc);
          iVar5 = *(int *)(iVar3 + 8);
          *(int *)(iVar5 + 0xc) = iVar7;
          *(int *)(iVar7 + 8) = iVar5;
          iVar8 = iVar3 + uVar12;
          goto LAB_40e2aa34;
        }
      }
      uVar12 = iVar7 + 1;
LAB_40e2aa6c:
      iVar3 = *(int *)(DAT_40e2aee8/*=0x47f40390*/ + 0x10);
      iVar7 = DAT_40e2aee8/*=0x47f40390*/ + 8;
      if (iVar3 == iVar7) {
LAB_40e2abd4:
        uVar9 = 1 << ((int)uVar12 >> 2 & 0xffU);
        uVar14 = *(uint *)(uVar1 + 4);
        if (uVar9 <= uVar14) {
          if ((uVar9 & uVar14) == 0) {
            uVar12 = uVar12 & 0xfffffffc;
            do {
              uVar9 = uVar9 << 1;
              uVar12 = uVar12 + 4;
            } while ((uVar9 & uVar14) == 0);
          }
          do {
            piVar11 = (int *)(uVar1 + uVar12 * 8);
            piVar2 = piVar11;
            uVar14 = uVar12;
            do {
              for (piVar4 = (int *)piVar2[3]; piVar4 != piVar2; piVar4 = (int *)piVar4[3]) {
                uVar17 = piVar4[1] & 0xfffffffc;
                uVar15 = uVar17 - uVar13;
                if (0xf < (int)uVar15) {
                  iVar5 = piVar4[3];
                  iVar3 = (int)piVar4 + uVar13;
                  piVar4[1] = uVar13 | 1;
                  iVar8 = piVar4[2];
                  *(int *)(iVar8 + 0xc) = iVar5;
                  *(int *)(iVar5 + 8) = iVar8;
                  *(int *)(uVar1 + 0x14) = iVar3;
                  *(int *)(uVar1 + 0x10) = iVar3;
                  *(int *)(iVar3 + 0xc) = iVar7;
                  *(int *)(iVar3 + 8) = iVar7;
                  *(uint *)(iVar3 + 4) = uVar15 | 1;
                  *(uint *)(iVar3 + uVar15) = uVar15;
                  return piVar4 + 2;
                }
                if (-1 < (int)uVar15) {
                  *(uint *)((int)piVar4 + uVar17 + 4) = *(uint *)((int)piVar4 + uVar17 + 4) | 1;
                  iVar3 = piVar4[3];
                  iVar5 = piVar4[2];
                  *(int *)(iVar5 + 0xc) = iVar3;
                  *(int *)(iVar3 + 8) = iVar5;
                  return piVar4 + 2;
                }
              }
              uVar14 = uVar14 + 1;
              piVar2 = piVar2 + 2;
            } while ((uVar14 & 3) != 0);
            do {
              if ((uVar12 & 3) == 0) {
                *(uint *)(uVar1 + 4) = *(uint *)(uVar1 + 4) & ~uVar9;
                break;
              }
              piVar2 = piVar11 + -2;
              piVar11 = (int *)*piVar11;
              uVar12 = uVar12 - 1;
            } while (piVar11 == piVar2);
            uVar9 = uVar9 * 2;
            uVar12 = uVar14;
            if (uVar9 == 0 || *(uint *)(uVar1 + 4) < uVar9) break;
            for (; (uVar9 & *(uint *)(uVar1 + 4)) == 0; uVar9 = uVar9 << 1) {
              uVar12 = uVar12 + 4;
            }
          } while( true );
        }
        uVar14 = *(uint *)(uVar1 + 8);
        uVar9 = *(uint *)(uVar14 + 4) & 0xfffffffc;
        uVar12 = uVar9 - uVar13;
        if ((int)uVar12 < 0x10) {
          iVar3 = uVar13 + *(int *)(iVar5 + 0x34);
          if (*(int *)(DAT_40e2aee8/*=0x47f40390*/ + 0x408) == -1) {
            uVar12 = iVar3 + 0x10;
          }
          else {
            uVar12 = iVar3 + 0x100fU & 0xfffff000;
          }
          uVar17 = FUN_40e2a5a4(uVar12);
          uVar15 = DAT_40e2aee8/*=0x47f40390*/;
          if (uVar17 != 0xffffffff) {
            uVar6 = uVar14 + uVar9;
            bVar18 = uVar1 <= uVar14;
            if (uVar14 != uVar1) {
              bVar18 = uVar6 <= uVar17;
            }
            if (bVar18) {
              iVar3 = uVar12 + *(int *)(iVar5 + 0xc);
              *(int *)(iVar5 + 0xc) = iVar3;
              if (uVar17 == uVar6) {
                *(uint *)(*(int *)(uVar15 + 8) + 4) = uVar12 + uVar9 | 1;
              }
              else {
                if (*(int *)(uVar15 + 0x408) == -1) {
                  *(uint *)(uVar15 + 0x408) = uVar17;
                }
                else {
                  *(uint *)(DAT_40e2aee4/*=0x47f52890*/ + 0xc) = iVar3 + (uVar17 - uVar6);
                }
                iVar3 = 0;
                if ((uVar17 & 7) != 0) {
                  iVar3 = 8 - (uVar17 & 7);
                  uVar17 = uVar17 + iVar3;
                }
                iVar7 = (iVar3 - (uVar17 + uVar12)) + (uVar17 + uVar12 + 0xfff & 0xfffff000);
                iVar3 = FUN_40e2a5a4(iVar7);
                if (iVar3 == -1) goto LAB_40e2aea4;
                *(int *)(iVar5 + 0xc) = iVar7 + *(int *)(iVar5 + 0xc);
                *(uint *)(uVar1 + 8) = uVar17;
                *(uint *)(uVar17 + 4) = iVar7 + (iVar3 - uVar17) | 1;
                if (uVar14 != uVar1) {
                  if (uVar9 < 0x10) {
                    *(undefined4 *)(*(int *)(DAT_40e2aee8/*=0x47f40390*/ + 8) + 4) = 1;
                    goto LAB_40e2aea4;
                  }
                  uVar12 = uVar9 - 0xc & 0xfffffff8;
                  *(uint *)(uVar14 + 4) = uVar12 | *(uint *)(uVar14 + 4) & 1;
                  *(undefined4 *)(uVar14 + uVar12 + 4) = 5;
                  *(undefined4 *)(uVar14 + uVar12 + 8) = 5;
                  if (0xf < uVar12) {
                    FUN_40e2a6ec(uVar14 + 8);
                  }
                }
              }
              uVar12 = *(uint *)(iVar5 + 0xc);
              if (*(uint *)(iVar5 + 0x38) < uVar12) {
                *(uint *)(DAT_40e2aee4/*=0x47f52890*/ + 0x38) = uVar12;
              }
              if (*(uint *)(iVar5 + 0x3c) < uVar12) {
                *(uint *)(DAT_40e2aee4/*=0x47f52890*/ + 0x3c) = uVar12;
              }
            }
          }
LAB_40e2aea4:
          uVar12 = (*(uint *)(*(int *)(uVar1 + 8) + 4) & 0xfffffffc) - uVar13;
          if ((int)uVar12 < 0x10) goto LAB_40e2a934;
        }
        iVar3 = *(int *)(uVar1 + 8);
        *(uint *)(iVar3 + 4) = uVar13 | 1;
        *(uint *)(uVar1 + 8) = iVar3 + uVar13;
        *(uint *)(iVar3 + uVar13 + 4) = uVar12 | 1;
      }
      else {
        uVar14 = *(uint *)(iVar3 + 4);
        uVar15 = uVar14 & 0xfffffffc;
        uVar9 = uVar15 - uVar13;
        if ((int)uVar9 < 0x10) {
          *(int *)(DAT_40e2aee8/*=0x47f40390*/ + 0x14) = iVar7;
          *(int *)(uVar1 + 0x10) = iVar7;
          if ((int)uVar9 < 0) {
            if (uVar15 < 0x200) {
              *(uint *)(uVar1 + 4) = *(uint *)(uVar1 + 4) | 1 << ((int)(uVar14 >> 3) >> 2 & 0xffU);
              iVar8 = uVar1 + (uVar14 >> 3) * 8;
              iVar16 = *(int *)(iVar8 + 8);
              *(int *)(iVar3 + 0xc) = iVar8;
              *(int *)(iVar3 + 8) = iVar16;
              *(int *)(iVar8 + 8) = iVar3;
              *(int *)(iVar16 + 0xc) = iVar3;
            }
            else {
              uVar9 = uVar14 >> 9;
              if (uVar9 < 5) {
                iVar8 = (uVar14 >> 6) + 0x38;
              }
              else if (uVar9 < 0x15) {
                iVar8 = uVar9 + 0x5b;
              }
              else if (uVar9 < 0x55) {
                iVar8 = (uVar14 >> 0xc) + 0x6e;
              }
              else if (uVar9 < 0x155) {
                iVar8 = (uVar14 >> 0xf) + 0x77;
              }
              else if (uVar9 < 0x555) {
                iVar8 = (uVar14 >> 0x12) + 0x7c;
              }
              else {
                iVar8 = 0x7e;
              }
              iVar10 = uVar1 + iVar8 * 8;
              iVar16 = *(int *)(iVar10 + 8);
              if (iVar16 == iVar10) {
                *(uint *)(DAT_40e2aee8/*=0x47f40390*/ + 4) =
                     *(uint *)(DAT_40e2aee8/*=0x47f40390*/ + 4) | 1 << (iVar8 >> 2 & 0xffU);
                iVar8 = iVar16;
              }
              else {
                do {
                  iVar8 = iVar16;
                  if ((*(uint *)(iVar16 + 4) & 0xfffffffc) <= uVar15) break;
                  iVar16 = *(int *)(iVar16 + 8);
                  iVar8 = iVar16;
                } while (iVar16 != iVar10);
                iVar16 = *(int *)(iVar8 + 0xc);
              }
              *(int *)(iVar3 + 0xc) = iVar16;
              *(int *)(iVar3 + 8) = iVar8;
              *(int *)(iVar16 + 8) = iVar3;
              *(int *)(iVar8 + 0xc) = iVar3;
            }
            goto LAB_40e2abd4;
          }
          *(uint *)(iVar3 + uVar15 + 4) = *(uint *)(iVar3 + uVar15 + 4) | 1;
        }
        else {
          iVar5 = iVar3 + uVar13;
          *(uint *)(iVar3 + 4) = uVar13 | 1;
          *(int *)(uVar1 + 0x14) = iVar5;
          *(int *)(uVar1 + 0x10) = iVar5;
          *(int *)(iVar5 + 0xc) = iVar7;
          *(int *)(iVar5 + 8) = iVar7;
          *(uint *)(iVar5 + 4) = uVar9 | 1;
          *(uint *)(iVar5 + uVar9) = uVar9;
        }
      }
    }
    piVar2 = (int *)(iVar3 + 8);
  }
  return piVar2;
}
