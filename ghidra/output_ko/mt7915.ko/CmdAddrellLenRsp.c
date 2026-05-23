// module: mt7915.ko
// function: CmdAddrellLenRsp @ 0x1ac64c
// size: 72 bytes
//

void CmdAddrellLenRsp(undefined4 param_1,char *param_2)

{
  if (*param_2 != '\0') {
    if (DebugLevel < 0) {
      return;
    }
    printk("%s: Unknow Status(%d)\n","CmdAddrellLenRsp");
    return;
  }
  if (DebugLevel < 4) {
    return;
  }
  printk("%s: Request target address and length success\n","CmdAddrellLenRsp");
  return;
}

