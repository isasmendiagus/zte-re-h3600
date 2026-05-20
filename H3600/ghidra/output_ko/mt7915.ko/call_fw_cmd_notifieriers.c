// module: mt7915.ko
// function: call_fw_cmd_notifieriers @ 0x1a5864
// size: 148 bytes
//

undefined4 call_fw_cmd_notifieriers(undefined4 param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  int local_24;
  undefined1 auStack_20 [20];
  
  if (param_3 == 0) {
    if (DebugLevel < 0) {
      uVar1 = 0xf000;
    }
    else {
      printk("%s: msg is null (val=0x%x)\n","call_fw_cmd_notifieriers",param_1);
      uVar1 = 0xf000;
    }
  }
  else {
    RTMP_QueryPacketInfo(param_3,auStack_20,&local_34,&local_30);
    local_2c = local_34;
    local_28 = local_30;
    local_24 = param_2;
    uVar1 = mt_notify_call_chain(param_2 + 0xa78620,param_1,&local_2c);
  }
  return uVar1;
}

