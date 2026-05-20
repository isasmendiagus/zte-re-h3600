// module: mt7915.ko
// function: SetMuruHeSndCtrl @ 0x239760
// size: 588 bytes
//

undefined4 SetMuruHeSndCtrl(undefined4 param_1,char *param_2)

{
  undefined1 uVar1;
  undefined2 uVar2;
  char *pcVar3;
  int iVar4;
  undefined4 uVar5;
  char *local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_34 = 0;
  local_30 = 0;
  local_38 = 0xc;
  local_3c = param_2;
  if (0 < DebugLevel) {
    printk(&_LC39,"SetMuruHeSndCtrl");
  }
  pcVar3 = strsep(&local_3c,"-");
  if (pcVar3 != (char *)0x0) {
    uVar1 = os_str_tol(pcVar3,0,10);
    local_30._0_2_ = CONCAT11(uVar1,(undefined1)local_30);
    if (0 < DebugLevel) {
      printk("%s:(param.ucTriggerFlow = %u\n","SetMuruHeSndCtrl",uVar1);
    }
    pcVar3 = strsep(&local_3c,"-");
    if (pcVar3 != (char *)0x0) {
      uVar1 = os_str_tol(pcVar3,0,10);
      local_30 = CONCAT31(local_30._1_3_,uVar1);
      if (0 < DebugLevel) {
        printk("%s:(param.ucInterval = %u\n","SetMuruHeSndCtrl",uVar1);
      }
      pcVar3 = strsep(&local_3c,"-");
      if (pcVar3 != (char *)0x0) {
        uVar2 = os_str_tol(pcVar3,0,10);
        local_30 = CONCAT22(uVar2,(undefined2)local_30);
        if (0 < DebugLevel) {
          printk("%s:(param.ucBrRuAlloc = %u\n","SetMuruHeSndCtrl",uVar2);
        }
        pcVar3 = strsep(&local_3c,"-");
        if (pcVar3 != (char *)0x0) {
          local_34 = os_str_tol(pcVar3,0,10);
          if (0 < DebugLevel) {
            printk("%s:(param.ucPpduDur = %u\n","SetMuruHeSndCtrl",local_34);
          }
          iVar4 = AndesAllocCmdMsg(param_1,0xc);
          if (iVar4 != 0) {
            local_2c = CONCAT13(0x9f,CONCAT12(0xed,(undefined2)local_2c));
            local_28 = CONCAT31(local_28._1_3_,10);
            uVar5 = 1;
            AndesInitCmdMsg(iVar4,local_2c,local_28,local_24,local_20,local_1c);
            AndesAppendCmdMsg(iVar4,&local_38,4);
            AndesAppendCmdMsg(iVar4,&local_34,8);
            AndesSendCmdMsg(param_1,iVar4);
            goto LAB_0023990c;
          }
        }
      }
    }
  }
  uVar5 = 0;
LAB_0023990c:
  if (0 < DebugLevel) {
    printk("%s:(Ret = %d_\n","SetMuruHeSndCtrl",uVar5);
  }
  return uVar5;
}

