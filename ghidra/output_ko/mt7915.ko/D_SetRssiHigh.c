// module: mt7915.ko
// function: D_SetRssiHigh @ 0x9b300
// size: 124 bytes
//

undefined4 D_SetRssiHigh(undefined4 *param_1,undefined4 param_2)

{
  int iVar1;
  undefined1 local_50 [18];
  undefined1 local_3e;
  
  iVar1 = DebugLevel;
  *(char *)(param_1 + 0x409) = (char)param_2;
  if (0 < iVar1) {
    printk("%s(): RssiHigh = %d\n","D_SetRssiHigh",param_2);
  }
  local_50[0] = 0x1e;
  local_3e = (char)param_2;
  RtmpOSWrielessEventSend(*param_1,1,0x950,0,local_50,0x40);
  return 1;
}

