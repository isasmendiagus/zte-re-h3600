// module: mt7915.ko
// function: RTMP_SET_STA_DWRR_QUANTUM @ 0xb15a0
// size: 156 bytes
//

void RTMP_SET_STA_DWRR_QUANTUM(undefined4 param_1,undefined1 param_2,undefined1 param_3)

{
  undefined1 local_42;
  undefined1 local_41;
  undefined4 local_40;
  undefined4 local_3c;
  uint local_38;
  undefined4 local_34;
  undefined1 *local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  os_zero_mem(&local_40,0x28);
  os_zero_mem(&local_42,2);
  local_34 = 0;
  local_28 = 0;
  local_2c = 2;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_40 = 0;
  local_38 = local_38 & 0xffffff00;
  local_3c = 0x23;
  local_42 = param_2;
  local_41 = param_3;
  local_30 = &local_42;
  HwCtrlEnqueueCmd(param_1,0,0x23,local_38,0,&local_42,2,0,0,0,0);
  return;
}

