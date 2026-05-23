// module: mt7915.ko
// function: sync_fsm_init @ 0x10bacc
// size: 676 bytes
//

void sync_fsm_init(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  *(char *)(param_2 * 0xaf5d8 + param_1 + 0x829436) = (char)param_2;
  StateMachineInit(param_3,param_4,4,10,sync_fsm_msg_invalid_state,0,0);
  StateMachineSetMsgChecker(param_3,sync_fsm_msg_checker);
  StateMachineSetAction(param_3,0,0,sync_fsm_join_req_action);
  StateMachineSetAction(param_3,0,2,sync_fsm_scan_req_action);
  StateMachineSetAction(param_3,0,6,sync_fsm_peer_response_idle_action);
  StateMachineSetAction(param_3,0,4,sync_fsm_peer_request_idle_action);
  StateMachineSetAction(param_3,0,9,sync_fsm_wsc_scan_comp_check_action);
  StateMachineSetAction(param_3,1,6,sync_fsm_peer_response_scan_action);
  StateMachineSetAction(param_3,1,5,sync_fsm_peer_response_scan_action);
  StateMachineSetAction(param_3,1,3,sync_fsm_scan_timeout_action);
  StateMachineSetAction(param_3,2,1,sync_fsm_join_timeout_action);
  StateMachineSetAction(param_3,2,6,sync_fsm_peer_response_join_action);
  StateMachineSetAction(param_3,2,5,sync_fsm_peer_response_join_action);
  StateMachineSetAction(param_3,3,2,sync_fsm_scan_req_action);
  StateMachineSetAction(param_3,3,6,sync_fsm_peer_response_idle_action);
  iVar1 = 0;
  do {
    iVar2 = iVar1 + 1;
    StateMachineSetAction(param_3,iVar1,8,sync_fsm_cancel_req_action);
    iVar1 = iVar2;
  } while (iVar2 != 4);
  iVar1 = param_1 + param_2 * 0xaf5d8;
  *(int *)(iVar1 + 0x8293ac) = param_1;
  *(char *)(iVar1 + 0x8293b4) = (char)param_2;
  RTMPInitTimer(param_1,param_1 + param_2 * 0xaf5d8 + 0x8293b8,rtmp_timer_sync_fsm_scan_timeout,
                iVar1 + 0x8293ac,0);
  iVar1 = param_1 + 0x57f9a4;
  do {
    if (*(char *)(iVar1 + 0x1c) == '\0') {
      *(int *)(iVar1 + 0x104) = param_1;
      *(int *)(iVar1 + 0x108) = iVar1 + -0x211e4c;
      RTMPInitTimer(param_1,iVar1,rtmp_timer_sync_fsm_join_timeout,iVar1 + 0x104,0);
    }
    iVar1 = iVar1 + 0x2137b0;
  } while (iVar1 != param_1 + 0x9a6904);
  return;
}

