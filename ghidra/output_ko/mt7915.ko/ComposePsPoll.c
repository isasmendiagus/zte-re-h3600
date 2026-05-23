// module: mt7915.ko
// function: ComposePsPoll @ 0x19b4c4
// size: 108 bytes
//

void ComposePsPoll(undefined4 param_1,byte *param_2,int param_3,undefined4 *param_4,
                  undefined4 *param_5)

{
  __memzero(param_2,0x10,param_3,param_4,param_4);
  *(ushort *)(param_2 + 2) = ~((ushort)~(ushort)((uint)(param_3 << 0x12) >> 0x10) >> 2);
  *param_2 = *param_2 & 3 | 0xa4;
  *(undefined4 *)(param_2 + 4) = *param_4;
  *(undefined2 *)(param_2 + 8) = *(undefined2 *)(param_4 + 1);
  *(undefined4 *)(param_2 + 10) = *param_5;
  *(undefined2 *)(param_2 + 0xe) = *(undefined2 *)(param_5 + 1);
  return;
}

