// module: mt7915.ko
// function: BN_GENCB_set @ 0x20e1ac
// size: 20 bytes
//

void BN_GENCB_set(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  param_1[1] = param_3;
  param_1[2] = param_2;
  *param_1 = 2;
  return;
}

