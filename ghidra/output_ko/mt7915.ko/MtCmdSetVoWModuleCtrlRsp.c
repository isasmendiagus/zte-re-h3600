// module: mt7915.ko
// function: MtCmdSetVoWModuleCtrlRsp @ 0x1ac5cc
// size: 124 bytes
//

void MtCmdSetVoWModuleCtrlRsp(int param_1,undefined2 *param_2,undefined4 param_3,undefined4 param_4)

{
  if (DebugLevel < 4) {
    return;
  }
  printk("%s: u4CtrlFieldID = 0x%x, ExtCmd (0x%02x)\n","MtCmdSetVoWModuleCtrlRsp",*param_2,
         *(undefined1 *)(param_1 + 3));
  if (DebugLevel < 4) {
    return;
  }
  printk("%s: u4CtrlGetStatus = 0x%x\n","MtCmdSetVoWModuleCtrlRsp",*(undefined4 *)(param_2 + 4));
  if (DebugLevel < 4) {
    return;
  }
  printk("%s: u4CtrlSetStatus = 0x%x\n","MtCmdSetVoWModuleCtrlRsp",*(undefined4 *)(param_2 + 2),
         param_4);
  return;
}

