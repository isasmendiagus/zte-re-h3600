// module: mt7915.ko
// function: WscPassXmlDeclare @ 0x200158
// size: 212 bytes
//

undefined4 WscPassXmlDeclare(int *param_1)

{
  int iVar1;
  
  if (2 < DebugLevel) {
    printk("======> WscPassXmlDeclare\n");
  }
  iVar1 = rtstrstr(*param_1,"<?xml");
  if (iVar1 == 0) {
    if (2 < DebugLevel) {
      printk("WscPassXmlDeclare: missing XML Declare <?xml\n");
      return 0;
    }
  }
  else {
    iVar1 = rtstrstr(*param_1,&_LC3);
    if (iVar1 != 0) {
      *param_1 = iVar1 + 2;
      if (DebugLevel < 3) {
        return 1;
      }
      printk("<====== WscPassXmlDeclare\n");
      return 1;
    }
    if (2 < DebugLevel) {
      printk("XML syntax error: missing XML Declare ?>\n");
      return 0;
    }
  }
  return 0;
}

