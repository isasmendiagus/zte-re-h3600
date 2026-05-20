// module: mt7915.ko
// function: CmdExtTlvUpdateRsp @ 0x1c1e1c
// size: 92 bytes
//

void CmdExtTlvUpdateRsp(undefined4 param_1,undefined1 *param_2,undefined4 param_3,undefined4 param_4
                       )

{
  if (DebugLevel < 3) {
    return;
  }
  printk("%s: EventExtCmdResult.ucExTenCID = 0x%x\n","CmdExtTlvUpdateRsp",*param_2);
  if (DebugLevel < 3) {
    return;
  }
  printk("%s: EventExtCmdResult.u4Status = 0x%x\n","CmdExtTlvUpdateRsp",*(undefined4 *)(param_2 + 4)
         ,param_4);
  return;
}

