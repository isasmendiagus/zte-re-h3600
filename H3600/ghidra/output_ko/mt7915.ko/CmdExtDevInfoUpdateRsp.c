// module: mt7915.ko
// function: CmdExtDevInfoUpdateRsp @ 0x1c3ee4
// size: 168 bytes
//

void CmdExtDevInfoUpdateRsp(undefined4 param_1,undefined1 *param_2)

{
  if (DebugLevel < 3) {
    if (*(int *)(param_2 + 4) == 0) {
      return;
    }
  }
  else {
    printk("%s: EventExtCmdResult.ucExTenCID = 0x%x\n","CmdExtDevInfoUpdateRsp",*param_2);
    if (*(int *)(param_2 + 4) == 0) {
      if (DebugLevel < 3) {
        return;
      }
      printk("%s::EventExtCmdResult.u4Status = 0x%x\n","CmdExtDevInfoUpdateRsp");
      if (DebugLevel < 3) {
        return;
      }
      printk("%s::ucOwnMacIdx(%d), u2TotalElementNum(%d)\n","CmdExtDevInfoUpdateRsp",param_2[8],
             *(undefined2 *)(param_2 + 10));
      return;
    }
  }
  if (DebugLevel < 0) {
    return;
  }
  printk("%s::BUG::EventExtCmdResult.u4Status = 0x%x\n","CmdExtDevInfoUpdateRsp");
  return;
}

