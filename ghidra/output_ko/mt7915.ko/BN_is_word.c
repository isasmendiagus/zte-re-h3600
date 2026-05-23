// module: mt7915.ko
// function: BN_is_word @ 0x20e094
// size: 100 bytes
//

bool BN_is_word(undefined4 *param_1,int param_2)

{
  if (param_1 == (undefined4 *)0x0) {
    return false;
  }
  if (param_1[1] != 1) {
    return param_2 == 0 && param_1[1] == 0;
  }
  if (param_2 != *(int *)*param_1) {
    return false;
  }
  if (param_2 == 0) {
    return true;
  }
  return param_1[3] == 0;
}

