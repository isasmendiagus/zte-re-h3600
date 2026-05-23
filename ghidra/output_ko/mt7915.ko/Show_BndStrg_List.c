// module: mt7915.ko
// function: Show_BndStrg_List @ 0x9b904
// size: 88 bytes
//

undefined4 Show_BndStrg_List(int param_1)

{
  if (*(int *)(&DAT_0036c93c + param_1) != 0) {
    (**(code **)(*(int *)(&DAT_0036c93c + param_1) + 4))(&DAT_0036b924 + param_1);
  }
  if (*(int *)(&DAT_0036d9d0 + param_1) != 0) {
    (**(code **)(*(int *)(&DAT_0036d9d0 + param_1) + 4))(&DAT_0036c9b8 + param_1);
  }
  return 1;
}

