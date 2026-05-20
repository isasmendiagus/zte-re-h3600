// module: mt7915.ko
// function: set_default_ap_edca_param @ 0x1288f4
// size: 112 bytes
//

void set_default_ap_edca_param(undefined1 *param_1)

{
  param_1[8] = 7;
  param_1[0xe] = 2;
  param_1[0xf] = 6;
  param_1[0x10] = 10;
  *(undefined2 *)(param_1 + 0x18) = 0x5e;
  *(undefined2 *)(param_1 + 0x1a) = 0x2f;
  *param_1 = 1;
  param_1[9] = 1;
  param_1[10] = 1;
  param_1[7] = 3;
  param_1[0xd] = 3;
  param_1[0x12] = 3;
  param_1[0xb] = 4;
  param_1[0xc] = 4;
  param_1[0x11] = 4;
  *(undefined2 *)(param_1 + 0x14) = 0;
  *(undefined2 *)(param_1 + 0x16) = 0;
  return;
}

