// module: mt7915.ko
// function: CmdExtEventRsp @ 0x1aba9c
// size: 152 bytes
//

void CmdExtEventRsp(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  if (DebugLevel < 1) {
    if (param_3 == 0) {
      return;
    }
  }
  else {
    printk("CmdEID=0x%x, EVENT[%d] = ",*(undefined1 *)(param_1 + 3));
    iVar1 = DebugLevel;
    if (param_3 == 0) goto LAB_001abadc;
  }
  iVar2 = 0;
  iVar1 = DebugLevel;
  do {
    if (0 < iVar1) {
      printk("0x%x ",*(undefined1 *)(param_2 + iVar2));
      iVar1 = DebugLevel;
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < param_3);
LAB_001abadc:
  if (0 < iVar1) {
    printk(&_LC19);
    return;
  }
  return;
}

