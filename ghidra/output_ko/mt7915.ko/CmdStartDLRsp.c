// module: mt7915.ko
// function: CmdStartDLRsp @ 0x1ab910
// size: 220 bytes
//

void CmdStartDLRsp(undefined4 param_1,undefined1 *param_2)

{
  switch(*param_2) {
  case 0:
    break;
  case 1:
    if (0 < DebugLevel) {
      printk("%s: WiFi FW Download Invalid Parameter\n","CmdStartDLRsp");
      return;
    }
    return;
  case 2:
    if (0 < DebugLevel) {
      printk("%s: WiFi FW Download Invalid CRC\n","CmdStartDLRsp");
      return;
    }
    return;
  case 3:
    if (0 < DebugLevel) {
      printk("%s: WiFi FW Download Decryption Fail\n","CmdStartDLRsp");
      return;
    }
    return;
  case 4:
    if (0 < DebugLevel) {
      printk("%s: WiFi FW Download Unknown CMD\n","CmdStartDLRsp");
      return;
    }
    return;
  case 5:
    if (0 < DebugLevel) {
      printk("%s: WiFi FW Download Timeout\n","CmdStartDLRsp");
      return;
    }
    return;
  default:
    if (0 < DebugLevel) {
      printk("%s: Unknow Status(%d)\n","CmdStartDLRsp");
      return;
    }
    return;
  }
  if (0 < DebugLevel) {
    printk("%s: WiFI FW Download Success\n","CmdStartDLRsp");
    return;
  }
  return;
}

