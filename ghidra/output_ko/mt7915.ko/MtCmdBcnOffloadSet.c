// module: mt7915.ko
// function: MtCmdBcnOffloadSet @ 0x1b5e1c
// size: 304 bytes
//

undefined4 MtCmdBcnOffloadSet(undefined4 param_1,undefined1 *param_2)

{
  int iVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  uVar2 = 0;
  uVar3 = 0;
  uVar4 = 0;
  uVar5 = 0;
  if (0 < DebugLevel) {
    uVar2 = 0;
    printk("%s(): Enable=%d, OM=%d, WlanIdx=%d, Band=%d, Len=%d, TimOffset=%d\n",
           "MtCmdBcnOffloadSet",param_2[1],*param_2,param_2[2],param_2[3],
           *(undefined2 *)(param_2 + 8),*(undefined2 *)(param_2 + 10),0,0,0,0);
  }
  iVar1 = AndesAllocCmdMsg(param_1,0x210);
  if (iVar1 == 0) {
    uVar3 = 3;
  }
  else {
    AndesInitCmdMsg(iVar1,CONCAT13(0x49,CONCAT12(0xed,uVar2)),
                    CONCAT22(0xffff,(short)CONCAT31((int3)((uint)uVar3 >> 8),0xf)),uVar4,uVar5,
                    EventExtCmdResult);
    AndesAppendCmdMsg(iVar1,param_2,0x210);
    uVar3 = chip_cmd_tx(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdBcnOffloadSet",uVar3);
  }
  return uVar3;
}

