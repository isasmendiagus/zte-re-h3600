// module: mt7915.ko
// function: SyncMuruSram @ 0x17f500
// size: 156 bytes
//

bool SyncMuruSram(undefined4 param_1)

{
  int iVar1;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_24 = 0;
  local_28 = 0x14;
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  iVar1 = AndesAllocCmdMsg(param_1,4);
  if (iVar1 != 0) {
    local_24 = CONCAT13(0x9f,CONCAT12(0xed,(undefined2)local_24));
    local_20 = CONCAT31(local_20._1_3_,10);
    AndesInitCmdMsg(iVar1,local_24,local_20,local_1c,local_18,local_14);
    AndesAppendCmdMsg(iVar1,&local_28,4);
    AndesSendCmdMsg(param_1,iVar1);
  }
  return iVar1 != 0;
}

