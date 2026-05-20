// module: mt7915.ko
// function: AutoChSelScanTimeoutAction @ 0x263e8
// size: 212 bytes
//

void AutoChSelScanTimeoutAction(undefined4 param_1,int param_2)

{
  char cVar1;
  undefined1 uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  
  iVar5 = *(int *)(param_2 + 0x92c);
  if (iVar5 == 0) {
    if (DebugLevel < 0) {
      return;
    }
    printk("AutoChSelScanTimeoutAction - pwdev == NULL \n");
    return;
  }
  uVar3 = HcGetBandByWdev(iVar5);
  iVar4 = HcGetAutoChCtrlbyBandIdx(param_1,uVar3);
  cVar1 = *(char *)(iVar4 + 0xc);
  if (2 < DebugLevel) {
    printk("%s----------------->\n","AutoChSelScanTimeoutAction");
  }
  UpdateChannelInfo(param_1,(int)cVar1,3,iVar5);
  uVar2 = AutoChSelFindScanChIdx(param_1,iVar5,(int)cVar1);
  *(undefined1 *)(iVar4 + 0xc) = uVar2;
  AutoChSelScanNextChannel(param_1,iVar5);
  if (DebugLevel < 3) {
    return;
  }
  printk("%s<-----------------\n","AutoChSelScanTimeoutAction");
  return;
}

