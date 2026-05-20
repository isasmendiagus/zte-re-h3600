// module: mt7915.ko
// function: AutoChSelScanTimeout @ 0x264d0
// size: 196 bytes
//

void AutoChSelScanTimeout(undefined4 param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  
  iVar3 = *param_2;
  iVar1 = param_2[2];
  iVar2 = HcGetAutoChCtrlbyBandIdx(iVar3,(char)iVar1);
  uVar4 = *(undefined4 *)(iVar2 + 8);
  if (2 < DebugLevel) {
    printk("%s----------------->\n","AutoChSelScanTimeout");
    if (2 < DebugLevel) {
      printk("[AutoChSelScanTimeout] - BandIdx = %d\n",(char)iVar1);
    }
  }
  MlmeEnqueueWithWdev(iVar3,0x2e,1,0,0,0,uVar4);
  RtmpOsMlmeUp(iVar3 + 0x286298);
  if (DebugLevel < 3) {
    return;
  }
  printk("%s<-----------------\n","AutoChSelScanTimeout");
  return;
}

