// module: mt7915.ko
// function: SetMuraMobilityThresholdCtrlProc @ 0x96a34
// size: 772 bytes
//

undefined4 SetMuraMobilityThresholdCtrlProc(int param_1,char *param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  size_t sVar3;
  int iVar4;
  uint uVar5;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  uVar5 = *(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_30 = 0;
  local_34 = 0x10;
  if (uVar5 != 0x7626 && (uVar5 != 0x7663 && uVar5 != 0x7615)) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s: Not Supported (Ret = %d_\n","SetMuraMobilityThresholdCtrlProc",0);
    return 0;
  }
  if (param_2 == (char *)0x0) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s(): No parameters!!\n","SetMuraMobilityThresholdCtrlProc");
  }
  else {
    sVar3 = strlen(param_2);
    if (sVar3 == 6) {
      iVar4 = rstrtok(param_2,&_LC78);
      if (iVar4 == 0) {
        uVar2 = 0;
        uVar1 = 0;
      }
      else {
        uVar1 = simple_strtol(iVar4,0,10);
        iVar4 = rstrtok(0,&_LC78);
        if (iVar4 == 0) {
          uVar2 = 0;
        }
        else {
          uVar2 = simple_strtol(iVar4,0,10);
          iVar4 = rstrtok(0,&_LC78);
          if (iVar4 != 0) {
            if (DebugLevel < 0) {
              return 0;
            }
            printk("%s(): Number of parameters exceed expectation !!\n",
                   "SetMuraMobilityThresholdCtrlProc");
            goto LAB_00096b08;
          }
        }
      }
      if (0 < DebugLevel) {
        printk("%s(): ucWlanId: %d, ucMobilityThreshold: %d\n","SetMuraMobilityThresholdCtrlProc",
               uVar1,uVar2);
      }
      iVar4 = AndesAllocCmdMsg(param_1,8);
      if (iVar4 == 0) {
        if (DebugLevel < 1) {
          return 0;
        }
        printk("%s(): command message memory allocated fail!!\n","SetMuraMobilityThresholdCtrlProc")
        ;
        return 0;
      }
      local_2c = CONCAT13(0x55,CONCAT12(0xed,(undefined2)local_2c));
      local_28 = CONCAT31(local_28._1_3_,10);
      local_30._0_2_ = CONCAT11(uVar2,uVar1);
      AndesInitCmdMsg(iVar4,local_2c,local_28,local_24,local_20,local_1c);
      AndesAppendCmdMsg(iVar4,&local_34,4);
      AndesAppendCmdMsg(iVar4,&local_30,4);
      chip_cmd_tx(param_1,iVar4);
      return 1;
    }
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s(): Wrong parameter format!!\n","SetMuraMobilityThresholdCtrlProc");
  }
LAB_00096b08:
  if ((((0 < DebugLevel) && (printk("Expected format is as below:\n\n"), 0 < DebugLevel)) &&
      (printk("\tiwpriv <interface> set mura_mobility_threshold_ctrl=OOO:OO\n\n"), 0 < DebugLevel))
     && (printk("\tparam1: WlanId (0~127)\n"), 0 < DebugLevel)) {
    printk("\tparam2: Mobility LQ Threshold (0~63)\n");
  }
  return 0;
}

