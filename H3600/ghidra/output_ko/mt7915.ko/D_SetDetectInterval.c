// module: mt7915.ko
// function: D_SetDetectInterval @ 0x9b280
// size: 124 bytes
//

undefined4 D_SetDetectInterval(undefined4 *param_1,undefined4 param_2)

{
  int iVar1;
  undefined1 local_50 [48];
  undefined4 local_20;
  
  iVar1 = DebugLevel;
  param_1[0x422] = param_2;
  if (0 < iVar1) {
    printk("%s(): ulSteeringDetectInterval = %u\n","D_SetDetectInterval",param_2);
  }
  local_50[0] = 0x20;
  local_20 = param_2;
  RtmpOSWrielessEventSend(*param_1,1,0x950,0,local_50,0x40);
  return 1;
}

