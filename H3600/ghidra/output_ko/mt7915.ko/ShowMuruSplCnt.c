// module: mt7915.ko
// function: ShowMuruSplCnt @ 0x23af28
// size: 244 bytes
//

bool ShowMuruSplCnt(undefined4 param_1)

{
  int iVar1;
  bool bVar2;
  undefined4 local_26c;
  undefined4 local_268;
  undefined4 local_264;
  undefined4 local_260;
  undefined1 *local_25c;
  code *local_258;
  undefined1 auStack_254 [580];
  
  memset(auStack_254,0,0x244);
  local_268 = 0;
  local_264 = 0;
  local_260 = 0;
  local_26c = 0x13;
  iVar1 = AndesAllocCmdMsg(param_1,4);
  bVar2 = iVar1 != 0;
  if (bVar2) {
    local_25c = auStack_254;
    local_258 = muruEventDispatcher;
    local_264 = CONCAT22(0x244,(undefined2)local_264);
    local_268 = CONCAT13(0x9f,CONCAT12(0xed,(undefined2)local_268));
    local_264 = CONCAT31(local_264._1_3_,5);
    AndesInitCmdMsg(iVar1,local_268,local_264,local_260,local_25c,muruEventDispatcher);
    AndesAppendCmdMsg(iVar1,&local_26c,4);
    AndesSendCmdMsg(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d_\n","ShowMuruSplCnt",bVar2);
  }
  return bVar2;
}

