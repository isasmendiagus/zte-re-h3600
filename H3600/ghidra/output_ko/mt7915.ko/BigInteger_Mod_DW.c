// module: mt7915.ko
// function: BigInteger_Mod_DW @ 0x1ff8a4
// size: 48 bytes
//

void BigInteger_Mod_DW(int param_1,undefined4 param_2,int *param_3)

{
  int extraout_r1;
  
  __aeabi_uidivmod(**(undefined4 **)(param_1 + 0xc));
  *param_3 = extraout_r1;
  **(int **)(param_1 + 0xc) = **(int **)(param_1 + 0xc) - extraout_r1;
  return;
}

