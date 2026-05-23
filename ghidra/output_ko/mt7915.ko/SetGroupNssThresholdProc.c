// module: mt7915.ko
// function: SetGroupNssThresholdProc @ 0x8d8d4
// size: 396 bytes
//

undefined4 SetGroupNssThresholdProc(undefined4 param_1,char *param_2)

{
  undefined1 uVar1;
  char *pcVar2;
  char *pcVar3;
  int iVar4;
  undefined4 uVar5;
  char *local_3c [2];
  undefined1 local_32;
  undefined1 uStack_31;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  local_32 = 0;
  uStack_31 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_30 = 10;
  local_3c[0] = param_2;
  pcVar2 = strsep(local_3c,"_");
  if ((pcVar2 != (char *)0x0) && (pcVar3 = strsep(local_3c,""), pcVar3 != (char *)0x0)) {
    uVar1 = os_str_tol(pcVar2,0,10);
    _local_32 = CONCAT11(uStack_31,uVar1);
    uVar1 = os_str_tol(pcVar3,0,10);
    uStack_31 = uVar1;
    if ((3 < DebugLevel) && (printk(&_LC0,"SetGroupNssThresholdProc"), 3 < DebugLevel)) {
      printk("Values %d %d\n",local_32,uStack_31);
    }
    iVar4 = AndesAllocCmdMsg(param_1,6);
    if (iVar4 != 0) {
      local_2c = CONCAT13(0x40,CONCAT12(0xed,(undefined2)local_2c));
      local_28 = CONCAT31(local_28._1_3_,10);
      uVar5 = 1;
      AndesInitCmdMsg(iVar4,local_2c,local_28,local_24,local_20,local_1c);
      AndesAppendCmdMsg(iVar4,&local_30,4);
      AndesAppendCmdMsg(iVar4,&local_32,2);
      AndesSendCmdMsg(param_1,iVar4);
      goto LAB_0008d9fc;
    }
  }
  uVar5 = 0;
LAB_0008d9fc:
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d\n","SetGroupNssThresholdProc",uVar5);
  }
  return uVar5;
}

