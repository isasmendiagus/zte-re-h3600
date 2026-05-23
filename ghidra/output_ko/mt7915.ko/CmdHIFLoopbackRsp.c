// module: mt7915.ko
// function: CmdHIFLoopbackRsp @ 0x1c3e0c
// size: 124 bytes
//

void CmdHIFLoopbackRsp(undefined4 param_1,char *param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  
  cVar1 = *param_2;
  if (DebugLevel < 1) {
    if (cVar1 == '\0') {
      return;
    }
  }
  else {
    printk("HIF Loopback status=%d\n",cVar1);
    if (cVar1 == '\0') {
      if (DebugLevel < 4) {
        return;
      }
      printk("%s: Request target address and length success\n","CmdHIFLoopbackRsp");
      return;
    }
  }
  if (DebugLevel < 0) {
    return;
  }
  printk("%s: Unknow Status(%d)\n","CmdHIFLoopbackRsp",cVar1,param_4);
  return;
}

