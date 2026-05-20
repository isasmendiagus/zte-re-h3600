// module: mt7915.ko
// function: BigInteger_Shift_Right1 @ 0x1fe7a8
// size: 284 bytes
//

void BigInteger_Shift_Right1(int param_1,undefined4 param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  size_t __n;
  int local_18;
  int local_14;
  
  local_18 = 0;
  local_14 = 0;
  if (param_1 == 0) {
    BigInteger_Bin2BI(test,0xc0,&local_14);
  }
  else {
    BigInteger_Copy(param_1,&local_14);
  }
  if (local_14 != 0) {
    __n = *(size_t *)(local_14 + 0x18);
    BigInteger_AllocSize(&local_18,__n);
    if (local_18 != 0) {
      memcpy(*(void **)(local_18 + 0xc),*(void **)(local_14 + 0xc),__n);
      iVar3 = *(int *)(local_18 + 0x14) + 0x3fffffff;
      *(undefined4 *)(local_18 + 0x1c) = *(undefined4 *)(local_14 + 0x1c);
      uVar2 = *(uint *)(*(int *)(local_18 + 0xc) + iVar3 * 4);
      *(uint *)(*(int *)(local_18 + 0xc) + iVar3 * 4) = uVar2 >> 1;
      uVar4 = *(int *)(local_18 + 0x14) - 2;
      iVar3 = (int)(short)uVar4;
      if (-1 < iVar3) {
        do {
          uVar4 = (uVar4 & 0xffff) - 1;
          uVar1 = uVar2 << 0x1f;
          uVar2 = *(uint *)(*(int *)(local_18 + 0xc) + iVar3 * 4);
          *(uint *)(*(int *)(local_18 + 0xc) + iVar3 * 4) = uVar1 | uVar2 >> 1;
          iVar3 = (int)(short)uVar4;
        } while (iVar3 != -1);
      }
      BigInteger_ClearHighBits();
      BigInteger_Copy(local_18,param_2);
      release_temporal_usage_big_interger(&local_14);
      release_temporal_usage_big_interger(&local_18);
    }
  }
  return;
}

