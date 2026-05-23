// module: mt7915.ko
// function: SetMuraFixedSndParamProc @ 0x95d34
// size: 544 bytes
//

undefined4 SetMuraFixedSndParamProc(int param_1,char *param_2)

{
  char *pcVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  char *local_34;
  undefined4 local_30;
  undefined1 local_29;
  char local_28;
  undefined1 local_27;
  undefined1 local_26;
  undefined1 local_25;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  uVar3 = *(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  local_29 = 0;
  local_28 = '\0';
  local_27 = 0;
  local_26 = 0;
  local_25 = 0;
  local_30 = 7;
  local_34 = param_2;
  if (uVar3 != 0x7626 && (uVar3 != 0x7663 && uVar3 != 0x7615)) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s: Not Supported (Ret = %d_\n","SetMuraFixedSndParamProc",0);
    return 0;
  }
  pcVar1 = strsep(&local_34,"-");
  if (pcVar1 != (char *)0x0) {
    local_28 = os_str_tol(pcVar1,0,10);
    if (local_28 == '\0') {
      local_29 = 1;
    }
    pcVar1 = strsep(&local_34,"-");
    if (pcVar1 != (char *)0x0) {
      local_27 = os_str_tol(pcVar1,0,10);
      pcVar1 = strsep(&local_34,"-");
      if (pcVar1 != (char *)0x0) {
        local_26 = os_str_tol(pcVar1,0,10);
        pcVar1 = strsep(&local_34,"");
        if (pcVar1 != (char *)0x0) {
          local_25 = os_str_tol(pcVar1,0,10);
          iVar2 = AndesAllocCmdMsg(param_1,9);
          if (iVar2 != 0) {
            local_24 = CONCAT13(0x55,CONCAT12(0xed,(undefined2)local_24));
            local_20 = CONCAT31(local_20._1_3_,10);
            uVar4 = 1;
            AndesInitCmdMsg(iVar2,local_24,local_20,local_1c,local_18,local_14);
            AndesAppendCmdMsg(iVar2,&local_30,4);
            AndesAppendCmdMsg(iVar2,&local_29,5);
            AndesSendCmdMsg(param_1,iVar2);
            goto LAB_00095f08;
          }
        }
      }
    }
  }
  uVar4 = 0;
LAB_00095f08:
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d_\n","SetMuraFixedSndParamProc",uVar4);
  }
  return uVar4;
}

