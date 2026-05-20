// module: mt7915.ko
// function: RTMP_GET_TEMPERATURE @ 0xb0e58
// size: 192 bytes
//

void RTMP_GET_TEMPERATURE(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined1 local_49;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined1 *local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  
  local_49 = (undefined1)param_2;
  os_zero_mem(&local_48,0x28);
  if (2 < DebugLevel) {
    printk("%s::uBandIdx:%d, ucDbdcIdx:%d\n","RTMP_GET_TEMPERATURE",local_49,param_2);
  }
  local_3c = 0;
  local_38 = &local_49;
  local_34 = 1;
  local_28 = 0;
  local_24 = 0;
  local_2c = 4;
  local_48 = 0;
  local_40 = CONCAT31(local_40._1_3_,1);
  local_44 = 0x10;
  local_30 = param_3;
  HwCtrlEnqueueCmd(param_1,0,0x10,local_40,0,local_38,1,param_3,4,0,0);
  return;
}

