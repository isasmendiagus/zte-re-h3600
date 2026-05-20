// module: mt7915.ko
// function: HW_SET_BCN_OFFLOAD @ 0xb1210
// size: 108 bytes
//

void HW_SET_BCN_OFFLOAD(undefined4 param_1,undefined1 param_2,undefined4 param_3,undefined1 param_4,
                       undefined1 param_5,undefined4 param_6,undefined4 param_7)

{
  undefined1 local_3c [4];
  undefined4 local_38;
  undefined1 local_34;
  undefined1 local_33;
  undefined4 local_30;
  undefined4 local_2c;
  
  os_zero_mem(local_3c,0x14);
  local_33 = param_5;
  local_30 = param_6;
  local_2c = param_7;
  local_3c[0] = param_2;
  local_38 = param_3;
  local_34 = param_4;
  FUN_000b0a74(param_1,0,0x26,0x14,local_3c);
  return;
}

