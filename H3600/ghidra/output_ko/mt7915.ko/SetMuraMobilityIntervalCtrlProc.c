// module: mt7915.ko
// function: SetMuraMobilityIntervalCtrlProc @ 0x964d8
// size: 676 bytes
//

undefined4 SetMuraMobilityIntervalCtrlProc(int param_1,char *param_2)

{
  size_t sVar1;
  int iVar2;
  uint uVar3;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  uVar3 = *(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_30 = 0;
  local_34 = 0xe;
  if (uVar3 != 0x7626 && (uVar3 != 0x7663 && uVar3 != 0x7615)) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s: Not Supported (Ret = %d_\n","SetMuraMobilityIntervalCtrlProc",0);
    return 0;
  }
  if (param_2 == (char *)0x0) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s(): No parameters!!\n","SetMuraMobilityIntervalCtrlProc");
  }
  else {
    sVar1 = strlen(param_2);
    if (sVar1 == 1) {
      iVar2 = rstrtok(param_2,&_LC78);
      if (iVar2 != 0) {
        simple_strtol(iVar2,0,10);
        iVar2 = rstrtok(0,&_LC78);
        if (iVar2 != 0) {
          if (DebugLevel < 0) {
            return 0;
          }
          printk("%s(): Number of parameters exceed expectation !!\n",
                 "SetMuraMobilityIntervalCtrlProc");
          goto LAB_0009661c;
        }
      }
      if (0 < DebugLevel) {
        printk("%s(): u2MobilityInteral: %d\n","SetMuraMobilityIntervalCtrlProc");
      }
      iVar2 = AndesAllocCmdMsg(param_1,8);
      if (iVar2 == 0) {
        if (DebugLevel < 1) {
          return 0;
        }
        printk("%s(): command message memory allocated fail!!\n","SetMuraMobilityIntervalCtrlProc");
        return 0;
      }
      local_2c = CONCAT13(0x55,CONCAT12(0xed,(undefined2)local_2c));
      local_28 = CONCAT31(local_28._1_3_,10);
      AndesInitCmdMsg(iVar2,local_2c,local_28,local_24,local_20,local_1c);
      AndesAppendCmdMsg(iVar2,&local_34,4);
      AndesAppendCmdMsg(iVar2,&local_30,4);
      chip_cmd_tx(param_1,iVar2);
      return 1;
    }
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s(): Wrong parameter format!!\n","SetMuraMobilityIntervalCtrlProc");
  }
LAB_0009661c:
  if (((0 < DebugLevel) && (printk("Expected format is as below:\n\n"), 0 < DebugLevel)) &&
     (printk("   iwpriv <interface> set mura_mobility_interval_ctrl=O\n\n"), 0 < DebugLevel)) {
    printk("   param1: Mobility Computation Profile Time Interval (180, 360)\n");
  }
  return 0;
}

