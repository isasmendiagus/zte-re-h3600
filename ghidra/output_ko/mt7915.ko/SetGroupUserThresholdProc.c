// module: mt7915.ko
// function: SetGroupUserThresholdProc @ 0x8d4f8
// size: 456 bytes
//

undefined4 SetGroupUserThresholdProc(undefined4 param_1,char *param_2)

{
  undefined1 uVar1;
  byte bVar2;
  char *pcVar3;
  char *pcVar4;
  int iVar5;
  undefined4 uVar6;
  char *local_3c [2];
  byte local_32;
  byte bStack_31;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  uVar6 = 0;
  local_32 = 0;
  bStack_31 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_30 = 8;
  local_3c[0] = param_2;
  pcVar3 = strsep(local_3c,"_");
  if ((pcVar3 != (char *)0x0) && (pcVar4 = strsep(local_3c,""), pcVar4 != (char *)0x0)) {
    uVar1 = os_str_tol(pcVar3,0,10);
    _local_32 = CONCAT11(bStack_31,uVar1);
    bVar2 = os_str_tol(pcVar4,0,10);
    bStack_31 = bVar2;
    if (4 < bVar2 || local_32 < 2) {
      if (DebugLevel < 4) {
        return 0;
      }
      printk("Min < 2 and Max > 4 is NOT allowed\n");
      goto LAB_0008d644;
    }
    if ((3 < DebugLevel) && (printk(&_LC0,"SetGroupUserThresholdProc"), 3 < DebugLevel)) {
      printk("Values %d %d\n",local_32,bStack_31);
    }
    iVar5 = AndesAllocCmdMsg(param_1,6);
    if (iVar5 != 0) {
      local_2c = CONCAT13(0x40,CONCAT12(0xed,(undefined2)local_2c));
      local_28 = CONCAT31(local_28._1_3_,10);
      uVar6 = 1;
      AndesInitCmdMsg(iVar5,local_2c,local_28,local_24,local_20,local_1c);
      AndesAppendCmdMsg(iVar5,&local_30,4);
      AndesAppendCmdMsg(iVar5,&local_32,2);
      AndesSendCmdMsg(param_1,iVar5);
      goto LAB_0008d644;
    }
  }
  uVar6 = 0;
LAB_0008d644:
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d\n","SetGroupUserThresholdProc",uVar6);
  }
  return uVar6;
}

