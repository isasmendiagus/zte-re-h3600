// module: mt7915.ko
// function: RT_SHA256_Init @ 0x125b1c
// size: 88 bytes
//

void RT_SHA256_Init(undefined4 *param_1)

{
  *param_1 = 0x6a09e667;
  param_1[1] = 0xbb67ae85;
  param_1[2] = 0x3c6ef372;
  param_1[3] = 0xa54ff53a;
  param_1[4] = 0x510e527f;
  param_1[5] = 0x9b05688c;
  param_1[7] = 0x5be0cd19;
  param_1[6] = 0x1f83d9ab;
  __memzero(param_1 + 10,0x40);
  param_1[8] = 0;
  param_1[9] = 0;
  param_1[0x1a] = 0;
  return;
}

