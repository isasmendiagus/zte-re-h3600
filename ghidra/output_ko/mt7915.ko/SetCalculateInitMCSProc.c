// module: mt7915.ko
// function: SetCalculateInitMCSProc @ 0x8d7b0
// size: 288 bytes
//

undefined4 SetCalculateInitMCSProc(undefined4 param_1,char *param_2)

{
  char *pcVar1;
  int iVar2;
  undefined4 uVar3;
  char *local_3c [2];
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 *local_18;
  code *local_14;
  
  local_34 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_30 = 0x10;
  local_3c[0] = param_2;
  pcVar1 = strsep(local_3c,"_");
  if ((pcVar1 == (char *)0x0) || (iVar2 = AndesAllocCmdMsg(param_1,8), iVar2 == 0)) {
    uVar3 = 0;
  }
  else {
    local_18 = &local_2c;
    local_14 = eventDispatcher;
    local_24 = CONCAT13(0x40,CONCAT12(0xed,(undefined2)local_24));
    local_20 = CONCAT31(local_20._1_3_,5);
    local_20 = CONCAT22(8,(undefined2)local_20);
    AndesInitCmdMsg(iVar2,local_24,local_20,local_1c,local_18,eventDispatcher);
    AndesAppendCmdMsg(iVar2,&local_30,4);
    AndesAppendCmdMsg(iVar2,&local_34,4);
    uVar3 = AndesSendCmdMsg(param_1,iVar2);
  }
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d\n","SetCalculateInitMCSProc",uVar3);
  }
  return uVar3;
}

