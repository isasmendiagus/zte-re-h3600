// module: mt7915.ko
// function: hqa_set_tssi_onoff @ 0x24ac0c
// size: 124 bytes
//

undefined4 hqa_set_tssi_onoff(undefined4 param_1,int param_2)

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
  uVar1 = mt_serv_set_tssi(param_1,local_18,local_14[0]);
  FUN_00246b90(param_2,2,uVar1);
  return uVar1;
}

