// module: mt7915.ko
// function: sta_mlme_auth_req_action @ 0x76ad0
// size: 384 bytes
//

void sta_mlme_auth_req_action(int param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar2 = GetStaCfgByWdev(param_1,*(undefined4 *)(param_2 + 0x92c));
  iVar4 = *(int *)(param_2 + 0x92c);
  bVar1 = *(byte *)(iVar4 + 0xe);
  if (0 < DebugLevel) {
    printk("%s:wdev(type=%d,wdev_idx=%d,wdev_func_idx=%d\n","sta_mlme_auth_req_action",
           *(undefined4 *)(iVar4 + 0x14),*(undefined1 *)(iVar4 + 0xc),bVar1);
  }
  if (iVar2 == 0) {
    printk(&_LC3,0xe1);
    dump_stack();
    if (iVar4 != 0) {
      return;
    }
    printk(&_LC1,0xe2);
    dump_stack();
    return;
  }
  if (iVar4 == 0) {
    printk(&_LC1,0xe2);
    dump_stack();
  }
  iVar3 = *(int *)(iVar4 + 0x14);
  if ((*(char *)(param_1 + 0x286285) == '\x01') && (iVar3 == 2)) {
    iVar3 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
    if (*(byte *)(iVar3 + 0x14a) <= bVar1) {
      return;
    }
    iVar3 = *(int *)(iVar4 + 0x14);
  }
  if (iVar3 == 0x100) {
    iVar2 = *(int *)(iVar4 + 4) + 0x3c;
  }
  else {
    iVar2 = iVar2 + 0x211e80;
  }
  iVar2 = sta_send_auth_req(param_1,param_2,iVar2,&_LC30,1,0,0);
  if (iVar2 == 0) {
    auth_fsm_state_transition(iVar4,0,"sta_mlme_auth_req_action");
    cntl_auth_assoc_conf(*(undefined4 *)(param_2 + 0x92c),2,0x51);
    return;
  }
  auth_fsm_state_transition(iVar4,1,"sta_mlme_auth_req_action");
  return;
}

