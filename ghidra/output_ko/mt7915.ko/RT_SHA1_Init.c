// module: mt7915.ko
// function: RT_SHA1_Init @ 0x1256d4
// size: 80 bytes
//

void RT_SHA1_Init(undefined4 *param_1)

{
  *param_1 = 0x67452301;
  param_1[1] = 0xefcdab89;
  param_1[3] = 0x10325476;
  param_1[4] = 0xc3d2e1f0;
  param_1[2] = 0x98badcfe;
  __memzero(param_1 + 8,0x40);
  param_1[6] = 0;
  param_1[7] = 0;
  param_1[0x18] = 0;
  return;
}

