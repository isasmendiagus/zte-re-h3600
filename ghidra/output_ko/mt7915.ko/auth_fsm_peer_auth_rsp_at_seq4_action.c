// module: mt7915.ko
// function: auth_fsm_peer_auth_rsp_at_seq4_action @ 0x10de44
// size: 224 bytes
//

void auth_fsm_peer_auth_rsp_at_seq4_action(undefined4 param_1,int param_2)

{
  code *pcVar1;
  int iVar2;
  undefined1 auStack_24 [20];
  
  iVar2 = *(int *)(param_2 + 0x92c);
  log_time_begin(1,auStack_24);
  if (iVar2 == 0) {
    printk(&_LC0,0x107);
    dump_stack();
    if (-1 < DebugLevel) {
      printk("[%s]: wdev %s\n","auth_fsm_peer_auth_rsp_at_seq4_action",&_LC3);
    }
  }
  else {
    pcVar1 = *(code **)(*(int *)(iVar2 + 0xedc) + 0xc);
    if (pcVar1 == (code *)0x0) {
      if (-1 < DebugLevel) {
        printk("[%s]: wdev %s , auth_api->auth_fsm_peer_auth_rsp_at_seq4_action %s\n",
               "auth_fsm_peer_auth_rsp_at_seq4_action",&_LC2,&_LC3);
      }
    }
    else {
      (*pcVar1)(param_1,param_2);
    }
    log_time_end(2,"peer_auth_rsp_at_seq4",1,auStack_24);
  }
  return;
}

