// module: mt7915.ko
// function: D_SetHoldTime @ 0x9b0f8
// size: 128 bytes
//

undefined4 D_SetHoldTime(undefined4 *param_1,undefined4 param_2)

{
  int iVar1;
  undefined1 local_50 [20];
  undefined4 local_3c;
  
  iVar1 = DebugLevel;
  param_1[0x40b] = param_2;
  if (0 < iVar1) {
    printk("%s(): HoldTime = %u\n","D_SetHoldTime",param_2);
    param_2 = param_1[0x40b];
  }
  local_50[0] = 0xf;
  local_3c = param_2;
  RtmpOSWrielessEventSend(*param_1,1,0x950,0,local_50,0x40);
  return 1;
}

