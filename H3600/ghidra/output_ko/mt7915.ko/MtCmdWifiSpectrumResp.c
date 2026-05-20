// module: mt7915.ko
// function: MtCmdWifiSpectrumResp @ 0x1ad6e4
// size: 156 bytes
//

void MtCmdWifiSpectrumResp(undefined4 param_1,int *param_2,undefined4 param_3)

{
  if (2 < DebugLevel) {
    printk("%s----------------->\n","MtCmdWifiSpectrumResp");
  }
  if (0 < DebugLevel) {
    printk("%s: FuncIndex = %d\n","MtCmdWifiSpectrumResp",*param_2);
  }
  if (*param_2 == 1) {
    MtCmdWifiSpectrumSolicitCapStatusCb(param_1,param_2,param_3);
  }
  if (DebugLevel < 3) {
    return;
  }
  printk("%s<-----------------\n","MtCmdWifiSpectrumResp");
  return;
}

