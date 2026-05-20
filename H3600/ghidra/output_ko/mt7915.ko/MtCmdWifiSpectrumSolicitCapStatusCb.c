// module: mt7915.ko
// function: MtCmdWifiSpectrumSolicitCapStatusCb @ 0x1ad654
// size: 140 bytes
//

void MtCmdWifiSpectrumSolicitCapStatusCb(int param_1,int param_2)

{
  char *pcVar1;
  int iVar2;
  int *piVar3;
  
  piVar3 = *(int **)(param_1 + 0xc);
  if (2 < DebugLevel) {
    printk("%s----------------->\n","MtCmdWifiSpectrumSolicitCapStatusCb");
  }
  iVar2 = *(int *)(param_2 + 4);
  *piVar3 = iVar2;
  if (DebugLevel < 1) {
    return;
  }
  pcVar1 = "Capture done!!";
  if (iVar2 != 1) {
    pcVar1 = "Not yet!!";
  }
  printk(&_LC68,pcVar1);
  if (DebugLevel < 3) {
    return;
  }
  printk("%s<-----------------\n","MtCmdWifiSpectrumSolicitCapStatusCb");
  return;
}

