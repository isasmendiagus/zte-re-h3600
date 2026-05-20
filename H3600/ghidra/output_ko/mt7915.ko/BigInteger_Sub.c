// module: mt7915.ko
// function: BigInteger_Sub @ 0x1fbb64
// size: 716 bytes
//

void BigInteger_Sub(int param_1,int param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint *puVar9;
  int iVar10;
  uint local_2c [2];
  
  if (((param_1 == 0) || (*(int *)(param_1 + 0xc) == 0 || param_2 == 0)) ||
     (*(int *)(param_2 + 0xc) == 0)) {
    printk("BigInteger_Sub: first or second operand is NULL.\n");
  }
  else {
    if (*param_3 == 0) {
      BigInteger_Init(param_3);
    }
    iVar1 = BigInteger_UnsignedCompare(param_1,param_2);
    local_2c[0] = (uint)(0 < *(int *)(param_2 + 0x1c) * *(int *)(param_1 + 0x1c));
    uVar3 = local_2c[0];
    if (iVar1 != 0) {
      uVar3 = 0;
    }
    if (uVar3 != 0) {
      BigInteger_AllocSize(param_3,1);
      return;
    }
    if (local_2c[0] == 0) {
      FUN_001fae18(local_2c);
      if (*(int *)(param_1 + 0x1c) == 1 && *(int *)(param_2 + 0x1c) == -1) {
        BigInteger_Copy(param_2,local_2c);
        if (local_2c[0] != 0) {
          *(undefined4 *)(local_2c[0] + 0x1c) = 1;
        }
        BigInteger_Add(param_1,local_2c[0],param_3);
      }
      else if (*(int *)(param_2 + 0x1c) == 1 && *(int *)(param_1 + 0x1c) == -1) {
        BigInteger_Copy(param_1,local_2c);
        if (local_2c[0] != 0) {
          *(undefined4 *)(local_2c[0] + 0x1c) = 1;
        }
        BigInteger_Add(local_2c[0],param_2,param_3);
        if (*param_3 != 0) {
          *(undefined4 *)(*param_3 + 0x1c) = 0xffffffff;
        }
      }
      release_temporal_usage_big_interger(local_2c);
    }
    else {
      if (iVar1 == 1) {
        BigInteger_Copy(param_1,param_3);
        iVar4 = param_2;
      }
      else {
        if (iVar1 != -1) {
          return;
        }
        BigInteger_Copy(param_2,param_3);
        iVar4 = param_1;
      }
      iVar10 = *param_3;
      if (iVar10 != 0) {
        puVar9 = *(uint **)(iVar10 + 0xc);
        iVar2 = *(int *)(iVar4 + 0xc);
        if (*(int *)(iVar10 + 0x14) != 0) {
          uVar5 = 0;
          uVar3 = 0;
          do {
            if (uVar5 < *(uint *)(iVar4 + 0x14)) {
              uVar7 = *puVar9;
              uVar8 = *(uint *)(iVar2 + uVar5 * 4);
              if (uVar8 <= uVar7 - uVar3) {
                uVar6 = uVar3;
                if (uVar7 != 0) {
                  uVar6 = 0;
                }
                if (uVar6 == 0) {
                  *puVar9 = (uVar7 - uVar8) - uVar3;
                  goto LAB_001fbcd8;
                }
              }
              *puVar9 = (1 - uVar3) + uVar7 + ~uVar8;
              uVar6 = 1;
            }
            else {
              if (uVar3 <= *puVar9) {
                *puVar9 = *puVar9 - uVar3;
                iVar10 = *param_3;
                break;
              }
              uVar6 = 1;
              *puVar9 = 0xffffffff;
            }
LAB_001fbcd8:
            iVar10 = *param_3;
            uVar5 = uVar5 + 1;
            puVar9 = puVar9 + 1;
            uVar3 = uVar6;
          } while (uVar5 < *(uint *)(iVar10 + 0x14));
        }
        if ((iVar1 == -1 && (*(int *)(param_2 + 0x1c) == 1 && *(int *)(param_1 + 0x1c) == 1)) ||
           (iVar1 == 1 && (*(int *)(param_1 + 0x1c) == -1 && *(int *)(param_2 + 0x1c) == -1))) {
          *(undefined4 *)(iVar10 + 0x1c) = 0xffffffff;
          iVar10 = *param_3;
        }
        BigInteger_ClearHighBits(iVar10);
        return;
      }
    }
  }
  return;
}

