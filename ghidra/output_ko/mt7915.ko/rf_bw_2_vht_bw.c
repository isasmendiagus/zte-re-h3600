// module: mt7915.ko
// function: rf_bw_2_vht_bw @ 0x203a0c
// size: 48 bytes
//

undefined4 rf_bw_2_vht_bw(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 == 2) {
    return 1;
  }
  if (param_1 == 3) {
    return 2;
  }
  if (param_1 == 6) {
    uVar1 = 3;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

