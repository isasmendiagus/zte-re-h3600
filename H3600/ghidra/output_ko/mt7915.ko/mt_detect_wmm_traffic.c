// module: mt7915.ko
// function: mt_detect_wmm_traffic @ 0xc7edc
// size: 52 bytes
//

void mt_detect_wmm_traffic(int param_1,undefined4 param_2,int param_3,int param_4)

{
  if (param_3 != 0 && param_3 != 3) {
    if (param_4 == 1) {
      *(int *)(param_1 + 0xa77c2c) = *(int *)(param_1 + 0xa77c2c) + 1;
    }
    else {
      *(int *)(param_1 + 0xa77c30) = *(int *)(param_1 + 0xa77c30) + 1;
    }
    return;
  }
  return;
}

