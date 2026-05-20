// module: mt7915.ko
// function: vht_cfg_init @ 0x106990
// size: 36 bytes
//

void vht_cfg_init(undefined1 *param_1)

{
  *param_1 = 1;
  param_1[4] = 0;
  param_1[2] = 1;
  param_1[1] = 1;
  param_1[3] = 1;
  param_1[6] = 1;
  return;
}

