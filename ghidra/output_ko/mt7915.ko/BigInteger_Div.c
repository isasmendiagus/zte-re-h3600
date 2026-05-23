// module: mt7915.ko
// function: BigInteger_Div @ 0x1fc9e0
// size: 1260 bytes
//

void BigInteger_Div(int param_1,int param_2,int *param_3,int *param_4)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  bool bVar10;
  undefined4 local_34;
  undefined4 local_30;
  int local_2c [2];
  
  local_34 = 0;
  local_30 = 0;
  local_2c[0] = 0;
  if (((param_1 == 0) || (*(int *)(param_1 + 0xc) == 0 || param_2 == 0)) ||
     (*(int **)(param_2 + 0xc) == (int *)0x0)) {
    printk("BigInteger_Div: first or second operand is NULL.\n");
  }
  else if ((*(int *)(param_2 + 0x18) == 1) && (**(int **)(param_2 + 0xc) == 0)) {
    printk("BigInteger_Div: second operand is zero.\n");
  }
  else {
    if (*param_3 == 0) {
      BigInteger_Init(param_3);
    }
    if (*param_4 == 0) {
      BigInteger_Init(param_4);
    }
    if ((*(int *)(param_2 + 0x18) == 1) && (**(int **)(param_2 + 0xc) == 1)) {
      BigInteger_Copy(param_1,param_3);
      BigInteger_Bin2BI(&DAT_005f4a1c,1,param_4);
    }
    else {
      iVar1 = BigInteger_UnsignedCompare(param_1,param_2);
      if (iVar1 == 0) {
        BigInteger_Bin2BI(&_LANCHOR1,1,param_3);
        BigInteger_Bin2BI(&DAT_005f4a1c,1,param_4);
      }
      else if (iVar1 == -1) {
        BigInteger_Bin2BI(&DAT_005f4a1c,1,param_3);
        BigInteger_Copy(param_1,param_4);
      }
      else {
        BigInteger_AllocSize(param_3,(*(int *)(param_1 + 0x18) + 1) - *(int *)(param_2 + 0x18));
        BigInteger_AllocSize(param_4,*(undefined4 *)(param_2 + 0x18));
        iVar1 = *(int *)(param_1 + 0x18) << 1;
        BigInteger_AllocSize(&local_34,iVar1);
        BigInteger_AllocSize(&local_30,iVar1);
        BigInteger_Copy(param_1,param_4);
        iVar1 = *(int *)(param_2 + 0x18);
        uVar2 = BigInteger_GetByteValue(param_2,iVar1);
        uVar5 = (*(int *)(param_1 + 0x18) + 1) - iVar1;
        if (uVar2 == 0) {
          printk("BigInteger_Div: SecondHighByte is zero.\n");
          return;
        }
        if (-1 < (int)uVar5) {
          uVar9 = uVar5;
          do {
            iVar1 = BigInteger_UnsignedCompare(*param_4,param_2);
            if (iVar1 == -1) break;
            if ((*param_4 != 0) &&
               ((*(int *)(param_2 + 0x18) - *(int *)(*param_4 + 0x18)) + uVar9 < 2)) {
              BigInteger_AllocSize(local_2c,uVar9 + 1);
              iVar1 = *param_4;
              if (uVar9 == 0) {
                uVar6 = 0;
              }
              else {
                uVar6 = uVar9 - 1 >> 2;
              }
              if ((uVar9 & 3) == 0) {
                iVar7 = 3;
              }
              else {
                iVar7 = (uVar9 & 3) - 1;
              }
              iVar8 = (*(int *)(param_1 + 0x18) - uVar5) + uVar9;
              iVar3 = BigInteger_GetByteValue(iVar1,iVar8 + 1);
              uVar4 = BigInteger_GetByteValue(iVar1,iVar8);
              uVar4 = iVar3 << 8 | uVar4;
              if (uVar2 <= uVar4) {
                iVar1 = __aeabi_uidiv(uVar4,uVar2);
                uVar4 = __aeabi_uidiv(uVar4,uVar2 + 1);
                if (uVar4 <= iVar1 + 1U) {
                  if (local_2c[0] == 0) {
                    return;
                  }
                  iVar3 = uVar6 * 4;
                  uVar6 = iVar7 << 3;
                  while( true ) {
                    if (*(int *)(local_2c[0] + 0x10) != 0) {
                      __memzero(*(undefined4 *)(local_2c[0] + 0xc));
                    }
                    if (0xff < (int)uVar4 && iVar7 == 3) {
                      *(uint *)(*(int *)(local_2c[0] + 0xc) + iVar3) = uVar4 << 0x18;
                      *(uint *)(*(int *)(local_2c[0] + 0xc) + iVar3 + 4) = (uVar4 << 0x10) >> 0x18;
                    }
                    else {
                      *(uint *)(*(int *)(local_2c[0] + 0xc) + iVar3) = uVar4 << (uVar6 & 0xff);
                    }
                    BigInteger_Mul(param_2,local_2c[0],&local_34);
                    iVar8 = BigInteger_UnsignedCompare(*param_4,local_34);
                    if (iVar8 < 1) break;
                    uVar4 = uVar4 + 1;
                    if (iVar1 + 1U < uVar4) goto LAB_001fcb18;
                    if (local_2c[0] == 0) {
                      return;
                    }
                  }
                  if (iVar8 == -1) {
                    BigInteger_AllocSize(local_2c,uVar9 + 1);
                    uVar4 = uVar4 - 1;
                    if (local_2c[0] == 0) {
                      return;
                    }
                    iVar1 = *(int *)(local_2c[0] + 0xc);
                    if (*(int *)(local_2c[0] + 0x10) != 0) {
                      __memzero();
                      iVar1 = *(int *)(local_2c[0] + 0xc);
                    }
                    if (0xff < (int)uVar4 && iVar7 == 3) {
                      *(uint *)(iVar1 + iVar3) = (uVar4 & 0xff) << (uVar6 & 0xff);
                      *(uint *)(*(int *)(local_2c[0] + 0xc) + iVar3 + 4) = uVar4 * 0x10000 >> 0x18;
                    }
                    else {
                      *(uint *)(iVar1 + iVar3) = uVar4 << (uVar6 & 0xff);
                    }
                    BigInteger_Mul(param_2,local_2c[0],&local_34);
                  }
                  BigInteger_Sub(*param_4,local_34,&local_30);
                  BigInteger_Copy(local_30,param_4);
                  BigInteger_Add(*param_3,local_2c[0],&local_30);
                  BigInteger_Copy(local_30,param_3);
                }
              }
            }
LAB_001fcb18:
            bVar10 = uVar9 != 0;
            uVar9 = uVar9 - 1;
          } while (bVar10);
        }
      }
    }
    if ((*param_3 != 0) && (*param_4 != 0)) {
      *(int *)(*param_3 + 0x1c) = *(int *)(param_2 + 0x1c) * *(int *)(param_1 + 0x1c);
      *(int *)(*param_4 + 0x1c) = *(int *)(param_2 + 0x1c) * *(int *)(param_1 + 0x1c);
      BigInteger_ClearHighBits(*param_3);
      BigInteger_ClearHighBits(*param_4);
      release_temporal_usage_big_interger(&local_34);
      release_temporal_usage_big_interger(&local_30);
      release_temporal_usage_big_interger(local_2c);
    }
  }
  return;
}

