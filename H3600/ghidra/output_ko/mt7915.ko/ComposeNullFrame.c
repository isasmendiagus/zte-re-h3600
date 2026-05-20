// module: mt7915.ko
// function: ComposeNullFrame @ 0xc7e64
// size: 120 bytes
//

void ComposeNullFrame(undefined4 param_1,byte *param_2,undefined4 *param_3,undefined4 *param_4,
                     undefined4 *param_5)

{
  __memzero(param_2,0x18,param_3,param_4,param_4);
  param_2[1] = param_2[1] | 1;
  *param_2 = *param_2 & 3 | 0x48;
  *(undefined4 *)(param_2 + 4) = *param_3;
  *(undefined2 *)(param_2 + 8) = *(undefined2 *)(param_3 + 1);
  *(undefined4 *)(param_2 + 10) = *param_4;
  *(undefined2 *)(param_2 + 0xe) = *(undefined2 *)(param_4 + 1);
  *(undefined4 *)(param_2 + 0x10) = *param_5;
  *(undefined2 *)(param_2 + 0x14) = *(undefined2 *)(param_5 + 1);
  return;
}

