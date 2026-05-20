// module: mt7915.ko
// function: twt_get_current_tsf @ 0x167940
// size: 68 bytes
//

void twt_get_current_tsf(int param_1,undefined4 *param_2)

{
  undefined4 local_10;
  undefined4 local_c;
  
  local_10 = 0;
  local_c = 0;
  AsicGetTsfTime(*(undefined4 *)(param_1 + 8),&local_10,&local_c,*(undefined1 *)(param_1 + 0x29));
  *param_2 = local_c;
  param_2[1] = local_10;
  return;
}

