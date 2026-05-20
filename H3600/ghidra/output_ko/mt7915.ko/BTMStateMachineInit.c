// module: mt7915.ko
// function: BTMStateMachineInit @ 0x228cc8
// size: 356 bytes
//

void BTMStateMachineInit(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  if (2 < DebugLevel) {
    printk(&_LC4,"BTMStateMachineInit");
  }
  StateMachineInit(param_2,param_3,7,10,Drop,6,0);
  StateMachineSetAction(param_2,1,1,SendBTMQueryIndication);
  StateMachineSetAction(param_2,2,2,SendBTMReq);
  StateMachineSetAction(param_2,2,3,SendBTMReqIE);
  StateMachineSetAction(param_2,2,4,SendBTMReqParam);
  StateMachineSetAction(param_2,2,8,BTMReqTimeout);
  StateMachineSetAction(param_2,5,7,SendBTMConfirm);
  StateMachineSetAction(param_2,5,9,ReceiveBTMRspTimeout);
  StateMachineSetAction(param_2,0,0,SendBTMQuery);
  StateMachineSetAction(param_2,4,6,SendBTMIndication);
  StateMachineSetAction(param_2,3,5,SendBTMRsp);
  return;
}

