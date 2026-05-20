// module: mt7915.ko
// function: pmUpdateBssInfoPM @ 0x1c27f8
// size: 240 bytes
//

void pmUpdateBssInfoPM(undefined4 param_1,int param_2,undefined4 param_3)

{
  undefined2 local_34;
  undefined2 local_32;
  undefined1 local_30;
  undefined1 local_2f;
  undefined1 local_2e;
  undefined1 local_2d;
  undefined1 local_2c;
  undefined1 local_2b;
  undefined1 local_2a;
  byte local_29;
  undefined1 local_28;
  byte local_27;
  undefined1 local_26;
  byte local_25;
  int local_24;
  
  local_30 = *(undefined1 *)(param_2 + 0x44);
  local_2f = *(undefined1 *)(param_2 + 0x45);
  local_2e = *(undefined1 *)(param_2 + 0x46);
  local_2d = *(undefined1 *)(param_2 + 0x47);
  local_29 = *(byte *)(param_2 + 0x58);
  local_34 = 3;
  local_24 = (uint)local_29 << 8;
  local_32 = 0x14;
  local_2b = 0x14;
  local_2c = 5;
  local_2a = 0xf;
  local_28 = 0x1f;
  local_26 = 0x3f;
  local_27 = local_29;
  local_25 = local_29;
  if (2 < DebugLevel) {
    printk("%s(BSS_INFO_PM), ucKeepAliveEn = %d, ucKeepAlivePeriod = %d, ucBeaconLossReportEn = %d, ucBeaconLossCount = %d, S0(%d, %d), S1(%d, %d), S2(%d, %d), S3(%d, %d), S4(%d, %d)\n"
           ,"pmUpdateBssInfoPM",local_30,local_2f,local_2e,local_2d,5,0x14,0xf,local_29,0x1f,
           local_29,0x3f,local_29,0,local_29);
  }
  AndesAppendCmdMsg(param_3,&local_34,0x14);
  return;
}

