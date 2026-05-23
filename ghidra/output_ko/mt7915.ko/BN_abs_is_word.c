// module: mt7915.ko
// function: BN_abs_is_word @ 0x20e000
// size: 68 bytes
//

bool BN_abs_is_word(undefined4 *param_1,int param_2)

{
  if (param_1 == (undefined4 *)0x0) {
    return false;
  }
  if ((param_1[1] == 1) && (*(int *)*param_1 == param_2)) {
    return true;
  }
  return param_2 == 0 && param_1[1] == 0;
}

