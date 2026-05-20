// module: mt7915.ko
// function: HW_SET_PBC_CTRL @ 0xb1b4c
// size: 52 bytes
//

void HW_SET_PBC_CTRL(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined1 param_4)

{
  undefined4 local_14;
  undefined4 local_10;
  undefined1 local_c;
  
  local_14 = param_2;
  local_10 = param_3;
  local_c = param_4;
  FUN_000b0a74(param_1,6,0x33,0xc,&local_14);
  return;
}

