// module: mt7915.ko
// function: MtCmdRfTestSetTTG @ 0x1ae860
// size: 244 bytes
//

void MtCmdRfTestSetTTG(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined1 param_4,
                      undefined1 param_5,byte param_6)

{
  uint local_d8 [19];
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined1 local_70;
  byte local_6f;
  undefined1 local_6e;
  
  os_zero_mem(&local_80,0x58);
  local_6e = param_5;
  local_6f = param_6;
  local_80 = CONCAT31(local_80._1_3_,1);
  local_7c = 0xf;
  local_78 = param_2;
  local_74 = param_3;
  local_70 = param_4;
  if (2 < DebugLevel) {
    printk("%s: <SetTTG> Structure parser Checking Log\n","MtCmdRfTestSetTTG");
    if ((2 < DebugLevel) &&
       (printk("--------------------------------------------------------------\n"), 2 < DebugLevel))
    {
      local_d8[0] = (uint)local_6f;
      printk("ChannelFreq = %d, ToneFreq = %d, TTGPwrIdx = %d, DbdcIdx= %d\n",param_2,param_3,
             local_70);
    }
  }
  local_8c = 0;
  local_88 = 8;
  memcpy(local_d8,&local_74,0x4c);
  FUN_001abb34(param_1,local_80,local_7c,local_78);
  return;
}

