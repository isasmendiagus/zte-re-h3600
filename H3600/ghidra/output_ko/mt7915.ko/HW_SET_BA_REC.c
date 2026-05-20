// module: mt7915.ko
// function: HW_SET_BA_REC @ 0xb12a0
// size: 116 bytes
//

void HW_SET_BA_REC(undefined4 param_1,undefined2 param_2,undefined1 param_3,undefined2 param_4,
                  undefined2 param_5,undefined1 param_6,undefined4 param_7,undefined1 param_8)

{
  undefined2 local_40;
  undefined1 local_3e;
  undefined2 local_3c;
  undefined1 local_3a;
  undefined4 local_38;
  undefined2 local_2e;
  undefined1 local_2c;
  
  os_zero_mem(&local_40,0x18);
  local_3c = param_5;
  local_3a = param_6;
  local_38 = param_7;
  local_2c = param_8;
  local_40 = param_2;
  local_3e = param_3;
  local_2e = param_4;
  FUN_000b0a74(param_1,0,0x1b,0x18,&local_40);
  return;
}

