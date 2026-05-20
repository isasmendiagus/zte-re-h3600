// module: mt7915.ko
// function: BN_is_odd @ 0x20e0f8
// size: 36 bytes
//

uint BN_is_odd(undefined4 *param_1)

{
  uint uVar1;
  
  if (param_1 != (undefined4 *)0x0) {
    if ((int)param_1[1] < 1) {
      uVar1 = 0;
    }
    else {
      uVar1 = *(uint *)*param_1 & 1;
    }
    return uVar1;
  }
  return 0;
}

