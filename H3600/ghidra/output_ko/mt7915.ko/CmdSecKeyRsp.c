// module: mt7915.ko
// function: CmdSecKeyRsp @ 0x1ab700
// size: 76 bytes
//

void CmdSecKeyRsp(undefined4 param_1,undefined4 *param_2)

{
  if (param_2[1] == 0) {
    if (DebugLevel < 3) {
      return;
    }
    printk("%s, wlan idx(%d), status: 0x%x\n","CmdSecKeyRsp",*param_2);
    return;
  }
  if (DebugLevel < 0) {
    return;
  }
  printk("%s, error set key, wlan idx(%d), status: 0x%x\n","CmdSecKeyRsp",*param_2);
  return;
}

