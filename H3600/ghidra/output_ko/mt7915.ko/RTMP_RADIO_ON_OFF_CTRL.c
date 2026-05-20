// module: mt7915.ko
// function: RTMP_RADIO_ON_OFF_CTRL @ 0xb0f1c
// size: 156 bytes
//

void RTMP_RADIO_ON_OFF_CTRL(undefined4 param_1,undefined1 param_2,undefined1 param_3)

{
  undefined2 local_4a;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined2 *local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  
  local_4a = 0;
  os_zero_mem(&local_48,0x28);
  local_30 = 0;
  local_34 = 2;
  local_38 = &local_4a;
  local_3c = 2000;
  local_40 = CONCAT31(local_40._1_3_,1);
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_48 = 0;
  local_44 = 0x32;
  local_4a = CONCAT11(param_3,param_2);
  HwCtrlEnqueueCmd(param_1,0,0x32,local_40,2000,local_38,2,0,0,0,0);
  return;
}

