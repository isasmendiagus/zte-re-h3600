// module: mt7915.ko
// function: he_cfg_init @ 0x2062a4
// size: 156 bytes
//

void he_cfg_init(undefined1 *param_1)

{
  *param_1 = 2;
  *(undefined2 *)(param_1 + 10) = 0x3ff;
  param_1[7] = 2;
  param_1[8] = 2;
  param_1[1] = 1;
  param_1[2] = 1;
  param_1[3] = 1;
  param_1[6] = 0;
  param_1[0xc] = 0;
  param_1[0x10] = 0;
  param_1[0x11] = 0;
  param_1[0x12] = 0;
  param_1[0x18] = 0;
  param_1[0x19] = 0;
  param_1[0x13] = 0;
  param_1[0x14] = 0;
  param_1[0x1d] = 0;
  param_1[0x1e] = 0;
  param_1[0x23] = 0;
  param_1[0xf] = 0xff;
  param_1[0x1c] = 0xff;
  param_1[0x17] = 0xff;
  param_1[0x21] = 0xff;
  param_1[0x26] = 0xff;
  param_1[0x1a] = 0xf;
  param_1[0x1b] = 0xf;
  param_1[0x15] = 0xf;
  param_1[0x16] = 0xf;
  param_1[0x1f] = 0xf;
  param_1[0x20] = 0xf;
  param_1[0x24] = 0xf;
  param_1[0x25] = 0xf;
  return;
}

