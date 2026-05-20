// module: mt7915.ko
// function: hqa_check_efuse_mode @ 0x246d80
// size: 84 bytes
//

undefined4 hqa_check_efuse_mode(int *param_1,int param_2)

{
  undefined4 local_c;
  
  if (*(char *)(*param_1 + 0x74) == '\0') {
    local_c = 0;
  }
  else {
    local_c = 0x1000000;
  }
  sys_ad_move_mem((void *)(param_2 + 0xe),&local_c,4);
  FUN_00246b90(param_2,6,0);
  return 0;
}

