// module: mt7915.ko
// function: ShowTxopDefaultProc @ 0x8ead8
// size: 232 bytes
//

bool ShowTxopDefaultProc(undefined4 param_1)

{
  int iVar1;
  bool bVar2;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 *local_18;
  code *local_14;
  
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_30 = 0x13;
  iVar1 = AndesAllocCmdMsg(param_1,0xc);
  bVar2 = iVar1 != 0;
  if (bVar2) {
    local_18 = &local_2c;
    local_14 = eventDispatcher;
    local_24 = CONCAT13(0x40,CONCAT12(0xed,(undefined2)local_24));
    local_20 = CONCAT31(local_20._1_3_,5);
    local_20 = CONCAT22(8,(undefined2)local_20);
    AndesInitCmdMsg(iVar1,local_24,local_20,local_1c,local_18,eventDispatcher);
    AndesAppendCmdMsg(iVar1,&local_30,4);
    AndesSendCmdMsg(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d\n","ShowTxopDefaultProc",bVar2);
  }
  return bVar2;
}

