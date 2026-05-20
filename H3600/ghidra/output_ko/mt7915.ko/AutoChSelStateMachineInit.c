// module: mt7915.ko
// function: AutoChSelStateMachineInit @ 0x26598
// size: 244 bytes
//

void AutoChSelStateMachineInit
               (undefined4 param_1,undefined1 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  iVar2 = HcGetAutoChCtrlbyBandIdx();
  iVar1 = DebugLevel;
  *(undefined4 *)(iVar2 + 0x254) = param_1;
  *(undefined1 *)(iVar2 + 0x25c) = param_2;
  if (2 < iVar1) {
    printk("%s----------------->\n","AutoChSelStateMachineInit");
  }
  StateMachineInit(param_3,param_4,2,2,Drop,0,0);
  StateMachineSetAction(param_3,0,0,AutoChSelScanReqAction);
  StateMachineSetAction(param_3,1,1,AutoChSelScanTimeoutAction);
  RTMPInitTimer(param_1,iVar2 + 0x18,rtmp_timer_AutoChSelScanTimeout,iVar2 + 0x254,0);
  if (DebugLevel < 3) {
    return;
  }
  printk("%s<-----------------\n","AutoChSelStateMachineInit");
  return;
}

