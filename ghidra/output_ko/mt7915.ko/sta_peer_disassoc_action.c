// module: mt7915.ko
// function: sta_peer_disassoc_action @ 0x7cf88
// size: 384 bytes
//

void sta_peer_disassoc_action(undefined4 param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined2 local_20;
  undefined1 auStack_1e [6];
  
  uVar4 = *(undefined4 *)(param_2 + 0x92c);
  iVar1 = GetStaCfgByWdev(param_1,uVar4);
  if (iVar1 == 0) {
    printk(&_LC1,0x999);
    dump_stack();
    return;
  }
  if (*(int *)(iVar1 + 0x12f4) == 0x1a) {
    uVar3 = RTMPMsecsToJiffies(200);
    wait_for_completion_timeout(iVar1 + 0x3f44,uVar3);
  }
  if (2 < DebugLevel) {
    printk("ASSOC - PeerDisassocAction()\n");
  }
  iVar2 = PeerDisassocSanity(param_1,param_2,*(undefined4 *)(param_2 + 0x908),auStack_1e,&local_20);
  if (iVar2 == 0) {
    if (2 < DebugLevel) {
      printk("ASSOC - PeerDisassocAction() sanity check fail\n");
    }
  }
  else {
    if (2 < DebugLevel) {
      printk("ASSOC - PeerDisassocAction() Reason = %d\n",local_20);
    }
    if (((*(uint *)(iVar1 + 0x212464) & 1) != 0) &&
       (iVar1 = memcmp((void *)(iVar1 + 0x212428),auStack_1e,6), iVar1 == 0)) {
      cntl_fsm_state_transition(uVar4,6,"sta_peer_disassoc_action");
      iVar1 = cntl_auth_assoc_conf(uVar4,7,local_20);
      if (iVar1 == 0) {
        LinkDown(param_1,2,uVar4,param_2);
      }
      assoc_fsm_state_transition(*(undefined4 *)(param_2 + 0x92c),0);
      return;
    }
  }
  return;
}

