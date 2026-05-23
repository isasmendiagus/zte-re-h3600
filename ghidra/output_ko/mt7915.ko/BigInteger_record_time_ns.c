// module: mt7915.ko
// function: BigInteger_record_time_ns @ 0x1faf8c
// size: 56 bytes
//

void BigInteger_record_time_ns
               (undefined4 *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = param_1[1];
  iVar3 = param_1[2];
  param_2 = param_2 + iVar2;
  param_1[1] = param_2;
  if (iVar3 == -1) {
    return;
  }
  uVar1 = __aeabi_uidiv(param_2,iVar3 + 1,iVar2,iVar3,param_4);
  param_1[2] = iVar3 + 1;
  *param_1 = uVar1;
  return;
}

