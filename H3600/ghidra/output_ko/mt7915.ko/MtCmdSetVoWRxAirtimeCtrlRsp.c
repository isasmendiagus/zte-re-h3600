// module: mt7915.ko
// function: MtCmdSetVoWRxAirtimeCtrlRsp @ 0x1ac8cc
// size: 244 bytes
//

void MtCmdSetVoWRxAirtimeCtrlRsp(int param_1,short *param_2,size_t param_3)

{
  memmove(*(void **)(param_1 + 0xc),param_2,param_3);
  if (3 < DebugLevel) {
    printk("%s: u4CtrlFieldID = 0x%x, ExtCmd (0x%02x)\n","MtCmdSetVoWRxAirtimeCtrlRsp",*param_2,
           *(undefined1 *)(param_1 + 3));
    if (3 < DebugLevel) {
      printk("%s: u4CtrlGetStatus = 0x%x\n","MtCmdSetVoWRxAirtimeCtrlRsp",
             *(undefined4 *)(param_2 + 4));
      if (3 < DebugLevel) {
        printk("%s: u4CtrlSetStatus = 0x%x\n","MtCmdSetVoWRxAirtimeCtrlRsp",
               *(undefined4 *)(param_2 + 2));
      }
    }
  }
  if (*param_2 != 4) {
    return;
  }
  if (param_2[1] == 1) {
    if (DebugLevel < 4) {
      return;
    }
    printk("%s: Non Wi-Fi for band%d = 0x%x\n","MtCmdSetVoWRxAirtimeCtrlRsp",(char)param_2[0xe],
           *(undefined4 *)(param_2 + 0xc));
    return;
  }
  if (param_2[1] != 2) {
    return;
  }
  if (DebugLevel < 4) {
    return;
  }
  printk("%s: OBSS for band%d = 0x%x\n","MtCmdSetVoWRxAirtimeCtrlRsp",(char)param_2[0x12],
         *(undefined4 *)(param_2 + 0x10));
  return;
}

