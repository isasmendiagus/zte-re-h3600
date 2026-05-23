// module: mt7915.ko
// function: BigInteger_Mul @ 0x1fc3b0
// size: 700 bytes
//

void BigInteger_Mul(int param_1,int param_2,int *param_3)

{
  longlong lVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  int *piVar9;
  uint uVar10;
  bool bVar11;
  uint local_38;
  
  if (((param_1 == 0) || (*(int **)(param_1 + 0xc) == (int *)0x0 || param_2 == 0)) ||
     (piVar9 = *(int **)(param_2 + 0xc), piVar9 == (int *)0x0)) {
    printk("BigInteger_Mul: first or second operand is NULL.\n");
    return;
  }
  if (*(int *)(param_1 + 0x18) == 1) {
    iVar5 = **(int **)(param_1 + 0xc);
    if (iVar5 == 0) {
LAB_001fc5e0:
      BigInteger_AllocSize(param_3,1);
      iVar5 = *param_3;
    }
    else {
      iVar7 = *(int *)(param_2 + 0x18);
      if (iVar7 == 1) {
        iVar7 = *piVar9;
        if (iVar7 == 0) goto LAB_001fc5e0;
        if (iVar5 != 1) goto LAB_001fc614;
      }
      else if (iVar5 != 1) goto LAB_001fc400;
      BigInteger_Copy(param_2,param_3);
      iVar5 = *param_3;
    }
  }
  else {
    iVar7 = *(int *)(param_2 + 0x18);
    if (iVar7 == 1) {
      iVar7 = *piVar9;
      if (iVar7 == 0) goto LAB_001fc5e0;
LAB_001fc614:
      if (iVar7 == 1) {
        BigInteger_Copy(param_1,param_3);
        iVar5 = *param_3;
        goto joined_r0x001fc5f4;
      }
      iVar7 = 1;
    }
LAB_001fc400:
    BigInteger_AllocSize(param_3,iVar7 + *(int *)(param_1 + 0x18));
    iVar5 = *param_3;
    if (iVar5 == 0) {
      return;
    }
    uVar10 = *(uint *)(param_1 + 0x14);
    if (uVar10 == 0) goto LAB_001fc560;
    local_38 = 0;
    iVar7 = 0;
    do {
      uVar2 = *(uint *)(*(int *)(param_1 + 0xc) + iVar7);
      if ((uVar2 != 0) && (*(int *)(param_2 + 0x14) != 0)) {
        uVar8 = 0;
        uVar10 = 0;
        iVar3 = iVar7;
        while( true ) {
          iVar4 = uVar10 * 4;
          uVar10 = uVar10 + 1;
          lVar1 = (ulonglong)*(uint *)(*(int *)(param_2 + 0xc) + iVar4) * (ulonglong)uVar2 +
                  (ulonglong)*(uint *)(*(int *)(iVar5 + 0xc) + iVar3) + (ulonglong)uVar8;
          *(int *)(*(int *)(iVar5 + 0xc) + iVar3) = (int)lVar1;
          uVar8 = (uint)((ulonglong)lVar1 >> 0x20);
          iVar3 = iVar3 + 4;
          if (*(uint *)(param_2 + 0x14) <= uVar10) break;
          iVar5 = *param_3;
        }
        if (uVar8 == 0) {
          iVar5 = *param_3;
          uVar10 = *(uint *)(param_1 + 0x14);
        }
        else {
          iVar5 = *param_3;
          uVar2 = uVar10 + local_38;
          if (uVar2 < *(uint *)(iVar5 + 0x14)) {
            iVar3 = uVar2 * 4;
            iVar4 = (local_38 + 1 + uVar10) - uVar2;
            do {
              uVar2 = uVar2 + iVar4;
              uVar10 = *(uint *)(*(int *)(iVar5 + 0xc) + iVar3);
              bVar11 = CARRY4(uVar8,uVar10);
              iVar6 = uVar8 + uVar10;
              uVar8 = 1;
              *(int *)(*(int *)(iVar5 + 0xc) + iVar3) = iVar6;
              iVar3 = iVar3 + 4;
              if (!bVar11) {
                iVar5 = *param_3;
                uVar10 = *(uint *)(param_1 + 0x14);
                goto LAB_001fc548;
              }
              iVar5 = *param_3;
            } while (uVar2 < *(uint *)(iVar5 + 0x14));
            uVar10 = *(uint *)(param_1 + 0x14);
          }
          else {
            uVar10 = *(uint *)(param_1 + 0x14);
          }
        }
      }
LAB_001fc548:
      local_38 = local_38 + 1;
      iVar7 = iVar7 + 4;
    } while (local_38 < uVar10);
  }
joined_r0x001fc5f4:
  if (iVar5 == 0) {
    return;
  }
LAB_001fc560:
  *(int *)(iVar5 + 0x1c) = *(int *)(param_2 + 0x1c) * *(int *)(param_1 + 0x1c);
  BigInteger_ClearHighBits(*param_3);
  return;
}

