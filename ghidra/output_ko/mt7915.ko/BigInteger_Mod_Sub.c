// module: mt7915.ko
// function: BigInteger_Mod_Sub @ 0x1fe460
// size: 176 bytes
//

void BigInteger_Mod_Sub(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int local_1c;
  undefined4 local_18;
  int local_14;
  
  local_1c = 0;
  local_18 = 0;
  BigInteger_Sub(param_1,param_2,&local_1c);
  iVar1 = local_1c;
  if (local_1c != 0) {
    if (*(int *)(local_1c + 0x1c) == 1) {
      BigInteger_Mod(local_1c,param_3,&local_18);
      goto LAB_001fe4d0;
    }
    local_14 = 0;
    *(undefined4 *)(local_1c + 0x1c) = 1;
    iVar1 = local_14;
  }
  local_14 = iVar1;
  BigInteger_Mod(local_1c,param_3,&local_14);
  BigInteger_Sub(param_3,local_14,&local_18);
  release_temporal_usage_big_interger(&local_14);
LAB_001fe4d0:
  BigInteger_Copy(local_18,param_4);
  release_temporal_usage_big_interger(&local_1c);
  release_temporal_usage_big_interger(&local_18);
  return;
}

