// module: mt7915.ko
// function: assoc_fsm_peer_assoc_rsp_action @ 0x10c468
// size: 224 bytes
//

void assoc_fsm_peer_assoc_rsp_action(undefined4 param_1,int param_2)

{
  code *pcVar1;
  int iVar2;
  undefined1 auStack_24 [20];
  
  iVar2 = *(int *)(param_2 + 0x92c);
  log_time_begin(1,auStack_24);
  if (iVar2 == 0) {
    printk(&_LC0,0xd9);
    dump_stack();
    if (-1 < DebugLevel) {
      printk("[%s]: wdev %s\n","assoc_fsm_peer_assoc_rsp_action",&_LC3);
    }
  }
  else {
    pcVar1 = *(code **)(*(int *)(iVar2 + 0xc98) + 4);
    if (pcVar1 == (code *)0x0) {
      if (-1 < DebugLevel) {
        printk("[%s]: wdev %s , assoc_api->peer_assoc_rsp_action %s\n",
               "assoc_fsm_peer_assoc_rsp_action",&_LC2,&_LC3);
      }
    }
    else {
      (*pcVar1)(param_1,param_2);
    }
    log_time_end(2,"peer_assoc_rsp",1,auStack_24);
  }
  return;
}

