// module: mt7915.ko
// function: BigInteger_Copy @ 0x1fb640
// size: 104 bytes
//

void BigInteger_Copy(int param_1,int *param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (param_1 == 0) {
    return;
  }
  BigInteger_AllocSize(param_2,*(undefined4 *)(param_1 + 0x18),param_3,param_4,param_4);
  iVar1 = *param_2;
  if (iVar1 == 0) {
    return;
  }
  memcpy(*(void **)(iVar1 + 0xc),*(void **)(param_1 + 0xc),*(int *)(iVar1 + 0x14) << 2);
  *(undefined4 *)(*param_2 + 0x14) = *(undefined4 *)(param_1 + 0x14);
  *(undefined4 *)(*param_2 + 0x18) = *(undefined4 *)(param_1 + 0x18);
  *(undefined4 *)(*param_2 + 0x1c) = *(undefined4 *)(param_1 + 0x1c);
  return;
}

