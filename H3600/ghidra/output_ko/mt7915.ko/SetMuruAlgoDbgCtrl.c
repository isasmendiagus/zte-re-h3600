// module: mt7915.ko
// function: SetMuruAlgoDbgCtrl @ 0x23a1b8
// size: 356 bytes
//

undefined4 SetMuruAlgoDbgCtrl(undefined4 param_1,char *param_2)

{
  undefined1 uVar1;
  undefined2 uVar2;
  char *pcVar3;
  int iVar4;
  undefined4 uVar5;
  char *local_34 [2];
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  local_28 = 0;
  local_2c = 0xf;
  local_34[0] = param_2;
  pcVar3 = strsep(local_34,"-");
  if (pcVar3 != (char *)0x0) {
    uVar1 = os_str_tol(pcVar3,0,10);
    local_28 = CONCAT31(local_28._1_3_,uVar1);
    pcVar3 = strsep(local_34,"-");
    if (pcVar3 != (char *)0x0) {
      uVar1 = os_str_tol(pcVar3,0,10);
      local_28._0_2_ = CONCAT11(uVar1,(undefined1)local_28);
      pcVar3 = strsep(local_34,"-");
      if (pcVar3 != (char *)0x0) {
        uVar2 = os_str_tol(pcVar3,0,10);
        local_28 = CONCAT22(uVar2,(undefined2)local_28);
        iVar4 = AndesAllocCmdMsg(param_1,8);
        if (iVar4 != 0) {
          local_24 = CONCAT13(0x9f,CONCAT12(0xed,(undefined2)local_24));
          local_20 = CONCAT31(local_20._1_3_,10);
          uVar5 = 1;
          AndesInitCmdMsg(iVar4,local_24,local_20,local_1c,local_18,local_14);
          AndesAppendCmdMsg(iVar4,&local_2c,4);
          AndesAppendCmdMsg(iVar4,&local_28,4);
          AndesSendCmdMsg(param_1,iVar4);
          goto LAB_0023a2e4;
        }
      }
    }
  }
  uVar5 = 0;
LAB_0023a2e4:
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d_\n","SetMuruAlgoDbgCtrl",uVar5);
  }
  return uVar5;
}

