// module: mt7915.ko
// function: vow_mbss_grp_band_map @ 0x42bdc
// size: 132 bytes
//

void vow_mbss_grp_band_map(int param_1,int param_2)

{
  undefined4 uVar1;
  uint uVar2;
  
  if (param_2 == 0) {
    return;
  }
  uVar1 = HcGetBandByWdev(param_2);
  uVar2 = (uint)*(byte *)(param_1 + (uint)*(byte *)(param_2 + 0xe) + 0xa7bea8);
  if (*(byte *)(param_1 + 0xa797a4) < 3) {
    FUN_0004049c(param_1,uVar1,uVar2);
  }
  *(char *)(param_1 + uVar2 * 0x1c + 0xa79840) = (char)uVar1;
  vow_set_at_estimator_group(param_1,4,uVar2);
  return;
}

