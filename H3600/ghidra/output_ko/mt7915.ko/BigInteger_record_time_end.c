// module: mt7915.ko
// function: BigInteger_record_time_end @ 0x1faf40
// size: 76 bytes
//

void BigInteger_record_time_end
               (int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  iVar1 = param_1[2];
  iVar2 = jiffies - param_1[1];
  param_1[1] = iVar2;
  if (iVar1 == -1) {
    return;
  }
  iVar2 = __aeabi_uidiv(*param_1 * iVar1 + iVar2,iVar1 + 1,iVar1,iVar2,param_4);
  param_1[2] = iVar1 + 1;
  *param_1 = iVar2;
  return;
}

