// module: mt7915.ko
// function: BigInteger_Mod @ 0x1fdcac
// size: 1184 bytes
//

void BigInteger_Mod(int param_1,int param_2,int *param_3)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  bool bVar11;
  int *local_5c;
  undefined4 *local_58;
  undefined4 *local_50;
  undefined4 local_34;
  undefined4 local_30;
  int local_2c [2];
  
  local_34 = 0;
  local_30 = 0;
  local_2c[0] = 0;
  if (((param_1 == 0) || (*(int *)(param_1 + 0xc) == 0 || param_2 == 0)) ||
     (*(int **)(param_2 + 0xc) == (int *)0x0)) {
    printk("BigInteger_Div: first or second operand is NULL.\n");
    return;
  }
  if (*(int *)(param_2 + 0x18) == 1) {
    iVar2 = **(int **)(param_2 + 0xc);
    if (iVar2 == 0) {
      printk("BigInteger_Div: second operand is zero.\n");
      return;
    }
    if (*param_3 == 0) goto LAB_001fe098;
LAB_001fe00c:
    if (iVar2 != 1) goto LAB_001fdd08;
  }
  else {
    if (*param_3 == 0) {
LAB_001fe098:
      BigInteger_Init(param_3);
      if (*(int *)(param_2 + 0x18) == 1) {
        iVar2 = **(int **)(param_2 + 0xc);
        goto LAB_001fe00c;
      }
    }
LAB_001fdd08:
    iVar2 = BigInteger_UnsignedCompare(param_1,param_2);
    if (iVar2 != 0) {
      if (iVar2 == -1) {
        BigInteger_Copy(param_1,param_3);
        iVar2 = *param_3;
      }
      else {
        BigInteger_AllocSize(param_3,*(undefined4 *)(param_2 + 0x18));
        iVar2 = *(int *)(param_1 + 0x18) << 1;
        BigInteger_AllocSize(&local_34,iVar2);
        BigInteger_AllocSize(&local_30,iVar2);
        BigInteger_AllocSize(local_2c,iVar2);
        BigInteger_Copy(param_1,param_3);
        uVar7 = *(uint *)(param_2 + 0x18);
        uVar3 = BigInteger_GetByteValue(param_2,uVar7);
        uVar6 = (*(int *)(param_1 + 0x18) + 1) - uVar7;
        if (uVar3 == 0) {
          printk("BigInteger_Mod: SecondHighByte is zero.\n");
          return;
        }
        iVar2 = *param_3;
        if (-1 < (int)uVar6) {
          uVar9 = uVar6;
          do {
            iVar2 = BigInteger_UnsignedCompare(iVar2,param_2);
            if (iVar2 == -1) {
              iVar2 = *param_3;
              break;
            }
            iVar2 = *param_3;
            if ((iVar2 != 0) && ((*(int *)(param_2 + 0x18) - *(int *)(iVar2 + 0x18)) + uVar9 < 2)) {
              BigInteger_AllocSize(local_2c,uVar9 + 1);
              if (uVar9 != 0) {
                uVar7 = uVar9 - 1;
              }
              iVar2 = *param_3;
              if (uVar9 != 0) {
                uVar7 = uVar7 >> 2;
              }
              else {
                uVar7 = 0;
              }
              if ((uVar9 & 3) == 0) {
                iVar8 = 3;
              }
              else {
                iVar8 = (uVar9 & 3) - 1;
              }
              iVar10 = (*(int *)(param_1 + 0x18) - uVar6) + uVar9;
              iVar4 = BigInteger_GetByteValue(iVar2,iVar10 + 1);
              uVar5 = BigInteger_GetByteValue(iVar2,iVar10);
              uVar5 = iVar4 << 8 | uVar5;
              if (uVar3 <= uVar5) {
                iVar4 = __aeabi_uidiv(uVar5,uVar3);
                uVar5 = __aeabi_uidiv(uVar5,uVar3 + 1);
                if (uVar5 <= iVar4 + 1U) {
                  if (local_2c[0] == 0) {
                    return;
                  }
                  uVar7 = uVar7 * 4;
                  uVar1 = iVar8 << 3;
                  while( true ) {
                    if (*(int *)(local_2c[0] + 0x10) != 0) {
                      __memzero(*(undefined4 *)(local_2c[0] + 0xc));
                    }
                    if (0xff < (int)uVar5 && iVar8 == 3) {
                      *(uint *)(*(int *)(local_2c[0] + 0xc) + uVar7) = uVar5 << 0x18;
                      *(uint *)(*(int *)(local_2c[0] + 0xc) + uVar7 + 4) = (uVar5 << 0x10) >> 0x18;
                    }
                    else {
                      *(uint *)(*(int *)(local_2c[0] + 0xc) + uVar7) = uVar5 << (uVar1 & 0xff);
                    }
                    BigInteger_Mul(param_2,local_2c[0],&local_34);
                    iVar2 = BigInteger_UnsignedCompare(*param_3,local_34);
                    if (iVar2 < 1) {
                      if (iVar2 == -1) {
                        uVar5 = uVar5 - 1;
                        iVar2 = *(int *)(local_2c[0] + 0xc);
                        if (*(int *)(local_2c[0] + 0x10) != 0) {
                          __memzero();
                          iVar2 = *(int *)(local_2c[0] + 0xc);
                        }
                        if (0xff < (int)uVar5 && iVar8 == 3) {
                          *(uint *)(iVar2 + uVar7) = (uVar5 & 0xff) << (uVar1 & 0xff);
                          uVar7 = *(int *)(local_2c[0] + 0xc) + uVar7;
                          *(uint *)(uVar7 + 4) = uVar5 * 0x10000 >> 0x18;
                        }
                        else {
                          *(uint *)(iVar2 + uVar7) = uVar5 << (uVar1 & 0xff);
                        }
                        BigInteger_Mul(param_2,local_2c[0],&local_34);
                      }
                      BigInteger_Sub(*param_3,local_34,&local_30);
                      BigInteger_Copy(local_30,param_3);
                      iVar2 = *param_3;
                      goto LAB_001fdddc;
                    }
                    uVar5 = uVar5 + 1;
                    if (iVar4 + 1U < uVar5) break;
                    if (local_2c[0] == 0) {
                      return;
                    }
                  }
                  iVar2 = *param_3;
                }
              }
            }
LAB_001fdddc:
            bVar11 = uVar9 != 0;
            uVar9 = uVar9 - 1;
          } while (bVar11);
        }
      }
      goto LAB_001fdfb4;
    }
  }
  BigInteger_Bin2BI(&DAT_005f4a1c,1,param_3);
  iVar2 = *param_3;
LAB_001fdfb4:
  local_50 = &local_30;
  local_58 = &local_34;
  local_5c = local_2c;
  iVar8 = 0;
  if (iVar2 != 0) {
    *(int *)(iVar2 + 0x1c) = *(int *)(param_2 + 0x1c) * *(int *)(param_1 + 0x1c);
    iVar8 = *param_3;
  }
  BigInteger_ClearHighBits(iVar8);
  release_temporal_usage_big_interger(local_58);
  release_temporal_usage_big_interger(local_50);
  release_temporal_usage_big_interger(local_5c);
  return;
}

