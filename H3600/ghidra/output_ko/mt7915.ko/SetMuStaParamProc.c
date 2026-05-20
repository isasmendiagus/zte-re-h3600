// module: mt7915.ko
// function: SetMuStaParamProc @ 0x8a718
// size: 524 bytes
//

undefined4 SetMuStaParamProc(undefined4 param_1,char *param_2)

{
  char *pcVar1;
  char *pcVar2;
  char *pcVar3;
  char *pcVar4;
  char *pcVar5;
  char *pcVar6;
  int iVar7;
  undefined4 uVar8;
  char *local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  
  local_54 = 0;
  local_50 = 0;
  local_4c = 0;
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_58 = 0x32;
  local_5c = param_2;
  pcVar1 = strsep(&local_5c,"_");
  if ((((pcVar1 != (char *)0x0) && (pcVar2 = strsep(&local_5c,"_"), pcVar2 != (char *)0x0)) &&
      (pcVar3 = strsep(&local_5c,"_"), pcVar3 != (char *)0x0)) &&
     (((pcVar4 = strsep(&local_5c,"_"), pcVar4 != (char *)0x0 &&
       (pcVar5 = strsep(&local_5c,"_"), pcVar5 != (char *)0x0)) &&
      (pcVar6 = strsep(&local_5c,""), pcVar6 != (char *)0x0)))) {
    local_40 = os_str_tol(pcVar1,0,0x10);
    local_3c = os_str_tol(pcVar2,0,0x10);
    local_38 = os_str_tol(pcVar3,0,0x10);
    local_34 = os_str_tol(pcVar4,0,0x10);
    local_30 = os_str_tol(pcVar5,0,0x10);
    local_2c = os_str_tol(pcVar6,0,0x10);
    iVar7 = AndesAllocCmdMsg(param_1,0x1c);
    if (iVar7 != 0) {
      uVar8 = 1;
      local_54 = CONCAT13(0x40,CONCAT12(0xed,(undefined2)local_54));
      local_50 = CONCAT31(local_50._1_3_,10);
      AndesInitCmdMsg(iVar7,local_54,local_50,local_4c,local_48,local_44);
      AndesAppendCmdMsg(iVar7,&local_58,4);
      AndesAppendCmdMsg(iVar7,&local_40,0x18);
      AndesSendCmdMsg(param_1,iVar7);
      goto LAB_0008a8e8;
    }
  }
  uVar8 = 0;
LAB_0008a8e8:
  if (-1 < DebugLevel) {
    printk("%s:(Ret = %d_\n","SetMuStaParamProc",uVar8);
  }
  return uVar8;
}

