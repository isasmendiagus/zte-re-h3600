// module: mt7915.ko
// function: ShowMuruGloAddr @ 0x23b020
// size: 276 bytes
//

bool ShowMuruGloAddr(undefined4 param_1)

{
  int iVar1;
  bool bVar2;
  undefined4 local_f8;
  undefined4 local_f4;
  undefined4 local_f0;
  undefined4 local_ec;
  undefined1 *local_e8;
  code *local_e4;
  undefined1 auStack_e0 [204];
  
  memset(auStack_e0,0,200);
  local_f8 = 0xb;
  local_f4 = 0;
  local_f0 = 0;
  local_ec = 0;
  if (0 < DebugLevel) {
    printk(&_LC51,"ShowMuruGloAddr");
  }
  iVar1 = AndesAllocCmdMsg(param_1,4);
  bVar2 = iVar1 != 0;
  if (bVar2) {
    local_e8 = auStack_e0;
    local_e4 = muruEventDispatcher;
    local_f4 = CONCAT13(0x9f,CONCAT12(0xed,(undefined2)local_f4));
    local_f0 = CONCAT31(local_f0._1_3_,5);
    local_f0 = CONCAT22(200,(undefined2)local_f0);
    AndesInitCmdMsg(iVar1,local_f4,local_f0,local_ec,local_e8,muruEventDispatcher);
    AndesAppendCmdMsg(iVar1,&local_f8,4);
    AndesSendCmdMsg(param_1,iVar1);
  }
  if (0 < DebugLevel) {
    printk("%s:(Ret = %d\n","ShowMuruGloAddr",bVar2);
  }
  return bVar2;
}

