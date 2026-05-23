// module: mt7915.ko
// function: HW_SET_RTS_THLD @ 0xb1b80
// size: 52 bytes
//

void HW_SET_RTS_THLD(undefined4 param_1,undefined4 param_2,undefined1 param_3,undefined4 param_4)

{
  undefined4 local_14;
  undefined1 local_10;
  undefined4 local_c;
  
  local_14 = param_2;
  local_10 = param_3;
  local_c = param_4;
  FUN_000b0a74(param_1,7,0x37,0xc,&local_14);
  return;
}

