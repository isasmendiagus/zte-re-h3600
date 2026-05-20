// module: mt7915.ko
// function: cntl_state_machine_init @ 0x10d12c
// size: 544 bytes
//

void cntl_state_machine_init(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  
  StateMachineSetMsgChecker(param_2,cntl_fsm_msg_checker);
  StateMachineInit(param_2,param_3,7,0xd,cntl_mlme_error_handle,0,0);
  StateMachineSetAction(param_2,0,0,cntl_mlme_connect);
  StateMachineSetAction(param_2,0,5,cntl_mlme_disconnect);
  StateMachineSetAction(param_2,0,8,cntl_mlme_scan);
  StateMachineSetAction(param_2,0,9,cntl_mlme_scan_conf);
  StateMachineSetAction(param_2,0,1,cntl_mlme_join_conf);
  StateMachineSetAction(param_2,1,1,cntl_mlme_join_conf);
  StateMachineSetAction(param_2,1,9,cntl_mlme_scan_conf);
  StateMachineSetAction(param_2,1,8,cntl_mlme_scan);
  StateMachineSetAction(param_2,2,2,cntl_mlme_auth_conf);
  StateMachineSetAction(param_2,2,5,cntl_mlme_disconnect);
  StateMachineSetAction(param_2,3,2,cntl_mlme_auth2_conf);
  StateMachineSetAction(param_2,3,5,cntl_mlme_disconnect);
  StateMachineSetAction(param_2,4,6,cntl_mlme_deauth_conf);
  StateMachineSetAction(param_2,5,3,cntl_mlme_assoc_conf);
  StateMachineSetAction(param_2,5,4,cntl_mlme_reassoc_conf);
  StateMachineSetAction(param_2,5,5,cntl_mlme_disconnect);
  StateMachineSetAction(param_2,6,7,cntl_mlme_disassoc_conf);
  iVar1 = 0;
  do {
    iVar2 = iVar1 + 1;
    StateMachineSetAction(param_2,iVar1,0xc,cntl_mlme_reset_all_fsm);
    iVar1 = iVar2;
  } while (iVar2 != 7);
  *(undefined4 *)(param_1 + 0xca8) = 0;
  return;
}

