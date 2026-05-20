// module: mt7915.ko
// function: ShowMuruLastSplByQid @ 0x23fe58
// size: 284 bytes
//

bool ShowMuruLastSplByQid(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  bool bVar2;
  byte local_31;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_30 = 0x12;
  local_31 = os_str_tol(param_2,0,10);
  if (2 < DebugLevel) {
    printk("%s: u1Qid = %d\n","ShowMuruLastSplByQid",local_31);
  }
  iVar1 = AndesAllocCmdMsg(param_1,5);
  bVar2 = iVar1 != 0;
  if (bVar2) {
    local_2c = CONCAT13(0x9f,CONCAT12(0xed,(undefined2)local_2c));
    local_28 = CONCAT31(local_28._1_3_,10);
    AndesInitCmdMsg(iVar1,local_2c,local_28,local_24,local_20,local_1c);
    AndesAppendCmdMsg(iVar1,&local_30,4);
    AndesAppendCmdMsg(iVar1,&local_31,1);
    AndesSendCmdMsg(param_1,iVar1);
  }
  if (2 < DebugLevel) {
    printk("%s: Ret = %d\n","ShowMuruLastSplByQid",bVar2);
  }
  return bVar2;
}

