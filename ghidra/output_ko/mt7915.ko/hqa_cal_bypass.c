// module: mt7915.ko
// function: hqa_cal_bypass @ 0x24bfc4
// size: 128 bytes
//

undefined4 hqa_cal_bypass(int param_1,int param_2)

{
  undefined4 uVar1;
  int local_1c;
  undefined4 local_18;
  undefined4 local_14 [2];
  
  local_1c = param_2 + 0xc;
  local_18 = 0;
  local_14[0] = 0;
  FUN_002474f4(1,4,&local_1c,&local_18);
  FUN_002474f4(1,4,&local_1c,local_14);
  *(char *)(param_1 + 0x4cc) = (char)local_14[0];
  uVar1 = mt_serv_set_cal_bypass(param_1,local_18);
  FUN_00246b90(param_2,2,uVar1);
  return uVar1;
}

