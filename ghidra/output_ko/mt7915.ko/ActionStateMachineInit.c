// module: mt7915.ko
// function: ActionStateMachineInit @ 0xa1d9c
// size: 544 bytes
//

void ActionStateMachineInit(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  StateMachineInit(param_2,param_3,1,0x20,Drop,0,0);
  StateMachineSetAction(param_2,0,0,PeerSpectrumAction);
  StateMachineSetAction(param_2,0,1,PeerQOSAction);
  StateMachineSetAction(param_2,0,2,ReservedAction);
  StateMachineSetAction(param_2,0,3,PeerBAAction);
  StateMachineSetAction(param_2,0,7,PeerHTAction);
  StateMachineSetAction(param_2,0,0x15,PeerVHTAction);
  StateMachineSetAction(param_2,0,0x17,MlmeADDBAAction);
  StateMachineSetAction(param_2,0,0x18,MlmeDELBAAction);
  StateMachineSetAction(param_2,0,0x19,MlmeDELBAAction);
  StateMachineSetAction(param_2,0,4,PeerPublicAction);
  StateMachineSetAction(param_2,0,5,PeerRMAction);
  StateMachineSetAction(param_2,0,0x1a,MlmeQOSAction);
  StateMachineSetAction(param_2,0,0x1b,MlmeDLSAction);
  StateMachineSetAction(param_2,0,0x1f,MlmeInvalidAction);
  StateMachineSetAction(param_2,0,8,PMF_PeerAction);
  StateMachineSetAction(param_2,0,10,PeerWNMAction);
  StateMachineSetAction(param_2,0,0x16,peer_twt_action);
  StateMachineSetAction(param_2,0,0x1c,mlme_twt_teradown_action);
  StateMachineSetAction(param_2,0,0x1e,twtMlmeSetupAction);
  StateMachineSetAction(param_2,0,0x1d,sta_send_event_report);
  return;
}

