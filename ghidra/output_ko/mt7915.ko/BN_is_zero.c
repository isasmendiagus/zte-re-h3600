// module: mt7915.ko
// function: BN_is_zero @ 0x20e044
// size: 20 bytes
//

bool BN_is_zero(int param_1)

{
  bool bVar1;
  
  bVar1 = false;
  if (param_1 != 0) {
    bVar1 = *(int *)(param_1 + 4) == 0;
  }
  return bVar1;
}

