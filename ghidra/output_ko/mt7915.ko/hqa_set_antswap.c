// module: mt7915.ko
// function: hqa_set_antswap @ 0x24c044
// size: 112 bytes
//

undefined4 hqa_set_antswap(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  int local_1c;
  undefined1 auStack_18 [4];
  undefined4 local_14;
  
  local_1c = param_2 + 0xc;
  FUN_002474f4(1,4,&local_1c,auStack_18);
  FUN_002474f4(1,4,&local_1c,&local_14);
  uVar1 = mt_serv_set_antswap(param_1,local_14);
  FUN_00246b90(param_2,2,uVar1);
  return uVar1;
}

