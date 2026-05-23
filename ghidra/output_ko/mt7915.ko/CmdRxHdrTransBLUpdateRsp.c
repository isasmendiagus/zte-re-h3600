// module: mt7915.ko
// function: CmdRxHdrTransBLUpdateRsp @ 0x1c4120
// size: 48 bytes
//

void CmdRxHdrTransBLUpdateRsp(undefined4 param_1,undefined1 *param_2)

{
  if (DebugLevel < 3) {
    return;
  }
  printk("%s: EventExtCmdResult.ucExTenCID = 0x%x,u4Status = 0x%x\n","CmdRxHdrTransBLUpdateRsp",
         *param_2,*(undefined4 *)(param_2 + 4));
  return;
}

