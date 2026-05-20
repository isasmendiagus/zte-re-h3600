// module: mt7915.ko
// function: Bignum_Mod_DW @ 0x20c8a4
// size: 44 bytes
//

void Bignum_Mod_DW(undefined4 *param_1,int param_2,uint *param_3)

{
  *param_3 = *(uint *)*param_1 & param_2 - 1U;
  *(uint *)*param_1 = -param_2 & *(uint *)*param_1;
  return;
}

