// module: mt7915.ko
// function: AutoChSelScanReqAction @ 0x2631c
// size: 200 bytes
//

void AutoChSelScanReqAction(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined1 auStack_19 [5];
  
  iVar3 = *(int *)(param_2 + 0x92c);
  if (iVar3 == 0) {
    if (-1 < DebugLevel) {
      printk("AutoChSelScanReqAction - pwdev == NULL \n");
    }
  }
  else {
    uVar1 = HcGetBandByWdev(iVar3);
    iVar2 = HcGetAutoChCtrlbyBandIdx(param_1,uVar1);
    if (2 < DebugLevel) {
      printk("%s----------------->\n","AutoChSelScanReqAction");
    }
    RTMPCancelTimer(iVar2 + 0x18,auStack_19);
    APAutoChannelInit(param_1,iVar3);
    AutoChSelScanNextChannel(param_1,iVar3);
    if (2 < DebugLevel) {
      printk("%s<-----------------\n","AutoChSelScanReqAction");
    }
  }
  return;
}

