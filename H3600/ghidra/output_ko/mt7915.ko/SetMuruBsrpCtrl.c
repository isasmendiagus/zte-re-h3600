// module: mt7915.ko
// function: SetMuruBsrpCtrl @ 0x2399b0
// size: 652 bytes
//

undefined4 SetMuruBsrpCtrl(undefined4 param_1,char *param_2)

{
  undefined1 uVar1;
  undefined2 uVar2;
  char *pcVar3;
  int iVar4;
  undefined4 uVar5;
  char *local_44 [2];
  undefined4 local_3c;
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
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_3c = 1;
  local_44[0] = param_2;
  pcVar3 = strsep(local_44,"-");
  if (pcVar3 != (char *)0x0) {
    iVar4 = os_str_tol(pcVar3,0,10);
    local_30._0_2_ = CONCAT11(iVar4 != 0,(undefined1)local_30);
    if (0 < DebugLevel) {
      printk("%s:(param.fgExtCmdBsrp = %u\n","SetMuruBsrpCtrl",iVar4 != 0);
    }
    pcVar3 = strsep(local_44,"-");
    if (pcVar3 != (char *)0x0) {
      uVar1 = os_str_tol(pcVar3,0,10);
      local_30 = CONCAT31(local_30._1_3_,uVar1);
      if (0 < DebugLevel) {
        printk("%s:(param.ucTriggerFlow = %u\n","SetMuruBsrpCtrl",uVar1);
      }
      pcVar3 = strsep(local_44,"-");
      if (pcVar3 != (char *)0x0) {
        uVar2 = os_str_tol(pcVar3,0,10);
        local_38 = CONCAT22(local_38._2_2_,uVar2);
        if (0 < DebugLevel) {
          printk("%s:(param.ucBsrpInterval = %u\n","SetMuruBsrpCtrl",uVar2);
        }
        pcVar3 = strsep(local_44,"-");
        if (pcVar3 != (char *)0x0) {
          uVar2 = os_str_tol(pcVar3,0,10);
          local_38 = CONCAT22(uVar2,(undefined2)local_38);
          if (0 < DebugLevel) {
            printk("%s:(param.ucBsrpRuAlloc = %u\n","SetMuruBsrpCtrl",uVar2);
          }
          pcVar3 = strsep(local_44,"-");
          if (pcVar3 != (char *)0x0) {
            local_34 = os_str_tol(pcVar3,0,10);
            if (0 < DebugLevel) {
              printk("%s:(param.u4PpduDur = %u\n","SetMuruBsrpCtrl",local_34);
            }
            iVar4 = AndesAllocCmdMsg(param_1,0x10);
            if (iVar4 != 0) {
              local_2c = CONCAT13(0x9f,CONCAT12(0xed,(undefined2)local_2c));
              local_28 = CONCAT31(local_28._1_3_,10);
              uVar5 = 1;
              AndesInitCmdMsg(iVar4,local_2c,local_28,local_24,local_20,local_1c);
              AndesAppendCmdMsg(iVar4,&local_3c,4);
              AndesAppendCmdMsg(iVar4,&local_38,0xc);
              AndesSendCmdMsg(param_1,iVar4);
              goto LAB_00239b98;
            }
          }
        }
      }
    }
  }
  uVar5 = 0;
LAB_00239b98:
  if (0 < DebugLevel) {
    printk("%s:(Ret = %d_)\n","SetMuruBsrpCtrl",uVar5);
  }
  return uVar5;
}

