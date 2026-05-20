// module: mt7915.ko
// function: SetMuraMobilityLogCtrlProc @ 0x97220
// size: 692 bytes
//

undefined4 SetMuraMobilityLogCtrlProc(int param_1,char *param_2)

{
  undefined1 uVar1;
  size_t sVar2;
  int iVar3;
  uint uVar4;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  uVar4 = *(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_30 = 0;
  local_34 = 0x13;
  if (uVar4 != 0x7626 && (uVar4 != 0x7663 && uVar4 != 0x7615)) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s: Not Supported (Ret = %d_\n","SetMuraMobilityLogCtrlProc",0);
    return 0;
  }
  if (param_2 == (char *)0x0) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s(): No parameters!!\n","SetMuraMobilityLogCtrlProc");
  }
  else {
    sVar2 = strlen(param_2);
    if (sVar2 == 1) {
      iVar3 = rstrtok(param_2,&_LC78);
      if (iVar3 == 0) {
        uVar1 = 1;
      }
      else {
        uVar1 = simple_strtol(iVar3,0,10);
        iVar3 = rstrtok(0,&_LC78);
        if (iVar3 != 0) {
          if (DebugLevel < 0) {
            return 0;
          }
          printk("%s(): Number of parameters exceed expectation !!\n","SetMuraMobilityLogCtrlProc");
          goto LAB_0009736c;
        }
      }
      if (0 < DebugLevel) {
        printk("%s(): fgMobilityLogEn: %d\n","SetMuraMobilityLogCtrlProc",uVar1);
      }
      iVar3 = AndesAllocCmdMsg(param_1,8);
      if (iVar3 == 0) {
        if (DebugLevel < 1) {
          return 0;
        }
        printk("%s(): command message memory allocated fail!!\n","SetMuraMobilityLogCtrlProc");
        return 0;
      }
      local_2c = CONCAT13(0x55,CONCAT12(0xed,(undefined2)local_2c));
      local_28 = CONCAT31(local_28._1_3_,10);
      local_30 = CONCAT31(local_30._1_3_,uVar1);
      AndesInitCmdMsg(iVar3,local_2c,local_28,local_24,local_20,local_1c);
      AndesAppendCmdMsg(iVar3,&local_34,4);
      AndesAppendCmdMsg(iVar3,&local_30,4);
      chip_cmd_tx(param_1,iVar3);
      return 1;
    }
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s(): Wrong parameter format!!\n","SetMuraMobilityLogCtrlProc");
  }
LAB_0009736c:
  if (((0 < DebugLevel) && (printk("Expected format is as below:\n\n"), 0 < DebugLevel)) &&
     (printk("   iwpriv <interface> set mura_mobility_log_ctrl=O\n\n"), 0 < DebugLevel)) {
    printk("   param1: Mobility Log Enable (0, 1)\n");
  }
  return 0;
}

