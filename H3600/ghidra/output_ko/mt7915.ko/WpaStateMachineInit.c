// module: mt7915.ko
// function: WpaStateMachineInit @ 0x1187bc
// size: 232 bytes
//

void WpaStateMachineInit(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  StateMachineInit(param_2,param_3,1,7,Drop,0,0);
  StateMachineSetAction(param_2,0,0,WpaEAPPacketAction);
  StateMachineSetAction(param_2,0,1,WpaEAPOLStartAction);
  StateMachineSetAction(param_2,0,2,WpaEAPOLLogoffAction);
  StateMachineSetAction(param_2,0,3,WpaEAPOLKeyAction);
  StateMachineSetAction(param_2,0,4,WpaEAPOLASFAlertAction);
  StateMachineSetAction(param_2,0,5,WpaEAPOLRetryAction);
  StateMachineSetAction(param_2,0,6,wpa_2way_action);
  return;
}

