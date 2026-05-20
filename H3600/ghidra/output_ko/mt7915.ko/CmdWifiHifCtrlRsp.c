// module: mt7915.ko
// function: CmdWifiHifCtrlRsp @ 0x1ac05c
// size: 112 bytes
//

void CmdWifiHifCtrlRsp(int param_1,undefined1 *param_2,size_t param_3,undefined4 param_4)

{
  if (2 < DebugLevel) {
    printk("%s: EventExtCmdResult.ucExTenCID = 0x%x\n","CmdWifiHifCtrlRsp",*param_2,DebugLevel,
           param_4);
    if (2 < DebugLevel) {
      printk("%s: EventExtCmdResult.u4Status = 0x%x\n","CmdWifiHifCtrlRsp",
             *(undefined4 *)(param_2 + 4),DebugLevel,param_4);
    }
  }
  os_move_mem(*(void **)(param_1 + 0xc),param_2,param_3);
  return;
}

