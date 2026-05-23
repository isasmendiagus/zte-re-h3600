// module: mt7915.ko
// function: hqa_tmr_setting @ 0x24a9d0
// size: 156 bytes
//

undefined4 hqa_tmr_setting(int param_1,int param_2)

{
  undefined4 uVar1;
  int local_1c [2];
  
  local_1c[0] = param_2 + 0xc;
  FUN_002474f4(1,4,local_1c,param_1 + 0x1f34);
  FUN_002474f4(1,4,local_1c,param_1 + 0x1f38);
  FUN_002474f4(1,4,local_1c,param_1 + 0x1f3c);
  FUN_002474f4(1,4,local_1c,param_1 + 8000);
  uVar1 = mt_serv_set_tmr(param_1);
  FUN_00246b90(param_2,2,uVar1);
  return uVar1;
}

