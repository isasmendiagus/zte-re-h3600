// module: mt7915.ko
// function: D_SetRssiDiff @ 0x9b400
// size: 124 bytes
//

undefined4 D_SetRssiDiff(undefined4 *param_1,undefined4 param_2)

{
  int iVar1;
  undefined1 local_50 [10];
  undefined1 local_46;
  
  iVar1 = DebugLevel;
  *(char *)((int)param_1 + 0x1022) = (char)param_2;
  if (0 < iVar1) {
    printk("%s(): RssiCheck = %u\n","D_SetRssiDiff",param_2);
  }
  local_50[0] = 0xc;
  local_46 = (char)param_2;
  RtmpOSWrielessEventSend(*param_1,1,0x950,0,local_50,0x40);
  return 1;
}

