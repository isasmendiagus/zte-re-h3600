// module: mt7915.ko
// function: MtCmdRfTestSetADC @ 0x1ae64c
// size: 288 bytes
//

void MtCmdRfTestSetADC(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                      byte param_5,byte param_6,byte param_7,byte param_8)

{
  uint local_e0;
  uint uStack_dc;
  uint uStack_d8;
  uint local_d4;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined1 local_74;
  undefined1 local_73;
  byte local_72;
  byte local_71;
  byte local_70;
  byte local_6f;
  
  local_88 = param_4;
  local_84 = param_3;
  os_zero_mem(&local_80,0x58);
  local_74 = (undefined1)local_84;
  local_73 = (undefined1)local_88;
  local_72 = param_5;
  local_71 = param_6;
  local_70 = param_7;
  local_6f = param_8;
  local_80 = CONCAT31(local_80._1_3_,1);
  local_7c = 0xd;
  local_78 = param_2;
  if (2 < DebugLevel) {
    printk("%s: <SetADC> Structure parser Checking Log\n","MtCmdRfTestSetADC");
    if ((2 < DebugLevel) &&
       (printk("--------------------------------------------------------------\n"), 2 < DebugLevel))
    {
      uStack_dc = (uint)local_71;
      local_e0 = (uint)local_72;
      uStack_d8 = (uint)local_70;
      local_d4 = (uint)local_6f;
      printk("ChannelFreq = %d, AntIndex = %d, BW = %d, SX= %d, DbdcIdx = %d, RunType = %d, FType = %d\n"
             ,param_2,local_74,local_73);
    }
  }
  local_94 = 0;
  local_90 = 8;
  memcpy(&local_e0,&local_74,0x4c);
  FUN_001abb34(param_1,local_80,local_7c,local_78);
  return;
}

