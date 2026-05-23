// module: mt7915.ko
// function: BarHeaderInit @ 0xa3ed0
// size: 136 bytes
//

void BarHeaderInit(undefined4 param_1,byte *param_2,undefined4 *param_3,undefined4 *param_4)

{
  short sVar1;
  
  __memzero(param_2,0x14,param_3,param_4,param_4);
  param_2[0x10] = param_2[0x10] & 0xfc | 4;
  *param_2 = *param_2 & 3 | 0x84;
  sVar1 = RTMPCalcDuration(param_1,0,0x14);
  *(short *)(param_2 + 2) = sVar1 + 0x10;
  *(undefined4 *)(param_2 + 4) = *param_3;
  *(undefined2 *)(param_2 + 8) = *(undefined2 *)(param_3 + 1);
  *(undefined4 *)(param_2 + 10) = *param_4;
  *(undefined2 *)(param_2 + 0xe) = *(undefined2 *)(param_4 + 1);
  return;
}

