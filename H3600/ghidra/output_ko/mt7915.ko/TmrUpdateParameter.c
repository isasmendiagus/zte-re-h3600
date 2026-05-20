// module: mt7915.ko
// function: TmrUpdateParameter @ 0x1d7ee8
// size: 64 bytes
//

undefined4 TmrUpdateParameter(int param_1,int param_2,int param_3)

{
  if (*(int *)("Set_RBIST_Capture_Start" + param_1 + 0x10) != 0) {
    if (param_2 == 0) {
      param_2 = 8;
    }
    *(char *)(*(int *)("Set_RBIST_Capture_Start" + param_1 + 0x10) + 8) = (char)param_2;
    if (param_3 == 0) {
      param_3 = 10;
    }
    *(char *)(*(int *)("Set_RBIST_Capture_Start" + param_1 + 0x10) + 9) = (char)param_3;
    return 1;
  }
  return 0;
}

