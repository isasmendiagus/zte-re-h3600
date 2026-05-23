// module: mt7915.ko
// function: SetTriggerMuTxProc @ 0x8e764
// size: 628 bytes
//

undefined4 SetTriggerMuTxProc(undefined4 param_1,char *param_2)

{
  undefined1 uVar1;
  char *pcVar2;
  char *pcVar3;
  char *pcVar4;
  char *pcVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined1 *puVar9;
  undefined4 *puVar10;
  char *local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 *local_48;
  undefined4 local_44;
  undefined4 local_40;
  uint local_3c;
  undefined4 local_38;
  undefined4 local_34 [3];
  undefined4 local_28;
  undefined1 uStack_25;
  undefined4 local_24 [2];
  
  uVar7 = 0;
  local_40 = 0;
  local_58 = 0x1f;
  local_3c = 0;
  local_38 = 0;
  local_34[0] = 0;
  local_34[1] = 0;
  local_34[2] = 0;
  local_28 = 0;
  local_24[0] = 0;
  local_54 = 0;
  local_50 = 0;
  local_4c = 0;
  local_44 = 0;
  local_5c = param_2;
  pcVar2 = strsep(&local_5c,"_");
  if ((((pcVar2 != (char *)0x0) && (pcVar3 = strsep(&local_5c,"_"), pcVar3 != (char *)0x0)) &&
      (pcVar4 = strsep(&local_5c,"_"), pcVar4 != (char *)0x0)) &&
     (pcVar5 = strsep(&local_5c,"_"), pcVar5 != (char *)0x0)) {
    uVar1 = os_str_tol(pcVar2,0,10);
    local_40 = CONCAT31(local_40._1_3_,uVar1);
    uVar1 = os_str_tol(pcVar3,0,10);
    local_40._0_2_ = CONCAT11(uVar1,(undefined1)local_40);
    local_3c = os_str_tol(pcVar4,0,10);
    local_38 = os_str_tol(pcVar5,0,10);
    if (local_3c != 0) {
      puVar9 = &uStack_25;
      do {
        uVar7 = uVar7 + 1;
        pcVar2 = strsep(&local_5c,"_");
        if (pcVar2 == (char *)0x0) goto LAB_0008e8ac;
        uVar1 = os_str_tol(pcVar2,0,10);
        puVar9 = puVar9 + 1;
        *puVar9 = uVar1;
      } while (uVar7 < local_3c);
      if (local_3c != 0) {
        puVar10 = &local_38;
        uVar7 = 0;
        do {
          pcVar2 = "_";
          if (local_3c - 1 == uVar7) {
            pcVar2 = "";
          }
          uVar7 = uVar7 + 1;
          pcVar2 = strsep(&local_5c,pcVar2);
          if (pcVar2 == (char *)0x0) goto LAB_0008e8ac;
          uVar8 = os_str_tol(pcVar2,0,10);
          puVar10 = puVar10 + 1;
          *puVar10 = uVar8;
        } while (uVar7 < local_3c);
      }
    }
    iVar6 = AndesAllocCmdMsg(param_1,0x24);
    if (iVar6 != 0) {
      local_50 = CONCAT22(0x20,(undefined2)local_50);
      uVar8 = 1;
      local_54 = CONCAT13(0x40,CONCAT12(0xed,(undefined2)local_54));
      local_50 = CONCAT31(local_50._1_3_,10);
      local_48 = &local_40;
      AndesInitCmdMsg(iVar6,local_54,local_50,local_4c,&local_40,local_44);
      AndesAppendCmdMsg(iVar6,&local_58,4);
      AndesAppendCmdMsg(iVar6,&local_40,0x20);
      AndesSendCmdMsg(param_1,iVar6);
      goto LAB_0008e8b0;
    }
  }
LAB_0008e8ac:
  uVar8 = 0;
LAB_0008e8b0:
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d\n","SetTriggerMuTxProc",uVar8);
  }
  return uVar8;
}

