// module: mt7915.ko
// function: BN_STACK_pop @ 0x20ed70
// size: 20 bytes
//

undefined4 BN_STACK_pop(int *param_1)

{
  int iVar1;
  
  iVar1 = param_1[1];
  param_1[1] = iVar1 + -1;
  return *(undefined4 *)(*param_1 + (iVar1 + -1) * 4);
}

