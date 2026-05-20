// module: mt7915.ko
// function: MtCmdRfTestSwitchMode @ 0x1ad334
// size: 108 bytes
//

void MtCmdRfTestSwitchMode(undefined4 param_1,int param_2,undefined1 param_3,undefined4 param_4)

{
  undefined1 auStack_c8 [76];
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_70;
  int local_6c;
  undefined4 uStack_68;
  undefined1 auStack_64 [76];
  
  os_zero_mem(&local_70,0x58);
  if (param_2 == 3) {
    local_70 = (uint)CONCAT21(local_70._2_2_,param_3) << 8;
  }
  local_70 = local_70 & 0xffffff00;
  local_7c = 0;
  local_78 = param_4;
  local_6c = param_2;
  memcpy(auStack_c8,auStack_64,0x4c);
  FUN_001abb34(param_1,local_70,local_6c,uStack_68);
  return;
}

