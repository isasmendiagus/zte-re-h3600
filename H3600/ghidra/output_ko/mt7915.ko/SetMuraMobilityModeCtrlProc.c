// module: mt7915.ko
// function: SetMuraMobilityModeCtrlProc @ 0x96ec0
// size: 860 bytes
//

undefined4 SetMuraMobilityModeCtrlProc(int param_1,char *param_2)

{
  undefined4 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  size_t sVar5;
  int iVar6;
  uint uVar7;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  
  uVar7 = *(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_38 = 0;
  local_3c = 0x12;
  if (uVar7 != 0x7626 && (uVar7 != 0x7663 && uVar7 != 0x7615)) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s: Not Supported (Ret = %d_\n","SetMuraMobilityModeCtrlProc",0);
    return 0;
  }
  if (param_2 == (char *)0x0) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s(): No parameters!!\n","SetMuraMobilityModeCtrlProc");
  }
  else {
    sVar5 = strlen(param_2);
    if (sVar5 == 5) {
      iVar6 = rstrtok(param_2,&_LC78);
      if (iVar6 == 0) {
        uVar3 = 1;
        uVar2 = 1;
        uVar4 = 0;
      }
      else {
        uVar2 = simple_strtol(iVar6,0,10);
        iVar6 = rstrtok(0,&_LC78);
        if (iVar6 == 0) {
          uVar3 = 1;
          uVar4 = 0;
        }
        else {
          uVar3 = simple_strtol(iVar6,0,10);
          iVar6 = rstrtok(0,&_LC78);
          if (iVar6 == 0) {
            uVar4 = 0;
          }
          else {
            uVar4 = simple_strtol(iVar6,0,10);
            iVar6 = rstrtok(0,&_LC78);
            if (iVar6 != 0) {
              if (DebugLevel < 0) {
                return 0;
              }
              printk("%s(): Number of parameters exceed expectation !!\n",
                     "SetMuraMobilityModeCtrlProc");
              goto LAB_00096f94;
            }
          }
        }
      }
      if (0 < DebugLevel) {
        printk("%s(): fgMULQPingPongEn: %d, fgMULQTriggerCalEn: %d, fgMobilityFlagForceEn: %d\n",
               "SetMuraMobilityModeCtrlProc",uVar2,uVar3,uVar4);
      }
      iVar6 = AndesAllocCmdMsg(param_1,8);
      uVar1 = local_38;
      if (iVar6 == 0) {
        if (DebugLevel < 1) {
          return 0;
        }
        printk("%s(): command message memory allocated fail!!\n","SetMuraMobilityModeCtrlProc");
        return 0;
      }
      local_34 = CONCAT13(0x55,CONCAT12(0xed,(undefined2)local_34));
      local_30 = CONCAT31(local_30._1_3_,10);
      local_38._3_1_ = SUB41(uVar1,3);
      local_38._0_3_ = CONCAT12(uVar4,CONCAT11(uVar3,uVar2));
      AndesInitCmdMsg(iVar6,local_34,local_30,local_2c,local_28,local_24);
      AndesAppendCmdMsg(iVar6,&local_3c,4);
      AndesAppendCmdMsg(iVar6,&local_38,4);
      chip_cmd_tx(param_1,iVar6);
      return 1;
    }
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s(): Wrong parameter format!!\n","SetMuraMobilityModeCtrlProc");
  }
LAB_00096f94:
  if ((((0 < DebugLevel) && (printk("Expected format is as below:\n\n"), 0 < DebugLevel)) &&
      (printk("   iwpriv <interface> set mura_mobility_mode_ctrl=O:O:O\n\n"), 0 < DebugLevel)) &&
     ((printk("   param1: Mobility PingPong Mechanism Enable (0, 1)\n"), 0 < DebugLevel &&
      (printk("   param2: Mobility Trigger Computation (0, 1)\n"), 0 < DebugLevel)))) {
    printk("   param3: Mobility Flag Enable Forced Mode (0, 1)\n");
  }
  return 0;
}

