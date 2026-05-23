// module: mt7915.ko
// function: send_cmd_msg @ 0x97cb4
// size: 320 bytes
//

undefined4 send_cmd_msg(undefined4 param_1,byte *param_2,int *param_3)

{
  int iVar1;
  code *pcVar2;
  undefined4 uVar3;
  short sVar4;
  byte bVar5;
  undefined4 local_30;
  int *local_28;
  
  local_28 = (int *)0x0;
  if ((*param_2 & 0x3f) < 0xc) {
    pcVar2 = (code *)0x0;
    bVar5 = 10;
    sVar4 = 0;
  }
  else if (param_3 == (int *)0x0) {
    pcVar2 = eventExtCmdTxcmdShow;
    bVar5 = 5;
    sVar4 = 0;
  }
  else {
    pcVar2 = eventExtCmdTxcmdShow;
    bVar5 = 5;
    sVar4 = (short)((uint)(*param_3 << 10) >> 0x10) + 4;
  }
  iVar1 = AndesAllocCmdMsg(param_1,((uint)(*(int *)param_2 << 10) >> 0x10) + 4);
  if (iVar1 == 0) {
    uVar3 = 1;
  }
  else {
    if (param_3 != (int *)0x0) {
      local_28 = param_3;
    }
    uVar3 = 0;
    local_30 = CONCAT22(sVar4,(ushort)bVar5);
    AndesInitCmdMsg(iVar1,0x98ed0000,local_30,0,local_28,pcVar2);
    AndesAppendCmdMsg(iVar1,param_2,((uint)(*(int *)param_2 << 10) >> 0x10) + 4);
    AndesSendCmdMsg(param_1,iVar1);
  }
  if (2 < DebugLevel) {
    printk("%s: Ret = %d\n","send_cmd_msg",uVar3);
  }
  return uVar3;
}

