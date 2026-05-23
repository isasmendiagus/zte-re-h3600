// module: mt7915.ko
// function: WscGetXmlSSID @ 0x20022c
// size: 256 bytes
//

undefined4 WscGetXmlSSID(undefined4 param_1,int *param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  iVar1 = rtstrstr(param_1,"<ssid",param_3,param_4,param_4);
  if (iVar1 == 0) {
    if (2 < DebugLevel) {
      printk("WscGetXmlSSID: missing <ssid\n");
      return 0;
    }
  }
  else {
    iVar1 = iVar1 + 5;
    iVar2 = rtstrstr(iVar1,&_LC8);
    if (iVar2 != 0) {
      iVar1 = iVar2 + 1;
    }
    iVar2 = rtstrstr(iVar1,"</ssid>");
    if (iVar2 != 0) {
      *param_2 = iVar2 - iVar1;
      RTMPZeroMemory(param_2 + 1,0x20);
      if (0x1f < *param_2 - 1U) {
        *(undefined1 *)param_2 = 0;
        *(undefined1 *)((int)param_2 + 1) = 0;
        *(undefined1 *)((int)param_2 + 2) = 0;
        *(undefined1 *)((int)param_2 + 3) = 0;
        return 0;
      }
      RTMPMoveMemory(param_2 + 1,iVar1);
      return 1;
    }
    if (2 < DebugLevel) {
      printk("WscGetXmlSSID: missing </ssid>\n");
      return 0;
    }
  }
  return 0;
}

