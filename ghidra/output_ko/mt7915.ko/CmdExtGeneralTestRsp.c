// module: mt7915.ko
// function: CmdExtGeneralTestRsp @ 0x1c4154
// size: 116 bytes
//

void CmdExtGeneralTestRsp(undefined4 param_1,char *param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  
  cVar1 = *param_2;
  if (DebugLevel < 0) {
    return;
  }
  printk("General Test status=%d\n",cVar1);
  if (cVar1 == '\0') {
    if (DebugLevel < 4) {
      return;
    }
    printk("%s: General Test success\n","CmdExtGeneralTestRsp");
    return;
  }
  if (DebugLevel < 0) {
    return;
  }
  printk("%s: General Test success Unknow Status(%d)\n","CmdExtGeneralTestRsp",cVar1,param_4);
  return;
}

