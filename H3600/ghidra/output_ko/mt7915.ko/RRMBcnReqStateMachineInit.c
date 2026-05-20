// module: mt7915.ko
// function: RRMBcnReqStateMachineInit @ 0x2233f8
// size: 180 bytes
//

void RRMBcnReqStateMachineInit(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  if (2 < DebugLevel) {
    printk(&_LC50,"RRMBcnReqStateMachineInit");
  }
  StateMachineInit(param_2,param_3,3,3,Drop,0,0);
  StateMachineSetAction(param_2,1,0,SendBcnReqToAir_SetParam);
  StateMachineSetAction(param_2,1,1,SendBcnReqToAir_Raw);
  StateMachineSetAction(param_2,2,2,BcnRepTimeout);
  return;
}

