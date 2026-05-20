// module: mt7915.ko
// function: GetMuraMonitorStateProc @ 0x95220
// size: 836 bytes
//

undefined1 GetMuraMonitorStateProc(int param_1,char *param_2)

{
  char *pcVar1;
  int iVar2;
  uint *puVar3;
  uint uVar4;
  undefined1 uVar5;
  uint uVar6;
  char *local_3bc [2];
  uint local_3b4;
  uint local_3b0;
  undefined4 local_3ac;
  undefined4 local_3a8;
  undefined4 local_3a4;
  uint *local_3a0;
  code *local_39c;
  uint local_398;
  uint local_394;
  uint local_390;
  uint local_38c;
  uint local_388;
  uint local_384;
  uint local_380;
  uint local_37c;
  uint local_378;
  uint local_374;
  uint local_370;
  
  uVar4 = *(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff;
  local_3b4 = 0;
  local_3ac = 0;
  uVar6 = (uint)(uVar4 != 0x7663 && uVar4 != 0x7615);
  if (uVar4 == 0x7626) {
    uVar6 = 0;
  }
  local_3a8 = 0;
  local_3a4 = 0;
  local_3b0 = 1;
  local_3bc[0] = param_2;
  if (uVar6 != 0) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s: Not Supported (Ret = %d_\n","GetMuraMonitorStateProc",0);
    return 0;
  }
  if (param_2 != (char *)0x0) {
    uVar4 = os_str_tol(param_2,0,10);
    if (uVar4 != 1) {
      if (uVar4 == 2) {
        local_3b0 = uVar4;
        local_398 = uVar6;
        local_394 = uVar6;
        local_390 = uVar6;
        local_38c = uVar6;
        local_388 = uVar6;
        local_384 = uVar6;
        local_380 = uVar6;
        local_37c = uVar6;
        local_378 = uVar6;
        local_374 = uVar6;
        local_370 = uVar6;
        pcVar1 = strsep(local_3bc,"-");
        if ((((pcVar1 == (char *)0x0) || (pcVar1 = strsep(local_3bc,""), pcVar1 == (char *)0x0)) ||
            (local_3b4 = os_str_tol(pcVar1,0,10), 0x43 < local_3b4)) ||
           (iVar2 = AndesAllocCmdMsg(param_1,0x30), iVar2 == 0)) goto LAB_00095358;
        local_3a0 = &local_398;
        local_39c = MuraEventDispatcher;
        local_3a8 = CONCAT22(0x2c,(undefined2)local_3a8);
        local_3ac._0_3_ = CONCAT12(0xed,(undefined2)local_3ac);
        local_3ac = CONCAT13(0x55,(undefined3)local_3ac);
        local_3a8 = CONCAT31(local_3a8._1_3_,5);
        AndesInitCmdMsg(iVar2,local_3ac,local_3a8,local_3a4,local_3a0,MuraEventDispatcher);
        AndesAppendCmdMsg(iVar2,&local_3b0,4);
        puVar3 = &local_3b4;
      }
      else {
        if (uVar4 != 3) {
          uVar5 = 1;
          goto LAB_000952e0;
        }
        memset(&local_398,0,100);
        local_3b0 = uVar4;
        iVar2 = AndesAllocCmdMsg(param_1,0x68);
        if (iVar2 == 0) goto LAB_00095358;
        local_3a0 = &local_398;
        local_39c = MuraEventDispatcher;
        local_3a8 = CONCAT22(100,(undefined2)local_3a8);
        local_3ac._0_3_ = CONCAT12(0xed,(undefined2)local_3ac);
        local_3ac = CONCAT13(0x55,(undefined3)local_3ac);
        local_3a8 = CONCAT31(local_3a8._1_3_,5);
        AndesInitCmdMsg(iVar2,local_3ac,local_3a8,local_3a4,local_3a0,MuraEventDispatcher);
        puVar3 = &local_3b0;
      }
      uVar5 = 1;
      AndesAppendCmdMsg(iVar2,puVar3,4);
      AndesSendCmdMsg(param_1,iVar2);
      goto LAB_000952e0;
    }
    memset(&local_398,0,0x380);
    iVar2 = AndesAllocCmdMsg(param_1,900);
    if (iVar2 != 0) {
      local_3a0 = &local_398;
      local_39c = MuraEventDispatcher;
      local_3a8 = CONCAT22(0x380,(undefined2)local_3a8);
      local_3ac._0_3_ = CONCAT12(0xed,(undefined2)local_3ac);
      local_3ac = CONCAT13(0x55,(undefined3)local_3ac);
      local_3a8 = CONCAT31(local_3a8._1_3_,5);
      AndesInitCmdMsg(iVar2,local_3ac,local_3a8,local_3a4,local_3a0,MuraEventDispatcher);
      AndesAppendCmdMsg(iVar2,&local_3b0,4);
      AndesSendCmdMsg(param_1,iVar2);
      uVar5 = 1;
      goto LAB_000952e0;
    }
  }
LAB_00095358:
  uVar5 = 0;
LAB_000952e0:
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d_\n","GetMuraMonitorStateProc",uVar5);
  }
  return uVar5;
}

