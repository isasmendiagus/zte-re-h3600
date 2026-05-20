// module: mt7915.ko
// function: CmdReStartDLRsp @ 0x1ab7e4
// size: 220 bytes
//

void CmdReStartDLRsp(undefined4 param_1,undefined1 *param_2)

{
  switch(*param_2) {
  case 0:
    break;
  case 1:
    if (0 < DebugLevel) {
      printk("%s: WiFi FW Download Invalid Parameter\n","CmdReStartDLRsp");
      return;
    }
    return;
  case 2:
    if (0 < DebugLevel) {
      printk("%s: WiFi FW Download Invalid CRC\n","CmdReStartDLRsp");
      return;
    }
    return;
  case 3:
    if (0 < DebugLevel) {
      printk("%s: WiFi FW Download Decryption Fail\n","CmdReStartDLRsp");
      return;
    }
    return;
  case 4:
    if (0 < DebugLevel) {
      printk("%s: WiFi FW Download Unknown CMD\n","CmdReStartDLRsp");
      return;
    }
    return;
  case 5:
    if (0 < DebugLevel) {
      printk("%s: WiFi FW Download Timeout\n","CmdReStartDLRsp");
      return;
    }
    return;
  default:
    if (0 < DebugLevel) {
      printk("%s: Unknow Status(%d)\n","CmdReStartDLRsp");
      return;
    }
    return;
  }
  if (0 < DebugLevel) {
    printk("%s: WiFI FW Download Success\n","CmdReStartDLRsp");
    return;
  }
  return;
}

