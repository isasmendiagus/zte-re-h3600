// module: mt7915.ko
// function: WscGetXmlKeyIndex @ 0x200690
// size: 184 bytes
//

undefined4 WscGetXmlKeyIndex(undefined4 param_1,char *param_2)

{
  int iVar1;
  
  *param_2 = '\x01';
  iVar1 = rtstrstr(param_1,"<keyIndex>");
  if (iVar1 == 0) {
    if (2 < DebugLevel) {
      printk("WscGetXmlKeyIndex: missing %s\n","<keyIndex>");
      return 0;
    }
  }
  else {
    iVar1 = rtstrstr(iVar1 + 10,"</keyIndex>");
    if (iVar1 != 0) {
      *param_2 = *(char *)(iVar1 + -1) + -0x30;
      return 1;
    }
    if (2 < DebugLevel) {
      printk("WscGetXmlKeyIndex: missing %s\n","</keyIndex>");
      return 0;
    }
  }
  return 0;
}

