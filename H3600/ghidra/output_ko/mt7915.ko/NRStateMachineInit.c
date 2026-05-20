// module: mt7915.ko
// function: NRStateMachineInit @ 0x2234b0
// size: 188 bytes
//

void NRStateMachineInit(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  if (2 < DebugLevel) {
    printk(&_LC50,"NRStateMachineInit");
  }
  StateMachineInit(param_2,param_3,2,3,Drop,1,0);
  StateMachineSetAction(param_2,0,0,send_nr_resp_toair);
  StateMachineSetAction(param_2,0,1,send_nr_rsp_param_toair);
  StateMachineSetAction(param_2,0,2,NRRspTimeout);
  return;
}

