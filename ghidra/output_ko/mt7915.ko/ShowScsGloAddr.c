// module: mt7915.ko
// function: ShowScsGloAddr @ 0x238ae8
// size: 284 bytes
//

bool ShowScsGloAddr(undefined4 param_1)

{
  int iVar1;
  bool bVar2;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 *local_38;
  code *local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_48 = 5;
  if (0 < DebugLevel) {
    printk(&_LC6,"ShowScsGloAddr");
  }
  iVar1 = AndesAllocCmdMsg(param_1,4);
  bVar2 = iVar1 != 0;
  if (bVar2) {
    local_38 = &local_30;
    local_34 = scsEventDispatcher;
    local_44 = CONCAT13(0x82,CONCAT12(0xed,(undefined2)local_44));
    local_40 = CONCAT31(local_40._1_3_,5);
    local_40 = CONCAT22(0x18,(undefined2)local_40);
    AndesInitCmdMsg(iVar1,local_44,local_40,local_3c,local_38,scsEventDispatcher);
    AndesAppendCmdMsg(iVar1,&local_48,4);
    AndesSendCmdMsg(param_1,iVar1);
  }
  if (0 < DebugLevel) {
    printk("%s:(Ret = %d\n","ShowScsGloAddr",bVar2);
  }
  return bVar2;
}

