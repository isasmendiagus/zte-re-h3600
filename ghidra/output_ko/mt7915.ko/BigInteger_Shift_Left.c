// module: mt7915.ko
// function: BigInteger_Shift_Left @ 0x1fec40
// size: 372 bytes
//

void BigInteger_Shift_Left(int param_1,uint param_2,undefined4 param_3)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  int local_28;
  int local_24;
  
  local_28 = 0;
  local_24 = 0;
  if (param_2 == 0) {
    BigInteger_Copy(param_1,param_3);
    return;
  }
  if (param_1 == 0) {
    BigInteger_Bin2BI(test,0xc0,&local_24);
  }
  else {
    BigInteger_Copy(param_1,&local_24);
  }
  if (local_24 != 0) {
    uVar1 = param_2 >> 5;
    param_2 = param_2 & 0x1f;
    iVar2 = *(int *)(local_24 + 0x18) + uVar1 * 4;
    if (param_2 == 0) {
      BigInteger_AllocSize(&local_28,iVar2);
      if (local_28 == 0) {
        return;
      }
      *(undefined4 *)(local_28 + 0x1c) = *(undefined4 *)(local_24 + 0x1c);
    }
    else {
      BigInteger_AllocSize(&local_28,iVar2 + (param_2 + 7 >> 3));
      if (local_28 == 0) {
        return;
      }
      *(undefined4 *)(local_28 + 0x1c) = *(undefined4 *)(local_24 + 0x1c);
      uVar6 = **(uint **)(local_24 + 0xc);
      *(uint *)(*(int *)(local_28 + 0xc) + uVar1 * 4) = uVar6 << param_2;
      uVar6 = uVar6 >> (0x20 - param_2 & 0xff);
      uVar3 = *(uint *)(local_24 + 0x14);
      if (1 < uVar3) {
        uVar5 = 1;
        uVar7 = uVar5;
        do {
          iVar2 = uVar5 + uVar1;
          uVar3 = uVar7 + 1;
          uVar4 = *(uint *)(*(int *)(local_24 + 0xc) + uVar5 * 4);
          uVar7 = uVar3 & 0xffff;
          uVar5 = (uint)(short)uVar3;
          uVar3 = uVar6 | uVar4 << param_2;
          uVar6 = uVar4 >> (0x20 - param_2 & 0xff);
          *(uint *)(*(int *)(local_28 + 0xc) + iVar2 * 4) = uVar3;
          uVar3 = *(uint *)(local_24 + 0x14);
        } while (uVar5 < uVar3);
      }
      *(uint *)(*(int *)(local_28 + 0xc) + (uVar3 + uVar1) * 4) = uVar6;
    }
    BigInteger_Copy(local_28,param_3);
    release_temporal_usage_big_interger(&local_24);
    release_temporal_usage_big_interger(&local_28);
  }
  return;
}

