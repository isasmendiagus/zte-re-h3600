// module: mt7915.ko
// function: StaRecUpdateAmsdu @ 0x1c2308
// size: 112 bytes
//

undefined4 StaRecUpdateAmsdu(undefined4 param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 local_18;
  undefined4 local_14;
  
  iVar2 = *(int *)(param_3 + 0x9c);
  local_18 = 0;
  local_14 = 0;
  if (iVar2 == 0) {
    uVar1 = 0xffffffff;
  }
  else {
    os_zero_mem(&local_18,8);
    local_14 = (uint)CONCAT21(local_14._2_2_,*(undefined1 *)(iVar2 + 0xd06)) << 8;
    local_18 = 0x80005;
    AndesAppendCmdMsg(param_2,&local_18,8);
    uVar1 = 0;
  }
  return uVar1;
}

