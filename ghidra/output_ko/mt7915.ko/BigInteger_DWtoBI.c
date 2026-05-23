// module: mt7915.ko
// function: BigInteger_DWtoBI @ 0x1ff0bc
// size: 56 bytes
//

void BigInteger_DWtoBI(undefined4 param_1,int *param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 extraout_r1;
  undefined4 extraout_r2;
  
  BigInteger_AllocSize(param_2,4);
  if (*param_2 == 0) {
    return;
  }
  **(undefined4 **)(*param_2 + 0xc) = param_1;
  BigInteger_ClearHighBits(*param_2,extraout_r1,extraout_r2,param_4);
  return;
}

