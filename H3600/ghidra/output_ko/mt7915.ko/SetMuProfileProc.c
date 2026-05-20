// module: mt7915.ko
// function: SetMuProfileProc @ 0x8c410
// size: 456 bytes
//

undefined4 SetMuProfileProc(undefined4 param_1,char *param_2)

{
  undefined1 uVar1;
  byte bVar2;
  char *pcVar3;
  char *pcVar4;
  char *pcVar5;
  char *pcVar6;
  int iVar7;
  undefined4 uVar8;
  char *local_44 [2];
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_3c = 2;
  local_44[0] = param_2;
  if (3 < DebugLevel) {
    printk("%s: arg = %s\n","SetMuProfileProc",param_2);
  }
  pcVar3 = strsep(local_44,"_");
  if ((((pcVar3 != (char *)0x0) && (pcVar4 = strsep(local_44,"_"), pcVar4 != (char *)0x0)) &&
      (pcVar5 = strsep(local_44,"_"), pcVar5 != (char *)0x0)) &&
     (pcVar6 = strsep(local_44,""), pcVar6 != (char *)0x0)) {
    uVar1 = os_str_tol(pcVar3,0,10);
    local_38._0_2_ = CONCAT11(uVar1,(undefined1)local_38);
    uVar1 = os_str_tol(pcVar4,0,10);
    local_38 = CONCAT31(local_38._1_3_,uVar1);
    bVar2 = os_str_tol(pcVar5,0,0x10);
    local_38._0_3_ = CONCAT12(local_38._2_1_ & 0xf0 | bVar2 & 0xf,(undefined2)local_38);
    uVar1 = os_str_tol(pcVar6,0,10);
    local_38 = CONCAT13(uVar1,(undefined3)local_38);
    iVar7 = AndesAllocCmdMsg(param_1,8);
    if (iVar7 != 0) {
      local_34 = CONCAT13(0x40,CONCAT12(0xed,(undefined2)local_34));
      local_30 = CONCAT31(local_30._1_3_,10);
      uVar8 = 1;
      AndesInitCmdMsg(iVar7,local_34,local_30,local_2c,local_28,local_24);
      AndesAppendCmdMsg(iVar7,&local_3c,4);
      AndesAppendCmdMsg(iVar7,&local_38,4);
      AndesSendCmdMsg(param_1,iVar7);
      goto LAB_0008c590;
    }
  }
  uVar8 = 0;
LAB_0008c590:
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d\n","SetMuProfileProc",uVar8);
  }
  return uVar8;
}

