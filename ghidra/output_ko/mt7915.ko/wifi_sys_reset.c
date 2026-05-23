// module: mt7915.ko
// function: wifi_sys_reset @ 0x1044a4
// size: 56 bytes
//

void wifi_sys_reset(undefined4 *param_1)

{
  param_1[1] = param_1 + 1;
  param_1[2] = param_1 + 1;
  param_1[7] = param_1 + 7;
  param_1[8] = param_1 + 7;
  param_1[4] = param_1 + 4;
  param_1[5] = param_1 + 4;
  *param_1 = 0;
  param_1[6] = 0;
  param_1[3] = 0;
  return;
}

