// module: mt7915.ko
// function: MtCmdSetVoWGroupCtrlRsp @ 0x1ac860
// size: 104 bytes
//

void MtCmdSetVoWGroupCtrlRsp(int param_1,undefined4 *param_2)

{
  memcpy(*(void **)(param_1 + 0xc),param_2,0x120);
  if (DebugLevel < 4) {
    return;
  }
  printk("%s: u4CtrlFieldID = 0x%x, ExtCmd (0x%02x)\n","MtCmdSetVoWGroupCtrlRsp",*param_2,
         *(undefined1 *)(param_1 + 3));
  if (DebugLevel < 4) {
    return;
  }
  printk("%s: ucCtrlStatus = 0x%x\n","MtCmdSetVoWGroupCtrlRsp",*(undefined1 *)((int)param_2 + 5));
  return;
}

