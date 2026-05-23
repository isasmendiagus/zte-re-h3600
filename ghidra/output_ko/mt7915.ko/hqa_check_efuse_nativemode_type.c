// module: mt7915.ko
// function: hqa_check_efuse_nativemode_type @ 0x246ce8
// size: 76 bytes
//

undefined4 hqa_check_efuse_nativemode_type(int *param_1,int param_2)

{
  int local_c;
  
  local_c = (uint)*(byte *)(*param_1 + 0x76) << 0x18;
  sys_ad_move_mem((void *)(param_2 + 0xe),&local_c,4);
  FUN_00246b90(param_2,6,0);
  return 0;
}

