// module: mt7915.ko
// function: SetTriggerGIDMgmtFrameProc @ 0x8e098
// size: 368 bytes
//

undefined4 SetTriggerGIDMgmtFrameProc(undefined4 param_1,char *param_2)

{
  undefined1 uVar1;
  undefined2 uVar2;
  char *pcVar3;
  char *pcVar4;
  char *pcVar5;
  int iVar6;
  undefined4 uVar7;
  char *local_3c [2];
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  local_30 = 0;
  local_34 = 0x22;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_3c[0] = param_2;
  pcVar3 = strsep(local_3c,"_");
  if (((pcVar3 != (char *)0x0) && (pcVar4 = strsep(local_3c,"_"), pcVar4 != (char *)0x0)) &&
     (pcVar5 = strsep(local_3c,""), pcVar5 != (char *)0x0)) {
    uVar2 = os_str_tol(pcVar3,0,10);
    local_30 = CONCAT22(local_30._2_2_,uVar2);
    uVar1 = os_str_tol(pcVar4,0,10);
    local_30._0_3_ = CONCAT12(uVar1,(undefined2)local_30);
    uVar1 = os_str_tol(pcVar5,0,10);
    local_30 = CONCAT13(uVar1,(undefined3)local_30);
    iVar6 = AndesAllocCmdMsg(param_1,8);
    if (iVar6 != 0) {
      local_2c = CONCAT13(0x40,CONCAT12(0xed,(undefined2)local_2c));
      local_28 = CONCAT31(local_28._1_3_,10);
      uVar7 = 1;
      AndesInitCmdMsg(iVar6,local_2c,local_28,local_24,local_20,local_1c);
      AndesAppendCmdMsg(iVar6,&local_34,4);
      AndesAppendCmdMsg(iVar6,&local_30,4);
      AndesSendCmdMsg(param_1,iVar6);
      goto LAB_0008e1d0;
    }
  }
  uVar7 = 0;
LAB_0008e1d0:
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d\n","SetTriggerGIDMgmtFrameProc",uVar7);
  }
  return uVar7;
}

