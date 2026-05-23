// module: mt7915.ko
// function: CmdEfuseBufferModeRsp @ 0x1ab78c
// size: 84 bytes
//

void CmdEfuseBufferModeRsp
               (undefined4 param_1,undefined1 *param_2,undefined4 param_3,undefined4 param_4)

{
  if (DebugLevel < 4) {
    return;
  }
  printk("%s: EventExtCmdResult.ucExTenCID = 0x%x\n","CmdEfuseBufferModeRsp",*param_2);
  if (DebugLevel < 4) {
    return;
  }
  printk("%s: EventExtCmdResult.u4Status = 0x%x\n","CmdEfuseBufferModeRsp",
         *(undefined4 *)(param_2 + 4),param_4);
  return;
}

