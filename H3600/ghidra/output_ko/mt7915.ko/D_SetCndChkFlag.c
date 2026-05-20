// module: mt7915.ko
// function: D_SetCndChkFlag @ 0x9aff4
// size: 124 bytes
//

undefined4 D_SetCndChkFlag(undefined4 *param_1,undefined4 param_2)

{
  int iVar1;
  undefined1 local_48 [24];
  undefined4 local_30;
  
  iVar1 = DebugLevel;
  param_1[4] = param_2;
  if (2 < iVar1) {
    printk("%s(): CndChkFlag = 0x%x\n","D_SetCndChkFlag",param_2);
    param_2 = param_1[4];
  }
  local_48[0] = 0x12;
  local_30 = param_2;
  RtmpOSWrielessEventSend(*param_1,1,0x950,0,local_48,0x40);
  return 1;
}

