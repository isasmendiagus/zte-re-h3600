// module: mt7915.ko
// function: BigInteger_is_odd @ 0x1fe3e4
// size: 40 bytes
//

uint BigInteger_is_odd(int param_1)

{
  uint uVar1;
  
  if (param_1 == 0) {
    return 0;
  }
  uVar1 = 0;
  if (*(int *)(param_1 + 0x18) != 0) {
    uVar1 = **(uint **)(param_1 + 0xc) & 1;
  }
  return uVar1;
}

