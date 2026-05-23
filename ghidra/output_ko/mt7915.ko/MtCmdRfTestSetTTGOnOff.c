// module: mt7915.ko
// function: MtCmdRfTestSetTTGOnOff @ 0x1ae958
// size: 220 bytes
//

void MtCmdRfTestSetTTGOnOff
               (undefined4 param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4)

{
  undefined1 auStack_d0 [76];
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined1 auStack_6c [80];
  
  os_zero_mem(&local_78,0x58);
  local_70._0_3_ = CONCAT12(param_4,CONCAT11(param_3,param_2));
  local_78 = CONCAT31(local_78._1_3_,1);
  local_74 = 0x10;
  if (2 < DebugLevel) {
    printk("%s: <SetTTGOnOff> Structure parser Checking Log\n","MtCmdRfTestSetTTGOnOff");
    if ((2 < DebugLevel) &&
       (printk("--------------------------------------------------------------\n"), 2 < DebugLevel))
    {
      printk("TTGEnable = %d, DbdcIdx = %d, AntIndex = %d\n",local_70 & 0xff,local_70._1_1_,
             local_70._2_1_);
    }
  }
  local_84 = 0;
  local_80 = 8;
  memcpy(auStack_d0,auStack_6c,0x4c);
  FUN_001abb34(param_1,local_78,local_74,local_70);
  return;
}

