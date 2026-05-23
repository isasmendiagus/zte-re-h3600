// module: mt7915.ko
// function: HW_ADD_REPT_ENTRY @ 0xb1a10
// size: 88 bytes
//

void HW_ADD_REPT_ENTRY(undefined4 param_1,undefined4 param_2,void *param_3)

{
  undefined4 local_24;
  undefined1 auStack_20 [12];
  
  os_zero_mem(&local_24,0xc);
  local_24 = param_2;
  os_move_mem(auStack_20,param_3,6);
  FUN_000b0a74(param_1,0,0x27,0xc,&local_24);
  return;
}

