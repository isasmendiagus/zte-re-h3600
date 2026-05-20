// module: mt7915.ko
// function: HW_STA_BF_SOUNDING_ADJUST @ 0xb1c9c
// size: 76 bytes
//

void HW_STA_BF_SOUNDING_ADJUST(undefined4 param_1,undefined1 param_2,undefined4 param_3)

{
  undefined4 local_20;
  undefined1 local_1c;
  
  os_zero_mem(&local_20,8);
  local_20 = param_3;
  local_1c = param_2;
  FUN_000b0a74(param_1,0,0x15,8,&local_20);
  return;
}

