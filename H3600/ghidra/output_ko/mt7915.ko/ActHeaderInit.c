// module: mt7915.ko
// function: ActHeaderInit @ 0xa26e8
// size: 108 bytes
//

void ActHeaderInit(undefined4 param_1,byte *param_2,undefined4 *param_3,undefined4 *param_4,
                  undefined4 *param_5)

{
  __memzero(param_2,0x18,param_3,param_4,param_4);
  *param_2 = *param_2 & 3 | 0xd0;
  *(undefined4 *)(param_2 + 4) = *param_3;
  *(undefined2 *)(param_2 + 8) = *(undefined2 *)(param_3 + 1);
  *(undefined4 *)(param_2 + 10) = *param_4;
  *(undefined2 *)(param_2 + 0xe) = *(undefined2 *)(param_4 + 1);
  *(undefined4 *)(param_2 + 0x10) = *param_5;
  *(undefined2 *)(param_2 + 0x14) = *(undefined2 *)(param_5 + 1);
  return;
}

