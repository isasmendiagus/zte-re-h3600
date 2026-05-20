// module: mt7915.ko
// function: BN_is_one @ 0x20e058
// size: 60 bytes
//

bool BN_is_one(undefined4 *param_1)

{
  if (param_1 == (undefined4 *)0x0) {
    return false;
  }
  if ((param_1[1] == 1) && (*(int *)*param_1 == 1)) {
    return param_1[3] == 0;
  }
  return false;
}

