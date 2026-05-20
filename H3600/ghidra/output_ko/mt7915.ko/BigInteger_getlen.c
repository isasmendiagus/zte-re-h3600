// module: mt7915.ko
// function: BigInteger_getlen @ 0x1fb3b8
// size: 12 bytes
//

undefined4 BigInteger_getlen(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (param_1 != 0) {
    uVar1 = *(undefined4 *)(param_1 + 0x18);
  }
  return uVar1;
}

