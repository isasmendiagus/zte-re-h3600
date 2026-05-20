// module: mt7915.ko
// function: WscGetXmlKey @ 0x2005a8
// size: 232 bytes
//

undefined4
WscGetXmlKey(undefined4 param_1,undefined4 param_2,undefined2 *param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  iVar1 = rtstrstr(param_1,"<networkKey",param_3,param_4,param_4);
  if (iVar1 == 0) {
    if (2 < DebugLevel) {
      printk("WscGetXmlKey: missing %s\n","<networkKey");
      return 0;
    }
  }
  else {
    iVar1 = iVar1 + 0xb;
    iVar2 = rtstrstr(iVar1,&_LC8);
    if (iVar2 != 0) {
      iVar1 = iVar2 + 1;
    }
    iVar2 = rtstrstr(iVar1,"</networkKey>");
    if (iVar2 == 0) {
      if (2 < DebugLevel) {
        printk("WscGetXmlKey: missing %s\n","</networkKey>");
        return 0;
      }
    }
    else {
      iVar2 = iVar2 - iVar1;
      if (iVar2 - 8U < 0x39) {
        RTMPMoveMemory(param_2,iVar1,iVar2);
        *param_3 = (short)iVar2;
        return 1;
      }
    }
  }
  return 0;
}

