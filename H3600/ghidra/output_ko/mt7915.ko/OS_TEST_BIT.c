// module: mt7915.ko
// function: OS_TEST_BIT @ 0x2451c8
// size: 36 bytes
//

uint OS_TEST_BIT(uint param_1,int param_2)

{
  uint uVar1;
  
  uVar1 = param_1 + 0x1f;
  if (-1 < (int)param_1) {
    uVar1 = param_1;
  }
  return *(uint *)(param_2 + ((int)uVar1 >> 5) * 4) >> (param_1 & 0x1f) & 1;
}

