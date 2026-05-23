// module: mt7915.ko
// function: D_SetChannelUtilization @ 0x9b200
// size: 124 bytes
//

undefined4 D_SetChannelUtilization(undefined4 *param_1,undefined4 param_2)

{
  int iVar1;
  undefined1 local_50 [52];
  undefined1 local_1c;
  
  iVar1 = DebugLevel;
  *(char *)((int)param_1 + 0x1025) = (char)param_2;
  if (0 < iVar1) {
    printk("%s(): ucChanUtilThreshold = %u\n","D_SetChannelUtilization",param_2);
  }
  local_50[0] = 0x1f;
  local_1c = (char)param_2;
  RtmpOSWrielessEventSend(*param_1,1,0x950,0,local_50,0x40);
  return 1;
}

