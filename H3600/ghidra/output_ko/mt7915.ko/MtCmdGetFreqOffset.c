// module: mt7915.ko
// function: MtCmdGetFreqOffset @ 0x1b6fa0
// size: 324 bytes
//

undefined4 MtCmdGetFreqOffset(int param_1,undefined1 param_2,undefined4 param_3)

{
  int iVar1;
  byte bVar2;
  undefined4 uVar3;
  byte local_64 [4];
  undefined1 local_60;
  
  iVar1 = AndesAllocCmdMsg(param_1,0x4c);
  if (iVar1 == 0) {
    uVar3 = 3;
  }
  else {
    AndesInitCmdMsg(iVar1,0x3ded0000,0x80007,0,param_3,MtCmdGetFreqOffsetRsp);
    if ((*(uint *)(param_1 + 0xa3ac14) & 1) == 0) {
      bVar2 = 0;
      if (*(int *)(param_1 + 0xa77bb4) == 1) {
        bVar2 = (byte)*(undefined4 *)(*(int *)(param_1 + 0xa77bb8) + 0x4e0) & 1;
      }
    }
    else {
      bVar2 = 1;
    }
    __memzero(local_64,0x4c);
    local_64[1] = 0xb;
    local_64[0] = bVar2;
    local_60 = param_2;
    AndesAppendCmdMsg(iVar1,local_64,0x4c);
    uVar3 = chip_cmd_tx(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdGetFreqOffset",uVar3);
  }
  return uVar3;
}

