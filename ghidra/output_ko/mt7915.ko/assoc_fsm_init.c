// module: mt7915.ko
// function: assoc_fsm_init @ 0x10c980
// size: 464 bytes
//

void assoc_fsm_init(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  StateMachineInit(param_3,param_4,4,0xb,assoc_fsm_msg_invalid_state,0,0);
  StateMachineSetMsgChecker(param_3,assoc_fsm_msg_checker);
  StateMachineSetAction(param_3,0,0,assoc_fsm_mlme_assoc_req_action);
  StateMachineSetAction(param_3,0,1,assoc_fsm_mlme_reassoc_req_action);
  StateMachineSetAction(param_3,0,2,assoc_fsm_mlme_disassoc_req_action);
  StateMachineSetAction(param_3,0,3,assoc_fsm_peer_disassoc_action);
  StateMachineSetAction(param_3,0,4,assoc_fsm_peer_assoc_req_action);
  StateMachineSetAction(param_3,0,6,assoc_fsm_peer_reassoc_req_action);
  StateMachineSetAction(param_3,1,3,assoc_fsm_peer_disassoc_action);
  StateMachineSetAction(param_3,1,5,assoc_fsm_peer_assoc_rsp_action);
  StateMachineSetAction(param_3,1,7,assoc_fsm_peer_assoc_rsp_action);
  StateMachineSetAction(param_3,1,9,assoc_fsm_mlme_assoc_req_timeout_action);
  StateMachineSetAction(param_3,2,3,assoc_fsm_peer_disassoc_action);
  StateMachineSetAction(param_3,2,7,assoc_fsm_peer_reassoc_rsp_action);
  StateMachineSetAction(param_3,2,5,assoc_fsm_peer_reassoc_rsp_action);
  StateMachineSetAction(param_3,2,10,assoc_fsm_mlme_reassoc_req_timeout_action);
  StateMachineSetAction(param_3,3,3,assoc_fsm_peer_disassoc_action);
  StateMachineSetAction(param_3,3,8,assoc_fsm_mlme_disassoc_req_timeout_action);
  *(undefined4 *)(param_2 + 0xbdc) = 0;
  return;
}

