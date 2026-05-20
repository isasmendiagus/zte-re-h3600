// module: mt7915.ko
// function: CmdRxHdrTransUpdateRsp @ 0x1c1e78
// size: 120 bytes
//

void CmdRxHdrTransUpdateRsp
               (undefined4 param_1,undefined1 *param_2,undefined4 param_3,undefined4 param_4)

{
  if (DebugLevel < 3) {
    return;
  }
  printk("%s: EventExtCmdResult.ucExTenCID = 0x%x\n","CmdRxHdrTransUpdateRsp",*param_2);
  if (*(int *)(param_2 + 4) == 0) {
    if (DebugLevel < 3) {
      return;
    }
    printk("%s::EventExtCmdResult.u4Status = 0x%x\n","CmdRxHdrTransUpdateRsp",0,param_4);
    return;
  }
  if (DebugLevel < 3) {
    return;
  }
  printk("%s::BUG::EventExtCmdResult.u4Status = 0x%x\n","CmdRxHdrTransUpdateRsp",
         *(int *)(param_2 + 4),param_4);
  return;
}

