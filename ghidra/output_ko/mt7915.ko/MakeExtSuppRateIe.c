// module: mt7915.ko
// function: MakeExtSuppRateIe @ 0xb43b0
// size: 128 bytes
//

void MakeExtSuppRateIe(undefined4 param_1,int param_2,int *param_3,int param_4)

{
  int iVar1;
  int local_14 [2];
  
  iVar1 = *param_3;
  if (*(char *)(param_2 + 0xaeb) != '\0' && *(short *)(param_2 + 0x18) != 2) {
    local_14[0] = 0;
    MakeOutgoingFrame(param_4 + iVar1,local_14,1,&ExtRateIe,1,param_2 + 0xaeb,
                      *(char *)(param_2 + 0xaeb),param_2 + 0xaec,0xffffffff);
    *param_3 = iVar1 + local_14[0];
  }
  return;
}

