// module: mt7915.ko
// function: hqa_log_on_off @ 0x24a074
// size: 184 bytes
//

/* WARNING: Type propagation algorithm not settling */

undefined4 hqa_log_on_off(int param_1,int param_2)

{
  undefined4 uVar1;
  int local_24 [6];
  
  local_24[0] = param_2 + 0xc;
  local_24[1] = 0;
  local_24[2] = 0;
  local_24[3] = 0;
  local_24[4] = 0;
  FUN_002474f4(1,4,local_24,local_24 + 1);
  FUN_002474f4(1,4,local_24,local_24 + 2);
  FUN_002474f4(1,4,local_24,local_24 + 3);
  FUN_002474f4(1,4,local_24,local_24 + 4);
  *(char *)(param_1 + 0x4cc) = (char)local_24[1];
  uVar1 = mt_serv_log_on_off(param_1,local_24[2],local_24[3],local_24[4]);
  FUN_00246b90(param_2,2,uVar1);
  return uVar1;
}

