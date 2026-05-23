// module: mt7915.ko
// function: ht_cfg_init @ 0x106580
// size: 104 bytes
//

void ht_cfg_init(undefined1 *param_1)

{
  *param_1 = 0xf;
  param_1[0x1a] = 3;
  *(undefined4 *)(param_1 + 0xc) = 0x92a;
  *(undefined4 *)(param_1 + 0x14) = 0x92b;
  param_1[1] = 0;
  param_1[0x10] = 2;
  param_1[0x18] = 0;
  param_1[8] = 0;
  param_1[0x1c] = 0;
  param_1[3] = 1;
  param_1[2] = 1;
  param_1[4] = 1;
  param_1[5] = 1;
  param_1[0x19] = 1;
  param_1[0x1d] = 1;
  *(undefined2 *)(param_1 + 0x1e) = 0x40;
  *(undefined2 *)(param_1 + 0x20) = 0x40;
  return;
}

