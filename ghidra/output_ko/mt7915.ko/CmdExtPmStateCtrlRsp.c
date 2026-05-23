// module: mt7915.ko
// function: CmdExtPmStateCtrlRsp @ 0x1ab618
// size: 84 bytes
//

void CmdExtPmStateCtrlRsp
               (undefined4 param_1,undefined1 *param_2,undefined4 param_3,undefined4 param_4)

{
  if (DebugLevel < 3) {
    return;
  }
  printk("%s: EventExtCmdResult.ucExTenCID = 0x%x\n","CmdExtPmStateCtrlRsp",*param_2);
  if (DebugLevel < 3) {
    return;
  }
  printk("%s: EventExtCmdResult.u4Status = 0x%x\n","CmdExtPmStateCtrlRsp",
         *(undefined4 *)(param_2 + 4),param_4);
  return;
}

