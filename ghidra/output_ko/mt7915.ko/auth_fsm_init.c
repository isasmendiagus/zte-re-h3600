// module: mt7915.ko
// function: auth_fsm_init @ 0x10e214
// size: 464 bytes
//

void auth_fsm_init(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  StateMachineInit(param_3,param_4,4,10,auth_fsm_msg_invalid_state,0,0);
  StateMachineSetAction(param_3,0,0,auth_fsm_mlme_auth_req_action);
  StateMachineSetAction(param_3,0,4,auth_fsm_peer_deauth_action);
  StateMachineSetAction(param_3,0,6,auth_fsm_peer_auth_req_action);
  StateMachineSetAction(param_3,0,7,auth_fsm_peer_auth_confirm_action);
  StateMachineSetAction(param_3,0,5,auth_fsm_mlme_deauth_req_action);
  StateMachineSetAction(param_3,1,1,auth_fsm_peer_auth_rsp_at_seq2_action);
  StateMachineSetAction(param_3,1,4,auth_fsm_peer_deauth_action);
  StateMachineSetAction(param_3,1,3,auth_fsm_auth_timeout_action);
  StateMachineSetAction(param_3,1,5,auth_fsm_mlme_deauth_req_action);
  StateMachineSetAction(param_3,2,1,auth_fsm_peer_auth_rsp_at_seq4_action);
  StateMachineSetAction(param_3,2,4,auth_fsm_peer_deauth_action);
  StateMachineSetAction(param_3,2,3,auth_fsm_auth_timeout_action);
  StateMachineSetAction(param_3,2,5,auth_fsm_mlme_deauth_req_action);
  StateMachineSetAction(param_3,0,8,auth_fsm_sae_auth_req_action);
  StateMachineSetAction(param_3,3,9,auth_fsm_sae_auth_rsp_action);
  StateMachineSetAction(param_3,3,4,auth_fsm_peer_deauth_action);
  StateMachineSetAction(param_3,3,3,auth_fsm_auth_timeout_action);
  *(undefined4 *)(param_2 + 0xe30) = 0;
  return;
}

