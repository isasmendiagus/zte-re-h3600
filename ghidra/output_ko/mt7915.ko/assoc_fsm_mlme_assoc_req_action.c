// module: mt7915.ko
// function: assoc_fsm_mlme_assoc_req_action @ 0x10c630
// size: 224 bytes
//

void assoc_fsm_mlme_assoc_req_action(undefined4 param_1,int param_2)

{
  code *pcVar1;
  int iVar2;
  undefined1 auStack_24 [20];
  
  iVar2 = *(int *)(param_2 + 0x92c);
  log_time_begin(1,auStack_24);
  if (iVar2 == 0) {
    printk(&_LC0,0x5a);
    dump_stack();
    if (-1 < DebugLevel) {
      printk("[%s]: wdev %s\n","assoc_fsm_mlme_assoc_req_action",&_LC3);
    }
  }
  else {
    pcVar1 = (code *)**(undefined4 **)(iVar2 + 0xc98);
    if (pcVar1 == (code *)0x0) {
      if (-1 < DebugLevel) {
        printk("[%s]: wdev %s , assoc_api->mlme_assoc_req_action %s\n",
               "assoc_fsm_mlme_assoc_req_action",&_LC2,&_LC3);
      }
    }
    else {
      (*pcVar1)(param_1,param_2);
    }
    log_time_end(2,"assoc_req",1,auStack_24);
  }
  return;
}

