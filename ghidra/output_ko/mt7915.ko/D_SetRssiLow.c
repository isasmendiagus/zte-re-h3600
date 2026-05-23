// module: mt7915.ko
// function: D_SetRssiLow @ 0x9b380
// size: 124 bytes
//

undefined4 D_SetRssiLow(undefined4 *param_1,undefined4 param_2)

{
  int iVar1;
  undefined1 local_50 [11];
  undefined1 local_45;
  
  iVar1 = DebugLevel;
  *(char *)((int)param_1 + 0x1023) = (char)param_2;
  if (0 < iVar1) {
    printk("%s(): RssiLow = %d\n","D_SetRssiLow",param_2);
  }
  local_50[0] = 0xd;
  local_45 = (char)param_2;
  RtmpOSWrielessEventSend(*param_1,1,0x950,0,local_50,0x40);
  return 1;
}

