// module: mt7915.ko
// function: StaRecUpdateBf @ 0x1c3358
// size: 84 bytes
//

undefined4 StaRecUpdateBf(undefined4 param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined1 auStack_40 [52];
  
  iVar2 = *(int *)(param_3 + 0x9c);
  if (iVar2 == 0) {
    uVar1 = 0xffffffff;
  }
  else {
    os_zero_mem(auStack_40,0x30);
    StaRecBfUpdate(iVar2,auStack_40);
    AndesAppendCmdMsg(param_2,auStack_40,0x30);
    uVar1 = 0;
  }
  return uVar1;
}

