// module: mt7915.ko
// function: StaRecUpdateHtInfo @ 0x1c29f0
// size: 108 bytes
//

undefined4 StaRecUpdateHtInfo(undefined4 param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined2 local_18;
  undefined2 local_16;
  undefined1 auStack_14 [4];
  
  iVar2 = *(int *)(param_3 + 0x9c);
  if (iVar2 == 0) {
    uVar1 = 0xffffffff;
  }
  else {
    os_zero_mem(&local_18);
    local_18 = 9;
    local_16 = 8;
    os_move_mem(auStack_14,(void *)(iVar2 + 0xca4),2);
    AndesAppendCmdMsg(param_2,&local_18,8);
    uVar1 = 0;
  }
  return uVar1;
}

