// module: mt7915.ko
// function: bssUpdateRA @ 0x1c3cac
// size: 112 bytes
//

void bssUpdateRA(undefined4 param_1,int param_2,undefined4 param_3)

{
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  os_zero_mem(&local_3c,0x2c);
  BssInfoRACommCfgSet(param_2 + 0x6c,&local_3c);
  AndesAppendCmdMsg(param_3,&local_3c,0x2c);
  return;
}

