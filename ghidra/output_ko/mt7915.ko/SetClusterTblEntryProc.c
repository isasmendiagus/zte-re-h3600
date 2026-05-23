// module: mt7915.ko
// function: SetClusterTblEntryProc @ 0x8ceec
// size: 712 bytes
//

undefined4 SetClusterTblEntryProc(undefined4 param_1,char *param_2)

{
  undefined1 uVar1;
  char *pcVar2;
  char *pcVar3;
  char *pcVar4;
  char *pcVar5;
  char *pcVar6;
  char *pcVar7;
  char *pcVar8;
  int iVar9;
  undefined4 uVar10;
  char *local_64 [2];
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  uint local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_58 = 0;
  local_54 = 0;
  local_50 = 0;
  local_4c = 0;
  local_48 = 0;
  local_5c = 6;
  local_64[0] = param_2;
  pcVar2 = strsep(local_64,"_");
  if ((((pcVar2 != (char *)0x0) && (pcVar3 = strsep(local_64,"_"), pcVar3 != (char *)0x0)) &&
      (pcVar4 = strsep(local_64,"_"), pcVar4 != (char *)0x0)) &&
     (((pcVar5 = strsep(local_64,"_"), pcVar5 != (char *)0x0 &&
       (pcVar6 = strsep(local_64,"_"), pcVar6 != (char *)0x0)) &&
      ((pcVar7 = strsep(local_64,"_"), pcVar7 != (char *)0x0 &&
       (pcVar8 = strsep(local_64,""), pcVar8 != (char *)0x0)))))) {
    uVar1 = os_str_tol(pcVar2,0,10);
    local_44 = CONCAT31(local_44._1_3_,uVar1);
    if (3 < DebugLevel) {
      printk(&_LC0,"SetClusterTblEntryProc");
    }
    local_40 = os_str_tol(pcVar3,0,0x10);
    local_3c = os_str_tol(pcVar4,0,0x10);
    local_38 = os_str_tol(pcVar5,0,0x10);
    local_34 = os_str_tol(pcVar6,0,0x10);
    local_30 = os_str_tol(pcVar7,0,0x10);
    local_2c = os_str_tol(pcVar8,0,0x10);
    if (3 < DebugLevel) {
      printk("Values: %d %d %d %d %d %d %d\n",local_44 & 0xff,local_40,local_3c,local_38,local_34,
             local_30,local_2c);
    }
    iVar9 = AndesAllocCmdMsg(param_1,0x20);
    if (iVar9 != 0) {
      local_58 = CONCAT13(0x40,CONCAT12(0xed,(undefined2)local_58));
      local_54 = CONCAT31(local_54._1_3_,10);
      AndesInitCmdMsg(iVar9,local_58,local_54,local_50,local_4c,local_48);
      AndesAppendCmdMsg(iVar9,&local_5c,4);
      AndesAppendCmdMsg(iVar9,&local_44,0x1c);
      AndesSendCmdMsg(param_1,iVar9);
      if (DebugLevel < 4) {
        return 1;
      }
      uVar10 = 1;
      printk("msg is sent\n");
      goto LAB_0008d138;
    }
  }
  uVar10 = 0;
LAB_0008d138:
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d\n","SetClusterTblEntryProc",uVar10);
  }
  return uVar10;
}

