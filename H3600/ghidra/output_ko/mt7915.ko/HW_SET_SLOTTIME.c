// module: mt7915.ko
// function: HW_SET_SLOTTIME @ 0xb17e4
// size: 52 bytes
//

void HW_SET_SLOTTIME(undefined4 param_1,undefined1 param_2,undefined1 param_3,undefined4 param_4)

{
  undefined1 local_10;
  undefined1 local_f;
  undefined4 local_c;
  
  local_10 = param_2;
  local_f = param_3;
  local_c = param_4;
  FUN_000b0a74(param_1,0,0x11,8,&local_10);
  return;
}

