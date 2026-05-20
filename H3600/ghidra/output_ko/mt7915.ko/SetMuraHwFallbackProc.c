// module: mt7915.ko
// function: SetMuraHwFallbackProc @ 0x95f58
// size: 484 bytes
//

undefined4 SetMuraHwFallbackProc(int param_1,char *param_2)

{
  undefined1 uVar1;
  char *pcVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  char *local_3c [2];
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  uVar4 = *(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff;
  local_34 = 0xc;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_3c[0] = param_2;
  if (uVar4 != 0x7626 && (uVar4 != 0x7663 && uVar4 != 0x7615)) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s: Not Supported (Ret = %d_\n","SetMuraHwFallbackProc",0);
    return 0;
  }
  pcVar2 = strsep(local_3c,"-");
  if (pcVar2 != (char *)0x0) {
    uVar1 = os_str_tol(pcVar2,0,10);
    local_30 = CONCAT31(local_30._1_3_,uVar1);
    pcVar2 = strsep(local_3c,"");
    if (pcVar2 != (char *)0x0) {
      uVar1 = os_str_tol(pcVar2,0,10);
      local_30._0_2_ = CONCAT11(uVar1,(undefined1)local_30);
      if (0 < DebugLevel) {
        printk("%s: UpConfig:%u Downconfig:%u\n","SetMuraHwFallbackProc",(undefined1)local_30,uVar1)
        ;
      }
      iVar3 = AndesAllocCmdMsg(param_1,8);
      if (iVar3 != 0) {
        local_2c = CONCAT13(0x55,CONCAT12(0xed,(undefined2)local_2c));
        local_28 = CONCAT31(local_28._1_3_,10);
        uVar5 = 1;
        AndesInitCmdMsg(iVar3,local_2c,local_28,local_24,local_20,local_1c);
        AndesAppendCmdMsg(iVar3,&local_34,4);
        AndesAppendCmdMsg(iVar3,&local_30,4);
        AndesSendCmdMsg(param_1,iVar3);
        goto LAB_000960dc;
      }
    }
  }
  uVar5 = 0;
LAB_000960dc:
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d_\n","SetMuraHwFallbackProc",uVar5);
  }
  return uVar5;
}

