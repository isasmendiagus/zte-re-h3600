// module: mt7915.ko
// function: SetTxReqMinTimeProc @ 0x8db50
// size: 308 bytes
//

bool SetTxReqMinTimeProc(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  bool bVar2;
  undefined2 local_32;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  local_32 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_30 = 0xc;
  local_32 = os_str_tol(param_2,0,0x10);
  if ((3 < DebugLevel) && (printk(&_LC0,"SetTxReqMinTimeProc"), 3 < DebugLevel)) {
    printk("Values %d\n",local_32);
  }
  iVar1 = AndesAllocCmdMsg(param_1,6);
  bVar2 = iVar1 != 0;
  if (bVar2) {
    local_2c = CONCAT13(0x40,CONCAT12(0xed,(undefined2)local_2c));
    local_28 = CONCAT31(local_28._1_3_,10);
    AndesInitCmdMsg(iVar1,local_2c,local_28,local_24,local_20,local_1c);
    AndesAppendCmdMsg(iVar1,&local_30,4);
    AndesAppendCmdMsg(iVar1,&local_32,2);
    AndesSendCmdMsg(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d\n","SetTxReqMinTimeProc",bVar2);
  }
  return bVar2;
}

