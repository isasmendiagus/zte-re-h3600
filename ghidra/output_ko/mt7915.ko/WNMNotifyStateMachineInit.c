// module: mt7915.ko
// function: WNMNotifyStateMachineInit @ 0x22a8fc
// size: 156 bytes
//

void WNMNotifyStateMachineInit(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  if (2 < DebugLevel) {
    printk(&_LC4,"WNMNotifyStateMachineInit");
  }
  StateMachineInit(param_2,param_3,3,2,Drop,2,0);
  StateMachineSetAction(param_2,0,0,SendWNMNotifyReq);
  StateMachineSetAction(param_2,1,1,SendWNMNotifyConfirm);
  return;
}

