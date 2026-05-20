// module: mt7915.ko
// function: set_default_sta_edca_param @ 0x128964
// size: 108 bytes
//

void set_default_sta_edca_param(undefined1 *param_1)

{
  *param_1 = 1;
  param_1[8] = 7;
  *(undefined2 *)(param_1 + 0x18) = 0x5e;
  *(undefined2 *)(param_1 + 0x1a) = 0x2f;
  param_1[7] = 3;
  param_1[0xd] = 3;
  param_1[0x12] = 3;
  param_1[9] = 2;
  param_1[10] = 2;
  param_1[0xe] = 2;
  param_1[0xb] = 4;
  param_1[0xc] = 4;
  param_1[0x11] = 4;
  param_1[0xf] = 10;
  param_1[0x10] = 10;
  *(undefined2 *)(param_1 + 0x14) = 0;
  *(undefined2 *)(param_1 + 0x16) = 0;
  return;
}

