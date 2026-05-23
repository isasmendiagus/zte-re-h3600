// module: mt7915.ko
// function: hqa_low_power @ 0x24c0b4
// size: 96 bytes
//

undefined4 hqa_low_power(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  int local_18;
  undefined4 local_14 [2];
  
  local_18 = param_2 + 0xc;
  local_14[0] = 0;
  FUN_002474f4(1,4,&local_18,local_14);
  uVar1 = mt_serv_set_low_power(param_1,local_14[0]);
  FUN_00246b90(param_2,2,uVar1);
  return uVar1;
}

