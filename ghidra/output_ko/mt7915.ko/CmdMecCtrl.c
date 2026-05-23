// module: mt7915.ko
// function: CmdMecCtrl @ 0x1b459c
// size: 476 bytes
//

undefined4 CmdMecCtrl(undefined4 param_1,undefined2 *param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  
  uVar4 = 0;
  uVar5 = 0;
  uVar6 = 0;
  iVar1 = AndesAllocCmdMsg(param_1,0xc);
  if (iVar1 == 0) {
    uVar4 = 3;
  }
  else {
    if (((3 < DebugLevel) && (printk("%s: u2Action=0x%02X\n","CmdMecCtrl",*param_2), 3 < DebugLevel)
        ) && (printk("%s: u2WlanIdx=0x%02X, u1AmsduAlgoEn=0x%02X\n","CmdMecCtrl",param_2[2],
                     *(undefined1 *)(param_2 + 3)), 3 < DebugLevel)) {
      uVar3 = (uint)(ushort)param_2[4];
      printk("%s: u2WlanIdx=0x%02X, u1AmsduEn=0x%02X, u1AmsduNum=0x%02X, u2AmsduLen=0x%02X\n",
             "CmdMecCtrl",param_2[2],*(undefined1 *)(param_2 + 3),*(undefined1 *)((int)param_2 + 7),
             uVar3,uVar4,uVar5,uVar6);
      if (3 < DebugLevel) {
        printk("%s: u1BaNum=0x%02X, u1AmsduNum=0x%02X, u2AmsduRateThr=0x%02X\n","CmdMecCtrl",
               *(undefined1 *)(param_2 + 2),*(undefined1 *)((int)param_2 + 5),param_2[3],uVar3,uVar4
               ,uVar5,uVar6);
      }
    }
    iVar2 = 0;
    do {
      if (3 < DebugLevel) {
        printk("[%u]: %u\n",iVar2,*(undefined1 *)((int)param_2 + iVar2));
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 != 0xc);
    AndesInitCmdMsg(iVar1,CONCAT13(0x1f,CONCAT12(0xed,(short)uVar4)),
                    CONCAT22(0xffff,(short)CONCAT31((int3)((uint)uVar5 >> 8),8)),500,0,0);
    AndesAppendCmdMsg(iVar1,param_2,0xc);
    uVar4 = chip_cmd_tx(param_1,iVar1);
  }
  if (0 < DebugLevel) {
    printk("%s:(ret = %d)\n","CmdMecCtrl",uVar4);
  }
  return uVar4;
}

