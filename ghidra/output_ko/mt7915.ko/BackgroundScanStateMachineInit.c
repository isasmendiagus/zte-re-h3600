// module: mt7915.ko
// function: BackgroundScanStateMachineInit @ 0x22db00
// size: 352 bytes
//

void BackgroundScanStateMachineInit(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  StateMachineInit(param_2,param_3,5,0xe,Drop,0,0);
  StateMachineSetAction(param_2,0,0,BackgroundScanStartAction);
  StateMachineSetAction(param_2,0,10,BackgroundScanWaitAction);
  StateMachineSetAction(param_2,1,1,BackgroundScanTimeoutAction);
  StateMachineSetAction(param_2,1,2,BackgroundScanCancelAction);
  StateMachineSetAction(param_2,1,0xb,BackgroundScanWaitAction);
  StateMachineSetAction(param_2,4,0,BackgroundScanPartialAction);
  StateMachineSetAction(param_2,4,2,BackgroundScanCancelAction);
  StateMachineSetAction(param_2,0,3,BackgroundSwitchChannelAction);
  StateMachineSetAction(param_2,1,0xd,dedicated_rx_hist_scan_timeout_action);
  StateMachineSetAction(param_2,0,0xc,DedicatedZeroWaitStartAction);
  StateMachineSetAction(param_2,2,7,DedicatedZeroWaitRunningAction);
  StateMachineSetAction(param_2,2,8,DedicatedZeroWaitRunningAction);
  return;
}

