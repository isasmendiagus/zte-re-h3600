// module: mt7915.ko
// function: HW_SET_ASIC_WCID_AAD_OM @ 0xb11e0
// size: 48 bytes
//

void HW_SET_ASIC_WCID_AAD_OM(undefined4 param_1,undefined4 param_2,undefined1 param_3)

{
  undefined4 local_10;
  undefined1 local_c;
  
  local_10 = param_2;
  local_c = param_3;
  FUN_000b0a74(param_1,3,8,8,&local_10);
  return;
}

