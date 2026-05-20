// module: mt7915.ko
// function: BN_set_flags @ 0x20e174
// size: 20 bytes
//

void BN_set_flags(int param_1,uint param_2)

{
  if (param_1 != 0) {
    *(uint *)(param_1 + 0x10) = *(uint *)(param_1 + 0x10) | param_2;
  }
  return;
}

