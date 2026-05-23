// module: mt7915.ko
// function: RTMP_SET_UPDATE_RSSI @ 0xb16b4
// size: 120 bytes
//

void RTMP_SET_UPDATE_RSSI(undefined4 param_1)

{
  undefined4 local_38;
  undefined4 local_34;
  uint local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  os_zero_mem(&local_38,0x28);
  local_2c = 0;
  local_24 = 0;
  local_28 = 0;
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  local_38 = 0;
  local_30 = local_30 & 0xffffff00;
  local_34 = 0x22;
  HwCtrlEnqueueCmd(param_1,0,0x22,local_30,0,0,0,0,0,0,0);
  return;
}

