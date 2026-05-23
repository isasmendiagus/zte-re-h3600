// module: mt7915.ko
// function: HW_SET_DEL_ASIC_WCID @ 0xb11b4
// size: 44 bytes
//

void HW_SET_DEL_ASIC_WCID(undefined4 param_1,undefined4 param_2)

{
  undefined4 local_28 [9];
  
  local_28[0] = param_2;
  FUN_000b0a74(param_1,3,7,0x20,local_28);
  return;
}

