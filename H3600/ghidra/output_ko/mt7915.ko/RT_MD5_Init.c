// module: mt7915.ko
// function: RT_MD5_Init @ 0x124ac4
// size: 72 bytes
//

void RT_MD5_Init(undefined4 *param_1)

{
  *param_1 = 0x67452301;
  param_1[1] = 0xefcdab89;
  param_1[2] = 0x98badcfe;
  param_1[3] = 0x10325476;
  __memzero(param_1 + 6,0x40);
  param_1[0x16] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  return;
}

