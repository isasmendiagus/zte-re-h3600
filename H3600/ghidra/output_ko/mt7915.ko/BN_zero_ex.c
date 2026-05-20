// module: mt7915.ko
// function: BN_zero_ex @ 0x20dfec
// size: 20 bytes
//

void BN_zero_ex(int param_1)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 4) = 0;
    *(undefined4 *)(param_1 + 0xc) = 0;
  }
  return;
}

