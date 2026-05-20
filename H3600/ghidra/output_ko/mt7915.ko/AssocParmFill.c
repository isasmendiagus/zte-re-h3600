// module: mt7915.ko
// function: AssocParmFill @ 0x12cbb8
// size: 52 bytes
//

void AssocParmFill(undefined4 param_1,undefined4 *param_2,undefined4 *param_3,ushort param_4,
                  undefined4 param_5,undefined2 param_6)

{
  undefined2 uVar1;
  
  *param_2 = *param_3;
  uVar1 = *(undefined2 *)(param_3 + 1);
  *(ushort *)((int)param_2 + 6) = param_4 & 0x533;
  param_2[3] = param_5;
  *(undefined2 *)(param_2 + 1) = uVar1;
  *(undefined2 *)(param_2 + 2) = param_6;
  return;
}

