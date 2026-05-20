// module: mt7915.ko
// function: BigInteger_Square @ 0x1fc66c
// size: 876 bytes
//

void BigInteger_Square(int param_1,int *param_2)

{
  int iVar1;
  int *piVar2;
  longlong lVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  undefined4 *puVar10;
  uint *puVar11;
  uint *puVar12;
  uint uVar13;
  uint uVar14;
  uint *puVar15;
  uint uVar16;
  int local_38;
  uint *local_34;
  
  if ((param_1 == 0) || (*(int **)(param_1 + 0xc) == (int *)0x0)) {
    printk("\tBigInteger_Square: the operand is NULL.\n");
    return;
  }
  if ((*(int *)(param_1 + 0x18) == 1) && (**(int **)(param_1 + 0xc) == 0)) {
    BigInteger_AllocSize(param_2);
LAB_001fc970:
    iVar4 = 0;
    if (*param_2 != 0) {
      *(undefined4 *)(*param_2 + 0x1c) = 1;
      iVar4 = *param_2;
    }
    BigInteger_ClearHighBits(iVar4);
    BigInteger_Free(&DAT_005f4a24);
    BigInteger_Free(&DAT_005f4a20);
    return;
  }
  BigInteger_AllocSize(param_2,(*(int *)(param_1 + 0x18) + 10) * 2);
  BigInteger_AllocSize(&DAT_005f4a20,(*(int *)(param_1 + 0x18) + 10) * 2);
  BigInteger_AllocSize(&DAT_005f4a24,(*(int *)(param_1 + 0x18) + 10) * 2);
  if (DAT_005f4a20 != 0) {
    if (*(int *)(param_1 + 0x14) != 0) {
      uVar14 = 0;
      puVar15 = *(uint **)(DAT_005f4a20 + 0xc);
      do {
        uVar8 = *(uint *)(*(int *)(param_1 + 0xc) + uVar14 * 4);
        uVar14 = uVar14 + 1;
        uVar6 = uVar8 >> 0x10;
        uVar8 = uVar8 & 0xffff;
        uVar13 = uVar6 * uVar8 * 0x20000;
        uVar6 = uVar6 * uVar6 + (uVar6 * uVar8 >> 0xf);
        uVar8 = uVar8 * uVar8 + uVar13;
        if (uVar13 < uVar8 || uVar13 - uVar8 == 0) {
          puVar15[1] = uVar6;
        }
        else {
          puVar15[1] = uVar6 + 1;
        }
        *puVar15 = uVar8;
        puVar15 = puVar15 + 2;
      } while (uVar14 < *(uint *)(param_1 + 0x14));
    }
    puVar15 = *(uint **)(param_1 + 0xc);
    if (*param_2 != 0) {
      puVar10 = *(undefined4 **)(*param_2 + 0xc);
      *puVar10 = 0;
      uVar14 = *(uint *)(param_1 + 0x14);
      uVar13 = *puVar15;
      if (1 < uVar14) {
        uVar6 = 0;
        uVar8 = 1;
        puVar11 = puVar10 + 1;
        do {
          puVar15 = puVar15 + 1;
          uVar8 = uVar8 + 1;
          lVar3 = (ulonglong)*puVar15 * (ulonglong)uVar13 + (ulonglong)uVar6;
          uVar6 = (uint)((ulonglong)lVar3 >> 0x20);
          puVar12 = puVar11 + 1;
          *puVar11 = (uint)lVar3;
          uVar14 = *(uint *)(param_1 + 0x14);
          puVar11 = puVar12;
        } while (uVar8 < uVar14);
        if (uVar6 != 0) {
          *puVar12 = uVar6;
          uVar14 = *(uint *)(param_1 + 0x14);
        }
      }
      iVar4 = *param_2;
      local_38 = 0xc;
      local_34 = *(uint **)(param_1 + 0xc);
      uVar6 = 1;
      uVar13 = uVar14 - 1;
      if (1 < uVar13) {
        do {
          uVar6 = uVar6 + 1;
          local_34 = local_34 + 1;
          uVar8 = *local_34;
          if (uVar6 < uVar14) {
            uVar7 = 0;
            uVar13 = 0;
            puVar15 = local_34;
            puVar11 = (uint *)(*(int *)(iVar4 + 0xc) + local_38);
            uVar16 = uVar6;
            do {
              uVar16 = uVar16 + 1;
              puVar15 = puVar15 + 1;
              uVar13 = uVar13 + CARRY4(uVar7,*puVar11);
              lVar3 = (ulonglong)uVar8 * (ulonglong)*puVar15 + (ulonglong)(uVar7 + *puVar11);
              uVar9 = (uint)((ulonglong)lVar3 >> 0x20);
              puVar12 = puVar11 + 1;
              *puVar11 = (uint)lVar3;
              uVar7 = uVar9 + uVar13;
              uVar14 = *(uint *)(param_1 + 0x14);
              uVar13 = (uint)CARRY4(uVar9,uVar13);
              puVar11 = puVar12;
            } while (uVar16 < uVar14);
            if (uVar7 != 0 || uVar13 != 0) {
              *puVar12 = *puVar12 + uVar7;
              uVar14 = *(uint *)(param_1 + 0x14);
            }
            iVar4 = *param_2;
            uVar13 = uVar14 - 1;
          }
          local_38 = local_38 + 8;
        } while (uVar6 < uVar13);
      }
      BigInteger_ClearHighBits();
      BigInteger_Copy(*param_2,&DAT_005f4a24);
      if (DAT_005f4a24 != 0) {
        iVar4 = *(int *)(DAT_005f4a24 + 0xc);
        if (*(int *)(DAT_005f4a24 + 0x14) == 0) {
          iVar5 = 0;
          uVar14 = 0;
        }
        else {
          uVar14 = 0;
          uVar13 = 0;
          do {
            *(uint *)(iVar4 + uVar13 * 4) = uVar14 | *(int *)(iVar4 + uVar13 * 4) << 1;
            iVar4 = *(int *)(DAT_005f4a24 + 0xc);
            iVar5 = uVar13 * 4;
            iVar1 = uVar13 * 4;
            uVar13 = uVar13 + 1;
            uVar14 = (uint)(*(uint *)(iVar4 + iVar5) < *(uint *)(*(int *)(*param_2 + 0xc) + iVar1));
          } while (uVar13 < *(uint *)(DAT_005f4a24 + 0x14));
          iVar5 = uVar13 * 4;
        }
        *(uint *)(iVar4 + iVar5) = uVar14;
        iVar4 = DAT_005f4a24;
        piVar2 = (int *)(DAT_005f4a24 + 0x14);
        *(int *)(DAT_005f4a24 + 0x18) = *(int *)(DAT_005f4a24 + 0x18) + 1;
        *(int *)(iVar4 + 0x14) = *piVar2 + 1;
        BigInteger_ClearHighBits(iVar4);
        BigInteger_Add(DAT_005f4a24,DAT_005f4a20,param_2);
        goto LAB_001fc970;
      }
    }
  }
  return;
}

