// module: mt7915.ko
// function: SetMuraPlatformTypeProc @ 0x96140
// size: 224 bytes
//

bool SetMuraPlatformTypeProc(undefined4 param_1)

{
  int iVar1;
  bool bVar2;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_2c = 8;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  local_28 = 0;
  iVar1 = AndesAllocCmdMsg(param_1,8);
  bVar2 = iVar1 != 0;
  if (bVar2) {
    local_24 = CONCAT13(0x55,CONCAT12(0xed,(undefined2)local_24));
    local_20 = CONCAT31(local_20._1_3_,10);
    AndesInitCmdMsg(iVar1,local_24,local_20,local_1c,local_18,local_14);
    AndesAppendCmdMsg(iVar1,&local_2c,4);
    AndesAppendCmdMsg(iVar1,&local_28,4);
    AndesSendCmdMsg(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d_\n","SetMuraPlatformTypeProc",bVar2);
  }
  return bVar2;
}

