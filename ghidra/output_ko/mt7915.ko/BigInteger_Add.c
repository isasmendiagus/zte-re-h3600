// module: mt7915.ko
// function: BigInteger_Add @ 0x1fbe30
// size: 500 bytes
//

void BigInteger_Add(int param_1,int param_2,int *param_3)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  bool bVar10;
  int local_24;
  
  local_24 = 0;
  if (((param_1 == 0) || (*(int *)(param_1 + 0xc) == 0 || param_2 == 0)) ||
     (*(int *)(param_2 + 0xc) == 0)) {
    printk("BigInteger_Add: first or second operand is NULL.\n");
  }
  else {
    if (*param_3 == 0) {
      BigInteger_Init(param_3);
    }
    iVar1 = BigInteger_UnsignedCompare(param_1,param_2);
    iVar3 = *(int *)(param_1 + 0x1c);
    iVar9 = *(int *)(param_2 + 0x1c);
    uVar2 = (uint)(iVar9 * iVar3) >> 0x1f;
    if (iVar1 != 0) {
      uVar2 = 0;
    }
    if (uVar2 != 0) {
      BigInteger_AllocSize(param_3,1);
      return;
    }
    if (iVar9 * iVar3 < 1) {
      if (iVar3 == 1 && iVar9 == -1) {
        BigInteger_Copy(param_2,&local_24);
        if (local_24 != 0) {
          *(undefined4 *)(local_24 + 0x1c) = 1;
        }
        BigInteger_Sub(param_1,local_24,param_3);
      }
      else if (iVar9 == 1 && iVar3 == -1) {
        BigInteger_Copy(param_1,&local_24);
        if (local_24 != 0) {
          *(undefined4 *)(local_24 + 0x1c) = 1;
        }
        BigInteger_Sub(param_2,local_24,param_3);
      }
    }
    else {
      uVar2 = *(uint *)(param_1 + 0x18);
      if (uVar2 <= *(uint *)(param_2 + 0x18)) {
        uVar2 = *(uint *)(param_2 + 0x18);
      }
      BigInteger_AllocSize(param_3,uVar2 + 1);
      iVar1 = *param_3;
      if (iVar1 == 0) {
        return;
      }
      if (*(int *)(iVar1 + 0x14) != 0) {
        iVar3 = 0;
        uVar8 = 0;
        uVar2 = 0;
        do {
          uVar4 = *(uint *)(param_1 + 0x14);
          uVar6 = 0;
          uVar5 = uVar4;
          if (uVar2 < uVar4) {
            uVar5 = *(uint *)(param_1 + 0xc);
          }
          uVar7 = 0;
          if (uVar2 < uVar4) {
            uVar6 = *(uint *)(uVar5 + iVar3);
          }
          uVar5 = uVar2 + 1;
          if (uVar2 < *(uint *)(param_2 + 0x14)) {
            uVar2 = *(uint *)(*(int *)(param_2 + 0xc) + iVar3);
            bVar10 = CARRY4(uVar6,uVar2);
            uVar6 = uVar6 + uVar2;
            uVar7 = (uint)bVar10;
          }
          iVar9 = uVar6 + uVar8;
          uVar8 = uVar7 + CARRY4(uVar6,uVar8);
          *(int *)(*(int *)(iVar1 + 0xc) + iVar3) = iVar9;
          iVar1 = *param_3;
          iVar3 = iVar3 + 4;
          uVar2 = uVar5;
        } while (uVar5 < *(uint *)(iVar1 + 0x14));
      }
      *(undefined4 *)(iVar1 + 0x1c) = *(undefined4 *)(param_1 + 0x1c);
      BigInteger_ClearHighBits(*param_3);
    }
    release_temporal_usage_big_interger(&local_24);
  }
  return;
}

