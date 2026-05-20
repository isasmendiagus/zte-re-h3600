// module: mt7915.ko
// function: StaRecUpdateBfee @ 0x1c2d0c
// size: 84 bytes
//

undefined4 StaRecUpdateBfee(undefined4 param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined1 auStack_18 [12];
  
  iVar2 = *(int *)(param_3 + 0x9c);
  if (iVar2 == 0) {
    uVar1 = 0xffffffff;
  }
  else {
    os_zero_mem(auStack_18,8);
    StaRecBfeeUpdate(iVar2,auStack_18);
    AndesAppendCmdMsg(param_2,auStack_18,8);
    uVar1 = 0;
  }
  return uVar1;
}

